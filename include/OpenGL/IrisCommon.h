//
// Created by Huisama on 2018/6/26.
//

#ifndef _H_IRISCOMMON_
#define _H_IRISCOMMON_

#include "Common/Iris2DCompileConfigure.h"
#include "Common/Iris2DUtil/IrisResult.h"

#include <string>
#include <unordered_set>

#include <glew.h>
#include <glfw3.h>

#define BEGIN_SAFE_LOOP() \
	auto __pGraphics__ = IrisGraphics::Instance(); \
	auto __pApp__ = IrisApplication::Instance(); \
	while (!pApp->IsQuited()) { \
		auto __fCurrentTime__ = static_cast<float>(::timeGetTime()); \
		auto __fElapsed__ = __fCurrentTime__ - IrisGraphics::Instance()->m_fLastTime; \
		__pGraphics__->m_fLastTime = __fCurrentTime__; \
		__pGraphics__->m_fLag += __fElapsed__; \
		while (__pGraphics__->m_fLag >= __pGraphics__->GetMsPerUpdate()) {

#define END_SAFE_LOOP() \
			__pGraphics__->m_fLag -= IrisGraphics::Instance()->GetMsPerUpdate(); \
		} \
		__pGraphics__->UpdateNoLock(); \
	}

#endif
