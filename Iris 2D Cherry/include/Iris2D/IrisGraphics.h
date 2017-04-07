#ifndef _H_IRISGRAPHICS_

#include "../IrisCommon.h"

namespace Iris2D {
	class IrisSprite;

#if ENGLISH
	/**
	 * Graphics class of Iris 2D
	 *
	 * This class provides a singleton instance to control updating of rendering, do other special effect for post-processing and do some operation to game window.
	 */
#elif CHINESE
	/**
	* Iris 2D Graphcis 类
	*
	* 这个类提供了一个单例来控制画面渲染更新、完成其它特殊的后期特效处理，以及对游戏的的窗口完成一些操作。
	*/
#endif
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
#if ENGLISH
		/**
		* Get the singleton pointer instance of IrisGraphics.
		* @return The singleton pointer instance of IrisGraphics.
		*/
#elif CHINESE
		/**
		* 获取 IrisGraphics 类的单例指针。
		* @return IrisGraphics 类的单例指针。
		*/
#endif
		static IrisGraphics* Instance();

	public:
		void AddSprite(IrisSprite* pSprite);
		void RemoveSprite(IrisSprite* pSprite);

#if ENGLISH
		/**
		* Do a update for rendering, in other words, set game 1 frame going forward.
		*
		* Iris 2D supports frame-locking so it will automatically control the speed of updating by using this function. The mechanism of the frame rate control is to simply wait if game updates too quickly.
		* @see UpdateNoLock()
		*/
#elif CHINESE
		/**
		* 进行一次渲染更新，换言之，让游戏前进一帧。
		*
		* Iris 2D 支持锁帧，因此如果使用该函数，那么 Iris 2D 将会自动地控制游戏的更新速度。 Iris 2D 控制帧率的机制，即是如果游戏更新过快则简单地进行等待。
		* @see UpdateNoLock()
		*/
#endif
		void Update(IR_PARAM_RESULT);

#if ENGLISH
		/**
		* Do a update for rendering, in other words, set game 1 frame going forward.
		*
		* If user doesn't want Iris 2D to manage game frame rate, conversely, to manage game frame manually, this function will work.
		*
		* This function will update frame without controling updating interval, as game will go fast as much as possible.
		* @see Update()
		*/
#elif CHINESE
		/**
		* 进行一次渲染更新，换言之，让游戏前进一帧。
		*
		* 如果用户不希望 Iris 2D 来管理游戏帧率，相反，希望自行手动控制帧率，那么可以使用该函数。
		*
		* 该函数将会在不控制两帧更新时间间隔的情况下更新游戏帧，因此游戏会全速运行。
		* @see Update()
		*/
#endif
		void UpdateNoLock(IR_PARAM_RESULT);

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

