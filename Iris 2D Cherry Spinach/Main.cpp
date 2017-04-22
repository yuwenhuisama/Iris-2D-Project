/*!
 * @brief	Direct3D 11 と Direct2D を相互運用するサンプル。
 * @date	2010/01/20
 * @author	御津凪
 */

//! UNICODE 用なので非 UNICODE ならばエラー。
#if !defined(UNICODE) && !defined(_UNICODE)
#error This is only for Unicode. It is necessary to compile with Unicode.
#endif

//! インクルードするヘッダファイル
#include <d3d11.h>
#include <d3d10_1.h>
#include <d2d1.h>
//#include <dxerr.h>
#include <wchar.h>
#include <stdarg.h>
#include <math.h>

#include <IrisCommon.h>

//! 使用するライブラリファイル
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3d10_1.lib")
#pragma comment (lib, "d2d1.lib")
//#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxgi.lib")

//! ウインドウクラス名
#define WNDCLASSNAME L"D3D2D"

//! プロトタイプ宣言
static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
static inline bool register_window_class( HINSTANCE hInstance );
static inline HWND create_window( HINSTANCE hInstance, UINT nWidth, UINT nHeight, bool bCentering );
static bool peek_message( void );

static inline void main_d2d( ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush );
static inline void main_d3d( ID3D11DeviceContext* pImmContext, ID3D11Texture2D* pBuckBuffer, ID3D11Texture2D* pTexture );

static int error_message( LPCWSTR lpTitle, LPCWSTR lpFormat, ... );
static int error_message_v( LPCWSTR lpTitle, LPCWSTR lpFormat, va_list va );
static inline int error_message_hr( LPCWSTR lpTitle, HRESULT hResult );

//! 自前 COM ポインタ(簡易)
template<class T> class ResPtr {
public:
	typedef ResPtr<T>	self_t;

	ResPtr( void ) : mPtr(NULL){ }
	~ResPtr( void ) { if(mPtr) mPtr->Release(); }

	operator T*( void ) const { return mPtr; }
	T** operator&( void ) { return &mPtr; }
	bool operator!( void ) const { return !mPtr; }

	const self_t& operator=( T* inPtr ) const { Set(inPtr); return *this; }
	const self_t& operator=( const self_t& inPtr ) const { Set(inPtr); return *this; }

	void Set( const self_t& inPtr ) const {
		if(mPtr) mPtr->Release();
		mPtr = inPtr.mPtr;
		if(mPtr) mPtr->AddRef();
	}
	void Set( T* inPtr ) const {
		if(mPtr) mPtr->Release();
		mPtr = inPtr;
		if(mPtr) mPtr->AddRef();
	}

	T* operator->() const { return mPtr; }
	T* Get() const { return mPtr; }

private:
	mutable T*	mPtr;
};

ResPtr<ID3D11Device>			device11;
ResPtr<IDXGISwapChain>			swapchain;
ResPtr<ID3D11Texture2D>			backbuffer;
ResPtr<ID3D11Texture2D>			texture11;
ResPtr<ID3D11DeviceContext>		immcontext;
ResPtr<IDXGIKeyedMutex>			keyedmutex11;

ResPtr<ID3D10Device1>			device101;
ResPtr<IDXGIKeyedMutex>			keyedmutex10;

ResPtr<ID2D1RenderTarget>		rendertarget;
ResPtr<ID2D1SolidColorBrush>	brush;


//! メインエントリポイント
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	HWND	hWnd;
	HRESULT	hr;

	// ウインドウ作成部分
	if (!register_window_class(hInstance))
	{
		return error_message(L"register_window_class", L"ウインドウクラスの登録に失敗");
	}
	hWnd = create_window(hInstance, 640, 480, true);
	if (hWnd == NULL)
	{
		return error_message(L"create_window", L"ウインドウの生成に失敗");
	}


	// 各デバイスの作成
	{
		ResPtr<ID2D1Factory>	d2dfactory;
		ResPtr<IDXGIAdapter1>	adapter;
		ResPtr<IDXGISurface1>	surface10;
		HANDLE					sharedHandle;

		// アダプタを取得
		{
			ResPtr<IDXGIFactory1> dxgiFactory;
			if FAILED(hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (LPVOID*)&dxgiFactory))
			{
				return error_message_hr(L"CreateDXGIFactory1", hr);
			}
			if FAILED(hr = dxgiFactory->EnumAdapters1(0, &adapter))
			{
				return error_message_hr(L"IDXGIFactory1::EnumAdapters1", hr);
			}
		}
		// D3D 11 を スワップチェインと共に作成
		{
			DXGI_SWAP_CHAIN_DESC	scd;
			ZeroMemory(&scd, sizeof(scd));
			scd.BufferDesc.Format	= DXGI_FORMAT_B8G8R8A8_UNORM;
			scd.SampleDesc.Count	= 1;
			scd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.BufferCount			= 1;
			scd.OutputWindow		= hWnd;
			scd.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;
			scd.Windowed			= TRUE;

			// D3D 11 デバイス生成時、 D3D_DRIVER_TYPE_UNKNOWN を指定しないと
			// うまくいかないことがある。
			// また、 D2D を使用する場合は D3D11_CREATE_DEVICE_BGRA_SUPPORT を
			// 指定する必要がある。
			hr = D3D11CreateDeviceAndSwapChain(
				adapter,
				D3D_DRIVER_TYPE_UNKNOWN,
				NULL,
				D3D11_CREATE_DEVICE_BGRA_SUPPORT,
				NULL,
				0,
				D3D11_SDK_VERSION,
				&scd,
				&swapchain,
				&device11,
				NULL,
				&immcontext
			);
			if FAILED(hr)
			{
				return error_message_hr(L"D3D11CreateDeviceAndSwapChain", hr);
			}
		}
		// D3D 10.1 を作成
		{
			// D3D10_DRIVER_TYPE_HARDWARE と D3D10_CREATE_DEVICE_BGRA_SUPPORT は必ず指定。
			// なお、こちらの環境では D3D10_FEATURE_LEVEL_9_3 にしないと動作しませんでした。
			hr = D3D10CreateDevice1(
				adapter,
				D3D10_DRIVER_TYPE_HARDWARE,
				NULL,
				D3D10_CREATE_DEVICE_BGRA_SUPPORT,
				D3D10_FEATURE_LEVEL_9_3,
				D3D10_1_SDK_VERSION,
				&device101
			);
			if FAILED(hr)
			{
				return error_message_hr(L"D3D10CreateDevice1", hr);
			}
		}
		// D2DFactory の生成
		{
			if FAILED(hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), (LPVOID*)&d2dfactory))
			{
				return error_message_hr(L"D2D1CreateFactory", hr);
			}
		}

		// 共有するテクスチャを D3D 11 から用意。
		// ここではバックバッファと同じサイズのテクスチャを作成。
		{
			D3D11_TEXTURE2D_DESC	bbd, std;

			if FAILED(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer)) {
				return error_message_hr(L"IDXGISwapChain::GetBuffer", hr);
			}
			backbuffer->GetDesc(&bbd);

			// 作成するテクスチャ情報の設定。
			// ・DXGI_FORMAT_B8G8R8A8_UNORM は固定。
			// ・D3D11_BIND_RENDER_TARGET は D2D での描画対象とするために必須。
			// ・D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX はテクスチャを共有するのに必須。
			ZeroMemory(&std, sizeof(std));
			std.Width				= bbd.Width;
			std.Height				= bbd.Height;
			std.MipLevels			= 1;
			std.ArraySize			= 1;
			std.Format				= DXGI_FORMAT_B8G8R8A8_UNORM;
			std.SampleDesc.Count	= 1;
			std.Usage				= D3D11_USAGE_DEFAULT;
			std.BindFlags			= D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			std.MiscFlags			= D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
			if FAILED(device11->CreateTexture2D(&std, NULL, &texture11))
			{
				return error_message_hr(L"ID3D11Texture2D::CreateTexture2D", hr);
			}
		}
		// 共有するための D3D 11 のキーミューテックスを取得
		if FAILED(texture11->QueryInterface(__uuidof(IDXGIKeyedMutex), (LPVOID*)&keyedmutex11))
		{
			return error_message_hr(L"ID3D11Texture2D::QueryInterface(IDXGIResource)", hr);
		}
		// 共有のためのハンドルを取得。
		{
			ResPtr<IDXGIResource> resource11;
			if FAILED(texture11->QueryInterface(__uuidof(IDXGIResource), (LPVOID*)&resource11))
			{
				return error_message_hr(L"ID3D11Texture2D::QueryInterface(IDXGIResource)", hr);
			}
			if FAILED(resource11->GetSharedHandle(&sharedHandle))
			{
				return error_message_hr(L"IDXGIResource::GetSharedHandle", hr);
			}
		}
		// D3D 10.1 で共有サーフェイスを生成。
		if FAILED(hr = device101->OpenSharedResource(sharedHandle, __uuidof(IDXGISurface1), (LPVOID*)&surface10))
		{
			return error_message_hr(L"ID3D10Device1::OpenSharedResource(IDXGISurface1)", hr);
		}
		// 共有するための D3D 10.1 のキーミューテックスを取得
		if FAILED(surface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (LPVOID*)&keyedmutex10))
		{
			return error_message_hr(L"IDXGISurface1::QueryInterface(IDXGIKeyedMutex)", hr);
		}
		// D2D のレンダーターゲットを D3D 10.1 の共有サーフェイスから生成。
		{
			D2D1_RENDER_TARGET_PROPERTIES	rtp;
			ZeroMemory(&rtp, sizeof(rtp));
			rtp.type		= D2D1_RENDER_TARGET_TYPE_HARDWARE;
			rtp.pixelFormat	= D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
			if FAILED(d2dfactory->CreateDxgiSurfaceRenderTarget(surface10, &rtp, &rendertarget))
			{
				return error_message_hr(L"ID2D1Factory::CreateDxgiSurfaceRenderTarget", hr);
			}
		}
	}
	// ここで共有の準備は整います。

	// D2D の描画用ブラシを生成
	if FAILED(hr = rendertarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f, 1.0f), &brush))
	{
		return error_message_hr(L"ID2D1RenderTarget::CreateSolidColorBrush", hr);
	}

	// ウインドウを表示。
	ShowWindow(hWnd, SW_SHOW);

	// ここからメインループ。
	while (peek_message())
	{
		// D3D 10.1 (D2D) 側のテクスチャの使用を開始。
		keyedmutex10->AcquireSync(0, INFINITE);

		// D2D 側の処理
		main_d2d(rendertarget, brush);

		// D3D 10.1 (D2D) 側のテクスチャの使用を完了。
		keyedmutex10->ReleaseSync(1);
		// D3D 11 側のテクスチャの使用を開始。

		DirectX::ScratchImage siImage;
		DirectX::CaptureTexture(device11, immcontext, texture11, siImage);
		auto hResult = DirectX::SaveToWICFile(*siImage.GetImage(0, 0, 0), DirectX::WIC_FLAGS_ALL_FRAMES, GUID_ContainerFormatPng, L"test.png", &GUID_WICPixelFormat32bppBGRA);

		keyedmutex11->AcquireSync(1, INFINITE);

		// D3D 側の処理
		main_d3d(immcontext, backbuffer, texture11);

		// D3D 11 側のテクスチャの使用を完了。
		keyedmutex11->ReleaseSync(0);

		// バックバッファを転送。
		swapchain->Present(1, 0);
	}

	// 後始末。

	swapchain->SetFullscreenState(FALSE, NULL);

	immcontext->ClearState();

	return 0;
}

// ウインドウプロシージャ
static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			// Esc キーを押したら終了する。
			if (LOWORD(wParam) == VK_ESCAPE) { DestroyWindow(hWnd); }
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


//! ウインドウクラスの登録
static inline bool register_window_class( HINSTANCE hInstance )
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize			= sizeof(wc);
	wc.lpszClassName	= WNDCLASSNAME;
	wc.hInstance		= hInstance;
	wc.lpfnWndProc		= WndProc;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);

	return (RegisterClassEx(&wc) != 0);
}

//! ウインドウの作成
static inline HWND create_window( HINSTANCE hInstance, UINT nWidth, UINT nHeight, bool bCentering )
{
	HWND hWnd = CreateWindow(
		WNDCLASSNAME,
		L"Direct3D 11 と Direct2D 動作サンプル",
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nWidth,
		nHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hWnd != NULL)
	{
		// スクリーンサイズ調整
		RECT	cr, wr;
		UINT	w, h;
		DWORD	flag = (bCentering ? 0 : SWP_NOMOVE);

		GetWindowRect(hWnd, &wr);
		GetClientRect(hWnd, &cr);
		w = nWidth + wr.right - wr.left - cr.right + cr.left;
		h = nHeight + wr.bottom - wr.top - cr.bottom + cr.top;
		SetWindowPos(
			hWnd,
			HWND_TOP,
			(GetSystemMetrics(SM_CXSCREEN) - w) >> 1,
			(GetSystemMetrics(SM_CYSCREEN) - h) >> 1,
			w, h, flag
		);
	}
	return hWnd;
}

//! メッセージ処理
static bool peek_message( void )
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return true;
}

//! D2D 側の描画
static inline void main_d2d( ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush )
{
	static float	angle = 0.0f;
	const float		strokeWidth = 16.0f;

	D2D1_SIZE_F		size;
	D2D1_POINT_2F	pos_size_2;

	angle += 0.005f;

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.7f, 0.0f, 1.0f));

	// サイズ等計算
	size = pRenderTarget->GetSize();
	pos_size_2.x = size.width / 2.0f; pos_size_2.y = size.height / 2.0f;

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(cosf(angle) * 2000, pos_size_2));

	pBrush->SetColor(D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.5f));
	pRenderTarget->DrawLine(
		D2D1::Point2F(pos_size_2.x - size.height * 0.4f, pos_size_2.y),
		D2D1::Point2F(pos_size_2.x + size.height * 0.4f, pos_size_2.y),
		pBrush, strokeWidth);

	pBrush->SetColor(D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.5f));
	pRenderTarget->DrawLine(
		D2D1::Point2F(pos_size_2.x, pos_size_2.y - size.height * 0.4f),
		D2D1::Point2F(pos_size_2.x, pos_size_2.y + size.height * 0.4f),
		pBrush, strokeWidth);

	pRenderTarget->EndDraw();

	return;
}
//! D3D 11 側の描画
static inline void main_d3d( ID3D11DeviceContext* pImmContext, ID3D11Texture2D* pBuckBuffer, ID3D11Texture2D* pTexture )
{
	// ここでは D2D で共有テクスチャに描画されたデータをバックバッファに転送しています。
	pImmContext->CopyResource(pBuckBuffer, pTexture);
}

//! エラーメッセージ表示
static int error_message( LPCWSTR lpTitle, LPCWSTR lpFormat, ... )
{
	va_list	va;
	va_start(va, lpFormat);
	error_message_v(lpTitle, lpFormat, va);
	va_end(va);
	return -1;
}
//! エラーメッセージ表示
static int error_message_v( LPCWSTR lpTitle, LPCWSTR lpFormat, va_list va )
{
	wchar_t	buffer[512];
	vswprintf_s(buffer, lpFormat, va);
	MessageBox(NULL, buffer, lpTitle, MB_APPLMODAL | MB_ICONERROR | MB_OK);
	OutputDebugString(buffer);
	OutputDebugString(L"\n");
	return -1;
}
//! エラーメッセージ表示
static inline int error_message_hr( LPCWSTR lpTitle, HRESULT hResult )
{
	//return error_message(lpTitle, DXGetErrorDescription(hResult));
	return 0;
}
