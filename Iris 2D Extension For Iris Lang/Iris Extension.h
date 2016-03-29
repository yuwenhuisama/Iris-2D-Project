#ifdef IRISEXTENSION_EXPORTS
#define IRISEXTENSION_API __declspec(dllexport)
#else
#define IRISEXTENSION_API __declspec(dllexport)
#endif

#include "IrisLangLibrary.h"

#ifdef __cplusplus
extern "C" {
#endif
	IRISEXTENSION_API bool IR_Initialize();
	IRISEXTENSION_API bool IR_Release();
#ifdef __cplusplus
}
#endif