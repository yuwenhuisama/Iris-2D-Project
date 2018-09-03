#include "Common/Iris2D/Animations/AnimationFrame.h"

namespace Iris2D {
	namespace Animation {

		AnimationFrame* AnimationFrame::Create(Sprite*& pSprite) {
			return nullptr;
		}

		void AnimationFrame::Release(AnimationFrame*& pAnimation) {
		}

		bool AnimationFrame::Update() {
			return m_pProxied->Update();
		}

		void AnimationFrame::Start() {
			m_pProxied->Start();
		}

		void AnimationFrame::End() {
			m_pProxied->End();
		}

		void AnimationFrame::SetLoop(bool bIsLoop) {
			m_pProxied->SetLoop(bIsLoop);
		}

		//void AnimationFrame::AddCallBack(float fProgress, const AnimationCallBack& fCallBack) {
		//	m_pProxied->AddCallBack(fProgress, fCallBack);
		//}

		void AnimationFrame::SetInterval(unsigned int nFrameCount) {
			m_pProxied->SetInterval(nFrameCount);
		}

		AnimationState AnimationFrame::GetAnimationState() {
			return m_pProxied->GetAnimationState();
		}
	}
}
