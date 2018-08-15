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
		void SetBrightness(float fBrightness);
		void SetFadeInfo(const glm::vec2& v2FadInfo);

	private:
		BackShaderGL() = default;
		~BackShaderGL() = default;
	};
}

#endif // _H_BACK_SHADER_GL_
