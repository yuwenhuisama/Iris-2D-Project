#include "Iris2D/IrisFont.h"
#include "Iris2D/IrisColor.h"

#ifdef _H_IRISFONT_
#define _H_IRISFONT_

namespace Iris2D
{
	IrisFont::IrisFont() : IrisRefCounter()
	{
	}
	
	IrisFont::~IrisFont() {
		IrisColor::Release(m_pColor);
	}

	IrisFont * IrisFont::Create(const std::wstring & wstrFontName)
	{
		auto pNewObject = new IrisFont();
		pNewObject->IncreamRefCount();
		pNewObject->m_wstrFontName = wstrFontName;

		return pNewObject;
	}

	void IrisFont::Release(IrisFont *& pFont)
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

	void IrisFont::SetName(const std::wstring & wstrFontName)
	{
		m_wstrFontName = wstrFontName;
	}

	const std::wstring & IrisFont::GetName() const
	{
		return m_wstrFontName;
	}

	void IrisFont::SetSize(unsigned int nSize)
	{
		m_nSize = nSize;
	}
	
	unsigned int IrisFont::GetSize() const
	{
		return m_nSize;
	}

	void IrisFont::SetBold(bool bBold)
	{
		m_bBold = bBold;
	}

	bool IrisFont::GetBold() const
	{
		return m_bBold;
	}

	void IrisFont::SetItalic(bool bItalic)
	{
		m_bItalic = bItalic;
	}

	bool IrisFont::GetItalic() const
	{
		return m_bItalic;
	}

	void IrisFont::SetShadow(bool bShadow)
	{
		m_bShadow = bShadow;
	}

	bool IrisFont::GetShadow() const
	{
		return m_bShadow;
	}

	void IrisFont::SetColor(IrisColor*& pColor)
	{
		IrisColor::Release(m_pColor);

		pColor->IncreamRefCount();
		m_pColor = pColor;
	}

	IrisColor * IrisFont::GetColor() const
	{
		return m_pColor;
	}
}
#endif // _H_IRISFONT_

