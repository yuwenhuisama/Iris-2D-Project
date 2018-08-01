#include "OpenGL/Iris2D/ViewportGL.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"

#include "Common/Iris2D/Viewport.h"

#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/ViewportVertexGL.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/SpriteGL.h"

#include "Common/Util/ProxyConvert.h"

#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Iris2D {
	Viewport* ViewportGL::sm_pGlobalViewport = nullptr;

	ViewportGL * ViewportGL::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		auto pViewport = new ViewportGL();

		if (!pViewport->CreateViewportVertexBufferAndFrameBuffer(nWidth, nHeight)) {
			delete pViewport;
			return nullptr;
		}

		GraphicsGL::Instance()->AddViewport(pViewport);

		pViewport->m_fX = fX;
		pViewport->m_fY = fY;

		return pViewport;
	}

	ViewportGL * ViewportGL::Create(const Rect * pRect, IR_PARAM_RESULT_CT) {
		return ViewportGL::Create(pRect->GetX(), pRect->GetY(), static_cast<unsigned int>(pRect->GetWidth()), static_cast<unsigned int>(pRect->GetHeight()), IR_PARAM);
	}

	void ViewportGL::Release(ViewportGL *& pViewport) {
		if (!pViewport) {
			return;
		}

		GraphicsGL::Instance()->RemoveViewport(pViewport);

		if (pViewport != GetProxied<ViewportGL*>(sm_pGlobalViewport)) {
			GraphicsGL::Instance()->RemoveViewport(pViewport);
			GetProxied<ViewportGL*>(sm_pGlobalViewport)->m_stSprites.insert(pViewport->m_stSprites.begin(), pViewport->m_stSprites.end());
		}

		delete pViewport;
		pViewport = nullptr;
	}

	void ViewportGL::ForceRelease(ViewportGL *& pViewport) {
		if (!pViewport) {
			return;
		}

		for (auto& pSprite : pViewport->m_stSprites) {
			SpriteGL::ForceRelease(pSprite);
		}

		auto pProxy = pViewport->GetProxy();
		Viewport::Release(pProxy);

		delete pViewport;
		pViewport = nullptr;
	}

	bool ViewportGL::InitializeGlobalViewport(float fX, float fY, unsigned int nWindowWidth, unsigned int nWindowHeight) {
		sm_pGlobalViewport = Viewport::Create(fX, fY, nWindowWidth, nWindowHeight);
		return sm_pGlobalViewport == nullptr;
	}

	bool ViewportGL::ReleaseGlobalViewport() {
		return true;
	}

	Viewport * ViewportGL::GetGlobalViewport() {
		return sm_pGlobalViewport;
	}

	void ViewportGL::SetOX(float fOX) {
	}

	float ViewportGL::GetOX() const {
		return 0.0f;
	}

	void ViewportGL::SetOY(float fOY) {
	}

	float ViewportGL::GetOY() const {
		return 0.0f;
	}

	void ViewportGL::SetSrcRect(Rect *& pSrcRect) {
	}

	Rect * ViewportGL::GetSrcRect() const {
		return nullptr;
	}

	void ViewportGL::SetTone(Tone *& pTone) {
	}

	Tone * ViewportGL::GetTone() const {
		return nullptr;
	}

	void ViewportGL::RenderSprites() {
		for (auto& pSprite : m_stSprites) {
			m_pTexture->UseTextureAsFrameBuffer();

			glClearColor(0.f, 0.f, 0.f, 0.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			pSprite->Render();

			m_pTexture->RestoreFrameBuffer();
		}
	}

	void ViewportGL::Render() {
		static auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GraphicsGL::Instance()->GetWidth()), static_cast<float>(GraphicsGL::Instance()->GetHeight()), 0.0f, -1.0f, 1.0f);

		auto pShader = ViewportShaderGL::Instance();

		//TODO: Optimize for dirty check
		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);

		glm::mat4 mtTrans(1.0f);
		mtTrans = glm::translate(mtTrans, {m_fX, m_fY, m_fZ});

		pShader->SetModelMatrix(mtTrans);

		// m_pTexture->SaveToFile(L"temp/output.png");
		m_pTexture->UseTexture();

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void ViewportGL::AddSprite(SpriteGL *& pSprite) {
		m_stSprites.insert(pSprite);
	}

	void ViewportGL::RemoveSprite(SpriteGL *& pSprite) {
		m_stSprites.erase(pSprite);
	}

	bool ViewportGL::CreateViewportVertexBufferAndFrameBuffer(unsigned int nWidth, unsigned int nHeight) {
		ViewportVertexGL arrBuffers[] = {
			{ {static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f}, {1.0f, 1.0f} },
			{ {static_cast<float>(nWidth),  0.0f,						 0.0f, 1.0f}, {1.0f, 0.0f} },
			{ {0.0f,					    0.0f,						 0.0f, 1.0f}, {0.0f, 0.0f} },
			{ {0.0f,					    static_cast<float>(nHeight), 0.0f, 1.0f}, {0.0f, 1.0f} },
		};

		static unsigned int arrIndiecs[] = {
			0, 1, 3,
			1, 2, 3,
		};

		GLuint VAO, VBO, EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(arrBuffers), arrBuffers, GL_STATIC_DRAW);

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndiecs), arrIndiecs, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ViewportVertexGL), reinterpret_cast<void*>(offsetof(ViewportVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ViewportVertexGL), reinterpret_cast<void*>(offsetof(ViewportVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);

		glBindVertexArray(0);

		m_nVAO = VAO;
		m_nVBO = VBO;
		m_nEBO = EBO;

		m_pTexture = TextureGL::CreateFrameBuffer(nWidth, nHeight);

		return m_pTexture != nullptr;
	}

	ViewportGL::~ViewportGL() {
		TextureGL::Release(m_pTexture);

		if (m_nVAO) {
			glDeleteVertexArrays(1, &m_nVAO);
		}
	}
}
