#ifndef _H_ANIMATION_REFFERED_
#define _H_ANIMATION_REFFERED_
#include "Common/Util/RefCounter.h"
#include "AnimationBase.h"

namespace Iris2D {
	namespace Animation {
		class AnimationRefferedProperty : public AnimationBaseProperty, public RefCounter {
		public:
			AnimationRefferedProperty() = default;
			virtual ~AnimationRefferedProperty() = default;
		};

		class AnimationRefferedFrame : public AnimationBaseFrame, public RefCounter {
		public:
			AnimationRefferedFrame() = default;
			virtual ~AnimationRefferedFrame() = default;
		};

		class AnimationRefferedGroup : public AnimationBaseGroup, public RefCounter {
		public:
			AnimationRefferedGroup() = default;
			virtual ~AnimationRefferedGroup() = default;
		};

	}
}

#endif // _H_ANIMATION_REFFERED_
