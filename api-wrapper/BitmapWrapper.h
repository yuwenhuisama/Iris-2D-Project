#ifndef _H_BITMAP_WRAPPER
#define _H_BITMAP_WRAPPER

#include "Common.h"

#undef LIBRARY_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif
	enum Bitmap_AlignType {
		nLeft = 0,
		nCenter,
		nRight,
	};

	EXPORT_API BITMAP_HANDLE Bitmap_Create(wchar_t* wstrFileName);
	EXPORT_API BITMAP_HANDLE Bitmap_Create2(unsigned int nWidth, unsigned int nHeight);
	EXPORT_API BITMAP_HANDLE Bitmap_Create3(BITMAP_HANDLE hSrcBitmap);
	EXPORT_API BITMAP_HANDLE Bitmap_CopyFrom(BITMAP_HANDLE hSrcBitmap);
	EXPORT_API void Bitmap_Release(BITMAP_HANDLE* hBitmap);

	EXPORT_API unsigned Bitmap_GetWidth(BITMAP_HANDLE hHandle);
	EXPORT_API unsigned Bitmap_GetHeight(BITMAP_HANDLE hHandle);
	EXPORT_API ResultCode Bitmap_Blt(BITMAP_HANDLE hHandle, unsigned int nDestX, unsigned int nDestY, BITMAP_HANDLE hSrcBitmap, RECT_HANDLE hSrcRect, float fOpacity);
	EXPORT_API ResultCode Bitmap_StretchBlt(BITMAP_HANDLE hHandle, RECT_HANDLE hDestRect, BITMAP_HANDLE hSrcBitmap, RECT_HANDLE hSrcRect, float fOpacity);
	EXPORT_API ResultCode Bitmap_FillRect(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, COLOR_HANDLE hColor);
	EXPORT_API ResultCode Bitmap_FillRect2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect, COLOR_HANDLE hColor);
	EXPORT_API ResultCode Bitmap_Clear(BITMAP_HANDLE hHandle);
	EXPORT_API ResultCode Bitmap_ClearRect(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight);
	EXPORT_API ResultCode Bitmap_ClearRect2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect);
	EXPORT_API COLOR_HANDLE Bitmap_GetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY);
	EXPORT_API ResultCode Bitmap_SetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, COLOR_HANDLE hColor);
	EXPORT_API ResultCode Bitmap_SaveToFile(BITMAP_HANDLE hHandle, wchar_t* wstrFilePath);
	EXPORT_API ResultCode Bitmap_HueChange(BITMAP_HANDLE hHandle, float fHue);
	EXPORT_API void Bitmap_SetFont(BITMAP_HANDLE hHandle, FONT_HANDLE* pFont);
	EXPORT_API FONT_HANDLE Bitmap_GetFont(BITMAP_HANDLE hHandle);
	EXPORT_API unsigned int Bitmap_TextSize(BITMAP_HANDLE hHandle, FONT_HANDLE hFont, wchar_t* wstrText);
	EXPORT_API ResultCode Bitmap_DrawText(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, wchar_t* wstrText, Bitmap_AlignType nAlign);
	EXPORT_API ResultCode Bitmap_DrawText2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect, wchar_t* wstrText, Bitmap_AlignType nAlign);
	EXPORT_API ResultCode Bitmap_Dispose(BITMAP_HANDLE hHandle);

#ifdef __cplusplus
}
#endif

#endif // _H_BITMAP_WRAPPER