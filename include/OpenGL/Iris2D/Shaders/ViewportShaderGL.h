#ifndef _H_VIEWPORT_SHADER_GL_
#define _H_VIEWPORT_SHADER_GL_

#include "ShaderGL.h"

namespace Iris2D {
	class ViewportShaderGL : public ShaderGL{
	public:
		static ViewportShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectMatrix(const glm::mat4& mtMat);
		void SetModelMatrix(const glm::mat4& mtMat);

	private:
		ViewportShaderGL() = default;
		~ViewportShaderGL() = default;
	};
}

#endif // !_H_VIEWPORT_SHADER_GL_
