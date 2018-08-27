#ifndef _H_IBITMAP_
#define _H_IBITMAP_

#include "Common/Util/Result.h"
#include <string>

#undef DrawText

namespace Iris2D {
	class Rect;
	class Color;
	class Font;
	class Bitmap;

	enum class AlignType {
		Left,
		Center,
		Right,
	};

	class IBitmap {
	public:
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual ResultCode Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity) = 0;

		virtual ResultCode StretchBlt(const Rect* pDestRect, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity) = 0;

		virtual ResultCode FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color* pColor) = 0;
		virtual ResultCode FillRect(const Rect* pRect, const Color* pColor) = 0;

		virtual ResultCode Clear() = 0;

		virtual ResultCode ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) = 0;
		virtual ResultCode ClearRect(const Rect* pRect) = 0;

		virtual Color* GetPixel(unsigned int nX, unsigned int nY) const = 0;
		virtual ResultCode GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) = 0;

		virtual ResultCode SetPixel(unsigned int nX, unsigned int nY, const Color *pColor) = 0;

		virtual ResultCode SaveToFile(const std::wstring& wstrFilePath) = 0;

		virtual ResultCode HueChange(float fHue) = 0;

		virtual void SetFont(Font*& pFont) = 0;
		virtual Font* GetFont() const = 0;

		virtual unsigned int TextSize(const Font* pFont, const std::wstring& wstrText) = 0;
		virtual ResultCode TextSize(const Font* pFont, const std::wstring& wstrText, unsigned int& nSize) = 0;

		virtual ResultCode DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign) = 0;
		virtual ResultCode DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign) = 0;

		virtual ResultCode Dispose() = 0;
	};
};

#endif // !_H_IBITMAP_
