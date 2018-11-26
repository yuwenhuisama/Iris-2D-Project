#ifndef _H_SPRITE_INDEXED_
#define _H_SPRITE_INDEXED_

#include "Common/Iris2D/Sprites/ISpriteIndexed.h"
#include "Common/Iris2D/Proxy.h"
#include "Common/Iris2D/Sprites/SpriteBase.h"

namespace Iris2D {
	class SpriteIndexed : public Proxy<ISpriteIndexed>, public ISpriteIndexed, public SpriteBase {

	public:
		static SpriteIndexed* Create(const std::vector<Rect*>& vcAreas, Viewport* pViewport = nullptr);
		static SpriteIndexed* Create(unsigned nRow, unsigned nColumn, Viewport* pViewport = nullptr);
		static void Release(SpriteIndexed*& pSprite);

	public:
		void SetIndex(unsigned nIndex) override;
		unsigned GetIndex() const override;

		ISprite* GetAbstractProxied() const override;

	private:
		SpriteIndexed(ISpriteIndexed* pSprite);
		~SpriteIndexed() = default;

	public:
		ResultCode SetBitmap(Bitmap*& pBitmap) override {
			return SpriteBase::SetBitmap(pBitmap);
		}

		Bitmap* GetBitmap() const override {
			return SpriteBase::GetBitmap();
		}

		void SetX(float fX) override {
			SpriteBase::SetX(fX);
		}

		float GetX() const override {
			return SpriteBase::GetX();
		}

		void SetY(float fY) override {
			SpriteBase::SetY(fY);
		}

		float GetY() const override {
			return SpriteBase::GetY();
		}

		void SetZ(float fZ) override {
			SpriteBase::SetZ(fZ);
		}

		float GetZ() const override {
			return SpriteBase::GetZ();
		}

		void SetAngle(float fAngle) override {
			SpriteBase::SetAngle(fAngle);
		}

		float GetAngle() const override {
			return SpriteBase::GetAngle();
		}

		void SetZoomX(float fZoomX) override {
			SpriteBase::SetZoomX(fZoomX);
		}

		float GetZoomX() const override {
			return SpriteBase::GetZoomX();
		}

		void SetZoomY(float fZoomY) override {
			SpriteBase::SetZoomY(fZoomY);
		}

		float GetZoomY() const override {
			return SpriteBase::GetZoomY();
		}

		void SetOX(float fOX) override {
			SpriteBase::SetOX(fOX);
		}

		float GetOX() const override {
			return SpriteBase::GetOX();
		}

		void SetOY(float fOY) override {
			SpriteBase::SetOY(fOY);
		}

		float GetOY() const override {
			return SpriteBase::GetOY();
		}

		void SetMirror(bool bMirror) override {
			SpriteBase::SetMirror(bMirror);
		}

		bool GetMirror() const override {
			return SpriteBase::GetMirror();
		}

		void SetVisible(bool bVisible) override {
			SpriteBase::SetVisible(bVisible);
		}

		bool GetVisible() const override {
			return SpriteBase::GetVisible();
		}

		void SetOpacity(float fOpacity) override {
			SpriteBase::SetOpacity(fOpacity);
		}

		float GetOpacity() const override {
			return SpriteBase::GetOpacity();
		}

		void SetTone(Tone*& pTone) override {
			SpriteBase::SetTone(pTone);
		}

		Tone* GetTone() const override {
			return SpriteBase::GetTone();
		}

		ResultCode Update() override {
			return SpriteBase::Update();
		}

		ResultCode SetEffect(Effect::EffectBase* pEffect) override {
			return SpriteBase::SetEffect(pEffect);
		}

		Viewport* GetViewport() override {
			return SpriteBase::GetViewport();
		}
	};
}

#endif // _H_SPRITE_INDEXED_
