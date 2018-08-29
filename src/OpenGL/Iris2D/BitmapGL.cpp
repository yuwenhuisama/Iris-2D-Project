#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Bitmap.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"

#include "Common/Util/ProxyConvert.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"

#include <glm/gtc/matrix_transform.hpp>
#include "OpenGL/OpenGLUtil/BackBufferVertexGL.h"

#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/FontGL.h"
#include "OpenGL/OpenGLUtil/DrawTextHelper.h"

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
		if (!pSrcBitmapGL)
			return nullptr;
		auto pBitmap = new BitmapGL();
		auto pShader = FillRectShaderGL::Instance();
		pShader->Initialize();
		GLuint VAO = pShader->BindBufferData(static_cast<float>(pSrcBitmapGL->GetWidth()), static_cast<float>(pSrcBitmapGL->GetHeight()));

		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(pSrcBitmapGL->GetWidth(), pSrcBitmapGL->GetHeight());
		auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pSrcBitmapGL->GetWidth()), 0.0f, static_cast<float>(pSrcBitmapGL->GetHeight()), -1.0f, 1.0f);
		const auto pFillRect = Rect::Create(0.0f, 0.0f, 0.0f, 0.0f);
		const auto pFillColor = Color::Create(00, 00, 00, 00);

		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, pSrcBitmapGL->GetWidth(), pSrcBitmapGL->GetHeight());//适口转换

		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation((*pFillRect));
		pShader->SetFillColor((*pFillColor));

		glBindVertexArray(VAO);
		GetProxied<BitmapGL*>(pSrcBitmapGL)->GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		//pTextureFrameBuffer->SaveToFile(L"d:\\frambuffer.png");
		glViewport(0, 0, static_cast<GLsizei>(nWindowWidth), static_cast<float>(nWindowHeight));//适口还原
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

		auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), -1.0f, 1.0f);
		int nWindowWidth, nWindowHeight;//保存原视口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, static_cast<GLsizei>(GetWidth()), static_cast<GLsizei>(GetHeight()));//适口转换

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		auto pShader = CopyRectShaderGL::Instance();
		pShader->Initialize();
		GLuint VAO = pShader->BindBufferData(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
		pShader->Use();
		pShader->SetDesOthoMat(c_mt4Projection);
		pShader->SetDesRect((*pDestRect));
		pShader->SetSrcTexCoordRect(*pSrcRect, GetProxied<BitmapGL*>(pSrcBitmap)->GetTexture());
		pShader->SetOpacity(fOpacity);

		//glActiveTexture(GL_TEXTURE0);
		GetTexture()->UseTexture(0);
		//GetTexture()->SaveToFile(L"d:\\frambuffera.png");;
		pShader->SetInt("destTexture", 0);

		//glActiveTexture(GL_TEXTURE1);
		GetProxied<BitmapGL*>(pSrcBitmap)->GetTexture()->UseTexture(1);
		//GetProxied<BitmapGL*>(pSrcBitmapGL)->SaveToFile(L"d:\\frambufferb.png");;
		pShader->SetInt("srcTexture", 1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		//pTextureFrameBuffer->SaveToFile(L"d:\\frambuffer3.png");
		glViewport(0, 0, static_cast<GLsizei>(nWindowWidth), static_cast<GLsizei>(nWindowHeight));//适口还原
		m_pTexture = pTextureFrameBuffer;

		
		
		return IRR_Success;
	}

	ResultCode BitmapGL::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor) {
		const auto  pRect = Rect::Create(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nWidth), static_cast<float>(nHeight));

		return FillRect(pRect, pColor);
	}

	ResultCode BitmapGL::FillRect(const Rect * pRect, const Color * pColor) {
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), -1.0f, 1.0f);

		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());//视口转换

		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		auto pShader = FillRectShaderGL::Instance();
		pShader->Initialize();
		GLuint VAO = pShader->BindBufferData(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation(*pRect);
		pShader->SetFillColor(*pColor);

		glBindVertexArray(VAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);//视口还原
		m_pTexture = pTextureFrameBuffer;
		//pTextureFrameBuffer->SaveToFile(L"d:\\frambuffer.png");
	//	return true;
		
		
		return IRR_Success;
	}

	ResultCode BitmapGL::Clear() {
		const auto  pRect = Rect::Create(0.f, 0.f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
		return ClearRect(pRect);
	}

	ResultCode BitmapGL::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight) {
		const auto  pRect = Rect::Create(static_cast<float>(nX), static_cast<float>(nY), static_cast<float>(nWidth), static_cast<float>(nHeight));
		return ClearRect(pRect);
	}

	ResultCode BitmapGL::ClearRect(const Rect * pRect) {
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()), -1.0f, 1.0f);

		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());//视口转换

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glDisable(GL_DEPTH_TEST);

		//开启混合
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		auto pShader = ClearRectShaderGL::Instance();
		pShader->Initialize();
		GLuint VAO = pShader->BindBufferData(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetRectLocation(*pRect);

		glBindVertexArray(VAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);//视口还原

		TextureGL::Release(m_pTexture);
		m_pTexture = pTextureFrameBuffer;

		//pTextureFrameBuffer->SaveToFile(L"d:\\frambuffer4.png");
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
		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		//	glViewport(0, 0, nWidth, nHeight);
		glViewport(0, 0, GetWidth(), GetHeight());//视口转换

		const auto pPixels = new GLubyte[sizeof(GLubyte) * 4];

		glReadPixels(nX, nY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);

		auto pColor = Color::Create(pPixels[0], pPixels[1], pPixels[2], pPixels[3]);

		delete[] pPixels;

		m_pTexture->RestoreFrameBuffer();
		glDeleteFramebuffers(1, &nFrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, nRestore);

		glViewport(0, 0, nWindowWidth, nWindowHeight);//视口还原

		return pColor;

		//return nullptr;
	}

	ResultCode BitmapGL::GetPixel(unsigned int nX, unsigned int nY, Color*& pColor) {
		pColor = GetPixel(nX, nY);

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
		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());//视口转换

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		auto pShader = HueChangeShaderGL::Instance();
		pShader->Initialize();
		GLuint VAO = pShader->BindBufferData();
		pShader->Use();
		pShader->setHue(static_cast<int>(fHue));


		glBindVertexArray(VAO);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);//视口还原
		m_pTexture = pTextureFrameBuffer;
		//pTextureFrameBuffer->SaveToFile(L"d:\\frambuffer.png");
		return IRR_Success;
	}

	void BitmapGL::SetFont(Font *& pFont) {
	}

	Font * BitmapGL::GetFont() const {
		return nullptr;
	}

	unsigned int BitmapGL::TextSize(const Font * pFont, const std::wstring & wstrText) {
		DrawTexHelper *drawtext = new DrawTexHelper();
		drawtext->LoadChar(GetProxied<FontGL*>(pFont)->GetFTFace(), wstrText);
		return drawtext->GetTextSize(wstrText);
	}

	ResultCode BitmapGL::TextSize(const Font* pFont, const std::wstring& wstrText, unsigned int& nSize) {
		nSize = TextSize(pFont,wstrText);
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign) {
		
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(GetWidth(), GetHeight());
		auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), 0.0f, static_cast<float>(GetHeight()));

		int nWindowWidth, nWindowHeight;//保存原适口大小
		glfwGetFramebufferSize(OpenGLHelper::Instance()->GetWindow(), &nWindowWidth, &nWindowHeight);

		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, GetWidth(), GetHeight());//视口转换

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		//background
		auto pShaderBackground = BackGroundShaderGL::Instance();
		pShaderBackground->Initialize();
		GLuint VAO1 = pShaderBackground->BindBufferData();

		pShaderBackground->Use();
		glBindVertexArray(VAO1);
		GetTexture()->UseTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		
		auto pShaderFont = FontShaderGL::Instance();
		pShaderFont->Initialize();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);

		pShaderFont->SetFontColor(*GetProxied<FontGL*>(GetFont())->GetColor());
		pShaderFont->Use();

		DrawTexHelper *drawtext = new DrawTexHelper();
		drawtext->LoadChar(GetProxied<FontGL*>(GetFont())->GetFTFace(), wstrText);
		drawtext->Draw(wstrText, static_cast<GLfloat>(nX), static_cast<GLfloat>(nY), static_cast<GLfloat>(nWidth), static_cast<GLfloat>(nHeight));
		

		pTextureFrameBuffer->RestoreFrameBuffer();
		glViewport(0, 0, nWindowWidth, nWindowHeight);//视口还原
		m_pTexture = pTextureFrameBuffer;

		
		return IRR_Success;
	}

	ResultCode BitmapGL::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign) {
		return DrawText(
			static_cast<unsigned int>(pRect->GetLeft()),
			static_cast<unsigned int>(pRect->GetTop()),
			static_cast<unsigned int>(pRect->GetRight()),
			static_cast<unsigned int>(pRect->GetBottom()),
			wstrText,
			nAlign
		);
		return IRR_Success;
	}

	ResultCode BitmapGL::Dispose() {
		TextureGL::Release(m_pTexture);
		return IRR_Success;
	}

	TextureGL * BitmapGL::GetTexture() const {
		return m_pTexture;
	}
}
