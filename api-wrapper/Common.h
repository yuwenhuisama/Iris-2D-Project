#ifndef _H_COMMON_WRAPPER_
#define _H_COMMON_WRAPPER_

#include "Common/Iris2D.h"
#include "Types.h"

#ifdef LIBRARY_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

#endif