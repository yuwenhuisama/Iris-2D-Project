#ifndef _H_FONT_GL_
#define _H_FONT_GL_

#include "Common/Util/RefCounter.h"
#include "OpenGL/Common.h"
#include "Common/Iris2D/IFont.h"
#include "Common/Iris2D/Proxied.h"
#include "OpenGL/Iris2D/ColorGL.h"
#include "Common/Iris2D/Color.h"
#include "OpenGL/OpenGLUtil/DrawTextHelper.h"

//#include <ft2build.h>
//#include FT_FREETYPE_H

namespace Iris2D
{
	class Color;
	class Font;
	class FontGL : public Proxied<Font>, public IFont, public RefCounter
	{
	private:
		std::wstring m_wstrFontName = GetDefaultName();
		unsigned int m_nSize = GetDefaultSize();;
		bool m_bBold = GetDefaultBold();
		bool m_bItalic = GetDefaultItalic();
		bool m_bShadow = GetDefaultShadow();
		Color* m_pColor = GetDefaultColor();

		GLuint VAO=0, VBO=0;
		FT_Library m_FTLibrary;
		FT_Face m_FTFace;

	public:
		FT_Library GetFTLibrary();
		 FT_Face GetFTFace();

		static bool Existed(const std::wstring& wstrFontName);

		static FontGL* Create(const std::wstring& wstrFontName);
		static void Release(FontGL*& pFont);

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
		FontGL() ;
		virtual ~FontGL();
	};
}
#endif // !_H_FONT_GL_
