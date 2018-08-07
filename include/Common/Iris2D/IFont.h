#ifndef _H_IFON_
#define _H_IFON_

#include <string>

namespace Iris2D {

	class Color;
	class IFont {
	public:
		virtual ~IFont() = default;
		virtual void SetName(const std::wstring& wstrFontName) = 0;
		virtual const std::wstring& GetName() const = 0;

		virtual void SetSize(unsigned int nSize) = 0;
		virtual unsigned int GetSize() const = 0;

		virtual void SetBold(bool bBold) = 0;
		virtual bool GetBold() const = 0;

		virtual void SetItalic(bool bItalic) = 0;
		virtual bool GetItalic() const = 0;

		virtual void SetShadow(bool bShadow) = 0;
		virtual bool GetShadow() const = 0;

		virtual void SetColor(Color*& pColor) = 0;
		virtual Color* GetColor() const = 0;
	};
}

#endif // !_H_IFON_
