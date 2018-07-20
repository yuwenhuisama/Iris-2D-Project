#ifndef _H_VIEWPORT_DX_
#define _H_VIEWPORT_DX_

#include "DirectX/Common.h"
#include "DirectX/Util/ViewportShaderBuffersDX.h"
#include "Common/Iris2D/IViewport.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D
{
	class SpriteDX;

	class Sprite;
	class Rect;
	class TextureDX;
	class Rect;
	class Color;
	class Viewport;

	__declspec(align(16))
	class ViewportDX : public IViewport, public Proxied<Viewport>
	{
	private:
		std::unordered_set<SpriteDX*> m_stSprits;

		ID3D11Buffer* m_pVertexBuffer = nullptr;
		TextureDX* m_pTexture = nullptr;

		ViewportVertexShaderBufferDX m_ivvsVertexBuffer;
		ViewportPixelShaderBufferDX m_ivpsPixelBuffer;

		//DirectX::XMMATRIX m_mxViewProjMatrix = DirectX::XMMatrixIdentity();

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;

		bool m_bVertexBufferDirtyFlag = false;
		bool m_bVisible = true;

		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		bool m_bSrcRectDirtyFlag = false;
		bool m_bToneDirtyFlag = false;

	public:
		static Viewport* sm_pGlobalViewport;

	public:
		/**
		* \~english
		* Create a viewport with a rectangle area.
		* @param fX The top left position of the area.
		* @param fY The top left position of the area.
		* @param nWidth The width of the area.
		* @param nHeight The height of the area.
		* @return If viewport has been created successfully pointer of ViewportDX will be returned otherwise nullptr.
		* @ see Create(RectDX* pRect, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 创建一个矩形区域的 Viewport。
		* @param fX 区域的左上角 X 坐标.
		* @param fY 区域的左上角 Y 坐标.
		* @param nWidth 区域的宽度.
		* @param nHeight 区域的高度.
		* @return 如果成功创建 Viewport ，那么将会返回该 ViewportDX 的指针，否则返回 nullptr。
		* @see Create(RectDX* pRect, IR_PARAM_RESULT)
		*/
		static ViewportDX* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		/**
		* \~english
		* Create a viewport with a rectangle area.
		* @param pRect The rect to specify the area.
		* @return If viewport has been created successfully pointer of ViewportDX will be returned otherwise nullptr.
		* @see Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 创建一个矩形区域的 Viewport。
		* @param pRect 用于确定区域的 Rect。
		* @return 如果成功创建 Viewport ，那么将会返回该 ViewportDX 的指针，否则返回 nullptr。
		* @see Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		*/
		static ViewportDX* Create(const Rect* pRect, IR_PARAM_RESULT);

		/**
		* \~english
		* Release a Viewport.
		* @param pViewport A pointer to viewport object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* 释放一个 Viewport 。
		* @param pViewport 指向将要被释放的 Viewport 的指针。当该函数被调用之后，传入的指针将会被设置成 nullptr 。
		*/
		static void Release(ViewportDX*& pViewport);

		static void ForceRelease(ViewportDX*& pViewport);

		static bool InitGlobalViewport(unsigned int nWindowWidth, unsigned int nWindowHeight);
		static void ReleaseGlobalViewport();
		static Viewport* GetGlobalViewport();

	public:

		/**
		* \~english
		* Set origin transfer position of current viewport.
		*
		* Initially, a viewport generated into screen is put at (-OX, -OY) where OX = 0 and OY = 0 defaultly and then moved to (-0X + X, OY + Y). (-OX, OY) is called origin transfer position.
		*
		* This property can be useful for rotating with any centern position.
		* @param fOX X position of origin transfer position of current viewport.
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
		* Get X position of origin transfer position of current viewport.
		* @return X position of origin transfer position of current viewport.
		*/
		/**
		* \~chinese
		* 获取当前 Viewport 的传送原点的 X 坐标。
		* @return 当前 Viewport 的传送原点的 X 坐标。
		*/
		float GetOX() const;

		/**
		* \~english
		* Set origin transfer position of current viewport.
		*
		* Initially, a viewport generated into screen is put at (-OX, -OY) where OX = 0 and OY = 0 defaultly and then moved to (-0X + X, -OY + Y). (OX, OY) is called origin transfer position.
		*
		* This property can be useful for rotating with any centern position.
		* @param fOY Y position of origin transfer position of current viewport.
		*/
		/**
		* \~chinese
		* 设置当前 Sprite 的传送原点。
		*
		* 一个新生成的 Sprite 一开始会被放到屏幕的 (-OX, -OY) 的位置（默认情况下 OX = 0 并且 OY = 0 ），然后它才会被移动到 ( -OX + X, -OY + Y ） 。( OX, OY ) 被称为传送原点。
		*
		* 这个属性在以任意点为旋转中心进行旋转的时候相当有用。
		* @param fOY 当前 Viewport 传送原点的 Y 坐标。
		*/
		void SetOY(float fOY);
		/**
		* \~english
		* Get Y position of origin transfer position of current viewport.
		* @return Y position of origin transfer position of current viewport.
		*/
		/**
		* \~chinese
		* 获取当前 Viewport 的传送原点的 Y 坐标。
		* @return 当前 Viewport 的传送原点的 Y 坐标。
		*/
		float GetOY() const;

		/**
		* \~english
		* Set a rect to limit the display content of current viewport.
		*
		* (0, 0) of current viewport is origin position of taken rect. This function can be helpful to let viewport just show a part of it.
		* @param pSrcRect A pointer to the limit rect object.
		*/
		/**
		* \~chinese
		* 设置一个 Rect 以限制当前 Viewport 显示的内容。
		*
		* 当前 Viewport 的 (0, 0)  即是传入的 Rect 的原点。这个函数便于让 Viewport 只显示它的内容的一部分。
		* @param pSrcRect 指向限制 Rect 对象的指针。
		*/
		void SetSrcRect(Rect*& pSrcRect);
		/**
		* \~english
		* Get the limit rect of current viewport.
		* @return The pointer to the limit rect object.
		*/
		/**
		* \~chinese
		* 获取当前 Viewport 的限制 Rect 的指针。
		* @return 当前 Viewport 的限制 Rect 的指针。
		*/
		Rect* GetSrcRect() const;

		/**
		* \~english
		* Set a tone object to current viewport. A tone is an object with R/G/B/A conponents, and it can influence the output of final pixels of viewport.
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
		* 为当前 Viewport 设置一个 Tone 对象。一个 Tone 是一个拥有 R/G/B/A 分量的对象，它能够影响当前 Viewport 最终输出的像素。
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
		* Get the tone object of current viewport.
		* @return The pointer to the tone object.
		*/
		/**
		* \~chinese
		* 获取当前 viewport 的 Tone 的指针。
		* @return 当前 Viewport 的 Tone 的指针。
		*/
		Tone* GetTone() const;

		bool Dispose();
		bool RenderSprite();
		bool RenderSelf();

		void AddSprite(SpriteDX* pSprite);
		void RemoveSprite(SpriteDX* pSprite);

		//void AddSprite(Sprite* pSprite);
		//void RemoveSprite(Sprite* pSprite);

	private:
		bool CreateViewportVertexBuffer(unsigned int nWidth, unsigned int nHeight);

		ViewportDX() = default;
		~ViewportDX();

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

#endif // !_H_VIEWPORT_DX_
