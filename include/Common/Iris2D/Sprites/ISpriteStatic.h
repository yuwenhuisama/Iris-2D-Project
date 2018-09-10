#ifndef _H_ISPRITE_STATIC_
#define _H_ISPRITE_STATIC_

#include "Common/Iris2D/Sprites/ISprite.h"

namespace Iris2D {
	class ISpriteStatic : virtual public ISprite {
	public:
		virtual void SetSrcRect(Rect*& pSrcRect) = 0;
		virtual Rect* GetSrcRect() const = 0;
	};
}

#endif // !_H_ISPRITE_STATIC_
