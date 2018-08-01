#ifndef _H_SPRITE_SHADER_GL_
#define _H_SPRITE_SHADER_GL_

#include "ShaderGL.h"

namespace Iris2D {
	class SpriteShaderGL : public ShaderGL{
	public:
		static SpriteShaderGL* Instance();

	public:
		bool Initialize();

		void SetTranslationMatrix(const glm::mat4& mtTranspose);
		void SetProjectionMatrix(const glm::mat4& mtProjection);

	private:
		SpriteShaderGL() = default;
		~SpriteShaderGL() = default;
	};
}

#endif // !_H_SPRITE_SHADER_GL_
