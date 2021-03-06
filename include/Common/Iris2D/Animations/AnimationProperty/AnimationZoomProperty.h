#ifndef _H_ANIMATION_ZOOM_PROPERTY_
#define _H_ANIMATION_ZOOM_PROPERTY_
#include "Common/Iris2D/Animations/AnimationProperty/AnimationProperty.h"

namespace Iris2D {
	namespace Animation {
		class AnimationZoomProperty : public AnimationProperty<ZoomVec2> {
			REF_FRIEND_DECLARE;

		public:
			static AnimationZoomProperty* Create(SpriteStatic*& pSprite);
			static void Release(AnimationZoomProperty*& pAnimation);

			ANIMATION_AUTO_RELEASE

		public:
			bool UpdateProperty(SpriteStatic* pSprite, const ZoomVec2& dpValue) override;

		private:
			AnimationZoomProperty() = default;
			~AnimationZoomProperty() = default;
		};
	}
}


#endif
