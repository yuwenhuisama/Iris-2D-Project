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
	* Iris 2D Graphcis ��
	*
	* ������ṩ��һ�����������ƻ�����Ⱦ���¡������������ĺ�����Ч�����Լ�����Ϸ�ĵĴ������һЩ������
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
		* ����һ����Ⱦ���£�����֮������Ϸǰ��һ֡��
		*
		* Iris 2D ֧����֡��������ʹ�øú�������ô Iris 2D �����Զ��ؿ�����Ϸ�ĸ����ٶȡ� Iris 2D ����֡�ʵĻ��ƣ����������Ϸ���¹�����򵥵ؽ��еȴ���
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
		* ����һ����Ⱦ���£�����֮������Ϸǰ��һ֡��
		*
		* ����û���ϣ�� Iris 2D ��������Ϸ֡�ʣ��෴��ϣ�������ֶ�����֡�ʣ���ô����ʹ�øú�����
		*
		* �ú��������ڲ�������֡����ʱ����������¸�����Ϸ֡�������Ϸ��ȫ�����С�
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
