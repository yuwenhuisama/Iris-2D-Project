#ifndef _H_IRECT_
#define _H_IRECT_

namespace Iris2D {
	class Rect;
	class IRect {
	public:
		virtual void SetX(float fX) = 0;
		virtual float GetX() const = 0;

		virtual void SetY(float fY) = 0;
		virtual float GetY() const = 0;

		virtual void SetWidth(float fWidth) = 0;
		virtual float GetWidth() const = 0;

		virtual void SetHeight(float fHeight) = 0;
		virtual float GetHeight() const = 0;

		virtual void SetLeft(float fLeft) = 0;
		virtual float GetLeft() const = 0;

		virtual void SetTop(float fTop) = 0;
		virtual float GetTop() const = 0;

		virtual void SetRight(float fRight) = 0;
		virtual float GetRight() const = 0;

		virtual void SetBottom(float fBottom) = 0;
		virtual float GetBottom() const = 0;

		virtual void Set(float fX, float fY, float fWidth, float fHeight) = 0;
		virtual void Set2(float fLeft, float fTop, float fRight, float fBottom) = 0;

		virtual bool CheckInsectionWith(const Rect* pRect) = 0;
	};
}

#endif // !_H_IRECT_
