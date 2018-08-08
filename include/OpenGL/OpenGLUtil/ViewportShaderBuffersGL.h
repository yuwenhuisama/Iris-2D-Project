#ifndef _H_VIEWPORT_SHADER_BUFFERS_GL_
#define _H_VIEWPORT_SHADER_BUFFERS_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct ViewportVertexBufferGL {
		glm::mat4 m_mt4Translate { 1.f, };
		glm::vec2 m_v2OrgPosition { 0.f, 0.f };
		glm::vec4 m_v4Rect { 0.0f, };
		glm::ivec4 m_v4Tone { 0, };
	};
}

#endif // !_H_VIEWPORT_SHADER_BUFFERS_GL_
