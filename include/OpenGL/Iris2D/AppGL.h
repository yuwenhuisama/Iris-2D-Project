#ifndef _H_APP_GL_
#define _H_APP_GL_

#include "Common/Iris2D/IApp.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D {
	class Application;
	class ApplicationGL : public Proxied<Application>, public IApplication {
	public:
		static ApplicationGL * Instance();

	private:
		enum class AppState {
			Uninitialized = 0,
			Initialized,
			Running,
			Quited,
		};

	private:
#ifdef _WIN32
		int m_nShowCmd = 0;
#endif // _WIN32

		AppState m_eAppState = AppState::Uninitialized;
		GameFunc m_pfGameFunc = nullptr;

	public:
		// Í¨¹ý IApplication ¼Ì³Ð
#ifdef _WIN32
		ResultCode Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) override;
#else
		ResultCode Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring & wszTitle) override;
#endif // _WIN32
		ResultCode Initialize(const AppStartupInfo * pInfo) override;
		bool Run() override;
		void Release() override;
		bool IsUninitialized() const override;
		bool IsInitiatlize() const override;
		bool IsRunning() const override;
		bool IsQuited() const override;
		void Quite() override;
		float GetTimeDelta() const override;

	private:
		ApplicationGL() = default;
		~ApplicationGL() = default;
	};
}

#endif // !_H_APP_GL_
