#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/AppFactory.h"

#ifdef _WIN32
#include "DirectX/Iris2D/ColorDX.h"

#endif // _WIN32

namespace Iris2D {
	Color::Color(IColor * pProxied) : Proxy(pProxied) {}

	Color * Color::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		Color* pColor = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = ColorDX::Create(cRed, cGreen, cBlue, cAlpha);
			pColor = new Color(pTmp);
			pTmp->SetProxy(pColor);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return pColor;
	}

	void Color::Release(Color *& pColor) {
		if (!pColor) {
			return;
		}

		auto* pProxied = pColor->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			ColorDX::Release(reinterpret_cast<ColorDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pColor;
			pColor = nullptr;
		}
	}

	void Color::SetRed(unsigned char cRed) {
		m_pProxied->SetRed(cRed);
	}

	unsigned char Color::GetRed() const {
		return m_pProxied->GetRed();
	}

	void Color::SetGreen(unsigned char cGreen) {
		m_pProxied->SetGreen(cGreen);
	}

	unsigned char Color::GetGreen() const {
		return m_pProxied->GetGreen();
	}

	void Color::SetBlue(unsigned char cBlue) {
		m_pProxied->SetBlue(cBlue);
	}

	unsigned char Color::GetBlue() const {
		return m_pProxied->GetBlue();
	}

	void Color::SetAlpha(unsigned char cAlpha) {
		m_pProxied->SetAlpha(cAlpha);
	}

	unsigned char Color::GetAlpha() const {
		return m_pProxied->GetAlpha();
	}

	void Color::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		m_pProxied->Set(cRed, cGreen, cBlue, cAlpha);
	}
};
