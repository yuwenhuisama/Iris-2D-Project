#ifndef _H_BACKGROUND_SHADER_GL_
#define _H_BACKGROUND_SHADER_GL_
#include "OpenGL/Iris2D/Shaders/ShaderGL.h"
#include <GL/glew.h>

namespace Iris2D {

	class ShaderGL;
	class BackGroundShaderGL : public ShaderGL {
	public:
		static BackGroundShaderGL* Instance();
	public:
		bool Initialize();

	private:
		BackGroundShaderGL() = default;
		~BackGroundShaderGL() = default;
	};

}

#endif // _H_BACKGROUD_SHADER_GL_

