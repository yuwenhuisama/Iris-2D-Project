#ifndef _H_VIEWPORT_SHADER_GL_
#define _H_VIEWPORT_SHADER_GL_

#include "ShaderGL.h"

namespace Iris2D {
	class ViewportShaderGL : public ShaderGL{
	public:
		static ViewportShaderGL* Instance();

	public:
		bool Initialize() override;

	};
}

#endif // !_H_VIEWPORT_SHADER_GL_
