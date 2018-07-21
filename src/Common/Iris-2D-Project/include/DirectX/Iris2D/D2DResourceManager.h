#ifndef _H_D2D_RESOURCE_MANAGER_
#define _H_D2D_RESOURCE_MANAGER_

#include "DirectX/Common.h"

namespace Iris2D
{
	class D2DResourceManager
	{
	private:
		ID2D1Factory1* m_pD2DFactory = nullptr;
		ID2D1Device* m_pD2DDevice = nullptr;
		ID2D1DeviceContext* m_pD2DDeviceContext = nullptr;
		IDWriteFactory3* m_pDWriteFactory = nullptr;
		//IWICImagingFactory2* m_pWICImagingFactory = nullptr;

	public:
		static D2DResourceManager* Instance();

	private:
		D2DResourceManager() = default;
		//bool D2DResourceManager::LoadWICResource(const std::wstring& wstrUri, IWICFormatConverter*& pConverter, unsigned int& nWidth, unsigned int& nHeight);
		bool CreateTexture(unsigned int nWidth, unsigned int nHeight, ID3D11Resource*& pTexture);
		bool MakeSharedResource(ID3D11Resource* pTexture, HANDLE& hResourceShareHandle, IDXGIKeyedMutex*& pDX11Mutex);
		bool CreateDxgiRenderTarget(HANDLE hResourceShareHandle, ID2D1RenderTarget*& pDxgiRenderBitmap, IDXGIKeyedMutex*& pDX10Mutex);

	public:
		bool Initialize();

		bool LoadBitmapFromFile(const std::wstring& wstrUri, 
			ID2D1RenderTarget*& pDxgiRenderTarget,
			ID3D11Resource*& pTexture,
			//ID2D1Bitmap*& pBitmap, 
			ID3D11ShaderResourceView*& pResourceView,
			HANDLE& hResourceShareHandle,
			IDXGIKeyedMutex*& pDX10Mutex,
			IDXGIKeyedMutex*& pDX11Mutex
		);

		bool CreateBlankTexture(
			unsigned int nWidth,
			unsigned int nHeight,
			ID2D1RenderTarget*& pDxgiRenderTarget,
			ID3D11Resource*& pTexture,
			//ID2D1Bitmap*& pBitmap,
			ID3D11ShaderResourceView*& pResourceView,
			HANDLE& hResourceShareHandle,
			IDXGIKeyedMutex*& pDX10Mutex,
			IDXGIKeyedMutex*& pDX11Mutex
		);

		ID2D1Factory1* GetD2DFactory() const;
		ID2D1DeviceContext* GetD2DDeviceContext() const;
		IDWriteFactory3* GetDWriteFactory() const;

		bool Release();

		~D2DResourceManager() = default;
	};


}
#endif // !_H_D2D_RESOURCE_MANAGER_
