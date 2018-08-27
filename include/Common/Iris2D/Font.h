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
		static Color* GetDefaultColor();

	public:
		// Í¨¹ý IFont ¼Ì³Ð
		void SetName(const std::wstring & wstrFontName) override;
		const std::wstring & GetName() const override;

		void SetSize(unsigned int nSize) override;
		unsigned int GetSize() const override;

		void SetBold(bool bBold) override;
		bool GetBold() const override;

		void SetItalic(bool bItalic) override;
		bool GetItalic() const override;

		void SetShadow(bool bShadow) override;
		bool GetShadow() const override;
		
		void SetColor(Color *& pColor) override;
		Color * GetColor() const override;

	private:
		Font(IFont* pFont);
		~Font() = default;
	};
}

#endif // !_H_FONT_
