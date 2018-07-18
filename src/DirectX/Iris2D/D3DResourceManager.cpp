#include "DirectX/Iris2D/D3DResourceManager.h"
#include "DirectX/Iris2D/Shaders/VertexShaderBase.h"
#include "DirectX/Iris2D/Shaders/PixelShaderBase.h"
#include "DirectX/Util/TextureDX.h"

namespace Iris2D
{
	D3DResourceManager * D3DResourceManager::Instance()
	{
		static auto pInstance = D3DResourceManager();
		return &pInstance;
	}

	bool D3DResourceManager::Initialize(HWND hWindow)
	{
		RECT rcDimensions;
		GetClientRect(hWindow, &rcDimensions);

		unsigned int nWidth = rcDimensions.right - rcDimensions.left;
		unsigned int nHeight = rcDimensions.bottom - rcDimensions.top;

		HRESULT hResult = S_OK;
		IDXGIFactory1* pIDxgiFactory = nullptr;
		IDXGIAdapter1* pAdapter = nullptr;

		if FAILED(hResult = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (LPVOID*)&pIDxgiFactory))
		{
			SafeCOMRelease(pIDxgiFactory);
			return false;
		}

		if FAILED(hResult = pIDxgiFactory->EnumAdapters1(0, &pAdapter))
		{
			SafeCOMRelease(pIDxgiFactory);
			SafeCOMRelease(pAdapter);
			return false;
		}

		if (!InitializeDirectX11(pAdapter, nWidth, nHeight, hWindow)) {
			SafeCOMRelease(pIDxgiFactory);
			SafeCOMRelease(pAdapter);
			return false;
		}

		if (!InitializeDirectX10(pAdapter)) {
			SafeCOMRelease(pIDxgiFactory);
			SafeCOMRelease(pAdapter);
			return false;
		}
		
		SafeCOMRelease(pIDxgiFactory);
		SafeCOMRelease(pAdapter);

		m_pD3D11Context->OMSetRenderTargets(1, &m_pBackBufferTarget, 0);

		D3D11_VIEWPORT dvViewport;
		dvViewport.Width = static_cast<float>(nWidth);
		dvViewport.Height = static_cast<float>(nHeight);
		dvViewport.MinDepth = 0.0f;
		dvViewport.MaxDepth = 1.0f;
		dvViewport.TopLeftX = 0.0f;
		dvViewport.TopLeftY = 0.0f;

		m_pD3D11Context->RSSetViewports(1, &dvViewport);

		return true;
	}

	bool D3DResourceManager::Release()
	{
		SafeCOMRelease(m_pD3D11Device);
		SafeCOMRelease(m_pD3D10Device);
		SafeCOMRelease(m_pD3D11Context);
		SafeCOMRelease(m_pSwapChain);
		SafeCOMRelease(m_pBackBufferTarget);
		//SafeCOMRelease(m_pCurrentVertexBuffer);

		return true;
	}
	
	ID3D11Device * D3DResourceManager::GetD3D11Device()
	{
		return m_pD3D11Device;
	}

	ID3D10Device1 * D3DResourceManager::GetD3D10Device()
	{
		return m_pD3D10Device;
	}

	ID3D11DeviceContext * D3DResourceManager::GetD3DDeviceContext()
	{
		return m_pD3D11Context;
	}

	IDXGISwapChain * D3DResourceManager::GetSwapChain()
	{
		return m_pSwapChain;
	}

	ID3D11RenderTargetView * D3DResourceManager::GetRenderTargetView()
	{
		return m_pBackBufferTarget;
	}

	void D3DResourceManager::SetVertexShader(VertexShaderBase * pVertexShader)
	{
		m_pD3D11Context->IASetInputLayout(pVertexShader->GetInputLayout());
		//m_pD3D11Context->VSSetShader(pVertexShader->GetVertexShader(), nullptr, 0);
		pVertexShader->SetToContext();
	}

	void D3DResourceManager::SetPixelShader(PixelShaderBase * pPixelShader)
	{
		//m_pD3D11Context->PSSetShader(pPixelShader->GetPixelShader(), nullptr, 0);
		pPixelShader->SetToContext();
	}

	void D3DResourceManager::SetCurrentVertexBufferInfo(unsigned int nStride, unsigned int nOffset, ID3D11Buffer * pVertexBuffer)
	{
		m_nCurrentBufferStride = nStride;
		m_nCurrentBufferOffset = nOffset;
		m_pCurrentVertexBuffer = pVertexBuffer;
	}

	void D3DResourceManager::SetCurrentTexture(TextureDX * pTexture)
	{
		m_pCurrentTexture = pTexture;
	}

	void D3DResourceManager::AdjustViewMatrix(unsigned int nWindowWidth, unsigned int nWindowHeight)
	{
		m_mxViewProjMatrix = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(nWindowWidth), static_cast<float>(nWindowHeight), 0.0f, 0.0f, 9999.0f);
		m_mxViewProjMatrix = DirectX::XMMatrixTranspose(m_mxViewProjMatrix);
	}

	const DirectX::XMMATRIX& D3DResourceManager::GetViewMatrix()
	{
		return m_mxViewProjMatrix;
	}

	bool D3DResourceManager::InitializeDirectX11(IDXGIAdapter1* pAdapter, int nWidth, int nHeight, HWND hWindow)
	{
		D3D_FEATURE_LEVEL arrDX11FeatureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		unsigned int nTotalFeatureLevels = ARRAYSIZE(arrDX11FeatureLevels);

		DXGI_SWAP_CHAIN_DESC dscdSwapChainDesc;
		ZeroMemory(&dscdSwapChainDesc, sizeof(dscdSwapChainDesc));
		dscdSwapChainDesc.BufferCount = 1;
		dscdSwapChainDesc.BufferDesc.Width = nWidth;
		dscdSwapChainDesc.BufferDesc.Height = nHeight;
		dscdSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		dscdSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		dscdSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		dscdSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dscdSwapChainDesc.OutputWindow = hWindow;
		dscdSwapChainDesc.Windowed = true;
		dscdSwapChainDesc.SampleDesc.Count = 1;
		dscdSwapChainDesc.SampleDesc.Quality = 0;

		unsigned int nCreationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		D3D_DRIVER_TYPE ddtDX11DriverType = D3D_DRIVER_TYPE_HARDWARE;

#ifdef _DEBUG
		nCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 
		auto hResult = D3D11CreateDeviceAndSwapChain(
			pAdapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			0,
			nCreationFlags,
			arrDX11FeatureLevels,
			nTotalFeatureLevels,
			D3D11_SDK_VERSION,
			&dscdSwapChainDesc,
			&m_pSwapChain,
			&m_pD3D11Device,
			nullptr,
			&m_pD3D11Context
		);

		if (FAILED(hResult)) {
			SafeCOMRelease(m_pSwapChain);
			SafeCOMRelease(m_pD3D11Device);
			SafeCOMRelease(m_pD3D11Context);
			return false;
		}

		ID3D11Texture2D* pBackBufferTexture = nullptr;

		hResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);

		if (FAILED(hResult))
		{
			SafeCOMRelease(m_pD3D11Device);
			SafeCOMRelease(m_pD3D11Context);
			SafeCOMRelease(m_pSwapChain);
			return false;
		}

		hResult = m_pD3D11Device->CreateRenderTargetView(pBackBufferTexture, 0, &m_pBackBufferTarget);

		SafeCOMRelease(pBackBufferTexture);

		if (FAILED(hResult)) {
			return false;
		}

		AdjustViewMatrix(nWidth, nHeight);

		return true;
	}

	bool D3DResourceManager::InitializeDirectX10(IDXGIAdapter1* pAdapter)
	{
		D3D_FEATURE_LEVEL arrDX10FeatureLevels[] = {
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		// DX 10 Device
		unsigned int nCreationFlags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
		nCreationFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif 

		// DX 10 Device		
		D3D10_DRIVER_TYPE ddtDX10DriverType = D3D10_DRIVER_TYPE_HARDWARE;

		auto hResult = D3D10CreateDevice1(
			pAdapter,
			D3D10_DRIVER_TYPE_HARDWARE,
			0,
			nCreationFlags,
			D3D10_FEATURE_LEVEL_10_1,
			D3D10_1_SDK_VERSION,
			&m_pD3D10Device
		);

		if (FAILED(hResult)) {
			SafeCOMRelease(m_pD3D10Device);
			return false;
		}

		return true;
	}
}