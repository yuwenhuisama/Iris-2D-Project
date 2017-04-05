#include "Iris2D/IrisSprite.h"
#include "Iris2D/IrisBitmap.h"
#include "Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "Iris2D/IrisD3DResourceManager.h"
#include "Iris2D Util/IrisSpriteVertex.h"
#include "Iris2D/IrisGraphics.h"
#include "Iris2D Util/IrisTexture.h"

namespace Iris2D
{
	IrisSprite * Iris2D::IrisSprite::Create()
	{
		auto pSprite = new IrisSprite();
		IrisGraphics::Instance()->AddSprite(pSprite);

		return pSprite;
	}

	void Iris2D::IrisSprite::Release(IrisSprite*& pSprite)
	{
		IrisGraphics::Instance()->RemoveSprite(pSprite);
		InnerRelease(pSprite);
		pSprite = nullptr;
	}

	void IrisSprite::InnerRelease(IrisSprite * pSprite)
	{
		delete pSprite;
	}

	void IrisSprite::SetBitmap(IrisBitmap* pBitmap)
	{
		if (m_pBitmap == pBitmap) {
			return;
		}
		m_pBitmap =  pBitmap;
		CreateSpriteVertexBuffer();
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

	void IrisSprite::SetRoomX(float fZoomX)
	{
		if (fZoomX == m_fZoomX) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomX = fZoomX;
	}

	float IrisSprite::GetRoomX() const
	{
		return m_fZoomX;
	}

	void IrisSprite::SetRoomY(float fZoomY)
	{
		if (fZoomY == m_fZoomY) {
			return;
		}

		m_bZoomDirtyFlag = true;
		m_fZoomY = fZoomY;
	}

	float IrisSprite::GetRoomY() const
	{
		return m_fZoomY;
	}

	void IrisSprite::Update()
	{
	}

	void IrisSprite::Render()
	{
		if (!m_pBitmap) {
			return;
		}

		if (m_bPositionDirtyFlag) {
			m_mbMatrixBuffer.m_mxTransMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_fX, m_fY, m_fZ));
			m_bPositionDirtyFlag = false;
		}

		if (m_bAngleDirtyFlag) {
			m_mbMatrixBuffer.m_mxRotMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(m_fAngle));
			m_bAngleDirtyFlag = false;
		}
		
		if (m_bZoomDirtyFlag) {
			m_mbMatrixBuffer.m_mxZoomMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(m_fZoomX, m_fZoomY, 1.0f));
			m_bZoomDirtyFlag = false;
		}

		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto pVertexShader = IrisSpriteVertexShader::Instance();
		auto pContex = pD3DManager->GetD3DDeviceContext();
		
		unsigned int nStride = sizeof(IrisSpriteVertex);
		unsigned int nOffset = 0;

		pVertexShader->SetViewProjectMatrix(pD3DManager->GetViewMatrix());
		pVertexShader->SetWorldMatrix(m_mbMatrixBuffer);

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

		pContex->Draw(6, 0);

		pTexture->ReleaseSyncFromDx11Side();

	}

	Iris2D::IrisSprite::~IrisSprite()
	{
		if (m_pBitmap) {
			IrisBitmap::Release(m_pBitmap);
			m_pBitmap = nullptr;
		}

		SafeCOMRelease(m_pVertexBuffer);
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
			{ XMFLOAT4(nWidth, 0.0f,    1.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT4(nWidth, nHeight, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT4(0.0f,   nHeight, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

			{ XMFLOAT4(0.0f,   nHeight, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
			{ XMFLOAT4(0.0f,   0.0f,    1.0f, 1.0f),   XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT4(nWidth, 0.0f,    1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
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