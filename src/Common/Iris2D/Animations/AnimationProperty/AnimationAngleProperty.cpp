#include "Common/Iris2D/Animations/AnimationProperty/AnimationAngleProperty.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/SpriteDX.h"
#endif

namespace Iris2D {
	namespace Animation {

		AnimationAngleProperty* AnimationAngleProperty::Create(SpriteStatic*& pSprite) {
			const auto pAnimation = new AnimationAngleProperty();
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

		void AnimationAngleProperty::Release(AnimationAngleProperty*& pAnimation) {
			if (!pAnimation) {
				return;
			}

			Iris2D::RefferRelease(pAnimation);
		}

		bool AnimationAngleProperty::UpdateProperty(SpriteStatic* pSprite, const AngleValue& dpValue) {
			pSprite->SetAngle(dpValue);
			return true;
		}
	}
}
