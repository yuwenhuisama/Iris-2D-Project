#ifndef _H_IRISFONT_
#define _H_IRISFONT_

#include "Common/Iris2DUtil/IrisRefCounter.h"
#include "../../DirectX/IrisCommon.h"

namespace Iris2D
{
	class IrisColor;
	class IrisFont : public IrisRefCounter
	{
	private:
		std::wstring m_wstrFontName = GetDefaultName();
		unsigned int m_nSize = GetDefaultSize();;
		bool m_bBold = GetDefaultBold();
		bool m_bItalic = GetDefaultItalic();
		bool m_bShadow = GetDefaultShadow();
		IrisColor* m_pColor = nullptr;

	public:
		static bool Existed(const std::wstring& wstrFontName);

		static IrisFont* Create(const std::wstring& wstrFontName);
		static void Release(IrisFont*& pFont);

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

		void SetColor(IrisColor*& pColor);
		IrisColor* GetColor() const;

		static std::wstring GetDefaultName();
		static unsigned int GetDefaultSize();
		static bool GetDefaultBold();
		static bool GetDefaultItalic();
		static bool GetDefaultShadow();
		static IrisColor* GetDefaultColor();

	private:
		IrisFont();
		virtual ~IrisFont();
	};
}
#endif // !_H_IRISFONT_
