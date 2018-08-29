#ifndef _H_IEFFECT_
#define _H_IEFFECT_

namespace Iris2D {
	class Sprite;

	namespace Effect {
		class IEffect {
		public:
			virtual ~IEffect() = default;
			virtual bool Update() = 0;
		};
	}
}

#endif
