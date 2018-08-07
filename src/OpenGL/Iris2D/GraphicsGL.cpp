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

		SpriteShaderGL::Instance()->Use();
		for (auto& pViewport : m_stViewports) {
			pViewport->RenderSprites();
		}

		m_pBackBuffer->UseTextureAsFrameBuffer();

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ViewportShaderGL::Instance()->Use();

		for (auto& pViewport : m_stViewports) {
			pViewport->Render();
		}

		m_pBackBuffer->RestoreFrameBuffer();

		static auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight), 0.0f, -1.0f, 1.0f);

		const auto pShader = BackShaderGL::Instance();

		// m_pBackBuffer->SaveToFile(L"temp\\a.png");

		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		m_pBackBuffer->UseTexture();

		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glfwSwapBuffers(OpenGLHelper::Instance()->GetWindow());
		glfwPollEvents();
	}

	void GraphicsGL::UpdateNoLock(IR_PARAM_RESULT_CT) {
		if (m_bVsync) {
			m_bVsync = false;
			glfwSwapInterval(0);
		}
	}

	void GraphicsGL::Wait(unsigned int nDuration, IR_PARAM_RESULT_CT) {
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

	unsigned int GraphicsGL::GetFrameCount() {
		return 0;
	}

	unsigned int GraphicsGL::GetBrightness() {
		return 0;
	}

	void GraphicsGL::SetBrightness(unsigned int nBrightness) {
	}

	void GraphicsGL::SetFrameRate(float fFrameRate) {
	}

	float GraphicsGL::GetFrameRate() const {
		return 0.0f;
	}

	void GraphicsGL::Release() {
	}

	float GraphicsGL::GetMsPerUpdate() {
		return 0.0f;
	}

	void GraphicsGL::AddViewport(ViewportGL*& pViewport) {
		m_stViewports.insert(pViewport);
	}

	void GraphicsGL::RemoveViewport(ViewportGL* & pViewport) {
		m_stViewports.erase(pViewport);
	}

	bool GraphicsGL::Intialize() {
		if (!ViewportGL::InitializeGlobalViewport(0, 0, GetWidth(), GetHeight())) {
			return false;
		}

		return CreateVertexBackBuffer();
	}

	bool GraphicsGL::CreateVertexBackBuffer() {

		BackBufferVertexGL arrBuffers[] = {
			{ { static_cast<float>(m_nWidth),  static_cast<float>(m_nHeight),  0.0f, 1.0f }, { 1.0f, 1.0f } },
			{ { static_cast<float>(m_nWidth),  0.0f,						   0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { 0.0f,						   0.0f,						   0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 0.0f,					       static_cast<float>(m_nHeight),  0.0f, 1.0f }, { 0.0f, 1.0f } },
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
