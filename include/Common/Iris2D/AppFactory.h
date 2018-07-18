#ifndef _H_APP_FACTORY_
#define _H_APP_FACTORY_

#include "IApp.h"
#include "AppStartupInfo.h"

namespace Iris2D {
	enum class ApiType {
		OpenGL,
		DirectX,
	};

	class AppFactory {
	private:
		static IApp* sm_pApp;

	public:
		static void InitApiType(ApiType eType);
		static IApp* GetApplication();
	};
}

#endif // !_H_APP_FACTORY_
