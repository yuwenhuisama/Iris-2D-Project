#ifndef _H_ANIMATION_PROPERTY_
#define _H_ANIMATION_PROPERTY_

#include "Common/Iris2D/Animations/AnimationBase.h"
#include "Common/Iris2D/Sprites/SpriteStatic.h"

#include <list>
#include <unordered_map>
#include <glm/vec2.hpp>
#include "Common/Iris2D/Animations/AnimationReferred.h"

namespace Iris2D {

	namespace Animation {
		typedef glm::vec2 PositionVec2;
		typedef glm::vec2 ZoomVec2;
		typedef float AngleValue;

		template<typename E>
		struct KeyFrameElement {
			KeyFrameElement(float fProgress, E dpData) : m_fProgress(fProgress), m_dpData(dpData) {}

			KeyFrameElement() {}

			float m_fProgress = 0.0;
			E m_dpData{};
		};

		struct AnimationCallBackPair {
			AnimationCallBackPair(float fProgress, const AnimationCallBack &fCallBack) : fProgress(fProgress),
																						 fCallBack(fCallBack) {}

			AnimationCallBackPair() {}

			float fProgress = 0.0f;
			AnimationCallBack fCallBack {};
		};

		template<typename E>
		class AnimationProperty: public AnimationRefferedProperty {
		protected:
			std::list<KeyFrameElement<E>> m_lsKeyFrameList {};
			
			unsigned int m_nTotalTime = 0;
			SpriteStatic* m_pSprite = nullptr;
			AnimationState m_eState = AnimationState::Pending;

			typename std::list<KeyFrameElement<E>>::iterator m_iterCurrent {};

			KeyFrameElement<E> m_dpPreFrameData;
			KeyFrameElement<E> m_dpStartFrameData;
			KeyFrameElement<E> m_dpEndFrameData;

			unsigned int m_nFrameCounter = 0;

			bool m_bIsLoop = false;

			std::list<AnimationCallBackPair> m_lsCallBackList {};
			std::unordered_map<unsigned int, AnimationCallBackPair> m_umapCallBackMap{};

		public:
			void SetTotalTime(unsigned int nTotalFrame) override {
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
						UpdateProperty(m_pSprite, m_dpStartFrameData.m_dpData);
						Start();
						return true;
					}
					return false;
				}

				++m_nFrameCounter;

				E dpValue{};

				if (m_lsKeyFrameList.empty()) {
					if (m_nFrameCounter == m_nTotalTime) {
						dpValue = m_dpEndFrameData.m_dpData;
						End();
					} else {
						auto fDelta = m_nFrameCounter / static_cast<float>(m_nTotalTime);
						dpValue = (1.0f - fDelta) * m_dpStartFrameData.m_dpData + fDelta * m_dpEndFrameData.m_dpData;
					}
				}
				else {
					if (m_iterCurrent == m_lsKeyFrameList.end()) {
						if (m_nFrameCounter == m_nTotalTime) {
							dpValue = m_dpEndFrameData.m_dpData;
							End();
						}
						else {
							const auto& iterLast = m_lsKeyFrameList.back();
							auto fDelta = (m_nFrameCounter - (iterLast.m_fProgress * m_nTotalTime)) / ((m_dpEndFrameData.m_fProgress - iterLast.m_fProgress) * m_nTotalTime);
							dpValue = (1.0f - fDelta) * iterLast.m_dpData + fDelta * m_dpEndFrameData.m_dpData;
						}
					}
					else {
						if (static_cast<unsigned int>(m_iterCurrent->m_fProgress * m_nTotalTime) == m_nFrameCounter) {
							dpValue = m_iterCurrent->m_dpData;
							m_dpPreFrameData = *m_iterCurrent;

							++m_iterCurrent;
						}
						else {
							// interpolation linear
							auto fDelta = (m_nFrameCounter - (m_dpPreFrameData.m_fProgress * m_nTotalTime)) / ((m_iterCurrent->m_fProgress - m_dpPreFrameData.m_fProgress) * m_nTotalTime);
							dpValue = (1.0f - fDelta) * m_dpPreFrameData.m_dpData + fDelta * m_iterCurrent->m_dpData;
						}
					}
				}

				if (!m_umapCallBackMap.empty() && m_umapCallBackMap.find(m_nFrameCounter) != m_umapCallBackMap.end()) {
					const auto& pair = m_umapCallBackMap[m_nFrameCounter];
					pair.fCallBack(pair.fProgress);
				}

				return UpdateProperty(m_pSprite, dpValue);
			}

			void Start() override {
				if (m_eState == AnimationState::Pending) {
					m_umapCallBackMap.clear();
					for (const auto& pair : m_lsCallBackList) {
						m_umapCallBackMap[static_cast<unsigned int>(m_nTotalTime * pair.fProgress)] = pair;
					}
				}

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

			void AddCallBack(float fProgress, const AnimationCallBack& fCallBack) override {
				m_lsCallBackList.push_back({ fProgress, fCallBack });
			}

			AnimationState GetAnimationState() override {
				return m_eState;
			}

			virtual bool UpdateProperty(SpriteStatic* pSprite, const E& dpValue) = 0;

		protected:
			AnimationProperty() : AnimationRefferedProperty() {}
			~AnimationProperty() {
				SpriteStatic::Release(m_pSprite);
			}
		};
	}
}


#endif
