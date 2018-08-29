#ifndef _H_BITMAP_WRAPPER
#define _H_BITMAP_WRAPPER

#include "Common.h"

#undef LIBRARY_EXPORTS

extern "C" {
	enum AlignType {
		nLeft = 0,
		nCenter,
		nRight,
	};

	EXPORT_API BITMAP_HANDLE Bitmap_Create1(const wchar_t* & wstrFileName);
	EXPORT_API BITMAP_HANDLE Bitmap_Create2(unsigned int nWidth, unsigned int nHeight);
	EXPORT_API BITMAP_HANDLE Bitmap_Create3(BITMAP_HANDLE pSrcBitmap);
	EXPORT_API BITMAP_HANDLE Bitmap_CopyFrom(BITMAP_HANDLE pSrcBitmap);
	EXPORT_API void Bitmap_Release(BITMAP_HANDLE& pBitmap);

	EXPORT_API int Bitmap_GetWidth(BITMAP_HANDLE hHandle);
	EXPORT_API int Bitmap_GetHeight(BITMAP_HANDLE hHandle);
	EXPORT_API bool Bitmap_Blt(BITMAP_HANDLE hHandle, unsigned int nDestX, unsigned int nDestY, const BITMAP_HANDLE pSrcBitmap, const RECT_HANDLE pSrcRect, float fOpacity);
	EXPORT_API bool Bitmap_StretchBlt(BITMAP_HANDLE hHandle, const RECT_HANDLE pDestRect, const BITMAP_HANDLE pSrcBitmap, const RECT_HANDLE pSrcRect, float fOpacity);
	EXPORT_API bool Bitmap_FillRect1(BITMAP_HANDLE hHandle, unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const COLOR_HANDLE pColor);
	EXPORT_API bool Bitmap_FillRect2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect, const COLOR_HANDLE pColor);
	EXPORT_API bool Bitmap_Clear(BITMAP_HANDLE hHandle);
	EXPORT_API bool Bitmap_ClearRect1(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight);
	EXPORT_API bool Bitmap_ClearRect2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect);
	EXPORT_API COLOR_HANDLE Bitmap_GetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY);
	EXPORT_API bool Bitmap_SetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, const COLOR_HANDLE pColor);
	EXPORT_API bool Bitmap_SaveToFile(BITMAP_HANDLE hHandle, const wchar_t* & wstrFilePath);
	EXPORT_API bool Bitmap_HueChange(BITMAP_HANDLE hHandle, float fHue);
	EXPORT_API void Bitmap_SetFont(BITMAP_HANDLE hHandle, FONT_HANDLE& pFont);
	EXPORT_API FONT_HANDLE Bitmap_GetFont(BITMAP_HANDLE hHandle);
	EXPORT_API unsigned int Bitmap_TextSize(BITMAP_HANDLE hHandle, const FONT_HANDLE pFont, const wchar_t* & wstrText);
	EXPORT_API bool Bitmap_DrawText1(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const wchar_t* & wstrText, AlignType nAlign);
	EXPORT_API bool Bitmap_DrawText2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect, const wchar_t* & wstrText, AlignType nAlign);
	EXPORT_API bool Bitmap_Dispose(BITMAP_HANDLE hHandle);
}

#endif // _H_BITMAP_WRAPPER