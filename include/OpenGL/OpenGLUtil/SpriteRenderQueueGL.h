#ifndef _H_SPRITE_RENDER_QUEUE_GL_
#define _H_SPRITE_RENDER_QUEUE_GL_
#include <deque>
#include "OpenGL/Iris2D/Sprites/SpriteBaseGL.h"
#include "OpenGL/Common.h"
#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"
#include "OpenGL/OpenGLUtil/BufferManagerGL.h"

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
	class SpriteRenderQueueGL {
	private:
		std::deque<RenderCommand> m_dqRenderCommandQueue {};
		BufferManagerGL<SpriteInstanceAttributeGL>* m_pStaticSpriteInstanceBufferManager = nullptr;
		BufferManagerGL<SpriteVertexGL>* m_pStaticSpriteVertexBufferManager = nullptr;

		std::vector<GLuint> m_vcVAOs {};
		unsigned int m_nCurrentVAOIndex = 0;

		GLuint m_nEBO = 0;

	public:
		static SpriteRenderQueueGL* Instance();
		bool Initialize();
		bool Release();

	public:
		ResultCode Push(const RenderCommand& rcCommand);

	private:
		ResultCode Render();
		ResultCode RenderSpriteStatics();

	private:
		SpriteRenderQueueGL() = default;
		~SpriteRenderQueueGL() = default;
	};
}

#endif // !_H_SPRITE_RENDER_QUEUE_GL_
