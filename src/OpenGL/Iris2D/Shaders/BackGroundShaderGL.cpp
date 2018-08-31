#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/Shaders/BackGroundShaderGL.h"

namespace Iris2D {
	
	BackGroundShaderGL* BackGroundShaderGL::Instance() {
		static BackGroundShaderGL fontshader;
		return &fontshader;
	}
	bool BackGroundShaderGL::Initialize()
	{
		return ShaderGL::Initialize("shaders/GLSL/backgroud_vertex_shader.vert", "shaders/GLSL/backgroud_fragment_shader.frag");

	}

}