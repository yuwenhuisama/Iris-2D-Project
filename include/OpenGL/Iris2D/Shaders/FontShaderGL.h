#ifndef _H_FONT_SHADER_GL_
#define _H_FONT_SHADER_GL_

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"
#include "Common/Iris2D/Color.h"
#include "Common/Iris2D/Rect.h"
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Iris2D {
	class Color;
	class Rect;
	class ShaderGL;
	class FontShaderGL : public ShaderGL {
	public:
		static FontShaderGL* Instance();
	public:
		bool Initialize();

		void SetFontColor(const  Color * fontColor);
		void SetProjectionMatrix(const glm::mat4& mtProjection);
		void SetDestRect(const Rect * pDestRect,const unsigned int nDesTextureWidth,const unsigned int nDesTextureHeight);

	private:
		FontShaderGL() = default;
		~FontShaderGL() = default;
	};

}

#endif // _H_FONT_SHADER_GL_

