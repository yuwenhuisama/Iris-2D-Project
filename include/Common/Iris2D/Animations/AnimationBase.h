#ifndef _H_ANIMATION_BASE_
#define _H_ANIMATION_BASE_
#include "IAnimation.h"
#include "Common/Iris2D/Proxy.h"

#define ANIMATION_AUTO_RELEASE\
		public:\
			AnimationBase* AutoRelease() override{\
				auto pAnimationDerived = this;\
				Release(pAnimationDerived);\
				return pAnimationDerived;\
			}\

namespace Iris2D {
	namespace Animation {
		class AnimationBase : public Proxy<IAnimation>, public IAnimation {
		public:
			AnimationBase(IAnimation* pProxied) : Proxy<IAnimation>(pProxied) {}
			virtual AnimationBase* AutoRelease() = 0;
			~AnimationBase() = default;
		};
	}
}

#endif
