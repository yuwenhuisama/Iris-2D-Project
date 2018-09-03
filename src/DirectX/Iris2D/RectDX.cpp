#include "DirectX/Iris2D/RectDX.h"



namespace Iris2D
{
	RectDX * RectDX::Create(float fX, float fY, float fWidth, float fHeight)
	{
		auto pRect = new RectDX();
		pRect->IncreamRefCount();

		if (fWidth <= 0.0f) {
			fWidth = 1.0f;
		}

		if (fHeight <= 0.0f) {
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
			fBottom = fTop + 1.0f;
		}

		if (fRight <= fLeft) {
			fRight = fLeft + 1.0f;
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
	}

	float RectDX::GetX() const
	{
		return m_f4Rect.x;
	}

	void RectDX::SetY(float fY)
	{
		m_dcChecker.Assign(m_f4Rect.y, fY, m_hModified);
	}

	float RectDX::GetY() const
	{
		return m_f4Rect.y;
	}

	void RectDX::SetWidth(float fWidth)
	{
		if (fWidth <= 0) {
			return;
		}
		m_dcChecker.Assign(m_f4Rect.z, fWidth, m_hModified);
	}

	float RectDX::GetWidth() const
	{
		return m_f4Rect.z;
	}

	void RectDX::SetHeight(float fHeight)
	{
		if (fHeight <= 0) {
			return;
		}
		m_dcChecker.Assign(m_f4Rect.w, fHeight, m_hModified);
	}

	float RectDX::GetHeight() const
	{
		return m_f4Rect.w;
	}

	void RectDX::SetLeft(float fLeft)
	{
		if (fLeft >= GetRight()) {
			return;
		}
		SetWidth(m_f4Rect.x + m_f4Rect.z - fLeft);
		m_f4Rect.x = fLeft;
	}

	float RectDX::GetLeft() const
	{
		return m_f4Rect.x;
	}

	void RectDX::SetRight(float fRight)
	{
		if (fRight <= GetLeft()) {
			return;
		}
		SetWidth(fRight - m_f4Rect.x);
	}

	float RectDX::GetRight() const
	{
		return m_f4Rect.x + m_f4Rect.z;
	}

	void RectDX::SetTop(float fTop)
	{
		if (fTop >= GetBottom()) {
			return;
		}
		SetHeight(m_f4Rect.y + m_f4Rect.w - fTop);
		m_f4Rect.y = fTop;
	}

	float RectDX::GetTop() const
	{
		return m_f4Rect.y;
	}

	void RectDX::SetBottom(float fBottom)
	{
		if (fBottom <= GetTop()) {
			return;
		}
		SetHeight(fBottom - m_f4Rect.y);
	}

	float RectDX::GetBottom() const
	{
		return m_f4Rect.y + m_f4Rect.w;
	}

	void RectDX::Set(float fX, float fY, float fWidth, float fHeight)
	{
		if (fWidth <= 0 || fHeight <= 0) {
			return;
		}

		SetX(fX);
		SetY(fY);
		SetWidth(fWidth);
		SetHeight(fHeight);
	}

	void RectDX::Set2(float fLeft, float fTop, float fRight, float fBottom)
	{
		if (fLeft >= fRight || fRight <= fLeft || fTop >= fBottom || fBottom <= fTop) {
			return;
		}

		SetLeft(fLeft);
		SetTop(fTop);
		SetRight(fRight);
		SetBottom(fBottom);
	}

	bool RectDX::Modified() const
	{
		return m_dcChecker.IsDirty(m_hModified);
	}

	void RectDX::ModifyDone()
	{
		m_dcChecker.ResetDirty(m_hModified);
	}

	bool RectDX::CheckInsectionWith(const Rect* pRect) {
		// TODO: compete insection check for RectDX.
		return true;
	}

	RectDX::RectDX() {
		m_hModified = m_dcChecker.Register();
	}

}