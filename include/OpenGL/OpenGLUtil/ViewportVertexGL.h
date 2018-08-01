#ifndef _H_VIEWPORT_VERTEX_GL
#define _H_VIEWPORT_VERTEX_GL

#include <glm/glm.hpp>

namespace Iris2D {
	struct ViewportVertexGL {
		glm::vec4 m_v4Position { 0.f, 0.f, 0.f, 0.f };
		glm::vec2 m_v2Texture { 0.f, 0.f };
	};
}

#endif // _H_VIEWPORT_VERTEX_GL
