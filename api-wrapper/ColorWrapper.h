#ifndef _H_COLOR_WRAPPER
#define _H_COLOR_WRAPPER

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif

	EXPORT_API COLOR_HANDLE Color_Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);
	EXPORT_API void Color_Release(COLOR_HANDLE* pColor);

	EXPORT_API void Color_SetRed(COLOR_HANDLE hHandle, unsigned char cRed) ;
	EXPORT_API unsigned char Color_GetRed(COLOR_HANDLE hHandle);

	EXPORT_API void Color_SetGreen(COLOR_HANDLE hHandle, unsigned char cGreen);
	EXPORT_API unsigned char Color_GetGreen(COLOR_HANDLE hHandle);

	EXPORT_API void Color_SetBlue(COLOR_HANDLE hHandle, unsigned char cBlue);
	EXPORT_API unsigned char Color_GetBlue(COLOR_HANDLE hHandle);

	EXPORT_API void Color_SetAlpha(COLOR_HANDLE hHandle, unsigned char cAlpha);
	EXPORT_API unsigned char Color_GetAlpha(COLOR_HANDLE hHandle);

	EXPORT_API void Color_Set(COLOR_HANDLE hHandle, unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);

#ifdef __cplusplus
}
#endif

#endif