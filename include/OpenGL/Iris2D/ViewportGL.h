#ifndef _H_VIEWPORT_GL_
#define _H_VIEWPORT_GL_

#include "Common/Iris2D/IViewport.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/Result.h"

namespace Iris2D {
	class Viewport;
	class Rect;
	class Color;
	typedef Color Tone;

	class ViewportGL : public Proxied<Viewport>, public IViewport {
	public:
		static ViewportGL* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		static ViewportGL* Create(const Rect* pRect, IR_PARAM_RESULT);
		static void Release(ViewportGL*& pViewport);

		static void ForceRelease(ViewportGL*& pViewport);

	private:
		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;

	public:
		// Í¨¹ý IViewport ¼Ì³Ð
		virtual void SetOX(float fOX) override;
		virtual float GetOX() const override;
		virtual void SetOY(float fOY) override;
		virtual float GetOY() const override;
		virtual void SetSrcRect(Rect *& pSrcRect) override;
		virtual Rect * GetSrcRect() const override;
		virtual void SetTone(Tone *& pTone) override;
		virtual Tone * GetTone() const override;
	};
}

#endif // !_H_VIEWPORT_GL_
