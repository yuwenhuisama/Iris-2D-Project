#include "OpenGL/Iris2D/Sprites/SpriteIndexedGL.h"
#include "Common/Iris2D/Bitmap.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"

#include "OpenGL/Iris2D/BitmapGL.h"
#include "OpenGL/Iris2D/RectGL.h"
#include "OpenGL/Iris2D/ColorGL.h"
#include "OpenGL/Iris2D/ViewportGL.h"

#include "Common/Iris2D/Effects/EffectBase.h"
#include "OpenGL/Iris2D/Effects/EffectBaseGL.h"
#include "OpenGL/OpenGLUtil/SpriteRenderQueueGL.h"
#include "Common/Util/Util.h"

namespace Iris2D {

	SpriteIndexedGL* SpriteIndexedGL::Create(const std::vector<Rect*>& vcAreas, Viewport* pViewport) {
		const auto pSprite = new SpriteIndexedGL();
		pSprite->m_pViewport = pViewport == nullptr ? ViewportGL::GetGlobalViewport() : pViewport;
		GetProxied<ViewportGL*>(pSprite->m_pViewport)->AddSprite(static_cast<SpriteBaseGL*>(pSprite));

		pSprite->m_vcAreas = vcAreas;

		return pSprite;
	}

	SpriteIndexedGL* SpriteIndexedGL::Create(unsigned nRow, unsigned nColumn, Viewport* pViewport) {

		const auto pSprite = new SpriteIndexedGL();
		pSprite->m_pViewport = pViewport == nullptr ? ViewportGL::GetGlobalViewport() : pViewport;
		GetProxied<ViewportGL*>(pSprite->m_pViewport)->AddSprite(static_cast<SpriteBaseGL*>(pSprite));

		if (pSprite->m_nRow != nRow || pSprite->m_nColumn != nColumn) {

		}
		pSprite->m_nRow = nRow;
		pSprite->m_nColumn = nColumn;

		return pSprite;
	}

	void SpriteIndexedGL::Release(SpriteIndexedGL*& pSprite) {
		if (pSprite) {
			if (pSprite->GetRefCount() == 1) {
				GetProxied<ViewportGL*>(pSprite->m_pViewport)->RemoveSprite(static_cast<SpriteBaseGL*>(pSprite));
			}
			RefferRelease(pSprite);
		}
	}

	void SpriteIndexedGL::SetOX(float fOX) {
		m_dcDirtyChecker.Assign(m_sivBuffer.m_svAttribute.m_v2OrgPosition.x, fOX, m_hOrgPos);
	}

	float SpriteIndexedGL::GetOX() const {
		return m_sivBuffer.m_svAttribute.m_v2OrgPosition.x;
	}

	void SpriteIndexedGL::SetOY(float fOY) {
		m_dcDirtyChecker.Assign(m_sivBuffer.m_svAttribute.m_v2OrgPosition.y, fOY, m_hOrgPos);
	}

	float SpriteIndexedGL::GetOY() const {
		return m_sivBuffer.m_svAttribute.m_v2OrgPosition.y;
	}

	void SpriteIndexedGL::SetSrcRect(Rect *& pSrcRect) {
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

	Rect * SpriteIndexedGL::GetSrcRect() const {
		return m_pSrcRect;
	}


	ResultCode SpriteIndexedGL::Update() {
		if (m_pEffect) {
			if (!m_pEffect->Update()) {
				return IRR_EffectUpdateFailed;
			}
		}

		return IRR_Success;
	}

	ResultCode SpriteIndexedGL::SetEffect(Effect::EffectBase* pEffect) {
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
		if (!pEffectGL->Initialize(m_pBitmap->GetWidth(), m_pBitmap->GetHeight())) {
			result = IRR_EffectInitializeFailed;
		}

		RefferAssign<Effect::EffectBaseGL*>(m_pEffect, pEffect);

		return result;
	}

	ResultCode SpriteIndexedGL::Render() {
		if (NeedDiscard()) {
			return IRR_Success;
		}

		auto pQueue = SpriteRenderQueueGL::Instance();

		pQueue->Push({ TargetType::SpriteIndexed, this });

		return IRR_Success;
	}

	bool SpriteIndexedGL::NeedDiscard() const {
		if (!m_pBitmap || !GetVisible() || m_fOpacity == 0.0f) {
			return true;
		}

		// TODO: Discard judge.

		return false;
	}

	void SpriteIndexedGL::SetIndex(unsigned nIndex) {
		m_nCurrentIndex = nIndex;
	}

	unsigned SpriteIndexedGL::GetIndex() const {
		return m_nCurrentIndex;
	}

	SpriteIndexedVertexGL SpriteIndexedGL::GetInstanceAttribute() {
		m_dcDirtyChecker.DoIfDirty(m_hTranslate, [&]() -> void {
			m_sivBuffer.m_svAttribute.m_v4TranslateAndZoom.x = m_v3Position.x;
			m_sivBuffer.m_svAttribute.m_v4TranslateAndZoom.y = m_v3Position.y;
		});

		m_dcDirtyChecker.DoIfDirty(m_hRotate, [&]() -> void {
			m_sivBuffer.m_svAttribute.m_mtRotation = glm::rotate(glm::mat4{ 1.0f }, m_fAngle * glm::pi<float>() / 180.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hZoom, [&]() -> void {
			m_sivBuffer.m_svAttribute.m_v4TranslateAndZoom.z = m_v2Zoom.x;
			m_sivBuffer.m_svAttribute.m_v4TranslateAndZoom.w = m_v2Zoom.y;
		});

		m_dcDirtyChecker.DoIfDirty(m_hOpacity, [&]() -> void {
			m_sivBuffer.m_svAttribute.m_f32Opacity = m_fOpacity;
		});

		m_dcDirtyChecker.DoIfDirty(m_hMirror, [&]() -> void {
			m_sivBuffer.m_svAttribute.m_i32Mirror = m_bMirror ? 1 : 0;
		});

		if (m_pSrcRect && GetProxied<RectGL*>(m_pSrcRect)->Modified()) {
			const auto fLeft = m_pSrcRect->GetLeft() / m_pBitmap->GetWidth();
			const auto fTop = m_pSrcRect->GetTop() / m_pBitmap->GetHeight();
			const auto fRight = m_pSrcRect->GetRight() / m_pBitmap->GetWidth();
			const auto fBottom = m_pSrcRect->GetBottom() / m_pBitmap->GetHeight();

			m_sivBuffer.m_svAttribute.m_v4Rect = {
				Clip(fLeft, 0.0f, 1.0f),
				Clip(fTop, 0.0f, 1.0f),
				Clip(fRight, 0.0f, 1.0f),
				Clip(fBottom, 0.0f, 1.0f),
			};

			GetProxied<RectGL*>(m_pSrcRect)->ModifyDone();
		}
		else if (!m_pSrcRect) {
			m_sivBuffer.m_svAttribute.m_v4Rect = { 0.0f, 0.0f, 1.0f, 1.0f };
		}

		if (m_pTone && GetProxied<ToneGL*>(m_pTone)->Modified()) {
			m_sivBuffer.m_svAttribute.m_v4Tone = {
				m_pTone->GetRed(),
				m_pTone->GetGreen(),
				m_pTone->GetBlue(),
				m_pTone->GetAlpha(),
			};

			GetProxied<ToneGL*>(m_pTone)->ModifyDone();
		}
		else if (!m_pTone) {
			m_sivBuffer.m_svAttribute.m_v4Tone = { 0, 0, 0, 0 };
		}

		return m_sivBuffer;
	}

	ResultCode SpriteIndexedGL::SetBitmap(Bitmap*& pBitmap) {
		if (m_vcAreas.empty() && (m_nColumn != 0 && m_nRow != 0)) {

			const auto fPerWidth = pBitmap->GetWidth() / static_cast<float>(m_nColumn);
			const auto fPerHeight = pBitmap->GetHeight() / static_cast<float>(m_nRow);

			for (size_t i = 0; i < m_nRow; ++i) {
				for (size_t j = 0; j < m_nColumn; ++j) {
					m_vcAreas.push_back(Rect::Create(i * fPerWidth, j * fPerHeight, fPerWidth, fPerHeight));
				}
			}
		} else {
			return IRR_WrongIndexedSprite;
		}

		return SpriteBaseGL::SetBitmap(pBitmap);
	}
}
