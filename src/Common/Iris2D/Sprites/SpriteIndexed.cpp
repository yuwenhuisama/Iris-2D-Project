#include "Common/Iris2D/Sprites/SpriteIndexed.h"

namespace Iris2D {

	void SpriteIndexed::SetIndex(unsigned nIndex) {
		m_pProxied->SetIndex(nIndex);
	}

	unsigned SpriteIndexed::GetIndex() const {
		return m_pProxied->GetIndex();
	}

	void SpriteIndexed::SetIndexedAreas(const std::vector<Rect*>& vcAreas) {
		m_pProxied->SetIndexedAreas(vcAreas);
	}

	void SpriteIndexed::SetSplitIndexAreas(unsigned nRow, unsigned nColumn) {
		m_pProxied->SetSplitIndexAreas(nRow, nColumn);
	}

	ISprite* SpriteIndexed::GetAbstractProxied() const {
		return  m_pProxied;
	}

	SpriteIndexed::SpriteIndexed(ISpriteIndexed* pSprite): Proxy(pSprite) {
	}
}
