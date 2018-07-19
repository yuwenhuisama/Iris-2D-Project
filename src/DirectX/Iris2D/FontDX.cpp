#include "DirectX/Iris2D/FontDX.h"
#include "DirectX/Iris2D/ColorDX.h"
#include "Common/Iris2D/Color.h"
#include "Common/Util/ProxyConvert.h"
#include <functional>

namespace Iris2D
{
	FontDX::FontDX() : RefCounter()
	{
	}
	
	FontDX::~FontDX() {
		Color::Release(m_pColor);
	}

	bool FontDX::Existed(const std::wstring & wstrFontName)
	{
		LPARAM lp = 0;
		lp = ::EnumFontsW(nullptr, wstrFontName.c_str(), [](const LOGFONTW* lplf, const TEXTMETRICW* lptm, DWORD dwType, LPARAM lpData)-> int CALLBACK { return 1; }, lp);
		return lp == 0 ? false : true;
	}

	FontDX * FontDX::Create(const std::wstring & wstrFontName)
	{
		auto pNewObject = new FontDX();
		pNewObject->IncreamRefCount();
		pNewObject->m_wstrFontName = wstrFontName;

		return pNewObject;
	}

	void FontDX::Release(FontDX *& pFont)
	{
		if (!pFont) {
			return;
		}

		pFont->DecreamRefCount();
		if (pFont->GetRefCount() == 0) {
			delete pFont;
			pFont = nullptr;
		}
	}

	void FontDX::SetName(const std::wstring & wstrFontName)
	{
		m_wstrFontName = wstrFontName;
	}

	const std::wstring & FontDX::GetName() const
	{
		return m_wstrFontName;
	}

	void FontDX::SetSize(unsigned int nSize)
	{
		m_nSize = nSize < 0 ? GetDefaultSize() : nSize;
	}
	
	unsigned int FontDX::GetSize() const
	{
		return m_nSize;
	}

	void FontDX::SetBold(bool bBold)
	{
		m_bBold = bBold;
	}

	bool FontDX::GetBold() const
	{
		return m_bBold;
	}

	void FontDX::SetItalic(bool bItalic)
	{
		m_bItalic = bItalic;
	}

	bool FontDX::GetItalic() const
	{
		return m_bItalic;
	}

	void FontDX::SetShadow(bool bShadow)
	{
		m_bShadow = bShadow;
	}

	bool FontDX::GetShadow() const
	{
		return m_bShadow;
	}

	Color * FontDX::GetColor() const
	{
		return m_pColor;
	}

	void FontDX::SetColor(Color *& pColor) {
		Color::Release(m_pColor);
		
		auto pTmp = GetProxied<ColorDX*>(pColor);
		pTmp->IncreamRefCount();
		m_pColor = pColor;
	}


	std::wstring FontDX::GetDefaultName()
	{
		return L"ËÎÌו";
	}

	unsigned int FontDX::GetDefaultSize()
	{
		return 20;
	}

	bool FontDX::GetDefaultBold()
	{
		return false;
	}

	bool FontDX::GetDefaultItalic()
	{
		return false;
	}

	bool FontDX::GetDefaultShadow()
	{
		return false;
	}

	Color * FontDX::GetDefaultColor()
	{
		static Color* pDefaultColor = Color::Create(0, 0, 0, 255);
		return pDefaultColor;
	}
}
