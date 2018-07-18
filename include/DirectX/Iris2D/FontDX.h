#ifndef _H_FONT_DX_
#define _H_FONT_DX_

#include "Common/Util/RefCounter.h"
#include "DirectX/Common.h"

namespace Iris2D
{
	class ColorDX;
	class FontDX : public RefCounter
	{
	private:
		std::wstring m_wstrFontName = GetDefaultName();
		unsigned int m_nSize = GetDefaultSize();;
		bool m_bBold = GetDefaultBold();
		bool m_bItalic = GetDefaultItalic();
		bool m_bShadow = GetDefaultShadow();
		ColorDX* m_pColor = nullptr;

	public:
		static bool Existed(const std::wstring& wstrFontName);

		static FontDX* Create(const std::wstring& wstrFontName);
		static void Release(FontDX*& pFont);

		void SetName(const std::wstring& wstrFontName);
		const std::wstring& GetName() const;

		void SetSize(unsigned int nSize);
		unsigned int GetSize() const;

		void SetBold(bool bBold);
		bool GetBold() const;

		void SetItalic(bool bItalic);
		bool GetItalic() const;

		void SetShadow(bool bShadow);
		bool GetShadow() const;

		void SetColor(ColorDX*& pColor);
		ColorDX* GetColor() const;

		static std::wstring GetDefaultName();
		static unsigned int GetDefaultSize();
		static bool GetDefaultBold();
		static bool GetDefaultItalic();
		static bool GetDefaultShadow();
		static ColorDX* GetDefaultColor();

	private:
		FontDX();
		virtual ~FontDX();
	};
}
#endif // !_H_FONT_DX_
