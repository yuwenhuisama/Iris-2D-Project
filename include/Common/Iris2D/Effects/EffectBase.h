#ifndef _H_EFFECT_BASE_
#define _H_EFFECT_BASE_
#include "IEffect.h"
#include "Common/Iris2D/Proxy.h"

#define EFFECT_AUTO_RELEASE\
			EffectBase* AutoRelease() override{\
				auto pEffectDerived = this;\
				Release(pEffectDerived);\
				return pEffectDerived;\
			}\

namespace Iris2D {
	namespace Effect {
		class EffectBase: public Proxy<IEffect>, public IEffect {
		public:
			EffectBase(IEffect* pProxied): Proxy<IEffect>(pProxied) {}
			virtual EffectBase* AutoRelease() = 0;
			virtual ~EffectBase() = default;
		};
	}
}

#endif //_H_EFFECT_BASE_
