#ifndef _H_IRISGRAPHICS_

#include "../IrisCommon.h"

namespace Iris2D {
	class IrisSprite;
	class IrisGraphics
	{
	private:
		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;

		std::unordered_set<IrisSprite*> m_stSprites;

	public:
		static IrisGraphics* Instance();

	public:
		void AddSprite(IrisSprite* pSprite);
		void RemoveSprite(IrisSprite* pSprite);

		void Update(IR_PARAM_RESULT);
		void Wait(unsigned int nDuration, IR_PARAM_RESULT);
		void FadeOut(unsigned int nDuration, IR_PARAM_RESULT);
		void FadeIn(unsigned int nDuration, IR_PARAM_RESULT);
		void Freeze(IR_PARAM_RESULT);
		void Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT);
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		void FrameReset();
		void ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		void SetWidth(unsigned int nWidth);
		unsigned int GetWidth();
		void SetHeight(unsigned int nHeight);
		unsigned int GetHeight();
		unsigned int GetFrameCount();

		unsigned int GetBrightness();
		void SetBrightness(unsigned int nBrightness);

		float GetFrameRate();

		void Release();

	private:
		IrisGraphics() = default;
	public:
		~IrisGraphics() = default;
	};
}
#endif // !_H_IRISGRAPHICS_

