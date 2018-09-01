#ifndef _H_RECT_
#define _H_RECT_

#include "Proxy.h"
#include "IRect.h"

namespace Iris2D {
	/**
	* \~english
	* Rect class of Iris 2D
	*
	* A rect represent a rectangle region of screen.
	*/
	/**
	* \~chinese
	* Iris 2D Rect 类
	*
	* 一个 Rect 代表了屏幕上的一个矩形区域。
	*/
	class Rect : public IRect, public Proxy<IRect> {
	public:
		/**
		* \~english
		* Create a rect.
		*
		* @param fX X position of left top point of created rect.
		* @param fY Y position of left top point of created rect.
		* @param fWidth Width of created rect.
		* @param fHeight Height of created rect.
		* @return A pointer to the created rect.
		*/
		/**
		* \~chinese
		* 生成一个 Rect。
		*
		* @param fX 生成的 Rect 左上角的 X 坐标。
		* @param fY 生成的 Rect 左上角的 Y 坐标。
		* @param fWidth 生成的 Rect 的宽度。
		* @param fHeight 生成的 Rect 的高度。
		* @return 生成的 Rect 的指针。
		* @see Create2(float fLeft, float fTop, float fRight, float fBottom)
		*/
		static Rect* Create(float fX, float fY, float fWidth, float fHeight);

		/**
		* \~english
		* Create a rect.
		*
		* @param fLeft X position of left edge of created rect.
		* @param fTop Y position of top edge of created rect.
		* @param fRight X position of right edge of created rect.
		* @param fBottom Y position of bottom edge of created rect.
		* @return A pointer to the created rect.
		*/
		/**
		* \~chinese
		* 生成一个 Rect。
		*
		* @param fLeft 生成的 Rect 左边边的 X 坐标。
		* @param fTop 生成的 Rect 上边边的 Y 坐标。
		* @param fRight 生成的 Rect 右边边的 X 坐标。
		* @param fBottom 生成的 Rect 下边边的 Y 坐标。
		* @return 生成的 Rect 的指针。
		* @see Create(float fX, float fY, float fWidth, float fHeight)
		*/
		static Rect* Create2(float fLeft, float fTop, float fRight, float fBottom);

		/**
		* \~english
		* Release a rect.
		* @param pRect A pointer to rect object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* 释放一个 Rect 对象。
		* @param pRect 指向将要被释放的 Rect 对象的指针。当该函数被调用之后，传入的指针将会被设置为 nullptr。
		*/
		static void Release(Rect*& pRect);

	public:
		/**
		* \~english
		* Set the x position of left top point of current rect.
		* @param fX The x position of left top position of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 左上角点的 X 坐标。
		* @param fX 当前 Rect 左上角点的 X 坐标。
		*/
		void SetX(float fX) override;
		/**
		* \~english
		* Get the x position of left top point of current rect.
		* @return The x position of left top point of current rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 左上角点的 X 坐标。
		* @return 当前 Rect 左上角点的 X 坐标。
		*/
		float GetX() const override;

		/**
		* \~english
		* Set the y position of left top point of current rect.
		* @param fY The y position of left top position of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 左上角点的 Y 坐标。
		* @param fY 当前 Rect 左上角点的 Y 坐标。
		*/
		void SetY(float fY) override;
		/**
		* \~english
		* Get the y position of left top point of current rect.
		* @return The y position of left top point of current rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 左上角点的 Y 坐标。
		* @return 当前 Rect 左上角点的 Y 坐标。
		*/
		float GetY() const override;

		/**
		* \~english
		* Set the width of current rect.
		* @param fWidth The width of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 的宽度。
		* @param fWidth 当前 Rect 的宽度。
		*/
		void SetWidth(float fWidth) override;
		/**
		* \~english
		* Set the width of current rect.
		* @return The width of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 的宽度。
		* @return 当前 Rect 的宽度。
		*/
		float GetWidth() const override;

		/**
		* \~english
		* Set the height of current rect.
		* @param fHeight The width of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 的高度。
		* @param fHeight 当前 Rect 的高度。
		*/
		void SetHeight(float fHeight) override;
		/**
		* \~english
		* Set the height of current rect.
		* @return The height of current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 的高度。
		* @return 当前 Rect 的高度。
		*/
		float GetHeight() const override;

		/**
		* \~english
		* Set the x position of left edge of current rect.
		* @param fLeft The x position of left edge of created rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 左边边的 X 坐标。
		* @param fLeft 当前 Rect 左边边的 X 坐标。
		*/
		void SetLeft(float fLeft) override;
		/**
		* \~english
		* Get the x position of left edge of current rect.
		* @return The x position of left edge of created rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 左边边的 X 坐标。
		* @return 当前 Rect 左边边的 X 坐标。
		*/
		float GetLeft() const override;

		/**
		* \~english
		* Set the y position of top edge of current rect.
		* @param fTop The y position of top edge of created rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 上边边的 X 坐标。
		* @param fTop 当前 Rect 上边边的 X 坐标。
		*/
		void SetTop(float fTop) override;
		/**
		* \~english
		* Get the y position of top edge of current rect.
		* @return The y position of top edge of created rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 上边边的 X 坐标。
		* @return 当前 Rect 上边边的 X 坐标。
		*/
		float GetTop() const override;

		/**
		* \~english
		* Set the x position of right edge of current rect.
		* @param fRight The x position of right edge of created rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 右边边的 X 坐标。
		* @param fRight 当前 Rect 右边边的 X 坐标。
		*/
		void SetRight(float fRight) override;
		/**
		* \~english
		* Get the x position of right edge of current rect.
		* @return The x position of right edge of created rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 右边边的 X 坐标。
		* @return 当前 Rect 右边边的 X 坐标。
		*/
		float GetRight() const override;

		/**
		* \~english
		* Set the y position of bottom edge of current rect.
		* @param fBottom The y position of bottom edge of created rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 下边边的 X 坐标。
		* @param fBottom 当前 Rect 下边边的 X 坐标。
		*/
		void SetBottom(float fBottom) override;
		/**
		* \~english
		* Get the y position of bottom edge of current rect.
		* @return The y position of bottom edge of created rect.
		*/
		/**
		* \~chinese
		* 获取当前 Rect 下边边的 X 坐标。
		* @return 当前 Rect 下边边的 X 坐标。
		*/
		float GetBottom() const override;

		/**
		* \~english
		* Set properties of current Rect.
		* @param fX X position of left top point of current rect.
		* @param fY Y position of left top point of current rect.
		* @param fWidth Width of current rect.
		* @param fHeight Height of current rect.
		* @return A pointer to current rect.
		*/
		/**
		* \~chinese
		* 设置当前 Rect 的属性。
		* @param fX 当前 Rect 左上角的 X 坐标。
		* @param fY 当前 Rect 左上角的 Y 坐标。
		* @param fWidth 当前 Rect 的宽度。
		* @param fHeight 当前 Rect 的高度。
		* @return 当前 Rect 的指针。
		* @see Set2(float fLeft, float fTop, float fRight, float fBottom)
		*/
		void Set(float fX, float fY, float fWidth, float fHeight) override;

		/**
		 * \~english
		 * Set properties of current Rect.
		 * \param fLeft X position of left edge of current rect.
		 *  \param fTop Y position of top edge of current rect.
		 * \param fRight X position of right edge of current rect.
		 * \param fBottom Y position of bottom edge of current rect.
		 * \return A pointer to current rect.
		 */
		/**
		 * \~chinese
		 * 设置当前 Rect 的属性。
		 * \param fLeft 当前 Rect 左边边的 X 坐标。
		 * \param fTop 当前 Rect 上边边的 Y 坐标。
		 * \param fRight 当前 Rect 右边边的 X 坐标。
		 * \param fBottom 当前 Rect 下边边的 Y 坐标。
		 * \return 当前 Rect 的指针。
		 * \see Set(float fX, float fY, float fWidth, float fHeight)
		 */
		void Set2(float fLeft, float fTop, float fRight, float fBottom) override;

		/**
		 * \~english
		 * \brief 
		 * \param pRect Target Rect Object.
		 * \return true if 2 rects insects with each other otherwise false.
		 */
		/**
		 * \~chinese
		 * \brief 
		 * \param pRect 目标 Rect 对象。
		 * \return 如果 2 个 Rect 相交返回 true 否则返回 false。
		 */
		bool CheckInsectionWith(const Rect* pRect) override;


		private:
			Rect(IRect* pRect);
			~Rect() = default;
	};
}

#endif // !_H_RECT_
