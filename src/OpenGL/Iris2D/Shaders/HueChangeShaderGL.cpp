#include "OpenGL/Iris2D/Shaders/HueChangeShaderGL.h"
namespace Iris2D {

	HueChangeShaderGL * HueChangeShaderGL::Instance() {
		static HueChangeShaderGL shader;
		return &shader;
	}

	bool HueChangeShaderGL::Initialize()
	{
		return ShaderGL::Initialize("shaders/GLSL/hue_vertex_shader.vert", "shaders/GLSL/hue_fragment_shader.frag");
	}

	void HueChangeShaderGL::SetHue(int nHue)
	{
		SetInt("hsv_h", nHue);
	}

	


}