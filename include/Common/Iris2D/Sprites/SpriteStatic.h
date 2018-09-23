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
	* Iris 2D Sprite ��
	*
	* һ�� Sprite ����ر�ʾ����ʾ����Ļ�ϵ��κζ�������һ���أ�һ�� Sprite һ�㶼��Ҫһ�� Bitmap ����ʾͼƬ�ȣ����򽫲���չʾ�κζ�����
	*
	* һ��������Կ�����ʾ���ݵ�λ�á����ųߴ硢�Ƕ��Լ�������ʾ���ԣ����� 2D ��Ϸ�������Ԫ�ء�
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
		* ����һ�� Sprite ����
		*
		* @param pViewport �� Sprite ������ Viewport���������Ϊ nullptr ��ô��ǰ Sprite ���ᱻ����ȫ�� Viewport ֮�С�
		* @return ��� Sprite ���󴴽��ɹ���ô��������ָ����򷵻� nullptr��
		*/
		static SpriteStatic* Create(Viewport* pViewport = nullptr);

		/**
		* \~english
		* Release a sprite.
		* @param pSprite A pointer to sprite object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* �ͷ�һ�� Sprite ����
		* @param pSprite ָ��Ҫ���ͷŵ� Sprite �����ָ�롣���ú���������֮�󣬴����ָ�뽫�ᱻ����Ϊ nullptr��
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
		 * ����һ�� Rect �����Ƶ�ǰ Sprite �� Bitmap ��ʾ�����ݡ�
		 *
		 * ��ǰ Sprite �� Bitmap �� (0, 0)  ���Ǵ���� Rect ��ԭ�㡣������������� Sprite ֻ��ʾ���� Bitmap ��һ���֡�
		 * @param pSrcRect ָ������ Rect �����ָ�롣
		 */
		void SetSrcRect(Rect*& pSrcRect) override;
		
		/**
		 * \~english
		 * Get the limit rect of current sprite.
		 * @return The pointer to the limit rect object.
		 */
		 /**
		 * \~chinese
		 * ��ȡ��ǰ Sprite ������ Rect ��ָ�롣
		 * @return ��ǰ Sprite ������ Rect ��ָ�롣
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
