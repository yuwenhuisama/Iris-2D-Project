#include "Iris2D.h"

std::string WStringToString(const std::wstring &wstr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

std::wstring StringToWString(const std::string &str)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), 0, 0);
	if (nSize <= 0) return NULL;
	WCHAR *pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst) return NULL;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pwszDst, nSize);
	pwszDst[nSize] = 0;
	if (pwszDst[0] == 0xFEFF)                    // skip Oxfeff
	for (int i = 0; i < nSize; i++)
		pwszDst[i] = pwszDst[i + 1];
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}

bool d3d::InitD3D(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	//
	// Create the main application window.
	//

	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)d3d::WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"Iris2D";

	if( !RegisterClass(&wc) )
	{
		::MessageBox(0, L"RegisterClass() - FAILED", 0, 0);
		return false;
	}

	HWND hwnd = 0;
	hwnd = ::CreateWindow(L"Iris2D", L"Iris2D",
		WS_EX_TOPMOST | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		200, 50, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

	ModuleIrisGraphics::hwnd = hwnd;

	if( !hwnd )
	{
		::MessageBox(0, L"CreateWindow() - FAILED", 0, 0);
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	//
	// Init D3D:
	//

	HRESULT hr = 0;

	// Step 1: Create the IDirect3D9 object.

	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if( !d3d9 )
	{
		::MessageBox(0, L"Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DDISPLAYMODE d3ddm;
	const HRESULT result = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(result)){
		throw "获得硬件显示模式失败";
		return FALSE;
	}

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.

	D3DPRESENT_PARAMETERS d3dpp;
	//d3dpp.BackBufferWidth            = width;
	//d3dpp.BackBufferHeight           = height;
	//d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	//d3dpp.BackBufferCount            = 1;
	//d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	//d3dpp.MultiSampleQuality         = 0;
	//d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
	//d3dpp.hDeviceWindow              = hwnd;
	//d3dpp.Windowed                   = windowed;
	//d3dpp.EnableAutoDepthStencil     = true;
	//d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	//d3dpp.Flags                      = 0;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;


	// Step 4: Create the device.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    device);            // return created device

	if( FAILED(hr) )
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object

	return true;
}

bool d3d::InitD3DInput(HWND hWnd, HINSTANCE hInstance, IDirectInputDevice8** KeyBoardInputDevice, IDirectInputDevice8** MouseInputDevice) {
	IDirectInput8* tDevice = 0;

	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&tDevice, NULL);
	if (FAILED(hr)){
		::MessageBox(0, L"DirectInput8Create() - FAILED", 0, 0);
		return false;
	}

	hr = tDevice->CreateDevice(GUID_SysKeyboard, KeyBoardInputDevice, NULL);
	if (FAILED(hr)){
		::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
		return false;
	}

	hr = tDevice->CreateDevice(GUID_SysMouse, MouseInputDevice, NULL);
	if (FAILED(hr)){
		::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
		return false;
	}

	(*KeyBoardInputDevice)->SetDataFormat(&c_dfDIKeyboard);
	(*KeyBoardInputDevice)->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//DIPROPDWORD property;
	//property.diph.dwSize = sizeof(DIPROPDWORD);
	//property.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	//property.diph.dwObj = 0;
	//property.diph.dwHow = DIPH_DEVICE;
	//property.dwData = DINPUT_BUFFERSIZE;

	(*MouseInputDevice)->SetDataFormat(&c_dfDIMouse);
	(*MouseInputDevice)->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	//(*MouseInputDevice)->SetProperty(DIPROP_BUFFERSIZE, &property.diph);

	tDevice->Release();

	return true;
}

//int d3d::EnterMsgLoop(bool (*ptr_display)(float timeDelta)){

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_DESTROY:
		::PostQuitMessage(0);
		IrisApp::Instance()->GoQuit();
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 d3d::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.5f;
	light.Phi          = 0.7f;

	return light;
}

D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}
