#include "Iris2D/IrisBitmap.h"
#include "Iris2D/IrisRect.h"
#include "Iris2D Util/IrisTexture.h"
#include "Iris2D/IrisD3DResourceManager.h"
#include "Iris2D/IrisD2DResourceManager.h"


namespace Iris2D
{
	IrisBitmap * IrisBitmap::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new IrisBitmap();

		pBitmap->m_pTexture = IrisTexture::Create(wstrFileName);
		if (pBitmap->m_pTexture == nullptr) {
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