#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/Shaders/FillRectshaderGL.h"
#include "OpenGL/OpenGLUtil/BackBufferVertexGL.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"


namespace Iris2D {
	
		FillRectShaderGL* FillRectShaderGL::Instance() {
			static FillRectShaderGL fillrectshader;
			return &fillrectshader;
		}

		bool FillRectShaderGL::Initialize() {
			return ShaderGL::Initialize("shaders/GLSL/fill_vertex_shader.vert", "shaders/GLSL/fill_fragment_shader.frag");
		}

		//£¨top,left,width,height£©
		void FillRectShaderGL::SetRectLocation(const Rect*  pRectLocation) {
			SetFloat4("fillLocation", pRectLocation->GetLeft(), pRectLocation->GetTop(), pRectLocation->GetRight(), pRectLocation->GetBottom());
		}
		
		void FillRectShaderGL::SetFillColor(const Color* pFillColor) {
			SetFloat4("fillColor", static_cast<float>(pFillColor->GetRed())/255.f , static_cast<float>(pFillColor->GetGreen())/255.f, static_cast<float>(pFillColor->GetBlue())/255.f, static_cast<float>(pFillColor->GetAlpha()) / 255.f);
		}

		void FillRectShaderGL::SetProjectionMatrix(const glm::mat4& mtProjection) {
			SetMatrix("projectionMat", mtProjection);
		}

		
}