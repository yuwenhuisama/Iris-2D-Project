#ifndef _H_EFFECT_FRAME_BUFFER_VERTEX_GL_
#define _H_EFFECT_FRAME_BUFFER_VERTEX_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct EffectFrameBufferVertexGL {
		glm::vec4 m_v4Position{ 0.f, };
		glm::vec2 m_v2Texture{ 0.f, };

		EffectFrameBufferVertexGL(const glm::vec4 &v4Position, const glm::vec2 &v2Texture) : m_v4Position(v4Position),
																							 m_v2Texture(v2Texture) {}
	};
}

#endif // !_H_EFFECT_FRAME_BUFFER_VERTEX_GL_
