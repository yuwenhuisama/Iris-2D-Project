#include "DirectX/Util/TextureDX.h"
#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Iris2D/D2DResourceManager.h"


namespace Iris2D
{
	ID3D11SamplerState* TextureDX::sm_pDefaultSamplerState = nullptr;
	ID3D11BlendState* TextureDX::sm_pDefaultBlendState = nullptr;

	bool TextureDX::Initialize()
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

		auto hResult = D3DResourceManager::Instance()->
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
		hResult = D3DResourceManager::Instance()->GetD3D11Device()->CreateBlendState(&dbdBlendDesc, &sm_pDefaultBlendState);
		if (FAILED(hResult)) {
			SafeCOMRelease(sm_pDefaultBlendState);
			return false;
		}

		D3DResourceManager::Instance()->GetD3DDeviceContext()->OMSetBlendState(sm_pDefaultBlendState, arrBlendFactor, 0xFFFFFFFF);

		return true;
	}

	bool TextureDX::Release()
	{
		SafeCOMRelease(sm_pDefaultBlendState);
		SafeCOMRelease(sm_pDefaultSamplerState);
		return true;
	}

	TextureDX* TextureDX::Create(const std::wstring& wstrTexturePath)
	{
		auto pTexture = new TextureDX();

		auto pD2DManager = D2DResourceManager::Instance();
		auto pD3DManager = D3DResourceManager::Instance();

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

	TextureDX * TextureDX::Create(unsigned int nWidth, unsigned int nHeight)
	{
		auto pTexture = new TextureDX();

		auto pD2DManager = D2DResourceManager::Instance();
		auto pD3DManager = D3DResourceManager::Instance();

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

	void TextureDX::Release(TextureDX*& pTexture)
	{
		delete pTexture;
		pTexture = nullptr;
	}

	TextureDX::~TextureDX() 
	{
		SafeCOMRelease(m_pTextureResource);
		SafeCOMRelease(m_pTexture);
		SafeCOMRelease(m_pRenderTargetBitmap);
		//SafeCOMRelease(m_pBitmap);
		SafeCOMRelease(m_pDX11Mutex);
		SafeCOMRelease(m_pDX10Mutex);
	}

	ID3D11ShaderResourceView * TextureDX::GetShaderResourceView()
	{
		return m_pTextureResource;
	}

	ID3D11SamplerState * TextureDX::GetDefaultSamplerState()
	{
		return sm_pDefaultSamplerState;
	}

	void TextureDX::AquireSyncFromDx11Side()
	{
		m_pDX11Mutex->AcquireSync(m_nSync++, INFINITE);
	}

	void TextureDX::ReleaseSyncFromDx11Side()
	{
		m_pDX11Mutex->ReleaseSync(--m_nSync);
	}

	void TextureDX::AquireSyncFromDx10Side()
	{
		m_pDX10Mutex->AcquireSync(m_nSync++, INFINITE);
	}

	void TextureDX::ReleaseSyncFromDx10Side()
	{
		m_pDX10Mutex->ReleaseSync(--m_nSync);
	}

	bool TextureDX::SaveToFile(const std::wstring & wstrFilePath)
	{
		AquireSyncFromDx11Side();
		DirectX::ScratchImage image;
		auto hResult = DirectX::CaptureTexture(D3DResourceManager::Instance()->GetD3D11Device(), D3DResourceManager::Instance()->GetD3DDeviceContext(), m_pTexture, image);
		if (FAILED(hResult)) {
			return false;
		}

		hResult = DirectX::SaveToWICFile(*image.GetImages(), DirectX::WIC_FLAGS_NONE, GUID_ContainerFormatPng, wstrFilePath.c_str(), &GUID_WICPixelFormat32bppBGRA);
		if (FAILED(hResult)) {
			return false;
		}
		ReleaseSyncFromDx11Side();
		return true;
	}

	ID3D11Resource * TextureDX::GetTexture()
	{
		return m_pTexture;
	}

	ID2D1RenderTarget* TextureDX::GetRenderTargetBitmap()
	{
		return m_pRenderTargetBitmap;
	}
	IDXGISurface * TextureDX::GetDxgiSurface()
	{
		IDXGISurface* pSurface = nullptr;
		//auto hResult = D3DResourceManager::Instance()->GetD3D11Device()->OpenSharedResource(m_hSharedResourceHandle, __uuidof(IDXGISurface), reinterpret_cast<LPVOID*>(&pSurface));
		auto hResult = m_pTexture->QueryInterface(__uuidof(IDXGISurface), (void**)&pSurface);
		if (FAILED(hResult)) {
			SafeCOMRelease(pSurface);
			return nullptr;
		}
		return pSurface;
	}
}