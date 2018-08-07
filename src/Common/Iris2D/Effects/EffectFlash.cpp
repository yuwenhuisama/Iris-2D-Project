#include "Common/Iris2D/Effects/EffectFlash.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/Effects/EffectFlashGL.h"

namespace Iris2D {
	namespace Effect {
		EffectFlash* EffectFlash::Create(Color*& pColor, unsigned int nDuration, bool bLoop) {
			EffectFlash* pEffectFlash = nullptr;
			switch (AppFactory::GetApiType()) {
#ifdef _WIN32
			case ApiType::DirectX:
			{
			}
			break;
#endif // _WIN32
			case ApiType::OpenGL: 
			{
				auto pTmp = EffectFlashGL::Create(pColor, nDuration, bLoop);
				pEffectFlash = new EffectFlash(pTmp);
				pTmp->SetProxy(pEffectFlash);
			}
				break;
			default:
				break;
			}

			return pEffectFlash;
		}

		void EffectFlash::Release(EffectFlash*& pEffectFlash) {
			if (!pEffectFlash) {
				return;
			}

			auto* pProxied = pEffectFlash->GetProxied();

			switch (AppFactory::GetApiType()) {
#ifdef _WIN32
			case ApiType::DirectX:
				break;
#endif // _WIN32
			case ApiType::OpenGL:
				EffectFlashGL::Release(reinterpret_cast<EffectFlashGL*&>(pProxied));
				break;
			default:
				break;
			}

			// Delete proxy object when proxied object has been released.
			if (!pProxied) {
				delete pEffectFlash;
				pEffectFlash = nullptr;
			}
		}

		bool EffectFlash::Update(const Sprite* pSprite) {
			return m_pProxied->Update(pSprite);
		}

		EffectFlash::EffectFlash(IEffect* pEffect): EffectBase(pEffect) {
		}
	}
}
