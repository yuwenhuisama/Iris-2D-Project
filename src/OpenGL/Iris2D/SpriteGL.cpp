#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/SpriteGL.h"
#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Viewport.h"
#include <glm/glm.hpp>

#include "Common/Util/ProxyConvert.h"

#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"

namespace Iris2D {
	SpriteGL * SpriteGL::Create(Viewport * pViewport) {

		auto pSprite = new SpriteGL();
		return pSprite;
	}

	void SpriteGL::Release(SpriteGL *& pSprite) {
		if (pSprite) {
			delete pSprite;
			pSprite = nullptr;
		}
	}

	void SpriteGL::ForceRelease(SpriteGL *& pSprite) {
	}

	void SpriteGL::SetBitmap(Bitmap *& pBitmap) {
		if (m_pBitmap) {
			delete m_pBitmap;
		}

		if (!pBitmap || pBitmap == m_pBitmap) {
			return;
		}

		if (!CreateVertexBuffer()) {
			return;
		}

		GetProxied<BitmapGL*>(pBitmap)->IncreamRefCount();

		m_pBitmap = pBitmap;
	}

	Bitmap * SpriteGL::GetBitmap() const {
		return m_pBitmap;
	}

	void SpriteGL::SetX(float fX) {
	}

	float SpriteGL::GetX() const {
		return 0.0f;
	}

	void SpriteGL::SetY(float fY) {
	}

	float SpriteGL::GetY() const {
		return 0.0f;
	}

	void SpriteGL::SetZ(float fZ) {
	}

	float SpriteGL::GetZ() const {
		return 0.0f;
	}

	void SpriteGL::SetAngle(float fAngle) {
	}

	float SpriteGL::GetAngle() const {
		return 0.0f;
	}

	void SpriteGL::SetZoomX(float fZoomX) {
	}

	float SpriteGL::GetZoomX() const {
		return 0.0f;
	}

	void SpriteGL::SetZoomY(float fZoomY) {
	}

	float SpriteGL::GetZoomY() const {
		return 0.0f;
	}

	void SpriteGL::SetOX(float fOX) {
	}

	float SpriteGL::GetOX() {
		return 0.0f;
	}

	void SpriteGL::SetOY(float fOY) {
	}

	float SpriteGL::GetOY() {
		return 0.0f;
	}

	void SpriteGL::SetMirror(bool bMirror) {
	}

	bool SpriteGL::GetMirror() {
		return false;
	}

	void SpriteGL::SetVisible(bool bVisible) {
	}

	bool SpriteGL::GetVisible() {
		return false;
	}

	void SpriteGL::SetOpacity(float fOpacity) {
	}

	float SpriteGL::GetOpacity() {
		return 0.0f;
	}

	void SpriteGL::SetSrcRect(Rect *& pSrcRect) {
	}

	Rect * SpriteGL::GetSrcRect() const {
		return nullptr;
	}

	void SpriteGL::SetTone(Tone *& pTone) {
	}

	Tone * SpriteGL::GetTone() const {
		return nullptr;
	}

	void SpriteGL::Update() {
	}

	bool SpriteGL::CreateVertexBuffer() {
		auto pBitmap = GetProxied<BitmapGL*>(m_pBitmap);

		auto nWidth = pBitmap->GetWidth();
		auto nHeight = pBitmap->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ glm::vec4(static_cast<float>(nWidth), 0.0f,						 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
			{ glm::vec4(static_cast<float>(nWidth), static_cast<float>(nHeight), 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec4(0.0f,					    static_cast<float>(nHeight), 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
			{ glm::vec4(0.0f,					    0.0f,						 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		};

		static unsigned int arrIndiecs[] = {
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

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), (void*)offsetof(SpriteVertexGL, m_v4Position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), (void*)offsetof(SpriteVertexGL, m_v2Texture));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_nVAO = VAO;
		m_nVBO = VBO;
		m_nEBO = EBO;

		return true;
	}

	bool SpriteGL::Render() {
		return true;
	}
}
