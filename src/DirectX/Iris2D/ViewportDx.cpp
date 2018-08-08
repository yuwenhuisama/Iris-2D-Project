#include "DirectX/Iris2D/ViewportDX.h"
#include "Common/Iris2D/Sprite.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/Viewport.h"
#include "Common/Util/ProxyConvert.h"

#include "DirectX/Iris2D/RectDX.h"
#include "DirectX/Iris2D/ColorDX.h"
#include "DirectX/Iris2D/SpriteDX.h"

#include "DirectX/Util/TextureDX.h"
#include "DirectX/Util/ViewportVertexDX.h"

#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Iris2D/GraphicsDX.h"
#include "DirectX/Iris2D/Shaders/ViewportVertexShader.h"
#include "DirectX/Iris2D/Shaders/ViewportPixelShader.h"
#include "DirectX/Iris2D/Shaders/SpriteVertexShader.h"
#include "DirectX/Iris2D/Shaders/SpritePixelShader.h"

namespace Iris2D
{
	Viewport* ViewportDX::sm_pGlobalViewport = nullptr;

	ViewportDX * ViewportDX::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pNewViewport = new ViewportDX();
		pNewViewport->m_pTexture = TextureDX::Create(nWidth, nHeight);
		if (!pNewViewport->m_pTexture) {
			delete pNewViewport;
			return nullptr;
		}

		if (!pNewViewport->CreateViewportVertexBuffer(nWidth, nHeight)) {
			delete pNewViewport;
			return nullptr;
		}

		GraphicsDX::Instance()->AddViewport(pNewViewport);
		
		pNewViewport->m_fX = fX;
		pNewViewport->m_fY = fY;
		pNewViewport->m_bVertexBufferDirtyFlag = true;

		//pNewViewport->m_mxViewProjMatrix = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(nWidth), static_cast<float>(nHeight), 0.0f, 0.0f, 9999.0f);
		//pNewViewport->m_mxViewProjMatrix = DirectX::XMMatrixTranspose(pNewViewport->m_mxViewProjMatrix);

		//pNewViewport->m_mxViewProjMatrix = D3DResourceManager::Instance()->GetViewMatrix();

		return pNewViewport;
	}

	ViewportDX * ViewportDX::Create(const Rect * pRect, IR_PARAM_RESULT_CT)
	{
		return Create(pRect->GetX(), pRect->GetY(), static_cast<unsigned int>(pRect->GetWidth()), static_cast<unsigned int>(pRect->GetHeight()), IR_PARAM);
	}

	void ViewportDX::Release(ViewportDX*& pViewport)
	{
		if (!pViewport) {
			return;
		}

		if (GetProxied<ViewportDX*>(sm_pGlobalViewport) != pViewport) {
			GetProxied<ViewportDX*>(sm_pGlobalViewport)->m_stSprits.insert(pViewport->m_stSprits.begin(), pViewport->m_stSprits.end());
			GraphicsDX::Instance()->RemoveViewport(pViewport);
		}

		delete pViewport;
		pViewport = nullptr;
	}

	void ViewportDX::ForceRelease(ViewportDX *& pViewport)
	{
		for (auto& pSprite : pViewport->m_stSprits) {
			SpriteDX::ForceRelease(pSprite);
		}

		auto pProxy = pViewport->GetProxy();
		Viewport::Release(pProxy);

		delete pViewport;
		pViewport = nullptr;
	}

	bool ViewportDX::InitGlobalViewport(unsigned int nWindowWidth, unsigned int nWindowHeight)
	{
		sm_pGlobalViewport = Viewport::Create(0.0f, 0.0f, nWindowWidth, nWindowHeight);
		return sm_pGlobalViewport != nullptr;
	}

	void ViewportDX::ReleaseGlobalViewport()
	{
		Viewport::Release(sm_pGlobalViewport);
	}

	Viewport * ViewportDX::GetGlobalViewport()
	{
		return sm_pGlobalViewport;
	}

	void ViewportDX::SetOX(float fOX)
	{
		m_ivvsVertexBuffer.m_f2OxOy.x = fOX;
	}

	float ViewportDX::GetOX() const
	{
		return m_ivvsVertexBuffer.m_f2OxOy.x;
	}

	void ViewportDX::SetOY(float fOY)
	{
		m_ivvsVertexBuffer.m_f2OxOy.y = fOY;
	}

	float ViewportDX::GetOY() const
	{
		return m_ivvsVertexBuffer.m_f2OxOy.y;
	}

	void ViewportDX::SetSrcRect(Rect *& pSrcRect)
	{
		Rect::Release(m_pSrcRect);

		GetProxied<RectDX*>(pSrcRect)->IncreamRefCount();
		m_pSrcRect = pSrcRect;

		m_bSrcRectDirtyFlag = true;
	}

	Rect * ViewportDX::GetSrcRect() const
	{
		return m_pSrcRect;
	}

	void ViewportDX::SetTone(Tone *& pTone)
	{
		Color::Release(m_pTone);

		GetProxied<ColorDX*>(pTone)->IncreamRefCount();
		m_pTone = pTone;

		m_bToneDirtyFlag = true;
	}

	Tone * ViewportDX::GetTone() const
	{
		return m_pTone;
	}

	bool ViewportDX::Dispose()
	{
		return true;
	}

	bool ViewportDX::RenderSprite()
	{
		if (!m_bVisible) {
			return true;
		}

		auto pD3DManager = D3DResourceManager::Instance();
		auto pContext = pD3DManager->GetD3DDeviceContext();
		auto pDevice = pD3DManager->GetD3D11Device();
		auto pBufferResource = m_pTexture->GetTexture();

		m_pTexture->AquireSyncFromDx11Side();
		//----
		ID3D11RenderTargetView* pNewRenderTargetView = nullptr;
		auto hResult = pDevice->CreateRenderTargetView(pBufferResource, nullptr, &pNewRenderTargetView);
		if (FAILED(hResult)) {
			SafeCOMRelease(pNewRenderTargetView);
			return false;
		}

		ID3D11RenderTargetView* pOldRenderTarget = nullptr;

		pContext->OMGetRenderTargets(1, &pOldRenderTarget, nullptr);
		pContext->OMSetRenderTargets(1, &pNewRenderTargetView, nullptr);

		const float arrClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		pContext->ClearRenderTargetView(pNewRenderTargetView, arrClearColor);

		//SpriteVertexShader::Instance()->SetViewProjectMatrix(m_mxViewProjMatrix);
		for (auto pSprite : m_stSprits) {
			pSprite->Render();
		}

		pContext->OMSetRenderTargets(1, &pOldRenderTarget, nullptr);
		SafeCOMRelease(pNewRenderTargetView);

		m_pTexture->ReleaseSyncFromDx11Side();
		//----
		return true;
	}

	bool ViewportDX::RenderSelf()
	{
		if (!m_bVisible) {
			return true;
		}

		auto pD3DManager = D3DResourceManager::Instance();
		auto pContext = pD3DManager->GetD3DDeviceContext();
		auto pVertexShader = ViewportVertexShader::Instance();
		auto pPixelShader = ViewportPixelShader::Instance();
		//----
		if (m_bVertexBufferDirtyFlag) {
			m_ivvsVertexBuffer.m_mxTransMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_fX, m_fY, m_fZ));
			m_bVertexBufferDirtyFlag = false;
		}
		
		if (m_bToneDirtyFlag || (m_pTone && GetProxied<ToneDX*>(m_pTone)->Modified())) {
			if (m_pTone) {
				m_ivpsPixelBuffer.m_f4Tone = { static_cast<float>(m_pTone->GetRed()), static_cast<float>(m_pTone->GetBlue()), static_cast<float>(m_pTone->GetGreen()), static_cast<float>(m_pTone->GetAlpha()) };
			}
			else {
				m_ivpsPixelBuffer.m_f4Tone = { 0.0f, 0.0f, 0.0f, 0.0f };
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

				auto ptSize = m_pTexture->GetRenderTargetBitmap()->GetSize();

				m_ivpsPixelBuffer.m_f4ViewportRect = {
					m_pSrcRect->GetLeft() / ptSize.width,
					m_pSrcRect->GetTop() / ptSize.height,
					m_pSrcRect->GetRight() / ptSize.width,
					m_pSrcRect->GetBottom() / ptSize.height
				};

				fAdjust(m_ivpsPixelBuffer.m_f4ViewportRect.x);
				fAdjust(m_ivpsPixelBuffer.m_f4ViewportRect.y);
				fAdjust(m_ivpsPixelBuffer.m_f4ViewportRect.z);
				fAdjust(m_ivpsPixelBuffer.m_f4ViewportRect.w);
			}
			else {
				m_ivpsPixelBuffer.m_f4ViewportRect = { 0.0f, 0.0f, 1.0f, 1.0f };
			}

			m_bSrcRectDirtyFlag = false;

			if (m_pSrcRect) {
				GetProxied<RectDX*>(m_pSrcRect)->ModifyDone();
			}
		}
		//----

		//----
		unsigned int nStride = sizeof(ViewportVertexDX);
		unsigned int nOffset = 0;

		pVertexShader->SetWorldMatrix(m_ivvsVertexBuffer);
		pPixelShader->SetColorProcessInfo(m_ivpsPixelBuffer);

		pD3DManager->SetCurrentVertexBufferInfo(nStride, nOffset, m_pVertexBuffer);
		pD3DManager->SetCurrentTexture(m_pTexture);

		pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pTexture->AquireSyncFromDx11Side();

		auto pShaderResource = m_pTexture->GetShaderResourceView();
		auto pShaderSampler = m_pTexture->GetDefaultSamplerState();

		pContext->PSSetShaderResources(0, 1, &pShaderResource);
		pContext->PSSetSamplers(0, 1, &pShaderSampler);

		pContext->Draw(6, 0);

		m_pTexture->ReleaseSyncFromDx11Side();
		//----

		return true;
	}

	void ViewportDX::AddSprite(SpriteDX * pSprite) {
		m_stSprits.insert(pSprite);
	}

	void ViewportDX::RemoveSprite(SpriteDX * pSprite) {
		m_stSprits.insert(pSprite);
	}

	void ViewportDX::SetZ(float fOZ) {
	}

	float ViewportDX::GetZ() {
	}

	//void ViewportDX::AddSprite(Sprite * pSprite)
	//{
	//	m_stSprits.insert(GetProxied<SpriteDX*>(pSprite));
	//}

	//void ViewportDX::RemoveSprite(Sprite * pSprite)
	//{
	//	m_stSprits.erase(GetProxied<SpriteDX*>(pSprite));
	//}

	bool ViewportDX::CreateViewportVertexBuffer(unsigned int nWidth, unsigned int nHeight)
	{
		SafeCOMRelease(m_pVertexBuffer);

		ViewportVertexDX arrVertices[] = {
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
		dbdVertextDesc.ByteWidth = sizeof(ViewportVertexDX) * 6;

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

	ViewportDX::~ViewportDX()
	{
		TextureDX::Release(m_pTexture);
		// SafeCOMRelease(m_pTexture);

		Rect::Release(m_pSrcRect);
		Color::Release(m_pTone);
	}
}