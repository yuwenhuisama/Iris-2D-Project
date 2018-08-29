#ifndef _H_DRAWTEXT_HELPER_
#define _H_DRAWTEXT_HELPER_

#include <map>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Iris2D {
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		//glm::ivec2 Size;    // Size of glyph
		int nWidth;
		int nHeight;
		//glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		int nLeft;
		int nTop;
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};
	class DrawTexHelper {
	private:
		GLuint VAO=0, VBO=0;

		std::map<wchar_t, Character> Characters;

	public:
		void Draw(const std::wstring text, GLfloat fx, GLfloat fy, GLfloat fw, GLfloat fh);
		void LoadChar(FT_Face face, const std::wstring &text);
		unsigned int GetTextSize(const std::wstring & wstrText);
		char * ws2c(const wchar_t * pwText);

		DrawTexHelper();
		~DrawTexHelper();

	};
}
#endif //_H_DRAWTEXT_HELPER_