#ifndef _H_FONT_
#define _H_FONT_

#include "Proxy.h"
#include "IFont.h"

namespace Iris2D {
	class Color;
	class Font: public IFont, public Proxy<IFont> {
	public:
		static bool Existed(const std::wstring& wstrFontName);

		static Font* Create(const std::wstring& wstrFontName);
		static void Release(Font*& pFont);

		static std::wstring GetDefaultName();
		static unsigned int GetDefaultSize();
		static bool GetDefaultBold();
		static bool GetDefaultItalic();
		static bool GetDefaultShadow();
		static ColorDX* GetDefaultColor();

	public:
		// Í¨¹ý IFont ¼Ì³Ð
		virtual void SetName(const std::wstring & wstrFontName) override;
		virtual const std::wstring & GetName() const override;

		virtual void SetSize(unsigned int nSize) override;
		virtual unsigned int GetSize() const override;

		virtual void SetBold(bool bBold) override;
		virtual bool GetBold() const override;

		virtual void SetItalic(bool bItalic) override;
		virtual bool GetItalic() const override;

		virtual void SetShadow(bool bShadow) override;
		virtual bool GetShadow() const override;
		
		virtual void SetColor(Color *& pColor) override;
		virtual Color * GetColor() const override;

	private:
		Font(IFont* pFont);
		~Font() = default;
	};
}

#endif // !_H_FONT_
