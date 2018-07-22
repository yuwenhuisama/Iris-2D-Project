#ifndef _H_BITMAP_GL_
#define _H_BITMAP_GL_

#include "Common/Iris2D/IBitmap.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D {
	class TextureGL;
	class BitmapGL : public RefCounter, public IBitmap, public Proxied<Bitmap> {
	public:
		static BitmapGL* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);
		static BitmapGL* Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		static BitmapGL* Create(Bitmap* pSrcBitmap, IR_PARAM_RESULT);
		static BitmapGL* CopyFrom(Bitmap* pSrcBitmap, IR_PARAM_RESULT);

		static void Release(BitmapGL*& pBitmap);

	private:
		Font* m_pFont = nullptr;
		TextureGL* m_pTexture = nullptr;

	public:
		// Í¨¹ý IBitmap ¼Ì³Ð
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
		virtual bool Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT) override;
		virtual bool StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT) override;
		virtual bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor, IR_PARAM_RESULT) override;
		virtual bool FillRect(const Rect * pRect, const Color * pColor, IR_PARAM_RESULT) override;
		virtual bool Clear(IR_PARAM_RESULT) override;
		virtual bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) override;
		virtual bool ClearRect(const Rect * pRect, IR_PARAM_RESULT) override;
		virtual Color * GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const override;
		virtual bool SetPixel(unsigned int nX, unsigned int nY, const Color * pColor, IR_PARAM_RESULT) override;
		virtual bool SaveToFile(const std::wstring & wstrFilePath) override;
		virtual bool HueChange(float fHue, IR_PARAM_RESULT) override;
		virtual void SetFont(Font *& pFont) override;
		virtual Font * GetFont() const override;
		virtual unsigned int TextSize(const Font * pFont, const std::wstring & wstrText, IR_PARAM_RESULT) override;
		virtual bool DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT) override;
		virtual bool DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT) override;
		virtual bool Dispose() override;

		TextureGL* GetTexture();
	};
}

#endif // !_H_BITMAP_GL_
