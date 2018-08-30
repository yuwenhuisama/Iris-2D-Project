#ifndef _H_DRAWTEXT_HELPER_
#define _H_DRAWTEXT_HELPER_

#include <map>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Iris2D {
	struct Character {
		GLuint m_nTextureID;   // ID handle of the glyph texture
		//glm::ivec2 Size;    // Size of glyph
		int m_nWidth;
		int m_nHeight;
		//glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		int m_nLeft;
		int m_nTop;
		GLuint m_nAdvance;    // Horizontal offset to advance to next glyph
	};

	class DrawTexHelper {
	private:
		GLuint m_nVAO = 0;
		GLuint m_nVBO = 0;

		std::map<wchar_t, Character> Characters;

	public:
		void Draw(const std::wstring& wstrText, GLfloat fX, GLfloat fY, GLfloat fW, GLfloat fH);
		void LoadChar(FT_Face ftFace, const std::wstring& wstrText);
		unsigned int GetTextSize(const std::wstring & wstrText);

		DrawTexHelper() = default;
		~DrawTexHelper();

	};
}
#endif //_H_DRAWTEXT_HELPER_