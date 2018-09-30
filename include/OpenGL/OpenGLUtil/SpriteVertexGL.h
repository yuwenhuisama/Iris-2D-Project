#ifndef _H_SPRITER_BUFFER_GL_
#define _H_SPRITER_BUFFER_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct SpriteVertexGL {
		glm::vec4 m_v4Position {0.f,};
		glm::vec2 m_v2Texture {0.f,};
	};

	struct SpriteInstanceAttributeGL {
		glm::mat4 m_mtRotation{ 1.f, };
		glm::vec4 m_v4TranslateAndZoom{ 0.0f, 0.0f, 1.0f, 1.0f };
		glm::vec2 m_v2OrgPosition{ 0.f, 0.f };
		glm::float32 m_f32Opacity{ 1.f };
		glm::int32 m_i32Mirror{ 1 };
		glm::vec4 m_v4Rect{ 0.0f, };
		glm::ivec4 m_v4Tone{ 0, };
	};

	struct SpriteIndexedVertexGL {
		SpriteVertexGL m_svBase {};
		SpriteInstanceAttributeGL m_svAttribute {};
	};

}

#endif // !_H_SPRITER_BUFFER_GL_
