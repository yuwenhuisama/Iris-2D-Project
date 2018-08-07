#ifndef _H_EFFECT_FRAME_BUFFER_VERTEX_GL_
#define _H_EFFECT_FRAME_BUFFER_VERTEX_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct EffectFrameBufferVertexGL {
		glm::vec4 m_v4Position{ 0.f, };
		glm::vec2 m_v2Texture{ 0.f, };
	};
}

#endif // !_H_EFFECT_FRAME_BUFFER_VERTEX_GL_
