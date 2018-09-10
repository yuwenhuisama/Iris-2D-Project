#ifndef _H_SPRITE_DX_
#define _H_SPRITE_DX_

#include "DirectX/Common.h"
#include "DirectX/Util/SpriteShaderBuffersDX.h"

#include "Common/Iris2D/Sprites/ISpriteStatic.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D
{
	class BitmapDX;
	class RectDX;
	class ColorDX;
	class ViewportDX;

	class Bitmap;
	class Rect;
	class Color;
	class Viewport;

	typedef ColorDX ToneDX;
	__declspec(align(16))
	class SpriteDX : public Proxied<ISprite>, public ISpriteStatic, public RefCounter
	{
	private:

		const float c_fPI = 3.14159f;
		const float c_fArcUnit = c_fPI / 180.0f;

		Bitmap* m_pBitmap = nullptr;
		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		ID3D11Buffer* m_pVertexBuffer = nullptr;

		SpriteVertexShaderBufferDX m_bfVertexShaderBuffer;
		SpritePixelShaderBufferDX  m_bfPixelShaderBuffer;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;
		float m_fAngle = 0.0f;
		float m_fZoomX = 1.0f;
		float m_fZoomY = 1.0f;

		bool m_bVisible = true;
		Viewport* m_pViewport = nullptr;

		bool m_bPositionDirtyFlag = false;
		bool m_bAngleDirtyFlag = false;
		bool m_bZoomDirtyFlag = false;
		bool m_bSrcRectDirtyFlag = false;
		bool m_bToneDirtyFlag = false;

	public:
		static SpriteDX* Create(Viewport* pViewport = nullptr);

		static void Release(SpriteDX*& pSprite);

		static void ForceRelease(SpriteDX* pSprite);

	public:

		ResultCode SetBitmap(Bitmap*& pBitmap) override;
		Bitmap* GetBitmap() const override;

		void SetX(float fX) override;
		float GetX() const override;

		void SetY(float fY) override;
		float GetY() const override;

		void SetZ(float fZ) override;
		float GetZ() const override;

		void SetAngle(float fAngle) override;
		float GetAngle() const override;

		void SetZoomX(float fZoomX) override;
		float GetZoomX() const override;

		void SetZoomY(float fZoomY) override;
		float GetZoomY() const override;

		void SetOX(float fOX) override;
		float GetOX() const override;

		void SetOY(float fOY) override;
		float GetOY() const override;

		void SetMirror(bool bMirror) override;
		bool GetMirror() const override;

		void SetVisible(bool bVisible) override;
		bool GetVisible() const override;

		void SetOpacity(float fOpacity) override;
		float GetOpacity() const override;

		void SetSrcRect(Rect*& pSrcRect) override;
		Rect* GetSrcRect() const override;

		void SetTone(Tone*& pTone) override;
		Tone* GetTone() const override;

		ResultCode Update() override;

		ResultCode SetEffect(Effect::EffectBase* pEffect) override;

		void Render();
		bool Dispose();

	private:
		SpriteDX() = default;
		~SpriteDX();

		bool CreateSpriteVertexBuffer();

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

#endif // !_H_SPRITE_DX_
