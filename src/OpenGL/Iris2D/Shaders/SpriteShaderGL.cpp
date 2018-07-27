#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

namespace Iris2D {
	SpriteShaderGL * SpriteShaderGL::Instance() {
		static SpriteShaderGL shader;
		return &shader;
	}

	bool SpriteShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/glsl/sprite_vertex_shader.vert", "shaders/glsl/sprite_fragment_shader.frag");
	}
}
