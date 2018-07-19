#ifndef _H_FONT_DX_
#define _H_FONT_DX_

#include "Common/Util/RefCounter.h"
#include "DirectX/Common.h"
#include "Common/Iris2D/IFont.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D
{
	class Color;
	class Font;
	class FontDX : public Proxied<Font>, public IFont, public RefCounter
	{
	private:
		std::wstring m_wstrFontName = GetDefaultName();
		unsigned int m_nSize = GetDefaultSize();;
		bool m_bBold = GetDefaultBold();
		bool m_bItalic = GetDefaultItalic();
		bool m_bShadow = GetDefaultShadow();
		Color* m_pColor = nullptr;

	public:
		static bool Existed(const std::wstring& wstrFontName);

		static FontDX* Create(const std::wstring& wstrFontName);
		static void Release(FontDX*& pFont);

		virtual void SetName(const std::wstring& wstrFontName);
		virtual const std::wstring& GetName() const;

		virtual void SetSize(unsigned int nSize);
		virtual unsigned int GetSize() const;

		virtual void SetBold(bool bBold);
		virtual bool GetBold() const;

		virtual void SetItalic(bool bItalic);
		virtual bool GetItalic() const;

		virtual void SetShadow(bool bShadow);
		virtual bool GetShadow() const;

		virtual void SetColor(Color*& pColor);
		virtual Color* GetColor() const;

		static std::wstring GetDefaultName();
		static unsigned int GetDefaultSize();
		static bool GetDefaultBold();
		static bool GetDefaultItalic();
		static bool GetDefaultShadow();
		static Color* GetDefaultColor();

	private:
		FontDX();
		virtual ~FontDX();
	};
}
#endif // !_H_FONT_DX_
