#ifndef _H_ANIMATION_ANGLE_PROPERTY_
#define _H_ANIMATION_ANGLE_PROPERTY_

#include "Common/Iris2D/Animations/AnimationProperty/AnimationProperty.h"

namespace Iris2D {
	namespace Animation {
		class AnimationAngleProperty: public AnimationProperty<AngleValue> {
			REF_FRIEND_DECLARE;

		public:
			static AnimationAngleProperty* Create(Sprite*& pSprite);
			static void Release(AnimationAngleProperty*& pAnimation);

			ANIMATION_AUTO_RELEASE

		public:
			bool UpdateProperty(Sprite* pSprite, const AngleValue& dpValue) override;

		private:
			AnimationAngleProperty() = default;
			~AnimationAngleProperty() = default;
		};
	}
}

#endif
