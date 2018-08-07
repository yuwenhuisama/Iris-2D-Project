#ifndef _H_IEFFECT_
#define _H_IEFFECT_

namespace Iris2D {
	class Sprite;

	namespace Effect {
		class IEffect {
		public:
			virtual ~IEffect() = default;
			virtual bool Update(const Sprite* pSprite) = 0;
		};
	}
}

#endif