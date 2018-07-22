#include "OpenGL/OpenGLUtil/TextureGL.h"
#include <codecvt>

#define STB_IMAGE_IMPLEMENTATION
#include "OpenGL/OpenGLUtil/stb_image.h"

namespace Iris2D {
	TextureGL * TextureGL::Create(const std::wstring & wstrTexturePath) {
		auto pObject = new TextureGL();

		if (!pObject->LoadTexture(wstrTexturePath)) {
			return pObject;
		}

		delete pObject;
		return nullptr;
	}

	TextureGL * TextureGL::Create(unsigned int nWidth, unsigned int nHeight) {
		auto pObject = new TextureGL();

		if (!pObject->CreateBlankTexture(nWidth, nHeight)) {
			return pObject;
		}

		delete pObject;
		return nullptr;
	}

	TextureGL * TextureGL::CreateFrameBuffer(unsigned int nWidth, unsigned int nHeight) {
		auto pObject = new TextureGL();

		if (!pObject->AsFrameBuffer(nWidth, nHeight)) {
			return pObject;
		}

		delete pObject;
		return nullptr;
	}

	bool TextureGL::Initialize() {
		// Wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// MIPMAP
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		return true;
	}

	void TextureGL::Release(TextureGL *& pTexture) {
		if (pTexture) {
			delete pTexture;
			pTexture = nullptr;
		}
	}

	void TextureGL::UseTexture() {
		glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	}

	void TextureGL::UnuseTexture() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int TextureGL::GetWidth() const {
		return m_nWidth;
	}

	unsigned int TextureGL::GetHeight() const {
		return m_nHeight;
	}

	bool TextureGL::LoadTexture(const std::wstring & wstrTexturePath) {
		// load texture data
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		auto strConverted = converter.to_bytes(wstrTexturePath);

		int nWidth, nHeight, nChannels;
		auto pData = stbi_load(strConverted.c_str(), &nWidth, &nHeight, &nChannels, 0);

		GLuint nTextureID = 0;
		glGenTextures(1, &nTextureID);

		glBindTexture(GL_TEXTURE_2D, nTextureID);

		if (nChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
		}
		else if (nChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(pData);

		glBindTexture(GL_TEXTURE_2D, 0);

		m_nWidth = nWidth;
		m_nHeight = nHeight;

		return true;
	}

	bool TextureGL::CreateBlankTexture(unsigned int nWidth, unsigned int nHeight) {

		GLuint nTextureID = 0;
		glGenTextures(1, &nTextureID);

		glBindTexture(GL_TEXTURE_2D, nTextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		return true;
	}

	bool TextureGL::AsFrameBuffer(unsigned int nWidth, unsigned int nHeight) {

		// generate frame buffer
		GLuint FBO = 0;
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		// generate texture
		GLuint nTexture;
		glGenTextures(1, &nTexture);
		glBindTexture(GL_TEXTURE_2D, nTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nTexture, 0);

		m_nTextureID = nTexture;

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return false;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// restore
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return true;
	}

	TextureGL::~TextureGL() {
		if (m_nTextureID) {
			glDeleteTextures(1, &m_nTextureID);
		}

		if (m_nFBO) {
			glDeleteFramebuffers(1, &m_nFBO);
		}
	}
}
