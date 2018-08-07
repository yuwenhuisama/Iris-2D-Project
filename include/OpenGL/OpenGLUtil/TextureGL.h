#ifndef _H_TEXTURE_GL_
#define _H_TEXTURE_GL_

#include <string>
#include "OpenGL/Common.h"

namespace Iris2D {
	class TextureGL {
	private:
		GLUnit m_nTextureID = 0;
		GLUnit m_nFBO = 0;
		GLUnit m_nRBO = 0;

		GLint m_nStoredFrameBuffer = 0;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;

	public:
		static TextureGL* Create(const std::wstring& wstrTexturePath);
		static TextureGL* Create(unsigned int nWidth, unsigned int nHeight);
		static TextureGL* CreateFrameBuffer(unsigned int nWidth, unsigned int nHeight);

		static bool Initialize();
		static void Release(TextureGL*& pTexture);

	public:
		void UseTexture() const;
		void UnuseTexture() const;

		void UseTextureAsFrameBuffer();
		void RestoreFrameBuffer() const;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		bool SaveToFile(const std::wstring& wstrFilePath) const;

	private:
		bool LoadTexture(const std::wstring& wstrTexturePath);
		bool CreateBlankTexture(unsigned int nWidth, unsigned int nHeight);
		bool AsFrameBuffer(unsigned int nWidth, unsigned int nHeight);

	private:
		TextureGL() = default;
		~TextureGL();
	};
}

#endif // !_H_TEXTURE_GL_
