#include "OpenGL/Iris2D/Shaders/CopyRectShaderGL.h"
#include "Common/Iris2D/Rect.h"


namespace Iris2D {

	CopyRectShaderGL* CopyRectShaderGL::Instance() {
		static CopyRectShaderGL copyRectShader;
		return &copyRectShader;
	}

	bool CopyRectShaderGL::Initialize() {
		return ShaderGL::Initialize("shaders/GLSL/copy_vertex_shader.vert", "shaders/GLSL/copy_fragment_shader.frag");
	}

	void CopyRectShaderGL::SetDesRect(const Rect* pDesRect) {
		SetFloat4("desRect", pDesRect->GetLeft(), pDesRect->GetTop(), pDesRect->GetRight(), pDesRect->GetBottom());
	}
	void CopyRectShaderGL::SetSrcTexCoordRect(const Rect* pSrcRect, const float &fWidth, const float &fHeight){//const TextureGL* pSrcTexture) {

		const float fSrcTexcoodLeft = static_cast<float>(pSrcRect->GetLeft()) / fWidth;
		const float fSrcTexcoodTop =1 - static_cast<float>(pSrcRect->GetTop()) / fHeight;
		const float fSrcTexcoodRight = static_cast<float>(pSrcRect->GetRight()) / fWidth;
		const float fSrcTexcoodBottom =1 - static_cast<float>(pSrcRect->GetBottom()) / fHeight;

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
	
}