#include "OpenGL/Iris2D/ViewportGL.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"

namespace Iris2D {
	ViewportGL * ViewportGL::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	ViewportGL * ViewportGL::Create(const Rect * pRect, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	void ViewportGL::Release(ViewportGL *& pViewport) {
	}

	void ViewportGL::ForceRelease(ViewportGL *& pViewport) {
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
}
