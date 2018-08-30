#include "OpenGL/Iris2D/Shaders/CopyRectShaderGL.h"
#include "Common/Iris2D/Rect.h"


namespace Iris2D {

	CopyRectShaderGL* CopyRectShaderGL::Instance() {
		static CopyRectShaderGL copyRectShader;
		return &copyRectShader;
	}

	bool CopyRectShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/copy_rect_shader.vert", "shaders/GLSL/copy_rect_shader.frag");
	}

	void CopyRectShaderGL::SetDesRect(const Rect* pDesRect) {
		SetFloat4("desRect", pDesRect->GetLeft(), pDesRect->GetTop(), pDesRect->GetRight(), pDesRect->GetBottom());
	}
	void CopyRectShaderGL::SetSrcTexCoordRect(const Rect* pSrcRect, const TextureGL* pSrcTexture) {

		const float fSrcTexcoodLeft = static_cast<float>(pSrcRect->GetLeft()) / static_cast<float>(pSrcTexture->GetWidth());
		const float fSrcTexcoodTop =1 - static_cast<float>(pSrcRect->GetTop()) / static_cast<float>(pSrcTexture->GetHeight());
		const float fSrcTexcoodRight = static_cast<float>(pSrcRect->GetRight()) / static_cast<float>(pSrcTexture->GetWidth());
		const float fSrcTexcoodBottom =1 - static_cast<float>(pSrcRect->GetBottom()) / static_cast<float>(pSrcTexture->GetHeight());

		SetFloat4("srcRect", fSrcTexcoodLeft, fSrcTexcoodTop, fSrcTexcoodRight, fSrcTexcoodBottom);
	}

	void CopyRectShaderGL::SetSrcRect(const Rect* pSrcRect) {
		SetFloat4("srcRect", pSrcRect->GetLeft(), pSrcRect->GetTop(), pSrcRect->GetRight(), pSrcRect->GetBottom());
	}

	void CopyRectShaderGL::SetProjectionMatrix(const glm::mat4 & mtProjection) {
		SetMatrix("desOthoMat", mtProjection);
	}

	void CopyRectShaderGL::SetDesOthoMat(const glm::mat4 & mtProjection) {
		SetMatrix("desOthoMat", mtProjection);
	}

	void CopyRectShaderGL::SetOpacity(float opacity) {
		SetFloat("opacity", opacity / 255.0f);
	}
	GLuint CopyRectShaderGL::BindBufferData(float fWidth,float fHeight) {
		float arrs[] = {
			//destPoint			 //DestSTtexcood	
			fWidth,	fHeight	,	1.0f,1.0f,
			fWidth,	0.0f,   	1.0f,0.0f,
			0.0f ,	0.0f,		0.0f,0.0f,
			0.0f ,	fHeight	,	0.0f,1.0f
		};
		unsigned int arrIndiecs[] = {
			0, 1, 3,
			1, 2, 3,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(arrs), arrs, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndiecs), arrIndiecs, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

		return VAO;
	
	}
}