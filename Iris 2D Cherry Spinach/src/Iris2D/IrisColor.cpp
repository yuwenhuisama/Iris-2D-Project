#include "Iris2D/IrisColor.h"


namespace Iris2D
{
	IrisColor * IrisColor::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		auto pColor = new IrisColor();
		pColor->IncreamRefCount();

		pColor->m_n4Color = { cRed, cGreen, cBlue, cAlpha };
		return pColor;
	}

	void IrisColor::Release(IrisColor *& pColor)
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

	void IrisColor::SetRed(unsigned char cRed)
	{
		m_n4Color.x = cRed;
		m_bModifyDirtyFlag = true;
	}

	unsigned char IrisColor::GetRed() const
	{
		return m_n4Color.x;
	}

	void IrisColor::SetGreen(unsigned char cGreen)
	{
		m_n4Color.y = cGreen;
		m_bModifyDirtyFlag = true;
	}

	unsigned char IrisColor::GetGreen() const
	{
		return m_n4Color.y;
	}

	void IrisColor::SetBlue(unsigned char cBlue)
	{
		m_n4Color.z = cBlue;
		m_bModifyDirtyFlag = true;
	}

	unsigned char IrisColor::GetBlue() const
	{
		return m_n4Color.z;
	}

	void IrisColor::SetAlpha(unsigned char cAlpha)
	{
		m_n4Color.w = cAlpha;
		m_bModifyDirtyFlag = true;
	}

	unsigned char IrisColor::GetAlpha() const
	{
		return m_n4Color.w;
	}

	void IrisColor::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		SetRed(cRed);
		SetGreen(cGreen);
		SetBlue(cBlue);
		SetAlpha(cAlpha);
	}

	bool IrisColor::Modified()
	{
		return m_bModifyDirtyFlag;
	}

	void IrisColor::ModifyDone()
	{
		m_bModifyDirtyFlag = false;
	}
}