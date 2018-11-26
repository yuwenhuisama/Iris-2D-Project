#ifndef _H_SPRITE_INDEXED_SHADER_GL_
#define _H_SPRITE_INDEXED_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

namespace Iris2D {
	class SpriteIndexedShaderGL : public ShaderGL {
	public:
		static SpriteIndexedShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectionMatrix(const glm::mat4& mtProjection);

	private:
		SpriteIndexedShaderGL() = default;
		~SpriteIndexedShaderGL() = default;

	};
}

#endif // !_H_SPRITE_INDEXED_SHADER_GL_