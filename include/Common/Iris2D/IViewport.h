#ifndef _H_IVIEWPORT_
#define _H_IVIEWPORT_

namespace Iris2D {
	class Rect;
	class Color;
	typedef Color Tone;

	class IViewport {
	public:
		virtual void SetOX(float fOX) = 0;
		virtual float GetOX() const = 0;

		virtual void SetOY(float fOY) = 0;
		virtual float GetOY() const = 0;

		virtual void SetSrcRect(Rect*& pSrcRect) = 0;
		virtual Rect* GetSrcRect() const = 0;

		virtual void SetTone(Tone*& pTone) = 0;
		virtual Tone* GetTone() const = 0;

		virtual void SetZ(float fZ) = 0;
		virtual float GetZ() = 0;
	};
}

#endif // !_H_IVIEWPORT_
