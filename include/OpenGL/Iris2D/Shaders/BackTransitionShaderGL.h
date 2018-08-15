#ifndef	_H_BACK_TRANSITION_SHADER_GL_
#define _H_BACK_TRANSITION_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"

namespace Iris2D {
	class BackTransitionShaderGL : public ShaderGL {
	public:
		static BackTransitionShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectionMatrix(const glm::mat4& mt4Projection);
		void SetBrightness(float fBrightness);

	private:
		BackTransitionShaderGL() = default;
		~BackTransitionShaderGL() = default;
	};
}

#endif // _H_BACK_TRANSITION_SHADER_GL_