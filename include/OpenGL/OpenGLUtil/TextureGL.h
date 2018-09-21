#ifndef _H_TEXTURE_GL_
#define _H_TEXTURE_GL_

#include <string>
#include "OpenGL/Common.h"
#include <unordered_map>
#include <Common/Util/RefCounter.h>

namespace Iris2D {
	class TextureGL : RefCounter {
		REF_FRIEND_DECLARE

	private:
		GLuint m_nTextureID = 0;
		GLuint m_nFBO = 0;
		GLuint m_nRBO = 0;

		GLint m_nStoredFrameBuffer = 0;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;

	private:
		static std::unordered_map<std::wstring, TextureGL*> m_umpCache;
		static std::unordered_map<TextureGL*, std::wstring> m_umpCacheReverse;

	public:
		static TextureGL* Create(const std::wstring& wstrTexturePath);
		static TextureGL* Create(unsigned int nWidth, unsigned int nHeight);
		static TextureGL* CreateFrameBuffer(unsigned int nWidth, unsigned int nHeight);
		static TextureGL* CopyFrom(const TextureGL* pTexture);

		static bool Initialize();
		static void Release(TextureGL*& pTexture);

	public:
		void UseTexture(unsigned int nUnit = 0) const;
		void UnuseTexture(unsigned int nUnit = 0) const;

		void UseTextureAsFrameBuffer();
		void RestoreFrameBuffer() const;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		unsigned char* GetPixels(unsigned int nWidth, unsigned int nHeight) const;

		bool SaveToFile(const std::wstring& wstrFilePath) const;

		GLuint GetTextureID();

	private:
		bool LoadTexture(const std::wstring& wstrTexturePath);
		bool LoadTexture(unsigned char* pPixels, unsigned int nWidth, unsigned int nHeight);
		bool CreateBlankTexture(unsigned int nWidth, unsigned int nHeight);
		bool AsFrameBuffer(unsigned int nWidth, unsigned int nHeight);

	private:
		TextureGL() = default;
		~TextureGL();
	};
}

#endif // !_H_TEXTURE_GL_
