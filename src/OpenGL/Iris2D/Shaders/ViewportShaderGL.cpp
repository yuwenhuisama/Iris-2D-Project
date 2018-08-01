#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"

namespace Iris2D {
	ViewportShaderGL * ViewportShaderGL::Instance() {
		static ViewportShaderGL shader;
		return &shader;
	}

	bool ViewportShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/viewport_vertex_shader.vert", "shaders/GLSL/viewport_fragment_shader.frag");
	}

	void ViewportShaderGL::SetProjectionMatrix(const glm::mat4& mtMat) {
		SetMatrix("projectionMat", mtMat);
	}

	void ViewportShaderGL::SetModelMatrix(const glm::mat4& mtMat) {
		SetMatrix("modelMat", mtMat);
	}
}
