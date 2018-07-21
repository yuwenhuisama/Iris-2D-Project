#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/OpenGLHelper.h"
#include "OpenGL/Common.h"

namespace Iris2D {
	GraphicsGL* GraphicsGL::Instance() {
		static GraphicsGL graphics;
		return &graphics;
	}

	void GraphicsGL::Update(IR_PARAM_RESULT_CT) {
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(OpenGLHelper::Instance()->GetWindow());
		glfwPollEvents();
	}

	void GraphicsGL::UpdateNoLock(IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::Wait(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::FadeOut(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::FadeIn(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::Freeze(IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::FrameReset() {
	}

	void GraphicsGL::ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
	}

	void GraphicsGL::SetWidth(unsigned int nWidth) {
	}

	unsigned int GraphicsGL::GetWidth() {
		return 0;
	}

	void GraphicsGL::SetHeight(unsigned int nHeight) {
	}

	unsigned int GraphicsGL::GetHeight() {
		return 0;
	}

	unsigned int GraphicsGL::GetFrameCount() {
		return 0;
	}

	unsigned int GraphicsGL::GetBrightness() {
		return 0;
	}

	void GraphicsGL::SetBrightness(unsigned int nBrightness) {
	}

	void GraphicsGL::SetFrameRate(float fFrameRate) {
	}

	float GraphicsGL::GetFrameRate() const {
		return 0.0f;
	}

	void GraphicsGL::Release() {
	}

	float GraphicsGL::GetMsPerUpdate() {
		return 0.0f;
	}
}
