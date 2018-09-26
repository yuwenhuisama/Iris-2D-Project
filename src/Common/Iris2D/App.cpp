#include "Common/Iris2D/App.h"
#include <ctime>

namespace Iris2D {

	Application* Application::Instance() {
		static Application app;
		return &app;
	}

	Application::Application(IApplication* pProxied) : Proxy(pProxied) {}

	Application::Application() : Proxy(nullptr) {}

#ifdef _WIN32
	ResultCode Application::Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
		return m_pProxied->Initialize(hInstance, nWidth, nHeight, pfGameFunc, wszTitle);
	}
#else
	ResultCode IApplication::Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) {
		return m_pProxied->Initialize(nWidth, nHeight, pfGameFunc, wszTitle);
	}
#endif // _WIN32

	ResultCode Application::Initialize(const AppStartupInfo* pInfo) {
		srand(static_cast<unsigned>(time(nullptr)));
		return m_pProxied->Initialize(pInfo);
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
