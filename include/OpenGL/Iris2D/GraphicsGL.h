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

	public:
		static GraphicsGL* Instance();

	public:
		// Í¨¹ý IGraphics ¼Ì³Ð
		virtual void Update(IR_PARAM_RESULT) override;
		virtual void UpdateNoLock(IR_PARAM_RESULT) override;
		virtual void Wait(unsigned int nDuration, IR_PARAM_RESULT) override;
		virtual void FadeOut(unsigned int nDuration, IR_PARAM_RESULT) override;
		virtual void FadeIn(unsigned int nDuration, IR_PARAM_RESULT) override;
		virtual void Freeze(IR_PARAM_RESULT) override;
		virtual void Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague, IR_PARAM_RESULT) override;
		virtual void FrameReset() override;
		virtual void ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) override;
		virtual void SetWidth(unsigned int nWidth) override;
		virtual unsigned int GetWidth() const override;
		virtual void SetHeight(unsigned int nHeight) override;
		virtual unsigned int GetHeight() const override;
		virtual unsigned int GetFrameCount() const override;
		virtual float GetBrightness() const override;
		virtual void SetBrightness(float fBrightness) override;
		virtual void SetFrameRate(float fFrameRate) override;
		virtual float GetFrameRate() const override;
		virtual void Release() override;
		virtual float GetMsPerUpdate() override;

		void AddViewport(ViewportGL*& pViewport);
		void RemoveViewport(ViewportGL*& pViewport);

		bool Intialize();
		void Render();

	private:

		bool CreateVertexBackBuffer();

		GraphicsGL() = default;
		~GraphicsGL() = default;

	public:
		friend class ApplicationGL;
	};
}


#endif // !_H_GRAPHICS_GL_
