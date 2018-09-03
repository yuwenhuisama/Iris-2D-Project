#include "Common/Iris2D/Animations/AnimationGroup/AnimationSerialGroup.h"

namespace Iris2D {
	namespace Animation {

		AnimationSerialGroup* AnimationSerialGroup::Create() {
			return new AnimationSerialGroup();
		}

		void AnimationSerialGroup::Release(AnimationSerialGroup*& pAnimationGroup) {
			if (!pAnimationGroup) {
				return;
			}

			RefferRelease(pAnimationGroup);
		}

		void AnimationSerialGroup::AddAnimation(AnimationRefferedProperty* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		void AnimationSerialGroup::AddAnimation(AnimationRefferedFrame* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		void AnimationSerialGroup::AddAnimation(AnimationRefferedGroup* pAnimation) {
			pAnimation->IncreamRefCount();
			m_lsAnimations.push_back(pAnimation);
		}

		bool AnimationSerialGroup::Update() {
			++m_nFrameCounter;

			if (!m_umapCallBack.empty() && m_umapCallBack.find(m_nFrameCounter) != m_umapCallBack.end()) {
				const auto& fCallBack = m_umapCallBack[m_nFrameCounter];
				fCallBack(m_nFrameCounter);
			}

			const auto& pCurrentAnimation = *m_iterCurrentAnimation;
			pCurrentAnimation->Update();

			if (pCurrentAnimation->GetAnimationState() == AnimationState::Terminated) {
				++m_iterCurrentAnimation;

				if (m_iterCurrentAnimation == m_lsAnimations.end()) {
					if (m_bIsLoop) {
						Start();
					} else {
						End();
					}
				}
			}

			return true;
		}

		void AnimationSerialGroup::Start() {
			m_nFrameCounter = 0;
			m_eState = AnimationState::Displaying;

			if (!m_lsAnimations.empty()) {
				m_iterCurrentAnimation = m_lsAnimations.begin();
			}

			for (auto& pAnimation : m_lsAnimations) {
				pAnimation->Start();
				pAnimation->SetLoop(false);
			}
		}

		void AnimationSerialGroup::End() {
			for (auto& pAnimation : m_lsAnimations) {
				pAnimation->End();
			}
			m_eState = AnimationState::Terminated;
		}

		void AnimationSerialGroup::SetLoop(bool bIsLoop) {
			m_bIsLoop = bIsLoop;
		}

		void AnimationSerialGroup::AddCallBack(unsigned int nFrameCount, const std::function<void(unsigned)>& fCallBack) {
			m_umapCallBack[nFrameCount] = fCallBack;
		}

		AnimationState AnimationSerialGroup::GetAnimationState() {
			return m_eState;
		}

		AnimationSerialGroup::~AnimationSerialGroup() {
			for (auto& pAnimation : m_lsAnimations) {
				pAnimation->AutoRelease();
			}
		}
	}
}
