#ifndef _H_FONT_WRAPPER
#define _H_FONT_WRAPPER

#include "Common.h"

#undef LIBRARY_EXPORTS
#ifdef __cplusplus
extern "C" {
#endif

	EXPORT_API bool Font_Existed(const wchar_t* wstrFontName);

	EXPORT_API FONT_HANDLE Font_Create(const wchar_t* wstrFontName);
	EXPORT_API void Font_Release(FONT_HANDLE* pFont);

	EXPORT_API wchar_t* Font_GetDefaultName();
	EXPORT_API unsigned int Font_GetDefaultSize();
	EXPORT_API bool Font_GetDefaultBold();
	EXPORT_API bool Font_GetDefaultItalic();
	EXPORT_API bool Font_GetDefaultShadow();
	EXPORT_API COLOR_HANDLE Font_GetDefaultColor();

	EXPORT_API void Font_SetName(FONT_HANDLE hHandle, const wchar_t* wstrFontName);
	EXPORT_API const wchar_t* Font_GetName(FONT_HANDLE hHandle);

	EXPORT_API void Font_SetSize(FONT_HANDLE hHandle, unsigned int nSize);
	EXPORT_API unsigned int Font_GetSize(FONT_HANDLE hHandle);

	EXPORT_API void Font_SetBold(FONT_HANDLE hHandle, bool bBold);
	EXPORT_API bool Font_GetBold(FONT_HANDLE hHandle);

	EXPORT_API void Font_SetItalic(FONT_HANDLE hHandle, bool bItalic);
	EXPORT_API bool Font_GetItalic(FONT_HANDLE hHandle);

	EXPORT_API void Font_SetShadow(FONT_HANDLE hHandle, bool bShadow);
	EXPORT_API bool Font_GetShadow(FONT_HANDLE hHandle);

	EXPORT_API void Font_SetColor(FONT_HANDLE hHandle, COLOR_HANDLE* pColor);
	EXPORT_API COLOR_HANDLE Font_GetColor(FONT_HANDLE hHandle);

#ifdef __cplusplus
}
#endif

#endif
