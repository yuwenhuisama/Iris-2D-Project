#ifndef _H_EFFECT_FLASH_
#define _H_EFFECT_FLASH_

#include "EffectBase.h"

namespace Iris2D {
	class Color;
	namespace Effect {
		class EffectFlash : public EffectBase {
		public:
			static EffectFlash* Create(Color*& pColor, unsigned int nDuration, bool bLoop);
			static void Release(EffectFlash*& pEffectFlash);

			EFFECT_AUTO_RELEASE

		public:
			bool Update() override;

		private:
			EffectFlash(IEffect* pEffect);
			~EffectFlash() = default;
		};
	}
}

#endif // _H_EFFECT_FLASH_
