#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/Font.h"
#include "Common/Iris2D/Bitmap.h"

#include "DirectX/Common.h"
#include "DirectX/Iris2D/BitmapDX.h"
#include "DirectX/Iris2D/ColorDX.h"
#include "DirectX/Iris2D/FontDX.h"

#include "DirectX/Util/TextureDX.h"
#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Iris2D/D2DResourceManager.h"
#include "DirectX/Util/DataConvertHelperDX.h"
#include <limits>

#include "Common/Util/ProxyConvert.h"

#undef max
#undef DrawText

namespace Iris2D
{
	BitmapDX * BitmapDX::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new BitmapDX();
		pBitmap->IncreamRefCount();

		pBitmap->m_pTexture = TextureDX::Create(wstrFileName);
		if (!pBitmap->m_pTexture) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	BitmapDX * BitmapDX::Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new BitmapDX();
		pBitmap->IncreamRefCount();

		pBitmap->m_pTexture = TextureDX::Create(nWidth, nHeight);
		if (pBitmap->m_pTexture == nullptr) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	BitmapDX * BitmapDX::Create(Bitmap * pSrcBitmap, IR_PARAM_RESULT_CT)
	{
		auto pNewBitmap = BitmapDX::Create(pSrcBitmap->GetWidth(), pSrcBitmap->GetHeight(), IR_PARAM);
		auto pArea = Rect::Create(0.0f, 0.0f, static_cast<float>(pSrcBitmap->GetWidth()), static_cast<float>(pSrcBitmap->GetHeight()));
		pNewBitmap->IncreamRefCount();

		pNewBitmap->Blt(0, 0, pSrcBitmap, pArea, 255.0f, IR_PARAM);

		Rect::Release(pArea);

		return pNewBitmap;
	}

	BitmapDX * BitmapDX::CopyFrom(Bitmap * pSrcBitmap, IR_PARAM_RESULT_CT) {
		return BitmapDX::Create(pSrcBitmap, IR_PARAM);
	}

	void BitmapDX::Release(BitmapDX *& pBitmap)
	{
		if (!pBitmap) {
			return;
		}

		pBitmap->DecreamRefCount();
		if (pBitmap->GetRefCount() == 0) {
			delete pBitmap;
			pBitmap = nullptr;
		}
	}

	bool BitmapDX::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor, IR_PARAM_RESULT_CT)
	{
		auto pDestRenderTarget = m_pTexture->GetRenderTargetBitmap();

		// Draw
		m_pTexture->AquireSyncFromDx10Side();
		pDestRenderTarget->BeginDraw();

		auto&& cfColorF = DataConvertHelperDX::ConvertToD2DColor(GetProxied<ColorDX*>(pColor));

		ID2D1SolidColorBrush* pBrush = nullptr;
		auto hResult = pDestRenderTarget->CreateSolidColorBrush(cfColorF, &pBrush);
		if (FAILED(hResult)) {
			SafeCOMRelease(pBrush);
			m_pTexture->ReleaseSyncFromDx10Side();
			return false;
		}

		pDestRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nX + nWidth), static_cast<float>(nY + nHeight)), pBrush);

		hResult = pDestRenderTarget->EndDraw();
		SafeCOMRelease(pBrush);

		if (FAILED(hResult)) {
			return false;
		}

		m_pTexture->ReleaseSyncFromDx10Side();

		return true;
	}

	bool BitmapDX::FillRect(const Rect * pRect, const Color * pColor, IR_PARAM_RESULT_CT)
	{
		return FillRect(static_cast<unsigned int>(pRect->GetX()), 
			static_cast<unsigned int>(pRect->GetY()),
			static_cast<unsigned int>(pRect->GetWidth()),
			static_cast<unsigned int>(pRect->GetHeight()),
			pColor, IR_PARAM);
	}

	bool BitmapDX::Clear(IR_PARAM_RESULT_CT)
	{
		auto pDestRenderTarget = m_pTexture->GetRenderTargetBitmap();

		// Draw
		m_pTexture->AquireSyncFromDx10Side();
		pDestRenderTarget->BeginDraw();

		pDestRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black, 0.0f));

	 	auto hResult = pDestRenderTarget->EndDraw();
		m_pTexture->ReleaseSyncFromDx10Side();

		if (FAILED(hResult)) {
			return false;
		}

		return true;
	}

	bool BitmapDX::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pClearColor = Color::Create(0, 0, 0, 0);
		auto bResult = FillRect(nX, nY, nWidth, nHeight, pClearColor);
		Color::Release(pClearColor);
		return bResult;
	}

	bool BitmapDX::ClearRect(const Rect * pRect, IR_PARAM_RESULT_CT)
	{
		auto pClearColor = Color::Create(0, 0, 0, 0);
		auto bResult = FillRect(pRect, pClearColor);
		Color::Release(pClearColor);
		return bResult;
	}

	Color* BitmapDX::GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT_CT) const
	{
		// Capture Texture
		auto pSrcD3DResource = m_pTexture->GetTexture();
		DirectX::ScratchImage siImage;
		m_pTexture->AquireSyncFromDx11Side();
		DirectX::CaptureTexture(D3DResourceManager::Instance()->GetD3D11Device(), D3DResourceManager::Instance()->GetD3DDeviceContext(), pSrcD3DResource, siImage);
		m_pTexture->ReleaseSyncFromDx11Side();	

		auto pImage = siImage.GetImages();
		if (nX < 0 || nX > pImage->width
			|| nY < 0 || nY > pImage->height) {
			return nullptr;
		}

		auto pRawData = pImage->pixels;
		auto nPitch = pImage->rowPitch;

		union {
			unsigned int m_nData;
			// ARGB
			struct {
				unsigned char m_cBlue;
				unsigned char m_cGreen;
				unsigned char m_cRed;
				unsigned char m_cAlpha;
			} m_stRGBA;
		} uRGBA;

		uRGBA.m_nData = *reinterpret_cast<unsigned int*>(pRawData + nPitch * nY + nX * sizeof(uRGBA));

		return Color::Create(uRGBA.m_stRGBA.m_cRed, uRGBA.m_stRGBA.m_cGreen, uRGBA.m_stRGBA.m_cBlue, uRGBA.m_stRGBA.m_cAlpha);

	}

	bool BitmapDX::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor, IR_PARAM_RESULT_CT)
	{
		return FillRect(nX, nY, nX + 1, nY + 1, pColor, IR_PARAM);
	}

	bool BitmapDX::SaveToFile(const std::wstring& wstrFilePath)
	{
		return m_pTexture->SaveToFile(wstrFilePath); 
	}

	bool BitmapDX::HueChange(float fHue, IR_PARAM_RESULT_CT)
	{
		// Copy a bitmap
		auto pTmpBitmap = BitmapDX::Create(GetProxy());
		auto pTmpTexture = pTmpBitmap->GetTexture();

		ID2D1Effect* pEffectHueRotate = nullptr;
		auto pRenderTarget = m_pTexture->GetRenderTargetBitmap();
		auto pSurface = m_pTexture->GetDxgiSurface();

		auto pD2DContext = D2DResourceManager::Instance()->GetD2DDeviceContext();
		auto pD2DFactory = D2DResourceManager::Instance()->GetD2DFactory();

		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		pD2DFactory->GetDesktopDpi(&fDpiX, &fDpiY);

		D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			fDpiX,
			fDpiY
		);

		m_pTexture->AquireSyncFromDx11Side();
		pTmpTexture->AquireSyncFromDx11Side();
		ID2D1Bitmap1* pBitmap = nullptr;
		ID2D1Bitmap1* pBitmap2 = nullptr;
		auto hResult = pD2DContext->CreateBitmapFromDxgiSurface(pSurface, &bitmapProperties, &pBitmap);
		SafeCOMRelease(pSurface);
		if (FAILED(hResult)) {
			SafeCOMRelease(pBitmap);
			BitmapDX::Release(pTmpBitmap);
			return false;
		}

		auto pTmpSurface = pTmpTexture->GetDxgiSurface();
		hResult = pD2DContext->CreateBitmapFromDxgiSurface(pTmpSurface, &bitmapProperties, &pBitmap2);
		SafeCOMRelease(pTmpSurface);
		
		if (FAILED(hResult)) {
			SafeCOMRelease(pBitmap);
			BitmapDX::Release(pTmpBitmap);
			return false;
		}

		hResult = pD2DContext->CreateEffect(CLSID_D2D1HueRotation, &pEffectHueRotate);
		if (FAILED(hResult)) {
			SafeCOMRelease(pBitmap);
			SafeCOMRelease(pEffectHueRotate);
			BitmapDX::Release(pTmpBitmap);
			return false;
		}

		pEffectHueRotate->SetInput(0, pBitmap2);
		pEffectHueRotate->SetValue(D2D1_HUEROTATION_PROP_ANGLE, fHue);
		
		pD2DContext->SetTarget(pBitmap);
		pD2DContext->BeginDraw();
		pD2DContext->DrawImage(pEffectHueRotate);

		hResult = pD2DContext->EndDraw();

		pTmpTexture->ReleaseSyncFromDx11Side();
		m_pTexture->ReleaseSyncFromDx11Side();

		if (FAILED(pTmpTexture)) {
			SafeCOMRelease(pBitmap);
			SafeCOMRelease(pBitmap2);
			SafeCOMRelease(pEffectHueRotate);
			BitmapDX::Release(pTmpBitmap);
			return false;
		}

		SafeCOMRelease(pBitmap);
		SafeCOMRelease(pBitmap2);
		SafeCOMRelease(pEffectHueRotate);
		BitmapDX::Release(pTmpBitmap);

		return true;
	}

	void BitmapDX::SetFont(Font *& pFont)
	{
		Font::Release(m_pFont);

		GetProxied<FontDX*>(pFont)->IncreamRefCount();

		m_pFont = pFont;
	}

	Font * BitmapDX::GetFont() const
	{
		return m_pFont;
	}

	unsigned int BitmapDX::TextSize(const Font * pFont, const std::wstring & wstrText, IR_PARAM_RESULT_CT)
	{
		auto pTextFormat = CreateTextFormat(GetProxied<FontDX*>(pFont));
		auto pDWriteFactory = D2DResourceManager::Instance()->GetDWriteFactory();

		IDWriteTextLayout* pLayout = nullptr;
		HRESULT hResult = S_OK;
		if (pTextFormat) {
			hResult = pDWriteFactory->CreateTextLayout(wstrText.c_str(), wstrText.size(), pTextFormat, std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), &pLayout);
		}

		DWRITE_TEXT_METRICS dtmTemp;
		if (SUCCEEDED(hResult)) {
			pLayout->GetMetrics(&dtmTemp);
		}
		
		SafeCOMRelease(pTextFormat);
		SafeCOMRelease(pLayout);

		return static_cast<unsigned int>(ceil(dtmTemp.widthIncludingTrailingWhitespace));
	}

	bool BitmapDX::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT_CT)
	{
		auto pTextFormat = CreateTextFormat(GetProxied<FontDX*>(m_pFont));
		auto pDWriteFactory = D2DResourceManager::Instance()->GetDWriteFactory();
		auto pRenderTarget = m_pTexture->GetRenderTargetBitmap();

		HRESULT hResult = S_OK;
		if (pTextFormat) {

			switch (nAlign)
			{
			case AlignType::Left:
				pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case AlignType::Center:
				pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case AlignType::Right:
				pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			default:
				break;
			}
			
			m_pTexture->AquireSyncFromDx10Side();

			pRenderTarget->BeginDraw();

			auto pColor = m_pFont
				? m_pFont->GetColor() ? m_pFont->GetColor() : Font::GetDefaultColor()
				: Font::GetDefaultColor();

			ID2D1SolidColorBrush* pBrush = nullptr;
			hResult =  pRenderTarget->CreateSolidColorBrush(DataConvertHelperDX::ConvertToD2DColor(GetProxied<ColorDX*>(pColor)), &pBrush);
			
			IDWriteTextLayout* pLayout = nullptr;
			if (SUCCEEDED(hResult)) {
				pRenderTarget->DrawTextA(wstrText.c_str(),
					wstrText.size(),
					pTextFormat,
					D2D1::RectF(nX, nY, nX + nWidth, nX + nHeight),
					pBrush,
					D2D1_DRAW_TEXT_OPTIONS_NONE,
					DWRITE_MEASURING_MODE_NATURAL
				);

				if (m_pFont ? m_pFont->GetShadow() : FontDX::GetDefaultShadow()) {
					ID2D1SolidColorBrush* pShadowBrush = nullptr;
					hResult = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 1.0f), &pShadowBrush);

					if (SUCCEEDED(hResult)) {
						pRenderTarget->DrawTextA(wstrText.c_str(),
							wstrText.size(),
							pTextFormat,
							D2D1::RectF(nX + 2.0f, nY + 2.0f, nX + nWidth, nX + nHeight),
							pBrush,
							D2D1_DRAW_TEXT_OPTIONS_NONE,
							DWRITE_MEASURING_MODE_NATURAL
						);
					}

					SafeCOMRelease(pShadowBrush);
				}

			}
			
			SafeCOMRelease(pBrush);
			SafeCOMRelease(pLayout);

			hResult = pRenderTarget->EndDraw();

			m_pTexture->ReleaseSyncFromDx10Side();
		}

		SafeCOMRelease(pTextFormat);

		return SUCCEEDED(hResult) ? true : false;
	}

	bool BitmapDX::DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT_CT)
	{
		return DrawText(static_cast<float>(pRect->GetX()), static_cast<float>(pRect->GetY()), static_cast<float>(pRect->GetWidth()), static_cast<float>(pRect->GetHeight()), wstrText, nAlign, IR_PARAM);
	}

	bool BitmapDX::Dispose()
	{
		TextureDX::Release(m_pTexture);
		Font::Release(m_pFont);
		return true;
	}

	TextureDX * BitmapDX::GetTexture() const
	{
		return m_pTexture;
	}

	IDWriteTextFormat * BitmapDX::CreateTextFormat(const FontDX * pFont)
	{
		IDWriteTextFormat* pTextFormat = nullptr;

		auto pDWriteFactory = D2DResourceManager::Instance()->GetDWriteFactory();

		std::wstring wstrFontName;
		DWRITE_FONT_WEIGHT dfwWeight;
		DWRITE_FONT_STYLE dfsStyle;
		unsigned int nSize;

		if (pFont) {
			wstrFontName = pFont->GetName();
			dfwWeight = pFont->GetBold() ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL;
			dfsStyle = pFont->GetItalic() ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
			nSize = pFont->GetSize();
		}
		else {
			wstrFontName = FontDX::GetDefaultName();
			dfwWeight = FontDX::GetDefaultBold() ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL;
			dfsStyle = FontDX::GetDefaultItalic() ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
			nSize = FontDX::GetDefaultSize();
		}

		auto hResult = pDWriteFactory->CreateTextFormat(
			wstrFontName.c_str(),
			nullptr,
			dfwWeight,
			dfsStyle,
			DWRITE_FONT_STRETCH_CONDENSED,
			static_cast<float>(nSize),
			L"zh-cn",
			&pTextFormat
		);

		if (FAILED(hResult)) {
			SafeCOMRelease(pTextFormat);
		}

		return pTextFormat;
	}

	unsigned int BitmapDX::GetWidth() const
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().width);
	}

	unsigned int BitmapDX::GetHeight() const
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().height);
	}

	bool BitmapDX::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT)
	{
		auto pDestSrc = Rect::Create(static_cast<float>(nDestX), static_cast<float>(nDestY), static_cast<float>(pSrcRect->GetWidth()), static_cast<float>(pSrcRect->GetHeight()));
		auto bResult = StretchBlt(pDestSrc, pSrcBitmap, pSrcRect, fOpacity, IR_PARAM);
		Rect::Release(pDestSrc);

		return bResult;
	}

	bool BitmapDX::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT)
	{
		if (fOpacity < 0.0f) {
			fOpacity = 0.0f;
		}
		else if (fOpacity > 255.0f) {
			fOpacity = 255.0f;
		}

		auto pSrcTexture = GetProxied<BitmapDX*>(pSrcBitmap)->GetTexture();
		auto pDestRenderTarget = m_pTexture->GetRenderTargetBitmap();

		// Capture Texture
		auto pSrcD3DResource = pSrcTexture->GetTexture();
		DirectX::ScratchImage siImage;
		pSrcTexture->AquireSyncFromDx11Side();
		DirectX::CaptureTexture(D3DResourceManager::Instance()->GetD3D11Device(), D3DResourceManager::Instance()->GetD3DDeviceContext(), pSrcD3DResource, siImage);
		pSrcTexture->ReleaseSyncFromDx11Side();

		auto pImage = siImage.GetImages();
		// Create Bitmap
		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		D2DResourceManager::Instance()->GetD2DFactory()->GetDesktopDpi(&fDpiX, &fDpiY);

		D2D1_BITMAP_PROPERTIES dbpProperties;
		dbpProperties.dpiX = fDpiX;
		dbpProperties.dpiY = fDpiY;
		dbpProperties.pixelFormat.format = pImage->format;
		dbpProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

		ID2D1Bitmap* pDestBitmap = nullptr;
		unsigned int nSrcWidth = pImage->width;
		unsigned int nSrcHeight = pImage->height;
		D2D1_SIZE_U dsuSize = { nSrcWidth, nSrcHeight };
		auto hResult = pDestRenderTarget->CreateBitmap(dsuSize, pImage->pixels, pImage->rowPitch, dbpProperties, &pDestBitmap);
		if (FAILED(hResult)) {
			SafeCOMRelease(pDestBitmap);
			return false;
		}

		// Draw
		m_pTexture->AquireSyncFromDx10Side();
		pDestRenderTarget->BeginDraw();
		pDestRenderTarget->DrawBitmap(
			pDestBitmap,
			D2D1::RectF(pDestRect->GetLeft(), pDestRect->GetTop(), pDestRect->GetRight(), pDestRect->GetBottom()),
			fOpacity / 255.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(pSrcRect->GetLeft(), pSrcRect->GetTop(), pSrcRect->GetRight(), pSrcRect->GetBottom())
		);

		hResult = pDestRenderTarget->EndDraw();
		m_pTexture->ReleaseSyncFromDx10Side();

		SafeCOMRelease(pDestBitmap);
		if (FAILED(hResult)) {
			return false;
		}
		return true;
	}

	BitmapDX::~BitmapDX()
	{
		Dispose();
	}
}