#ifndef _H_CHARACTER_GL_
#define _H_CHARACTER_GL_
#include <GL/glew.h>
#include<OpenGL/OpenGLUtil/TextureGL.h>
namespace Iris2D {
	struct Character {
	public:
		GLuint m_nTextureID;
		int m_nWidth;
		int m_nHeight;
		int m_nLeft;
		int m_nTop;
		GLuint m_nAdvance;
	};
	struct CharacterWithcache {
	public:
		TextureGL * m_pTexture;
		int times;
	};
}
#endif // _H_CHARACTER_GL_
