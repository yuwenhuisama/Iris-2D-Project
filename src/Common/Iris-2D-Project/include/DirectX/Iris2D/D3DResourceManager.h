#ifndef _H_D3D_RESOURCE_MANAGER_
#define _H_D3D_RESOURCE_MANAGER_

#include "DirectX/Common.h"

namespace Iris2D
{
	class PixelShaderBase;
	class VertexShaderBase;
	class TextureDX;
	__declspec(align(16)) class D3DResourceManager
	{
	private:
		ID3D11Device* m_pD3D11Device = nullptr;
		ID3D10Device1* m_pD3D10Device = nullptr;

		ID3D11DeviceContext* m_pD3D11Context = nullptr;

		IDXGISwapChain* m_pSwapChain = nullptr;
		ID3D11RenderTargetView* m_pBackBufferTarget = nullptr;

		unsigned int m_nCurrentBufferStride = 0;
		unsigned int m_nCurrentBufferOffset = 0;
		ID3D11Buffer* m_pCurrentVertexBuffer = 0;
		TextureDX* m_pCurrentTexture = nullptr;

		DirectX::XMMATRIX m_mxViewProjMatrix;

	public:
		static D3DResourceManager* Instance();

	public:
		bool Initialize(HWND hWindow);
		bool Release();

	public:
		ID3D11Device* GetD3D11Device();
		ID3D10Device1* GetD3D10Device();

		ID3D11DeviceContext* GetD3DDeviceContext();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRenderTargetView();

		void SetVertexShader(VertexShaderBase* pVertexShader);
		void SetPixelShader(PixelShaderBase* pPixelShader);
		void SetCurrentVertexBufferInfo(unsigned int nStride, unsigned int nOffset, ID3D11Buffer* pVertexBuffer);
		void SetCurrentTexture(TextureDX* pTexture);

		void AdjustViewMatrix(unsigned int nWindowWidth, unsigned int nWindowHeight);

		const DirectX::XMMATRIX& GetViewMatrix();

	private:

		bool InitializeDirectX11(IDXGIAdapter1* pAdapter, int nWidth, int nHeight, HWND hWindow);
		bool InitializeDirectX10(IDXGIAdapter1* pAdapter);

		D3DResourceManager() = default;
		~D3DResourceManager() = default;

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}
	};
}

#endif // !_H_D3D_RESOURCE_MANAGER_


