#ifndef _H_CLEARRECT_SHADER_GL_
#define _H_CLEARRECT_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

#include "Common/Iris2D/Rect.h"




namespace Iris2D {


	class Rect;
	class ShaderGL;
	class ClearRectShaderGL : public ShaderGL {
	public:
		static ClearRectShaderGL* Instance();
	public:
		bool Initialize();
		void SetRectLocation(const Rect& rectLocation);
		void SetProjectionMatrix(const glm::mat4& mtProjection);
		GLuint BindBufferData(float fWidth, float fHeigh);

	private:
		ClearRectShaderGL() = default;
		~ClearRectShaderGL() = default;
	};

}

#endif // _H_CLEARRECT_SHADER_GL_

