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
			return ShaderGL::Initialize("shaders/GLSL/fill_rect_shader.vert", "shaders/GLSL/fill_rect_shader.frag");
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

		GLuint FillRectShaderGL::BindBufferData(float fWidth, float fHeigh) {
			BackBufferVertexGL arrBuffers[] = {
			{ { fWidth,	fHeigh,	0.0f, 1.0f },{ 1.0f, 1.0f } },
			{ { fWidth,	0.0f,	0.0f, 1.0f },{ 1.0f, 0.0f } },
			{ { 0.0f,	0.0f,	0.0f, 1.0f },{ 0.0f, 0.0f } },
			{ { 0.0f,	fHeigh,	0.0f, 1.0f },{ 0.0f, 1.0f } },
			};
			unsigned int arrIndiecs[] = {
				0, 1, 3,
				1, 2, 3,
			};
			GLuint VAO, VBO, EBO;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(arrBuffers), arrBuffers, GL_STATIC_DRAW);

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndiecs), arrIndiecs, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(BackBufferVertexGL), reinterpret_cast<void*>(offsetof(BackBufferVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BackBufferVertexGL), reinterpret_cast<void*>(offsetof(BackBufferVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
			return VAO;
		}
}