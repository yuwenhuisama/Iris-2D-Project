#ifndef _H_ANIMATION_REFFERED_
#define _H_ANIMATION_REFFERED_
#include "Common/Util/RefCounter.h"
#include "AnimationBase.h"

namespace Iris2D {
	namespace Animation {
		class AnimationReffered : public AnimationBase, public RefCounter {
		public:
			AnimationReffered() : AnimationBase(nullptr) {}
			virtual ~AnimationReffered() = default;
		};
	}
}

#endif // _H_ANIMATION_REFFERED_