#ifndef _H_SPRITE_RENDER_QUEUE_GL_
#define _H_SPRITE_RENDER_QUEUE_GL_
#include <deque>
#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"
#include "OpenGL/Common.h"

namespace Iris2D {

	enum class TargetType {
		SpriteStatic = 0,
		SpriteIndexed,
		None,
		End,
	};

	struct RenderCommand {
		TargetType m_eTargetType = TargetType::None;
		SpriteBaseGL* m_pSprite = nullptr;
	};

	class BitmapGL;
	class TextureGL;
	struct SpriteInstanceAttributeGL;
	class SpriteRenderQueueGL {
	private:
		std::deque<RenderCommand> m_dqRenderCommandQueue {};

	public:
		static SpriteRenderQueueGL* Instance();

	public:
		ResultCode Push(const RenderCommand& rcCommand);
		ResultCode Push(RenderCommand&& rcCommand);

	private:
		ResultCode Render();
		ResultCode RenderSpriteStatics();

		bool CreateSpriteStaticVertexBuffer(const TextureGL* pTexture, GLuint& nVAO, GLuint& nVBO, GLuint& nEBO, GLuint& nInstanceVBO, SpriteInstanceAttributeGL* pAttribArray, unsigned int nArraySize);

	private:
		SpriteRenderQueueGL() = default;
		~SpriteRenderQueueGL() = default;
	};
}

#endif // !_H_SPRITE_RENDER_QUEUE_GL_
