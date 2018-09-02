#ifndef _H_ANIMATION_PROPERTY_
#define _H_ANIMATION_PROPERTY_

#include "Common/Iris2D/Animations/AnimationBase.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Sprite.h"

#include <list>
#include <glm/vec2.hpp>

namespace Iris2D {
	class Sprite;
	namespace Animation {

		//struct PositionVec2 {
		//	float m_nX = 0.0f;
		//	float m_nY = 0.0f;
		//};

		//struct ZoomVec2 {
		//	float m_nX = 0.0f;
		//	float m_nY = 0.0f;
		//};

		typedef glm::vec2 PositionVec2;
		typedef glm::vec2 ZoomVec2;

		typedef float AngleValue;

		template<typename E>
		struct KeyFrameElement {
			float m_fProgress = 0.0;
			E m_v2Data{};
		};

		template<typename E>
		class AnimationProperty: public AnimationBase, public RefCounter {
		protected:
			std::list<KeyFrameElement<E>> m_lsKeyFrameList {};
			
			unsigned int m_nTotalTime = 0;
			Sprite* m_pSprite = nullptr;
			AnimationState m_eState = AnimationState::Pending;

			typename std::list<KeyFrameElement<E>>::iterator m_iterCurrent {};

			KeyFrameElement<E> m_dpPreFrameData;

			KeyFrameElement<E> m_dpStartFrameData;
			KeyFrameElement<E> m_dpEndFrameData;

			unsigned int m_nFrameCounter = 0;

			bool m_bIsLoop = false;

			//static AnimationProperty* Create(Sprite*& pSprite);
			//static void Release(AnimationProperty*& pAnimation);

			//ANIMATION_AUTO_RELEASE

		public:
			void SetTotalTime(unsigned nTotalFrame) {
				m_nTotalTime = nTotalFrame;
			}

			void SetKeyFrameList(const std::list<KeyFrameElement<E>>& lsKeyFrameList) {
				m_lsKeyFrameList = lsKeyFrameList;
			}

			void SetKeyFrameList(std::list<KeyFrameElement<E>>&& lsKeyFrameList) {
				m_lsKeyFrameList = lsKeyFrameList;
			}

			void SetStartKeyFrame(const E& kfeElement) {
				m_dpStartFrameData = { 0.0f, kfeElement };
			}

			void SetEndKeyFrame(const E& kfeElement) {
				m_dpEndFrameData = { 1.0f, kfeElement };
			}

			bool Update() override {
				if (m_eState != AnimationState::Displaying) {
					if(m_bIsLoop && m_eState == AnimationState::Terminated) {
						UpdateProperty(m_pSprite, m_dpStartFrameData.m_v2Data);
						Start();
						return true;
					} else {
						return false;
					}
				}

				if (m_lsKeyFrameList.empty()) {
					return false;
				}

				++m_nFrameCounter;

				E dpValue {};
				if (m_iterCurrent == m_lsKeyFrameList.end()) {
					if (m_nFrameCounter == m_nTotalTime) {
						dpValue = m_dpEndFrameData.m_v2Data;
						End();
					} else {
						const auto& iterLast = m_lsKeyFrameList.back();
						auto fDelta = (m_nFrameCounter - (iterLast.m_fProgress * m_nTotalTime)) / ((m_dpEndFrameData.m_fProgress - iterLast.m_fProgress) * m_nTotalTime);
						dpValue = (1.0f - fDelta) * iterLast.m_v2Data + fDelta * m_dpEndFrameData.m_v2Data;
					}
				}
				else {
					if (static_cast<unsigned int>(m_iterCurrent->m_fProgress * m_nTotalTime) == m_nFrameCounter) {
						dpValue = m_iterCurrent->m_v2Data;
						m_dpPreFrameData = *m_iterCurrent;

						++m_iterCurrent;
					}
					else {
						// interpolation
						auto fDelta = (m_nFrameCounter - (m_dpPreFrameData.m_fProgress * m_nTotalTime)) / ((m_iterCurrent->m_fProgress - m_dpPreFrameData.m_fProgress) * m_nTotalTime);

						dpValue = (1.0f - fDelta) * m_dpPreFrameData.m_v2Data + fDelta * m_iterCurrent->m_v2Data;
					}
				}

				return UpdateProperty(m_pSprite, dpValue);
			}

			void Start() override {

				m_nFrameCounter = 0;

				m_eState= AnimationState::Displaying;
				m_dpPreFrameData = m_dpStartFrameData;

				m_iterCurrent = m_lsKeyFrameList.begin();
			}

			void End() override {
				m_eState = AnimationState::Terminated;
			}

			void SetLoop(bool bIsLoop) override {
				m_bIsLoop = bIsLoop;
			}

			virtual bool UpdateProperty(Sprite* pSprite, const E& dpValue) = 0;

		protected:
			AnimationProperty(IAnimation* pAnimation) : AnimationBase(pAnimation) {}
			~AnimationProperty() {
				Sprite::Release(m_pSprite);
			}

		};
	}
}


#endif
