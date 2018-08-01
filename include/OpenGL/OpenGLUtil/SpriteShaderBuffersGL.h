#ifndef _H_SPRITE_SHADER_BUFFERS_GL_
#define _H_SPRITE_SHADER_BUFFERS_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct SpriteVertexBufferGL {
		glm::mat4 m_mt4Translate { 1.f, };
		glm::mat4 m_mtRotation { 1.f, };
		glm::mat4 m_mtZoom { 1.f, };
		glm::vec2 m_v2OrgPosition { 0.f, 0.f };
		glm::vec1 m_v1Opacity { 1.f };
		glm::ivec1 m_v1Mirror { 1 };
	};
}

#endif // !_H_SPRITE_SHADER_BUFFERS_GL_
