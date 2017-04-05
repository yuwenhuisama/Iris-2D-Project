#include "Iris2D\IrisD2DResourceManager.h"
#include "Iris2D\IrisD3DResourceManager.h"

namespace Iris2D
{
	IrisD2DResourceManager * IrisD2DResourceManager::Instance()
	{
		static auto pInstance = IrisD2DResourceManager();
		return &pInstance;
	}

	bool IrisD2DResourceManager::Initialize()
	{
		auto hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hResult)) {
			return false;
		}

		CoInitialize(nullptr);
		hResult = CoCreateInstance(CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<LPVOID*>(&m_pWICImagingFactory));

		if (FAILED(hResult)) {
			return false;
		}

		return true;
	}

	bool IrisD2DResourceManager::LoadWICResource(const std::wstring& wstrUri, IWICBitmapFrameDecode*& pSource, IWICFormatConverter*& pConverter) {

		IWICBitmapDecoder* pDecoder = nullptr;

		// Load Picture
		auto hResult = m_pWICImagingFactory->CreateDecoderFromFilename(
			wstrUri.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);

		if (FAILED(hResult)) {
			goto failed_release;
		}

		hResult = pDecoder->GetFrame(0, &pSource);
		if (FAILED(hResult))
		{
			goto failed_release;
		}

		hResult = m_pWICImagingFactory->CreateFormatConverter(&pConverter);
		if (FAILED(hResult))
		{
			goto failed_release;
		}

		hResult = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
		if (FAILED(hResult))
		{
			goto failed_release;
		}

		SafeCOMRelease(pDecoder);
		return true;

	failed_release:

		SafeCOMRelease(pDecoder);
		return false;
	}

	bool IrisD2DResourceManager::CreateTexture(IWICBitmapFrameDecode*& pSource, ID3D11Resource*& pTexture) {
		// CreateTexture
		unsigned int nWidth = 0;
		unsigned int nHeight = 0;
		pSource->GetSize(&nWidth, &nHeight);

		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.ArraySize = 1;
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		texDesc.Height = nHeight;
		texDesc.Width = nWidth;
		texDesc.MipLevels = 1;
		texDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		
		ID3D11Texture2D* pTmpTexture = nullptr;
		auto hResult = IrisD3DResourceManager::Instance()->GetD3D11Device()->CreateTexture2D(&texDesc, nullptr, &pTmpTexture);
		if (FAILED(hResult)) {
			SafeCOMRelease(pSource);
			SafeCOMRelease(pTmpTexture);
			return false;;
		}

		hResult = pTmpTexture->QueryInterface(IID_ID3D11Resource, (void **)&pTexture);
		if (FAILED(hResult)) {
			SafeCOMRelease(pSource);
			SafeCOMRelease(pTmpTexture);
			SafeCOMRelease(pTexture);
		}

		SafeCOMRelease(pTmpTexture);
		SafeCOMRelease(pSource);
		return true;
	}

	bool IrisD2DResourceManager::MakeSharedResource(ID3D11Resource* pTexture, HANDLE& hResourceShareHandle, IDXGIKeyedMutex*& pDX11Mutex) {
		pDX11Mutex = nullptr;
		auto hResult = pTexture->QueryInterface(__uuidof(IDXGIKeyedMutex), (LPVOID*)&pDX11Mutex);
		if (FAILED(hResult) || (pDX11Mutex == nullptr)) {
			goto failed_release;
			return false;
		}

		IDXGIResource* pDXGIResource = nullptr;
		hResult = pTexture->QueryInterface(__uuidof(IDXGIResource), reinterpret_cast<LPVOID*>(&pDXGIResource));
		if (FAILED(hResult)) {
			goto failed_release;
		}

		hResourceShareHandle = nullptr;
		hResult = pDXGIResource->GetSharedHandle(&hResourceShareHandle);
		if (FAILED(hResult)) {
			goto failed_release;
		}

		//SafeCOMRelease(pDXGIKeyedMutex);
		SafeCOMRelease(pDXGIResource);

		return true;

	failed_release:

		SafeCOMRelease(pDX11Mutex);
		SafeCOMRelease(pDXGIResource);

		return false;
	}

	bool IrisD2DResourceManager::CreateDxgiRenderTarget(HANDLE hResourceShareHandle, ID2D1RenderTarget*& pDxgiRenderTarget, IDXGIKeyedMutex*& pDX10Mutex) {
		// CreateRenderTarget
		IDXGISurface1* pDxgiSurface = nullptr;
		auto hResult = IrisD3DResourceManager::Instance()->GetD3D10Device()->OpenSharedResource(hResourceShareHandle, __uuidof(IDXGISurface1), reinterpret_cast<LPVOID*>(&pDxgiSurface));
		if (FAILED(hResult)) {
			goto failed_release;
		}

		pDX10Mutex = nullptr;
		hResult = pDxgiSurface->QueryInterface(__uuidof(IDXGIKeyedMutex), reinterpret_cast<LPVOID*>(&pDX10Mutex));
		if (FAILED(hResult) || pDX10Mutex == nullptr) {
			goto failed_release;
		}

		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		m_pD2DFactory->GetDesktopDpi(&fDpiX, &fDpiY);
		auto dsProps = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			fDpiX,
			fDpiY
		);

		hResult = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
			pDxgiSurface,
			&dsProps,
			&pDxgiRenderTarget
		);
		if (FAILED(hResult)) {
			goto failed_release;
		}

		SafeCOMRelease(pDxgiSurface);

		return true;

	failed_release:

		SafeCOMRelease(pDxgiSurface);
		SafeCOMRelease(pDX10Mutex);
		SafeCOMRelease(pDxgiRenderTarget);
		return false;
	}

	bool IrisD2DResourceManager::LoadBitmapFromFile(
		const std::wstring& wstrUri, 
		ID2D1RenderTarget*& pDxgiRenderTarget, 
		ID3D11Resource*& pTexture, 
		ID2D1Bitmap*& pBitmap, 
		HANDLE& hResourceShareHandle,
		IDXGIKeyedMutex*& pDX10Mutex,
		IDXGIKeyedMutex*& pDX11Mutex)
	{
		IWICBitmapFrameDecode* pSource = nullptr;
		IWICFormatConverter* pConverter = nullptr;
		
		pBitmap = nullptr;
		pDxgiRenderTarget = nullptr;
		pTexture = nullptr;
		hResourceShareHandle = nullptr;

		if (!LoadWICResource(wstrUri, pSource, pConverter)) {
			return false;
		}

		if (!CreateTexture(pSource, pTexture)) {
			return false;
		}

		if (!MakeSharedResource(pTexture, hResourceShareHandle, pDX11Mutex)) {
			return false;
		}

		if (!CreateDxgiRenderTarget(hResourceShareHandle, pDxgiRenderTarget, pDX10Mutex)) {
			return false;
		}

		// Create Bitmap
		auto hResult = pDxgiRenderTarget->CreateBitmapFromWicBitmap(pConverter, &pBitmap);
		if (FAILED(hResult)) {
			SafeCOMRelease(pBitmap);
			SafeCOMRelease(pConverter);
			return false;
		}
		SafeCOMRelease(pConverter);

		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		m_pD2DFactory->GetDesktopDpi(&fDpiX, &fDpiY);
		auto dsProps = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			fDpiX,
			fDpiY
		);

		//Render
		hResult = pDX10Mutex->AcquireSync(0, INFINITE);

		pDxgiRenderTarget->BeginDraw();
		pDxgiRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		auto siSize = pBitmap->GetSize();
		auto ptTop = D2D1::Point2F(0.0f, 0.0f);

		pDxgiRenderTarget->DrawBitmap(pBitmap,
			D2D1::RectF(
				ptTop.x,
				ptTop.y,
				ptTop.x + siSize.width,
				ptTop.y + siSize.height
			)
		);

		hResult = pDxgiRenderTarget->EndDraw();
		if (FAILED(hResult)) {
			return false;
		}

		hResult = pDX10Mutex->ReleaseSync(1);

		if (FAILED(hResult)) {
			return false;
		}

		return true;

	}

	bool IrisD2DResourceManager::Release()
	{
		SafeCOMRelease(m_pD2DFactory);
		SafeCOMRelease(m_pWICImagingFactory);
		return true;
	}
}
