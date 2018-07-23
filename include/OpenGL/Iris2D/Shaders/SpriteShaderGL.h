#ifndef _H_SPRITE_SHADER_GL_
#define _H_SPRITE_SHADER_GL_

#include "ShaderGL.h";

namespace Iris2D {
	class SpriteShaderGL : public ShaderGL{
	public:
		static SpriteShaderGL* Instance();

	public:
		bool Initialize() override;

	public:
		SpriteShaderGL() = default;
		~SpriteShaderGL() = default;
	};
}

#endif // !_H_SPRITE_SHADER_GL_
