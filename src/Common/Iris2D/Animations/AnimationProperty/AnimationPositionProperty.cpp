#include "Common/Iris2D/Animations/AnimationProperty/AnimationPositionProperty.h"
#include "Common/Iris2D/Sprite.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/SpriteGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/SpriteDX.h"
#endif

namespace Iris2D {
	namespace Animation {

		AnimationPositionProperty* AnimationPositionProperty::Create(Sprite*& pSprite) {
			const auto pAnimation = new AnimationPositionProperty();
			pAnimation->m_pSprite = pSprite;

			switch (AppFactory::GetApiType()) {
#ifdef _WIN32
			case ApiType::DirectX:
				RefferAssign<SpriteDX*>(pAnimation->m_pSprite, pSprite);
				break;
#endif // _WIN32
			case ApiType::OpenGL:
				RefferAssign<SpriteGL*>(pAnimation->m_pSprite, pSprite);
				break;
			default:
				break;
			}

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
	}
}
