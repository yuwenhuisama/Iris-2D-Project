#ifndef _H_COMMON_DX_
#define _H_COMMON_DX_

#include "Common/CompileConfigure.h"
#include "Common/Util/Result.h"
#include "DxUtil/DirectXTex.h"
#include "DxUtil/WICTextureLoader.h"

#include <Windows.h>
#include <string>
#include <unordered_set>
#include <d3d11.h>
#include <D3DCompiler.h>
#include <DirectXMath.h>
#include <d2d1_2.h>
#include <dxgi1_2.h>
#include <d2d1effects.h>
#include <d2d1effects_1.h>
#include <d2d1effects_2.h>
#include <wincodec.h>
#include <wrl.h>
#include <dwrite_3.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Dwrite.lib")

//#if defined(DEBUG) || defined(_DEBUG)
//#pragma comment(lib, "./lib/Debug/DirectXTex.lib")
//#else
//#pragma comment(lib, "lib/Release/DirectXTex.lib")
//#pragma comment(lib, "Dxguid.lib")
//#endif

/*
#define BEGIN_SAFE_LOOP() \
	auto __pGraphics__ = GraphicsDX::Instance(); \
	auto __pApp__ = ApplicationDX::Instance(); \
	while (!pApp->IsQuited()) { \
		auto __fCurrentTime__ = static_cast<float>(::timeGetTime()); \
		auto __fElapsed__ = __fCurrentTime__ - GraphicsDX::Instance()->m_fLastTime; \
		__pGraphics__->m_fLastTime = __fCurrentTime__; \
		__pGraphics__->m_fLag += __fElapsed__; \
		while (__pGraphics__->m_fLag >= __pGraphics__->GetMsPerUpdate()) {

#define END_SAFE_LOOP() \
			__pGraphics__->m_fLag -= GraphicsDX::Instance()->GetMsPerUpdate(); \
		} \
		__pGraphics__->UpdateNoLock(); \
	}
*/

namespace Iris2D {
	template <class T>
	void SafeCOMRelease(T*& pPointer) {
		if (pPointer) {
			pPointer->Release();
			pPointer = nullptr;
		}
	}
}

#endif
