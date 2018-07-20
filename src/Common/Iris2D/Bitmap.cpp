#include "Common/Iris2D/Bitmap.h"
#include "Common/Iris2D/AppFactory.h"

#ifdef _WIN32
#include "DirectX/Iris2D/BitmapDX.h"
#endif // _WIN32


namespace Iris2D {
	Bitmap::Bitmap(IBitmap* pBitmap) : Proxy(pBitmap) {}

	Bitmap * Bitmap::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(wstrFileName, IR_PARAM);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(nWidth, nHeight, IR_PARAM);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::Create(Bitmap * pSrcBitmap, IR_PARAM_RESULT_CT) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::Create(pSrcBitmap, IR_PARAM);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}
		return pBitmap;
	}

	Bitmap * Bitmap::CopyFrom(Bitmap * pSrcBitmap, IR_PARAM_RESULT_CT) {
		Bitmap* pBitmap = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = BitmapDX::CopyFrom(pSrcBitmap, IR_PARAM);
			pBitmap = new Bitmap(pTmp);
			pTmp->SetProxy(pBitmap);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
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

	bool Bitmap::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT) {
		return m_pProxied->Blt(nDestX, nDestY, pSrcBitmap, pSrcRect, fOpacity, IR_PARAM);
	}

	bool Bitmap::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT) {
		return m_pProxied->StretchBlt(pDestRect, pSrcBitmap, pSrcRect, fOpacity, IR_PARAM);
	}

	bool Bitmap::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor, IR_PARAM_RESULT_CT) {
		return m_pProxied->FillRect(nX, nY, nWidth, nHeight, pColor, IR_PARAM);
	}

	bool Bitmap::FillRect(const Rect * pRect, const Color * pColor, IR_PARAM_RESULT_CT) {
		return m_pProxied->FillRect(pRect, pColor, IR_PARAM);
	}

	bool Bitmap::Clear(IR_PARAM_RESULT_CT) {
		return m_pProxied->Clear(IR_PARAM);
	}

	bool Bitmap::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		return m_pProxied->ClearRect(nX, nY, nWidth, nHeight, IR_PARAM);
	}

	bool Bitmap::ClearRect(const Rect * pRect, IR_PARAM_RESULT_CT) {
		return m_pProxied->ClearRect(pRect, IR_PARAM);
	}

	Color * Bitmap::GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT_CT) const {
		return m_pProxied->GetPixel(nX, nY, IR_PARAM);
	}

	bool Bitmap::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor, IR_PARAM_RESULT_CT) {
		return m_pProxied->SetPixel(nX, nY, pColor, IR_PARAM);
	}

	bool Bitmap::SaveToFile(const std::wstring & wstrFilePath) {
		return m_pProxied->SaveToFile(wstrFilePath);
	}

	bool Bitmap::HueChange(float fHue, IR_PARAM_RESULT_CT) {
		return m_pProxied->HueChange(fHue, IR_PARAM);
	}

	void Bitmap::SetFont(Font *& pFont) {
		m_pProxied->SetFont(pFont);
	}

	Font * Bitmap::GetFont() const {
		return m_pProxied->GetFont();
	}

	unsigned int Bitmap::TextSize(const Font * pFont, const std::wstring & wstrText, IR_PARAM_RESULT_CT) {
		return m_pProxied->TextSize(pFont, wstrText, IR_PARAM);
	}

	bool Bitmap::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT_CT) {
		return m_pProxied->DrawText(nX, nY, nWidth, nHeight, wstrText, nAlign, IR_PARAM);
	}

	bool Bitmap::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT_CT) {
		return m_pProxied->DrawText(pRect, wstrText, nAlign, IR_PARAM);
	}

	bool Bitmap::Dispose() {
		return m_pProxied->Dispose();
	}
}