#ifndef _H_IRISAPP_
#define _H_IRISAPP_

#include "DirectX/IrisCommon.h"

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
	/**
	* \~english
	* Application Class of Iris 2D.
	*
	* This class provides a singleton instance to maintain the Iris 2D application, including initializing Iris 2D, releasing resouce and so on.
	*/
	/**
	* \~chinese
	* Iris 2D Application�ࡣ
	*
	* ������ṩ��һ������������ά�� Iris 2D Ӧ�ã�������ʼ�� Iris 2D���ͷ���Դ�ȡ�
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
		* \~english
		* Type of call-back function of Iris 2D application.
		*/
		/**
		* \~chinese
		* Iris 2D �ص����������͡�
		*/
		typedef bool(*GameFunc)();

		/**
		* \~english
		* Startup information structure of Iris 2D application.
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		/**
		* \~chinese
		* Iris 2D ������Ϣ�Ľṹ�塣
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		struct IrisAppStartInfo {
		    IrisAppStartInfo() = default;
#ifdef _WIN32
			IrisAppStartInfo(HINSTANCE hInstance, int nShowCmd, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight,
				bool(*pfFunc)(), const std::wstring &wstrTitle);
#else
            IrisAppStartInfo(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight,
                             bool (*pfFunc)(), const std::wstring &wstrTitle);
#endif

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
		};

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
		static IrisApplication* Instance();

	public:

		/**
		* \~english
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
		* @return If application successfully initialized true will be returned otherwise false. If initialization has been failed, Release() should be called to terminate current application.
		* @see Initialize(const IrisAppStartInfo* pInfo)
		* @see GameFunc
		*/
		/**
		* \~chinese
		* ��ʼ��Iris 2D ����Ҫ����Դ�Լ������
		*
		* �ú������������к� Iris 2D ��صĲ���ִ��֮ǰ�����á�
		*
		* �ú������ٱ��Ƽ���������Ϊ�ú���ֻ���������¼����ϵ� Iris 2D API��
		*
		* ���ɵ���Ϸ���ڵ����꽫��Ĭ��Ϊ (0 ,0) ���� Show Command ����Ĭ��Ϊ 0 ��
		* @param hInstance Windows Ӧ�õ� Instance ����������� WinMain �Ĳ�����
		* @param nWidth Iris 2D ���ڳ�ʼ����ȡ�
		* @param nHeight Iris 2D ���ڳ�ʼ���߶ȡ�
		* @param pfGameFunc Iris 2D �ص�����ָ�룬�û���Ϸ����Ӧ�ñ�д�ڴ˺���֮�С�
		* @param wszTitle Iris 2D ���ڵĳ�ʼ�����⡣
		* @return ��� Iris 2D �ɹ���ʼ������ô���� true ���򷵻� false �������ʼ��ʧ�ܣ���ô������� Release() ��������ǰ����
		* @see Initialize(const IrisAppStartInfo* pInfo)
		* @see GameFunc
		*/
#ifdef _WIN32
		bool Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);
#else
        bool Initialize(unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle);
#endif

		/**
		* \~english
		* Initialize resource and components of Iris 2D application required.
		*
		* This function has to be called before all the oparation related to Iris 2D APIs. (Recommanded)
		* @return If application successfully initialized true will be returned otherwise false. If initialization has been failed, Release() should be called to terminate current application.
		* @see Release()
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see IrisAppStartInfo
		*/
		/**
		* \~chinese
		* ��ʼ��Iris 2D ����Ҫ����Դ�Լ������
		*
		* �ú������������к� Iris 2D ��صĲ���ִ��֮ǰ�����á����Ƽ���
		* @return ��� Iris 2D �ɹ���ʼ������ô���� true ���򷵻� false �������ʼ��ʧ�ܣ���ô������� Release() ��������ǰ����
		* @see Release()
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see IrisAppStartInfo
		*/
		bool Initialize(const IrisAppStartInfo* pInfo);

		/**
		* \~english
		* To start Iris 2D game logic, whose code has been written in call-back function in Initialize().
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		/**
		* \~chinese
		* ���� Iris 2D ��Ϸ�߼�����Ϸ�߼�������д�� Initialize() �Ļص������еġ�
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		bool Run();

		/**
		* \~english
		* Release all the resource maintained by Iris 2D such as Sprites/Viewports/Bitmaps and other DirectX-related resource.
		*/
		/**
		* \~chinese
		* �ͷ������� Iris 2D ά������Դ���� Sprite/Viewport/Bitmap �����Լ������� DirectX ��ص���Դ��
		*/
		void Release();

		/**
		* \~english
		* Check if current application state is Uninitialized.
		* @return If Initialize() has not been called or initialization of Iris 2D application has been failed, false will been returned otherwise true.
		*/
		/**
		* \~chinese
		* ��鵱ǰӦ��״̬�Ƿ�Ϊδ��ʼ����
		* @return ��� Initialize() û�б����û��� Iris 2D ��ʼ��ʧ�ܣ���ô���᷵�� false �����򷵻� true ��
		*/
		bool IsUninitialized() const;

		/**
		* \~english
		* Check if current application state is Initialized.
		* @return If initialization of Iris 2D application has been successful and function of Run() has not been called true will be returned otherwise false.
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		/**
		* \~chinese
		* ��鵱ǰӦ��״̬�Ƿ�Ϊ�ѳ�ʼ����
		* @return ��� Iris 2D ��ʼ���ɹ����� Run() û�б����ã���ô���� true ���򷵻� false ��
		* @see Initialize(HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, GameFunc pfGameFunc, const std::wstring& wszTitle)
		* @see Initialize(const IrisAppStartInfo* pInfo)
		*/
		bool IsInitiatlize() const;

		/**
		* \~english
		* Check if current application state is Running.
		* @return If function Run() has been called true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* ��鵱ǰӦ��״̬�Ƿ�Ϊ�������С�
		* @return ��� Run() �����ã���ô���᷵�� true ���򷵻� false��
		*/
		bool IsRunning() const;

		/**
		* \~english
		* Check if current application state is Quited.
		*
		* Quite will happend when the window of Iris 2D application has been closed or the state of IrisApplication singleton instance has been manually set to Quite.
		* @return If window of Iris 2D application has been closed true will be returned otherwise false.
		* @see Quite()
		*/
		/**
		* \~chinese
		* ��鵱ǰӦ��״̬�Ƿ�Ϊ���˳���
		*
		* �� Iris 2D �Ĵ��ڱ��رջ��� IrisApplication ������״̬���ֶ��ı�� Quite ����ô���ᷢ���˳���
		* @return ��� Iris 2D ����Ĵ��ڱ��رգ���ô���� true ���򷵻� false ��
		* @see Quite()
		*/
		bool IsQuited() const;

		/**
		* \~english
		* Set current state of IrisApplication sington instance Quite manually.
		* @see IsQuited()
		*/
		/**
		* \~chinese
		* �ֶ����õ�ǰ IrisApplication ��״̬Ϊ Quite ��
		* @see IsQuited()
		*/
		void Quite();

		/**
		* \~english
		* Get delta time between two frame in Iris 2D.
		*
		* This can be helpful for user to ensure speed of the game.
		* @return Time delta (in milliseconds).
		*/
		/**
		* \~chinese
		* ��ȡ Iris 2D ��֮֡���ʱ������
		*
		* �÷����������û�ȷ����Ϸ�ٶȡ�
		* @return �Ժ���Ϊ��λ��ʱ������
		*/
		float GetTimeDelta();

	private:
#ifdef _WIN32
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

	private:
		bool InitializeWindow(const IrisAppStartInfo* pInfo);
	};

}
#endif