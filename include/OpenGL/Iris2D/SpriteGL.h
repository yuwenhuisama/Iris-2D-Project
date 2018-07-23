#ifndef _H_SPRITE_GL_
#define _H_SPRITE_GL_

#include "Common/Iris2D/ISprite.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D {
	class Viewport;
	class Sprite;

	class SpriteGL : public ISprite, public Proxied<Sprite> {
	private:
		Bitmap* m_pBitmap = nullptr;
		Rect* m_pSrcRect = nullptr;

		GLuint m_nVBO = 0;
		GLuint m_nVAO = 0;
		GLuint m_nEBO = 0;

	public:
		SpriteGL * Create(Viewport* pViewport = nullptr);
		static void Release(SpriteGL*& pSprite);

		static void ForceRelease(SpriteGL* pSprite);

	public:
		// Í¨¹ý ISprite ¼Ì³Ð
		virtual void SetBitmap(Bitmap *& pBitmap) override;
		virtual Bitmap * GetBitmap() const override;

		virtual void SetX(float fX) override;
		virtual float GetX() const override;

		virtual void SetY(float fY) override;
		virtual float GetY() const override;

		virtual void SetZ(float fZ) override;
		virtual float GetZ() const override;

		virtual void SetAngle(float fAngle) override;
		virtual float GetAngle() const override;

		virtual void SetZoomX(float fZoomX) override;
		virtual float GetZoomX() const override;

		virtual void SetZoomY(float fZoomY) override;
		virtual float GetZoomY() const override;

		virtual void SetOX(float fOX) override;
		virtual float GetOX() override;

		virtual void SetOY(float fOY) override;
		virtual float GetOY() override;

		virtual void SetMirror(bool bMirror) override;
		virtual bool GetMirror() override;

		virtual void SetVisible(bool bVisible) override;
		virtual bool GetVisible() override;

		virtual void SetOpacity(float fOpacity) override;
		virtual float GetOpacity() override;

		virtual void SetSrcRect(Rect *& pSrcRect) override;
		virtual Rect * GetSrcRect() const override;

		virtual void SetTone(Tone *& pTone) override;
		virtual Tone * GetTone() const override;

		virtual void Update() override;

	public:
		bool CreateVertexBuffer();
		bool Render();
	};
}

#endif // !_H_SPRITE_GL_
