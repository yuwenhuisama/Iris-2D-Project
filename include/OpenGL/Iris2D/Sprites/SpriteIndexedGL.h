#ifndef _H_SPRITE_INDEXED_GL
#define _H_SPRITE_INDEXED_GL
#include "SpriteBaseGL.h"
#include "Common/Iris2D/Sprites/ISpriteIndexed.h"

namespace Iris2D {

	class Bitmap;
	class Viewport;
	class SpriteIndexedGL : public ISpriteIndexed, public SpriteBaseGL {
	private:
		Bitmap* m_pBitmap = nullptr;
		unsigned int m_nCurrentIndex = 0;
		const std::vector<Rect*> m_vcAreas{};

	public:
		static ResultCode Create(Viewport* pViewport = nullptr);
		static void Release(SpriteIndexedGL*& pSprite);

	public:
		ResultCode SetBitmap(Bitmap*& pBitmap) override;
		Bitmap* GetBitmap() const override;
		void SetOX(float fOX) override;
		float GetOX() const override;
		void SetOY(float fOY) override;
		float GetOY() const override;
		ResultCode Update() override;
		ResultCode SetEffect(Effect::EffectBase* pEffect) override;
		ResultCode Render() override;

		void SetIndex(unsigned nIndex) override;
		unsigned GetIndex() const override;
		void SetIndexedAreas(const std::vector<Rect*>& vcAreas) override;
		void SetIndexedAreas(std::vector<Rect*>&& vcAreas) override;
		void SetSplitIndexAreas(unsigned nRow, unsigned nColumn) override;

	public:
		void SetX(float fX) override {
			SpriteBaseGL::SetX(fX);
		}

		float GetX() const override {
			return SpriteBaseGL::GetX();
		}

		void SetY(float fY) override {
			SpriteBaseGL::SetY(fY);

		}

		float GetY() const override {
			return SpriteBaseGL::GetY();
		}

		void SetZ(float fZ) override {
			SpriteBaseGL::SetZ(fZ);
		}

		float GetZ() const override {
			return SpriteBaseGL::GetZ();
		}

		void SetAngle(float fAngle) override {
			SpriteBaseGL::SetAngle(fAngle);
		}

		float GetAngle() const override {
			return SpriteBaseGL::GetAngle();
		}

		void SetZoomX(float fZoomX) override {
			SpriteBaseGL::SetZoomX(fZoomX);
		}

		float GetZoomX() const override {
			return SpriteBaseGL::GetZoomX();
		}

		void SetZoomY(float fZoomY) override {
			SpriteBaseGL::SetZoomY(fZoomY);
		}

		float GetZoomY() const override {
			return SpriteBaseGL::GetZoomY();
		}

		void SetMirror(bool bMirror) override {
			SpriteBaseGL::SetMirror(bMirror);
		}

		bool GetMirror() const override {
			return SpriteBaseGL::GetMirror();
		}

		void SetVisible(bool bVisible) override {
			SpriteBaseGL::SetVisible(bVisible);
		}

		bool GetVisible() const override {
			return SpriteBaseGL::GetVisible();
		}

		void SetOpacity(float fOpacity) override {
			SpriteBaseGL::SetOpacity(fOpacity);
		}

		float GetOpacity() const override {
			return SpriteBaseGL::GetOpacity();
		}

		void SetTone(Tone*& pTone) override {
			SpriteBaseGL::SetTone(pTone);
		}

		Tone* GetTone() const override {
			return SpriteBaseGL::GetTone();
		}

		Viewport* GetViewport() override {
			return SpriteBaseGL::GetViewport();
		}

	};

}

#endif // !_H_SPRITE_INDEXED_GL
