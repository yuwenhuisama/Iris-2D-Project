#ifndef _H_GRAPHICS_DX_
#define _H_GRAPHICS_DX_

#include "DirectX/Common.h"

namespace Iris2D {
	class ViewportDX;


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
	class GraphicsDX
	{
	private:

		const float c_fDefaultFPS = 60.0f;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;
		float m_fFrameRate = c_fDefaultFPS;
		float m_fMsPerUpdate = 1000.0f / c_fDefaultFPS;

		bool m_bUpdateLockFlag = false;

		std::unordered_set<ViewportDX*> m_stViewports;

	public:
		float m_fLag = 0.0f;
		float m_fLastTime = 0.0f;
		float m_fCurrentTime = 0;

	public:
		/**
		* \~english
		* Get the singleton pointer instance of GraphicsDX.
		* @return The singleton pointer instance of GraphicsDX.
		*/
		/**
		* \~chinese
		* ��ȡ GraphicsDX ��ĵ���ָ�롣
		* @return GraphicsDX ��ĵ���ָ�롣
		*/
		static GraphicsDX* Instance();

	public:
		void AddViewport(ViewportDX* pViewport);
		void RemoveViewport(ViewportDX* pViewport);

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
		GraphicsDX() = default;
		bool Render();

	public:
		~GraphicsDX() = default;
	};
}

#endif // !_H_GRAPHICS_DX_