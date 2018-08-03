#include "OpenGL/Iris2D/RectGL.h"



namespace Iris2D
{
	RectGL * RectGL::Create(float fX, float fY, float fWidth, float fHeight)
	{
		auto pRect = new RectGL();
		pRect->IncreamRefCount();

		if (fWidth <= 0) {
			fWidth = 1.0f;
		}

		if (fHeight <= 0) {
			fHeight = 1.0f;
		}

		pRect->m_f4Rect = { fX, fY, fWidth, fHeight };
		return pRect;
	}

	RectGL * RectGL::Create2(float fLeft, float fTop, float fRight, float fBottom)
	{
		auto pRect = new RectGL();
		pRect->IncreamRefCount();

		if (fBottom <= fTop) {
			fBottom = fTop + 1;
		}

		if (fRight <= fLeft) {
			fRight = fLeft + 1;
		}

		pRect->m_f4Rect = { fLeft, fTop, fRight - fLeft, fBottom - fTop };
		return pRect;
	}

	void RectGL::Release(RectGL *& pRect)
	{
		if (!pRect) {
			return;
		}

		pRect->DecreamRefCount();
		if (pRect->GetRefCount() == 0) {
			delete pRect;
			pRect = nullptr;
		}
	}

	void RectGL::SetX(float fX)
	{
		m_f4Rect.x = fX;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetX() const
	{
		return m_f4Rect.x;
	}

	void RectGL::SetY(float fY)
	{
		m_f4Rect.y = fY;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetY() const
	{
		return m_f4Rect.y;
	}

	void RectGL::SetWidth(float fWidth)
	{
		m_f4Rect.z = fWidth;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetWidth() const
	{
		return m_f4Rect.z;
	}

	void RectGL::SetHeight(float fHeight)
	{
		m_f4Rect.w = fHeight;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetHeight() const
	{
		return m_f4Rect.w;
	}

	void RectGL::SetLeft(float fLeft)
	{
		m_f4Rect.z = m_f4Rect.x + m_f4Rect.z - fLeft;
		m_f4Rect.x = fLeft;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetLeft() const
	{
		return m_f4Rect.x;
	}

	void RectGL::SetRight(float fRight)
	{
		m_f4Rect.z = m_f4Rect.x + fRight - m_f4Rect.x;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetRight() const
	{
		return m_f4Rect.x + m_f4Rect.z;
	}

	void RectGL::SetTop(float fTop)
	{
		m_f4Rect.w = m_f4Rect.y + m_f4Rect.w - fTop;
		m_f4Rect.y = fTop;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetTop() const
	{
		return m_f4Rect.y;
	}

	void RectGL::SetBottom(float fBottom)
	{
		m_f4Rect.w = m_f4Rect.y + fBottom - m_f4Rect.y;
		m_bModifyDirtyFlag = true;
	}

	float RectGL::GetBottom() const
	{
		return m_f4Rect.y + m_f4Rect.w;
	}

	void RectGL::Set(float fX, float fY, float fWidth, float fHeight)
	{
		SetX(fX);
		SetY(fY);
		SetWidth(fWidth);
		SetHeight(fHeight);
	}

	void RectGL::Set2(float fLeft, float fTop, float fRight, float fBottom)
	{
		SetLeft(fLeft);
		SetTop(fTop);
		SetRight(fRight);
		SetBottom(fBottom);
	}

	bool RectGL::Modified()
	{
		return m_bModifyDirtyFlag;
	}

	void RectGL::ModifyDone()
	{
		m_bModifyDirtyFlag = false;
	}

}