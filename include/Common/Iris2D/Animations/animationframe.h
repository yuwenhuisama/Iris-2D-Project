#ifndef _H_ANIMATION_FRAME_
#define _H_ANIMATION_FRAME_

#include "AnimationBase.h"

namespace Iris2D {
	class Sprite;
	namespace Animation {
		class AnimationFrame: public Proxy<AnimationBaseFrame>, public AnimationBaseFrame {
			ANIMATION_AUTO_RELEASE

		public:
			static AnimationFrame* Create(Sprite*& pSprite);
			static void Release(AnimationFrame*& pAnimation);

		public:
			bool Update() override;
			void Start() override;
			void End() override;
			void SetLoop(bool bIsLoop) override;
			void SetInterval(unsigned int nFrameCount) override;
			AnimationState GetAnimationState() override;
		};
	}
}

#endif //_H_ANIMATION_FRAME_
