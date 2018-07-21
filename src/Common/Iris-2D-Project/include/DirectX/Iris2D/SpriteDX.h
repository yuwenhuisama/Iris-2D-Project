#ifndef _H_SPRITE_DX_
#define _H_SPRITE_DX_

#include "DirectX/Common.h"
#include "DirectX/Util/SpriteShaderBuffersDX.h"

#include "Common/Iris2D/ISprite.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D
{
	class Sprite;
	class BitmapDX;
	class RectDX;
	class ColorDX;
	class ViewportDX;

	class Bitmap;
	class Rect;
	class Color;
	class Viewport;

	typedef ColorDX ToneDX;
	__declspec(align(16))
	class SpriteDX : public Proxied<Sprite>, public ISprite
	{
	private:

		const float c_fPI = 3.14159f;
		const float c_fArcUnit = c_fPI / 180.0f;

		Bitmap* m_pBitmap = nullptr;
		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		ID3D11Buffer* m_pVertexBuffer = nullptr;

		SpriteVertexShaderBufferDX m_bfVertexShaderBuffer;
		SpritePixelShaderBufferDX  m_bfPixelShaderBuffer;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;
		float m_fAngle = 0.0f;
		float m_fZoomX = 1.0f;
		float m_fZoomY = 1.0f;

		bool m_bVisible = true;
		Viewport* m_pViewport = nullptr;

		bool m_bPositionDirtyFlag = false;
		bool m_bAngleDirtyFlag = false;
		bool m_bZoomDirtyFlag = false;
		bool m_bSrcRectDirtyFlag = false;
		bool m_bToneDirtyFlag = false;

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
		static SpriteDX* Create(Viewport* pViewport = nullptr);

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
		static void Release(SpriteDX*& pSprite);

		static void ForceRelease(SpriteDX* pSprite);

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
		* 为当前 Sprite 设置 Bitmap 对象，该 Bitmap 对象即是当前 Sprite 的显示内容。
		*
		* 如果在设置 Bitmap 之前该 Sprite 已经存在 Bitmap ，那么用户应该手动释放之前的 Bitmap ，Iris 2D 不会自动释放之前的 Bitmap 。此项特性出于对于共享 Bitmap 的考虑。
		* @param pBitmap 一个 BitmapDX 对象的指针。
		*/
		void SetBitmap(Bitmap*& pBitmap);
		Bitmap* GetBitmap() const;

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
		*/
		/**
		* \~chinese
		* 设置一个 Rect 以限制当前 Sprite 的 Bitmap 显示的内容。
		*
		* 当前 Sprite 的 Bitmap 的 (0, 0)  即是传入的 Rect 的原点。这个函数便于让 Sprite 只显示它的 Bitmap 的一部分。
		* @param pSrcRect 指向限制 Rect 对象的指针。
		*/
		void SetSrcRect(Rect*& pSrcRect);
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
		Rect* GetSrcRect() const;

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
		* 为当前 Sprite 设置一个 Tone 对象。一个 Tone 是一个拥有 R/G/B/A 分量的对象，它能够影响当前 Sprite 最终输出的像素。
		*
		* 最终输出的像素将会按照下述公式生成：
		*
		* grayFull = (preColor.r * 38 + preColor.g * 75 + preColor.b * 15) / 128
		*
		* resultColor.rgb = tone.rgb + (color.rgb + (grayFull - color.rgb) * tone.a)
		*
		* @param pTone 指向 Tone 对象的指针。
		*/
		void SetTone(Tone*& pTone);
		/**
		* \~english
		* Get the tone object of current sprite.
		* @return The pointer to the tone object.
		*/
		/**
		* \~chinese
		* 获取当前 Sprite 的 Tone 的指针。
		* @return 当前 Sprite 的 Tone 的指针。
		*/
		Tone* GetTone() const;

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
		bool Dispose();

	private:
		SpriteDX() = default;
		~SpriteDX();

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

#endif // !_H_SPRITE_DX_
