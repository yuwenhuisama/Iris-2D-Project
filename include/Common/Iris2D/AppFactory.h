#ifndef _H_APP_FACTORY_
#define _H_APP_FACTORY_

#include "AppStartupInfo.h"

namespace Iris2D {
	enum class ApiType {
		OpenGL = 0,
		DirectX,
	};

	class Application;
	class Graphics;

	class AppFactory {
	private:
		static Application* sm_pApp;
		static Graphics* sm_pGraphics;

		static ApiType sm_eType;

	public:
		static void InitApiType(ApiType eType);
		static Application* GetApplication();
		static Graphics* GetGraphics();

		static ApiType GetApiType();
	};
}

#endif // !_H_APP_FACTORY_
