#include "Iris2D Util\IrisTexture.h"
#include "Iris2D\IrisD3DResourceManager.h"
#include "Iris2D\IrisD2DResourceManager.h"


namespace Iris2D
{
	ID3D11SamplerState* IrisTexture::sm_pDefaultSamplerState = nullptr;
	ID3D11BlendState* IrisTexture::sm_pDefaultBlendState = nullptr;

	bool IrisTexture::Initialize()
	{
		// Default Sampler Desc
		D3D11_SAMPLER_DESC dsdDefaultSamplerDesc;
		memset(&dsdDefaultSamplerDesc, 0, sizeof(D3D11_SAMPLER_DESC));

		dsdDefaultSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		dsdDefaultSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		dsdDefaultSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		dsdDefaultSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		dsdDefaultSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		dsdDefaultSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		auto hResult = IrisD3DResourceManager::Instance()->
			GetD3D11Device()->
			CreateSamplerState(&dsdDefaultSamplerDesc, &sm_pDefaultSamplerState);
			
		if (FAILED(hResult)) {
			SafeCOMRelease(sm_pDefaultSamplerState);
			return false;
		}

		// Default Blend State
		D3D11_BLEND_DESC dbdBlendDesc;
		memset(&dbdBlendDesc, 0, sizeof(D3D11_BLEND_DESC));
		dbdBlendDesc.RenderTarget[0].BlendEnable = true;
		dbdBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		dbdBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		dbdBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		dbdBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		dbdBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		dbdBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		dbdBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		float arrBlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		hResult = IrisD3DResourceManager::Instance()->GetD3D11Device()->CreateBlendState(&dbdBlendDesc, &sm_pDefaultBlendState);
		if (FAILED(hResult)) {
			SafeCOMRelease(sm_pDefaultBlendState);
			return false;
		}

		IrisD3DResourceManager::Instance()->GetD3DDeviceContext()->OMSetBlendState(sm_pDefaultBlendState, arrBlendFactor, 0xFFFFFFFF);

		return true;
	}

	bool IrisTexture::Release()
	{
		SafeCOMRelease(sm_pDefaultBlendState);
		SafeCOMRelease(sm_pDefaultSamplerState);
		return true;
	}

	IrisTexture* IrisTexture::Create(const std::wstring& wstrTexturePath)
	{
		auto pTexture = new IrisTexture();

		auto pD2DManager = IrisD2DResourceManager::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();

		if (!pD2DManager->LoadBitmapFromFile(wstrTexturePath, 
			pTexture->m_pRenderTargetBitmap, 
			pTexture->m_pTexture, 
			//pTexture->m_pBitmap, 
			pTexture->m_pTextureResource,
			pTexture->m_hSharedResourceHandle,
			pTexture->m_pDX10Mutex,
			pTexture->m_pDX11Mutex)) {
			delete pTexture;
			return nullptr;
		}

		//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		//srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		//srvDesc.Texture2D.MipLevels = 1;
		//srvDesc.Texture2D.MostDetailedMip = 0;

		//pTexture->m_bDX10MutexRequired = true;

		//auto hResult = pD3DManager->GetD3D11Device()->CreateShaderResourceView(pTexture->m_pTexture, &srvDesc, &pTexture->m_pTextureResource);

		//if (FAILED(hResult)) {
		//	delete pTexture;
		//	return nullptr;
		//}

		return pTexture;
	}

	IrisTexture * IrisTexture::Create(unsigned int nWidth, unsigned int nHeight)
	{
		auto pTexture = new IrisTexture();

		auto pD2DManager = IrisD2DResourceManager::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		if (!pD2DManager->CreateBlankTexture(nWidth,
			nHeight,
			pTexture->m_pRenderTargetBitmap,
			pTexture->m_pTexture,
			//pTexture->m_pBitmap,
			pTexture->m_pTextureResource,
			pTexture->m_hSharedResourceHandle,
			pTexture->m_pDX10Mutex,
			pTexture->m_pDX11Mutex)) {

			delete pTexture;
			return nullptr;
		}

		//pTexture->m_bDX10MutexRequired = true;

		auto hResult = pD3DManager->GetD3D11Device()->CreateShaderResourceView(pTexture->m_pTexture, &srvDesc, &pTexture->m_pTextureResource);

		if (FAILED(hResult)) {
			delete pTexture;
			return nullptr;
		}

		return pTexture;
	}

	void IrisTexture::Release(IrisTexture*& pTexture)
	{
		delete pTexture;
		pTexture = nullptr;
	}

	IrisTexture::~IrisTexture() 
	{
		SafeCOMRelease(m_pTextureResource);
		SafeCOMRelease(m_pTexture);
		SafeCOMRelease(m_pRenderTargetBitmap);
		//SafeCOMRelease(m_pBitmap);
		SafeCOMRelease(m_pDX11Mutex);
		SafeCOMRelease(m_pDX10Mutex);
	}

	ID3D11ShaderResourceView * IrisTexture::GetShaderResourceView()
	{
		return m_pTextureResource;
	}

	ID3D11SamplerState * IrisTexture::GetDefaultSamplerState()
	{
		return sm_pDefaultSamplerState;
	}

	void IrisTexture::AquireSyncFromDx11Side()
	{
		m_pDX11Mutex->AcquireSync(m_nSync++, INFINITE);
	}

	void IrisTexture::ReleaseSyncFromDx11Side()
	{
		m_pDX11Mutex->ReleaseSync(--m_nSync);
	}

	void IrisTexture::AquireSyncFromDx10Side()
	{
		m_pDX10Mutex->AcquireSync(m_nSync++, INFINITE);
	}

	void IrisTexture::ReleaseSyncFromDx10Side()
	{
		m_pDX10Mutex->ReleaseSync(--m_nSync);
	}
	ID3D11Resource * IrisTexture::GetTexture()
	{
		return m_pTexture;
	}

	ID2D1RenderTarget* IrisTexture::GetRenderTargetBitmap()
	{
		return m_pRenderTargetBitmap;
	}
}