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
 * Iris 2D �������ռ�
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
		* ��ȡ IrisApplication �ĵ���ָ�롣
		* @return IrisApplication �ĵ���ָ�롣
		*/
		static ApplicationDX* Instance();

	public:
#ifdef _WIN32
		ResultCode Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle) override;
#else
		ResultCode(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle) override;
#endif
		ResultCode Initialize(const AppStartupInfo* pInfo) override;
		bool Run() override;
		void Release() override;
		bool IsUninitialized() const override;
		bool IsInitiatlize() const override;
		bool IsRunning() const override;
		bool IsQuited() const override;
		void Quite() override;
		float GetTimeDelta() const override;

	private:
#ifdef _WIN32
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

	private:
		bool InitializeWindow(const AppStartupInfo* pInfo);
	};

}
#endif