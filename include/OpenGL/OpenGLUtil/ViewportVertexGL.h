#ifndef _H_VIEWPORT_VERTEX_GL
#define _H_VIEWPORT_VERTEX_GL

#include <glm/glm.hpp>

namespace Iris2D {
	struct ViewportVertexGL {
		ViewportVertexGL(const glm::vec4 &v4Position, const glm::vec2 &v2Texture) : m_v4Position(v4Position),
																					m_v2Texture(v2Texture) {}

		glm::vec4 m_v4Position { 0.f, 0.f, 0.f, 0.f };
		glm::vec2 m_v2Texture { 0.f, 0.f };
	};
}

#endif // _H_VIEWPORT_VERTEX_GL
