#ifndef _H_GRAPHICS_DX_
#define _H_GRAPHICS_DX_

#include "DirectX/Common.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Iris2D/IGraphics.h"

namespace Iris2D {
	class Graphics;
	class ViewportDX;

	class GraphicsDX : public Proxied<Graphics>, public IGraphics
	{
	private:

		const float c_fDefaultFPS = 60.0f;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;
		float m_fFrameRate = c_fDefaultFPS;
		float m_fMsPerUpdate = 1000.0f / c_fDefaultFPS;

		bool m_bUpdateLockFlag = false;

		std::unordered_set<ViewportDX*> m_stViewports;

		unsigned int m_nFrameCount = 0;

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
		ResultCode Freeze();
		ResultCode Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague) override;
		//void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		void FrameReset() override;
		ResultCode ResizeScreen(unsigned int nWidth, unsigned int nHeight) override;

		void SetWidth(unsigned int nWidth);
		unsigned int GetWidth() const override;
		void SetHeight(unsigned int nHeight);
		unsigned int GetHeight() const override;
		unsigned int GetFrameCount() const override;

		float GetBrightness() const override;
		void SetBrightness(float fBrightness) override;

		void SetFrameRate(float fFrameRate) override;
		float GetFrameRate() const override;

		void Release() override;

		float GetMsPerUpdate() override;
		//void SetLastTime(float fTime);

	private:
		GraphicsDX() = default;
		bool Render();

	public:
		~GraphicsDX() = default;
	};
}

#endif // !_H_GRAPHICS_DX_