#ifndef _H_VIEWPORT_WRAPPER
#define _H_VIEWPORT_WRAPPER

#include "Common.h"

#undef LIBRARY_EXPORTS
#ifdef __cplusplus
extern "C" {
#endif

	EXPORT_API VIEWPORT_HANDLE Viewport_Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight);
	EXPORT_API VIEWPORT_HANDLE Viewport_Create2(const RECT_HANDLE pRect);
	EXPORT_API void Viewport_Release(VIEWPORT_HANDLE* pViewport);

	EXPORT_API void Viewport_ForceRelease(VIEWPORT_HANDLE* pViewport);

	EXPORT_API void Viewport_SetOX(VIEWPORT_HANDLE hHandle, float fOX);
	EXPORT_API float Viewport_GetOX(VIEWPORT_HANDLE hHandle);

	EXPORT_API void Viewport_SetOY(VIEWPORT_HANDLE hHandle, float fOY);
	EXPORT_API float Viewport_GetOY(VIEWPORT_HANDLE hHandle);

	EXPORT_API void Viewport_SetSrcRect(VIEWPORT_HANDLE hHandle, RECT_HANDLE* pSrcRect);
	EXPORT_API RECT_HANDLE Viewport_GetSrcRect(VIEWPORT_HANDLE hHandle);

	EXPORT_API void Viewport_SetTone(VIEWPORT_HANDLE hHandle, COLOR_HANDLE* pTone);
	EXPORT_API COLOR_HANDLE Viewport_GetTone(VIEWPORT_HANDLE hHandle);

	EXPORT_API void Viewport_SetZ(VIEWPORT_HANDLE hHandle, float fZ);
	EXPORT_API float Viewport_GetZ(VIEWPORT_HANDLE hHandle);

	EXPORT_API unsigned int Viewport_GetWidth(VIEWPORT_HANDLE hHandle);
	EXPORT_API unsigned int Viewport_GetHeight(VIEWPORT_HANDLE hHandle);


#ifdef __cplusplus
}
#endif

#endif