#ifndef _H_TEXTURE_GL_
#define _H_TEXTURE_GL_

#include <string>
#include "OpenGL/Common.h"

namespace Iris2D {
	class TextureGL {
	private:
		GLUnit m_nTextureID = 0;

	public:
		static TextureGL* Create(const std::wstring& wstrTexturePath);
		static TextureGL* Create(unsigned int nWidth, unsigned int nHeight);

		static bool Initialize();
		static void Release(TextureGL*& pTexture);

		void UseTexture();
		void UnuseTexture();

	private:
		bool LoadTexture(const std::wstring& wstrTexturePath);
		bool CreateBlankTexture(unsigned int nWidth, unsigned int nHeight);

	private:
		TextureGL() = default;
		~TextureGL();
	};
}

#endif // !_H_TEXTURE_GL_
