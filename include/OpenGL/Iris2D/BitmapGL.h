#ifndef _H_BITMAP_GL_
#define _H_BITMAP_GL_

#include "Common/Iris2D/IBitmap.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"


#ifdef _WIN32
#undef DrawText
#endif

namespace Iris2D {
	class TextureGL;
	class BitmapGL : public RefCounter, public IBitmap, public Proxied<Bitmap> {

		REF_FRIEND_DECLARE;

	public:
		static BitmapGL* Create(const std::wstring& wstrFileName);
		static BitmapGL* Create(unsigned int nWidth, unsigned int nHeight);
		static BitmapGL* Create(Bitmap* pSrcBitmap);
		static BitmapGL* CopyFrom(Bitmap* pSrcBitmap);

		static void Release(BitmapGL*& pBitmap);

	private:
		BitmapGL() = default;
		~BitmapGL() = default;

	private:
		Font* m_pFont = nullptr;
		TextureGL* m_pTexture = nullptr;

	public:
		// Í¨¹ý IBitmap ¼Ì³Ð
		 unsigned int GetWidth() const override;
		 unsigned int GetHeight() const override;
		 ResultCode Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) override;
		 ResultCode StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) override;
		 ResultCode FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor) override;
		 ResultCode FillRect(const Rect * pRect, const Color * pColor) override;
		 ResultCode Clear() override;
		 ResultCode ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) override;
		 ResultCode ClearRect(const Rect * pRect) override;
		 Color * GetPixel(unsigned int nX, unsigned int nY) const override;
		 ResultCode GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) override;

		 ResultCode SetPixel(unsigned int nX, unsigned int nY, const Color * pColor) override;
		 ResultCode SaveToFile(const std::wstring & wstrFilePath) override;
		 ResultCode HueChange(float fHue) override;
		 void SetFont(Font *& pFont) override;
		 Font * GetFont() const override;
		 unsigned int TextSize(const Font * pFont, const std::wstring & wstrText) override;
		 ResultCode TextSize(const Font * pFont, const std::wstring & wstrText, unsigned int& nSize) override;

		 ResultCode DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign) override;
		 ResultCode DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign) override;
		 ResultCode Dispose() override;

		TextureGL* GetTexture() const;

	};
}

#endif // !_H_BITMAP_GL_
