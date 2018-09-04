#ifndef _H_ANIMATION_SERIAL_GROUP_
#define _H_ANIMATION_SERIAL_GROUP_

#include "Common/Iris2D/Animations/AnimationReferred.h"
#include <unordered_map>

namespace Iris2D {
	namespace Animation {
		class AnimationSerialGroup : public AnimationRefferedGroup {
			REF_FRIEND_DECLARE
			ANIMATION_AUTO_RELEASE

		private:
			std::list<AnimationBase*> m_lsAnimations;
			bool m_bIsLoop = false;
			std::unordered_map<unsigned int, std::function<void(unsigned int)>> m_umapCallBack{};
			unsigned int m_nFrameCounter = 0;
			AnimationState m_eState = AnimationState::Pending;
			std::list<AnimationBase*>::iterator m_iterCurrentAnimation {};

		public:
			static AnimationSerialGroup* Create();
			static void Release(AnimationSerialGroup*& pAnimationGroup);

		public:
			void AddAnimation(AnimationRefferedProperty* pAnimation);
			void AddAnimation(AnimationRefferedFrame* pAnimation);
			void AddAnimation(AnimationRefferedGroup* pAnimation);

			bool Update() override;
			void Start() override;
			void End() override;
			void SetLoop(bool bIsLoop) override;
			void AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned int)>& fCallBack) override;
			AnimationState GetAnimationState() override;

		private:
			AnimationSerialGroup() = default;
			~AnimationSerialGroup();
		};

	}
}


#endif
