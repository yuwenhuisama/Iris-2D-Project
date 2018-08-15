#include "OpenGL/Iris2D/Shaders/BackTransitionShaderGL.h"

namespace Iris2D {

	BackTransitionShaderGL* BackTransitionShaderGL::Instance() {
		static BackTransitionShaderGL shader;
		return &shader;
	}

	bool BackTransitionShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/back_vertex_shader.vert", "shaders/GLSL/back_transition_fragment_shader.frag");
	}

	void BackTransitionShaderGL::SetProjectionMatrix(const glm::mat4& mt4Projection) {
		SetMatrix("projectionMat", mt4Projection);
	}

	void BackTransitionShaderGL::SetBrightness(float fBrightness) {
		SetFloat("brightness", fBrightness);
	}
}
