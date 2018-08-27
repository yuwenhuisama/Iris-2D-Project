#include "OpenGL/Iris2D/ColorGL.h"


namespace Iris2D {
	ColorGL * ColorGL::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		auto pColor = new ColorGL();

		pColor->m_n4Color = { cRed, cGreen, cBlue, cAlpha };
		return pColor;
	}

	void ColorGL::Release(ColorGL *& pColor) {
		if (!pColor) {
			return;
		}

		RefferRelease(pColor);
	}

	void ColorGL::SetRed(unsigned char cRed) {
		m_dcChecker.Assign(m_n4Color.x, cRed, m_hModified);
	}

	unsigned char ColorGL::GetRed() const {
		return m_n4Color.x;
	}

	void ColorGL::SetGreen(unsigned char cGreen) {
		m_dcChecker.Assign(m_n4Color.x, cGreen, m_hModified);
	}

	unsigned char ColorGL::GetGreen() const {
		return m_n4Color.y;
	}

	void ColorGL::SetBlue(unsigned char cBlue) {
		m_dcChecker.Assign(m_n4Color.z, cBlue, m_hModified);
	}

	unsigned char ColorGL::GetBlue() const {
		return m_n4Color.z;
	}

	void ColorGL::SetAlpha(unsigned char cAlpha) {
		m_dcChecker.Assign(m_n4Color.w, cAlpha, m_hModified);
	}

	unsigned char ColorGL::GetAlpha() const {
		return m_n4Color.w;
	}

	void ColorGL::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		SetRed(cRed);
		SetGreen(cGreen);
		SetBlue(cBlue);
		SetAlpha(cAlpha);
	}

	bool ColorGL::Modified() const {
		return m_dcChecker.IsDirty(m_hModified);
	}

	void ColorGL::ModifyDone() {
		m_dcChecker.ResetDirty(m_hModified);
	}

	ColorGL::ColorGL() {
		m_hModified = m_dcChecker.Register();
	}
}