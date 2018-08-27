#include "Common/Iris2D/App.h"

namespace Iris2D {

	Application* Application::Instance() {
		static Application app;
		return &app;
	}

	Application::Application(IApplication* pProxied) : Proxy(pProxied) {}

	Application::Application() : Proxy(nullptr) {}

#ifdef _WIN32
	bool Application::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle, IR_PARAM_RESULT_CT) {
		return m_pProxied->Initialize(hInstance, nWidth, nHeight, pfGameFunc, wszTitle, IR_PARAM);
	}
#else
	bool IApplication::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
		return m_pProxied->Initialize(nWidth, nHeight, pfGameFunc, wszTitle);
	}
#endif // _WIN32

	bool Application::Initialize(const AppStartupInfo* pInfo, IR_PARAM_RESULT_CT) {
		return m_pProxied->Initialize(pInfo, IR_PARAM);
	}

	bool Application::Run() {
		return m_pProxied->Run();
	}

	void Application::Release() {
		m_pProxied->Release();
	}

	bool Application::IsUninitialized() const {
		return m_pProxied->IsUninitialized();
	}

	bool Application::IsInitiatlize() const {
		return m_pProxied->IsInitiatlize();
	}

	bool Application::IsRunning() const {
		return m_pProxied->IsRunning();
	}


	bool Application::IsQuited() const {
		return m_pProxied->IsQuited();
	}

	void Application::Quite() {
		return m_pProxied->Quite();
	}

	float Application::GetTimeDelta() const {
		return m_pProxied->GetTimeDelta();
	}

}
