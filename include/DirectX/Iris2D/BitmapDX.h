#ifndef _H_BITMAP_DX_
#define _H_BITMAP_DX_

#include "Common/Common.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/IBitmap.h"

#undef DrawText

namespace Iris2D
{
	class TextureDX;
	class Rect;
	class Color;
	class Font;
	class Btmap;

	class FontDX;
	class BitmapDX: public Proxied<Bitmap>, public IBitmap, public RefCounter
	{
	private:
		TextureDX* m_pTexture = nullptr;
		Font* m_pFont = nullptr;

	public:
		static BitmapDX* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);
		static BitmapDX* Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		static BitmapDX* Create(Bitmap* pSrcBitmap, IR_PARAM_RESULT);
		static BitmapDX* CopyFrom(Bitmap* pSrcBitmap, IR_PARAM_RESULT);

		static void Release(BitmapDX*& pBitmap);

		virtual unsigned int GetWidth() const;

		virtual unsigned int GetHeight() const;

		virtual bool Blt(unsigned int nDestX, unsigned int nDestY,  const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

		virtual bool StretchBlt(const Rect* pDestRect, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

		virtual bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color* pColor, IR_PARAM_RESULT);

		virtual bool FillRect(const Rect* pRect, const Color* pColor, IR_PARAM_RESULT);
		
		virtual bool Clear(IR_PARAM_RESULT);
		
		virtual bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		virtual bool ClearRect(const Rect* pRect, IR_PARAM_RESULT);

		virtual Color* GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const;

		virtual bool SetPixel(unsigned int nX, unsigned int nY, const Color *pColor, IR_PARAM_RESULT);
		
		virtual bool SaveToFile(const std::wstring& wstrFilePath);

		virtual bool HueChange(float fHue, IR_PARAM_RESULT);

		virtual void SetFont(Font*& pFont);
		virtual Font* GetFont() const;

		virtual unsigned int TextSize(const Font* pFont, const std::wstring& wstrText, IR_PARAM_RESULT);
		virtual bool DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT);
		virtual bool DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT);

		virtual bool Dispose();

		TextureDX* GetTexture() const;
	private:

		IDWriteTextFormat* CreateTextFormat(const FontDX * pFont);

		BitmapDX() = default;
		~BitmapDX();
	};

}
 // !_H_BITMAP_DX_
#endif