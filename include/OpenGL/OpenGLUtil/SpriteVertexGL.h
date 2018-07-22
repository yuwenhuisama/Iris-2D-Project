#ifndef _H_SPRITER_BUFFER_GL_
#define _H_SPRITER_BUFFER_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct SpriteVertexGL {
		glm::vec4 m_v4Position;
		glm::vec2 m_v2Texture;
	};
}

#endif // !_H_SPRITER_BUFFER_GL_
