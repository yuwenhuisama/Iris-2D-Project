#ifndef _H_APP_FACTORY_WRAPPER_
#define _H_APP_FACTORY_WRAPPER_

#include "Common.h"

#undef LIBRARY_EXPORTS

extern "C" {
	enum App_ApiType {
		OPENGL = 0,
		DIRECTX,
	};

	EXPORT_API void App_InitApiType(App_ApiType eApiType);
	EXPORT_API App_ApiType App_GetApiType();
}

#endif // _H_APP_FACTORY_WRAPPER_
