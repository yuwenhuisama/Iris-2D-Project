#include "Common/Iris2D/Animations/AnimationProperty/AnimationZoomProperty.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/SpriteDX.h"
#endif

namespace Iris2D {
	namespace Animation {
		AnimationZoomProperty* AnimationZoomProperty::Create(SpriteStatic*& pSprite) {
			const auto pAnimation = new AnimationZoomProperty();
			pAnimation->m_pSprite = pSprite;

			switch (AppFactory::GetApiType()) {
#ifdef _WIN32
			case ApiType::DirectX:
				RefferAssign<SpriteDX*>(pAnimation->m_pSprite, pSprite);
				break;
#endif // _WIN32
			case ApiType::OpenGL:
				RefferAssign<SpriteStaticGL*>(pAnimation->m_pSprite, pSprite);
				break;
			default:
				break;
			}

			return pAnimation;
		}

		void AnimationZoomProperty::Release(AnimationZoomProperty*& pAnimation) {
			if (!pAnimation) {
				return;
			}

			Iris2D::RefferRelease(pAnimation);
		}

		bool AnimationZoomProperty::UpdateProperty(SpriteStatic* pSprite, const PositionVec2& dpValue) {
			pSprite->SetZoomX(dpValue.x);
			pSprite->SetZoomY(dpValue.y);
			return true;
		}
	}
}
