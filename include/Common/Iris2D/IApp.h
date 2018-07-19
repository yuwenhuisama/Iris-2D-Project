#ifndef _H_IAPP_
#define _H_IAPP_
#ifdef _WIN32
#include <Windows.h>
#endif
#include <string>

namespace Iris2D {

	class AppStartupInfo;
	typedef bool (*GameFunc)();

	class IApplication {
	public:
	#ifdef _WIN32
		virtual bool Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle) = 0;
	#else
		virtual bool Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle) = 0;
	#endif

		virtual bool Initialize(const AppStartupInfo* pInfo) = 0;

		virtual bool Run() = 0;

		virtual void Release() = 0;

		virtual bool IsUninitialized() const = 0;

		virtual bool IsInitiatlize() const = 0;

		virtual bool IsRunning() const = 0;

		virtual bool IsQuited() const = 0;

		virtual void Quite() = 0;

		virtual float GetTimeDelta() const = 0;
	};
}
#endif // !_H_IAPP_
