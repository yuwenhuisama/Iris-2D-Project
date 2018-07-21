#include "OpenGL/Iris2D/AppGL.h"
#include "OpenGL/Iris2D/OpenGLHelper.h"
#include "Common/Iris2D/AppStartupInfo.h"

namespace Iris2D {
	ApplicationGL * ApplicationGL::Instance() {
		static ApplicationGL application;
		return &application;
	}

#ifdef _WIN32
	bool ApplicationGL::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
#else
	bool ApplicationGL::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
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

	bool ApplicationGL::Initialize(const AppStartupInfo * pInfo) {
		auto pHelper = OpenGLHelper::Instance();

		if (!pHelper->Initialze()) {
			return false;
		}

		if (!pHelper->InitializeWindow(pInfo->m_nX, pInfo->m_nY, pInfo->m_nWidth, pInfo->m_nHeight, pInfo->m_wstrTitle)) {
			return false;
		}

		m_pfGameFunc = pInfo->m_pfFunc;
#ifdef _WIN32
		m_nShowCmd = pInfo->nShowCmd;
#endif // _WIN32
		return true;
	}

	bool ApplicationGL::Run() {
		m_eAppState = AppState::Running;
		OpenGLHelper::Instance()->ShowWindow();

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
