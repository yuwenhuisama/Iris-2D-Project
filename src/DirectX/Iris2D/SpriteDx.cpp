#include "DirectX/Iris2D/SpriteDX.h"
#include "DirectX/Iris2D/ViewportDX.h"
#include "DirectX/Iris2D/BitmapDX.h"
#include "DirectX/Iris2D/RectDX.h"
#include "DirectX/Iris2D/ColorDX.h"
#include "DirectX/Iris2D/Shaders/SpriteVertexShader.h"
#include "DirectX/Iris2D/Shaders/SpritePixelShader.h"
#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Util/SpriteVertexDX.h"
#include "DirectX/Iris2D/GraphicsDX.h"
#include "DirectX/Util/TextureDX.h"

#include "Common/Iris2D/Viewport.h"
#include "Common/Iris2D/Bitmap.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/Sprite.h"
#include "Common/Util/ProxyConvert.h"

#include <functional>

namespace Iris2D
{
	SpriteDX * Iris2D::SpriteDX::Create(Viewport* pViewport)
	{
		auto pSprite = new SpriteDX();
		pSprite->m_pViewport = pViewport == nullptr ? ViewportDX::GetGlobalViewport() : pViewport;
		
		GetProxied<ViewportDX*>(pSprite->m_pViewport)->AddSprite(pSprite);

		return pSprite;
	}

	void Iris2D::SpriteDX::Release(SpriteDX*& pSprite)
	{
		if (!pSprite) {
			return;
		}
		GetProxied<ViewportDX*>(pSprite->m_pViewport)->RemoveSprite(pSprite);
		delete pSprite;
		pSprite = nullptr;
	}

	void SpriteDX::ForceRelease(SpriteDX * pSprite)
	{
		auto pProxy = pSprite->GetProxy();;
		Sprite::ForceRelease(pProxy);
		delete pSprite;
	}

	void SpriteDX::SetBitmap(Bitmap*& pBitmap)
	{
		if (m_pBitmap == pBitmap) {
			return;
		}

		if (!pBitmap) {
			return;
		}

		Bitmap::Release(m_pBitmap);
		GetProxied<BitmapDX*>(pBitmap)->IncreamRefCount();

		m_pBitmap =  pBitmap;
		CreateSpriteVertexBuffer();

		m_bfPixelShaderBuffer.m_f4SpriteRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	}

	Bitmap * SpriteDX::GetBitmap() const
	{
		return m_pBitmap;
	}

	void SpriteDX::SetX(float fX)
	{
		if (fX == m_fX) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fX = fX;
	}

	float SpriteDX::GetX() const
	{
		return m_fY;
	}

	void SpriteDX::SetY(float fY)
	{
		if (fY == m_fY) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fY = fY;
	}

	float SpriteDX::GetY() const
	{
		return m_fY;
	}

	void SpriteDX::SetZ(float fZ)
	{
		if (fZ == m_fZ) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fZ = fZ;
	}

	float SpriteDX::GetZ() const
	{
		return m_fZ;
	}

	void SpriteDX::SetAngle(float fAngle)
	{
		if (fAngle == m_fAngle) {
			return;
		}

		m_bAngleDirtyFlag = true;
		m_fAngle = fAngle * c_fArcUnit;
	}

	float SpriteDX::GetAngle() const
	{
		return m_fAngle;
	}

	void SpriteDX::SetZoomX(float fZoomX)
	{
		if (fZoomX == m_fZoomX) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomX = fZoomX;
	}

	float SpriteDX::GetZoomX() const
	{
		return m_fZoomX;
	}

	void SpriteDX::SetZoomY(float fZoomY)
	{
		if (fZoomY == m_fZoomY) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomY = fZoomY;
	}

	float SpriteDX::GetZoomY() const
	{
		return m_fZoomY;
	}

	void SpriteDX::SetOX(float fOX)
	{
		m_bfVertexShaderBuffer.m_f2OxOy.x = fOX;
	}

	float SpriteDX::GetOX()
	{
		return m_bfVertexShaderBuffer.m_f2OxOy.x;
	}

	void SpriteDX::SetOY(float fOY)
	{
		m_bfVertexShaderBuffer.m_f2OxOy.y = fOY;
	}

	float SpriteDX::GetOY()
	{
		return m_bfVertexShaderBuffer.m_f2OxOy.y;
	}

	void SpriteDX::SetMirror(bool bMirror)
	{
		m_bfPixelShaderBuffer.m_nMirror = (bMirror ? 1 : 0);
	}

	bool SpriteDX::GetMirror()
	{
		return m_bfPixelShaderBuffer.m_nMirror == 1;
	}

	void SpriteDX::SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}

	bool SpriteDX::GetVisible()
	{
		return m_bVisible;
	}

	void SpriteDX::SetOpacity(float fOpacity)
	{
		if (fOpacity < 0.0f) {
			fOpacity = 0.0f;
		}
		else if (fOpacity > 255.0f) {
			fOpacity = 255.0f;
		}
		m_bfPixelShaderBuffer.m_fOpacity = fOpacity / 255.0f;
	}

	float SpriteDX::GetOpacity()
	{
		return m_bfPixelShaderBuffer.m_fOpacity;;
	}

	void SpriteDX::SetSrcRect(Rect *& pSrcRect)
	{
		Rect::Release(m_pSrcRect);
		GetProxied<RectDX*>(pSrcRect)->IncreamRefCount();

		m_pSrcRect = pSrcRect;

		m_bSrcRectDirtyFlag = true;
	}

	Rect* SpriteDX::GetSrcRect() const
	{
		return m_pSrcRect;
	}

	void SpriteDX::SetTone(Tone *& pTone)
	{
		Color::Release(m_pTone);

		GetProxied<ToneDX*>(pTone)->IncreamRefCount();
		m_pTone = pTone;

		m_bToneDirtyFlag = true;
	}

	Tone * SpriteDX::GetTone() const
	{
		return m_pTone;
	}

	void SpriteDX::Update()
	{
	}

	void SpriteDX::SetEffect(Effect::EffectBase* pEffect) {
	}

	void SpriteDX::Render()
	{
		if (!m_pBitmap || !m_bVisible || m_bfPixelShaderBuffer.m_fOpacity == 0.0f) {
			return;
		}

		if (m_bPositionDirtyFlag) {
			m_bfVertexShaderBuffer.m_mxTransMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_fX, m_fY, m_fZ));
			m_bPositionDirtyFlag = false;
		}

		if (m_bAngleDirtyFlag) {
			m_bfVertexShaderBuffer.m_mxRotMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(m_fAngle));
			m_bAngleDirtyFlag = false;
		}
		
		if (m_bZoomDirtyFlag) {
			m_bfVertexShaderBuffer.m_mxZoomMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(m_fZoomX, m_fZoomY, 1.0f));
			m_bZoomDirtyFlag = false;
		}

		if (m_bToneDirtyFlag || (m_pTone && GetProxied<ToneDX*>(m_pTone)->Modified())) {
			if (m_pTone) {
				m_bfPixelShaderBuffer.m_f4Tone = { static_cast<float>(m_pTone->GetRed()), static_cast<float>(m_pTone->GetBlue()), static_cast<float>(m_pTone->GetGreen()), static_cast<float>(m_pTone->GetAlpha()) };
			}
			else {
				m_bfPixelShaderBuffer.m_f4Tone = { 0.0f, 0.0f, 0.0f, 0.0f };
			}

			m_bToneDirtyFlag = false;

			if (m_pTone) {
				GetProxied<ToneDX*>(m_pTone)->ModifyDone();
			}
		}

		static auto fAdjust = [](float& fData) -> void { 
			if (fData < 0.0f) {
				fData = 0.0f;
			}
			else if (fData > 1.0f) {
				fData = 1.0f;
			}
		};

		if (m_bSrcRectDirtyFlag || (m_pSrcRect && GetProxied<RectDX*>(m_pSrcRect)->Modified())) {
			if (m_pSrcRect) {
				auto left = m_pSrcRect->GetLeft();
				auto top = m_pSrcRect->GetTop();
				auto right = m_pSrcRect->GetRight();
				auto bottom = m_pSrcRect->GetBottom();

				m_bfPixelShaderBuffer.m_f4SpriteRect = {
					m_pSrcRect->GetLeft() / m_pBitmap->GetWidth(),
					m_pSrcRect->GetTop() / m_pBitmap->GetHeight(),
					m_pSrcRect->GetRight() / m_pBitmap->GetWidth(),
					m_pSrcRect->GetBottom() / m_pBitmap->GetHeight() };

				fAdjust(m_bfPixelShaderBuffer.m_f4SpriteRect.x);
				fAdjust(m_bfPixelShaderBuffer.m_f4SpriteRect.y);
				fAdjust(m_bfPixelShaderBuffer.m_f4SpriteRect.z);
				fAdjust(m_bfPixelShaderBuffer.m_f4SpriteRect.w);
			}
			else {
				m_bfPixelShaderBuffer.m_f4SpriteRect = { 0.0f, 0.0f, 1.0f, 1.0f };
			}

			m_bSrcRectDirtyFlag = false;

			if (m_pSrcRect) {
				GetProxied<RectDX*>(m_pSrcRect)->ModifyDone();
			}
		}

		auto pD3DManager = D3DResourceManager::Instance();
		auto pVertexShader = SpriteVertexShader::Instance();
		auto pPixelShader = SpritePixelShader::Instance();

		auto pContex = pD3DManager->GetD3DDeviceContext();
		
		unsigned int nStride = sizeof(SpriteVertex);
		unsigned int nOffset = 0;

		pVertexShader->SetWorldMatrix(m_bfVertexShaderBuffer);
		pPixelShader->SetColorProcessInfo(m_bfPixelShaderBuffer);

		pD3DManager->SetCurrentVertexBufferInfo(nStride, nOffset, m_pVertexBuffer);
		pD3DManager->SetCurrentTexture(GetProxied<BitmapDX*>(m_pBitmap)->GetTexture());

		pContex->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
		pContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		auto pTexture = GetProxied<BitmapDX*>(m_pBitmap)->GetTexture();

		pTexture->AquireSyncFromDx11Side();

		auto pShaderResource = pTexture->GetShaderResourceView();
		auto pShaderSampler = pTexture->GetDefaultSamplerState();

		pContex->PSSetShaderResources(0, 1, &pShaderResource);
		pContex->PSSetSamplers(0, 1, &pShaderSampler);

		//DirectX::ScratchImage image;
		//DirectX::CaptureTexture(D3DResourceManager::Instance()->GetD3D11Device(), D3DResourceManager::Instance()->GetD3DDeviceContext(), m_pBitmap->GetTexture()->GetTexture(), image);
		//DirectX::SaveToWICFile(*image.GetImages(), DirectX::WIC_FLAGS_NONE, GUID_ContainerFormatPng, L"te.png", &GUID_WICPixelFormat32bppBGRA);

		pContex->Draw(6, 0);

		pTexture->ReleaseSyncFromDx11Side();

	}

	bool SpriteDX::Dispose()
	{
		Bitmap::Release(m_pBitmap);
		Rect::Release(m_pSrcRect);
		Color::Release(m_pTone);

		SafeCOMRelease(m_pVertexBuffer);

		return true;
	}

	Iris2D::SpriteDX::~SpriteDX()
	{
		Dispose();
	}

	bool SpriteDX::CreateSpriteVertexBuffer()
	{
		if (!m_pBitmap) {
			return false;
		}

		SafeCOMRelease(m_pVertexBuffer);

		auto nWidth = m_pBitmap->GetWidth();
		auto nHeight = m_pBitmap->GetHeight();

		SpriteVertex arrVertices[] = {
			{ XMFLOAT4(static_cast<float>(nWidth), 0.0f,						1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT4(static_cast<float>(nWidth), static_cast<float>(nHeight), 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT4(0.0f,					   static_cast<float>(nHeight), 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

			{ XMFLOAT4(0.0f,					   static_cast<float>(nHeight), 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT4(0.0f,					   0.0f,						1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT4(static_cast<float>(nWidth), 0.0f,						1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		};

		D3D11_BUFFER_DESC dbdVertextDesc;
		memset(&dbdVertextDesc, 0, sizeof(D3D11_BUFFER_DESC));

		dbdVertextDesc.Usage = D3D11_USAGE_DEFAULT;
		dbdVertextDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		dbdVertextDesc.ByteWidth = sizeof(SpriteVertex) * 6;

		D3D11_SUBRESOURCE_DATA dsdResourceData;
		memset(&dsdResourceData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
		dsdResourceData.pSysMem = arrVertices;

		auto pD3DManager = D3DResourceManager::Instance();
		auto hResult = pD3DManager->GetD3D11Device()->CreateBuffer(&dbdVertextDesc, &dsdResourceData, &m_pVertexBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pVertexBuffer);
			return false;
		}

		return true;
	}

}