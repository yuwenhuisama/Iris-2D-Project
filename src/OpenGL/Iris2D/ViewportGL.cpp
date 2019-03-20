#include "OpenGL/Iris2D/ViewportGL.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"

#include "Common/Iris2D/Viewport.h"

#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/ViewportVertexGL.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"

#include "Common/Util/ProxyConvert.h"

#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "OpenGL/Iris2D/ColorGL.h"
#include "OpenGL/Iris2D/RectGL.h"
#include "Common/Util/Util.h"
#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"
#include "OpenGL/OpenGLUtil/SpriteRenderQueueGL.h"


namespace Iris2D {
	Viewport* ViewportGL::sm_pGlobalViewport = nullptr;

	ViewportGL * ViewportGL::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight) {
		auto pViewport = new ViewportGL();

		if (!pViewport->CreateViewportVertexBufferAndFrameBuffer(nWidth, nHeight)) {
			delete pViewport;
			return nullptr;
		}

		GraphicsGL::Instance()->AddViewport(pViewport);

		pViewport->m_fX = fX;
		pViewport->m_fY = fY;

		pViewport->m_vvbBuffer.m_mt4Translate = glm::translate(glm::mat4{ 1.0 }, glm::vec3{ fX, fY, pViewport->m_fZ });

		return pViewport;
	}

	ViewportGL * ViewportGL::Create(const Rect * pRect) {
		return ViewportGL::Create(pRect->GetX(), pRect->GetY(), static_cast<unsigned int>(pRect->GetWidth()), static_cast<unsigned int>(pRect->GetHeight()));
	}

	void ViewportGL::Release(ViewportGL *& pViewport) {
		if (!pViewport) {
			return;
		}

		GraphicsGL::Instance()->RemoveViewport(pViewport);

		if (pViewport != GetProxied<ViewportGL*>(sm_pGlobalViewport)) {
			if (pViewport->GetRefCount() == 1) {
				GraphicsGL::Instance()->RemoveViewport(pViewport);
				GetProxied<ViewportGL*>(sm_pGlobalViewport)->m_stSprites.insert(pViewport->m_stSprites.begin(), pViewport->m_stSprites.end());
			}
		}

		RefferRelease(pViewport);
	}

	void ViewportGL::ForceRelease(ViewportGL *& pViewport) {
		if (!pViewport) {
			return;
		}

		for (auto& pSprite : pViewport->m_stSprites) {
			SpriteStaticGL::ForceRelease(dynamic_cast<SpriteStaticGL*>(pSprite.second));
		}

		auto pProxy = pViewport->GetProxy();
		Viewport::Release(pProxy);

		delete pViewport;
		pViewport = nullptr;
	}

	bool ViewportGL::InitializeGlobalViewport(float fX, float fY, unsigned int nWindowWidth, unsigned int nWindowHeight) {
		sm_pGlobalViewport = Viewport::Create(fX, fY, nWindowWidth, nWindowHeight);
		return sm_pGlobalViewport != nullptr;
	}

	bool ViewportGL::ReleaseGlobalViewport() {
		Viewport::Release(sm_pGlobalViewport);
		return true;
	}

	Viewport * ViewportGL::GetGlobalViewport() {
		return sm_pGlobalViewport;
	}

	void ViewportGL::SetOX(float fOX) {
		m_vvbBuffer.m_v2OrgPosition.x = fOX;
	}

	float ViewportGL::GetOX() const {
		return m_vvbBuffer.m_v2OrgPosition.x;
	}

	void ViewportGL::SetOY(float fOY) {
		m_vvbBuffer.m_v2OrgPosition.y = fOY;
	}

	float ViewportGL::GetOY() const {
		return m_vvbBuffer.m_v2OrgPosition.y;
	}

	void ViewportGL::SetSrcRect(Rect *& pSrcRect) {
		if (pSrcRect == m_pSrcRect) {
			return;
		}

		Rect::Release(m_pSrcRect);

		if (!pSrcRect) {
			m_pSrcRect = nullptr;
			return;
		}

		RefferAssign<RectGL*>(m_pSrcRect, pSrcRect);
	}

	Rect * ViewportGL::GetSrcRect() const {
		return m_pSrcRect;
	}

	void ViewportGL::SetTone(Tone *& pTone) {
		if (pTone == m_pTone) {
			return;
		}

		Tone::Release(m_pTone);

		if (!pTone) {
			m_pTone = nullptr;
			return;
		}

		RefferAssign<ToneGL*>(m_pTone, pTone);
	}

	Tone * ViewportGL::GetTone() const {
		return m_pTone;
	}

	void ViewportGL::SetZ(float fZ) {
		m_dcChecker.Assign(m_fZ, fZ, m_hPosHandler);
	}

	float ViewportGL::GetZ() {
		return m_fZ;
	}

	unsigned int ViewportGL::GetWidth() const {
		return m_pTexture->GetWidth();
	}

	unsigned int ViewportGL::GetHeight() const {
		return m_pTexture->GetHeight();
	}

	ResultCode ViewportGL::RenderSprites() {
		m_pTexture->UseTextureAsFrameBuffer();

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

		auto eResult = IRR_Success;

		for (auto& pSprite : m_stSprites) {
			// TODO: optimize for batch render.
			eResult = pSprite.second->Render();
			if(IR_FAILED(eResult)) {
				break;
			}
		}

		auto pQueue = SpriteRenderQueueGL::Instance();
		pQueue->Push({ TargetType::End, nullptr });

		m_pTexture->RestoreFrameBuffer();

		//m_pTexture->SaveToFile(L"temp.png");

		return eResult;
	}

	ResultCode ViewportGL::Render() {
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GraphicsGL::Instance()->GetWidth()), static_cast<float>(GraphicsGL::Instance()->GetHeight()), 0.0f, 0.0f, 9999.0f);
		glViewport(0, 0, GraphicsGL::Instance()->GetWidth(), GraphicsGL::Instance()->GetHeight());

		auto pShader = ViewportShaderGL::Instance();

		pShader->SetProjectionMatrix(c_mt4Projection);

		if (m_pSrcRect && GetProxied<RectGL*>(m_pSrcRect)->Modified()) {
			const auto fLeft = m_pSrcRect->GetLeft() / m_pTexture->GetWidth();
			const auto fTop = m_pSrcRect->GetTop() / m_pTexture->GetHeight();
			const auto fRight = m_pSrcRect->GetRight() / m_pTexture->GetWidth();
			const auto fBottom = m_pSrcRect->GetBottom() / m_pTexture->GetHeight();

			m_vvbBuffer.m_v4Rect = {
				Clip(fLeft, 0.0f, 1.0f),
				Clip(fTop, 0.0f, 1.0f),
				Clip(fRight, 0.0f, 1.0f),
				Clip(fBottom, 0.0f, 1.0f),
			};
			GetProxied<RectGL*>(m_pSrcRect)->ModifyDone();
		} else if (!m_pSrcRect) {
			m_vvbBuffer.m_v4Rect = { 0.0f, 0.0f, 1.0f, 1.0f };
		}

		if (m_pTone && GetProxied<ToneGL*>(m_pTone)->Modified()) {
			m_vvbBuffer.m_v4Tone = {
				m_pTone->GetRed(),
				m_pTone->GetGreen(),
				m_pTone->GetBlue(),
				m_pTone->GetAlpha(),
			};

			GetProxied<ToneGL*>(m_pTone)->ModifyDone();
		}
		else if (!m_pTone) {
			m_vvbBuffer.m_v4Tone = { 0, 0, 0, 0 };
		}

		m_dcChecker.DoIfDirty(m_hPosHandler, [&]() -> void {
			m_vvbBuffer.m_mt4Translate = glm::translate(glm::mat4{ 1.0 }, glm::vec3{ m_fX, m_fY, 0.0f });
		});

		pShader->SetModelMatrix(m_vvbBuffer.m_mt4Translate);
		pShader->SetOrgPosition(m_vvbBuffer.m_v2OrgPosition);
		pShader->SetRect(m_vvbBuffer.m_v4Rect);
		pShader->SetTone(m_vvbBuffer.m_v4Tone);

		m_pTexture->UseTexture();
		//m_pTexture->SaveToFile(L"temp/4212.png");

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#if !defined(NDEBUG) | defined(_DEBUG)
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		return IRR_Success;
	}

	void ViewportGL::AddSprite(SpriteBaseGL* pSprite) {
		m_stSprites.insert(std::pair<float, SpriteBaseGL*>(pSprite->GetZ(), pSprite));
	}

	void ViewportGL::RemoveSprite(SpriteBaseGL* pSprite) {
		auto iterRange = m_stSprites.equal_range(pSprite->GetZ());
		while (iterRange.first != iterRange.second) {
			if (iterRange.first->second == pSprite) {
				m_stSprites.erase(iterRange.first);
				break;
			}
			++iterRange.first;
		}
	}

	bool ViewportGL::CreateViewportVertexBufferAndFrameBuffer(unsigned int nWidth, unsigned int nHeight) {
		ViewportVertexGL arrBuffers[] = {
			{ {static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f}, {1.0f, 0.0f} },
			{ {static_cast<float>(nWidth),  0.0f,						 0.0f, 1.0f}, {1.0f, 1.0f} },
			{ {0.0f,					    0.0f,						 0.0f, 1.0f}, {0.0f, 1.0f} },
			{ {0.0f,					    static_cast<float>(nHeight), 0.0f, 1.0f}, {0.0f, 0.0f} },
		};

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(arrBuffers, sizeof(arrBuffers), m_nVAO, m_nVBO, m_nEBO, []()-> void {
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ViewportVertexGL), reinterpret_cast<void*>(offsetof(ViewportVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ViewportVertexGL), reinterpret_cast<void*>(offsetof(ViewportVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);
		})) {
			return false;
		}

		m_pTexture = TextureGL::CreateFrameBuffer(nWidth, nHeight);

		return m_pTexture != nullptr;
	}

	ViewportGL::ViewportGL() {
		m_hPosHandler = m_dcChecker.Register();
	}

	ViewportGL::~ViewportGL() {
		TextureGL::Release(m_pTexture);
		Rect::Release(m_pSrcRect);
		Tone::Release(m_pTone);

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
}
