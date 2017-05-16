#include "Iris2D/IrisViewport.h"
#include "Iris2D/IrisSprite.h"
#include "Iris2D/IrisRect.h"
#include "Iris2D/IrisColor.h"
#include "Iris2D Util/IrisTexture.h"
#include "Iris2D Util/IrisViewportVertex.h"
#include "Iris2D/IrisD3DResourceManager.h"
#include "Iris2D/IrisGraphics.h"
#include "Iris2D/IrisShaders/IrisViewportVertexShader.h"
#include "Iris2D/IrisShaders/IrisViewportPixelShader.h"
#include "Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "Iris2D/IrisShaders/IrisSpritePixelShader.h"

namespace Iris2D
{
	IrisViewport* IrisViewport::sm_pGlobalViewport = nullptr;

	IrisViewport * IrisViewport::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pNewViewport = new IrisViewport();
		pNewViewport->m_pTexture = IrisTexture::Create(nWidth, nHeight);
		if (!pNewViewport->m_pTexture) {
			delete pNewViewport;
			return nullptr;
		}

		if (!pNewViewport->CreateViewportVertexBuffer(nWidth, nHeight)) {
			delete pNewViewport;
			return nullptr;
		}

		IrisGraphics::Instance()->AddViewport(pNewViewport);
		
		pNewViewport->m_fX = fX;
		pNewViewport->m_fY = fY;
		pNewViewport->m_bVertexBufferDirtyFlag = true;

		//pNewViewport->m_mxViewProjMatrix = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(nWidth), static_cast<float>(nHeight), 0.0f, 0.0f, 9999.0f);
		//pNewViewport->m_mxViewProjMatrix = DirectX::XMMatrixTranspose(pNewViewport->m_mxViewProjMatrix);

		//pNewViewport->m_mxViewProjMatrix = IrisD3DResourceManager::Instance()->GetViewMatrix();

		return pNewViewport;
	}

	IrisViewport * IrisViewport::Create(const IrisRect * pRect, IR_PARAM_RESULT_CT)
	{
		return Create(pRect->GetX(), pRect->GetY(), static_cast<unsigned int>(pRect->GetWidth()), static_cast<unsigned int>(pRect->GetHeight()), IR_PARAM);
	}

	void IrisViewport::Release(IrisViewport*& pViewport)
	{
		if (!pViewport) {
			return;
		}

		IrisGraphics::Instance()->RemoveViewport(pViewport);

		if (sm_pGlobalViewport != pViewport) {
			sm_pGlobalViewport->m_stSprits.insert(pViewport->m_stSprits.begin(), pViewport->m_stSprits.end());
		}

		delete pViewport;
		pViewport = nullptr;
	}

	void IrisViewport::ManagedRelease(IrisViewport* pViewport)
	{
		delete pViewport;
	}

	void IrisViewport::InnerRelease(IrisViewport *& pViewport)
	{
		for (auto& pSprite : pViewport->m_stSprits) {
			IrisSprite::InnerRelease(pSprite);
		}

		delete pViewport;
		pViewport = nullptr;
	}

	bool IrisViewport::InitGlobalViewport(unsigned int nWindowWidth, unsigned int nWindowHeight)
	{
		sm_pGlobalViewport = Create(0.0f, 0.0f, nWindowWidth, nWindowHeight);
		return sm_pGlobalViewport != nullptr;
	}

	void IrisViewport::ReleaseGlobalViewport()
	{
		Release(sm_pGlobalViewport);
	}

	IrisViewport * IrisViewport::GetGlobalViewport()
	{
		return sm_pGlobalViewport;
	}

	void IrisViewport::SetOX(float fOX)
	{
		m_ivvsVertexBuffer.m_f2OxOy.x = fOX;
	}

	float IrisViewport::GetOX() const
	{
		return m_ivvsVertexBuffer.m_f2OxOy.x;
	}

	void IrisViewport::SetOY(float fOY)
	{
		m_ivvsVertexBuffer.m_f2OxOy.y = fOY;
	}

	float IrisViewport::GetOY() const
	{
		return m_ivvsVertexBuffer.m_f2OxOy.y;
	}

	void IrisViewport::SetSrcRect(IrisRect *& pSrcRect)
	{
		IrisRect::Release(m_pSrcRect);

		pSrcRect->IncreamRefCount();
		m_pSrcRect = pSrcRect;

		m_bSrcRectDirtyFlag = true;
	}

	IrisRect * IrisViewport::GetSrcRect() const
	{
		return m_pSrcRect;
	}

	void IrisViewport::SetTone(IrisTone *& pTone)
	{
		IrisColor::Release(m_pTone);

		pTone->IncreamRefCount();
		m_pTone = pTone;

		m_bToneDirtyFlag = true;
	}

	IrisTone * IrisViewport::GetTone() const
	{
		return m_pTone;
	}

	bool IrisViewport::Dispose()
	{
		return true;
	}

	bool IrisViewport::RenderSprite()
	{
		if (!m_bVisible) {
			return true;
		}

		auto pD3DManager = IrisD3DResourceManager::Instance();
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

		//IrisSpriteVertexShader::Instance()->SetViewProjectMatrix(m_mxViewProjMatrix);
		for (auto pSprite : m_stSprits) {
			pSprite->Render();
		}

		pContext->OMSetRenderTargets(1, &pOldRenderTarget, nullptr);
		SafeCOMRelease(pNewRenderTargetView);

		m_pTexture->ReleaseSyncFromDx11Side();
		//----
		return true;
	}

	bool IrisViewport::RenderSelf()
	{
		if (!m_bVisible) {
			return true;
		}

		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto pContext = pD3DManager->GetD3DDeviceContext();
		auto pVertexShader = IrisViewportVertexShader::Instance();
		auto pPixelShader = IrisViewportPixelShader::Instance();
		//----
		if (m_bVertexBufferDirtyFlag) {
			m_ivvsVertexBuffer.m_mxTransMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_fX, m_fY, m_fZ));
			m_bVertexBufferDirtyFlag = false;
		}
		
		if (m_bToneDirtyFlag || (m_pTone && m_pTone->Modified())) {
			if (m_pTone) {
				m_ivpsPixelBuffer.m_f4Tone = { static_cast<float>(m_pTone->GetRed()), static_cast<float>(m_pTone->GetBlue()), static_cast<float>(m_pTone->GetGreen()), static_cast<float>(m_pTone->GetAlpha()) };
			}
			else {
				m_ivpsPixelBuffer.m_f4Tone = { 0.0f, 0.0f, 0.0f, 0.0f };
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
				m_pSrcRect->ModifyDone();
			}
		}
		//----

		//----
		unsigned int nStride = sizeof(IrisViewportVertex);
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

	void IrisViewport::AddSprite(IrisSprite * pSprite)
	{
		m_stSprits.insert(pSprite);
	}

	void IrisViewport::RemoveSprite(IrisSprite * pSprite)
	{
		m_stSprits.erase(pSprite);
	}

	bool IrisViewport::CreateViewportVertexBuffer(unsigned int nWidth, unsigned int nHeight)
	{
		SafeCOMRelease(m_pVertexBuffer);

		IrisViewportVertex arrVertices[] = {
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
		dbdVertextDesc.ByteWidth = sizeof(IrisViewportVertex) * 6;

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

	IrisViewport::~IrisViewport()
	{
		IrisTexture::Release(m_pTexture);
		SafeCOMRelease(m_pTexture);

		IrisRect::Release(m_pSrcRect);
		IrisColor::Release(m_pTone);
	}
}