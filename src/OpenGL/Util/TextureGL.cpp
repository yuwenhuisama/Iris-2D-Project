#include "OpenGL/OpenGLUtil/TextureGL.h"
#include <codecvt>

#define STB_IMAGE_IMPLEMENTATION
#include "OpenGL/OpenGLUtil/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "OpenGL/OpenGLUtil/stb_image_write.h"

#include "OpenGL/Iris2D/GraphicsGL.h"

namespace Iris2D {
	TextureGL * TextureGL::Create(const std::wstring & wstrTexturePath) {
		auto pObject = new TextureGL();

		if (pObject->LoadTexture(wstrTexturePath)) {
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

		if (pObject->AsFrameBuffer(nWidth, nHeight)) {
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

		//stbi_set_flip_vertically_on_load(true);
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

	void TextureGL::UseTextureAsFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFBO);
	}

	void TextureGL::RestoreFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int TextureGL::GetWidth() const {
		return m_nWidth;
	}

	unsigned int TextureGL::GetHeight() const {
		return m_nHeight;
	}

	bool TextureGL::SaveToFile(const std::wstring& wstrFilePath) {

		GLint nRestore = 0;

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &nRestore);

		GLuint nFrameBuffer = 0;
		glGenFramebuffers(1, &nFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, nFrameBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTextureID, 0);

		GLenum eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (eStatus != GL_FRAMEBUFFER_COMPLETE) {
			printf("failed to make complete framebuffer object %x", eStatus);
			return false;
		}
		
		const auto nWidth = m_nWidth;
		const auto nHeight = m_nHeight;

		glViewport(0, 0, nWidth, nHeight);

		auto pPixels = new GLubyte[nWidth * nHeight * sizeof(GLubyte) * 4];

		glReadPixels(0, 0, nWidth, nHeight, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);

		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		auto strConverted = converter.to_bytes(wstrFilePath);

		stbi_write_png(strConverted.c_str(), nWidth, nHeight, STBI_rgb_alpha, pPixels, nWidth * 4);

		delete[] pPixels;

		glDeleteFramebuffers(1, &nFrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, nRestore);

		return true;
	}

	bool TextureGL::LoadTexture(const std::wstring & wstrTexturePath) {
		// load texture data
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		auto strConverted = converter.to_bytes(wstrTexturePath);

		int nWidth, nHeight, nChannels;
		auto pData = stbi_load(strConverted.c_str(), &nWidth, &nHeight, &nChannels, STBI_rgb_alpha);

		GLuint nTextureID = 0;
		glGenTextures(1, &nTextureID);

		glBindTexture(GL_TEXTURE_2D, nTextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(pData);

		glBindTexture(GL_TEXTURE_2D, 0);

		m_nWidth = nWidth;
		m_nHeight = nHeight;

		m_nTextureID = nTextureID;

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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nTexture, 0);

		m_nTextureID = nTexture;

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return false;

		unsigned int RBO = 0;
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, nWidth, nHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// restore
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_nFBO = FBO;
		m_nRBO = RBO;

		m_nWidth = nWidth;
		m_nHeight = nHeight;

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
