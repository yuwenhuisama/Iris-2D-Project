#ifndef _H_COPYRECT_SHADER_GL_
#define _H_COPYRECT_SHADER_GL_
#include"OpenGL/Iris2D/Shaders/ShaderGL.h"
#include"Common/Iris2D/Rect.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
namespace Iris2D {

	class CopyRectShaderGL : public ShaderGL {
	public:
		static CopyRectShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectionMatrix(const glm::mat4& mtProjection);
		void SetDesOthoMat(const glm::mat4 & mtProjection);
		void SetDesRect(const Rect & fillRect);
		void SetSrcTexCoordRect(const Rect & srcRect, TextureGL *psrcTextur);
		void SetSrcRect(const Rect & srcRect);
		void SetOpacity(float opacity);

		GLuint BindBufferData(float fWidth, float fHeight);


	private:
		CopyRectShaderGL() = default;
		~CopyRectShaderGL() = default;
	};



}
#endif // _H_COPYRECT_SHADER_GL_
