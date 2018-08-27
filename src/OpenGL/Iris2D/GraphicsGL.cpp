#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/ViewportGL.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/OpenGLUtil/BackBufferVertexGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"
#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackShaderGL.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Common/Common.h"
#include "Common/Util/Util.h"
#include "OpenGL/Iris2D/Shaders/BackTransitionShaderGL.h"

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

		Render(IR_PARAM);
		glfwSwapBuffers(OpenGLHelper::Instance()->GetWindow());
		glfwPollEvents();

		m_bUpdateLockFlag = false;

#ifdef _DEBUG
		static unsigned int  nCount = 0;

		if (nCount < 60) {
			++nCount;
		}
		else {
			const auto pWindow = OpenGLHelper::Instance()->GetWindow();

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

		static double fTmp = 0.0;

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
			Render(IR_PARAM);

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
			const auto pWindow = OpenGLHelper::Instance()->GetWindow();

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
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
		}
		else {
			for (size_t i = 0; i < nDuration; i++) {
				UpdateNoLock(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
		}
	}

	void GraphicsGL::FadeOut(unsigned int nDuration, IR_PARAM_RESULT_CT) {
		// (r, g, b, a) -> (0, 0, 0, 0)
		m_bFading = true;
		m_nDuration = nDuration;
		for (size_t i = nDuration; i > 0; --i) {
			m_nCurrentDuration = i;
			if (m_bVsync) {
				Update(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
			else {
				UpdateNoLock(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
		}
		m_bFading = false;
	}

	void GraphicsGL::FadeIn(unsigned int nDuration, IR_PARAM_RESULT_CT) {
		// (0, 0, 0, 0) -> (r, g, b, a)
		m_bFading = true;
		m_nDuration = nDuration;
		for (size_t i = 0; i < nDuration; ++i) {
			m_nCurrentDuration = i;
			if (m_bVsync) {
				Update(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
			else {
				UpdateNoLock(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}
		}
		m_bFading = false;
	}

	void GraphicsGL::Freeze(IR_PARAM_RESULT_CT) {
		m_bFreezing = true;

		TextureGL::Release(m_pFreezedBackBuffer);

		// Freeze current back buffer preparing for transition
		m_pFreezedBackBuffer = TextureGL::CopyFrom(m_pBackBuffer);

		if (!m_pFreezedBackBuffer) {
			IR_PARAM_SET_RESULT(IR_RESULT_FAILED, L"Error when creating freezed back buffer.");
		}
	}

	void GraphicsGL::Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague, IR_PARAM_RESULT_CT) {
		if (!m_bFreezing) {
			return;
		}

		m_bFreezing = false;
		m_bTransition = true;

		TextureGL* pMaskBuffer = nullptr;

		if (!wstrFilename.empty()) {
			pMaskBuffer = TextureGL::Create(wstrFilename);
			if (!pMaskBuffer) {
				IR_PARAM_SET_RESULT(IR_RESULT_FAILED, L"Error when creating mask buffer.");
				return;
			}
		}

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight), 0.0f, 0.0f, 9999.0f);

		auto pShader = BackTransitionShaderGL::Instance();

		pShader->Use();

		m_pFreezedBackBuffer->UseTexture(0);
		if (pMaskBuffer) {
			pMaskBuffer->UseTexture(1);
			pShader->SetType(1);
		} else {
			pShader->SetType(0);
		}
		m_pBackBuffer->UseTexture(2);

		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetBrightness(m_fBrightness - 0.5f);

		pShader->SetInt("texturePreSampler", 0);
		pShader->SetInt("textureMaskSampler", 1);
		pShader->SetInt("texturePostSampler", 2);

		float fCompare = 1.0f;
		const float fStep = fCompare / nDuration;
		while (fCompare >= 0) {

			pShader->SetCompare(1 - fCompare);
			pShader->SetVague(nVague / 256.0f);

			Update(IR_PARAM);
			if(IR_FAILD(IR_PARAM)) {
				break;
			}
			fCompare -= fStep;
		}

		TextureGL::Release(m_pFreezedBackBuffer);
		TextureGL::Release(pMaskBuffer);

		m_bTransition = false;
	}

	void GraphicsGL::FrameReset() {
		m_nFrameCount = 0;
	}

	void GraphicsGL::ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		m_bManualResize = true;

		const auto pWindow = OpenGLHelper::Instance()->GetWindow();

		glfwSetWindowSize(pWindow, nWidth, nHeight);

		Release();

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		if (!CreateVertexBackBuffer()) {
			IR_PARAM_SET_RESULT(IR_RESULT_FAILED, L"Error when creating back buffer.");
		}

		m_bManualResize = false;
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

	float GraphicsGL::GetBrightness()  const {
		return m_fBrightness;
	}

	void GraphicsGL::SetBrightness(float fBrightness) {
		m_fBrightness = clip(fBrightness, 0.0f, 1.0f);
	}

	void GraphicsGL::SetFrameRate(float fFrameRate) {
		m_fFrameRate = fFrameRate;
		m_fMsPerUpdate = 1000.0f / fFrameRate;
	}

	float GraphicsGL::GetFrameRate() const {
		return m_fFrameRate;
	}

	void GraphicsGL::Release() {
		TextureGL::Release(m_pBackBuffer);

		if (m_nVAO) {
			glDeleteVertexArrays(1, &m_nVAO);
		}

		if (m_nVBO) {
			glDeleteBuffers(1, &m_nVBO);
		}

		if (m_nEBO) {
			glDeleteBuffers(1, &m_nEBO);
		}
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

	void GraphicsGL::Render(IR_PARAM_RESULT_CT) {
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(m_nWidth), static_cast<float>(m_nHeight), 0.0f, 0.0f, 9999.0f);

		if (m_bTransition) {
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

			glBindVertexArray(m_nVAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		else {
			SpriteShaderGL::Instance()->Use();
			for (auto& pViewport : m_stViewports) {
				pViewport.second->RenderSprites();
			}

			m_pBackBuffer->UseTextureAsFrameBuffer();

			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

			ViewportShaderGL::Instance()->Use();

			for (auto& pViewport : m_stViewports) {
				pViewport.second->Render(IR_PARAM);
				if (IR_FAILD(IR_PARAM)) {
					break;
				}
			}

			m_pBackBuffer->RestoreFrameBuffer();

			const auto pShader = BackShaderGL::Instance();

			pShader->Use();
			pShader->SetProjectionMatrix(c_mt4Projection);
			pShader->SetBrightness(m_fBrightness - 0.5f);

			if (m_bFading) {
				pShader->SetFadeInfo(glm::vec2{ m_nCurrentDuration, m_nDuration });
			}
			else {
				pShader->SetFadeInfo(glm::vec2{ 1.0f, 1.0f });
			}

			if (!m_bFreezing) {
				m_pBackBuffer->UseTexture();
			}
			else {
				m_pFreezedBackBuffer->UseTexture();
			}

			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

			glBindVertexArray(m_nVAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}

	}

	bool GraphicsGL::IsManualResize() const {
		return m_bManualResize;
	}

	void GraphicsGL::AutoResize(unsigned nWidth, unsigned nHeight) {
		Release();

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		CreateVertexBackBuffer();
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
