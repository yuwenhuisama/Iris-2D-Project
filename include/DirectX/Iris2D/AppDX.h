#ifndef _H_APP_DX_
#define _H_APP_DX_

#include "Common/Iris2D/IApp.h"
#include "Common/Iris2D/AppStartupInfo.h"
#include "DirectX/Common.h"

/**
 * \~english
 * Namespace of Iris 2D
 */
/**
 * \~chinese
 * Iris 2D 的命名空间
 */
namespace Iris2D
{
	class ApplicationDX : public IApplication
	{
	private:
		enum class AppState {
			Uninitialized = 0,
			Initialized,
			Running,
			Quited,
		};

	private:
		AppState m_eAppState = AppState::Uninitialized;

	private:
		ApplicationDX() = default;
		~ApplicationDX() = default;

	private:
		GameFunc m_pfGameFunc = nullptr;
#ifdef _WIN32
		HWND m_hWindow = nullptr;
		int m_nShowCmd = 0;
#endif
	public:

		/**
		* \~english
		* Get the singleton instance pointer of IrisApplication.
		* @return The singleton instance pointer of IrisApplication.
		*/
		/**
		* \~chinese
		* 获取 IrisApplication 的单例指针。
		* @return IrisApplication 的单例指针。
		*/
		static ApplicationDX* Instance();

	public:
#ifdef _WIN32
		virtual bool Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);
#else
		virtual bool Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);
#endif
		virtual bool Initialize(const AppStartupInfo* pInfo);
		virtual bool Run();
		virtual void Release();
		virtual bool IsUninitialized() const;
		virtual bool IsInitiatlize() const;
		virtual bool IsRunning() const;
		virtual bool IsQuited() const;
		virtual void Quite();
		virtual float GetTimeDelta() const;

	private:
#ifdef _WIN32
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

	private:
		bool InitializeWindow(const AppStartupInfo* pInfo);
	};

}
#endif