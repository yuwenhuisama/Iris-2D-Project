#include "DirectX/Iris2D/ColorDX.h"


namespace Iris2D
{
	ColorDX * ColorDX::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		auto pColor = new ColorDX();
		pColor->IncreamRefCount();

		pColor->m_n4Color = { cRed, cGreen, cBlue, cAlpha };
		return pColor;
	}

	void ColorDX::Release(ColorDX *& pColor)
	{
		if (!pColor) {
			return;
		}

		pColor->DecreamRefCount();
		if (pColor->GetRefCount() == 0) {
			delete pColor;
			pColor = nullptr;
		}
	}

	void ColorDX::SetRed(unsigned char cRed)
	{
		m_dcChecker.Assign(m_n4Color.x, cRed, m_hModified);
		//m_n4Color.x = cRed;
		//m_bModifyDirtyFlag = true;
	}

	unsigned char ColorDX::GetRed() const
	{
		return m_n4Color.x;
	}

	void ColorDX::SetGreen(unsigned char cGreen)
	{
		m_dcChecker.Assign(m_n4Color.x, cGreen, m_hModified);
		//m_n4Color.y = cGreen;
		//m_bModifyDirtyFlag = true;
	}

	unsigned char ColorDX::GetGreen() const
	{
		return m_n4Color.y;
	}

	void ColorDX::SetBlue(unsigned char cBlue)
	{
		m_dcChecker.Assign(m_n4Color.z, cBlue, m_hModified);
		//m_n4Color.z = cBlue;
		//m_bModifyDirtyFlag = true;
	}

	unsigned char ColorDX::GetBlue() const
	{
		return m_n4Color.z;
	}

	void ColorDX::SetAlpha(unsigned char cAlpha)
	{
		m_dcChecker.Assign(m_n4Color.w, cAlpha, m_hModified);
		//m_n4Color.w = cAlpha;
		//m_bModifyDirtyFlag = true;
	}

	unsigned char ColorDX::GetAlpha() const
	{
		return m_n4Color.w;
	}

	void ColorDX::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		SetRed(cRed);
		SetGreen(cGreen);
		SetBlue(cBlue);
		SetAlpha(cAlpha);
	}

	bool ColorDX::Modified()
	{
		return m_dcChecker.IsDirty(m_hModified);
	}

	void ColorDX::ModifyDone()
	{
		m_dcChecker.ResetDirty(m_hModified);
	}
	ColorDX::ColorDX() {
		m_hModified = m_dcChecker.Register();
	}
}