#ifndef _H_BACK_SHADER_GL_
#define _H_BACK_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

namespace Iris2D {
	class BackShaderGL : public ShaderGL {
	public:
		static BackShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectionMatrix(const glm::mat4& mt4Projection);

	private:
		BackShaderGL() = default;
		~BackShaderGL() = default;
	};
}

#endif // _H_BACK_SHADER_GL_
