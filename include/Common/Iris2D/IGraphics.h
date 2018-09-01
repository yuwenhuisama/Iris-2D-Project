#ifndef _H_IGRAPHICS_
#define _H_IGRAPHICS_

#include "Common/Util/Result.h"
#include <string>

namespace Iris2D {
	class IGraphics {
	public:
		virtual ResultCode Update() = 0;
		virtual ResultCode UpdateNoLock() = 0;

		virtual ResultCode Wait(unsigned int nDuration) = 0;
		virtual ResultCode FadeOut(unsigned int nDuration) = 0;
		virtual ResultCode FadeIn(unsigned int nDuration) = 0;
		virtual ResultCode Freeze() = 0;
		virtual ResultCode Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague) = 0;
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		virtual void FrameReset() = 0;
		virtual ResultCode ResizeScreen(unsigned int nWidth, unsigned int nHeight) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetFrameCount() const = 0;

		virtual float GetBrightness() const = 0;
		virtual void SetBrightness(float fBrightness) = 0;

		virtual void SetFrameRate(float fFrameRate) = 0;
		virtual float GetFrameRate() const = 0;

		virtual void Release() = 0;

		virtual float GetMsPerUpdate() = 0;
	};
}

#endif // !_H_IGRAPHICS_
