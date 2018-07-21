#ifndef _H_APP_STARTUP_INFO_
#define _H_APP_STARTUP_INFO_
#include <string>
#include <Windows.h>

namespace Iris2D {

	/**
	* \~english
	* Type of call-back function of Iris 2D application.
	*/
	/**
	* \~chinese
	* Iris 2D 回调函数的类型。
	*/
	typedef bool(*GameFunc)();

	/**
	* \~english
	* Startup information structure of Iris 2D application.
	* @see Initialize(const AppStartupInfo* pInfo)
	*/
	/**
	* \~chinese
	* Iris 2D 启动信息的结构体。
	* @see Initialize(const AppStartupInfo* pInfo)
	*/
	struct AppStartupInfo {
		AppStartupInfo() = default;

	#ifdef _WIN32
		HINSTANCE m_hInstance = nullptr;
		/**< \~english Instance handle of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows 应用的 Instance 句柄，来自于 WinMain 的参数。 */
		int nShowCmd = 0;
	#endif
		/**< \~english Show command of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows 应用的 Show command，来自于 WinMain 的参数。 */
		unsigned int m_nX = 0;
		/**< \~english Initial X Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化 X 坐标。 */
		unsigned int m_nY = 0;
		/**< \~english Initial Y Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化 Y 坐标。 */
		unsigned int m_nWidth = 0;
		/**< \~english Initial width of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化宽度。 */
		unsigned int m_nHeight = 0;
		/**< \~english Initial height of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口初始化高度。 */
		GameFunc m_pfFunc = nullptr;
		/**< \~english Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function */
		/**< \~chinese Iris 2D 回调函数指针，用户游戏代码应该被写在此函数之中。 */
		std::wstring m_wstrTitle = L"";
		/**< \~english Initial title of the window of Iris 2D application. */
		/**< \~chinese Iris 2D 窗口的初始化标题。 */

#ifdef _WIN32
		AppStartupInfo(HINSTANCE hInstance, int nShowCmd, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, bool(*pfFunc)(), const std::wstring & wstrTitle) : m_nX(nX), m_nY(nY),
			m_nWidth(nWidth),
			m_nHeight(nHeight),
			m_pfFunc(pfFunc),
			m_wstrTitle(wstrTitle), m_hInstance(hInstance), nShowCmd(nShowCmd) {}
#else
		AppStartupInfo(unsigned int nX, unsigned int nY, unsigned int nWidth,
			unsigned int nHeight, bool(*pfFunc)(),
			const std::wstring &wstrTitle) : m_nX(nX), m_nY(nY),
			m_nWidth(nWidth),
			m_nHeight(nHeight),
			m_pfFunc(pfFunc),
			m_wstrTitle(wstrTitle) {}
#endif // _WIN32
	};
};
#endif // !_H_APP_STARTUP_INFO
