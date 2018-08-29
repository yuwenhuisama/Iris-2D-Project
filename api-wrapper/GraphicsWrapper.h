#ifndef _H_GRAPHICS_WRAPPER_
#define _H_GRAPHICS_WRAPPER_

#include "Common.h"

#undef LIBRARY_EXPORTS
#ifdef __cplusplus
extern "C" {
#endif

	EXPORT_API GRAPHICS_HANDLE Graphics_GetInstance();
	EXPORT_API ResultCode Graphics_Update(GRAPHICS_HANDLE hGraphics);
	EXPORT_API ResultCode Graphics_UpdateNoLock(GRAPHICS_HANDLE hGraphics);

	EXPORT_API ResultCode Graphics_Wait(GRAPHICS_HANDLE hGraphics, unsigned int nDuration);

	EXPORT_API ResultCode Graphics_FadeOut(GRAPHICS_HANDLE hGraphics, unsigned int nDuration);
	EXPORT_API ResultCode Graphics_FadeIn(GRAPHICS_HANDLE hGraphics, unsigned int nDuration);

	EXPORT_API ResultCode Graphics_Freeze(GRAPHICS_HANDLE hGraphics);
	EXPORT_API ResultCode Graphics_Transition(GRAPHICS_HANDLE hGraphics, unsigned int nDuration, wchar_t* wstrFilename, unsigned int nVague);

	EXPORT_API void Graphics_FrameReset(GRAPHICS_HANDLE hGraphics);

	EXPORT_API ResultCode Graphics_ResizeScreen(GRAPHICS_HANDLE hGraphics, unsigned int nWidth, unsigned int nHeight);

	EXPORT_API void Graphics_SetWidth(GRAPHICS_HANDLE hGraphics, unsigned int nWidth);
	EXPORT_API unsigned int Graphics_GetWidth(GRAPHICS_HANDLE hGraphics);
	EXPORT_API void Graphics_SetHeight(GRAPHICS_HANDLE hGraphics, unsigned int nHeight);
	EXPORT_API unsigned int Graphics_GetHeight(GRAPHICS_HANDLE hGraphics);

	EXPORT_API unsigned int Graphics_GetFrameCount(GRAPHICS_HANDLE hGraphics);

	EXPORT_API float Graphics_GetBrightness(GRAPHICS_HANDLE hGraphics);
	EXPORT_API void Graphics_SetBrightness(GRAPHICS_HANDLE hGraphics, float fBrightness);

	EXPORT_API void Graphics_SetFrameRate(GRAPHICS_HANDLE hGraphics, float fFrameRate);
	EXPORT_API float Graphics_GetFrameRate(GRAPHICS_HANDLE hGraphics);

	EXPORT_API void Graphics_Release(GRAPHICS_HANDLE hGraphics);
	EXPORT_API float Graphics_GetMsPerUpdate(GRAPHICS_HANDLE hGraphics);

#ifdef __cplusplus
}
#endif

#endif // _H_GRAPHICS_WRAPPER_
