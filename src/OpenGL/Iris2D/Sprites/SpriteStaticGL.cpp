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
#include "OpenGL/OpenGLUtil/SpriteRenderQueueGL.h"

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
				GetProxied<ViewportGL*>(pSprite->m_pViewport)->RemoveSprite(static_cast<SpriteBaseGL*>(pSprite));
			}
			RefferRelease(pSprite);
		}
	}

	void SpriteStaticGL::ForceRelease(SpriteStaticGL* pSprite) {
		auto pProxy = dynamic_cast<SpriteStatic*>(pSprite->GetProxy());
		SpriteStatic::ForceRelease(pProxy);
		delete pSprite;
	}

	void SpriteStaticGL::SetOX(float fOX) {
		m_dcDirtyChecker.Assign(m_siaBuffer.m_v2OrgPosition.x, fOX, m_hOrgPos);
	}

	float SpriteStaticGL::GetOX() const {
		return m_siaBuffer.m_v2OrgPosition.x;
	}

	void SpriteStaticGL::SetOY(float fOY) {
		m_dcDirtyChecker.Assign(m_siaBuffer.m_v2OrgPosition.y, fOY, m_hOrgPos);
	}

	float SpriteStaticGL::GetOY() const {
		return m_siaBuffer.m_v2OrgPosition.y;
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

	bool SpriteStaticGL::CheckMergeableWith(const SpriteStaticGL* pSpriteTarget) {
		return (
			(m_pBitmap == pSpriteTarget->m_pBitmap || GetProxied<BitmapGL*>(m_pBitmap)->GetTexture() == GetProxied<BitmapGL*>(pSpriteTarget->GetBitmap())->GetTexture())
			&& (!pSpriteTarget->m_pEffect && !m_pEffect)
		);
	}

	ResultCode SpriteStaticGL::Render() {
		if (NeedDiscard()) {
			return IRR_Success;
		}

		auto pQueue = SpriteRenderQueueGL::Instance();

		pQueue->Push({ TargetType::SpriteStatic, this });
		
		return IRR_Success;
	}

	TextureGL* SpriteStaticGL::RenderEffect() {
		if (m_pEffect) {
			TextureGL* pEffectTexture = nullptr;
			auto pEffect = GetProxied<Effect::EffectBaseGL*>(m_pEffect);
			const auto pTexture = GetProxied<BitmapGL*>(m_pBitmap)->GetTexture();
			pEffectTexture = pEffect->Render(pTexture);

			return pEffectTexture;
		}
		return nullptr;
	}

	SpriteInstanceAttributeGL SpriteStaticGL::GetInstanceAttribute() {
		m_dcDirtyChecker.DoIfDirty(m_hTranslate, [&]() -> void {
			m_siaBuffer.m_v4TranslateAndZoom.x = m_v3Position.x;
			m_siaBuffer.m_v4TranslateAndZoom.y = m_v3Position.y;
		});

		m_dcDirtyChecker.DoIfDirty(m_hRotate, [&]() -> void {
			m_siaBuffer.m_mtRotation = glm::rotate(glm::mat4{ 1.0f }, m_fAngle * glm::pi<float>() / 180.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hZoom, [&]() -> void {
			m_siaBuffer.m_v4TranslateAndZoom.z = m_v2Zoom.x;
			m_siaBuffer.m_v4TranslateAndZoom.w = m_v2Zoom.y;
		});

		m_dcDirtyChecker.DoIfDirty(m_hOpacity, [&]() -> void {
			m_siaBuffer.m_f32Opacity = m_fOpacity;
		});

		m_dcDirtyChecker.DoIfDirty(m_hMirror, [&]() -> void {
			m_siaBuffer.m_i32Mirror = m_bMirror ? 1 : 0;
		});

		if (m_pSrcRect && GetProxied<RectGL*>(m_pSrcRect)->Modified()) {
			const auto fLeft = m_pSrcRect->GetLeft() / m_pBitmap->GetWidth();
			const auto fTop = m_pSrcRect->GetTop() / m_pBitmap->GetHeight();
			const auto fRight = m_pSrcRect->GetRight() / m_pBitmap->GetWidth();
			const auto fBottom = m_pSrcRect->GetBottom() / m_pBitmap->GetHeight();

			m_siaBuffer.m_v4Rect = {
				Clip(fLeft, 0.0f, 1.0f),
				Clip(fTop, 0.0f, 1.0f),
				Clip(fRight, 0.0f, 1.0f),
				Clip(fBottom, 0.0f, 1.0f),
			};

			GetProxied<RectGL*>(m_pSrcRect)->ModifyDone();
		}
		else if (!m_pSrcRect) {
			m_siaBuffer.m_v4Rect = { 0.0f, 0.0f, 1.0f, 1.0f };
		}

		if (m_pTone && GetProxied<ToneGL*>(m_pTone)->Modified()) {
			m_siaBuffer.m_v4Tone = {
				m_pTone->GetRed(),
				m_pTone->GetGreen(),
				m_pTone->GetBlue(),
				m_pTone->GetAlpha(),
			};

			GetProxied<ToneGL*>(m_pTone)->ModifyDone();
		}
		else if (!m_pTone) {
			m_siaBuffer.m_v4Tone = { 0, 0, 0, 0 };
		}

		return m_siaBuffer;
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
	}
}
