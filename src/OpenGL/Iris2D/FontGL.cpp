#include "OpenGL/Iris2D/FontGL.h"

#include "Common/Util/ProxyConvert.h"
#include <functional>
#include  <codecvt>
namespace Iris2D {

	
	FT_Library FontGL::GetFTLibrary()
	{
		return m_FTLibrary;
	}

	FT_Face FontGL::GetFTFace()
	{
		return m_FTFace;
	}

	bool FontGL::Existed(const std::wstring & wstrFontName)
	{
		//return m_FTFace==nullptr?false:true;
		return false;
	}

	FontGL * FontGL::Create(const std::wstring & wstrFontName)
	{
		auto pNewObject = new FontGL();
		pNewObject->IncreamRefCount();
		pNewObject->m_wstrFontName = wstrFontName;
		if (FT_Init_FreeType(&pNewObject->m_FTLibrary))
			return nullptr;
		const wchar_t* pwText = &wstrFontName[0];

		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		auto strConverted = converter.to_bytes(wstrFontName);


		if (FT_New_Face(pNewObject->m_FTLibrary, strConverted.c_str(), 0, &pNewObject->m_FTFace))
			return nullptr;
		FT_Select_Charmap(pNewObject->m_FTFace, FT_ENCODING_UNICODE);
		FT_Set_Pixel_Sizes(pNewObject->m_FTFace, 0, pNewObject->m_nSize);

		return pNewObject;
		
		//return nullptr;
	}

	void FontGL::Release(FontGL *& pFont)
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

	void FontGL::SetName(const std::wstring & wstrFontName)
	{
		m_wstrFontName = wstrFontName;
	}

	const std::wstring & FontGL::GetName() const
	{
		return m_wstrFontName;
	}

	void FontGL::SetSize(unsigned int nSize)
	{
		m_nSize = nSize < 0 ? GetDefaultSize() : nSize;
		FT_Set_Pixel_Sizes(m_FTFace, 0, m_nSize);
	}

	unsigned int FontGL::GetSize() const
	{
		return m_nSize;
	}

	void FontGL::SetBold(bool bBold)
	{
		m_bBold = bBold;
	}

	bool FontGL::GetBold() const
	{
		return m_bBold;
	}

	void FontGL::SetItalic(bool bItalic)
	{
		if (bItalic && !m_bItalic) {
			float lean = 0.5f;
			FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = lean * 0x10000L;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
		}
		else if (!bItalic && m_bItalic) {
			float lean = 0.0f;
			FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = 0;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
		}
		m_bItalic = bItalic;
	}

	bool FontGL::GetItalic() const
	{
		return m_bItalic;
	}

	void FontGL::SetShadow(bool bShadow)
	{
		m_bShadow = bShadow;
	}

	bool FontGL::GetShadow() const
	{
		return m_bShadow;
	}

	void FontGL::SetColor(Color *& pColor)
	{
		m_pColor = pColor;
	}

	Color * FontGL::GetColor() const
	{
		return m_pColor?GetDefaultColor(): m_pColor;
	}

	std::wstring FontGL::GetDefaultName()
	{
		return L"C:/Windows/Fonts/simhei.ttf";
	}

	unsigned int FontGL::GetDefaultSize()
	{
		return 20;
	}

	bool FontGL::GetDefaultBold()
	{
		return false;
	}

	bool FontGL::GetDefaultItalic()
	{
		return false;
	}

	bool FontGL::GetDefaultShadow()
	{
		return false;
	}

	Color * FontGL::GetDefaultColor()
	{
		static Color* pDefaultColor = Color::Create(0, 0, 0, 255);
		return pDefaultColor;
	}
	FontGL::FontGL(){}
	FontGL::~FontGL()
	{
	}

	

}