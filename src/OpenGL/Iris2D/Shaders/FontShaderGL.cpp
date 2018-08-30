#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h"



namespace Iris2D {
	FontShaderGL* FontShaderGL::Instance() {
		static FontShaderGL fontshader;
		return &fontshader;
	}

	bool FontShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/font_shader.vert", "shaders/GLSL/font_shader.frag");
	}

	void FontShaderGL::SetFontColor(const Color & fontColor)
	{
		SetFloat4("textColor", static_cast<float>(fontColor.GetRed()) / 255.f, static_cast<float>(fontColor.GetGreen()) / 255.f, static_cast<float>(fontColor.GetBlue()) / 255.f, static_cast<float>(fontColor.GetAlpha()) / 255.f);

	}

	void FontShaderGL::SetProjectionMatrix(const glm::mat4 & mtProjection)
	{
		SetMatrix("projectionMat", mtProjection);
	}

	GLuint FontShaderGL::BindBufferData(const std::wstring & wstrText)
	{
		return 0;
	}




}
