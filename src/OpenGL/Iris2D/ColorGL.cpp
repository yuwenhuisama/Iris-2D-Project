#include "OpenGL/Iris2D/ColorGL.h"


namespace Iris2D
{
	ColorGL * ColorGL::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		auto pColor = new ColorGL();
		pColor->IncreamRefCount();

		pColor->m_n4Color = { cRed, cGreen, cBlue, cAlpha };
		return pColor;
	}

	void ColorGL::Release(ColorGL *& pColor)
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

	void ColorGL::SetRed(unsigned char cRed)
	{
		m_n4Color.x = cRed;
		m_bModifyDirtyFlag = true;
	}

	unsigned char ColorGL::GetRed() const
	{
		return m_n4Color.x;
	}

	void ColorGL::SetGreen(unsigned char cGreen)
	{
		m_n4Color.y = cGreen;
		m_bModifyDirtyFlag = true;
	}

	unsigned char ColorGL::GetGreen() const
	{
		return m_n4Color.y;
	}

	void ColorGL::SetBlue(unsigned char cBlue)
	{
		m_n4Color.z = cBlue;
		m_bModifyDirtyFlag = true;
	}

	unsigned char ColorGL::GetBlue() const
	{
		return m_n4Color.z;
	}

	void ColorGL::SetAlpha(unsigned char cAlpha)
	{
		m_n4Color.w = cAlpha;
		m_bModifyDirtyFlag = true;
	}

	unsigned char ColorGL::GetAlpha() const
	{
		return m_n4Color.w;
	}

	void ColorGL::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha)
	{
		SetRed(cRed);
		SetGreen(cGreen);
		SetBlue(cBlue);
		SetAlpha(cAlpha);
	}

	bool ColorGL::Modified()
	{
		return m_bModifyDirtyFlag;
	}

	void ColorGL::ModifyDone()
	{
		m_bModifyDirtyFlag = false;
	}
}