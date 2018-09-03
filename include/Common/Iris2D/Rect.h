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
	* Iris 2D Rect ��
	*
	* һ�� Rect ��������Ļ�ϵ�һ����������
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
		* ����һ�� Rect��
		*
		* @param fX ���ɵ� Rect ���Ͻǵ� X ���ꡣ
		* @param fY ���ɵ� Rect ���Ͻǵ� Y ���ꡣ
		* @param fWidth ���ɵ� Rect �Ŀ�ȡ�
		* @param fHeight ���ɵ� Rect �ĸ߶ȡ�
		* @return ���ɵ� Rect ��ָ�롣
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
		* ����һ�� Rect��
		*
		* @param fLeft ���ɵ� Rect ��߱ߵ� X ���ꡣ
		* @param fTop ���ɵ� Rect �ϱ߱ߵ� Y ���ꡣ
		* @param fRight ���ɵ� Rect �ұ߱ߵ� X ���ꡣ
		* @param fBottom ���ɵ� Rect �±߱ߵ� Y ���ꡣ
		* @return ���ɵ� Rect ��ָ�롣
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
		* �ͷ�һ�� Rect ����
		* @param pRect ָ��Ҫ���ͷŵ� Rect �����ָ�롣���ú���������֮�󣬴����ָ�뽫�ᱻ����Ϊ nullptr��
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
		* ���õ�ǰ Rect ���Ͻǵ�� X ���ꡣ
		* @param fX ��ǰ Rect ���Ͻǵ�� X ���ꡣ
		*/
		void SetX(float fX) override;
		/**
		* \~english
		* Get the x position of left top point of current rect.
		* @return The x position of left top point of current rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect ���Ͻǵ�� X ���ꡣ
		* @return ��ǰ Rect ���Ͻǵ�� X ���ꡣ
		*/
		float GetX() const override;

		/**
		* \~english
		* Set the y position of left top point of current rect.
		* @param fY The y position of left top position of current rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect ���Ͻǵ�� Y ���ꡣ
		* @param fY ��ǰ Rect ���Ͻǵ�� Y ���ꡣ
		*/
		void SetY(float fY) override;
		/**
		* \~english
		* Get the y position of left top point of current rect.
		* @return The y position of left top point of current rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect ���Ͻǵ�� Y ���ꡣ
		* @return ��ǰ Rect ���Ͻǵ�� Y ���ꡣ
		*/
		float GetY() const override;

		/**
		* \~english
		* Set the width of current rect.
		* @param fWidth The width of current rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �Ŀ�ȡ�
		* @param fWidth ��ǰ Rect �Ŀ�ȡ�
		*/
		void SetWidth(float fWidth) override;
		/**
		* \~english
		* Set the width of current rect.
		* @return The width of current rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �Ŀ�ȡ�
		* @return ��ǰ Rect �Ŀ�ȡ�
		*/
		float GetWidth() const override;

		/**
		* \~english
		* Set the height of current rect.
		* @param fHeight The width of current rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �ĸ߶ȡ�
		* @param fHeight ��ǰ Rect �ĸ߶ȡ�
		*/
		void SetHeight(float fHeight) override;
		/**
		* \~english
		* Set the height of current rect.
		* @return The height of current rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �ĸ߶ȡ�
		* @return ��ǰ Rect �ĸ߶ȡ�
		*/
		float GetHeight() const override;

		/**
		* \~english
		* Set the x position of left edge of current rect.
		* @param fLeft The x position of left edge of created rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect ��߱ߵ� X ���ꡣ
		* @param fLeft ��ǰ Rect ��߱ߵ� X ���ꡣ
		*/
		void SetLeft(float fLeft) override;
		/**
		* \~english
		* Get the x position of left edge of current rect.
		* @return The x position of left edge of created rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect ��߱ߵ� X ���ꡣ
		* @return ��ǰ Rect ��߱ߵ� X ���ꡣ
		*/
		float GetLeft() const override;

		/**
		* \~english
		* Set the y position of top edge of current rect.
		* @param fTop The y position of top edge of created rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �ϱ߱ߵ� X ���ꡣ
		* @param fTop ��ǰ Rect �ϱ߱ߵ� X ���ꡣ
		*/
		void SetTop(float fTop) override;
		/**
		* \~english
		* Get the y position of top edge of current rect.
		* @return The y position of top edge of created rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect �ϱ߱ߵ� X ���ꡣ
		* @return ��ǰ Rect �ϱ߱ߵ� X ���ꡣ
		*/
		float GetTop() const override;

		/**
		* \~english
		* Set the x position of right edge of current rect.
		* @param fRight The x position of right edge of created rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �ұ߱ߵ� X ���ꡣ
		* @param fRight ��ǰ Rect �ұ߱ߵ� X ���ꡣ
		*/
		void SetRight(float fRight) override;
		/**
		* \~english
		* Get the x position of right edge of current rect.
		* @return The x position of right edge of created rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect �ұ߱ߵ� X ���ꡣ
		* @return ��ǰ Rect �ұ߱ߵ� X ���ꡣ
		*/
		float GetRight() const override;

		/**
		* \~english
		* Set the y position of bottom edge of current rect.
		* @param fBottom The y position of bottom edge of created rect.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Rect �±߱ߵ� X ���ꡣ
		* @param fBottom ��ǰ Rect �±߱ߵ� X ���ꡣ
		*/
		void SetBottom(float fBottom) override;
		/**
		* \~english
		* Get the y position of bottom edge of current rect.
		* @return The y position of bottom edge of created rect.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Rect �±߱ߵ� X ���ꡣ
		* @return ��ǰ Rect �±߱ߵ� X ���ꡣ
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
		* ���õ�ǰ Rect �����ԡ�
		* @param fX ��ǰ Rect ���Ͻǵ� X ���ꡣ
		* @param fY ��ǰ Rect ���Ͻǵ� Y ���ꡣ
		* @param fWidth ��ǰ Rect �Ŀ�ȡ�
		* @param fHeight ��ǰ Rect �ĸ߶ȡ�
		* @return ��ǰ Rect ��ָ�롣
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
		 * ���õ�ǰ Rect �����ԡ�
		 * \param fLeft ��ǰ Rect ��߱ߵ� X ���ꡣ
		 * \param fTop ��ǰ Rect �ϱ߱ߵ� Y ���ꡣ
		 * \param fRight ��ǰ Rect �ұ߱ߵ� X ���ꡣ
		 * \param fBottom ��ǰ Rect �±߱ߵ� Y ���ꡣ
		 * \return ��ǰ Rect ��ָ�롣
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
		 * \param pRect Ŀ�� Rect ����
		 * \return ��� 2 �� Rect �ཻ���� true ���򷵻� false��
		 */
		bool CheckInsectionWith(const Rect* pRect) override;


		private:
			Rect(IRect* pRect);
			~Rect() = default;
	};
}

#endif // !_H_RECT_
