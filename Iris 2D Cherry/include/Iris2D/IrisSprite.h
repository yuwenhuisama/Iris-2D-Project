#ifndef _H_IRISSPRITE_

#include "../IrisCommon.h"
#include "Iris2D Util/IrisSpriteMatrixBuffer.h"

namespace Iris2D
{
	class IrisBitmap;
	__declspec(align(16)) 
#if ENGLISH
		/**
		* Sprite class of Iris 2D
		*
		* A sprite abustractly represents something displayed on screen, further more, a sprite usually needs a bitmap to get an image to display or sprite won't show anything.
		*
		* A sprite can control the position, the scaling size, the angle and other displaying properties for an image, and it's the most basic element of 2D games.
		*/
#elif CHINESE
		/**
		* Iris 2D Sprite 类
		*
		* 一个 Sprite 抽象地表示了显示在屏幕上的任何东西，进一步地，一个 Sprite 一般都需要一个 Bitmap 来显示图片等，否则将不会展示任何东西。
		*
		* 一个精灵可以控制显示内容的位置、缩放尺寸、角度以及其他显示属性，它是 2D 游戏最基本的元素。
		*/
#endif
	class IrisSprite
	{
	private:

		const float c_fPI = 3.14159f;
		const float c_fArcUnit = c_fPI / 180.0f;

		IrisBitmap* m_pBitmap = nullptr;
		ID3D11Buffer* m_pVertexBuffer = nullptr;

		IrisSpriteMatrixBuffer m_mbMatrixBuffer;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;
		float m_fAngle = 0.0f;
		float m_fZoomX = 1.0f;
		float m_fZoomY = 1.0f;

		bool m_bPositionDirtyFlag = false;
		bool m_bAngleDirtyFlag = false;
		bool m_bZoomDirtyFlag = false;

	public:
#if ENGLISH
		/**
		* Create a sprite object.
		* @return If sprite has been created successfully pointer of IrisSprite will be returned otherwise nullptr.
		*/
#elif CHINESE
		/**
		* 创建一个 Sprite 对象。
		* @return 如果 Sprite 对象创建成功那么返回它的指针否则返回 nullptr。
		*/
#endif
		static IrisSprite* Create();

#if ENGLISH
		/**
		* Release a sprite.
		* @param pSprite A pointer to sprite object to be released. After this function called, pointer taken will be set to nullptr.
		*/
#elif CHINESE
		/**
		* 释放一个 Sprite 对象。
		* @param pSprite 指向将要被释放的 Sprite 对象的指针。当该函数被调用之后，传入的指针将会被设置为 nullptr。
		*/
#endif
		static void Release(IrisSprite*& pSprite);

		static void InnerRelease(IrisSprite* pSprite);

	public:
		void SetBitmap(IrisBitmap* pBitmap);
		IrisBitmap* GetBitmap() const;

		void SetX(float fX);
		float GetX() const;

		void SetY(float fY);
		float GetY() const;

		void SetZ(float fZ);
		float GetZ() const;

		void SetAngle(float fAngle);
		float GetAngle() const;

		void SetRoomX(float fZoomX);
		float GetRoomX() const;

		void SetRoomY(float fZoomY);
		float GetRoomY() const;

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
