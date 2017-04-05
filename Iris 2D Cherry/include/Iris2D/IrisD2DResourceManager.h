#ifndef _H_IRISD2DRESOURCEMANAGER_
#define _H_IRISD2DRESOURCEMANAGER_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisD2DResourceManager
	{
	private:
		ID2D1Factory* m_pD2DFactory = nullptr;
		IWICImagingFactory* m_pWICImagingFactory = nullptr;

	public:
		static IrisD2DResourceManager* Instance();

	private:
		IrisD2DResourceManager() = default;
		bool LoadWICResource(const std::wstring& wstrUri, IWICBitmapFrameDecode*& pSource, IWICFormatConverter*& pConverter);
		bool CreateTexture(IWICBitmapFrameDecode*& pSource, ID3D11Resource*& pTexture);
		bool MakeSharedResource(ID3D11Resource* pTexture, HANDLE& hResourceShareHandle, IDXGIKeyedMutex*& pDX11Mutex);
		bool CreateDxgiRenderTarget(HANDLE hResourceShareHandle, ID2D1RenderTarget*& pDxgiRenderTarget, IDXGIKeyedMutex*& pDX10Mutex);

	public:
		bool Initialize();

		bool LoadBitmapFromFile(const std::wstring& wstrUri, 
			ID2D1RenderTarget*& pDxgiRenderTarget, 
			ID3D11Resource*& pTexture,
			ID2D1Bitmap*& pBitmap, 
			HANDLE& hResourceShareHandle,
			IDXGIKeyedMutex*& pDX10Mutex,
			IDXGIKeyedMutex*& pDX11Mutex
		);

		bool Release();

		~IrisD2DResourceManager() = default;
	};


}
#endif // !_H_IRISD2DRESOURCEMANAGER_
