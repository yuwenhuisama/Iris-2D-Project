#ifndef _H_IRISAPP_
#define _H_IRISAPP_

#include "IrisCommon.h"

/**
 *  Namespace of Iris 2D
 */
namespace Iris2D
{
	/**
	 * Application Class of Iris2D
	 *
	 * This class provides a singleton instance to maintain the Iris 2D application, including initializing Iris 2D, releasing resouce and so on.
	 */
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

		/**
		 * Type of call-back function of Iris 2D application.
		 */
		typedef bool(*GameFunc)();

		/**
		 * Startup information structure of Iris 2D application.
		 * @see Initialize(const IrisAppStartInfo* pInfo)
		 */
		struct IrisAppStartInfo {
			HINSTANCE m_hInstance = nullptr; /**< Instance handle of Windows application taken from WinMain as a parameter. */
			int nShowCmd = 0; /**< Show command of Windows application taken from WinMain as a parameter. */

			unsigned int m_nX = 0; /**< Initial X Position of the window of Iris 2D application. */
			unsigned int m_nY = 0; /**< Initial Y Position of the window of Iris 2D application. */
			unsigned int m_nWidth = 0; /**< Initial width of the window of Iris 2D application. */
			unsigned int m_nHeight = 0; /**< Initial height of the window of Iris 2D application. */
			GameFunc m_pfFunc = nullptr; /**< Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function */
			std::wstring m_wstrTitle = L""; /**< Initial title of the window of Iris 2D application. */
		};

	private:
		GameFunc m_pfGameFunc = nullptr;
		HWND m_hWindow = nullptr;
		int m_nShowCmd = 0;

	public:
		/**
		 * Get the singleton instance of IrisApplication.
		 */
		static IrisApplication* Instance();

	public:
		/**
		 * Initialize resource and components of Iris 2D application required.
		 *
		 * This function has to be called before all the oparation related to Iris 2D APIs.
		 *
		 * This function is NO recommended because it is just be provided for being downward compatible with old Iris 2D API.
		 *
		 * Position of created window will defaultly be (0, 0) and Show Command will defautly be 0.
		 * @param hInstance Instance handle of Windows application taken from WinMain as a parameter.
		 * @param nWidth Initial width of the window of Iris 2D application.
		 * @param nHeight Initial height of the window of Iris 2D application.
		 * @param pfGameFunc Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function.
		 * @param wszTitle Initial title of the window of Iris 2D application.
		 * @see Initialize(const IrisAppStartInfo* pInfo)
		 * @see GameFunc
		 */
		bool Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);

		/**
		 * Initialize resource and components of Iris 2D application required.
		 *
		 * This function has to be called before all the oparation related to Iris 2D APIs. (Recommanded)
		 * @return If application successfully initialized true will be returned otherwise false. If initialization has been failed, Release() should be called to terminate current application.
		 * @see Release()
		 * @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		 * @see IrisAppStartInfo
		 */
		bool Initialize(const IrisAppStartInfo* pInfo);

		/**
		 * To start Iris 2D game logic, whose code has been written in call-back function in Initialize();
		 * @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		 * @see Initialize(const IrisAppStartInfo* pInfo)
		 */
		bool Run();

		/**
		 * Release all the resource maintained by Iris 2D such as Sprites/Viewports/Bitmaps and other DirectX-related resource.
		 */
		void Release();

		/**
		 * Check if current application state is Uninitialized.
		 * @return If Initialize() has not been called or initialization of Iris 2D application has been failed, false will been returned otherwise true.
		 */
		bool IsUninitialized() const;

		/**
		* Check if current application state is Initialized.
		* @return If initialization of Iris 2D application has been successful and function of Run() has not been called true will be returned otherwise false.
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see Initialize(const IrisAppStartInfo* pInfo) 
		*/
		bool IsInitiatlize() const;

		/**
		* Check if current application state is Running.
		* @return If function Run() has been called true will be returned otherwise false.
		*/
		bool IsRunning() const;

		/**
		 * Check if current application state is Quited.
		 *
		 * Quite will happend when the window of Iris 2D application has been closed or the state of IrisApplication singleton instance has been manually set to Quite.
		 * @return If window of Iris 2D application has been closed true will be returned otherwise false.
		 * @see Quite()
		 */
		bool IsQuited() const;

		/**
		 * Set current state of IrisApplication sington instance Quite manually.
		 * @see IsQuited()
		 */
		void Quite();

		/**
		 * Get delta time between two frame in Iris 2D.
		 *
		 * This can be helpful for use to ensure speed of the game.
		 * @return Time delta (in milliseconds).
		 */
		float GetTimeDelta();

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		bool InitializeWindow(const IrisAppStartInfo* pInfo);
	};

}
#endif