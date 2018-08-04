#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

namespace Iris2D {
	SpriteShaderGL * SpriteShaderGL::Instance() {
		static SpriteShaderGL shader;
		return &shader;
	}

	bool SpriteShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/sprite_vertex_shader.vert", "shaders/GLSL/sprite_fragment_shader.frag");
	}

	void SpriteShaderGL::SetTranslationMatrix(const glm::mat4& mtTranspose) {
		SetMatrix("spriteVertexInfo.translateMat", mtTranspose);
	}

	void SpriteShaderGL::SetRotationMatrix(const glm::mat4& mtRotate) {
		SetMatrix("spriteVertexInfo.rotationMat", mtRotate);
	}

	void SpriteShaderGL::SetZoomMatrix(const glm::mat4& mtZoom) {
		SetMatrix("spriteVertexInfo.zoomMat", mtZoom);
	}

	void SpriteShaderGL::SetProjectionMatrix(const glm::mat4& mtProjection) {
		SetMatrix("projectionMat", mtProjection);
	}

	void SpriteShaderGL::SetOrgPosition(const glm::vec2 & v2OrgPosition) {
		SetFloat2("spriteVertexInfo.orgPos", v2OrgPosition);
	}

	void SpriteShaderGL::SetOpacity(const glm::float32& f32Opacity) {
		SetFloat("spriteFragmentInfo.opacity", f32Opacity);
	}

	void SpriteShaderGL::SetMirror(const glm::int32& nMirror) {
		SetInt("spriteFragmentInfo.mirror", nMirror);
	}

	void SpriteShaderGL::SetRect(const glm::vec4& v4Rect) {
		SetFloat4("spriteFragmentInfo.rect", v4Rect.x, v4Rect.y, v4Rect.z, v4Rect.w);
	}

	void SpriteShaderGL::SetTone(const glm::ivec4& v4Tone) {
		SetInt4("spriteFragmentInfo.tone", v4Tone.x, v4Tone.y, v4Tone.z, v4Tone.w);
	}
}
