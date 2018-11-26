#ifndef _H_SPRITE_INDEXED_GL
#define _H_SPRITE_INDEXED_GL
#include "SpriteBaseGL.h"
#include "Common/Iris2D/Sprites/ISpriteIndexed.h"
#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"
#include "OpenGL/OpenGLUtil/SpriteShaderBuffersGL.h"

namespace Iris2D {

	class Bitmap;
	class Viewport;
	class SpriteIndexedGL : public ISpriteIndexed, public SpriteBaseGL {
		REF_FRIEND_DECLARE
	private:
		unsigned int m_nCurrentIndex = 0;
		std::vector<Rect*> m_vcAreas{};

		Rect* m_pSrcRect = nullptr;

		SpriteIndexedInstanceAttributeGL m_sivBuffer{};

		unsigned int m_nRow = 0;
		unsigned int m_nColumn = 0;

	public:
		static SpriteIndexedGL* Create(const std::vector<Rect*>& vcAreas, Viewport* pViewport = nullptr);
		static SpriteIndexedGL* Create(unsigned nRow, unsigned nColumn, Viewport* pViewport = nullptr);
		static void Release(SpriteIndexedGL*& pSprite);

	public:
		void SetOX(float fOX) override;
		float GetOX() const override;
		void SetOY(float fOY) override;
		float GetOY() const override;
		ResultCode Update() override;
		ResultCode SetEffect(Effect::EffectBase* pEffect) override;
		ResultCode Render() override;
		bool NeedDiscard() const;

		void SetSrcRect(Rect *& pSrcRect);
		Rect * GetSrcRect() const;

		void SetIndex(unsigned nIndex) override;
		unsigned GetIndex() const override;

		SpriteIndexedInstanceAttributeGL GetInstanceAttribute();

		bool CheckMergeableWith(const SpriteIndexedGL* pSpriteTarget);

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

		ResultCode SetBitmap(Bitmap*& pBitmap) override;

		Bitmap* GetBitmap() const override {
			return SpriteBaseGL::GetBitmap();
		}
	};

}

#endif // !_H_SPRITE_INDEXED_GL
