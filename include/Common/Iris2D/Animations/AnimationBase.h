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
		class AnimationBase : public IAnimation {
		public:
			virtual ~AnimationBase() = default;
			virtual AnimationBase* AutoRelease() = 0;
		};

		class AnimationBaseProperty : public AnimationBase {
		public:
			virtual void SetTotalTime(unsigned int nTotalFrame) = 0;
			virtual void AddCallBack(float fProgress, const AnimationCallBack& fCallBack) = 0;
		};

		class AnimationBaseFrame : public AnimationBase {
		public:
			virtual void SetInterval(unsigned int nTotalFrame) = 0;
		};

		class AnimationBaseGroup : public AnimationBase {
			virtual void AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned int)>& fCallBack) = 0;
		};
	}
}

#endif
