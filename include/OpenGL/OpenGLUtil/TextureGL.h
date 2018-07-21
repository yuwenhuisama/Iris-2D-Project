#ifndef _H_TEXTURE_GL_
#define _H_TEXTURE_GL_

namespace Iris2D {
	class TextureGL {
	public:
		static TextureGL* Create(const std::wstring& wstrTexturePath);
		static TextureGL* Create(unsigned int nWidth, unsigned int nHeight);
	};
}

#endif // !_H_TEXTURE_GL_
