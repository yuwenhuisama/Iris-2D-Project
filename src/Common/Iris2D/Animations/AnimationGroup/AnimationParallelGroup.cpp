#include "Common/Iris2D/Animations/AnimationGroup/AnimationParallelGroup.h"

namespace Iris2D {
	namespace Animation {


		AnimationParallelGroup* AnimationParallelGroup::Create() {
			return new AnimationParallelGroup();
		}

		void AnimationParallelGroup::Release(AnimationParallelGroup*& pAnimationGroup) {
			if (!pAnimationGroup) {
				return;
			}

			RefferRelease(pAnimationGroup);
		}

		void AnimationParallelGroup::AddAnimation(AnimationRefferedProperty* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		void AnimationParallelGroup::AddAnimation(AnimationRefferedFrame* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		void AnimationParallelGroup::AddAnimation(AnimationRefferedGroup* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		bool AnimationParallelGroup::Update() {
			++m_nFrameCounter;

			if (!m_umapCallBack.empty() && m_umapCallBack.find(m_nFrameCounter) != m_umapCallBack.end()) {
				const auto& fCallBack = m_umapCallBack[m_nFrameCounter];
				fCallBack(m_nFrameCounter);
			}

			bool bNeedStop = true;
			for (auto& pAnimation : m_lsAnimations) {
				const auto bResult = pAnimation->Update();
				const auto bState = pAnimation->GetAnimationState();

				if (bState != AnimationState::Terminated) {
					bNeedStop = false;
				}

				if (!bResult) {
					return false;
				}
			}

			if (!m_bIsLoop && bNeedStop) {
				End();
			}

			return true;
		}

		void AnimationParallelGroup::Start() {
			m_nFrameCounter = 0;
			m_eState = AnimationState::Displaying;

			for (auto& pAnimation : m_lsAnimations) {
				pAnimation->Start();
				pAnimation->SetLoop(m_bIsLoop);
			}
		}

		void AnimationParallelGroup::End() {
			for (auto& pAnimation : m_lsAnimations) {
				pAnimation->End();
			}

			m_eState = AnimationState::Terminated;
		}

		void AnimationParallelGroup::SetLoop(bool bIsLoop) {
			m_bIsLoop = bIsLoop;
		}

		void AnimationParallelGroup::AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned)>& fCallBack) {
			m_umapCallBack[nFrameCount] = fCallBack;
		}

		AnimationState AnimationParallelGroup::GetAnimationState() {
			return m_eState;
		}

		AnimationParallelGroup::~AnimationParallelGroup() {
			for(auto& pAnimation : m_lsAnimations) {
				pAnimation->AutoRelease();
			}
		}
	}
}
