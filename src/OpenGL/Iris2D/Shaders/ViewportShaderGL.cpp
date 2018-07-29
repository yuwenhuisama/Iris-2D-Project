#include "OpenGL/Iris2D/Shaders/ViewportShaderGL.h"

namespace Iris2D {
	ViewportShaderGL * ViewportShaderGL::Instance() {
		static ViewportShaderGL shader;
		return &shader;
	}

	bool ViewportShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/viewport_vertex_shader.vert", "viewport_fragment_shader.frag");
	}

	void ViewportShaderGL::SetProjectMatrix(const glm::mat4& mtMat) {
		SetMatrix("modelMat", mtMat);
	}

	void ViewportShaderGL::SetModelMatrix(const glm::mat4& mtMat) {
		SetMatrix("projectionMat", mtMat);
	}
}
