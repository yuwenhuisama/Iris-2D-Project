#include "Common/Iris2D/Bitmap.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/BitmapGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/BitmapDX.h"
#endif // _WIN32


namespace Iris2D {
	Bitmap::Bitmap(IBitmap* pBitmap) : Proxy(pBitmap) {}

	Bitmap * Bitmap::Create(const std::wstring & wstrFileName) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(wstrFileName);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = BitmapGL::Create(wstrFileName);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::Create(unsigned int nWidth, unsigned int nHeight) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(nWidth, nHeight);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = BitmapGL::Create(nWidth, nHeight);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::Create(Bitmap * pSrcBitmap) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(pSrcBitmap);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = BitmapGL::Create(pSrcBitmap);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::CopyFrom(Bitmap * pSrcBitmap) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::CopyFrom(pSrcBitmap);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = BitmapGL::CopyFrom(pSrcBitmap);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
		default:
			break;
		}
		return pBitmap;
	}

	void Bitmap::Release(Bitmap *& pBitmap) {
		if (!pBitmap) {
			return;
		}

		auto* pProxied = pBitmap->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			BitmapDX::Release(reinterpret_cast<BitmapDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			BitmapGL::Release(reinterpret_cast<BitmapGL*&>(pProxied));
			break;
		default:
			break;
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pBitmap;
			pBitmap = nullptr;
		}
	}

	unsigned int Bitmap::GetWidth() const {
		return m_pProxied->GetWidth();
	}

	unsigned int Bitmap::GetHeight() const {
		return m_pProxied->GetHeight();
	}

	ResultCode Bitmap::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) {
		return m_pProxied->Blt(nDestX, nDestY, pSrcBitmap, pSrcRect, fOpacity);
	}

	ResultCode Bitmap::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) {
		return m_pProxied->StretchBlt(pDestRect, pSrcBitmap, pSrcRect, fOpacity);
	}

	ResultCode Bitmap::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor) {
		return m_pProxied->FillRect(nX, nY, nWidth, nHeight, pColor);
	}

	ResultCode Bitmap::FillRect(const Rect * pRect, const Color * pColor) {
		return m_pProxied->FillRect(pRect, pColor);
	}

	ResultCode Bitmap::Clear() {
		return m_pProxied->Clear();
	}

	ResultCode Bitmap::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
		return m_pProxied->ClearRect(nX, nY, nWidth, nHeight);
	}

	ResultCode Bitmap::ClearRect(const Rect * pRect) {
		return m_pProxied->ClearRect(pRect);
	}

	Color * Bitmap::GetPixel(unsigned int nX, unsigned int nY) const {
		return m_pProxied->GetPixel(nX, nY);
	}

	ResultCode Bitmap::GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) {
		return m_pProxied->GetPixel(nX, nY, pColor);
	}

	ResultCode Bitmap::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor) {
		return m_pProxied->SetPixel(nX, nY, pColor);
	}

	ResultCode Bitmap::SaveToFile(const std::wstring & wstrFilePath) {
		return m_pProxied->SaveToFile(wstrFilePath);
	}

	ResultCode Bitmap::HueChange(float fHue) {
		return m_pProxied->HueChange(fHue);
	}

	void Bitmap::SetFont(Font *& pFont) {
		m_pProxied->SetFont(pFont);
	}

	Font * Bitmap::GetFont() const {
		return m_pProxied->GetFont();
	}

	unsigned int Bitmap::TextSize(const Font * pFont, const std::wstring & wstrText) {
		return m_pProxied->TextSize(pFont, wstrText);
	}

	ResultCode Bitmap::TextSize(const Font * pFont, const std::wstring & wstrText, unsigned int& nSize) {
		return m_pProxied->TextSize(pFont, wstrText, nSize);
	}

	ResultCode Bitmap::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign) {
		return m_pProxied->DrawText(nX, nY, nWidth, nHeight, wstrText, nAlign);
	}

	ResultCode Bitmap::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign) {
		return m_pProxied->DrawText(pRect, wstrText, nAlign);
	}

	ResultCode Bitmap::Dispose() {
		return m_pProxied->Dispose();
	}
}