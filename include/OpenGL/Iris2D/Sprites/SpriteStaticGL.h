#ifndef _H_SPRITE_STATIC_GL_
#define _H_SPRITE_STATIC_GL_

#include "Common/Iris2D/Sprites/ISpriteStatic.h"
#include "Common/Iris2D/Proxied.h"
#include <glm/glm.hpp>

#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/SpriteShaderBuffersGL.h"

#include "Common/Util/DirtyChecker.h"
#include "Common/Util/RefCounter.h"
#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"
#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"

namespace Iris2D {
	class Viewport;
	class Color;
	typedef Color Tone;

	namespace Effect{
		class EffectBase;
		class EffectBaseGL;
	}

	class TextureGL;
	class SpriteStaticGL :  public ISpriteStatic, public SpriteBaseGL {
		REF_FRIEND_DECLARE

	private:
		Rect* m_pSrcRect = nullptr;
		SpriteInstanceAttributeGL m_siaBuffer;

	public:
		static SpriteStaticGL * Create(Viewport* pViewport = nullptr);
		static void Release(SpriteStaticGL*& pSprite);

		static void ForceRelease(SpriteStaticGL* pSprite);

	public:
		void SetOX(float fOX) override;
		float GetOX() const override;

		void SetOY(float fOY) override;
		float GetOY() const override;

		void SetSrcRect(Rect *& pSrcRect) override;
		Rect * GetSrcRect() const override;

		ResultCode Update() override;

		ResultCode SetEffect(Effect::EffectBase* pEffect) override;

		bool CheckMergeableWith(const SpriteStaticGL* pSpriteTarget);

	public:
		ResultCode Render() override;
		TextureGL* RenderEffect();
		SpriteInstanceAttributeGL GetInstanceAttribute();

	private:
		bool NeedDiscard() const;

	private:
		SpriteStaticGL() = default;
		~SpriteStaticGL();

	public:
		void SetX(float fX) override {
			SpriteBaseGL::SetX(fX);
		}

		float GetX() const override {
			return SpriteBaseGL::GetX();
		}

		void SetY(float fY) override {
			SpriteBaseGL::SetY(fY);

		}

		float GetY() const override {
			return SpriteBaseGL::GetY();
		}

		void SetZ(float fZ) override {
			SpriteBaseGL::SetZ(fZ);
		}

		float GetZ() const override {
			return SpriteBaseGL::GetZ();
		}

		void SetAngle(float fAngle) override {
			SpriteBaseGL::SetAngle(fAngle);
		}

		float GetAngle() const override {
			return SpriteBaseGL::GetAngle();
		}

		void SetZoomX(float fZoomX) override {
			SpriteBaseGL::SetZoomX(fZoomX);
		}

		float GetZoomX() const override {
			return SpriteBaseGL::GetZoomX();
		}

		void SetZoomY(float fZoomY) override {
			SpriteBaseGL::SetZoomY(fZoomY);
		}

		float GetZoomY() const override {
			return SpriteBaseGL::GetZoomY();
		}

		void SetMirror(bool bMirror) override {
			SpriteBaseGL::SetMirror(bMirror);
		}

		bool GetMirror() const override {
			return SpriteBaseGL::GetMirror();
		}

		void SetVisible(bool bVisible) override {
			SpriteBaseGL::SetVisible(bVisible);
		}

		bool GetVisible() const override {
			return SpriteBaseGL::GetVisible();
		}

		void SetOpacity(float fOpacity) override {
			SpriteBaseGL::SetOpacity(fOpacity);
		}

		float GetOpacity() const override {
			return SpriteBaseGL::GetOpacity();
		}

		void SetTone(Tone*& pTone) override {
			SpriteBaseGL::SetTone(pTone);
		}

		Tone* GetTone() const override {
			return SpriteBaseGL::GetTone();
		}

		Viewport* GetViewport() override {
			return SpriteBaseGL::GetViewport();
		}

		ResultCode SetBitmap(Bitmap*& pBitmap) override {
			return SpriteBaseGL::SetBitmap(pBitmap);
		}

		Bitmap* GetBitmap() const override {
			return SpriteBaseGL::GetBitmap();
		}

	};
}

#endif // !_H_SPRITE_STATIC_GL_
