#define LIBRARY_EXPORTS
#include "AppFactoryWrapper.h"

EXPORT_API void App_InitApiType(App_ApiType eApiType) {
	switch(eApiType) {
	case OPENGL:
		Iris2D::AppFactory::InitApiType(Iris2D::ApiType::OpenGL);
		break;
#ifdef __WIN32
	case DIRECTX:
		Iris2D::AppFactory::InitApiType(Iris2D::ApiType::DirectX);
		break;
#endif
	default:
		break;
	}
}

EXPORT_API App_ApiType App_GetApiType() {
	return static_cast<App_ApiType>(Iris2D::AppFactory::GetApiType());
}
