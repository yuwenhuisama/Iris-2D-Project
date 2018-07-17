#include "DirectX/Iris2D/IrisApp.h"
#include "DirectX/Iris2D/IrisD3DResourceManager.h"
#include "DirectX/Iris2D/IrisD2DResourceManager.h"
#include "DirectX/Iris2D/IrisViewport.h"
#include "DirectX/Iris2DUtil/IrisTexture.h"
#include "DirectX/Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisSpritePixelShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisViewportVertexShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisViewportPixelShader.h"
#include "DirectX/Iris2D/IrisGraphics.h"


namespace Iris2D
{
	IrisApplication* IrisApplication::Instance()
	{
		static auto pInstance = IrisApplication();
		return &pInstance;
	}

#ifdef _WIN32
	bool IrisApplication::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wstrTitle)
#else
	bool IrisApplication::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wstrTitle)
#endif
	{
		IrisAppStartInfo iasiInfo;
#if IR_API_VERSION == 1
		iasiInfo.m_hInstance = hInstance;
#endif
		iasiInfo.m_nWidth = nWidth;
		iasiInfo.m_nHeight = nHeight;
		iasiInfo.m_pfFunc = pfGameFunc;
		iasiInfo.m_wstrTitle = wstrTitle;

		return Initialize(&iasiInfo);
	}

	bool IrisApplication::Initialize(const IrisAppStartInfo * pInfo)
	{
		m_eAppState = IrisAppState::Uninitialized;

		if (!InitializeWindow(pInfo)) {
			return false;
		}

		if (!IrisD3DResourceManager::Instance()->Initialize(m_hWindow)) {
			return false;
		}

		if (!IrisD2DResourceManager::Instance()->Initialize()) {
			return false;
		}

		IrisGraphics::Instance()->SetWidth(pInfo->m_nWidth);
		IrisGraphics::Instance()->SetHeight(pInfo->m_nHeight);

		if (!IrisTexture::Initialize()) {
			return false;
		}


		if (!IrisViewport::InitGlobalViewport(pInfo->m_nWidth, pInfo->m_nHeight)) {
			return false;
		}

		/* Shaders */
		// Sprite Vertex Shader
		auto pSpriteVertexShader = IrisSpriteVertexShader::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();
		if (!pSpriteVertexShader->Initialize()) {
			return false;
		}

		if (!pSpriteVertexShader->CreateInputLayout()) {
			return false;
		}

		// Sprite Pixel Shader
		auto pSpritePixelShader = IrisSpritePixelShader::Instance();
		if (!pSpritePixelShader->Initialize()) {
			return false;
		}

		// Viewport Vertex Shader
		auto pViewportVertexShader = IrisViewportVertexShader::Instance();
		if (!pViewportVertexShader->Initialize()) {
			return false;
		}

		if (!pViewportVertexShader->CreateInputLayout()) {
			return false;
		}

		// Viewport Pixel Shader
		auto pViewportPixelShader = IrisViewportPixelShader::Instance();
		if (!pViewportPixelShader->Initialize()) {
			return false;
		}

		m_pfGameFunc = pInfo->m_pfFunc;
		m_nShowCmd = pInfo->nShowCmd;

		m_eAppState = IrisAppState::Initialized;

		return true;
	}

	bool IrisApplication::Run()
	{
		m_eAppState = IrisAppState::Running;
		ShowWindow(m_hWindow, m_nShowCmd);

		// IrisGraphics::Instance()->m_fLastTime = static_cast<float>(glfwGetTime());
		IrisGraphics::Instance()->m_fLastTime = static_cast<float>(::timeGetTime());
//		IrisGraphics::Instance()->m_fLag = 0.0f;
		return m_pfGameFunc();
	}

	void IrisApplication::Release()
	{
		IrisD3DResourceManager::Instance()->Release();
		IrisD2DResourceManager::Instance()->Release();
		//IrisTexture::Release();
		//IrisViewport::ReleaseGlobalViewport();
		//IrisGraphics::Instance()->Release();
		//IrisSpritePixelShader::Instance()->Release();
		//IrisSpriteVertexShader::Instance()->Release();
	}

	bool IrisApplication::IsUninitialized() const
	{
		return m_eAppState == IrisAppState::Uninitialized;
	}

	bool IrisApplication::IsInitiatlize() const
	{
		return m_eAppState == IrisAppState::Initialized;
	}

	bool IrisApplication::IsRunning() const
	{
		return m_eAppState == IrisAppState::Running;
	}

	bool IrisApplication::IsQuited() const
	{
		return m_eAppState == IrisAppState::Quited;
	}

	void IrisApplication::Quite()
	{
		m_eAppState = IrisAppState::Quited;
	}

	float IrisApplication::GetTimeDelta()
	{
		return 0.0f;
	}

	LRESULT IrisApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			IrisApplication::Instance()->Quite();
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	bool IrisApplication::InitializeWindow(const IrisAppStartInfo* pInfo)
	{
		WNDCLASSEX wndClass = { 0 };
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = pInfo->m_hInstance;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = "IrisAppWindow";

		if (!RegisterClassEx(&wndClass)) {
			return false;
		}

		RECT rcArea = { 0, 0, pInfo->m_nWidth, pInfo->m_nHeight };
		AdjustWindowRect(&rcArea, WS_OVERLAPPEDWINDOW, false);

		HWND hHwnd = CreateWindowW(L"IrisAppWindow",
			pInfo->m_wstrTitle.c_str(),
			WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
			pInfo->m_nX,
			pInfo->m_nY,
			rcArea.right - rcArea.left,
			rcArea.bottom - rcArea.top,
			nullptr,
			nullptr,
			pInfo->m_hInstance,
			nullptr);

		if (!hHwnd) {
			return false;
		}

		m_hWindow = hHwnd;

		return true;
	}

#ifdef _WIN32
	IrisApplication::IrisAppStartInfo::IrisAppStartInfo(HINSTANCE hInstance, int nShowCmd, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, bool(*pfFunc)(), const std::wstring & wstrTitle) : m_nX(nX), m_nY(nY),
		m_nWidth(nWidth),
		m_nHeight(nHeight),
		m_pfFunc(pfFunc),
		m_wstrTitle(wstrTitle), m_hInstance(hInstance), nShowCmd(nShowCmd) {}
#else
	IrisApplication::IrisAppStartInfo::IrisAppStartInfo(unsigned int nX, unsigned int nY, unsigned int nWidth,
		unsigned int nHeight, bool(*pfFunc)(),
		const std::wstring &wstrTitle) : m_nX(nX), m_nY(nY),
		m_nWidth(nWidth),
		m_nHeight(nHeight),
		m_pfFunc(pfFunc),
		m_wstrTitle(wstrTitle) {}
#endif // _WIN32
}