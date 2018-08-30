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
		return ShaderGL::Initialize("shaders/GLSL/clear_rect_shader.vert", "shaders/GLSL/clear_rect_shader.frag");
	}

	//£¨top,left,width,height£©
	void ClearRectShaderGL::SetRectLocation(const Rect*  pLocation) {
		SetFloat4("fillLocation", pLocation->GetLeft(), pLocation->GetTop(), pLocation->GetRight(), pLocation->GetBottom());
	}

	void ClearRectShaderGL::SetProjectionMatrix(const glm::mat4& mtProjection) {
		SetMatrix("projectionMat", mtProjection);
	}

	GLuint ClearRectShaderGL::BindBufferData(float fWidth, float fHeigh) {
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