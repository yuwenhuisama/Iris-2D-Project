#include "DirectX/Iris2D/AppDX.h"
#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Iris2D/D2DResourceManager.h"
#include "DirectX/Iris2D/ViewportDX.h"
#include "DirectX/Util/TextureDX.h"
#include "DirectX/Iris2D/Shaders/SpriteVertexShader.h"
#include "DirectX/Iris2D/Shaders/SpritePixelShader.h"
#include "DirectX/Iris2D/Shaders/ViewportVertexShader.h"
#include "DirectX/Iris2D/Shaders/ViewportPixelShader.h"
#include "DirectX/Iris2D/GraphicsDX.h"

namespace Iris2D
{
	ApplicationDX* ApplicationDX::Instance()
	{
		static auto pInstance = ApplicationDX();
		return &pInstance;
	}

#ifdef _WIN32
	ResultCode ApplicationDX::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle)
#else
	ResultCode ApplicationDX::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wstrTitle)
#endif
	{
		AppStartupInfo iasiInfo;
#ifdef _WIN32
		iasiInfo.m_hInstance = hInstance;
#endif
		iasiInfo.m_nWidth = nWidth;
		iasiInfo.m_nHeight = nHeight;
		iasiInfo.m_pfFunc = pfGameFunc;
		iasiInfo.m_wstrTitle = wszTitle;

		return Initialize(&iasiInfo);
	}

	ResultCode ApplicationDX::Initialize(const AppStartupInfo * pInfo)
	{
		m_eAppState = AppState::Uninitialized;

		if (!InitializeWindow(pInfo)) {
			return IRR_WindowInitializeFailed;
		}

		if (!D3DResourceManager::Instance()->Initialize(m_hWindow)) {
			return IRR_D3DInitializeFailed;
		}

		if (!D2DResourceManager::Instance()->Initialize()) {
			return IRR_D2DInitializeFailed;
		}

		GraphicsDX::Instance()->SetWidth(pInfo->m_nWidth);
		GraphicsDX::Instance()->SetHeight(pInfo->m_nHeight);

		if (!TextureDX::Initialize()) {
			return IRR_TextureSettingInitializeFailed;
		}


		if (!ViewportDX::InitGlobalViewport(pInfo->m_nWidth, pInfo->m_nHeight)) {
			return IRR_RenderBufferCreateFailed;
		}

		/* Shaders */
		// Sprite Vertex Shader
		auto pSpriteVertexShader = SpriteVertexShader::Instance();
		auto pD3DManager = D3DResourceManager::Instance();
		if (!pSpriteVertexShader->Initialize()) {
			return IRR_ShaderInitializeFailed;
		}

		if (!pSpriteVertexShader->CreateInputLayout()) {
			return IRR_ShaderInitializeFailed;
		}

		// Sprite Pixel Shader
		auto pSpritePixelShader = SpritePixelShader::Instance();
		if (!pSpritePixelShader->Initialize()) {
			return IRR_ShaderInitializeFailed;
		}

		// Viewport Vertex Shader
		auto pViewportVertexShader = ViewportVertexShader::Instance();
		if (!pViewportVertexShader->Initialize()) {
			return IRR_ShaderInitializeFailed;
		}

		if (!pViewportVertexShader->CreateInputLayout()) {
			return IRR_ShaderInitializeFailed;
		}

		// Viewport Pixel Shader
		auto pViewportPixelShader = ViewportPixelShader::Instance();
		if (!pViewportPixelShader->Initialize()) {
			return IRR_ShaderInitializeFailed;
		}

		m_pfGameFunc = pInfo->m_pfFunc;
		m_nShowCmd = pInfo->nShowCmd;

		m_eAppState = AppState::Initialized;

		return IRR_Success;
	}

	bool ApplicationDX::Run()
	{
		m_eAppState = AppState::Running;
		ShowWindow(m_hWindow, m_nShowCmd);

		// GraphicsDX::Instance()->m_fLastTime = static_cast<float>(glfwGetTime());
		GraphicsDX::Instance()->m_fLastTime = static_cast<float>(::timeGetTime());
//		GraphicsDX::Instance()->m_fLag = 0.0f;
		return m_pfGameFunc();
	}

	void ApplicationDX::Release()
	{
		D3DResourceManager::Instance()->Release();
		D2DResourceManager::Instance()->Release();
		TextureDX::Release();
		ViewportDX::ReleaseGlobalViewport();
		GraphicsDX::Instance()->Release();
		SpritePixelShader::Instance()->Release();
		SpriteVertexShader::Instance()->Release();
	}

	bool ApplicationDX::IsUninitialized() const
	{
		return m_eAppState == AppState::Uninitialized;
	}

	bool ApplicationDX::IsInitiatlize() const
	{
		return m_eAppState == AppState::Initialized;
	}

	bool ApplicationDX::IsRunning() const
	{
		return m_eAppState == AppState::Running;
	}

	bool ApplicationDX::IsQuited() const
	{
		return m_eAppState == AppState::Quited;
	}

	void ApplicationDX::Quite()
	{
		m_eAppState = AppState::Quited;
	}

	float ApplicationDX::GetTimeDelta() const
	{
		return 0.0f;
	}

	LRESULT ApplicationDX::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			ApplicationDX::Instance()->Quite();
			break;
		default:
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	bool ApplicationDX::InitializeWindow(const AppStartupInfo* pInfo)
	{
		WNDCLASSEX wndClass = { 0 };
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = pInfo->m_hInstance;
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = "IrisAppWindow";

		if (!RegisterClassEx(&wndClass)) {
			return false;
		}

		RECT rcArea = { 0, 0, pInfo->m_nWidth, pInfo->m_nHeight };
		AdjustWindowRect(&rcArea, WS_OVERLAPPEDWINDOW, false);

		const HWND hHwnd = CreateWindowW(L"IrisAppWindow",
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
}