#ifndef _H_CHARACTER_GL_
#define _H_CHARACTER_GL_
#include <GL/glew.h>
namespace Iris2D {
	struct Character {
		GLuint m_nTextureID;
		int m_nWidth;
		int m_nHeight;
		int m_nLeft;
		int m_nTop;
		GLuint m_nAdvance;
		int m_nTextureMapLocationX;
	};
}
#endif // _H_CHARACTER_GL_
