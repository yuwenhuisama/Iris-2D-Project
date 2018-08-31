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

	void ViewportShaderGL::SetOrgPosition(const glm::vec2& v2OrgPosition) {
		SetFloat2("orgPos", v2OrgPosition);
	}

	void ViewportShaderGL::SetRect(const glm::vec4& v4Rect) {
		SetFloat4("rect", v4Rect.r, v4Rect.g, v4Rect.b, v4Rect.a);
	}

	void ViewportShaderGL::SetTone(const glm::ivec4& v4Tone) {
		SetFloat4("tone", v4Tone.r, v4Tone.g, v4Tone.b, v4Tone.a);
	}

	void ViewportShaderGL::SetModelMatrix(const glm::mat4& mtMat) {
		SetMatrix("modelMat", mtMat);
	}
}