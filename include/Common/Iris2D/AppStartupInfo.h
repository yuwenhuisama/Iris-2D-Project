#ifndef _H_APP_STARTUP_INFO_
#define _H_APP_STARTUP_INFO_
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <functional>

namespace Iris2D {

	/**
	* \~english
	* Type of call-back function of Iris 2D application.
	*/
	/**
	* \~chinese
	* Iris 2D �ص����������͡�
	*/
	//typedef bool(*GameFunc)();
	typedef std::function<bool(void)> GameFunc;

	/**
	* \~english
	* Startup information structure of Iris 2D application.
	* @see Initialize(const AppStartupInfo* pInfo)
	*/
	/**
	* \~chinese
	* Iris 2D ������Ϣ�Ľṹ�塣
	* @see Initialize(const AppStartupInfo* pInfo)
	*/
	struct AppStartupInfo {
		AppStartupInfo() = default;

	#ifdef _WIN32
		HINSTANCE m_hInstance = nullptr;
		/**< \~english Instance handle of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows Ӧ�õ� Instance ����������� WinMain �Ĳ����� */
		int nShowCmd = 0;
	#endif
		/**< \~english Show command of Windows application taken from WinMain as a parameter. */
		/**< \~chinese Windows Ӧ�õ� Show command�������� WinMain �Ĳ����� */
		unsigned int m_nX = 0;
		/**< \~english Initial X Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ�� X ���ꡣ */
		unsigned int m_nY = 0;
		/**< \~english Initial Y Position of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ�� Y ���ꡣ */
		unsigned int m_nWidth = 0;
		/**< \~english Initial width of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ����ȡ� */
		unsigned int m_nHeight = 0;
		/**< \~english Initial height of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڳ�ʼ���߶ȡ� */
		GameFunc m_pfFunc = nullptr;
		/**< \~english Initial call-back function pointer of Iris 2D application, user's code of game should be written in this function */
		/**< \~chinese Iris 2D �ص�����ָ�룬�û���Ϸ����Ӧ�ñ�д�ڴ˺���֮�С� */
		std::wstring m_wstrTitle = L"";
		/**< \~english Initial title of the window of Iris 2D application. */
		/**< \~chinese Iris 2D ���ڵĳ�ʼ�����⡣ */

#ifdef _WIN32
		AppStartupInfo(HINSTANCE hInstance, int nShowCmd, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, GameFunc pfFunc, const std::wstring& wstrTitle) : m_hInstance(hInstance), nShowCmd(nShowCmd),
			m_nX(nX),
			m_nY(nY),
			m_nWidth(nWidth),
			m_nHeight(nHeight), m_pfFunc(pfFunc), m_wstrTitle(wstrTitle) {}
#else
		AppStartupInfo(unsigned int nX, unsigned int nY, unsigned int nWidth,
			unsigned int nHeight, const GameFunc& pfFunc,
			const std::wstring &wstrTitle) : m_nX(nX), m_nY(nY),
			m_nWidth(nWidth),
			m_nHeight(nHeight),
			m_pfFunc(pfFunc),
			m_wstrTitle(wstrTitle) {}
#endif // _WIN32
	};
};
#endif // !_H_APP_STARTUP_INFO
