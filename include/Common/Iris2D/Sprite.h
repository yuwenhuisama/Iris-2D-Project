#ifndef _H_SPRITE_
#define _H_SPRITE_

#include "ISprite.h"
#include "Proxy.h"

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
	class Sprite : public ISprite, public Proxy<ISprite> {
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
		static Sprite* Create(Viewport* pViewport = nullptr);

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
		static void Release(Sprite*& pSprite);

		static void ForceRelease(Sprite*& pSprite);

	public:

		/**
		* \~english
		* Set bitmap object to current sprite, which is the image content of current sprite's display.
		*
		* If a bitmap has existed in current sprite, user should manually release it as Iris 2D won't automatically release it. This feature comes from thought about shared bitmap.
		* @param pBitmap A BitmapDX object's pointer.
		*/
		/**
		* \~chinese
		* Ϊ��ǰ Sprite ���� Bitmap ���󣬸� Bitmap �����ǵ�ǰ Sprite ����ʾ���ݡ�
		*
		* ��������� Bitmap ֮ǰ�� Sprite �Ѿ����� Bitmap ����ô�û�Ӧ���ֶ��ͷ�֮ǰ�� Bitmap ��Iris 2D �����Զ��ͷ�֮ǰ�� Bitmap ���������Գ��ڶ��ڹ��� Bitmap �Ŀ��ǡ�
		* @param pBitmap һ�� BitmapDX �����ָ�롣
		*/
		void SetBitmap(Bitmap*& pBitmap) override;
		
		Bitmap* GetBitmap() const override;

		/**
		* \~english
		* Set the pixel x position of current sprite. (Under the GDI coordinate system).
		* @param fX The pixel x position of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite ������ X ���ꡣ������ GDI ����ϵ��
		* @param fX ��ǰ Sprite ������ X ���ꡣ
		*/
		void SetX(float fX) override;
		/**
		* \~english
		* Get the pixel x position of current sprite. (Under the GDI coordinate system)
		* @ return the pixel x position of current sprite.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite ������ X ���ꡣ������ GDI ����ϵ��
		* @return ��ǰ Sprite ������ X ���ꡣ
		*/
		float GetX() const override;

		/**
		* \~english
		* Set the pixel y position of current sprite. (Under the GDI coordinate system).
		* @param fY The pixel y position of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite ������ Y ���ꡣ������ GDI ����ϵ��
		* @param fY ��ǰ Sprite ������ Y ���ꡣ
		*/
		void SetY(float fY) override;
		/**
		* \~english
		* Get the pixel y position of current sprite. (Under the GDI coordinate system)
		* @ return the pixel y position of current sprite.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite ������ Y ���ꡣ������ GDI ����ϵ��
		* @return ��ǰ Sprite ������ Y ���ꡣ
		*/
		float GetY() const override;

		/**
		* \~english
		* Set the Z depth of current sprite. The depth of sprite decides the rending order of current sprite, the bigger Z is and the later sprite will be renderd.
		*
		* Range of Z is [0.0f, 9999.0f]
		* @param fZ depth of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �� Z ��ȡ� Sprite ����Ⱦ�����������Ⱦ���� Z Խ����ȾԽ����
		*
		* Z �ķ�ΧΪ [0.0f, 9999.0f]
		* @param fZ ��ǰ Sprite �� Z ��ȡ�
		*/
		void SetZ(float fZ) override;
		/**
		* \~english
		* Get the Z depth of current sprite.
		* @return Z depth of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �� Z ��ȡ�
		* @return ��ǰ Sprite �� Z ��ȡ�
		*/
		float GetZ() const override;

		/**
		* \~english
		* Set the angle of current sprite. ( Angle Degree )
		* @param fAngle The angle of current sprite
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �ĽǶȡ����Ƕ��ƣ�
		* @param fAngle ��ǰ Sprite �ĽǶȡ�
		*/
		void SetAngle(float fAngle) override;
		/**
		* \~english
		* Get the angle of current sprite. ( Angle Degree )
		* @return The angle of current sprite
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �ĽǶȡ����Ƕ��ƣ�
		* @return ��ǰ Sprite �ĽǶȡ�
		*/
		float GetAngle() const override;

		/**
		* \~english
		* Set the horizental scalling rate of current sprite.
		* @param fZoomX The horizental scalling rate of current sprite
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �ĺ��������ʡ�
		* @param fZoomX ��ǰ Sprite �ĺ��������ʡ�
		*/
		void SetZoomX(float fZoomX) override;
		/**
		* \~english
		* Get the horizental scalling rate of current sprite.
		* @return The horizental scalling rate of current sprite
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �ĺ��������ʡ�
		* @return ��ǰ Sprite �ĺ��������ʡ�
		*/
		float GetZoomX() const override;

		/**
		* \~english
		* Set the vertical scalling rate of current sprite.
		* @param fZoomY The vertical scalling rate of current sprite
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �����������ʡ�
		* @param fZoomY ��ǰ Sprite �����������ʡ�
		*/
		void SetZoomY(float fZoomY) override;
		/**
		* \~english
		* Get the vertical scalling rate of current sprite.
		* @return The vertical scalling rate of current sprite
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �����������ʡ�
		* @return ��ǰ Sprite �����������ʡ�
		*/
		float GetZoomY() const override;

		/**
		* \~english
		* Set origin transfer position of current sprite.
		*
		* Initially, a sprite generated into screen is put at (-OX, -OY) where OX = 0 and OY = 0 defaultly and then moved to (-0X + X, OY + Y). (-OX, OY) is called origin transfer position.
		*
		* This property can be useful for rotating with any centern position.
		* @param fOX X position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �Ĵ���ԭ�㡣
		*
		* һ�������ɵ� Sprite һ��ʼ�ᱻ�ŵ���Ļ�� (-OX, -OY) ��λ�ã�Ĭ������� OX = 0 ���� OY = 0 ����Ȼ�����Żᱻ�ƶ��� ( -OX + X, -OY + Y �� ��( OX, OY ) ����Ϊ����ԭ�㡣
		*
		* ����������������Ϊ��ת���Ľ�����ת��ʱ���൱���á�
		* @param fOX ��ǰ Sprite ����ԭ��� X ���ꡣ
		*/
		void SetOX(float fOX) override;
		/**
		* \~english
		* Get X position of origin transfer position of current sprite.
		* @return X position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �Ĵ���ԭ��� X ���ꡣ
		* @return ��ǰ Sprite �Ĵ���ԭ��� X ���ꡣ
		*/
		float GetOX() override;

		/**
		* \~english
		* Set origin transfer position of current sprite.
		*
		* Initially, a sprite generated into screen is put at (-OX, -OY) where OX = 0 and OY = 0 defaultly and then moved to (-0X + X, -OY + Y). (OX, OY) is called origin transfer position.
		*
		* This property can be useful for rotating with any centern position.
		* @param fOY Y position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �Ĵ���ԭ�㡣
		*
		* һ�������ɵ� Sprite һ��ʼ�ᱻ�ŵ���Ļ�� (-OX, -OY) ��λ�ã�Ĭ������� OX = 0 ���� OY = 0 ����Ȼ�����Żᱻ�ƶ��� ( -OX + X, -OY + Y �� ��( OX, OY ) ����Ϊ����ԭ�㡣
		*
		* ����������������Ϊ��ת���Ľ�����ת��ʱ���൱���á�
		* @param fOY ��ǰ Sprite ����ԭ��� Y ���ꡣ
		*/
		void SetOY(float fOY) override;
		/**
		* \~english
		* Get Y position of origin transfer position of current sprite.
		* @return Y position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �Ĵ���ԭ��� Y ���ꡣ
		* @return ��ǰ Sprite �Ĵ���ԭ��� Y ���ꡣ
		*/
		float GetOY() override;

		/**
		* \~english
		* Set if current sprite displays mirrorly.
		* @param bMirror If true is sent, current sprite will display mirrorly otherwise normally.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �Ƿ��Ծ�����ʾ��
		* @param bMirror �������Ϊ true ����ô�����Ծ�����ʾ������������ʾ��
		*/
		void SetMirror(bool bMirror) override;
		/**
		* \~english
		* Get if current sprite displays mirrorly.
		* @return If sprite displays mirrorly true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �Ƿ��Ծ�����ʾ��
		* @return ����Ǿ�����ʾ���� true �����򷵻� false ��
		*/
		bool GetMirror() override;

		/**
		* \~english
		* Set if current sprite is visible.
		* @param bVisible If true is sent, current sprite will be visible otherwise invisible.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite �Ƿ�ɼ���
		* @param bVisible ������� true ����ô��ǰ Sprite �ɼ����򲻿ɼ���
		*/
		void SetVisible(bool bVisible) override;
		/**
		* \~english
		* Get if current sprite is visible.
		* @return If current sprite is visible true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �Ƿ�ɼ���
		* @return �����ǰ Sprite �ɼ���ô���� true �����򷵻� false ��
		*/
		bool GetVisible() override;

		/**
		* \~english
		* Set opacity value of current sprite. The smaller this value is, the more transparent display of sprite will be.
		*
		* Opacity value's range is [0.0f, 255.0f]. If value taken is out of range, Iris 2D will autumatically modify it.
		*
		* @return Opacity value of current sprite.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Sprite ��͸��ֵ�����ֵԽС�� Sprite Խ�ӽ�͸����
		*
		* ͸��ֵ�ķ�ΧΪ [0.0f, 255.0f]����������ֵ���ڸ÷�Χ�ڣ���ô Iris 2D �����Զ�����������
		*
		* @return ��ǰ Sprite ��͸��ֵ��
		*/
		void SetOpacity(float fOpacity) override;
		/**
		* \~english
		* Get opacity value of current sprite.
		* @return Opacity value of current sprite.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite ��͸��ֵ��
		* @return ��ǰ Sprite ��͸��ֵ��
		*/
		float GetOpacity() override;

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

		/**
		* \~english
		* Set a tone object to current sprite. A tone is an object with R/G/B/A conponents, and it can influence the output of final pixels of current sprite.
		*
		* The result pixel will be generated using formula as follow:
		*
		* grayFull = (preColor.r * 38 + preColor.g * 75 + preColor.b * 15) / 128
		*
		* resultColor.rgb = tone.rgb + (color.rgb + (grayFull - color.rgb) * tone.a)
		*
		* @param pTone A pointer to the tone object.
		*/
		/**
		* \~chinese
		*
		* Ϊ��ǰ Sprite ����һ�� Tone ����һ�� Tone ��һ��ӵ�� R/G/B/A �����Ķ������ܹ�Ӱ�쵱ǰ Sprite ������������ء�
		*
		* ������������ؽ��ᰴ��������ʽ���ɣ�
		*
		* grayFull = (preColor.r * 38 + preColor.g * 75 + preColor.b * 15) / 128
		*
		* resultColor.rgb = tone.rgb + (color.rgb + (grayFull - color.rgb) * tone.a)
		*
		* @param pTone ָ�� Tone �����ָ�롣
		*/
		void SetTone(Tone*& pTone) override;
		/**
		* \~english
		* Get the tone object of current sprite.
		* @return The pointer to the tone object.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Sprite �� Tone ��ָ�롣
		* @return ��ǰ Sprite �� Tone ��ָ�롣
		*/
		Tone* GetTone() const override;

		/**
		* \~english
		* Update current sprite for 1 frame. If current sprite has been set an animation, call of this function will set the animation foraward 1 frame otherwise nothing will be down.
		*/
		/**
		* \~chinese
		* �Ե�ǰ�� Sprite ����һ֡�������ǰ�� Sprite �������˶�������ô���øú��������õ�ǰ Sprite �Ķ���ǰ��һ֡��
		*/
		void Update() override;

		
		/**
		 * \~english
		 * \brief Set effect to current sprite.
		 * \param pEffect A pointer to an effect object.
		 */
		 /**
		 * \~chinese
		 * \brief �Ե�ǰ Sprite ����һ����Ч��
		 * \param pEffect ָ�� Effect �����ָ��
		 */
		void SetEffect(Effect::EffectBase* pEffect) override;

		private:
			Sprite(ISprite* pSprite);
			~Sprite() = default;
	};
}

#endif // !_H_SPRITE_
