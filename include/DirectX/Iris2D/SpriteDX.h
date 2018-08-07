#ifndef _H_SPRITE_DX_
#define _H_SPRITE_DX_

#include "DirectX/Common.h"
#include "DirectX/Util/SpriteShaderBuffersDX.h"

#include "Common/Iris2D/ISprite.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D
{
	class Sprite;
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
	class SpriteDX : public Proxied<Sprite>, public ISprite
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

		void SetBitmap(Bitmap*& pBitmap);
		Bitmap* GetBitmap() const;

		void SetX(float fX);
		float GetX() const;

		void SetY(float fY);
		float GetY() const;

		void SetZ(float fZ);
		float GetZ() const;

		void SetAngle(float fAngle);
		float GetAngle() const;

		void SetZoomX(float fZoomX);
		float GetZoomX() const;

		void SetZoomY(float fZoomY);
		float GetZoomY() const;

		void SetOX(float fOX);
		float GetOX();

		void SetOY(float fOY);
		float GetOY();

		void SetMirror(bool bMirror);
		bool GetMirror();

		void SetVisible(bool bVisible);
		bool GetVisible();

		void SetOpacity(float fOpacity);
		float GetOpacity();

		void SetSrcRect(Rect*& pSrcRect);
		Rect* GetSrcRect() const;

		void SetTone(Tone*& pTone);
		Tone* GetTone() const;

		void Update();

		void SetEffect(Effect::EffectBase* pEffect) override;

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
