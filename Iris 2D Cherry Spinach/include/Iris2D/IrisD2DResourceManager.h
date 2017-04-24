#ifndef _H_IRISD2DRESOURCEMANAGER_
#define _H_IRISD2DRESOURCEMANAGER_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisD2DResourceManager
	{
	private:
		ID2D1Factory1* m_pD2DFactory = nullptr;
		ID2D1Device* m_pD2DDevice = nullptr;
		//ID2D1DeviceContext* m_pD2DDeviceContex = nullptr;
		IWICImagingFactory2* m_pWICImagingFactory = nullptr;

	public:
		static IrisD2DResourceManager* Instance();

	private:
		IrisD2DResourceManager() = default;
		//bool IrisD2DResourceManager::LoadWICResource(const std::wstring& wstrUri, IWICFormatConverter*& pConverter, unsigned int& nWidth, unsigned int& nHeight);
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

		ID2D1Factory1* GetD2DFactory();

		bool Release();

		~IrisD2DResourceManager() = default;
	};


}
#endif // !_H_IRISD2DRESOURCEMANAGER_
