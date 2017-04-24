#include "Iris2D/IrisBitmap.h"
#include "Iris2D/IrisRect.h"
#include "Iris2D/IrisColor.h"
#include "Iris2D Util/IrisTexture.h"
#include "Iris2D/IrisD3DResourceManager.h"
#include "Iris2D/IrisD2DResourceManager.h"
#include "Iris2D Util/IrisDataConvertHelper.h"


namespace Iris2D
{
	IrisBitmap * IrisBitmap::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new IrisBitmap();

		pBitmap->m_pTexture = IrisTexture::Create(wstrFileName);
		if (!pBitmap->m_pTexture) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	IrisBitmap * IrisBitmap::Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new IrisBitmap();

		pBitmap->m_pTexture = IrisTexture::Create(nWidth, nHeight);
		if (pBitmap->m_pTexture == nullptr) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	void IrisBitmap::Release(IrisBitmap *& pBitmap)
	{
		if (!pBitmap) {
			return;
		}
		delete pBitmap;
		pBitmap = nullptr;
	}

	bool IrisBitmap::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, IrisColor * pColor, IR_PARAM_RESULT_CT)
	{
		auto pDestRenderTarget = m_pTexture->GetRenderTargetBitmap();

		// Draw
		m_pTexture->AquireSyncFromDx10Side();
		pDestRenderTarget->BeginDraw();

		auto&& cfColorF = IrisDataConvertHelper::ConvertToD2DColor(pColor);

		ID2D1SolidColorBrush* pBrush = nullptr;
		auto hResult = pDestRenderTarget->CreateSolidColorBrush(cfColorF, &pBrush);
		if (FAILED(hResult)) {
			SafeCOMRelease(pBrush);
			m_pTexture->ReleaseSyncFromDx10Side();
			return false;
		}

		pDestRenderTarget->FillRectangle(D2D1::RectF(nX, nY, nX + nWidth, nY + nHeight), pBrush);

		hResult = pDestRenderTarget->EndDraw();
		SafeCOMRelease(pBrush);

		if (FAILED(hResult)) {
			return false;
		}

		m_pTexture->ReleaseSyncFromDx10Side();

		return true;
	}

	bool IrisBitmap::FillRect(IrisRect * pRect, IrisColor * pColor, IR_PARAM_RESULT_CT)
	{
		return FillRect(pRect->GetX(), pRect->GetY(), pRect->GetWidth(), pRect->GetHeight(), pColor, IR_PARAM);
	}

	bool IrisBitmap::Clear(IR_PARAM_RESULT_CT)
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

	bool IrisBitmap::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pClearColor = IrisColor::Create(0, 0, 0, 0);
		auto bResult = FillRect(nX, nY, nWidth, nHeight, pClearColor);
		IrisColor::Release(pClearColor);
		return bResult;
	}

	bool IrisBitmap::ClearRect(IrisRect * pRect, IR_PARAM_RESULT_CT)
	{
		auto pClearColor = IrisColor::Create(0, 0, 0, 0);
		auto bResult = FillRect(pRect, pClearColor);
		IrisColor::Release(pClearColor);
		return bResult;
	}

	IrisColor* IrisBitmap::GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT_CT)
	{
		// Capture Texture
		auto pSrcD3DResource = m_pTexture->GetTexture();
		DirectX::ScratchImage siImage;
		m_pTexture->AquireSyncFromDx11Side();
		DirectX::CaptureTexture(IrisD3DResourceManager::Instance()->GetD3D11Device(), IrisD3DResourceManager::Instance()->GetD3DDeviceContext(), pSrcD3DResource, siImage);
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

		return IrisColor::Create(uRGBA.m_stRGBA.m_cRed, uRGBA.m_stRGBA.m_cGreen, uRGBA.m_stRGBA.m_cBlue, uRGBA.m_stRGBA.m_cAlpha);

	}

	bool IrisBitmap::SetPixel(unsigned int nX, unsigned int nY, IrisColor * pColor, IR_PARAM_RESULT_CT)
	{
		return FillRect(nX, nY, nX + 1, nY + 1, pColor, IR_PARAM);
	}

	bool IrisBitmap::SaveToFile(const std::wstring& wstrFilePath)
	{
		m_pTexture->AquireSyncFromDx11Side();
		DirectX::ScratchImage image;
		auto hResult = DirectX::CaptureTexture(IrisD3DResourceManager::Instance()->GetD3D11Device(), IrisD3DResourceManager::Instance()->GetD3DDeviceContext(), m_pTexture->GetTexture(), image);
		if (FAILED(hResult)) {
			return false;
		}

		hResult = DirectX::SaveToWICFile(*image.GetImages(), DirectX::WIC_FLAGS_NONE, GUID_ContainerFormatPng, wstrFilePath.c_str(), &GUID_WICPixelFormat32bppBGRA);
		if (FAILED(hResult)) {
			return false;
		}

		m_pTexture->ReleaseSyncFromDx11Side();
	}

	bool IrisBitmap::HueChange(float fHue, IR_PARAM_RESULT_CT)
	{
		ID2D1Effect* pEffectRgbToHue = nullptr;
		auto pRenderTarget = m_pTexture->GetRenderTargetBitmap();
		//pRenderTarget->CreteaEffect()
		//IrisD2DResourceManager::Instance()->GetD2DFactory()

		return true;
	}

	IrisTexture * IrisBitmap::GetTexture()
	{
		return m_pTexture;
	}

	unsigned int IrisBitmap::GetWidth()
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().width);
	}

	unsigned int IrisBitmap::GetHeight()
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().height);
	}

	bool IrisBitmap::Blt(unsigned int nDestX, unsigned int nDestY, IrisBitmap * pSrcBitmap, IrisRect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT)
	{
		auto pDestSrc = IrisRect::Create(nDestX, nDestY, pSrcRect->GetWidth(), pSrcRect->GetHeight());
		auto bResult = StretchBlt(pDestSrc, pSrcBitmap, pSrcRect, fOpacity, IR_PARAM);
		IrisRect::Release(pDestSrc);

		return bResult;
	}

	bool IrisBitmap::StretchBlt(IrisRect * pDestRect, IrisBitmap * pSrcBitmap, IrisRect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT)
	{
		if (fOpacity < 0.0f) {
			fOpacity = 0.0f;
		}
		else if (fOpacity > 255.0f) {
			fOpacity = 255.0f;
		}

		auto pSrcTexture = pSrcBitmap->GetTexture();
		auto pDestRenderTarget = m_pTexture->GetRenderTargetBitmap();

		// Capture Texture
		auto pSrcD3DResource = pSrcTexture->GetTexture();
		DirectX::ScratchImage siImage;
		pSrcTexture->AquireSyncFromDx11Side();
		DirectX::CaptureTexture(IrisD3DResourceManager::Instance()->GetD3D11Device(), IrisD3DResourceManager::Instance()->GetD3DDeviceContext(), pSrcD3DResource, siImage);
		pSrcTexture->ReleaseSyncFromDx11Side();

		auto pImage = siImage.GetImages();
		// Create Bitmap
		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		IrisD2DResourceManager::Instance()->GetD2DFactory()->GetDesktopDpi(&fDpiX, &fDpiY);

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

	IrisBitmap::~IrisBitmap()
	{
		if (m_pTexture) {
			IrisTexture::Release(m_pTexture);
		}
	}
}