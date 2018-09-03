#ifndef _H_GRAPHICS_
#define _H_GRAPHICS_

#include "Common/Iris2D/IGraphics.h"
#include "Proxy.h"

namespace Iris2D {
	/**
	* \~english
	* Graphics class of Iris 2D
	*
	* This class provides a singleton instance to control updating of rendering, do other special effect for post-processing and do some operation to game window.
	*/
	/**
	* \~chinese
	* Iris 2D Graphcis 类
	*
	* 这个类提供了一个单例来控制画面渲染更新、完成其它特殊的后期特效处理，以及对游戏的的窗口完成一些操作。
	*/
	class Graphics : public Proxy<IGraphics>, public IGraphics {
	public:
		static Graphics* Instance();

	public:
		/**
		* \~english
		* Do a update for rendering, in other words, set game 1 frame going forward.
		*
		* Iris 2D supports frame-locking so it will automatically control the speed of updating by using this function. The mechanism of the frame rate control is to simply wait if game updates too quickly.
		* @see UpdateNoLock()
		*/
		/**
		* \~chinese
		* 进行一次渲染更新，换言之，让游戏前进一帧。
		*
		* Iris 2D 支持锁帧，因此如果使用该函数，那么 Iris 2D 将会自动地控制游戏的更新速度。 Iris 2D 控制帧率的机制，即是如果游戏更新过快则简单地进行等待。
		* @see UpdateNoLock()
		*/
		ResultCode Update() override;

		/**
		* \~english
		* Do a update for rendering, in other words, set game 1 frame going forward.
		*
		* If user doesn't want Iris 2D to manage game frame rate, conversely, to manage game frame manually, this function will work.
		*
		* This function will update frame without controling updating interval, as game will go fast as much as possible.
		* @see Update()
		*/
		/**
		* \~chinese
		* 进行一次渲染更新，换言之，让游戏前进一帧。
		*
		* 如果用户不希望 Iris 2D 来管理游戏帧率，相反，希望自行手动控制帧率，那么可以使用该函数。
		*
		* 该函数将会在不控制两帧更新时间间隔的情况下更新游戏帧，因此游戏会全速运行。
		* @see Update()
		*/
		ResultCode UpdateNoLock() override;

		ResultCode Wait(unsigned int nDuration) override;
		ResultCode FadeOut(unsigned int nDuration) override;
		ResultCode FadeIn(unsigned int nDuration) override;
		ResultCode Freeze() override;
		ResultCode Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague) override;
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		void FrameReset() override;
		ResultCode ResizeScreen(unsigned int nWidth, unsigned int nHeight) override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		unsigned int GetFrameCount() const override;

		float GetBrightness() const override;
		void SetBrightness(float fBrightness) override;

		void SetFrameRate(float fFrameRate) override;
		float GetFrameRate() const override;

		void Release() override;

		float GetMsPerUpdate() override;

	private:
		Graphics();
		~Graphics() = default;
	};
}

#endif // !_H_GRAPHICS_
