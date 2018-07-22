#ifndef _H_GRAPHICS_GL_
#define _H_GRAPHICS_GL_

#include "Common/Iris2D/IGraphics.h"
#include "Common/Iris2D/Proxied.h"

#include <unordered_set>

namespace Iris2D {
	class ViewportGL;
	class Graphics;
	class GraphicsGL : public IGraphics, public Proxied<Graphics> {
	private:
		std::unordered_set<ViewportGL*> m_stViewports;

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
		virtual unsigned int GetWidth() override;
		virtual void SetHeight(unsigned int nHeight) override;
		virtual unsigned int GetHeight() override;
		virtual unsigned int GetFrameCount() override;
		virtual unsigned int GetBrightness() override;
		virtual void SetBrightness(unsigned int nBrightness) override;
		virtual void SetFrameRate(float fFrameRate) override;
		virtual float GetFrameRate() const override;
		virtual void Release() override;
		virtual float GetMsPerUpdate() override;

		void AddViewport(ViewportGL*& pViewport);
		void RemoveViewport(ViewportGL*& pViewport);

	private:
		GraphicsGL() = default;
		~GraphicsGL() = default;
	};
}


#endif // !_H_GRAPHICS_GL_
