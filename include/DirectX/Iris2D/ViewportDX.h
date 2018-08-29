#ifndef _H_VIEWPORT_DX_
#define _H_VIEWPORT_DX_

#include "DirectX/Common.h"
#include "DirectX/Util/ViewportShaderBuffersDX.h"
#include "Common/Iris2D/IViewport.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D
{
	class SpriteDX;

	class Sprite;
	class Rect;
	class TextureDX;
	class Rect;
	class Color;
	class Viewport;

	__declspec(align(16))
	class ViewportDX : public IViewport, public Proxied<Viewport>, public RefCounter
	{
	private:
		std::unordered_set<SpriteDX*> m_stSprits;

		ID3D11Buffer* m_pVertexBuffer = nullptr;
		TextureDX* m_pTexture = nullptr;

		ViewportVertexShaderBufferDX m_ivvsVertexBuffer;
		ViewportPixelShaderBufferDX m_ivpsPixelBuffer;

		//DirectX::XMMATRIX m_mxViewProjMatrix = DirectX::XMMatrixIdentity();

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;

		bool m_bVertexBufferDirtyFlag = false;
		bool m_bVisible = true;

		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		bool m_bSrcRectDirtyFlag = false;
		bool m_bToneDirtyFlag = false;

	public:
		static Viewport* sm_pGlobalViewport;

	public:
		static ViewportDX* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight);

		static ViewportDX* Create(const Rect* pRect);
		static void Release(ViewportDX*& pViewport);

		static void ForceRelease(ViewportDX*& pViewport);

		static bool InitGlobalViewport(unsigned int nWindowWidth, unsigned int nWindowHeight);
		static void ReleaseGlobalViewport();
		static Viewport* GetGlobalViewport();

	public:

		void SetOX(float fOX) override;
		float GetOX() const override;

		void SetOY(float fOY) override;
		float GetOY() const override;

		void SetSrcRect(Rect*& pSrcRect) override;
		Rect* GetSrcRect() const override;

		void SetTone(Tone*& pTone) override;
		Tone* GetTone() const override;

		bool Dispose();
		bool RenderSprite();
		bool RenderSelf();

		void AddSprite(SpriteDX* pSprite);
		void RemoveSprite(SpriteDX* pSprite);

		void SetZ(float fOZ) override;
		float GetZ() override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

	private:
		bool CreateViewportVertexBuffer(unsigned int nWidth, unsigned int nHeight);

		ViewportDX() = default;
		~ViewportDX();

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

#endif // !_H_VIEWPORT_DX_
