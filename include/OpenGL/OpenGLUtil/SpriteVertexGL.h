#ifndef _H_SPRITER_BUFFER_GL_
#define _H_SPRITER_BUFFER_GL_

#include <glm/glm.hpp>

namespace Iris2D {
	struct SpriteVertexGL {
		SpriteVertexGL(const glm::vec4 &v4Position, const glm::vec2 &v2Texture) : m_v4Position(v4Position),
																				  m_v2Texture(v2Texture) {}

		glm::vec4 m_v4Position {0.f,};
		glm::vec2 m_v2Texture;
	};

	struct SpriteInstanceAttributeGL {
		SpriteInstanceAttributeGL(const glm::mat4 &mtRotation, const glm::vec4 &v4TranslateAndZoom,
								  const glm::vec2 &v2OrgPosition, glm::float32 f32Opacity, glm::int32 i32Mirror,
								  const glm::vec4 &v4Rect, const glm::ivec4 &v4Tone) : m_mtRotation(mtRotation),
																					   m_v4TranslateAndZoom(
																							   v4TranslateAndZoom),
																					   m_v2OrgPosition(v2OrgPosition),
																					   m_f32Opacity(f32Opacity),
																					   m_i32Mirror(i32Mirror),
																					   m_v4Rect(v4Rect),
																					   m_v4Tone(v4Tone) {}

		SpriteInstanceAttributeGL() {}

		glm::mat4 m_mtRotation{ 1.f, };
		glm::vec4 m_v4TranslateAndZoom{ 0.0f, 0.0f, 1.0f, 1.0f };
		glm::vec2 m_v2OrgPosition{ 0.f, 0.f };
		glm::float32 m_f32Opacity{ 1.f };
		glm::int32 m_i32Mirror{ 1 };
		glm::vec4 m_v4Rect{ 0.0f, };
		glm::ivec4 m_v4Tone{ 0, };
	};

	struct SpriteIndexedVertexGL {
		SpriteIndexedVertexGL(const glm::vec4 &v4Position) : m_v4Position(v4Position) {}

		glm::vec4 m_v4Position{ 0.f, };
	};

	struct SpriteIndexedInstanceAttributeGL {
		SpriteIndexedInstanceAttributeGL(const glm::vec4 &v4TextureA, const glm::vec4 &v4TextureB,
										 const SpriteInstanceAttributeGL &svAttribute) : m_v4TextureA(v4TextureA),
																						 m_v4TextureB(v4TextureB),
																						 m_svAttribute(svAttribute) {}

		SpriteIndexedInstanceAttributeGL() {}

		glm::vec4 m_v4TextureA;
		glm::vec4 m_v4TextureB;
		SpriteInstanceAttributeGL m_svAttribute {};
	};

}

#endif // !_H_SPRITER_BUFFER_GL_
