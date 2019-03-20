#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Bitmap.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"

#include "Common/Util/ProxyConvert.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/FontGL.h"

#include "OpenGL/Iris2D/Shaders/FillRectShaderGL.h"
#include "OpenGL/Iris2D/Shaders/CopyRectShaderGL.h"
#include "OpenGL/Iris2D/Shaders/ClearRectShaderGL.h"
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h"
#include "OpenGL/Iris2D/Shaders/HueChangeShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackGroundShaderGL.h"
#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Font.h"

#ifdef _WIN32
#undef DrawText
#endif

namespace Iris2D {
	BitmapGL * BitmapGL::Create(const std::wstring & wstrFileName) {
		const auto pTexture = TextureGL::Create(wstrFileName);

		if (!pTexture) {
			return nullptr;
		}

		const auto pBitmap = new BitmapGL();

		pBitmap->m_pTexture = pTexture;

		return pBitmap;
	}

	BitmapGL * BitmapGL::Create(unsigned int nWidth, unsigned int nHeight) {
		const auto pTexture = TextureGL::Create(nWidth, nHeight);

		if (!pTexture) {
			return nullptr;
		}

		const auto pBitmap = new BitmapGL();

		pBitmap->m_pTexture = pTexture;

		return pBitmap;
	}

	BitmapGL * BitmapGL::Create(Bitmap * pSrcBitmapGL) {
		if (!pSrcBitmapGL) {
			return nullptr;
		}
		const auto pBitmap = new BitmapGL();

		auto pShader = FillRectShaderGL::Instance();
		static GLfloat arrVertices[] = {
			static_cast<float>(pSrcBitmapGL->GetWidth()),	static_cast<float>(pSrcBitmapGL->GetHeight()),	1.0f, 1.0f,
			static_cast<float>(pSrcBitmapGL->GetWidth()),	0.0f,											1.0f, 0.0f,
			0.0f,											0.0f,											0.0f, 0.0f,
			0.0f,											static_cast<float>(pSrcBitmapGL->GetHeight()),  0.0f, 1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		})) {
			return nullptr;
		}
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(pSrcBitmapGL->GetWidth(), pSrcBitmapGL->GetHeight());
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pSrcBitmapGL->GetWidth()), 0.0f, static_cast<float>(pSrcBitmapGL->GetHeight()), -1.0f, 1.0f);
		const auto pFillRect = Rect::Create(0.0f, 0.0f, 0.0f, 0.0f);
		const auto pFillColor = Color::Create(00, 00, 00, 00);

		int nWindowWidth = 0;
		int nWindowHeight = 0;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, pSrcBitmapGL->GetWidth(), pSrcBitmapGL->GetHeight());

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glDisable(GL_DEPTH_TEST);

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation(pFillRect);
		pShader->SetFillColor(pFillColor);

		glBindVertexArray(nVAO);
		GetProxied<BitmapGL*>(pSrcBitmapGL)->GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);

		pBitmap->m_pTexture = pTextureFrameBuffer;

		return pBitmap;
	}

	BitmapGL * BitmapGL::CopyFrom(Bitmap * pSrcBitmapGL) {
		return Create(pSrcBitmapGL);
	}

	void BitmapGL::Release(BitmapGL *& pBitmap) {
		if (!pBitmap) {
			return;
		}

		RefferRelease(pBitmap);
	}

	unsigned int BitmapGL::GetWidth() const {
		return m_pTexture->GetWidth();
	}

	unsigned int BitmapGL::GetHeight() const {
		return m_pTexture->GetHeight();
	}

	ResultCode BitmapGL::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) {
		auto const pDestRect = Rect::Create(static_cast<float>(nDestX), static_cast<float>(nDestY), pSrcRect->GetWidth(), pSrcRect->GetHeight());
		return StretchBlt(pDestRect, pSrcBitmap, pSrcRect, fOpacity);
	}

	ResultCode BitmapGL::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity) {
		if (fOpacity < 0.0f) {
			fOpacity = 0.0f;
		}
		else if (fOpacity > 255.0f) {
			fOpacity = 255.0f;
		}

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), -1.0f, 1.0f);
		int nWindowWidth, nWindowHeight;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, static_cast<GLsizei>(GetWidth()), static_cast<GLsizei>(GetHeight()));

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShader = CopyRectShaderGL::Instance();


		//const GLuint VAO = pShader->BindBufferData(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
		static GLfloat arrVertices[] = {
			static_cast<float>(GetWidth()),	static_cast<float>(GetHeight()),	1.0f, 1.0f,
			static_cast<float>(GetWidth()),	0.0f,								1.0f, 0.0f,
			0.0f,							0.0f,								0.0f, 0.0f,
			0.0f,							static_cast<float>(GetHeight()),	0.0f, 1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}
		
		pShader->Use();
		pShader->SetDesOthoMat(c_mt4Projection);
		pShader->SetDesRect(pDestRect);
		pShader->SetSrcTexCoordRect(pSrcRect, static_cast<float>(GetProxied<BitmapGL*>(pSrcBitmap)->GetWidth()),static_cast<float>(GetProxied<BitmapGL*>(pSrcBitmap)->GetHeight()));
		pShader->SetOpacity(fOpacity);

		GetTexture()->UseTexture(0);
		pShader->SetInt("destTexture", 0);
		GetProxied<BitmapGL*>(pSrcBitmap)->GetTexture()->UseTexture(1);
		pShader->SetInt("srcTexture", 1);

		glBindVertexArray(nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, static_cast<GLsizei>(nWindowWidth), static_cast<GLsizei>(nWindowHeight));//�ʿڻ�ԭ

		TextureGL::Release(m_pTexture);

		m_pTexture = pTextureFrameBuffer;
		
		return IRR_Success;
	} 

	ResultCode BitmapGL::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor) {
		const auto  pRect = Rect::Create(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nWidth), static_cast<float>(nHeight));
		return FillRect(pRect, pColor);
	}

	ResultCode BitmapGL::FillRect(const Rect * pRect, const Color * pColor) {
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), -1.0f, 1.0f);

		int nWindowWidth = 0;
		int nWindowHeight = 0;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());

		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShader = FillRectShaderGL::Instance();

		static GLfloat arrVertices[] = {
			static_cast<float>(GetWidth()),	static_cast<float>(GetHeight()),	1.0f, 1.0f,
			static_cast<float>(GetWidth()),	0.0f,								1.0f, 0.0f,
			0.0f,							0.0f,								0.0f, 0.0f,
			0.0f,							static_cast<float>(GetHeight()),	0.0f, 1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation(pRect);
		pShader->SetFillColor(pColor);

		glBindVertexArray(nVAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);

		TextureGL::Release(m_pTexture);

		m_pTexture = pTextureFrameBuffer;

		return IRR_Success;
	}

	ResultCode BitmapGL::Clear() {
		const auto pRect = Rect::Create(0.f, 0.f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
		return ClearRect(pRect);
	}

	ResultCode BitmapGL::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
		const auto  pRect = Rect::Create(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nWidth), static_cast<float>(nHeight));
		return ClearRect(pRect);
	}

	ResultCode BitmapGL::ClearRect(const Rect * pRect) {
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), 0.0f, 9999.0f);

		int nWindowWidth = 0;
		int nWindowHeight = 0;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShader = ClearRectShaderGL::Instance();

		static GLfloat arrVertices[] = {
			static_cast<float>(GetWidth()),	static_cast<float>(GetHeight()),	1.0f, 1.0f,
			static_cast<float>(GetWidth()),	0.0f,								1.0f, 0.0f,
			0.0f,							0.0f,								0.0f, 0.0f,
			0.0f,							static_cast<float>(GetHeight()),  0.0f, 1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation(pRect);

		glBindVertexArray(nVAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);

		TextureGL::Release(m_pTexture);
		m_pTexture = pTextureFrameBuffer;

		return IRR_Success;
	}

	Color * BitmapGL::GetPixel(unsigned int nX, unsigned int nY) const {
		GLint nRestore = 0;

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &nRestore);

		m_pTexture->UseTextureAsFrameBuffer();
		
		GLuint nFrameBuffer = 0;
		glGenFramebuffers(1, &nFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, nFrameBuffer);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GetTexture()->GetTextureID(), 0);
		
		const auto eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (eStatus != GL_FRAMEBUFFER_COMPLETE) {
			PrintFormatDebugMessageW(L"Failed to make complete framebuffer object %x", eStatus);
			return nullptr;
		}

		int nWindowWidth, nWindowHeight;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		glViewport(0, 0, GetWidth(), GetHeight());

		const auto pPixels = new GLubyte[sizeof(GLubyte) * 4];

		glReadPixels(nX, nY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);

		const auto pColor = Color::Create(pPixels[0], pPixels[1], pPixels[2], pPixels[3]);

		delete[] pPixels;

		m_pTexture->RestoreFrameBuffer();
		glDeleteFramebuffers(1, &nFrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, nRestore);

		glViewport(0, 0, nWindowWidth, nWindowHeight);

		return pColor;
	}

	ResultCode BitmapGL::GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) {
		pColor = GetPixel(nX, nY);

		if (!pColor) {
			return IRR_TextureReadFailed;
		}

		return IRR_Success;
	}

	ResultCode BitmapGL::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor) {
		return FillRect(nX, nY, nX + 1, nY + 1, pColor);
	}

	ResultCode BitmapGL::SaveToFile(const std::wstring & wstrFilePath) {
		return GetTexture()->SaveToFile(wstrFilePath) ? IRR_Success : IRR_TextureOutputFailed;
	}

	ResultCode BitmapGL::HueChange(float fHue) {
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		int nWindowWidth, nWindowHeight;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShader = HueChangeShaderGL::Instance();

		float arrVertices[] = {
			1.0f,	 1.0f,		1.0f,1.0f,
			1.0f,	-1.0f,   	1.0f,0.0f,
			-1.0f ,	-1.0f,		0.0f,0.0f,
			-1.0f ,	 1.0f,    	0.0f,1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;
		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}

		pShader->Use();
		pShader->SetHue(static_cast<int>(fHue));

		glBindVertexArray(nVAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);
		TextureGL::Release(m_pTexture);
		m_pTexture = pTextureFrameBuffer;
		return IRR_Success;
	}

	void BitmapGL::SetFont(Font *& pFont) {
		m_pFont = pFont;
	}

	Font * BitmapGL::GetFont() const {
		return m_pFont;
	}

	unsigned int BitmapGL::TextSize(const Font * pFont, const std::wstring & wstrText) {
		//GetProxied<FontGL*>(pFont)->LoadChar(wstrText);
		return GetProxied<FontGL*>(pFont)->GetTextWidth(wstrText);
	}

	ResultCode BitmapGL::TextSize(const Font* pFont, const std::wstring& wstrText, unsigned int& nSize) {
		nSize = TextSize(pFont,wstrText);
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType eAlign) {
		GetProxied<FontGL*>(m_pFont)->SetUseCache(true);
		auto pfontTexture=GetProxied<FontGL*>(m_pFont)->DrawString(wstrText, nWidth, nHeight, eAlign);

		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		int nWindowWidth, nWindowHeight;
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);
		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//background
		auto pShaderBackground = BackGroundShaderGL::Instance();
		static GLfloat arrVertices[] = {
			//position	    //texcoord
			1.0f,  1.0f,   1.0f, 1.0f,
			1.0f, -1.0f,   1.0f, 0.0f,
			-1.0f, -1.0f,   0.0f, 0.0f,
			-1.0f,  1.0f,   0.0f, 1.0f
		};

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices, sizeof(arrVertices), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}
		pShaderBackground->Use();
		glBindVertexArray(nVAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		auto pShaderFont2 = BackGroundShaderGL::Instance();
		const GLfloat & fH = static_cast<GLfloat>(GetHeight());
		const GLfloat & fW = static_cast<GLfloat>(GetWidth());
		const GLfloat & ftop = nY / fH * 2 - 1;
		const GLfloat & fleft = nX / fW * 2 - 1;
		const GLfloat & fright = (static_cast<GLfloat>(nX + pfontTexture->GetWidth())) / fW * 2 - 1;
		const GLfloat & fbottom = (static_cast<GLfloat>(nY + pfontTexture->GetHeight())) / fH * 2 - 1;
		GLfloat arrVertices2[] = {
			fright,  fbottom,    1.0f, 1.0f,
			fright,  ftop,   1.0f, 0.0f,
			fleft,   ftop,   0.0f, 0.0f,
			fleft,   fbottom,   0.0f, 1.0f
		};
		GLuint nVAO2 = 0;
		GLuint nVBO2 = 0;
		GLuint nEBO2 = 0;
		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrVertices2, sizeof(arrVertices2), nVAO2, nVBO2, nEBO2, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		})) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}
		pShaderFont2->Use();
		glBindVertexArray(nVAO2);
		pfontTexture->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#ifdef _DEBUG
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);
		pTextureFrameBuffer->RestoreFrameBuffer();
		m_pTexture = pTextureFrameBuffer;
		TextureGL::Release(pfontTexture);
		//m_pTexture->SaveToFile(L"d:\\hehe2.png");
		if (nVAO) {
			glDeleteVertexArrays(1, &nVAO);
		}
		if (nVBO) {
			glDeleteBuffers(1, &nVBO);
		}
		if (nEBO) {
			glDeleteBuffers(1, &nEBO);
		}
		if (nVAO2) {
			glDeleteVertexArrays(1, &nVAO2);
		}
		if (nVBO2) {
			glDeleteBuffers(1, &nVBO2);
		}
		if (nEBO2) {
			glDeleteBuffers(1, &nEBO2);
		}
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType eAlign) {
		return DrawText(
			static_cast<unsigned int>(pRect->GetLeft()),
			static_cast<unsigned int>(pRect->GetTop()),
			static_cast<unsigned int>(pRect->GetWidth()),
			static_cast<unsigned int>(pRect->GetHeight()),
			wstrText,
			eAlign
		);
	}

	ResultCode BitmapGL::Dispose() {
		TextureGL::Release(m_pTexture);
		return IRR_Success;
	}

	TextureGL * BitmapGL::GetTexture() const {
		return m_pTexture;
	}
}
