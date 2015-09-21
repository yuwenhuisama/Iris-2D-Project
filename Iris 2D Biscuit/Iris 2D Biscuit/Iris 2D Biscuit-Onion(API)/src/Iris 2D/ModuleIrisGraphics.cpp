#include "ModuleIrisGraphics.h"
namespace Iris2D{

	typedef union
	{
		ARGB Color;
		struct
		{
			BYTE Blue;
			BYTE Green;
			BYTE Red;
			BYTE Alpha;
		};
	}ARGBQuad, *PARGBQuad;

	int ModuleIrisGraphics::width;
	int ModuleIrisGraphics::height;
	IDirect3DDevice9 *ModuleIrisGraphics::Device;
	IDirect3DTexture9* ModuleIrisGraphics::ExchangeTexture = 0;
	IDirect3DVertexBuffer9* ModuleIrisGraphics::ExchangeVertex = 0;

	IDirect3DTexture9* ModuleIrisGraphics::FreezedTexture = 0;
	IDirect3DTexture9* ModuleIrisGraphics::TransitionTexture = 0;

	float ModuleIrisGraphics::frameRate = 0;
	unsigned long ModuleIrisGraphics::frameCount = 0;
	float ModuleIrisGraphics::brightness = 255;

	list<IIrisViewport*> ModuleIrisGraphics::viewports;
	IIrisViewport* ModuleIrisGraphics::gViewport;

	HWND ModuleIrisGraphics::hwnd = 0;

	bool ModuleIrisGraphics::isFreeze = false;
	bool ModuleIrisGraphics::isTransition = false;

	bool ModuleIrisGraphics::ViewportSortFunc(IIrisViewport*& vp1, IIrisViewport*& vp2){
		return vp1->GetZ() > vp2->GetZ();
	}

	void ModuleIrisGraphics::SortViewports(){
		viewports.sort(ViewportSortFunc);
	}

	int ModuleIrisGraphics::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	{
		UINT  num = 0;          // number of image encoders
		UINT  size = 0;         // size of the image encoder array in bytes
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		if (size == 0)
			return -1;  // Failure
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
			return -1;  // Failure
		GetImageEncoders(num, size, pImageCodecInfo);
		for (UINT j = 0; j < num; ++j)
		{
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;  // Success
			}
		}
		free(pImageCodecInfo);
		return -1;  // Failure
	}

	ModuleIrisGraphics::ModuleIrisGraphics(void)
	{
	}

	bool ModuleIrisGraphics::MakeExchangeTexture(){
		if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, &(ExchangeTexture), NULL)))
			return false;;
		if (FAILED(Device->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &FreezedTexture, NULL)))
			return false;
		if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, &(TransitionTexture), NULL)))
			return false;
		return true;
	}

	bool ModuleIrisGraphics::MakeExchangeVertex(){
		HRESULT r = Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(ExchangeVertex), 0);

		if (FAILED(r))
		{
			MessageBox(NULL, L"Create buffer failed!", L"Error", 0);
			return false;
		}

		Iris2DVertex* v;
		if(FAILED(ExchangeVertex->Lock(0, 0, (void**)&v, 0))) return false;
		/* persist to change*/
		/*
		v[0] = Iris2DVertex(0.0f, (float)height, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)width, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f, (float)height, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)width, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)width, (float)height, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
		*/

		v[0] = Iris2DVertex(0.0f, (float)height, 0.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)width, 0.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f, (float)height, 0.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)width, 0.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)width, (float)height, 0.0f, 1.0f, 1.0f);
		
		v[0]._u += 0.5f / width; v[0]._v += 0.5f / height;
		v[1]._u += 0.5f / width; v[1]._v += 0.5f / height;
		v[2]._u += 0.5f / width; v[2]._v += 0.5f / height;
		v[3]._u += 0.5f / width; v[3]._v += 0.5f / height;
		v[4]._u += 0.5f / width; v[4]._v += 0.5f / height;
		v[5]._u += 0.5f / width; v[5]._v += 0.5f / height;

		if (FAILED(ExchangeVertex->Unlock())) return false;
		return true;
	}

	bool ModuleIrisGraphics::Init(){
		gViewport = new IrisViewport(0, 0, (float)ModuleIrisGraphics::width, (float)ModuleIrisGraphics::height);
		if (!MakeExchangeTexture()) return false;
		if (!MakeExchangeVertex()) return false;
		return true;
	}

	void ModuleIrisGraphics::AddViewport(IIrisViewport *viewport){
		viewports.push_back(viewport);
	}

	void ModuleIrisGraphics::DeleteViewport(IIrisViewport *viewport){
		viewports.remove(viewport);
	}

	IIrisViewport* ModuleIrisGraphics::GetGViewport(){
		return gViewport;
	}

	void ModuleIrisGraphics::SetDevice(IDirect3DDevice9 *tDevice){
		Device = tDevice;
	}

	IDirect3DDevice9* ModuleIrisGraphics::GetDevice(){
		return Device;
	}

	void ModuleIrisGraphics::Update(IR_PARAM_RESULT_CT){

		IrisApp* app = IrisApp::Instance();
		IrisShader* shader;
		D3DXMATRIX proj;

		HRESULT hr = Device->TestCooperativeLevel();
		if (hr == D3DERR_DEVICENOTRESET){
			app->OnDeviceLost();
			Device->Reset(&app->curD3DParameters);
			app->OnDeviceRecover();
		}

		ModuleIrisAudio::Update();

		shader = IrisShader::Instance();
		D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::GetWidth(), (float)ModuleIrisGraphics::GetHeight(), 0.0f, 0, 9999.0f);

		while (!app->CanDisplay){
			if (app->MessageLoop() == WM_QUIT){
				app->GoQuit();
				IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
				return;
			}
		}

		IrisApp::Instance()->CanDisplay = false;
		
		// 如果正在渐变，那么不更新Viewport和Sprite
		if (!isTransition)
			if (!ModuleIrisGraphics::UpdateSpritesAndViewports(shader, proj)){
				IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Updating Sprites And Viewports !")
				return;
			}
		// 如果正在冻结，那么不把后台交换页画上去
		if (!isFreeze)
			if (!ModuleIrisGraphics::UpdateBackBuffer(shader, proj)){
				IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Updating Backbuffer !")
				return;
			}
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	bool ModuleIrisGraphics::UpdateSpritesAndViewports(IrisShader*& shader, D3DXMATRIX& proj){
		// 把Viewport的Sprite画到各自Viewport的Texure上
		list<IIrisViewport*>::iterator it;
		for (it = viewports.begin(); it != viewports.end(); it++){
			static_cast<IrisViewport*>((*it))->RenderSurface();
		}

		// 把Viewport的Texture画到后台交换页上
		IDirect3DSurface9* eSurface;
		IDirect3DSurface9* oldSurface;
		if(FAILED(ModuleIrisGraphics::ExchangeTexture->GetSurfaceLevel(0, &(eSurface)))) return false;
		Device->GetRenderTarget(0, &oldSurface);
		Device->SetRenderTarget(0, eSurface);

		// shader
		shader->SetViewportProjMatrix(proj);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		shader->DoViewportShade(viewports);

		Device->EndScene();
		Device->SetRenderTarget(0, oldSurface);
		eSurface->Release();
		oldSurface->Release();

		return true;
	}

	bool ModuleIrisGraphics::UpdateBackBuffer(IrisShader*& shader, D3DXMATRIX& proj){

		shader->SetBackbufferProjMatrix(proj);
		// 最后把后台交换页画到后台缓存上
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		shader->DoBackBufferShade();

		Device->EndScene();
		Device->Present(0, 0, 0, 0);

		return true;
	}

	void ModuleIrisGraphics::DisposeAllGraphicsSource(){
		ModuleIrisGraphics::DeleteViewport(ModuleIrisGraphics::gViewport);

		list<IIrisViewport*>::iterator it;
		for (it = viewports.begin(); it != viewports.end(); it++){
			static_cast<IrisViewport*>((*it))->AutoDispose();
		}

		list<IIrisSprite*> sprites = static_cast<IrisViewport*>(ModuleIrisGraphics::gViewport)->GetSprites();
		list<IIrisSprite*>::iterator its = sprites.begin();
		for (its = sprites.begin(); its != sprites.end(); its++){
			static_cast<IrisSprite*>((*its))->AutoDispose();
		}
	}

	void ModuleIrisGraphics::Wait(int duration, IR_PARAM_RESULT_CT){
		for (int i = 0; i < duration; i++){
			Update(IR_PARAM);
			if (IR_PARAM && IR_FAILD(*_rParam))
				return;
		}
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::Freeze(IR_PARAM_RESULT_CT){
		bool flag = true;

		isFreeze = true;

		// 保存当前BackBuffer
		IDirect3DSurface9* EXSurface;
		IDirect3DSurface9* ExchangeSurface;
		if (FAILED(ExchangeTexture->GetSurfaceLevel(0, &EXSurface))) flag = false;
		if (FAILED((Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &ExchangeSurface, 0)))) flag = false;
		if (FAILED(Device->GetRenderTargetData(EXSurface, ExchangeSurface))) flag = false;

		D3DLOCKED_RECT rect;
		memset(&rect, 0, sizeof(rect));
		if (FAILED((FreezedTexture->LockRect(0, &rect, NULL, 0)))) flag = false;

		PARGBQuad p1 = (PARGBQuad)rect.pBits;
		PARGBQuad c1 = 0;

		D3DLOCKED_RECT rc;
		memset(&rc, 0, sizeof(rc));
		if (FAILED(ExchangeSurface->LockRect(&rc, 0, D3DLOCK_NOOVERWRITE))) flag = false;

		PARGBQuad p2 = (PARGBQuad)rc.pBits;
		PARGBQuad c2 = 0;

		memcpy(p1, p2, width * height * sizeof(ARGBQuad));

		if (FAILED(ExchangeSurface->UnlockRect())) flag = false;
		if (FAILED(FreezedTexture->UnlockRect(0))) flag = false;
		if (FAILED(EXSurface->Release())) flag = false;
		if (FAILED(ExchangeSurface->Release())) flag = false;

		//D3DXSaveTextureToFile(L"a.bmp", D3DXIFF_BMP, FreezedTexture, 0);

 		if (!flag)
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Freeazing !")
		else
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::Transition(int duration, wstring filename, int vague, IR_PARAM_RESULT_CT){

		if (duration < 0){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Duration of Transition !")
			return;
		}

		if (vague < 0) vague = 0;
		else if (vague > 256) vague = 256;

		float changeVague = vague / 256.0f;

		if (!isFreeze){
			Freeze(IR_PARAM);
			if (IR_PARAM && IR_FAILD(*IR_PARAM))
				return;
		}
		Update(IR_PARAM);
		isFreeze = false;
		isTransition = true;
		if (IR_PARAM && IR_FAILD(*IR_PARAM))
			return;

		IDirect3DTexture9* maskTexture = NULL;
		IrisBitmap* mask = NULL;
		IrisShader* shader = IrisShader::Instance();
		if (filename == L"")
			shader->SetTransitionType(0);
		else {
			shader->SetTransitionType(1);
			mask = new IrisBitmap(filename, IR_PARAM);
			if (IR_PARAM && IR_FAILD(*IR_PARAM)){
				delete mask;
				return;
			}
			//if (mask->GetWidth() != ModuleIrisGraphics::GetWidth() ||
			//	mask->GetHeight() != ModuleIrisGraphics::GetHeight()){
			//	IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in File Size of Transition !")
			//	delete mask;
			//	return;
			//}
			if (!mask->MakeTexture(mask->limitRect)){
				IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Transition !")
				delete mask;
				return;
			}
			maskTexture = mask->GetTexture();
		}

		IDirect3DSurface9* eSurface;
		IDirect3DSurface9* oldSurface;

		D3DXMATRIX proj;
		D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::GetWidth(), (float)ModuleIrisGraphics::GetHeight(), 0.0f, 0, 9999.0f);
		shader->SetTransitionProjMatrix(proj);

		// gray值越大越先消失
		float cmp = 1.0f;
		float step = cmp / duration;
		ModuleIrisGraphics::TransitionTexture->GetSurfaceLevel(0, &eSurface);
		while (cmp >= 0){
			/* 先画到TransitionTexturer上 */
			Device->GetRenderTarget(0, &oldSurface);
			Device->SetRenderTarget(0, eSurface);
			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
			Device->BeginScene();
			shader->DoTransitionShade(maskTexture, 1.0f - cmp, changeVague);
			Device->EndScene();
			//D3DXSaveTextureToFile(L"a.bmp", D3DXIFF_BMP, ExchangeTexture, 0);
			/* 最后画到backbuffer上 */
			Device->SetRenderTarget(0, oldSurface);
			if (IR_PARAM && IR_FAILD(*IR_PARAM)){
				if (mask) delete mask;
				return;
			}
			Update(IR_PARAM);
			cmp -= step;
		}
		if (mask)
			delete mask;
		isTransition = false;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::FadeOut(int duration, IR_PARAM_RESULT_CT){
		if (brightness == 0.0f)
			return;
		for (int i = 0; i < duration; i++){
			brightness -= 255.0f / duration;
			if (brightness < 0.0f) brightness = 0.0f;
			Update(IR_PARAM);
			if (IR_PARAM && IR_FAILD(*IR_PARAM))
				return;
		}
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::FadeIn(int duration, IR_PARAM_RESULT_CT){
		if (brightness == 255.0f)
			return;
		for (int i = 0; i < duration; i++){
			brightness += 255.0f / duration;
			if (brightness > 255.0f) brightness = 255.0f;
			Update(IR_PARAM);
			if (IR_PARAM && IR_FAILD(*IR_PARAM))
				return;
		}
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT_CT){
		bool flag = true;
		IDirect3DSurface9* EXSurface;
		IDirect3DSurface9* ExchangeSurface;
		if(FAILED(ExchangeTexture->GetSurfaceLevel(0, &EXSurface))) flag = false;
		if(FAILED(Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &ExchangeSurface, 0))) flag = false;
		if (FAILED(Device->GetRenderTargetData(EXSurface, ExchangeSurface))) flag = false;

		D3DLOCKED_RECT rc;
		memset(&rc, 0, sizeof(rc));
		if (FAILED(ExchangeSurface->LockRect(&rc, 0, D3DLOCK_NOOVERWRITE))) flag = false;
		PARGBQuad p2 = (PARGBQuad)rc.pBits;
		PARGBQuad c2 = 0;
		IrisColor color(0, 0, 0, 0);
		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				c2 = p2 + x + y * rc.Pitch / sizeof(ARGBQuad);
				color.Set(c2->Red, c2->Green, c2->Blue, c2->Alpha);
				bitmap->SetPixel(x, y, &color);
			}
		}

		if (FAILED(ExchangeSurface->UnlockRect())) flag = false;
		if (FAILED(EXSurface->Release())) flag = false;
		if (FAILED(ExchangeSurface->Release())) flag = false;
		if (!flag)
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Snap2Bitmap")
		else
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	int ModuleIrisGraphics::GetBrightness(){
		return (int)ModuleIrisGraphics::brightness;
	}

	void ModuleIrisGraphics::SetBrightness(int bs){
		float tbrightness = (float)(bs > 255 ? 255 : bs < 0 ? 0 : bs);
		ModuleIrisGraphics::brightness = tbrightness;
	}

	void ModuleIrisGraphics::FrameReset(){
		ModuleIrisGraphics::frameCount = 0;
	}

	void ModuleIrisGraphics::ResizeScreen(int width, int height, IR_PARAM_RESULT_CT){
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void ModuleIrisGraphics::SetWidth(int w){
		width = w;
	}

	int ModuleIrisGraphics::GetWidth(){
		return width;
	}

	void ModuleIrisGraphics::SetHeight(int h){
		height = h;
	}

	int ModuleIrisGraphics::GetHeight(){
		return height;
	}

	void ModuleIrisGraphics::SetHwnd(HWND hWnd){
		hwnd = hWnd;
	}

	HWND ModuleIrisGraphics::GetHwnd(){
		return hwnd;
	}

	unsigned long ModuleIrisGraphics::GetFrameCount(){
		return frameCount;
	}

	float ModuleIrisGraphics::GetFrameRate() {
		return frameRate;
	}

	void ModuleIrisGraphics::OnDeviceLost(){
		ExchangeTexture->Release();
		ExchangeVertex->Release();
		FreezedTexture->Release();
		TransitionTexture->Release();
		list<IIrisViewport*>::iterator it;
		for (it = viewports.begin(); it != viewports.end(); ++it){
			(static_cast<IrisViewport*>(*it))->OnDeviceLost();
		}
		IrisBitmap::OnRelease();
	}

	void ModuleIrisGraphics::OnDeviceRecover(){
		MakeExchangeVertex();
		MakeExchangeTexture();
		list<IIrisViewport*>::iterator it;
		for (it = viewports.begin(); it != viewports.end(); ++it){
			(static_cast<IrisViewport*>(*it))->OnDeviceRecover();
		}
		IrisBitmap::OnRecover();
	}

	ModuleIrisGraphics::~ModuleIrisGraphics(void)
	{
	}
}