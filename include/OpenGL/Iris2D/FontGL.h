#ifndef _H_FONT_GL_
#define _H_FONT_GL_

#include "Common/Util/RefCounter.h"
#include "OpenGL/Common.h"
#include "Common/Iris2D/IFont.h"
#include "Common/Iris2D/Proxied.h"
#include "OpenGL/Iris2D/ColorGL.h"
#include "Common/Iris2D/Color.h"
//#include "OpenGL/OpenGLUtil/DrawTextHelper.h"


#include "OpenGL/OpenGLUtil/TextureGL.h"
#include <GL/glew.h>
#include <map>
#include "Common/Iris2D/Rect.h"
#include "OpenGL/OpenGLUtil/Character.h"
#include "Common/Iris2D/IBitmap.h"
#include <ft2build.h>
#include FT_FREETYPE_H

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
	



		//GLuint m_nVAO = 0;
		//GLuint m_nVBO = 0;
		FT_Library m_FTLibrary=NULL;
		FT_Face m_FTFace=NULL;

		unsigned int m_nTextureMapWidth = 0;
		unsigned int m_nTextureMapHeight = 0;
		unsigned int m_nOriginY = 0;
		std::map<wchar_t, Character> Characters;

		TextureGL * m_pTemporaryTexture=nullptr;





	public:
		FT_Library GetFTLibrary();
		FT_Face GetFTFace();
		void LoadChar(const std::wstring& wstrText);
		unsigned int GetTextWidth(const std::wstring & wstrText);
	//	void DrawString(const std::wstring& wstrText, GLfloat fX, GLfloat fY, GLfloat fW, GLfloat fH);
		void DrawString(const std::wstring&, GLfloat fWidth, GLfloat fHeight, AlignType eAlign);
		TextureGL *GetTemporaryTexture();
		




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
