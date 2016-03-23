#include "Iris 2D/IrisApp.h"
#include "Iris 2D/IrisD3DNamespace.h"
#include "Iris 2D/ModuleIrisGraphics.h"
#include "Iris 2D/ModuleIrisAudio.h"
#include "Iris 2D/ModuleIrisInput.h"
#include "Iris 2D/IrisShader.h"
#include "Iris 2D/IrisBitmap.h"

namespace Iris2D{
	IrisApp* IrisApp::instance = NULL;

	IrisApp* IrisApp::Instance(){
		if (instance == NULL){
			instance = new IrisApp;
		}
		return instance;
	}

	IrisApp::IrisApp()
	{
		CanDisplay = true;
		this->lastTime = ::timeGetTime();
	}

	void IrisApp::ToggleWindowMode(){
		curD3DParameters.Windowed = !curD3DParameters.Windowed;
		if (!curD3DParameters.Windowed)
			::GetWindowRect(ModuleIrisGraphics::GetHwnd(), &windowRect);
		if (curD3DParameters.Windowed){
			curD3DParameters.FullScreen_RefreshRateInHz = 0;
		}
		else{
			curD3DParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}

		OnDeviceLost();
		HRESULT r = Device->Reset(&curD3DParameters);
		if (FAILED(r))
			::MessageBox(0, L"Error When Toggling Window Mode.", L"Error", 0);
		OnDeviceRecover();
	}
	
	void IrisApp::OnDeviceLost(){
		IrisShader::Instance()->ReleaseShaderSource();
		ModuleIrisGraphics::OnDeviceLost();
	}

	void IrisApp::OnDeviceRecover(){

		//-------------Projection Matrix Setting-------------
		D3DXMATRIX proj;
		D3DXMatrixOrthoOffCenterLH(&proj, 0, (float)800, (float)600, 0, 0.0f, 9999.0f);
		Device->SetTransform(D3DTS_PROJECTION, &proj);

		//-------------State Setting-------------
		Device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE); //¿¹¾â³Ý

		Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		/* persist to change*/
		Device->SetRenderState(D3DRS_LIGHTING, true);

		D3DXVECTOR3 dir(0.0f, 0.0f, 1.0f);
		D3DXCOLOR c = d3d::WHITE;
		D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

		Device->SetLight(0, &dirLight);
		Device->LightEnable(0, true);

		//Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		//Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		Device->SetRenderState(D3DRS_ALPHAREF, 0x00000000);
		Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		Device->SetRenderState(D3DRS_SPECULARENABLE, true);

		// use alpha channel in texture for alpha
		Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// set blending factors so that alpha component determines transparency
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// alpha enable
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		IrisShader::Instance()->InitShader(Device,
			L"hlsl\\SpriteShader.hlsl",
			L"hlsl\\ViewportShader.hlsl",
			L"hlsl\\BackbufferShader.hlsl",
			L"hlsl\\TransitionEffectShader.hlsl");
		if (curD3DParameters.Windowed){
			::SetWindowPos(
				ModuleIrisGraphics::GetHwnd(),
				HWND_NOTOPMOST,
				windowRect.left,
				windowRect.top,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top,
				SWP_DRAWFRAME | SWP_SHOWWINDOW);
		}
		ModuleIrisGraphics::OnDeviceRecover();
		IrisBitmap::OnRecover();
	}

	void IrisApp::Display(IR_PARAM_RESULT_CT){
		if(this->ptr_display())
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error while Game Runing!")
	}

	void IrisApp::Release(IR_PARAM_RESULT_CT){
		bool flag = true;
		if (!IrisShader::Instance()->ReleaseShaderSource()) flag = false;
		delete IrisShader::Instance();
		ModuleIrisGraphics::DisposeAllGraphicsSource();
		if (FAILED(Device->Release())) flag = false;
		if (FAILED(MouseInputDevice->Unacquire())) flag = false;
		if (FAILED(MouseInputDevice->Release())) flag = false;
		if (FAILED(KeyBoardInputDevice->Unacquire())) flag = false;
		if (FAILED(KeyBoardInputDevice->Release())) flag = false;
		if(!ModuleIrisAudio::ReleaseAudio()) flag = false;
		GdiplusShutdown(m_pGdiToken);
		if (flag)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Resource!")
	}

	void IrisApp::Run(IR_PARAM_RESULT_CT) {
		this->RuningState = Running;
		this->Display();
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		//this->MessageLoop();
	}

	int IrisApp::MessageLoop(){

		MSG msg;
		IrisShader* shader;
		D3DXMATRIX proj;

		shader = IrisShader::Instance();
		D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::GetWidth(), (float)ModuleIrisGraphics::GetHeight(), 0.0f, 0, 9999.0f);

		::ZeroMemory(&msg, sizeof(MSG));

		if (msg.message != WM_QUIT)
		{
			if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				currentTime = ::timeGetTime();
				if (currentTime > lastTime){
					timeDelta = (float)(currentTime - lastTime);
					ModuleIrisGraphics::frameCount += 1;
					ModuleIrisGraphics::frameRate = 1000.0f / timeDelta;
					lastTime = currentTime + (DWORD)(1000.0f / 60.0f);
					CanDisplay = true;
				}
				if (!ModuleIrisGraphics::isFreeze)
					ModuleIrisGraphics::UpdateBackBuffer(shader, proj);
			}
		}
		else {
			return WM_QUIT;
		}
		return -1;
	}


	bool IrisApp::Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title, IR_PARAM_RESULT_CT){
		GdiplusStartupInput m_gdiplusStartupInput;
		GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

		this->ptr_display = pf;

		if (!d3d::InitD3D(hInstance, width, height, true, D3DDEVTYPE_HAL, &Device)){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in InitD3D!")
			::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
			return false;
		}

		if (!d3d::InitD3DInput(ModuleIrisGraphics::GetHwnd(), hInstance, &KeyBoardInputDevice, &MouseInputDevice)){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in InitD3D Input!")
			::MessageBox(0, L"InitD3DInput() - FAILED", 0, 0);
			return false;
		}
		
		if (!ModuleIrisAudio::InitAudio(64)){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Init Audio!")
			::MessageBox(0, L"InitAudio() - FAILED", 0, 0);
			return false;
		}

		if (!d3d::InitD3DShader(Device)){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Init Shader!")
			::MessageBox(0, L"InitShader() - FAILED", 0, 0);
			return false;
		}

		if (!Setup(width, height)){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Setup!")
			::MessageBox(0, L"Setup() - FAILED", 0, 0);
			return false;
		}

		::SetWindowTextW(ModuleIrisGraphics::GetHwnd(), title.c_str());

		ModuleIrisGraphics::SetWidth(width);
		ModuleIrisGraphics::SetHeight(height);

		SetWindowSize();

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")

		return true;
	}

	void IrisApp::SetWindowSize()
	{
		RECT WindowRect;
		RECT ClientRect;
		GetWindowRect(ModuleIrisGraphics::hwnd, &WindowRect);
		GetClientRect(ModuleIrisGraphics::hwnd, &ClientRect);
		WindowRect.right += (ModuleIrisGraphics::width - ClientRect.right);
		WindowRect.bottom += (ModuleIrisGraphics::height - ClientRect.bottom);
		MoveWindow(ModuleIrisGraphics::hwnd, WindowRect.left, WindowRect.top, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, true);
	}

	bool IrisApp::Setup(int Width, int Height){

		// Initialization function calling
		ModuleIrisGraphics::SetWidth(Width);
		ModuleIrisGraphics::SetHeight(Height);
		ModuleIrisGraphics::SetDevice(this->Device);
		ModuleIrisInput::KeyBoardInputDevice = this->KeyBoardInputDevice;
		ModuleIrisInput::MouseInputDevice = this->MouseInputDevice;
		if (!ModuleIrisGraphics::Init())
			return false;

		//-------------Projection Matrix Setting-------------
		D3DXMATRIX proj;
		D3DXMatrixOrthoOffCenterLH(&proj, 0, (float)Width, (float)Height, 0, 0.0f, 9999.0f);
		Device->SetTransform(D3DTS_PROJECTION, &proj);

		//-------------State Setting-------------
		Device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE); //¿¹¾â³Ý

		Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		/* persist to change*/
		Device->SetRenderState(D3DRS_LIGHTING, true);

		D3DXVECTOR3 dir(0.0f, 0.0f, 1.0f);
		D3DXCOLOR c = d3d::WHITE;
		D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

		Device->SetLight(0, &dirLight);
		Device->LightEnable(0, true);

		//Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		//Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		Device->SetRenderState(D3DRS_ALPHAREF, 0x00000000);
		Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		Device->SetRenderState(D3DRS_SPECULARENABLE, true);

		// use alpha channel in texture for alpha
		Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// set blending factors so that alpha component determines transparency
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// alpha enable
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		return true;
	}

	IrisApp::~IrisApp()
	{
	}
}