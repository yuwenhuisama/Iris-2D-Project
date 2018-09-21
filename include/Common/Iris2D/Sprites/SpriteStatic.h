#ifndef _H_SPRITE_STATIC_
#define _H_SPRITE_STATIC_

#include "Common/Iris2D/Sprites/ISpriteStatic.h"
#include "Common/Iris2D/Proxy.h"
#include "Common/Iris2D/Sprites/SpriteBase.h"

namespace Iris2D {
	namespace Effect {
		class EffectBase;
	}

	class Viewport;
	/**
	* \~english
	* Sprite class of Iris 2D
	*
	* A sprite abustractly represents something displayed on screen, further more, a sprite usually needs a bitmap to get an image to display or sprite won't show anything.
	*
	* A sprite can control the position, the scaling size, the angle and other displaying properties for an image, and it's the most basic element of 2D games.
	*/
	/**
	* \~chinese
	* Iris 2D Sprite 类
	*
	* 一个 Sprite 抽象地表示了显示在屏幕上的任何东西，进一步地，一个 Sprite 一般都需要一个 Bitmap 来显示图片等，否则将不会展示任何东西。
	*
	* 一个精灵可以控制显示内容的位置、缩放尺寸、角度以及其他显示属性，它是 2D 游戏最基本的元素。
	*/
	class SpriteStatic : public ISpriteStatic, public Proxy<ISpriteStatic>, public SpriteBase {
	public:
		/**
		* \~english
		* Create a sprite object.
		*
		* @param pViewport The viewport in which current sprite is put. If nullptr is taken, current sprite will be put into global viewport.
		* @return If sprite has been created successfully pointer of SpriteDX will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* 创建一个 Sprite 对象。
		*
		* @param pViewport 该 Sprite 所处的 Viewport。如果设置为 nullptr 那么当前 Sprite 将会被放在全局 Viewport 之中。
		* @return 如果 Sprite 对象创建成功那么返回它的指针否则返回 nullptr。
		*/
		static SpriteStatic* Create(Viewport* pViewport = nullptr);

		/**
		* \~english
		* Release a sprite.
		* @param pSprite A pointer to sprite object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* 释放一个 Sprite 对象。
		* @param pSprite 指向将要被释放的 Sprite 对象的指针。当该函数被调用之后，传入的指针将会被设置为 nullptr。
		*/
		static void Release(SpriteStatic*& pSprite);

		static void ForceRelease(SpriteStatic*& pSprite);

	public:
		/**
		 * \~english
		 * Set a rect to limit the display content of bitmap of current sprite.
		 *
		 * (0, 0) of current sprite's bitmap is origin position of taken rect. This function can be helpful to let sprite just show a part of current sprite's bitmap.
		 * @param pSrcRect A pointer to the limit rect object.
		 */
		/**
		 * \~chinese
		 * 设置一个 Rect 以限制当前 Sprite 的 Bitmap 显示的内容。
		 *
		 * 当前 Sprite 的 Bitmap 的 (0, 0)  即是传入的 Rect 的原点。这个函数便于让 Sprite 只显示它的 Bitmap 的一部分。
		 * @param pSrcRect 指向限制 Rect 对象的指针。
		 */
		void SetSrcRect(Rect*& pSrcRect) override;
		
		/**
		 * \~english
		 * Get the limit rect of current sprite.
		 * @return The pointer to the limit rect object.
		 */
		 /**
		 * \~chinese
		 * 获取当前 Sprite 的限制 Rect 的指针。
		 * @return 当前 Sprite 的限制 Rect 的指针。
		 */
		Rect* GetSrcRect() const override;

		ISprite* GetAbstractProxied() const override;

		private:
			SpriteStatic(ISpriteStatic* pSprite);
			~SpriteStatic() = default;

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

#endif // !_H_SPRITE_STATIC_
