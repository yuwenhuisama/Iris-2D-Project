//
// Created by Huisama on 2018/6/26.
//

#ifndef _H_COMMON_C_
#define _H_COMMON_C_

#define IR_VERSION "0.3.1"

#include "Common/CompileConfigure.h"
#include "Common/Util/DebugUtil.h"

#include "OpenGL/Common.h"

#ifdef _WIN32
#define PLATFORM_WINDOWS
#else
#define PLATFORM_APPLE
#endif

#ifdef PLATFORM_APPLE
#define BOOL bool
#define VOID void
#endif

#ifdef _WIN32
#include "DirectX/Common.h"
#endif

#endif //_H_COMMON_C_
