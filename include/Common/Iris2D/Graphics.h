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
		void Update(IR_PARAM_RESULT);

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
		void UpdateNoLock(IR_PARAM_RESULT);

		void Wait(unsigned int nDuration, IR_PARAM_RESULT);
		void FadeOut(unsigned int nDuration, IR_PARAM_RESULT);
		void FadeIn(unsigned int nDuration, IR_PARAM_RESULT);
		void Freeze(IR_PARAM_RESULT);
		void Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague, IR_PARAM_RESULT);
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		void FrameReset();
		void ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		void SetWidth(unsigned int nWidth);
		unsigned int GetWidth() const;
		void SetHeight(unsigned int nHeight);
		unsigned int GetHeight() const;
		unsigned int GetFrameCount() const;

		float GetBrightness() const;
		void SetBrightness(float fBrightness);

		void SetFrameRate(float fFrameRate);
		float GetFrameRate() const;

		void Release();

		float GetMsPerUpdate();

	private:
		Graphics();
		~Graphics() = default;
	};
}

#endif // !_H_GRAPHICS_
