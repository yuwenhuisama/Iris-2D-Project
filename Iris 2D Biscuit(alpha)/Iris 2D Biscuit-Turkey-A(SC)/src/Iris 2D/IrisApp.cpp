#include "IrisApp.h"

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
	this->lastTime = GetTickCount();
}

void IrisApp::Display(){
	this->ptr_display();
}

void IrisApp::GoQuit(){
	this->RuningState = Quit;
}

void IrisApp::Release(){
	IrisShader::Instance()->ReleaseShaderSource();
	delete IrisShader::Instance();
	ModuleIrisGraphics::disposeAllGraphicsSource();
	Device->Release();
	MouseInputDevice->Unacquire();
	MouseInputDevice->Release();
	KeyBoardInputDevice->Unacquire();
	KeyBoardInputDevice->Release();
	ModuleIrisAudio::ReleaseAudio();
	GdiplusShutdown(m_pGdiToken);
}

void IrisApp::Run() {
	this->RuningState = Running;
	this->Display();
	//this->MessageLoop();
}

int IrisApp::MessageLoop(){

	MSG msg;
	IrisShader* shader;
	D3DXMATRIX proj;

	shader = IrisShader::Instance();
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)ModuleIrisGraphics::getWidth(), (float)ModuleIrisGraphics::getHeight(), 0.0f, 0, 9999.0f);

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
			currentTime = GetTickCount();
			if (currentTime > lastTime){
				timeDelta = (float)(currentTime - lastTime);
				ModuleIrisGraphics::frameCount += 1;
				ModuleIrisGraphics::frameRate = 1000.0f / timeDelta;
				lastTime = currentTime + (DWORD)(1000.0f / FPSMax);
				CanDisplay = true;
			}
			ModuleIrisGraphics::UpdateBackBuffer(shader, proj);
		}
	}
	else {
		return WM_QUIT;
	}
	return -1;
}


bool IrisApp::Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title){
	GdiplusStartupInput m_gdiplusStartupInput;
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

	this->ptr_display = pf;

	if (!d3d::InitD3D(hInstance, width, height, true, D3DDEVTYPE_HAL, &Device)){
		::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
		return false;
	}

	if (!d3d::InitD3DInput(ModuleIrisGraphics::hwnd, hInstance, &KeyBoardInputDevice, &MouseInputDevice)){
		::MessageBox(0, L"InitD3DDevice() - FAILED", 0, 0);
		return false;
	}


	if (!ModuleIrisAudio::InitAudio(64)){
		::MessageBox(0, L"InitAudio() - FAILED", 0, 0);
		return false;
	}

	if (!d3d::InitD3DShader(Device)){
		::MessageBox(0, L"InitShader() - FAILED", 0, 0);
		return false;
	}

	if (!Setup(width, height)){
		::MessageBox(0, L"Setup() - FAILED", 0, 0);
		return false;
	}

	::SetWindowTextW(ModuleIrisGraphics::hwnd, title.c_str());

	ModuleIrisGraphics::width = width;
	ModuleIrisGraphics::height = height;

	SetWindowSize();

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
	ModuleIrisGraphics::width = Width;
	ModuleIrisGraphics::height = Height;
	ModuleIrisGraphics::Device = this->Device;
	ModuleIrisInput::KeyBoardInputDevice = this->KeyBoardInputDevice;
	ModuleIrisInput::MouseInputDevice = this->MouseInputDevice;
	ModuleIrisGraphics::Init();

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

IDirect3DDevice9* IrisApp::GetDevice(){
	return this->Device;
}

IrisApp::~IrisApp()
{
}
