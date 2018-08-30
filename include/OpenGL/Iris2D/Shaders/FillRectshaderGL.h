#ifndef _H_FILLRECT_SHADER_GL_
#define _H_FILLRECT_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

namespace Iris2D {
	class Color;
	class Rect;
	class ShaderGL;
	class FillRectShaderGL : public ShaderGL {
	public:
		static FillRectShaderGL* Instance();
	public:
		bool Initialize(); 
		void SetRectLocation(const Rect* rectLocation);
		void SetFillColor(const Color* fillColor);
		void SetProjectionMatrix(const glm::mat4& mtProjection);

		GLuint BindBufferData(float fWidth, float fHeigh);

	private:
		FillRectShaderGL() = default;
		~FillRectShaderGL() = default;
	};
	
}

#endif // _H_FILLRECT_SHADER_GL_

