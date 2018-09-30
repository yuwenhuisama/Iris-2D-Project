#ifndef _H_SPRITE_SHADER_BUFFERS_GL_
#define _H_SPRITE_SHADER_BUFFERS_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct SpriteStaticVertexShaderBufferGL {
		glm::mat4 m_mt4Translate { 1.f, };
		glm::mat4 m_mtRotation { 1.f, };
		glm::mat4 m_mtZoom { 1.f, };
		glm::vec2 m_v2OrgPosition { 0.f, 0.f };
		glm::float32 m_f32Opacity { 1.f };
		glm::int32 m_i32Mirror { 1 };
		glm::vec4 m_v4Rect { 0.0f, };
		glm::ivec4 m_v4Tone { 0, };
	};
}

#endif // !_H_SPRITE_SHADER_BUFFERS_GL_
