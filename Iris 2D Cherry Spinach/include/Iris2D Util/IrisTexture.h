#ifndef _H_IRISTEXTURE_
#define _H_IRISTEXTURE_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisTexture
	{
	private:
		ID3D11ShaderResourceView* m_pTextureResource = nullptr;
		ID3D11Resource* m_pTexture = nullptr;

		ID2D1RenderTarget* m_pRenderTargetBitmap = nullptr;
		//ID2D1Bitmap* m_pBitmap = nullptr;
		HANDLE m_hSharedResourceHandle = nullptr;

		IDXGIKeyedMutex* m_pDX11Mutex = nullptr;
		IDXGIKeyedMutex* m_pDX10Mutex = nullptr;
		
	private:
		static ID3D11SamplerState* sm_pDefaultSamplerState;
		static ID3D11BlendState* sm_pDefaultBlendState;

	public:
		static IrisTexture* Create(const std::wstring& wstrTexturePath);
		static IrisTexture* Create(unsigned int nWidth, unsigned int nHeight);

		static bool Initialize();
		static bool Release();
		static void Release(IrisTexture*& pTexture);

	private:

		bool m_bDX10MutexRequired = false;
		bool m_bDX11MutexRequired = false;

		IrisTexture() = default;
		~IrisTexture();

	public:
		ID3D11ShaderResourceView* GetShaderResourceView();
		static ID3D11SamplerState* GetDefaultSamplerState();

		void AquireSyncFromDx11Side();
		void ReleaseSyncFromDx11Side();

		void AquireSyncFromDx10Side();
		void ReleaseSyncFromDx10Side();

		ID3D11Resource* GetTexture();
		ID2D1RenderTarget* GetRenderTargetBitmap();
		//ID2D1Bitmap* GetD2DBitmap();
	};
}
#endif // !_H_IRISTEXTURE_
