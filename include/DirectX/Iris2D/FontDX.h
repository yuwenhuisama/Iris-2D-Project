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

		void SetName(const std::wstring& wstrFontName) override;
		const std::wstring& GetName() const override;

		void SetSize(unsigned int nSize) override;
		unsigned int GetSize() const override;

		void SetBold(bool bBold) override;
		bool GetBold() const override;

		void SetItalic(bool bItalic) override;
		bool GetItalic() const override;

		void SetShadow(bool bShadow) override;
		bool GetShadow() const override;

		void SetColor(Color*& pColor) override;
		Color* GetColor() const override;

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
