#define LIBRARY_EXPORTS
#include "BitmapWrapper.h"

EXPORT_API BITMAP_HANDLE Bitmap_Create(wchar_t* wstrFileName) {
	return Iris2D::Bitmap::Create(wstrFileName);
}

EXPORT_API BITMAP_HANDLE Bitmap_Create2(unsigned int nWidth, unsigned int nHeight) {
	return Iris2D::Bitmap::Create(nWidth, nHeight);
}

EXPORT_API BITMAP_HANDLE Bitmap_Create3(BITMAP_HANDLE hSrcBitmap) {
	const auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(hSrcBitmap);
	return Iris2D::Bitmap::Create(pCastedSrcBitmap);
}

EXPORT_API BITMAP_HANDLE Bitmap_CopyFrom(BITMAP_HANDLE hSrcBitmap) {
	const auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(hSrcBitmap);
	return Iris2D::Bitmap::CopyFrom(pCastedSrcBitmap);
}

EXPORT_API void Bitmap_Release(BITMAP_HANDLE* pBitmap) {
	auto pCastedBitmap = reinterpret_cast<Iris2D::Bitmap*&>(*pBitmap);
	return Iris2D::Bitmap::Release(pCastedBitmap);
}

EXPORT_API unsigned int Bitmap_GetWidth(BITMAP_HANDLE hHandle) {
	const auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	return pBitmap->GetWidth();
}
EXPORT_API unsigned Bitmap_GetHeight(BITMAP_HANDLE hHandle) {
	const auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	return pBitmap->GetHeight();
}

EXPORT_API ResultCode Bitmap_Blt(BITMAP_HANDLE hHandle, unsigned int nDestX, unsigned int nDestY, BITMAP_HANDLE hSrcBitmap, RECT_HANDLE hSrcRect, float fOpacity) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(hSrcBitmap);
	const auto pCastedSrcRect = reinterpret_cast<Iris2D::Rect*>(hSrcRect);

	return pBitmap->Blt(nDestX, nDestY, pCastedSrcBitmap, pCastedSrcRect, fOpacity);
}

EXPORT_API ResultCode Bitmap_StretchBlt(BITMAP_HANDLE hHandle, RECT_HANDLE hDestRect, BITMAP_HANDLE hSrcBitmap, RECT_HANDLE hSrcRect, float fOpacity) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedDestRect = reinterpret_cast<Iris2D::Rect*>(hDestRect);
	const auto pCastedSrcRect = reinterpret_cast<Iris2D::Rect*>(hSrcRect);
	const auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(hSrcBitmap);

	return pBitmap->StretchBlt(pCastedDestRect, pCastedSrcBitmap, pCastedSrcRect, fOpacity);
}

EXPORT_API ResultCode Bitmap_FillRect(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, COLOR_HANDLE hColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedColor = reinterpret_cast<Iris2D::Color*>(hColor);

	return pBitmap->FillRect(nX, nY, nWidth, nHeight, pCastedColor);
}

EXPORT_API ResultCode Bitmap_FillRect2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect, COLOR_HANDLE hColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(hRect);
	const auto pCastedColor = reinterpret_cast<Iris2D::Color*>(hColor);

	return pBitmap->FillRect(pCastedRect, pCastedColor);
}

EXPORT_API ResultCode Bitmap_Clear(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->Clear();
}

EXPORT_API ResultCode Bitmap_ClearRect(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->ClearRect(nX, nY, nWidth, nHeight);
}

EXPORT_API ResultCode Bitmap_ClearRect2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(hRect);

	return pBitmap->ClearRect(pCastedRect);
}

EXPORT_API COLOR_HANDLE Bitmap_GetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY) {
	const auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->GetPixel(nX, nY);
}

EXPORT_API ResultCode Bitmap_SetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, COLOR_HANDLE hColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedColor = reinterpret_cast<Iris2D::Color*>(hColor);

	return pBitmap->SetPixel(nX, nY, pCastedColor);
}

EXPORT_API ResultCode Bitmap_SaveToFile(BITMAP_HANDLE hHandle, wchar_t* wstrFilePath) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->SaveToFile(wstrFilePath);
}

EXPORT_API ResultCode Bitmap_HueChange(BITMAP_HANDLE hHandle, float fHue) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->HueChange(fHue);
}

EXPORT_API void Bitmap_SetFont(BITMAP_HANDLE hHandle, FONT_HANDLE* pFont) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedFont = reinterpret_cast<Iris2D::Font*&>(*pFont);

	pBitmap->SetFont(pCastedFont);
}
EXPORT_API FONT_HANDLE Bitmap_GetFont(BITMAP_HANDLE hHandle) {
	const auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->GetFont();
}

EXPORT_API unsigned int Bitmap_TextSize(BITMAP_HANDLE hHandle, FONT_HANDLE hFont, wchar_t* wstrText) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedFont = reinterpret_cast<Iris2D::Font*>(hFont);

	return pBitmap->TextSize(pCastedFont, wstrText);
}

EXPORT_API ResultCode Bitmap_DrawText(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, wchar_t* wstrText, Bitmap_AlignType nAlign) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->DrawText(nX, nY, nWidth, nHeight, wstrText, static_cast<Iris2D::AlignType>(nAlign));
}

EXPORT_API ResultCode Bitmap_DrawText2(BITMAP_HANDLE hHandle, RECT_HANDLE hRect, wchar_t* wstrText, Bitmap_AlignType nAlign) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	const auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(hRect);

	return pBitmap->DrawText(pCastedRect, wstrText, static_cast<Iris2D::AlignType>(nAlign));
}
EXPORT_API ResultCode Bitmap_Dispose(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->Dispose();
}