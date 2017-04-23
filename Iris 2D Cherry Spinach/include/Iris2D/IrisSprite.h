#ifndef _H_IRISSPRITE_

#include "../IrisCommon.h"
//#include "IrisTone.h"
#include "Iris2D Util/IrisSpriteShaderBuffers.h"

namespace Iris2D
{
	class IrisBitmap;
	class IrisRect;
	class IrisColor;
	typedef IrisColor IrisTone;
	__declspec(align(16)) 
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
	class IrisSprite
	{
	private:

		const float c_fPI = 3.14159f;
		const float c_fArcUnit = c_fPI / 180.0f;

		IrisBitmap* m_pBitmap = nullptr;
		IrisRect* m_pSrcRect = nullptr;
		IrisTone* m_pTone = nullptr;

		ID3D11Buffer* m_pVertexBuffer = nullptr;

		IrisSpriteVertexShaderBuffer m_bfVertexShaderBuffer;
		IrisSpritePixelShaderBuffer  m_bfPixelShaderBuffer;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;
		float m_fAngle = 0.0f;
		float m_fZoomX = 1.0f;
		float m_fZoomY = 1.0f;
		
		bool m_bVisible = true;

		bool m_bPositionDirtyFlag = false;
		bool m_bAngleDirtyFlag = false;
		bool m_bZoomDirtyFlag = false;
		bool m_bSrcRectDirtyFlag = false;
		bool m_bToneDirtyFlag = false;

	public:
		/**
		* \~english
		* Create a sprite object.
		* @return If sprite has been created successfully pointer of IrisSprite will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* 创建一个 Sprite 对象。
		* @return 如果 Sprite 对象创建成功那么返回它的指针否则返回 nullptr。
		*/
		static IrisSprite* Create();

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
		static void Release(IrisSprite*& pSprite);

		static void InnerRelease(IrisSprite* pSprite);

	public:

		/**
		* \~english
		* Set bitmap object to current sprite, which is the image content of current sprite's display.
		*
		* If a bitmap has existed in current sprite, user should manually release it as Iris 2D won't automatically release it. This feature comes from thought about shared bitmap.
		* @param bReleaseLastSrcBitmap Optional, false defaultly. If true is taken, current sprite will initiatively release the bitmap that has been already stored inside.
		* @param pBitmap A IrisBitmap object's pointer.
		*/
		/**
		* \~chinese
		* 为当前 Sprite 设置 Bitmap 对象，该 Bitmap 对象即是当前 Sprite 的显示内容。
		*
		* 如果在设置 Bitmap 之前该 Sprite 已经存在 Bitmap ，那么用户应该手动释放之前的 Bitmap ，Iris 2D 不会自动释放之前的 Bitmap 。此项特性出于对于共享 Bitmap 的考虑。
		* @param pBitmap 一个 IrisBitmap 对象的指针。
		* @param bReleaseLastSrcBitmap 可选，默认为 false 。如果设置为 true ，那么 Sprite 将会主动释放已经保存在其内部的那个 Bitmap。
		*/
		void SetBitmap(IrisBitmap* pBitmap, bool bReleaseLastSrcBitmap = false);
		IrisBitmap* GetBitmap() const;

		/**
		* \~english
		* Set the pixel x position of current sprite. (Under the GDI coordinate system).
		* @param fX The pixel x position of current sprite.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的像素 X 坐标。（基于 GDI 坐标系）
		* @param fX 当前 Sprite 的像素 X 坐标。
		*/
		void SetX(float fX);
		/**
		* \~english
		* Get the pixel x position of current sprite. (Under the GDI coordinate system)
		* @ return the pixel x position of current sprite.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的像素 X 坐标。（基于 GDI 坐标系）
		* @return 当前 Sprite 的像素 X 坐标。
		*/
		float GetX() const;

		/**
		* \~english
		* Set the pixel y position of current sprite. (Under the GDI coordinate system).
		* @param fY The pixel y position of current sprite.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的像素 Y 坐标。（基于 GDI 坐标系）
		* @param fY 当前 Sprite 的像素 Y 坐标。
		*/
		void SetY(float fY);
		/**
		* \~english
		* Get the pixel y position of current sprite. (Under the GDI coordinate system)
		* @ return the pixel y position of current sprite.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的像素 Y 坐标。（基于 GDI 坐标系）
		* @return 当前 Sprite 的像素 Y 坐标。
		*/
		float GetY() const;

		/**
		* \~english
		* Set the Z depth of current sprite. The depth of sprite decides the rending order of current sprite, the bigger Z is and the later sprite will be renderd.
		*
		* Range of Z is [0.0f, 9999.0f]
		* @param fZ depth of current sprite.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的 Z 深度。 Sprite 的深度决定了它的渲染次序， Z 越大渲染越靠后。
		*
		* Z 的范围为 [0.0f, 9999.0f]
		* @param fZ 当前 Sprite 的 Z 深度。
		*/
		void SetZ(float fZ);
		/**
		* \~english
		* Get the Z depth of current sprite.
		* @return Z depth of current sprite.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的 Z 深度。
		* @return 当前 Sprite 的 Z 深度。
		*/
		float GetZ() const;

		/**
		* \~english
		* Set the angle of current sprite. ( Angle Degree )
		* @param fAngle The angle of current sprite
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的角度。（角度制）
		* @param fAngle 当前 Sprite 的角度。
		*/
		void SetAngle(float fAngle);
		/**
		* \~english
		* Get the angle of current sprite. ( Angle Degree )
		* @return The angle of current sprite
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的角度。（角度制）
		* @return 当前 Sprite 的角度。
		*/
		float GetAngle() const;

		/**
		* \~english
		* Set the horizental scalling rate of current sprite.
		* @param fZoomX The horizental scalling rate of current sprite
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的横向拉伸率。
		* @param fZoomX 当前 Sprite 的横向拉伸率。
		*/
		void SetZoomX(float fZoomX);
		/**
		* \~english
		* Get the horizental scalling rate of current sprite.
		* @return The horizental scalling rate of current sprite
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的横向拉伸率。
		* @return 当前 Sprite 的横向拉伸率。
		*/
		float GetZoomX() const;

		/**
		* \~english
		* Set the vertical scalling rate of current sprite.
		* @param fZoomY The vertical scalling rate of current sprite
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的纵向拉伸率。
		* @param fZoomY 当前 Sprite 的纵向拉伸率。
		*/
		void SetZoomY(float fZoomY);
		/**
		* \~english
		* Get the vertical scalling rate of current sprite.
		* @return The vertical scalling rate of current sprite
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的纵向拉伸率。
		* @return 当前 Sprite 的纵向拉伸率。
		*/
		float GetZoomY() const;

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
		* 设置当前 Sprite 的传送原点。
		*
		* 一个新生成的 Sprite 一开始会被放到屏幕的 (-OX, -OY) 的位置（默认情况下 OX = 0 并且 OY = 0 ），然后它才会被移动到 ( -OX + X, -OY + Y ） 。( OX, OY ) 被称为传送原点。
		*
		* 这个属性在以任意点为旋转中心进行旋转的时候相当有用。
		* @param fOX 当前 Sprite 传送原点的 X 坐标。
		*/

		void SetOX(float fOX);
		/**
		* \~english
		* Get X position of origin transfer position of current sprite.
		* @return X position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的传送原点的 X 坐标。
		* @return 当前 Sprite 的传送原点的 X 坐标。
		*/
		float GetOX();

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
		* 设置当前 Sprite 的传送原点。
		*
		* 一个新生成的 Sprite 一开始会被放到屏幕的 (-OX, -OY) 的位置（默认情况下 OX = 0 并且 OY = 0 ），然后它才会被移动到 ( -OX + X, -OY + Y ） 。( OX, OY ) 被称为传送原点。
		*
		* 这个属性在以任意点为旋转中心进行旋转的时候相当有用。
		* @param fOY 当前 Sprite 传送原点的 Y 坐标。
		*/
		void SetOY(float fOY);
		/**
		* \~english
		* Get Y position of origin transfer position of current sprite.
		* @return Y position of origin transfer position of current sprite.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的传送原点的 Y 坐标。
		* @return 当前 Sprite 的传送原点的 Y 坐标。
		*/
		float GetOY();

		/**
		* \~english
		* Set if current sprite displays mirrorly.
		* @param bMirror If true is sent, current sprite will display mirrorly otherwise normally.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 是否以镜像显示。
		* @param bMirror 如果设置为 true ，那么将会以镜像显示，否则正常显示。
		*/
		void SetMirror(bool bMirror);
		/**
		* \~english
		* Get if current sprite displays mirrorly.
		* @return If sprite displays mirrorly true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 是否以镜像显示。
		* @return 如果是镜像显示返回 true ，否则返回 false 。
		*/
		bool GetMirror();

		/**
		* \~english
		* Set if current sprite is visible.
		* @param bVisible If true is sent, current sprite will be visible otherwise invisible.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 是否可见。
		* @param bVisible 如果传入 true ，那么当前 Sprite 可见否则不可见。
		*/
		void SetVisible(bool bVisible);
		/**
		* \~english
		* Get if current sprite is visible.
		* @return If current sprite is visible true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 是否可见。
		* @return 如果当前 Sprite 可见那么返回 true ，否则返回 false 。
		*/
		bool GetVisible();

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
		* 设置当前 Sprite 的透明值。这个值越小， Sprite 越接近透明。
		*
		* 透明值的范围为 [0.0f, 255.0f]。如果传入的值不在该范围内，那么 Iris 2D 将会自动进行修正。
		*
		* @return 当前 Sprite 的透明值。
		*/
		void SetOpacity(float fOpacity);
		/**
		* \~english
		* Get opacity value of current sprite.
		* @return Opacity value of current sprite.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的透明值。
		* @return 当前 Sprite 的透明值。
		*/
		float GetOpacity();

		/**
		* \~english
		* Set a rect to limit the display content of bitmap of current sprite.
		* 
		* (0, 0) of current sprite's bitmap is origin position of taken rect. This function can be helpful to let sprite just show a part of current sprite's bitmap.
		* @param pSrcRect A pointer to the limit rect object.
		* @param bReleaseLastSrcRect Optional, false defaultly. If true is taken, current sprite will initiatively release the rect that has been already stored inside.
		*/
		/**
		* \~chinese
		* 设置一个 Rect 以限制当前 Sprite 的 Bitmap 显示的内容。
		*
		* 当前 Sprite 的 Bitmap 的 (0, 0)  即是传入的 Rect 的原点。这个函数便于让 Sprite 只显示它的 Bitmap 的一部分。
		* @param pSrcRect 指向限制 Rect 对象的指针。
		* @param bReleaseLastSrcRect 可选，默认为 false 。如果设置为 true ，那么 Sprite 将会主动释放已经保存在其内部的那个限制 Rect 对象。
		*/
		void SetSrcRect(IrisRect* pSrcRect, bool bReleaseLastSrcRect = false);
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
		IrisRect* GetSrcRect();

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
		* @param bReleaseLastSrcTone Optional, false defaultly. If true is taken, current sprite will initiatively release the tone that has been already stored inside.
		*/
		/**
		* \~chinese
		*
		* 为当前 Sprite 设置一个 Tone 对象。一个 Tone 是一个拥有 R/G/B/A 分量的对象，它能够影响当前 Sprite 最终输出的像素。
		*
		* 最终输出的像素将会按照下述公式生成：
		*
		* grayFull = (preColor.r * 38 + preColor.g * 75 + preColor.b * 15) / 128
		*
		* resultColor.rgb = tone.rgb + (color.rgb + (grayFull - color.rgb) * tone.a)
		*
		* @param pTone 指向 Tone 对象的指针。
		* @param bReleaseLastSrcTone 可选，默认为 false 。如果设置为 true ，那么 Sprite 将会主动释放已经保存在其内部的那个 Tone 对象。
		*/
		void SetTone(IrisTone* pTone, bool bReleaseLastSrcTone = false);
		IrisTone* GetTone();

		/**
		* \~english
		* Update current sprite for 1 frame. If current sprite has been set an animation, call of this function will set the animation foraward 1 frame otherwise nothing will be down.
		*/
		/**
		* \~chinese
		* 对当前的 Sprite 更新一帧。如果当前的 Sprite 被设置了动画，那么调用该函数将会让当前 Sprite 的动画前进一帧。
		*/
		void Update();

		void Render();

	private:
		IrisSprite() = default;
		~IrisSprite();

		bool CreateSpriteVertexBuffer();

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}

	};
}


#endif // !_H_IRISSPRITE_
