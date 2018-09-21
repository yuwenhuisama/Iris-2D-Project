#ifndef _H_ISPRITE_INDEXED_
#define _H_ISPRITE_INDEXED_

#include "Common/Iris2D/Sprites/ISprite.h"
#include <vector>

namespace Iris2D {
	class ISpriteIndexed : virtual public ISprite {
	public:
		virtual void SetIndex(unsigned int nIndex) = 0;
		virtual unsigned int GetIndex() const = 0;
		virtual void SetIndexedAreas(const std::vector<Rect*>& vcAreas) = 0;
		virtual void SetIndexedAreas(std::vector<Rect*>&& vcAreas) = 0;
		virtual void SetSplitIndexAreas(unsigned int nRow, unsigned int nColumn) = 0;
	};
}

#endif
