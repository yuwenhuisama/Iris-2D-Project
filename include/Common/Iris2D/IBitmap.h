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

		virtual bool Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity, IR_PARAM_RESULT) = 0;

		virtual bool StretchBlt(const Rect* pDestRect, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity, IR_PARAM_RESULT) = 0;

		virtual bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color* pColor, IR_PARAM_RESULT) = 0;
		virtual bool FillRect(const Rect* pRect, const Color* pColor, IR_PARAM_RESULT) = 0;

		virtual bool Clear(IR_PARAM_RESULT) = 0;

		virtual bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) = 0;
		virtual bool ClearRect(const Rect* pRect, IR_PARAM_RESULT) = 0;

		virtual Color* GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const = 0;

		virtual bool SetPixel(unsigned int nX, unsigned int nY, const Color *pColor, IR_PARAM_RESULT) = 0;

		virtual bool SaveToFile(const std::wstring& wstrFilePath) = 0;

		virtual bool HueChange(float fHue, IR_PARAM_RESULT) = 0;

		virtual void SetFont(Font*& pFont) = 0;
		virtual Font* GetFont() const = 0;

		virtual unsigned int TextSize(const Font* pFont, const std::wstring& wstrText, IR_PARAM_RESULT) = 0;
		virtual bool DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT) = 0;
		virtual bool DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT) = 0;

		virtual bool Dispose() = 0;
	};
};

#endif // !_H_IBITMAP_
