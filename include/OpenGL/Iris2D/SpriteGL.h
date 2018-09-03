#ifndef _H_SPRITE_GL_
#define _H_SPRITE_GL_

#include "Common/Iris2D/ISprite.h"
#include "Common/Iris2D/Proxied.h"
#include <glm/glm.hpp>

#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/SpriteShaderBuffersGL.h"

#include "Common/Util/DirtyChecker.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D {
	class Viewport;
	class Sprite;
	class Color;
	typedef Color Tone;

	namespace Effect{
		class EffectBase;
		class EffectBaseGL;
	}

	class SpriteGL : public ISprite, public Proxied<Sprite>, public RefCounter {
		REF_FRIEND_DECLARE

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
		ResultCode SetBitmap(Bitmap *& pBitmap) override;
		Bitmap * GetBitmap() const override;

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

		void SetSrcRect(Rect *& pSrcRect) override;
		Rect * GetSrcRect() const override;

		void SetTone(Tone *& pTone) override;
		Tone * GetTone() const override;

		ResultCode Update() override;

		ResultCode SetEffect(Effect::EffectBase* pEffect) override;

	public:
		bool CreateVertexBuffer();
		ResultCode Render();

	private:
		bool NeedDiscard() const;

	private:
		SpriteGL();
		~SpriteGL();
	};
}

#endif // !_H_SPRITE_GL_
