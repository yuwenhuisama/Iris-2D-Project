#ifndef _H_SPRITE_GL_
#define _H_SPRITE_GL_

#include "Common/Iris2D/ISprite.h"
#include "Common/Iris2D/Proxied.h"
#include <glm/glm.hpp>

#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/SpriteShaderBuffersGL.h"

#include "Common/Util/DirtyChecker.h"

namespace Iris2D {
	class Viewport;
	class Sprite;
	class Color;
	typedef Color Tone;

	namespace Effect{
		class EffectBase;
		class EffectBaseGL;
	}

	class SpriteGL : public ISprite, public Proxied<Sprite> {
	private:
		Bitmap* m_pBitmap = nullptr;
		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		Viewport* m_pViewport = nullptr;

		Effect::EffectBase* m_pEffect = nullptr;

		GLuint m_nVBO = 0;
		GLuint m_nVAO = 0;
		GLuint m_nEBO = 0;

		SpriteVertexBufferGL m_svbfBuffer;

		glm::vec3 m_v3Position { 0.f, 0.f, 0.f };
		glm::vec2 m_v2Zoom{ 1.f, 1.f };
		//glm::vec2 m_v2OrgPosition { 0.f, 0.f };

		float m_fAngle = 0.f;
		float m_fOpacity = 1.f;
		bool m_bMirror = false;
		bool m_bVisible = true;

		DirtyChecker m_dcDirtyChecker;
		DirtyChecker::DirtyCheckerHandler m_hTranslate = 0;
		DirtyChecker::DirtyCheckerHandler m_hZoom = 0;
		DirtyChecker::DirtyCheckerHandler m_hOrgPos = 0;
		DirtyChecker::DirtyCheckerHandler m_hRotate = 0;
		DirtyChecker::DirtyCheckerHandler m_hMirror = 0;
		DirtyChecker::DirtyCheckerHandler m_hOpacity = 0;

	public:
		static SpriteGL * Create(Viewport* pViewport = nullptr);
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

		virtual void SetEffect(Effect::EffectBase* pEffect) override;

	public:
		bool CreateVertexBuffer();
		bool Render();

	private:
		SpriteGL();
		~SpriteGL();
	};
}

#endif // !_H_SPRITE_GL_
