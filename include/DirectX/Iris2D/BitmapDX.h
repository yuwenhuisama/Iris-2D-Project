#ifndef _H_BITMAP_DX_
#define _H_BITMAP_DX_

#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/IBitmap.h"

#undef DrawText

struct IDWriteTextFormat;

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
		static BitmapDX* Create(const std::wstring& wstrFileName);
		static BitmapDX* Create(unsigned int nWidth, unsigned int nHeight);
		static BitmapDX* Create(Bitmap* pSrcBitmap);
		static BitmapDX* CopyFrom(Bitmap* pSrcBitmap);

		static void Release(BitmapDX*& pBitmap);

		unsigned int GetWidth() const override;

		unsigned int GetHeight() const override;

		ResultCode Blt(unsigned int nDestX, unsigned int nDestY,  const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity) override;

		ResultCode StretchBlt(const Rect* pDestRect, const Bitmap* pSrcBitmap, const Rect* pSrcRect, float fOpacity) override;

		ResultCode FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color* pColor) override;

		ResultCode FillRect(const Rect* pRect, const Color* pColor) override;

		ResultCode Clear() override;

		ResultCode ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) override;

		ResultCode ClearRect(const Rect* pRect) override;

		Color* GetPixel(unsigned int nX, unsigned int nY) const override;

		ResultCode SetPixel(unsigned int nX, unsigned int nY, const Color *pColor) override;

		ResultCode SaveToFile(const std::wstring& wstrFilePath) override;

		ResultCode HueChange(float fHue) override;

		void SetFont(Font*& pFont) override;
		Font* GetFont() const override;

		unsigned int TextSize(const Font* pFont, const std::wstring& wstrText) override;
		ResultCode DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign) override;
		ResultCode DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign) override;

		ResultCode GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) override;
		ResultCode TextSize(const Font* pFont, const std::wstring& wstrText, unsigned int& nSize) override;

		ResultCode Dispose() override;

		TextureDX* GetTexture() const;
	private:

		IDWriteTextFormat* CreateTextFormat(const FontDX * pFont);

		BitmapDX() = default;
		~BitmapDX();
	
	};

}
 // !_H_BITMAP_DX_
#endif