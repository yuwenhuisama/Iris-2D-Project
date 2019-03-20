#ifndef _H_APP_WARPPER_
#define _H_APP_WARPPER_

#include "Common.h"

#undef LIBRARY_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif
	typedef BOOL(*App_GameFunc)(VOID* pUserData);

#pragma pack(push, 8)  
	struct App_AppStartupInfo {

#ifdef _WIN32
		HINSTANCE m_hInstance;
		/**< \~english Instance handle of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows Ӧ�õ� Instance ����������� WinMain �Ĳ����� */
		int nShowCmd;
#endif
		/**< \~english Show command of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows Ӧ�õ� Show command�������� WinMain �Ĳ����� */
		unsigned int m_nX;
		/**< \~english Initial X Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ�� X ���ꡣ */
		unsigned int m_nY;
		/**< \~english Initial Y Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ�� Y ���ꡣ */
		unsigned int m_nWidth;
		/**< \~english Initial width of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ����ȡ� */
		unsigned int m_nHeight;
		/**< \~english Initial height of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ���߶ȡ� */
		App_GameFunc m_pfFunc;
		/**< \~english Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function */
		/**< \~chinese Iris 2D �ص�����ָ�룬�û���Ϸ����Ӧ�ñ�д�ڴ˺���֮�С� */
		wchar_t* m_wstrTitle;
		/**< \~english Initial title of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڵĳ�ʼ�����⡣ */
	};
#pragma pack(pop)

	EXPORT_API APP_HANDLE App_GetInstance();

#if PLATFORM_WINDOWS
	EXPORT_API ResultCode App_Initialize(APP_HANDLE hHandle, HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, App_GameFunc pfGameFunc, wchar_t* wszTitle);
#else
	EXPORT_API ResultCode App_Initialize(APP_HANDLE hHandle, unsigned int nWidth, unsigned int nHeight, App_GameFunc pfGameFunc, wchar_t* wszTitle);
#endif

	EXPORT_API ResultCode App_Initialize2(APP_HANDLE hHandle, App_AppStartupInfo* pInfo);
	EXPORT_API BOOL App_Run(APP_HANDLE hHandle);
	EXPORT_API void App_Release(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsUninitialized(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsRunning(APP_HANDLE hHandle);
	EXPORT_API BOOL App_IsQuited(APP_HANDLE hHandle);
	EXPORT_API void App_Quite(APP_HANDLE hHandle);
	EXPORT_API float App_GetTimeDelta(APP_HANDLE hHandle);

#ifdef __cplusplus
}
#endif

#endif
