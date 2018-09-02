#include "Common/Iris2D/Animations/AnimationPositionProperty.h"
#include "Common/Iris2D/Sprite.h"
#include "OpenGL/Iris2D/SpriteGL.h"

namespace Iris2D {
	namespace Animation {

		AnimationPositionProperty* AnimationPositionProperty::Create(Sprite*& pSprite) {
			const auto pAnimation = new AnimationPositionProperty();
			pAnimation->m_pSprite = pSprite;

			RefferAssign<SpriteGL*>(pAnimation->m_pSprite, pSprite);

			return pAnimation;
		}

		void AnimationPositionProperty::Release(AnimationPositionProperty*& pAnimation) {
			if (!pAnimation) {
				return;
			}

			Iris2D::RefferRelease(pAnimation);
		}

		bool AnimationPositionProperty::UpdateProperty(Sprite* pSprite, const PositionVec2& dpValue) {
			pSprite->SetX(dpValue.x);
			pSprite->SetY(dpValue.y);
			return true;
		}

		AnimationPositionProperty::AnimationPositionProperty(): AnimationProperty(nullptr) {
		}
	}
}
