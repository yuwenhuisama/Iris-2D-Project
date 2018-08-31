#include "Common/Util/DebugUtil.h"
#include "OpenGL/OpenGLUtil/BackBufferVertexGL.h"
#include "OpenGL/Iris2D/Shaders/ClearRectShaderGL.h"
#include "Common/Iris2D/Rect.h"

namespace Iris2D {
	ClearRectShaderGL* ClearRectShaderGL::Instance() {
		static ClearRectShaderGL clearRectshader;
		return &clearRectshader;
	}

	bool ClearRectShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/clear_vertex_shader.vert", "shaders/GLSL/clear_fragment_shader.frag");
	}

	//£¨top,left,width,height£©
	void ClearRectShaderGL::SetRectLocation(const Rect*  pLocation) {
		SetFloat4("fillLocation", pLocation->GetLeft(), pLocation->GetTop(), pLocation->GetRight(), pLocation->GetBottom());
	}

	void ClearRectShaderGL::SetProjectionMatrix(const glm::mat4& mtProjection) {
		SetMatrix("projectionMat", mtProjection);
	}



}