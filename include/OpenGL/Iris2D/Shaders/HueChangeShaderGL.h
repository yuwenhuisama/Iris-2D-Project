#ifndef _H_HUECHANGE_SHADER_GL_
#define _H_HUECHANGE_SHADER_GL_

#include "ShaderGL.h"
#include <GL/glew.h>
namespace Iris2D {
	class HueChangeShaderGL :public ShaderGL {
	public :
		static HueChangeShaderGL* Instance();

		bool Initialize();

		void SetHue(int nHue);
		GLuint BindBufferData();

	private:
		HueChangeShaderGL() = default;
		~HueChangeShaderGL() = default;
	};
}

#endif // !_H_HUECHANGE_SHADER_GL_
