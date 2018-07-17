#include "DirectX/Iris2D/IrisRect.h"



namespace Iris2D
{
	IrisRect * IrisRect::Create(float fX, float fY, float fWidth, float fHeight)
	{
		auto pRect = new IrisRect();
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

	IrisRect * IrisRect::Create2(float fLeft, float fTop, float fRight, float fBottom)
	{
		auto pRect = new IrisRect();
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

	void IrisRect::Release(IrisRect *& pRect)
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

	void IrisRect::SetX(float fX)
	{
		m_f4Rect.x = fX;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetX() const
	{
		return m_f4Rect.x;
	}

	void IrisRect::SetY(float fY)
	{
		m_f4Rect.y = fY;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetY() const
	{
		return m_f4Rect.y;
	}

	void IrisRect::SetWidth(float fWidth)
	{
		m_f4Rect.z = fWidth;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetWidth() const
	{
		return m_f4Rect.z;
	}

	void IrisRect::SetHeight(float fHeight)
	{
		m_f4Rect.w = fHeight;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetHeight() const
	{
		return m_f4Rect.w;
	}

	void IrisRect::SetLeft(float fLeft)
	{
		m_f4Rect.z = m_f4Rect.x + m_f4Rect.z - fLeft;
		m_f4Rect.x = fLeft;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetLeft() const
	{
		return m_f4Rect.x;
	}

	void IrisRect::SetRight(float fRight)
	{
		m_f4Rect.z = m_f4Rect.x + fRight - m_f4Rect.x;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetRight() const
	{
		return m_f4Rect.x + m_f4Rect.z;
	}

	void IrisRect::SetTop(float fTop)
	{
		m_f4Rect.w = m_f4Rect.y + m_f4Rect.w - fTop;
		m_f4Rect.y = fTop;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetTop() const
	{
		return m_f4Rect.y;
	}

	void IrisRect::SetBottom(float fBottom)
	{
		m_f4Rect.w = m_f4Rect.y + fBottom - m_f4Rect.y;
		m_bModifyDirtyFlag = true;
	}

	float IrisRect::GetBottom() const
	{
		return m_f4Rect.y + m_f4Rect.w;
	}

	void IrisRect::Set(float fX, float fY, float fWidth, float fHeight)
	{
		SetX(fX);
		SetY(fY);
		SetWidth(fWidth);
		SetHeight(fHeight);
	}

	void IrisRect::Set2(float fLeft, float fTop, float fRight, float fBottom)
	{
		SetLeft(fLeft);
		SetTop(fTop);
		SetRight(fRight);
		SetBottom(fBottom);
	}

	bool IrisRect::Modified()
	{
		return m_bModifyDirtyFlag;
	}

	void IrisRect::ModifyDone()
	{
		m_bModifyDirtyFlag = false;
	}

}