#ifndef _H_GRAPHICS_GL_
#define _H_GRAPHICS_GL_

#include "Common/Iris2D/IGraphics.h"
#include "Common/Iris2D/Proxied.h"
#include "OpenGL/Common.h"

#include <unordered_set>

namespace Iris2D {
	class TextureGL;
	class ViewportGL;
	class Graphics;
	class GraphicsGL : public IGraphics, public Proxied<Graphics> {
	private:
		std::unordered_set<ViewportGL*> m_stViewports;

		unsigned int m_nWidth = 0;
		unsigned int m_nHeight = 0;

		TextureGL* m_pBackBuffer = nullptr;
		GLuint m_nVAO = 0;
		GLuint m_nVBO = 0;
		GLuint m_nEBO = 0;

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
		virtual void Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT) override;
		virtual void FrameReset() override;
		virtual void ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) override;
		virtual void SetWidth(unsigned int nWidth) override;
		virtual unsigned int GetWidth() const override;
		virtual void SetHeight(unsigned int nHeight) override;
		virtual unsigned int GetHeight() const override;
		virtual unsigned int GetFrameCount() override;
		virtual unsigned int GetBrightness() override;
		virtual void SetBrightness(unsigned int nBrightness) override;
		virtual void SetFrameRate(float fFrameRate) override;
		virtual float GetFrameRate() const override;
		virtual void Release() override;
		virtual float GetMsPerUpdate() override;

		void AddViewport(ViewportGL*& pViewport);
		void RemoveViewport(ViewportGL*& pViewport);

		bool Intialize();

	private:

		bool CreateVertexBackBuffer();

		GraphicsGL() = default;
		~GraphicsGL() = default;
	};
}


#endif // !_H_GRAPHICS_GL_
