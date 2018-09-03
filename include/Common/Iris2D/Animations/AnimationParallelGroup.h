#ifndef _H_ANIMATION_PARALLEL_GROUP_
#define _H_ANIMATION_PARALLEL_GROUP_

#include <list>
#include "AnimationReferred.h"
#include <unordered_map>

namespace Iris2D {
	namespace Animation {
		class AnimationParallelGroup: public AnimationReffered {
			REF_FRIEND_DECLARE
			ANIMATION_AUTO_RELEASE
		
		private:
			std::list<AnimationBase*> m_lsAnimations;
			bool m_bIsLoop = false;
			std::unordered_map<unsigned int, std::function<void(unsigned int)>> m_umapCallBack {};
			unsigned int m_nFrameCounter = 0;
			AnimationState m_eState = AnimationState::Pending;

		public:
			static AnimationParallelGroup* Create();
			static void Release(AnimationParallelGroup*& pAnimationGroup);

		public:
			void AddAnimation(AnimationReffered* pAnimation);
			bool Update() override;
			void Start() override;
			void End() override;
			void SetLoop(bool bIsLoop) override;
			void AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned int)>& fCallBack);
			AnimationState GetAnimationState() override;

		private:
			void SetTotalTime(unsigned int nFrame) override;
			void AddCallBack(float fProgress, const AnimationCallBack& fCallBack) override;

		private:
			AnimationParallelGroup() = default;
			~AnimationParallelGroup();
		};
	}
}


#endif // !_H_ANIMATION_PARALLEL_GROUP_
