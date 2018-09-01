#ifndef _H_CLEARRECT_SHADER_GL_
#define _H_CLEARRECT_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

namespace Iris2D {
	class Rect;
	class ClearRectShaderGL : public ShaderGL {
	public:
		static ClearRectShaderGL* Instance();
	public:
		bool Initialize();
		void SetRectLocation(const Rect* pLocation);
		void SetProjectionMatrix(const glm::mat4& mtProjection);

	private:
		ClearRectShaderGL() = default;
		~ClearRectShaderGL() = default;
	};

}

#endif // _H_CLEARRECT_SHADER_GL_

