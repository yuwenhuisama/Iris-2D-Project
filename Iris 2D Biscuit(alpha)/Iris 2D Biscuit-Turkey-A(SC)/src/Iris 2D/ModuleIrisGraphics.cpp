#include "ModuleIrisGraphics.h"

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

list<IrisViewport*> ModuleIrisGraphics::viewports;
IrisViewport* ModuleIrisGraphics::gViewport;

HWND ModuleIrisGraphics::hwnd = 0;

bool ModuleIrisGraphics::isFreeze = false;

int ModuleIrisGraphics::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}


bool ModuleIrisGraphics::compareViewprotWithZ(IrisViewport *v1, IrisViewport *v2){
	return v1->GetZ() < v2->GetZ();
}

void ModuleIrisGraphics::sortViewports(){
	ModuleIrisGraphics::viewports.sort(ModuleIrisGraphics::compareViewprotWithZ);
}

ModuleIrisGraphics::ModuleIrisGraphics(void)
{
}

void ModuleIrisGraphics::MakeExchangeTexture(){
	Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &(ExchangeTexture), NULL);
	Device->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &FreezedTexture, NULL);
	Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &(TransitionTexture), NULL);
}

void ModuleIrisGraphics::MakeExchangeVertex(){
	HRESULT r = Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(ExchangeVertex), 0);

	if (FAILED(r))
	{
		MessageBox(NULL, L"Create buffer failed!", L"Error", 0);
	}

	Iris2DVertex* v;
	ExchangeVertex->Lock(0, 0, (void**)&v, 0);
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
	ExchangeVertex->Unlock();
}

void ModuleIrisGraphics::Init(){
	gViewport = new IrisViewport(0, 0, (float)ModuleIrisGraphics::width, (float)ModuleIrisGraphics::height);
	MakeExchangeTexture();
	MakeExchangeVertex();
}

void ModuleIrisGraphics::addViewport(IrisViewport *viewport){
	viewports.push_back(viewport);
}

void ModuleIrisGraphics::deleteViewport(IrisViewport *viewport){
	viewports.remove(viewport);
}

IrisViewport* ModuleIrisGraphics::getGViewport(){
	return gViewport;
}

void ModuleIrisGraphics::setDevice(IDirect3DDevice9 *tDevice){
	Device = tDevice;
}

void ModuleIrisGraphics::Update(){

	IrisApp* app = IrisApp::Instance();
	IrisShader* shader;
	D3DXMATRIX proj;

	shader = IrisShader::Instance();
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::getWidth(), (float)ModuleIrisGraphics::getHeight(), 0.0f, 0, 9999.0f);

	while (!app->CanDisplay){
		if (app->MessageLoop() == WM_QUIT){
			app->GoQuit();
			return;
		}
	}

	IrisApp::Instance()->CanDisplay = false;

	ModuleIrisGraphics::UpdateSpritesAndViewports(shader, proj);
	// 如果正在冻结，那么不把后台交换页画上去
	if (!isFreeze)
		ModuleIrisGraphics::UpdateBackBuffer(shader, proj);
}


void ModuleIrisGraphics::UpdateSpritesAndViewports(IrisShader*& shader, D3DXMATRIX& proj){
	// 把Viewport的Sprite画到各自Viewport的Texure上
	list<IrisViewport*>::iterator it;
	for (it = viewports.begin(); it != viewports.end(); it++){
		(*it)->RenderSurface();
	}

	// 把Viewport的Texture画到后台交换页上
	IDirect3DSurface9* eSurface;
	IDirect3DSurface9* oldSurface;
	ModuleIrisGraphics::ExchangeTexture->GetSurfaceLevel(0, &(eSurface));
	Device->GetRenderTarget(0, &oldSurface);
	Device->SetRenderTarget(0, eSurface);

	// shader
	shader->SetViewportProjMatrix(proj);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	Device->BeginScene();

	shader->DoViewportShade(viewports);

	Device->EndScene();
	Device->SetRenderTarget(0, oldSurface);
}

void ModuleIrisGraphics::UpdateBackBuffer(IrisShader*& shader, D3DXMATRIX& proj){

	shader->SetBackbufferProjMatrix(proj);
	// 最后把后台交换页画到后台缓存上
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	Device->BeginScene();

	shader->DoBackBufferShade();

	Device->EndScene();
	
	Device->Present(0, 0, 0, 0);
}

void ModuleIrisGraphics::disposeAllGraphicsSource(){
	ModuleIrisGraphics::deleteViewport(ModuleIrisGraphics::gViewport);

	list<IrisViewport*>::iterator it;
	for(it = viewports.begin(); it != viewports.end(); it++){
		(*it)->AutoDispose();
	}

	list<IrisSprite*> sprites = ModuleIrisGraphics::gViewport->GetSprites();
	list<IrisSprite*>::iterator its = sprites.begin();
	for(its = sprites.begin(); its != sprites.end(); its++){
		(*its)->AutoDispose();
	}
}

void ModuleIrisGraphics::Wait(int duration){
	for (int i = 0; i < duration; i++)
		Update();
}

void ModuleIrisGraphics::freeze(){
	isFreeze = true;
	
	// 保存当前BackBuffer
	IDirect3DSurface9* EXSurface;
	IDirect3DSurface9* ExchangeSurface;
	ExchangeTexture->GetSurfaceLevel(0, &EXSurface);
	Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &ExchangeSurface, 0);
	Device->GetRenderTargetData(EXSurface, ExchangeSurface);

	D3DLOCKED_RECT rect;
	memset(&rect, 0, sizeof(rect));
	FreezedTexture->LockRect(0, &rect, NULL, 0);
	PARGBQuad p1 = (PARGBQuad)rect.pBits;
	PARGBQuad c1 = 0;

	D3DLOCKED_RECT rc;
	memset(&rc, 0, sizeof(rc));
	ExchangeSurface->LockRect(&rc, 0, D3DLOCK_NOOVERWRITE);
	PARGBQuad p2 = (PARGBQuad)rc.pBits;
	PARGBQuad c2 = 0;
	
	memcpy(p1, p2, width * height * sizeof(ARGBQuad));

	ExchangeSurface->UnlockRect();
	FreezedTexture->UnlockRect(0);
	EXSurface->Release();
	ExchangeSurface->Release();
}

void ModuleIrisGraphics::transition(int duration, wstring filename, int vague){

	if (!isFreeze){
		freeze();
	}
	Update();

	IDirect3DTexture9* maskTexture = NULL;
	IrisBitmap* mask = NULL;
	IrisShader* shader = IrisShader::Instance();
	if (filename == L"")
		shader->SetTransitionType(0);
	else {
		shader->SetTransitionType(1);
		mask = new IrisBitmap(filename);
		mask->MakeTexture(mask->limitRect);
		maskTexture = mask->GetTexture();
	}

	IDirect3DSurface9* eSurface;
	IDirect3DSurface9* oldSurface;
	
	D3DXMATRIX proj;
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::getWidth(), (float)ModuleIrisGraphics::getHeight(), 0.0f, 0, 9999.0f);
	shader->SetTransitionProjMatrix(proj);

	// gray值越大越先消失
	float cmp = 1.0;
	float step = cmp / duration;
	ModuleIrisGraphics::TransitionTexture->GetSurfaceLevel(0, &eSurface);
	while (cmp >= 0){
		/* 先画到TransitionTexturer上 */
		Device->GetRenderTarget(0, &oldSurface);
		Device->SetRenderTarget(0, eSurface);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();
		shader->DoTransitionShade(maskTexture, cmp);
		Device->EndScene();
		/* 最后画到backbuffer上 */
		Device->SetRenderTarget(0, oldSurface);
		Update();
		cmp -= step;
	}
	if (mask)
		delete mask;
	isFreeze = false;
}

void ModuleIrisGraphics::fadeOut(int duration){
	if(brightness == 0.0f)
		return;
	for (int i = 0; i < duration; i++){
		brightness -= 255.0f / duration;
		if (brightness < 0.0f) brightness = 0.0f;
		Update();
	}
}

void ModuleIrisGraphics::fadeIn(int duration){
	if (brightness == 255.0f)
		return;
	for (int i = 0; i < duration; i++){
		brightness += 255.0f / duration;
		if (brightness > 255.0f) brightness = 255.0f;
		Update();
	}
}

void ModuleIrisGraphics::snap2Bitmap(IrisBitmap *bitmap){
	IDirect3DSurface9* EXSurface;
	IDirect3DSurface9* ExchangeSurface;
	ExchangeTexture->GetSurfaceLevel(0, &EXSurface);	
	Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &ExchangeSurface, 0);
	Device->GetRenderTargetData(EXSurface, ExchangeSurface);

	D3DLOCKED_RECT rc;
	memset(&rc, 0, sizeof(rc));
	ExchangeSurface->LockRect(&rc, 0, D3DLOCK_NOOVERWRITE);
	PARGBQuad p2 = (PARGBQuad)rc.pBits;
	PARGBQuad c2 = 0;
	IrisColor color(0, 0, 0, 0);
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			c2 = p2 + x + y * rc.Pitch / sizeof(ARGBQuad);
			color.set(c2->Red, c2->Green, c2->Blue, c2->Alpha);
			bitmap->SetPixel(x, y, &color);
		}
	}

	ExchangeSurface->UnlockRect();
	EXSurface->Release();
	ExchangeSurface->Release();
}

int ModuleIrisGraphics::getBrightness(){
	return (int)ModuleIrisGraphics::brightness;
}

void ModuleIrisGraphics::setBrightness(int bs){
	float tbrightness = (float)(bs > 255 ? 255 : bs < 0 ? 0 : bs);
	ModuleIrisGraphics::brightness = tbrightness;
}

void ModuleIrisGraphics::frameReset(){
	ModuleIrisGraphics::frameCount = 0;
}

void ModuleIrisGraphics::resizeScreen(int width, int height){
}

int ModuleIrisGraphics::getWidth(){
	return width;
}

int ModuleIrisGraphics::getHeight(){
	return height;
}

ModuleIrisGraphics::~ModuleIrisGraphics(void)
{
}