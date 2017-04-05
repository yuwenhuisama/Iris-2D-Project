#ifndef _H_IRISAPP_
#define _H_IRISAPP_

#include "IrisCommon.h"

namespace Iris2D
{
	class IrisApplication
	{
	private:
		enum class IrisAppState {
			Uninitialized = 0,
			Initialized,
			Running,
			Quited,
		};

	private:
		IrisAppState m_eAppState = IrisAppState::Uninitialized;

	private:
		IrisApplication() = default;
		~IrisApplication() = default;

	public:
		int WindowMessageLoop();

	public:
		typedef bool(*GameFunc)();

		struct IrisAppStartInfo {
			HINSTANCE m_hInstance = nullptr;
			int nShowCmd = 0;

			unsigned int m_nX = 0;
			unsigned int m_nY = 0;
			unsigned int m_nWidth = 0;
			unsigned int m_nHeight = 0;
			GameFunc m_pfFunc = nullptr;
			std::wstring m_wstrTitle = L"";
		};

	private:
		GameFunc m_pfGameFunc = nullptr;
		HWND m_hWindow = nullptr;
		int m_nShowCmd = 0;

	public:
		static IrisApplication* Instance();

	public:
		bool Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);
		bool Initialize(const IrisAppStartInfo* pInfo);
		bool Run();
		void Release();
		bool IsUninitialized() const;
		bool IsInitiatlize() const;
		bool IsRunning() const;
		bool IsQuited() const;
		void ShutDown();
		void Quite();
		float GetTimeDelta();

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		bool InitializeWindow(const IrisAppStartInfo* pInfo);
	};

}
#endif