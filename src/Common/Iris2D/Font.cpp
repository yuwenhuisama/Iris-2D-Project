#include "Common/Iris2D/Font.h"
#include "Common/Iris2D/AppFactory.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Iris2D/Color.h"

#ifdef _WIN32
#include "DirectX/Iris2D/FontDX.h"
#endif // _WIN32


namespace Iris2D {
	Font::Font(IFont* pFont) : Proxy(pFont) {}

	void Font::SetName(const std::wstring & wstrFontName) {
		m_pProxied->SetName(wstrFontName);
	}

	const std::wstring & Font::GetName() const {
		return m_pProxied->GetName();
	}

	void Font::SetSize(unsigned int nSize) {
		m_pProxied->SetSize(nSize);
	}

	unsigned int Font::GetSize() const {
		return m_pProxied->GetSize();
	}

	void Font::SetBold(bool bBold) {
		m_pProxied->SetBold(bBold);
	}

	bool Font::GetBold() const {
		return m_pProxied->GetBold();
	}

	void Font::SetItalic(bool bItalic) {
		m_pProxied->SetItalic(bItalic);
	}

	bool Font::GetItalic() const {
		return m_pProxied->GetItalic();
	}

	void Font::SetShadow(bool bShadow) {
		m_pProxied->SetShadow(bShadow);
	}

	bool Font::GetShadow() const {
		return m_pProxied->GetShadow();
	}

	void Font::SetColor(Color *& pColor) {
		auto pProxied = pColor->GetProxied();
		m_pProxied->SetColor(pProxied);
	}

	Color * Font::GetColor() const {
		return static_cast<Proxied<Color>*>(m_pProxied->GetColor())->GetProxy();
	}

	bool Font::Existed(const std::wstring & wstrFontName) {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::Existed(wstrFontName);
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}

		return false;
	}

	Font * Font::Create(const std::wstring & wstrFontName) {
		IFont* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp= FontDX::Create(wstrFontName);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Font(pProxied);
	}

	void Font::Release(Font *& pFont) {
		auto* pProxied = pFont->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			FontDX::Release(static_cast<FontDX*>(pProxied));
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

	std::wstring Font::GetDefaultName() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultName();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return L"";
	}

	unsigned int Font::GetDefaultSize() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultSize();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return 0;
	}

	bool Font::GetDefaultBold() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultBold();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return false;
	}

	bool Font::GetDefaultItalic() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultItalic();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return false;
	}

	bool Font::GetDefaultShadow() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultShadow();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return false;
	}

	Color * Font::GetDefaultColor() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case: ApiType::DirectX :
			return FontDX::GetDefaultColor();
#endif // _WIN32
		case: ApiType::OpenGL :
			break;
		default:
			break;
		}
		return nullptr;
	}
}