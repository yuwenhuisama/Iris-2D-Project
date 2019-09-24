#include "Common/Iris2D/Font.h"
#include "Common/Iris2D/AppFactory.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Iris2D/Color.h"

#include "Common/Util/ProxyConvert.h"

#include "OpenGL/Iris2D/FontGL.h"
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
		m_pProxied->SetColor(pColor);
	}

	Color * Font::GetColor() const {
		return m_pProxied->GetColor();
	}

	bool Font::Existed(const std::wstring & wstrFontName) {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::Existed(wstrFontName);
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::Existed(wstrFontName);
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}

		return false;
	}

	Font * Font::Create(const std::wstring & wstrFontName) {
		Font* pFont = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp= FontDX::Create(wstrFontName);
			pFont = new Font(pTmp);
			pFont->SetProxied(pTmp);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL: {
			auto pTmp = FontGL::Create(wstrFontName);
			pFont = new Font(pTmp);
			pFont->SetProxied(pTmp);
		}
			break;
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}

		return pFont;
	}

	void Font::Release(Font *& pFont) {
		if (!pFont) {
			return;
		}

		auto pProxied = pFont->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			FontDX::Release(reinterpret_cast<FontDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			FontGL::Release(reinterpret_cast<FontGL*&>(pProxied));
			break;
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pFont;
			pFont = nullptr;
		}
	}

	std::wstring Font::GetDefaultName() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultName();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultName();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return L"";
	}

	unsigned int Font::GetDefaultSize() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultSize();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultSize();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return 0;
	}

	bool Font::GetDefaultBold() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultBold();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultBold();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return false;
	}

	bool Font::GetDefaultItalic() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultItalic();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultItalic();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return false;
	}

	bool Font::GetDefaultShadow() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultShadow();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultShadow();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return false;
	}

	Color * Font::GetDefaultColor() {
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			return FontDX::GetDefaultColor();
#endif // _WIN32
		case ApiType::OpenGL:
			return FontGL::GetDefaultColor();
		case ApiType::Vulkan:
			break;
			/*
			break;
		default:
			break;
			*/
		}
		return nullptr;
	}
}