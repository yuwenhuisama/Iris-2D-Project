#include "OpenGL/Iris2D/AppGL.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "Common/Iris2D/AppStartupInfo.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/Iris2D/GraphicsGL.h"

#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackTransitionShaderGL.h"

#include "Common/Util/DebugUtil.h"

#include "OpenGL/Iris2D/Shaders/BackGroundShaderGL.h";
#include "OpenGL/Iris2D/Shaders/ClearRectShaderGL.h";
#include "OpenGL/Iris2D/Shaders/CopyRectShaderGL.h";
#include "OpenGL/Iris2D/Shaders/FillRectshaderGL.h";
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h";
#include "OpenGL/Iris2D/Shaders/HueChangeShaderGL.h";

namespace Iris2D {
	ApplicationGL * ApplicationGL::Instance() {
		static ApplicationGL application;
		return &application;
	}

#ifdef _WIN32
	ResultCode ApplicationGL::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
#else
	ResultCode ApplicationGL::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
#endif // _WIN32_
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

	ResultCode ApplicationGL::Initialize(const AppStartupInfo * pInfo) {
		auto pHelper = OpenGLHelper::Instance();

#ifdef _DEBUG
		PrintDebugMessageW(L"Iris 2D is currently running under Debug mode.");
#endif

		if (!pHelper->Initialze()) {
			PrintDebugMessageW(L"Error when initializing OpenGL.");
			return IRR_OpenGLInitializeFailed;
		}

		if (!pHelper->InitializeWindow(pInfo->m_nX, pInfo->m_nY, pInfo->m_nWidth, pInfo->m_nHeight, pInfo->m_wstrTitle)) {
			PrintDebugMessageW(L"Error when initializing glfw window.");
			return IRR_WindowInitializeFailed;
		}

		if (!TextureGL::Initialize()) {
			PrintDebugMessageW(L"Error when initializing Texture settings.");
			return IRR_TextureSettingInitializeFailed;
		}

		GraphicsGL::Instance()->SetWidth(pInfo->m_nWidth);
		GraphicsGL::Instance()->SetHeight(pInfo->m_nHeight);

		if (!GraphicsGL::Instance()->Intialize()) {
			PrintDebugMessageW(L"Error when initializing Graphics settings.");
			return IRR_GraphicsInitializeFailed;
		}
		
		if (!ViewportShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing viewport shader.");
			return IRR_ShaderInitializeFailed;
		}
		
		if (!SpriteShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing sprite shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!BackShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing back shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!BackTransitionShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing back transition shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!BackGroundShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing back ground shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!ClearRectShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing clear rect shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!CopyRectShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing copy rect shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!FillRectShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing fill rect shader.");
			return IRR_ShaderInitializeFailed;
		}

		if (!FontShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing font shader.");
			return IRR_ShaderInitializeFailed;
		}	

		if (!HueChangeShaderGL::Instance()->Initialize()) {
			PrintDebugMessageW(L"Error when initializing hue change shader.");
			return IRR_ShaderInitializeFailed;
		}

		m_pfGameFunc = pInfo->m_pfFunc;
#ifdef _WIN32
		m_nShowCmd = pInfo->nShowCmd;
#endif // _WIN32
		return IRR_Success;
	}

	bool ApplicationGL::Run() {
		m_eAppState = AppState::Running;
		OpenGLHelper::Instance()->ShowWindow();

		GraphicsGL::Instance()->m_dLastTime = ::timeGetTime();

		return m_pfGameFunc();
	}

	void ApplicationGL::Release() {
		OpenGLHelper::Instance()->Terminate();
	}

	bool ApplicationGL::IsUninitialized() const {
		return m_eAppState == AppState::Uninitialized;
	}

	bool ApplicationGL::IsInitiatlize() const {
		return m_eAppState == AppState::Initialized;
	}

	bool ApplicationGL::IsRunning() const {
		return m_eAppState == AppState::Running;
	}

	bool ApplicationGL::IsQuited() const {
		return m_eAppState == AppState::Quited || OpenGLHelper::Instance()->ShouldBeClosed();
	}

	void ApplicationGL::Quite() {
		m_eAppState = AppState::Quited;
	}

	float ApplicationGL::GetTimeDelta() const {
		return 0.0f;
	}
}
