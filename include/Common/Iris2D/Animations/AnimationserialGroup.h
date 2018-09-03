#ifndef _H_ANIMATION_SERIAL_GROUP_
#define _H_ANIMATION_SERIAL_GROUP_

#include "AnimationReferred.h"
#include <unordered_map>

namespace Iris2D {
	namespace Animation {
		class AnimationSerialGroup : public AnimationReffered {
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
			void AddAnimation(AnimationReffered* pAnimation);
			bool Update() override;
			void Start() override;
			void End() override;
			void SetLoop(bool bIsLoop) override;
			void AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned int)>& fCallBack);
			AnimationState GetAnimationState() override;

		private:
			void AddCallBack(float fProgress, const AnimationCallBack& fCallBack) override;
			void SetTotalTime(unsigned nTotalFrame) override;

		private:
			AnimationSerialGroup() = default;
			~AnimationSerialGroup();
		};

	}
}


#endif
