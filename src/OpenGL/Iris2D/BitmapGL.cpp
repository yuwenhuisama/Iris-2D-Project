#include "OpenGL/Iris2D/BitmapGL.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"

namespace Iris2D {
	BitmapGL * BitmapGL::Create(const std::wstring & wstrFileName) {
		const auto pTexture = TextureGL::Create(wstrFileName);

		if (!pTexture) {
			return nullptr;
		}

		const auto pBitmap = new BitmapGL();

		pBitmap->m_pTexture = pTexture;

		return pBitmap;
	}

	BitmapGL * BitmapGL::Create(unsigned int nWidth, unsigned int nHeight) {
		const auto pTexture = TextureGL::Create(nWidth, nHeight);

		if (!pTexture) {
			return nullptr;
		}

		const auto pBitmap = new BitmapGL();

		pBitmap->m_pTexture = pTexture;

		return pBitmap;
	}

	BitmapGL * BitmapGL::Create(Bitmap * pSrcBitmapGL) {
		return nullptr;
	}

	BitmapGL * BitmapGL::CopyFrom(Bitmap * pSrcBitmapGL) {
		return nullptr;
	}

	void BitmapGL::Release(BitmapGL *& pBitmap) {

		if (!pBitmap) {
			return;
		}

		RefferRelease(pBitmap);

	}

	unsigned int BitmapGL::GetWidth() const {
		return m_pTexture->GetWidth();
	}

	unsigned int BitmapGL::GetHeight() const {
		return m_pTexture->GetHeight();
	}

	ResultCode BitmapGL::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmapGL, const Rect * pSrcRect, float fOpacity) {
		return IRR_Success;
	}

	ResultCode BitmapGL::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmapGL, const Rect * pSrcRect, float fOpacity) {
		return IRR_Success;
	}

	ResultCode BitmapGL::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor) {
		return IRR_Success;
	}

	ResultCode BitmapGL::FillRect(const Rect * pRect, const Color * pColor) {
		return IRR_Success;
	}

	ResultCode BitmapGL::Clear() {
		return IRR_Success;
	}

	ResultCode BitmapGL::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
		return IRR_Success;
	}

	ResultCode BitmapGL::ClearRect(const Rect * pRect) {
		return IRR_Success;
	}

	Color * BitmapGL::GetPixel(unsigned int nX, unsigned int nY) const {
		return nullptr;
	}

	ResultCode BitmapGL::GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) {
		return IRR_Success;
	}

	ResultCode BitmapGL::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor) {
		return IRR_Success;
	}

	ResultCode BitmapGL::SaveToFile(const std::wstring & wstrFilePath) {
		return IRR_Success;
	}

	ResultCode BitmapGL::HueChange(float fHue) {
		return IRR_Success;
	}

	void BitmapGL::SetFont(Font *& pFont) {
	}

	Font * BitmapGL::GetFont() const {
		return nullptr;
	}

	unsigned int BitmapGL::TextSize(const Font * pFont, const std::wstring & wstrText) {
		return 0;
	}

	ResultCode BitmapGL::TextSize(const Font* pFont, const std::wstring& wstrText, unsigned int& nSize) {
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign) {
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign) {
		return IRR_Success;
	}

	ResultCode BitmapGL::Dispose() {
		TextureGL::Release(m_pTexture);
		return IRR_Success;
	}

	TextureGL * BitmapGL::GetTexture() const {
		return m_pTexture;
	}
}
