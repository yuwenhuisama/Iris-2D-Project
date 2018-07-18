#include "Common/Iris2D/AppFactory.h"
#include "DirectX/Iris2D/AppDX.h"

namespace Iris2D {
	IApp* AppFactory::sm_pApp = nullptr;

	IApp * AppFactory::GetApplication()  {
		return sm_pApp;
	}

	void AppFactory::InitApiType(ApiType eType) {
		if (eType == ApiType::OpenGL) {

		}
#ifdef _WIN32
		else if (eType == ApiType::DirectX) {
			sm_pApp = ApplicationDX::Instance();
		}
#endif // _WIN32
	}
}
