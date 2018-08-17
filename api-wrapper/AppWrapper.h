#ifndef _H_APP_WARPPER_
#define _H_APP_WARPPER_

#include "Common.h"

#undef LIBRARY_EXPORTS

extern "C" {
	typedef BOOL(*App_GameFunc)();

	struct App_AppStartupInfo {

#ifdef _WIN32
		HINSTANCE m_hInstance;
		/**< \~english Instance handle of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows 应用的 Instance 句柄，来自于 WinMain 的参数。 */
		int nShowCmd;
#endif
		/**< \~english Show command of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows 应用的 Show command，来自于 WinMain 的参数。 */
		unsigned int m_nX;
		/**< \~english Initial X Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化 X 坐标。 */
		unsigned int m_nY;
		/**< \~english Initial Y Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化 Y 坐标。 */
		unsigned int m_nWidth;
		/**< \~english Initial width of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化宽度。 */
		unsigned int m_nHeight;
		/**< \~english Initial height of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化高度。 */
		App_GameFunc m_pfFunc;
		/**< \~english Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function */
		/**< \~chinese Iris 2D 回调函数指针，用户游戏代码应该被写在此函数之中。 */
		wchar_t* m_wstrTitle;
		/**< \~english Initial title of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口的初始化标题。 */
	};


	EXPORT_API APP_HANDLE App_GetInstance();
	EXPORT_API BOOL App_Initialize1(APP_HANDLE hHandle, HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, App_GameFunc pfGameFunc, wchar_t* wszTitle);
	EXPORT_API BOOL App_Initialize2(APP_HANDLE hHandle, App_AppStartupInfo* pInfo);
	EXPORT_API BOOL App_Run(APP_HANDLE hHandle);
	EXPORT_API void App_Release(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsUninitialized(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsRunning(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsQuited(APP_HANDLE hHandle);
	EXPORT_API void App_Quite(APP_HANDLE hHandle);
	EXPORT_API float App_GetTimeDelta(APP_HANDLE hHandle);
}

#endif
