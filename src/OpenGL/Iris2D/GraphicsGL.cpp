#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/OpenGLHelper.h"
#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/ViewportGL.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/OpenGLUtil/BackBufferVertexGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"
#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackShaderGL.h"
#include "OpenGL/Iris2D/OpenGLHelper.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Common/Common.h"

namespace Iris2D {
	GraphicsGL* GraphicsGL::Instance() {
		static GraphicsGL graphics;
		return &graphics;
	}

	void GraphicsGL::Update(IR_PARAM_RESULT_CT) {

		if (!m_bVsync) {
			m_bVsync = true;
			glfwSwapInterval(1);
		}

		Render();
		glfwSwapBuffers(OpenGLHelper::Instance()->GetWindow());
		glfwPollEvents();

		m_bUpdateLockFlag = false;

#ifdef _DEBUG
		static unsigned int  nCount = 0;

		if (nCount < 60) {
			++nCount;
		}
		else {
			auto pWindow = OpenGLHelper::Instance()->GetWindow();

			boost::format format("Fps: %1%, Frame count: %2%");
			format % (1000.0f / m_fMsPerUpdate);
			format % m_nFrameCount;

			glfwSetWindowTitle(pWindow, format.str().c_str());
			nCount = 0;
		}

#endif // _DEBUG

		++m_nFrameCount;
	}

	void GraphicsGL::UpdateNoLock(IR_PARAM_RESULT_CT) {
		if (m_bVsync) {
			m_bVsync = false;
			glfwSwapInterval(0);
		}

		static float fTmp = 0.0f;

		while (!m_bUpdateLockFlag) {
#ifdef _WIN32
			fTmp = m_dCurrentTime;
			m_dCurrentTime = ::timeGetTime();
#else
			// TODO: time get on Unix
#endif // _WIN32
			if (m_dCurrentTime >= m_dLastTime) {
				m_fTimeDelta = (m_dCurrentTime - fTmp);
				m_dLastTime = m_dCurrentTime + m_fMsPerUpdate;
				m_bUpdateLockFlag = true;
			}
			Render();

			glfwSwapBuffers(OpenGLHelper::Instance()->GetWindow());
			glfwPollEvents();
		}
		m_bUpdateLockFlag = false;

#ifdef _DEBUG
		static unsigned int  nCount = 0;

		if (nCount < 60) {
			++nCount;
		}
		else {
			auto pWindow = OpenGLHelper::Instance()->GetWindow();

			boost::format format("Fps: %1%, Frame count: %2%");
			format % (1000.0f / m_fMsPerUpdate);
			format % m_nFrameCount;

			glfwSetWindowTitle(pWindow, format.str().c_str());
			nCount = 0;
		}

#endif // _DEBUG

		++m_nFrameCount;
	}

	void GraphicsGL::Wait(unsigned int nDuration, IR_PARAM_RESULT_CT) {
		if (m_bVsync) {
			for (size_t i = 0; i < nDuration; i++) {
				Update(IR_PARAM);
			}
		}
		else {
			for (size_t i = 0; i < nDuration; i++) {
				UpdateNoLock(IR_PARAM);
			}
		}
		++m_nFrameCount;
	}

	void GraphicsGL::FadeOut(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::FadeIn(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::Freeze(IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::FrameReset() {
		m_nFrameCount = 0;
	}

	void GraphicsGL::ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::SetWidth(unsigned int nWidth) {
		m_nWidth = nWidth;
	}

	unsigned int GraphicsGL::GetWidth() const {
		return m_nWidth;
	}

	void GraphicsGL::SetHeight(unsigned int nHeight) {
		m_nHeight = nHeight;
	}

	unsigned int GraphicsGL::GetHeight() const {
		return m_nHeight;
	}

	unsigned int GraphicsGL::GetFrameCount() const {
		return m_nFrameCount;
	}

	unsigned int GraphicsGL::GetBrightness()  const {
		return 0;
	}

	void GraphicsGL::SetBrightness(unsigned int nBrightness) {
	}

	void GraphicsGL::SetFrameRate(float fFrameRate) {
		m_fFrameRate = fFrameRate;
		m_fMsPerUpdate = 1000.0f / fFrameRate;
	}

	float GraphicsGL::GetFrameRate() const {
		return m_fFrameRate;
	}

	void GraphicsGL::Release() {
	}

	float GraphicsGL::GetMsPerUpdate() {
		return m_fTimeDelta;
	}

	void GraphicsGL::AddViewport(ViewportGL*& pViewport) {
		m_stViewports.insert(std::pair<float, ViewportGL*>(pViewport->GetZ(), pViewport));
	}

	void GraphicsGL::RemoveViewport(ViewportGL* & pViewport) {
		//m_stViewports.erase(pViewport);
		auto iterRange = m_stViewports.equal_range(pViewport->GetZ());
		while (iterRange.first != iterRange.second) {
			if (iterRange.first->second == pViewport) {
				m_stViewports.erase(iterRange.first);
				break;
			}
			++iterRange.first;
		}
	}

	bool GraphicsGL::Intialize() {
		if (!ViewportGL::InitializeGlobalViewport(0, 0, GetWidth(), GetHeight())) {
			return false;
		}

		SetFrameRate(60.0f);

		return CreateVertexBackBuffer();
	}

	void GraphicsGL::Render() {
		SpriteShaderGL::Instance()->Use();
		for (auto& pViewport : m_stViewports) {
			pViewport.second->RenderSprites();
		}

		m_pBackBuffer->UseTextureAsFrameBuffer();

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

		ViewportShaderGL::Instance()->Use();

		for (auto& pViewport : m_stViewports) {
			pViewport.second->Render();
			//m_pBackBuffer->SaveToFile(L"temp\\a.png");
		}

		m_pBackBuffer->RestoreFrameBuffer();

		static auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight), 0.0f, 0.0f, 9999.0f);

		const auto pShader = BackShaderGL::Instance();

		//m_pBackBuffer->SaveToFile(L"temp\\a.png");

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		m_pBackBuffer->UseTexture();

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	bool GraphicsGL::CreateVertexBackBuffer() {

		BackBufferVertexGL arrBuffers[] = {
			{ { static_cast<float>(m_nWidth),  static_cast<float>(m_nHeight),  0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { static_cast<float>(m_nWidth),  0.0f,						   0.0f, 1.0f }, { 1.0f, 1.0f } },
			{ { 0.0f,						   0.0f,						   0.0f, 1.0f }, { 0.0f, 1.0f } },
			{ { 0.0f,					       static_cast<float>(m_nHeight),  0.0f, 1.0f }, { 0.0f, 0.0f } },
		};

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrBuffers, sizeof(arrBuffers), m_nVAO, m_nVBO, m_nEBO, []() -> void {
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(BackBufferVertexGL), reinterpret_cast<void*>(offsetof(BackBufferVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BackBufferVertexGL), reinterpret_cast<void*>(offsetof(BackBufferVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);
		})) {
			return false;
		}

		m_pBackBuffer = TextureGL::CreateFrameBuffer(m_nWidth, m_nHeight);

		return m_pBackBuffer != nullptr;
	}
}
