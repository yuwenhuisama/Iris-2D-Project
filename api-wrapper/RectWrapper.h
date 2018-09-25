#ifndef _H_RECT_WRAPPER
#define _H_RECT_WRAPPER

#include "Common.h"

#undef LIBRARY_EXPORTS
#ifdef __cplusplus
extern "C" {
#endif

	EXPORT_API RECT_HANDLE Rect_Create(float fX, float fY, float fWidth, float fHeight);
	EXPORT_API RECT_HANDLE Rect_Create2(float fLeft, float fTop, float fRight, float fBottom);
	EXPORT_API void Rect_Release(RECT_HANDLE* pRect);

	EXPORT_API void Rect_SetX(RECT_HANDLE hHandle, float fX);
	EXPORT_API float Rect_GetX(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetY(RECT_HANDLE hHandle, float fY);
	EXPORT_API float Rect_GetY(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetWidth(RECT_HANDLE hHandle, float fWidth);
	EXPORT_API float Rect_GetWidth(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetHeight(RECT_HANDLE hHandle, float fHeight);
	EXPORT_API float Rect_GetHeight(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetLeft(RECT_HANDLE hHandle, float fLeft);
	EXPORT_API float Rect_GetLeft(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetTop(RECT_HANDLE hHandle, float fTop);
	EXPORT_API float Rect_GetTop(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetRight(RECT_HANDLE hHandle, float fRight);
	EXPORT_API float Rect_GetRight(RECT_HANDLE hHandle);

	EXPORT_API void Rect_SetBottom(RECT_HANDLE hHandle, float fBottom);
	EXPORT_API float Rect_GetBottom(RECT_HANDLE hHandle);

	EXPORT_API void Rect_Set(RECT_HANDLE hHandle, float fX, float fY, float fWidth, float fHeight);
	EXPORT_API void Rect_Set2(RECT_HANDLE hHandle, float fLeft, float fTop, float fRight, float fBottom);

	EXPORT_API bool Rect_CheckInsectionWith(RECT_HANDLE hHandle, const RECT_HANDLE pRect);


#ifdef __cplusplus
}
#endif

#endif