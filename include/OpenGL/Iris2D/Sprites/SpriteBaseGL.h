#ifndef _H_SPRITE_BASE_GL_
#define _H_SPRITE_BASE_GL_

#include "Common/Iris2D/Sprites/ISprite.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/RefCounter.h"
#include "Common/Util/DirtyChecker.h"
#include <glm/glm.hpp>

namespace Iris2D {

	class Viewport;
	class SpriteBaseGL : public Proxied<ISprite>, virtual public ISprite, public RefCounter {
	protected:
		Bitmap* m_pBitmap = nullptr;
		Tone* m_pTone = nullptr;
		Viewport* m_pViewport = nullptr;

		Effect::EffectBase* m_pEffect = nullptr;
		bool m_bVisible = true;

		glm::vec3 m_v3Position{ 0.f, 0.f, 0.f };
		glm::vec2 m_v2Zoom{ 1.f, 1.f };

		float m_fAngle = 0.f;
		float m_fOpacity = 1.f;
		bool m_bMirror = false;

		DirtyChecker m_dcDirtyChecker;
		DirtyChecker::DirtyCheckerHandler m_hTranslate = 0;
		DirtyChecker::DirtyCheckerHandler m_hZoom = 0;
		DirtyChecker::DirtyCheckerHandler m_hOrgPos = 0;
		DirtyChecker::DirtyCheckerHandler m_hRotate = 0;
		DirtyChecker::DirtyCheckerHandler m_hMirror = 0;
		DirtyChecker::DirtyCheckerHandler m_hOpacity = 0;

	public:

		SpriteBaseGL();

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
		void SetMirror(bool bMirror) override;
		bool GetMirror() const override;
		void SetVisible(bool bVisible) override;
		bool GetVisible() const override;
		void SetOpacity(float fOpacity) override;
		float GetOpacity() const override;
		void SetTone(Tone*& pTone) override;
		Tone* GetTone() const override;

		Bitmap* GetBitmap() const override;
		ResultCode SetBitmap(Bitmap*& pBitmap) override;

		Viewport* GetViewport() override;

		virtual ResultCode Render() = 0;
	};
}

#endif // !_H_SPRITE_BASE_GL_
