#include "OpenGL/Iris2D/Sprites/SpriteIndexedGL.h"
#include "Common/Iris2D/Bitmap.h"
#include "OpenGL/Iris2D/BitmapGL.h"

namespace Iris2D {

	ResultCode SpriteIndexedGL::Create(Viewport* pViewport) {
		return IRR_Success;
	}

	void SpriteIndexedGL::Release(SpriteIndexedGL*& pSprite) {
	}

	ResultCode SpriteIndexedGL::SetBitmap(Bitmap*& pBitmap) {
		if (pBitmap == m_pBitmap) {
			return IRR_Success;
		}

		Bitmap::Release(m_pBitmap);

		if (!pBitmap) {
			m_pBitmap = nullptr;
			return IRR_Success;
		}

		RefferAssign<BitmapGL*>(m_pBitmap, pBitmap);

		return IRR_Success;
	}

	Bitmap* SpriteIndexedGL::GetBitmap() const {
		return m_pBitmap;
	}

	void SpriteIndexedGL::SetOX(float fOX) {
	}

	float SpriteIndexedGL::GetOX() const {
		return 0.0f;
	}

	void SpriteIndexedGL::SetOY(float fOY) {
	}

	float SpriteIndexedGL::GetOY() const {
		return 0.0f;
	}

	ResultCode SpriteIndexedGL::Update() {
		return IRR_Success;
	}

	ResultCode SpriteIndexedGL::SetEffect(Effect::EffectBase* pEffect) {
		return IRR_Success;
	}

	ResultCode SpriteIndexedGL::Render() {
		return IRR_Success;
	}

	void SpriteIndexedGL::SetIndex(unsigned nIndex) {
	}

	unsigned SpriteIndexedGL::GetIndex() const {
		return 0;
	}

	void SpriteIndexedGL::SetIndexedAreas(const std::vector<Rect*>& vcAreas) {
	}

	void SpriteIndexedGL::SetIndexedAreas(std::vector<Rect*>&& vcAreas) {
	}

	void SpriteIndexedGL::SetSplitIndexAreas(unsigned nRow, unsigned nColumn) {
	}
}
