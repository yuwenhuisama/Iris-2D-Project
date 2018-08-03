#include "DirectX/Iris2D/RectDX.h"



namespace Iris2D
{
	RectDX * RectDX::Create(float fX, float fY, float fWidth, float fHeight)
	{
		auto pRect = new RectDX();
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

	RectDX * RectDX::Create2(float fLeft, float fTop, float fRight, float fBottom)
	{
		auto pRect = new RectDX();
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

	void RectDX::Release(RectDX *& pRect)
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

	void RectDX::SetX(float fX)
	{
		m_dcChecker.Assign(m_f4Rect.x, fX, m_hModified);
		//m_f4Rect.x = fX;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetX() const
	{
		return m_f4Rect.x;
	}

	void RectDX::SetY(float fY)
	{
		m_dcChecker.Assign(m_f4Rect.y, fY, m_hModified);
		//m_f4Rect.y = fY;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetY() const
	{
		return m_f4Rect.y;
	}

	void RectDX::SetWidth(float fWidth)
	{
		m_dcChecker.Assign(m_f4Rect.z, fWidth, m_hModified);
		//m_f4Rect.z = fWidth;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetWidth() const
	{
		return m_f4Rect.z;
	}

	void RectDX::SetHeight(float fHeight)
	{
		m_dcChecker.Assign(m_f4Rect.w, fHeight, m_hModified);
		//m_f4Rect.w = fHeight;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetHeight() const
	{
		return m_f4Rect.w;
	}

	void RectDX::SetLeft(float fLeft)
	{
		SetWidth(m_f4Rect.x + m_f4Rect.z - fLeft);
		m_dcChecker.Assign(m_f4Rect.x, fLeft, m_hModified);

		//m_f4Rect.z = m_f4Rect.x + m_f4Rect.z - fLeft;
		//m_f4Rect.x = fLeft;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetLeft() const
	{
		return m_f4Rect.x;
	}

	void RectDX::SetRight(float fRight)
	{
		m_dcChecker.Assign(m_f4Rect.z, fRight, m_hModified);
		//m_f4Rect.z = m_f4Rect.x + fRight - m_f4Rect.x;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetRight() const
	{
		return m_f4Rect.x + m_f4Rect.z;
	}

	void RectDX::SetTop(float fTop)
	{
		SetHeight(m_f4Rect.y + m_f4Rect.w - fTop);
		m_dcChecker.Assign(m_f4Rect.y, fTop, m_hModified);

		//m_f4Rect.w = m_f4Rect.y + m_f4Rect.w - fTop;
		//m_f4Rect.y = fTop;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetTop() const
	{
		return m_f4Rect.y;
	}

	void RectDX::SetBottom(float fBottom)
	{
		SetHeight(m_f4Rect.y + fBottom - m_f4Rect.y);
		//m_f4Rect.w = m_f4Rect.y + fBottom - m_f4Rect.y;
		//m_bModifyDirtyFlag = true;
	}

	float RectDX::GetBottom() const
	{
		return m_f4Rect.y + m_f4Rect.w;
	}

	void RectDX::Set(float fX, float fY, float fWidth, float fHeight)
	{
		SetX(fX);
		SetY(fY);
		SetWidth(fWidth);
		SetHeight(fHeight);
	}

	void RectDX::Set2(float fLeft, float fTop, float fRight, float fBottom)
	{
		SetLeft(fLeft);
		SetTop(fTop);
		SetRight(fRight);
		SetBottom(fBottom);
	}

	bool RectDX::Modified()
	{
		m_dcChecker.ResetDirty(m_hModified);
		//return m_bModifyDirtyFlag;
	}

	void RectDX::ModifyDone()
	{
		m_hModified = m_dcChecker.Register();
		//m_bModifyDirtyFlag = false;
	}
	RectDX::RectDX() {
		m_hModified = m_dcChecker.Register();
	}


}