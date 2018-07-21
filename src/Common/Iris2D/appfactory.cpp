#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/AppGL.h"
#include "OpenGL/Iris2D/GraphicsGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/AppDX.h"
#include "DirectX/Iris2D/GraphicsDX.h"
#endif // _WIN32

#include "Common/Iris2D/App.h"
#include "Common/Iris2D/Graphics.h"

namespace Iris2D {
	Application* AppFactory::sm_pApp = nullptr;
	Graphics* AppFactory::sm_pGraphics= nullptr;
	ApiType AppFactory::sm_eType = ApiType::DirectX;

	Application * AppFactory::GetApplication()  {
		return sm_pApp;
	}

	Graphics * AppFactory::GetGraphics() {
		return sm_pGraphics;
	}

	ApiType AppFactory::GetApiType() {
		return sm_eType;
	}

	void AppFactory::InitApiType(ApiType eType) {
		if (eType == ApiType::OpenGL) {
			sm_pApp = Application::Instance();
			sm_pApp->SetProxied(ApplicationGL::Instance());

			sm_pGraphics = Graphics::Instance();
			sm_pGraphics->SetProxied(GraphicsGL::Instance());
		}
#ifdef _WIN32
		else if (eType == ApiType::DirectX) {
			sm_pApp = Application::Instance();
			sm_pApp->SetProxied(ApplicationDX::Instance());

			sm_pGraphics = Graphics::Instance();
			sm_pGraphics->SetProxied(GraphicsDX::Instance());
		}
#endif // _WIN32

		sm_eType = eType;
	}
}
