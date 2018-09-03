#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h"



namespace Iris2D {
	FontShaderGL* FontShaderGL::Instance() {
		static FontShaderGL fontshader;
		return &fontshader;
	}

	bool FontShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/font_vertex_shader.vert", "shaders/GLSL/font_fragment_shader.frag");
	}

	void FontShaderGL::SetFontColor(const Color * fontColor)
	{
		SetFloat4("textColor", static_cast<float>(fontColor->GetRed()) / 255.f, static_cast<float>(fontColor->GetGreen()) / 255.f, static_cast<float>(fontColor->GetBlue()) / 255.f, static_cast<float>(fontColor->GetAlpha()) / 255.f);
	}

	void FontShaderGL::SetProjectionMatrix(const glm::mat4 & mtProjection)
	{
		SetMatrix("projectionMat", mtProjection);
	}

	void FontShaderGL::SetDestRect(const Rect * pDestRect, const unsigned int nDesTextureWidth, const unsigned int nDesTextureHeight)
	{
		SetFloat4("desRect", 2*(pDestRect->GetLeft() / nDesTextureWidth)-1, 2*(pDestRect->GetTop() / nDesTextureHeight)-1, 2*(pDestRect->GetRight() / nDesTextureWidth)-1, 2*(pDestRect->GetBottom() / nDesTextureHeight)-1);
	}



}
