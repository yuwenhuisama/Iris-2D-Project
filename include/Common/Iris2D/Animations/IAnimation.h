#ifndef _H_IANIMATION_
#define _H_IANIMATION_

#include <functional>

namespace Iris2D {
	namespace Animation {

		enum class AnimationState {
			Pending,
			Displaying,
			Terminated,
		};

		typedef std::function<void(float)> AnimationCallBack;

		class IAnimation {
		public:
			virtual bool Update() = 0;
			virtual void Start() = 0;
			virtual void End() = 0;
			virtual void SetLoop(bool bIsLoop) = 0;
			virtual AnimationState GetAnimationState() = 0;
			virtual ~IAnimation() = default;
		};
	}
}


#endif
