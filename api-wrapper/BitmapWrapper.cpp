#define LIBRARY_EXPORTS
#include "BitmapWrapper.h"

EXPORT_API BITMAP_HANDLE Create1(const wchar_t*& wstrFileName) {
	return Iris2D::Bitmap::Create(wstrFileName);
}

EXPORT_API BITMAP_HANDLE Create2(unsigned int nWidth, unsigned int nHeight) {
	return Iris2D::Bitmap::Create(nWidth, nHeight);
}

EXPORT_API BITMAP_HANDLE Create3(BITMAP_HANDLE pSrcBitmap) {
	auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(pSrcBitmap);
	return Iris2D::Bitmap::Create(pCastedSrcBitmap);
}

EXPORT_API BITMAP_HANDLE CopyFrom(BITMAP_HANDLE pSrcBitmap) {
	auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(pSrcBitmap);
	return Iris2D::Bitmap::CopyFrom(pCastedSrcBitmap);
}

EXPORT_API void Release(BITMAP_HANDLE& pBitmap) {
	auto pCastedBitmap = reinterpret_cast<Iris2D::Bitmap*>(pBitmap);
	return Iris2D::Bitmap::Release(pCastedBitmap);
}

EXPORT_API int GetWidth(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	return pBitmap->GetWidth();
}
EXPORT_API int GetHeight(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	return pBitmap->GetHeight();
}

EXPORT_API bool Blt(BITMAP_HANDLE hHandle, unsigned int nDestX, unsigned int nDestY, const BITMAP_HANDLE pSrcBitmap, const RECT_HANDLE pSrcRect, float fOpacity) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(pSrcBitmap);
	auto pCastedSrcRect = reinterpret_cast<Iris2D::Rect*>(pSrcRect);

	return pBitmap->Blt(nDestX, nDestY, pCastedSrcBitmap, pCastedSrcRect, fOpacity);
}

EXPORT_API bool StretchBlt(BITMAP_HANDLE hHandle, const RECT_HANDLE pDestRect, const BITMAP_HANDLE pSrcBitmap, const RECT_HANDLE pSrcRect, float fOpacity) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedDestRect = reinterpret_cast<Iris2D::Rect*>(pDestRect);
	auto pCastedSrcRect = reinterpret_cast<Iris2D::Rect*>(pSrcRect);
	auto pCastedSrcBitmap = reinterpret_cast<Iris2D::Bitmap*>(pSrcBitmap);

	return pBitmap->StretchBlt(pCastedDestRect, pCastedSrcBitmap, pCastedSrcRect, fOpacity);
}

EXPORT_API bool FillRect1(BITMAP_HANDLE hHandle, unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const COLOR_HANDLE pColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedColor = reinterpret_cast<Iris2D::Color*>(pColor);

	pBitmap->FillRect(nX, nY, nWidth, nHeight, pCastedColor);
}

EXPORT_API bool FillRect2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect, const COLOR_HANDLE pColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(pRect);
	auto pCastedColor = reinterpret_cast<Iris2D::Color*>(pColor);

	pBitmap->FillRect(pCastedRect, pCastedColor);
}

EXPORT_API bool Clear(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	pBitmap->Clear();
}

EXPORT_API bool ClearRect1(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	pBitmap->ClearRect(nX, nY, nWidth, nHeight);
}

EXPORT_API bool ClearRect2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(pRect);

	pBitmap->ClearRect(pCastedRect);
}

EXPORT_API COLOR_HANDLE GetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->GetPixel(nX, nY);
}

EXPORT_API bool SetPixel(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, const COLOR_HANDLE pColor) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedColor = reinterpret_cast<Iris2D::Color*>(pColor);

	return pBitmap->SetPixel(nX, nY, pCastedColor);
}

EXPORT_API bool SaveToFile(BITMAP_HANDLE hHandle, const wchar_t* & wstrFilePath) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->SaveToFile(wstrFilePath);
}

EXPORT_API bool HueChange(BITMAP_HANDLE hHandle, float fHue) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->HueChange(fHue);
}

EXPORT_API void SetFont(BITMAP_HANDLE hHandle, FONT_HANDLE& pFont) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedFont = reinterpret_cast<Iris2D::Font*>(pFont);

	pBitmap->SetFont(pCastedFont);
}
EXPORT_API FONT_HANDLE GetFont(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->GetFont();
}

EXPORT_API unsigned int TextSize(BITMAP_HANDLE hHandle, const FONT_HANDLE pFont, const wchar_t* & wstrText) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedFont = reinterpret_cast<Iris2D::Font*>(pFont);

	return pBitmap->TextSize(pCastedFont, wstrText);
}

EXPORT_API bool DrawText1(BITMAP_HANDLE hHandle, unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const wchar_t* & wstrText, AlignType nAlign) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->DrawText(nX, nY, nWidth, nHeight, wstrText, nAlign);
}

EXPORT_API bool DrawText2(BITMAP_HANDLE hHandle, const RECT_HANDLE pRect, const wchar_t* & wstrText, AlignType nAlign) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);
	auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(pRect);

	return pBitmap->DrawText(pCastedRect, wstrText, nAlign);
}
EXPORT_API bool Dispose(BITMAP_HANDLE hHandle) {
	auto pBitmap = reinterpret_cast<Iris2D::Bitmap*>(hHandle);

	return pBitmap->Dispose();
}