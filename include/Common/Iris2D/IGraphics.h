#ifndef _H_IGRAPHICS_
#define _H_IGRAPHICS_

#include "Common/Util/Result.h"

namespace Iris2D {
	class IGraphics {
	public:
		virtual void Update(IR_PARAM_RESULT) = 0;
		virtual void UpdateNoLock(IR_PARAM_RESULT) = 0;

		virtual void Wait(unsigned int nDuration, IR_PARAM_RESULT) = 0;
		virtual void FadeOut(unsigned int nDuration, IR_PARAM_RESULT) = 0;
		virtual void FadeIn(unsigned int nDuration, IR_PARAM_RESULT) = 0;
		virtual void Freeze(IR_PARAM_RESULT) = 0;
		virtual void Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT) = 0;
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		virtual void FrameReset() = 0;
		virtual void ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) = 0;

		virtual void SetWidth(unsigned int nWidth) = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual void SetHeight(unsigned int nHeight) = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetFrameCount() const = 0;

		virtual unsigned int GetBrightness() const = 0;
		virtual void SetBrightness(unsigned int nBrightness) = 0;

		virtual void SetFrameRate(float fFrameRate) = 0;
		virtual float GetFrameRate() const = 0;

		virtual void Release() = 0;

		virtual float GetMsPerUpdate() = 0;
	};
}

#endif // !_H_IGRAPHICS_
