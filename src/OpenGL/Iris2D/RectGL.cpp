#include "OpenGL/Iris2D/RectGL.h"
#include "Common/Iris2D/Rect.h"

namespace Iris2D
{
	RectGL * RectGL::Create(float fX, float fY, float fWidth, float fHeight)
	{
		auto pRect = new RectGL();

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

		if (fBottom <= fTop) {
			fBottom = fTop + 1.0f;
		}

		if (fRight <= fLeft) {
			fRight = fLeft + 1.0f;
		}

		pRect->m_f4Rect = { fLeft, fTop, fRight - fLeft, fBottom - fTop };
		return pRect;
	}

	void RectGL::Release(RectGL *& pRect)
	{
		if (!pRect) {
			return;
		}

		RefferRelease(pRect);
	}

	void RectGL::SetX(float fX)
	{
		m_dcChecker.Assign(m_f4Rect.x, fX, m_hModified);
	}

	float RectGL::GetX() const
	{
		return m_f4Rect.x;
	}

	void RectGL::SetY(float fY)
	{
		m_dcChecker.Assign(m_f4Rect.y, fY, m_hModified);
	}

	float RectGL::GetY() const
	{
		return m_f4Rect.y;
	}

	void RectGL::SetWidth(float fWidth)
	{
		if (fWidth <= 0) {
			return;
		}
		m_dcChecker.Assign(m_f4Rect.z, fWidth, m_hModified);
	}

	float RectGL::GetWidth() const
	{
		return m_f4Rect.z;
	}

	void RectGL::SetHeight(float fHeight)
	{
		if (fHeight <= 0) {
			return;
		}
		m_dcChecker.Assign(m_f4Rect.w, fHeight, m_hModified);
	}

	float RectGL::GetHeight() const
	{
		return m_f4Rect.w;
	}

	void RectGL::SetLeft(float fLeft)
	{
		if (fLeft >= GetRight()) {
			return;
		}
		SetWidth(m_f4Rect.x + m_f4Rect.z - fLeft);
		m_f4Rect.x = fLeft;
	}

	float RectGL::GetLeft() const
	{
		return m_f4Rect.x;
	}

	void RectGL::SetRight(float fRight)
	{
		if (fRight <= GetLeft()) {
			return;
		}
		SetWidth(fRight - m_f4Rect.x);
	}

	float RectGL::GetRight() const
	{
		return m_f4Rect.x + m_f4Rect.z;
	}

	void RectGL::SetTop(float fTop)
	{
		if (fTop >= GetBottom()) {
			return;
		}
		SetHeight(m_f4Rect.y + m_f4Rect.w - fTop);
		m_f4Rect.y = fTop;
	}

	float RectGL::GetTop() const
	{
		return m_f4Rect.y;
	}

	void RectGL::SetBottom(float fBottom)
	{
		if (fBottom <= GetTop()) {
			return;
		}

		SetHeight(fBottom - m_f4Rect.y);
	}

	float RectGL::GetBottom() const
	{
		return m_f4Rect.y + m_f4Rect.w;
	}

	void RectGL::Set(float fX, float fY, float fWidth, float fHeight)
	{
		if (fWidth <= 0 || fHeight <= 0) {
			return;
		}

		SetX(fX);
		SetY(fY);
		SetWidth(fWidth);
		SetHeight(fHeight);
	}

	void RectGL::Set2(float fLeft, float fTop, float fRight, float fBottom)
	{
		if (fLeft >= fRight || fRight <= fLeft || fTop >= fBottom || fBottom <= fTop) {
			return;
		}

		SetLeft(fLeft);
		SetTop(fTop);
		SetRight(fRight);
		SetBottom(fBottom);
	}

	bool RectGL::Modified() const
	{
		return m_dcChecker.IsDirty(m_hModified);
	}

	void RectGL::ModifyDone()
	{
		m_dcChecker.ResetDirty(m_hModified);
	}

	bool RectGL::CheckInsectionWith(const Rect* pRect) {
		return !(GetLeft() > pRect->GetRight() || GetTop() > pRect->GetBottom() || pRect->GetLeft() > GetRight() || pRect->GetTop() > GetBottom());
	}

	RectGL::RectGL() {
		m_hModified = m_dcChecker.Register();
	}

}