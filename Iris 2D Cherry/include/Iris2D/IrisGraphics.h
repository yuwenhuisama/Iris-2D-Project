#ifndef _H_IRISGRAPHICS_

#include "../IrisCommon.h"

namespace Iris2D {
	class IrisSprite;

	/**
	 * Graphics class of Iris 2D
	 *
	 * This class provides a singleton instance to control updating of rendering, do other special effect for post-processing and do some operation to game window.
	 */
	class IrisGraphics
	{
	private:
		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;
		float m_fFrameRate = 60.0f;
		float m_fMsPerUpdate = 1000.0f / m_fFrameRate;

		bool m_bUpdateLockFlag = false;

		std::unordered_set<IrisSprite*> m_stSprites;

	public:
		float m_fLag = 0.0f;
		float m_fLastTime = 0.0f;
		float m_fCurrentTime = 0;

	public:

		/**
		* Get the singleton instance of IrisApplication.
		*/
		static IrisGraphics* Instance();

	public:
		void AddSprite(IrisSprite* pSprite);
		void RemoveSprite(IrisSprite* pSprite);

		/**
		 * Do a update for rendering, in other words, set game 1 frame going forward.
		 *
		 * Iris 2D supports frame-locking so it will automatically control the speed of updating.
		 */
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

		void SetFrameRate(float fFrameRate);
		float GetFrameRate() const;

		void Release();

		float GetMsPerUpdate();
		//void SetLastTime(float fTime);

	private:
		IrisGraphics() = default;
	public:
		~IrisGraphics() = default;
	};
}
#endif // !_H_IRISGRAPHICS_

