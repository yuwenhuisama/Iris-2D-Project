#ifndef _H_ISPRITE_
#define _H_ISPRITE_

#include "Common/Util/Result.h"

namespace Iris2D {

	namespace Effect {
		class EffectBase;
	}

	class Bitmap;
	class Rect;
	class Color;
	typedef Color Tone;
	class ISprite {
	protected:
		virtual ~ISprite() = default;

	public:
		virtual ResultCode SetBitmap(Bitmap*& pBitmap) = 0;
		virtual Bitmap* GetBitmap() const = 0;

		virtual void SetX(float fX) = 0;
		virtual float GetX() const = 0;

		virtual void SetY(float fY) = 0;
		virtual float GetY() const = 0;

		virtual void SetZ(float fZ) = 0;
		virtual float GetZ() const = 0;

		virtual void SetAngle(float fAngle) = 0;
		virtual float GetAngle() const = 0;

		virtual void SetZoomX(float fZoomX) = 0;
		virtual float GetZoomX() const = 0;

		virtual void SetZoomY(float fZoomY) = 0;
		virtual float GetZoomY() const = 0;

		virtual void SetOX(float fOX) = 0;
		virtual float GetOX() const = 0;

		virtual void SetOY(float fOY) = 0;
		virtual float GetOY() const = 0;

		virtual void SetMirror(bool bMirror) = 0;
		virtual bool GetMirror() const = 0;

		virtual void SetVisible(bool bVisible) = 0;
		virtual bool GetVisible() const = 0;

		virtual void SetOpacity(float fOpacity) = 0;
		virtual float GetOpacity() const = 0;

		virtual void SetSrcRect(Rect*& pSrcRect) = 0;
		virtual Rect* GetSrcRect() const = 0;

		virtual void SetTone(Tone*& pTone) = 0;
		virtual Tone* GetTone() const = 0;

		virtual ResultCode Update() = 0;
		virtual ResultCode SetEffect(Effect::EffectBase* pEffect) = 0;
	};
}

#endif // !_H_ISPRITE_
