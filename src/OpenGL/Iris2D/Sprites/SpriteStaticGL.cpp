#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"
#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Viewport.h"
#include "Common/Iris2D/Sprites/SpriteStatic.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Common/Iris2D/Bitmap.h"
#include "Common/Util/ProxyConvert.h"

#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"

#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

#include "OpenGL/Iris2D/ViewportGL.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"

#include "Common/Util/Util.h"

#include "OpenGL/Iris2D/ColorGL.h"
#include "OpenGL/Iris2D/RectGL.h"

#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "OpenGL/Iris2D/Effects/EffectBaseGL.h"
#include "Common/Iris2D/Effects/EffectBase.h"

namespace Iris2D {
	SpriteStaticGL * SpriteStaticGL::Create(Viewport * pViewport) {
		const auto pSprite = new SpriteStaticGL();

		pSprite->m_pViewport = pViewport == nullptr ? ViewportGL::GetGlobalViewport() : pViewport;

		GetProxied<ViewportGL*>(pSprite->m_pViewport)->AddSprite(static_cast<SpriteBaseGL*>(pSprite));

		return pSprite;
	}

	void SpriteStaticGL::Release(SpriteStaticGL *& pSprite) {
		if (pSprite) {
			if (pSprite->GetRefCount() == 1) {
				GetProxied<ViewportGL*>(pSprite->m_pViewport)->RemoveSprite(reinterpret_cast<SpriteBaseGL*&>(pSprite));
			}
			RefferRelease(pSprite);
		}
	}

	void SpriteStaticGL::ForceRelease(SpriteStaticGL* pSprite) {
		auto pProxy = dynamic_cast<SpriteStatic*>(pSprite->GetProxy());
		SpriteStatic::ForceRelease(pProxy);
		delete pSprite;
	}

	ResultCode SpriteStaticGL::SetBitmap(Bitmap *& pBitmap) {
		if (pBitmap == m_pBitmap) {
			return IRR_Success;
		}

		Bitmap::Release(m_pBitmap);

		if (!pBitmap) {
			m_pBitmap = nullptr;
			return IRR_Success;
		}

		RefferAssign<BitmapGL*>(m_pBitmap, pBitmap);

		if(!CreateVertexBuffer()) {
			return IRR_OpenGLVertexBufferCreateFailed;
		}

		return IRR_Success;
	}

	Bitmap * SpriteStaticGL::GetBitmap() const {
		return m_pBitmap;
	}

	void SpriteStaticGL::SetOX(float fOX) {
		m_dcDirtyChecker.Assign(m_svbfBuffer.m_v2OrgPosition.x, fOX, m_hOrgPos);
	}

	float SpriteStaticGL::GetOX() const {
		return m_svbfBuffer.m_v2OrgPosition.x;
	}

	void SpriteStaticGL::SetOY(float fOY) {
		m_dcDirtyChecker.Assign(m_svbfBuffer.m_v2OrgPosition.y, fOY, m_hOrgPos);
	}

	float SpriteStaticGL::GetOY() const {
		return m_svbfBuffer.m_v2OrgPosition.y;
	}

	void SpriteStaticGL::SetSrcRect(Rect *& pSrcRect) {
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

	Rect * SpriteStaticGL::GetSrcRect() const {
		return m_pSrcRect;
	}

	ResultCode SpriteStaticGL::Update() {
		if(m_pEffect) {
			if(!m_pEffect->Update()) {
				return IRR_EffectUpdateFailed;
			}
		}

		return IRR_Success;
	}

	ResultCode SpriteStaticGL::SetEffect(Effect::EffectBase* pEffect) {
		if (pEffect == m_pEffect) {
			return IRR_Success;
		}

		if (m_pEffect) {
			m_pEffect->AutoRelease();
		}

		if (!pEffect) {
			m_pEffect = nullptr;
			return IRR_Success;
		}

		auto result = IRR_Success;
		const auto pEffectGL = GetProxied<Effect::EffectBaseGL*>(pEffect);
		if(!pEffectGL->Initialize(m_pBitmap->GetWidth(), m_pBitmap->GetHeight())) {
			result = IRR_EffectInitializeFailed;
		}

		RefferAssign<Effect::EffectBaseGL*>(m_pEffect, pEffect);

		return result;
	}

	bool SpriteStaticGL::CreateVertexBuffer() {
		const auto pBitmap = GetProxied<BitmapGL*>(m_pBitmap);

		const auto nWidth = pBitmap->GetWidth();
		const auto nHeight = pBitmap->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f },{ 1.0f, 1.0f } },
			{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f },{ 1.0f, 0.0f } },
			{ { 0.0f,					     0.0f,						   0.0f, 1.0f },{ 0.0f, 0.0f } },
			{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f },{ 0.0f, 1.0f } },
		};

		return OpenGLHelper::Instance()->CreateVertextBuffer(arrBuffers, sizeof(arrBuffers), m_nVAO, m_nVBO, m_nEBO, [&]() -> void {
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);
		});
	}

	ResultCode SpriteStaticGL::Render() {

		if (NeedDiscard()) {
			return IRR_Success;
		}

		TextureGL* pEffectTexture = nullptr;
		auto pShader = SpriteShaderGL::Instance();

		if (m_pEffect) {
			auto pEffect = GetProxied<Effect::EffectBaseGL*>(m_pEffect);
			const auto pTexture = GetProxied<BitmapGL*>(m_pBitmap)->GetTexture();
			pEffectTexture = pEffect->Render(pTexture);

			pShader->Use();
		}

		m_dcDirtyChecker.DoIfDirty(m_hTranslate, [&]() -> void {
			m_svbfBuffer.m_mt4Translate = glm::translate(glm::mat4{ 1.0f, }, { m_v3Position.x, m_v3Position.y, 0.0f});
		});
		
		m_dcDirtyChecker.DoIfDirty(m_hRotate, [&]() -> void {
			m_svbfBuffer.m_mtRotation = glm::rotate(glm::mat4{ 1.0f }, m_fAngle * glm::pi<float>() / 180.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hZoom, [&]() -> void {
			m_svbfBuffer.m_mtZoom = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ m_v2Zoom.x, m_v2Zoom.y, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hOpacity, [&]() -> void {
			m_svbfBuffer.m_f32Opacity = m_fOpacity;
		});

		m_dcDirtyChecker.DoIfDirty(m_hMirror, [&]() -> void {
			m_svbfBuffer.m_i32Mirror = m_bMirror ? 1 : 0;
		});

		if (m_pSrcRect && GetProxied<RectGL*>(m_pSrcRect)->Modified()) {
			const auto fLeft = m_pSrcRect->GetLeft() / m_pBitmap->GetWidth();
			const auto fTop = m_pSrcRect->GetTop() / m_pBitmap->GetHeight();
			const auto fRight = m_pSrcRect->GetRight() / m_pBitmap->GetWidth();
			const auto fBottom = m_pSrcRect->GetBottom() / m_pBitmap->GetHeight();

			m_svbfBuffer.m_v4Rect = {
				clip(fLeft, 0.0f, 1.0f),
				clip(fTop, 0.0f, 1.0f),
				clip(fRight, 0.0f, 1.0f),
				clip(fBottom, 0.0f, 1.0f),
			};

			GetProxied<RectGL*>(m_pSrcRect)->ModifyDone();
		} else if (!m_pSrcRect){
			m_svbfBuffer.m_v4Rect = { 0.0f, 0.0f, 1.0f, 1.0f };
		}

		if (m_pTone && GetProxied<ToneGL*>(m_pTone)->Modified()) {
			m_svbfBuffer.m_v4Tone = {
				m_pTone->GetRed(),
				m_pTone->GetGreen(),
				m_pTone->GetBlue(),
				m_pTone->GetAlpha(),
			};

			GetProxied<ToneGL*>(m_pTone)->ModifyDone();
		} else if (!m_pTone) {
			m_svbfBuffer.m_v4Tone = { 0, 0, 0, 0 };
		}

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(m_pViewport->GetWidth()), static_cast<float>(m_pViewport->GetHeight()), 0.0f, 0.0f, 9999.0f);

		glViewport(0, 0, m_pViewport->GetWidth(), m_pViewport->GetHeight());

		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetTranslationMatrix(m_svbfBuffer.m_mt4Translate);
		pShader->SetRotationMatrix(m_svbfBuffer.m_mtRotation);
		pShader->SetZoomMatrix(m_svbfBuffer.m_mtZoom);
		pShader->SetOpacity(m_svbfBuffer.m_f32Opacity);
		pShader->SetMirror(m_svbfBuffer.m_i32Mirror);
		pShader->SetOrgPosition(m_svbfBuffer.m_v2OrgPosition);
		pShader->SetRect(m_svbfBuffer.m_v4Rect);
		pShader->SetTone(m_svbfBuffer.m_v4Tone);

		if (!m_pEffect) {
			GetProxied<BitmapGL*>(m_pBitmap)->GetTexture()->UseTexture();
		} else {
			pEffectTexture->UseTexture();
		}

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		return IRR_Success;
	}

	bool SpriteStaticGL::NeedDiscard() const {
		if (!m_pBitmap || !GetVisible() || m_fOpacity == 0.0f) {
			return true;
		}

		Rect* pViewportArea = nullptr;
		Rect* pThisArea = nullptr;

		// TODO: optimize area rect generation.
		if (!m_pViewport->GetSrcRect()) {
			pViewportArea = Rect::Create(0, 0, m_pViewport->GetWidth(), m_pViewport->GetHeight());
		} else {
			RefferAssign<RectGL*>(pViewportArea, m_pViewport->GetSrcRect());
		}

		if (!m_pSrcRect) {
			pThisArea = Rect::Create(-GetOX(), -GetOY(), m_pBitmap->GetWidth() * GetZoomX(), m_pBitmap->GetHeight() * GetZoomY());
		} else {
			pThisArea = Rect::Create(-GetOX(), -GetOY(), m_pSrcRect->GetWidth() * GetZoomX(), m_pSrcRect->GetHeight() * GetZoomY());
		}

		const auto bResult = !pThisArea->CheckInsectionWith(pViewportArea);

		Rect::Release(pViewportArea);
		Rect::Release(pThisArea);

		return bResult;
	}

	SpriteStaticGL::~SpriteStaticGL() {
		Bitmap::Release(m_pBitmap);
		Rect::Release(m_pSrcRect);
		Tone::Release(m_pTone);
		if (m_pEffect) {
			m_pEffect->AutoRelease();
		}

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
