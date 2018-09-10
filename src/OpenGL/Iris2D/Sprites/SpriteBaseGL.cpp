#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"
#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"
#include "OpenGL/Iris2D/FontGL.h"
#include "Common/Util/Util.h"

namespace Iris2D {


	SpriteBaseGL::SpriteBaseGL() {
		m_hTranslate = m_dcDirtyChecker.Register();
		m_hZoom = m_dcDirtyChecker.Register();
		m_hOrgPos = m_dcDirtyChecker.Register();
		m_hRotate = m_dcDirtyChecker.Register();
		m_hMirror = m_dcDirtyChecker.Register();
		m_hOpacity = m_dcDirtyChecker.Register();
	}

	void SpriteBaseGL::SetX(float fX) {
		m_dcDirtyChecker.Assign(m_v3Position.x, fX, m_hTranslate);
	}

	float SpriteBaseGL::GetX() const {
		return m_v3Position.x;
	}

	void SpriteBaseGL::SetY(float fY) {
		m_dcDirtyChecker.Assign(m_v3Position.y, fY, m_hTranslate);
	}

	float SpriteBaseGL::GetY() const {
		return m_v3Position.y;
	}

	void SpriteBaseGL::SetZ(float fZ) {
		m_dcDirtyChecker.Assign(m_v3Position.z, fZ, m_hTranslate);
	}

	float SpriteBaseGL::GetZ() const {
		return m_v3Position.z;
	}

	void SpriteBaseGL::SetAngle(float fAngle) {
		m_dcDirtyChecker.Assign(m_fAngle, fAngle, m_hRotate);
	}

	float SpriteBaseGL::GetAngle() const {
		return m_fAngle;
	}

	void SpriteBaseGL::SetZoomX(float fZoomX) {
		m_dcDirtyChecker.Assign(m_v2Zoom.x, fZoomX, m_hZoom);
	}

	float SpriteBaseGL::GetZoomX() const {
		return m_v2Zoom.x;
	}

	void SpriteBaseGL::SetZoomY(float fZoomY) {
		m_dcDirtyChecker.Assign(m_v2Zoom.y, fZoomY, m_hZoom);
	}

	float SpriteBaseGL::GetZoomY() const {
		return m_v2Zoom.y;
	}


	void SpriteBaseGL::SetMirror(bool bMirror) {
		m_dcDirtyChecker.Assign(m_bMirror, bMirror, m_hMirror);
	}

	bool SpriteBaseGL::GetMirror() const {
		return m_bMirror;
	}

	void SpriteBaseGL::SetVisible(bool bVisible) {
		m_bVisible = bVisible;
	}

	bool SpriteBaseGL::GetVisible() const {
		return m_bVisible;
	}

	void SpriteBaseGL::SetOpacity(float fOpacity) {
		fOpacity = clip(fOpacity, 0.0f, 1.0f);
		m_dcDirtyChecker.Assign(m_fOpacity, fOpacity, m_hOpacity);
	}

	float SpriteBaseGL::GetOpacity() const {
		return m_fOpacity;
	}

	void SpriteBaseGL::SetTone(Tone *& pTone) {
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

	Tone * SpriteBaseGL::GetTone() const {
		return m_pTone;
	}

}
