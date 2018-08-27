#ifndef _H_GRAPHICS_GL_
#define _H_GRAPHICS_GL_

#include "Common/Iris2D/IGraphics.h"
#include "Common/Iris2D/Proxied.h"
#include "OpenGL/Common.h"

//#include <unordered_set>
#include <map>

namespace Iris2D {
	class TextureGL;
	class ViewportGL;
	class Graphics;
	class TextureGL;
	class GraphicsGL : public IGraphics, public Proxied<Graphics> {
	private:
		//std::unordered_set<ViewportGL*> m_stViewports;
		std::multimap<float, ViewportGL*, std::less<>> m_stViewports;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;

		TextureGL* m_pBackBuffer = nullptr;
		TextureGL* m_pFreezedBackBuffer = nullptr;

		GLuint m_nVAO = 0;
		GLuint m_nVBO = 0;
		GLuint m_nEBO = 0;

		bool m_bVsync = true;

		float m_fFrameRate = 60.0f;
		float m_fMsPerUpdate = 0.0f;

		unsigned int m_nFrameCount = 0;

		double m_dCurrentTime = 0;
		double m_dLastTime = 0;

		float m_fTimeDelta = 0.0f;

		bool m_bUpdateLockFlag = false;

		float m_fBrightness = 0.5;

		bool m_bFading = false;
		unsigned int m_nDuration = 0;
		unsigned int m_nCurrentDuration = 0;

		bool m_bFreezing = false;
		bool m_bTransition = false;

		bool m_bManualResize = false;

	public:
		static GraphicsGL* Instance();

	public:
		// Í¨¹ý IGraphics ¼Ì³Ð
		ResultCode Update() override;
		ResultCode UpdateNoLock() override;
		ResultCode Wait(unsigned int nDuration) override;
		ResultCode FadeOut(unsigned int nDuration) override;
		ResultCode FadeIn(unsigned int nDuration) override;
		ResultCode Freeze() override;
		ResultCode Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague) override;
		void FrameReset() override;
		ResultCode ResizeScreen(unsigned int nWidth, unsigned int nHeight) override;
		void SetWidth(unsigned int nWidth) override;
		unsigned int GetWidth() const override;
		void SetHeight(unsigned int nHeight) override;
		unsigned int GetHeight() const override;
		unsigned int GetFrameCount() const override;
		float GetBrightness() const override;
		void SetBrightness(float fBrightness) override;
		void SetFrameRate(float fFrameRate) override;
		float GetFrameRate() const override;
		void Release() override;
		float GetMsPerUpdate() override;

		void AddViewport(ViewportGL*& pViewport);
		void RemoveViewport(ViewportGL*& pViewport);

		bool Intialize();
		ResultCode Render();

		bool IsManualResize() const;
		void AutoResize(unsigned int nWidth, unsigned int nHeight);

	private:

		bool CreateVertexBackBuffer();

		GraphicsGL() = default;
		~GraphicsGL() = default;

	public:
		friend class ApplicationGL;
	};
}


#endif // !_H_GRAPHICS_GL_
