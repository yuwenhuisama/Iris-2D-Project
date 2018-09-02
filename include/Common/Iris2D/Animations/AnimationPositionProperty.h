#ifndef _H_ANIMATION_POSITION_PROPERTY_
#define _H_ANIMATION_POSITION_PROPERTY_
#include "AnimationProperty.h"
#include "AnimationBase.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D {
	namespace Animation {
		class AnimationPositionProperty: public AnimationProperty<PositionVec2> {
			REF_FRIEND_DECLARE;

		public:
			static AnimationPositionProperty* Create(Sprite*& pSprite);
			static void Release(AnimationPositionProperty*& pAnimation);

			ANIMATION_AUTO_RELEASE

		public:
			bool UpdateProperty(Sprite* pSprite, const PositionVec2& dpValue) override;

		private:
			AnimationPositionProperty() = default;
			~AnimationPositionProperty() = default;
		};
	}
}

#endif
