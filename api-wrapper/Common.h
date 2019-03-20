#ifndef _H_COMMON_WRAPPER_
#define _H_COMMON_WRAPPER_

#include "Common/Iris2D.h"
#include "Common/Util/Result.h"
#include "Types.h"

#ifdef LIBRARY_EXPORTS

#ifdef PLATFORM_WINDOWS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

#else
#define EXPORT_API __declspec(dllimport)
#endif

#endif
