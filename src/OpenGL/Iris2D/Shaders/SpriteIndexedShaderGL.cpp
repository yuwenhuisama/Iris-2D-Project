#include "OpenGL/Iris2D/Shaders/SpriteIndexedShaderGL.h"

namespace Iris2D {

	SpriteIndexedShaderGL* SpriteIndexedShaderGL::Instance() {
		static SpriteIndexedShaderGL instance;
		return &instance;
	}

	bool SpriteIndexedShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/sprite_indexed_vertex_shader.vert", "shaders/GLSL/sprite_fragment_shader.frag");
	}

	void SpriteIndexedShaderGL::SetProjectionMatrix(const glm::mat4& mtProjection) {
		SetMatrix("projectionMat", mtProjection);
	}
}
