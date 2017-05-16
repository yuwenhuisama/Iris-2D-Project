#include "Iris2D/IrisSprite.h"
#include "Iris2D/IrisViewport.h"
#include "Iris2D/IrisBitmap.h"
#include "Iris2D/IrisRect.h"
#include "Iris2D/IrisColor.h"
#include "Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "Iris2D/IrisShaders/IrisSpritePixelShader.h"
#include "Iris2D/IrisD3DResourceManager.h"
#include "Iris2D Util/IrisSpriteVertex.h"
#include "Iris2D/IrisGraphics.h"
#include "Iris2D Util/IrisTexture.h"
#include <functional>

namespace Iris2D
{
	IrisSprite * Iris2D::IrisSprite::Create(IrisViewport* pViewport)
	{
		auto pSprite = new IrisSprite();
		pSprite->m_pViewport = pViewport == nullptr ? IrisViewport::GetGlobalViewport() : pViewport;
		pSprite->m_pViewport->AddSprite(pSprite);;

		return pSprite;
	}

	void Iris2D::IrisSprite::Release(IrisSprite*& pSprite)
	{
		if (!pSprite) {
			return;
		}
		pSprite->m_pViewport->RemoveSprite(pSprite);
		InnerRelease(pSprite);
		pSprite = nullptr;
	}

	void IrisSprite::InnerRelease(IrisSprite * pSprite)
	{
		delete pSprite;
	}

	void IrisSprite::SetBitmap(IrisBitmap*& pBitmap)
	{
		if (m_pBitmap == pBitmap) {
			return;
		}

		IrisBitmap::Release(m_pBitmap);
		pBitmap->IncreamRefCount();

		m_pBitmap =  pBitmap;
		CreateSpriteVertexBuffer();

		m_bfPixelShaderBuffer.m_f4SpriteRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	}

	IrisBitmap * IrisSprite::GetBitmap() const
	{
		return m_pBitmap;
	}

	void IrisSprite::SetX(float fX)
	{
		if (fX == m_fX) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fX = fX;
	}

	float IrisSprite::GetX() const
	{
		return m_fY;
	}

	void IrisSprite::SetY(float fY)
	{
		if (fY == m_fY) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fY = fY;
	}

	float IrisSprite::GetY() const
	{
		return m_fY;
	}

	void IrisSprite::SetZ(float fZ)
	{
		if (fZ == m_fZ) {
			return;
		}

		m_bPositionDirtyFlag = true;
		m_fZ = fZ;
	}

	float IrisSprite::GetZ() const
	{
		return m_fZ;
	}

	void IrisSprite::SetAngle(float fAngle)
	{
		if (fAngle == m_fAngle) {
			return;
		}

		m_bAngleDirtyFlag = true;
		m_fAngle = fAngle * c_fArcUnit;
	}

	float IrisSprite::GetAngle() const
	{
		return m_fAngle;
	}

	void IrisSprite::SetZoomX(float fZoomX)
	{
		if (fZoomX == m_fZoomX) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomX = fZoomX;
	}

	float IrisSprite::GetZoomX() const
	{
		return m_fZoomX;
	}

	void IrisSprite::SetZoomY(float fZoomY)
	{
		if (fZoomY == m_fZoomY) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomY = fZoomY;
	}

	float IrisSprite::GetZoomY() const
	{
		return m_fZoomY;
	}

	void IrisSprite::SetOX(float fOX)
	{
		m_bfVertexShaderBuffer.m_f2OxOy.x = fOX;
	}

	float IrisSprite::GetOX()
	{
		return m_bfVertexShaderBuffer.m_f2OxOy.x;
	}

	void IrisSprite::SetOY(float fOY)
	{
		m_bfVertexShaderBuffer.m_f2OxOy.y = fOY;
	}

	float IrisSprite::GetOY()
	{
		return m_bfVertexShaderBuffer.m_f2OxOy.y;
	}

	void IrisSprite::SetMirror(bool bMirror)
	{
		m_bfPixelShaderBuffer.m_nMirror = (bMirror ? 1 : 0);
	}

	bool IrisSprite::GetMirror()
	{
		return m_bfPixelShaderBuffer.m_nMirror == 1;
	}

	void IrisSprite::SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}

	bool IrisSprite::GetVisible()
	{
		return m_bVisible;
	}

	void IrisSprite::SetOpacity(float fOpacity)
	{
		if (fOpacity < 0.0f) {
			fOpacity = 0.0f;
		}
		else if (fOpacity > 255.0f) {
			fOpacity = 255.0f;
		}
		m_bfPixelShaderBuffer.m_fOpacity = fOpacity / 255.0f;
	}

	float IrisSprite::GetOpacity()
	{
		return m_bfPixelShaderBuffer.m_fOpacity;;
	}

	void IrisSprite::SetSrcRect(IrisRect *& pSrcRect)
	{
		IrisRect::Release(m_pSrcRect);
		pSrcRect->IncreamRefCount();

		m_pSrcRect = pSrcRect;

		m_bSrcRectDirtyFlag = true;
	}

	IrisRect * IrisSprite::GetSrcRect() const
	{
		return m_pSrcRect;
	}

	void IrisSprite::SetTone(IrisTone *& pTone)
	{
		IrisColor::Release(m_pTone);

		pTone->IncreamRefCount();
		m_pTone = pTone;

		m_bToneDirtyFlag = true;
	}

	IrisTone * IrisSprite::GetTone() const
	{
		return m_pTone;
	}

	void IrisSprite::Update()
	{
	}

	void IrisSprite::Render()
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

		if (m_bToneDirtyFlag || (m_pTone && m_pTone->Modified())) {
			if (m_pTone) {
				m_bfPixelShaderBuffer.m_f4Tone = { static_cast<float>(m_pTone->GetRed()), static_cast<float>(m_pTone->GetBlue()), static_cast<float>(m_pTone->GetGreen()), static_cast<float>(m_pTone->GetAlpha()) };
			}
			else {
				m_bfPixelShaderBuffer.m_f4Tone = { 0.0f, 0.0f, 0.0f, 0.0f };
			}

			m_bToneDirtyFlag = false;

			if (m_pTone) {
				m_pTone->ModifyDone();
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

		if (m_bSrcRectDirtyFlag || (m_pSrcRect && m_pSrcRect->Modified())) {
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
				m_pSrcRect->ModifyDone();
			}
		}

		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto pVertexShader = IrisSpriteVertexShader::Instance();
		auto pPixelShader = IrisSpritePixelShader::Instance();

		auto pContex = pD3DManager->GetD3DDeviceContext();
		
		unsigned int nStride = sizeof(IrisSpriteVertex);
		unsigned int nOffset = 0;

		pVertexShader->SetWorldMatrix(m_bfVertexShaderBuffer);
		pPixelShader->SetColorProcessInfo(m_bfPixelShaderBuffer);

		pD3DManager->SetCurrentVertexBufferInfo(nStride, nOffset, m_pVertexBuffer);
		pD3DManager->SetCurrentTexture(m_pBitmap->GetTexture());

		pContex->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
		pContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		auto pTexture = m_pBitmap->GetTexture();

		pTexture->AquireSyncFromDx11Side();

		auto pShaderResource = pTexture->GetShaderResourceView();
		auto pShaderSampler = pTexture->GetDefaultSamplerState();

		pContex->PSSetShaderResources(0, 1, &pShaderResource);
		pContex->PSSetSamplers(0, 1, &pShaderSampler);

		//DirectX::ScratchImage image;
		//DirectX::CaptureTexture(IrisD3DResourceManager::Instance()->GetD3D11Device(), IrisD3DResourceManager::Instance()->GetD3DDeviceContext(), m_pBitmap->GetTexture()->GetTexture(), image);
		//DirectX::SaveToWICFile(*image.GetImages(), DirectX::WIC_FLAGS_NONE, GUID_ContainerFormatPng, L"te.png", &GUID_WICPixelFormat32bppBGRA);

		pContex->Draw(6, 0);

		pTexture->ReleaseSyncFromDx11Side();

	}

	bool IrisSprite::Dispose()
	{
		IrisBitmap::Release(m_pBitmap);
		IrisRect::Release(m_pSrcRect);
		IrisColor::Release(m_pTone);

		SafeCOMRelease(m_pVertexBuffer);

		return true;
	}

	Iris2D::IrisSprite::~IrisSprite()
	{
		Dispose();
	}

	bool IrisSprite::CreateSpriteVertexBuffer()
	{
		if (!m_pBitmap) {
			return false;
		}

		SafeCOMRelease(m_pVertexBuffer);

		auto nWidth = m_pBitmap->GetWidth();
		auto nHeight = m_pBitmap->GetHeight();

		IrisSpriteVertex arrVertices[] = {
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
		dbdVertextDesc.ByteWidth = sizeof(IrisSpriteVertex) * 6;

		D3D11_SUBRESOURCE_DATA dsdResourceData;
		memset(&dsdResourceData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
		dsdResourceData.pSysMem = arrVertices;

		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto hResult = pD3DManager->GetD3D11Device()->CreateBuffer(&dbdVertextDesc, &dsdResourceData, &m_pVertexBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pVertexBuffer);
			return false;
		}

		return true;
	}

}