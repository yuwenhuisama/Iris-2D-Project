#include "Common.h"
#include "AppFactory.h"

#ifdef _WIN32
#include "DirectX/Iris2D/ColorDX.h"
#include "..\..\..\include\Common\Iris2D\Color.h"
#endif // _WIN32


namespace Iris2D {
	Color::Color(IColor * pProxied) : Proxy(pProxied) {}

	Color * Color::Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		IColor* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = ColorDX::Create(cRed, cGreen, cBlue, cAlpha);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Color(pProxied);
	}

	void Color::Release(Color *& pColor) {
		auto* pProxied = pColor->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			ColorDX::Release(static_cast<ColorDX*>(pProxied));
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
		m_pProxied->SetGreen(cGreen)
	}

	unsigned char Color::GetGreen() const {
		return m_pProxied->GetGreen();
	}

	void Color::SetBlue(unsigned char cBlue) {
		m_pProxied->SetBlue(cGreen)
	}

	unsigned char Color::GetBlue() const {
		m_pProxied->GetBlue()
	}

	void Color::SetAlpha(unsigned char cAlpha) {
		m_pProxied->SetAlpha(cAlpha)
	}

	unsigned char Color::GetAlpha() const {
		return m_pProxied->GetAlpha();
	}

	void Color::Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
		m_pProxied->Set(cRed, cGreen, cBlue, cAlpha);
	}
};
