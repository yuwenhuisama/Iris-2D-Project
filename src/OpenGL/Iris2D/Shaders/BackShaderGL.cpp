#include "OpenGL/Iris2D/Shaders/BackShaderGL.h"

namespace Iris2D {

	BackShaderGL* BackShaderGL::Instance() {
		static BackShaderGL backshader;
		return &backshader;
	}

	bool BackShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/back_vertex_shader.vert", "shaders/GLSL/back_fragment_shader.frag");
	}

	void BackShaderGL::SetProjectionMatrix(const glm::mat4& mt4Projection) {
		SetMatrix("projectionMat", mt4Projection);
	}
}
