#ifndef _H_VIEWPORT_SHADER_GL_
#define _H_VIEWPORT_SHADER_GL_

#include "ShaderGL.h"

namespace Iris2D {
	class ViewportShaderGL : public ShaderGL{
	public:
		static ViewportShaderGL* Instance();

	public:
		bool Initialize();
		void SetProjectionMatrix(const glm::mat4& mtMat);
		void SetModelMatrix(const glm::mat4& mtMat);
		void SetOrgPosition(const glm::vec2& v2OrgPosition);
		void SetRect(const glm::vec4& v4Rect);
		void SetTone(const glm::ivec4& v4Tone);

	private:
		ViewportShaderGL() = default;
		~ViewportShaderGL() = default;
	};
}

#endif // !_H_VIEWPORT_SHADER_GL_
