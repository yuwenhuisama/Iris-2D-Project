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
		auto hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), reinterpret_cast<void**>(&m_pD2DFactory));
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pD2DFactory);
			return false;
		}

		//*********************
		//IDXGIDevice1* pDxgiDevice = nullptr;
		//hResult = IrisD3DResourceManager::Instance()->GetD3D11Device()->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDxgiDevice));
		//if (FAILED(hResult)) {
		//	SafeCOMRelease(m_pD2DFactory);
		//	SafeCOMRelease(pDxgiDevice);
		//	return false;
		//}

		//hResult = m_pD2DFactory->CreateDevice(pDxgiDevice, &m_pD2DDevice);
		//if (FAILED(hResult)) {
		//	SafeCOMRelease(m_pD2DDevice);
		//	SafeCOMRelease(m_pD2DFactory);
		//	return false;
		//}
		//SafeCOMRelease(pDxgiDevice);

		//hResult = m_pD2DDevice->CreateDeviceContext(
		//	D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		//	&m_pD2DDeviceContex
		//	);
		//if (FAILED(hResult)) {
		//	SafeCOMRelease(m_pD2DDevice);
		//	SafeCOMRelease(m_pD2DFactory);
		//	SafeCOMRelease(m_pD2DDeviceContex);
		//	return false;
		//}
		//*********************

		CoInitialize(nullptr);
		hResult = CoCreateInstance(CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory2,
			reinterpret_cast<LPVOID*>(&m_pWICImagingFactory));

		if (FAILED(hResult)) {
			return false;
		}

		return true;
	}

	bool IrisD2DResourceManager::LoadWICResource(const std::wstring& wstrUri, IWICFormatConverter*& pConverter, unsigned int& nWidth, unsigned int& nHeight) {

		IWICBitmapDecoder* pDecoder = nullptr;
		IWICBitmapFrameDecode* pSource = nullptr;
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

		pSource->GetSize(&nWidth, &nHeight);

		hResult = m_pWICImagingFactory->CreateFormatConverter(&pConverter);
		if (FAILED(hResult))
		{
			goto failed_release;
		}

		hResult = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);
		if (FAILED(hResult))
		{
			goto failed_release;
		}

		SafeCOMRelease(pDecoder);
		SafeCOMRelease(pSource);
		return true;

	failed_release:

		SafeCOMRelease(pDecoder);
		SafeCOMRelease(pSource);
		return false;
	}

	bool IrisD2DResourceManager::CreateTexture(unsigned int nWidth, unsigned int nHeight, ID3D11Resource*& pTexture) {
		// CreateTexture
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
			SafeCOMRelease(pTmpTexture);
			return false;;
		}

		hResult = pTmpTexture->QueryInterface(IID_ID3D11Resource, (void **)&pTexture);
		if (FAILED(hResult)) {
			SafeCOMRelease(pTmpTexture);
			SafeCOMRelease(pTexture);
		}

		SafeCOMRelease(pTmpTexture);
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
		HANDLE& hResourceShareHandle,
		IDXGIKeyedMutex*& pDX10Mutex,
		IDXGIKeyedMutex*& pDX11Mutex)
	{
		IWICBitmapFrameDecode* pSource = nullptr;
		IWICFormatConverter* pConverter = nullptr;

		ID2D1Bitmap* pBitmap = nullptr;
		pDxgiRenderTarget = nullptr;
		pTexture = nullptr;
		hResourceShareHandle = nullptr;

		unsigned int nWidth = 0;
		unsigned int nHeight = 0;

		if (!LoadWICResource(wstrUri, pConverter, nWidth, nHeight)) {
			return false;
		}

		if (!CreateTexture(nWidth, nHeight, pTexture)) {
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
		SafeCOMRelease(pBitmap);
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
			pDX10Mutex->ReleaseSync(1);
			return false;
		}

		hResult = pDX10Mutex->ReleaseSync(1);

		if (FAILED(hResult)) {
			return false;
		}

		return true;

	}
	/*
	bool IrisD2DResourceManager::LoadBitmapFromFileEx(const std::wstring & wstrUri, ID3D11Resource *& pTexture, HANDLE & hResourceShareHandle, IDXGIKeyedMutex *& pDX10Mutex, IDXGIKeyedMutex *& pDX11Mutex)
	{
		IWICBitmapFrameDecode* pSource = nullptr;
		IWICFormatConverter* pConverter = nullptr;

		//pDxgiRenderTarget = nullptr;
		pTexture = nullptr;
		hResourceShareHandle = nullptr;

		unsigned int nWidth = 0;
		unsigned int nHeight = 0;

		if (!LoadWICResource(wstrUri, pConverter, nWidth, nHeight)) {
			return false;
		}

		if (!CreateTexture(nWidth, nHeight, pTexture)) {
			return false;
		}

		IDXGISurface* pSurface = nullptr;
		auto hResult = pTexture->QueryInterface(IID_IDXGISurface, (void**)&pSurface);

		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		m_pD2DFactory->GetDesktopDpi(&fDpiX, &fDpiY);
		auto dsProps = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			fDpiX,
			fDpiY
		);

		D2D1_BITMAP_PROPERTIES1 dbp1;
		dbp1.pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE };
		dbp1.colorContext = nullptr;
		dbp1.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;
		dbp1.dpiX = fDpiX;
		dbp1.dpiY = fDpiY;

		ID2D1Bitmap1* pRenderBitmap = nullptr;
		hResult = m_pD2DDeviceContex->CreateBitmapFromDxgiSurface(pSurface, dbp1, &pRenderBitmap);

		ID2D1Bitmap1* pBitmap = nullptr;
		hResult = m_pD2DDeviceContex->CreateBitmapFromWicBitmap(pConverter, &pBitmap);

		m_pD2DDeviceContex->SetTarget(pRenderBitmap);
		m_pD2DDeviceContex->BeginDraw();
		m_pD2DDeviceContex->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		auto siSize = pBitmap->GetSize();
		auto ptTop = D2D1::Point2F(0.0f, 0.0f);

		m_pD2DDeviceContex->DrawBitmap(pBitmap,
			D2D1::RectF(
				ptTop.x,
				ptTop.y,
				ptTop.x + siSize.width,
				ptTop.y + siSize.height
			)
		);

		hResult = m_pD2DDeviceContex->EndDraw();

		return true;
	}
	*/

	bool IrisD2DResourceManager::CreateBlankTexture(unsigned int nWidth, unsigned int nHeight, ID2D1RenderTarget*& pDxgiRenderTarget, ID3D11Resource *& pTexture, HANDLE & hResourceShareHandle, IDXGIKeyedMutex *& pDX10Mutex, IDXGIKeyedMutex *& pDX11Mutex)
	{
		if (!CreateTexture(nWidth, nHeight, pTexture)) {
			return false;
		}

		if (!MakeSharedResource(pTexture, hResourceShareHandle, pDX11Mutex)) {
			return false;
		}

		if (!CreateDxgiRenderTarget(hResourceShareHandle, pDxgiRenderTarget, pDX10Mutex)) {
			return false;
		}

		// Create Bitmap
		D2D1_SIZE_U dsuSize;
		dsuSize.width = nWidth;
		dsuSize.width = nHeight;

		float fDpiX = 0.0f;
		float fDpiY = 0.0f;
		m_pD2DFactory->GetDesktopDpi(&fDpiX, &fDpiY);
		auto dsProps = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			fDpiX,
			fDpiY
		);

		D2D1_BITMAP_PROPERTIES dbpProperties;
		dbpProperties.dpiX = fDpiX;
		dbpProperties.dpiY = fDpiY;
		dbpProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		dbpProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

		HRESULT hResult = S_OK;

		//Render
		hResult = pDX10Mutex->AcquireSync(0, INFINITE);

		pDxgiRenderTarget->BeginDraw();
		pDxgiRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black, 0.0f));

		hResult = pDxgiRenderTarget->EndDraw();
		if (FAILED(hResult)) {
			pDX10Mutex->ReleaseSync(1);
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
