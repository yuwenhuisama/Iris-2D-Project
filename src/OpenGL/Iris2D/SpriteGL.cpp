#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/SpriteGL.h"
#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Viewport.h"
#include "Common/Iris2D/Sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Common/Iris2D/Bitmap.h"
#include "Common/Util/ProxyConvert.h"

#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"

#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/ViewportGL.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"

namespace Iris2D {
	SpriteGL * SpriteGL::Create(Viewport * pViewport) {
		auto pSprite = new SpriteGL();

		pSprite->m_pViewport = pViewport == nullptr ? ViewportGL::GetGlobalViewport() : pViewport;

		GetProxied<ViewportGL*>(pSprite->m_pViewport)->AddSprite(pSprite);

		return pSprite;
	}

	void SpriteGL::Release(SpriteGL *& pSprite) {
		if (pSprite) {
			GetProxied<ViewportGL*>(pSprite->m_pViewport)->RemoveSprite(pSprite);
			delete pSprite;
			pSprite = nullptr;
		}
	}

	void SpriteGL::ForceRelease(SpriteGL * pSprite) {
		auto pProxy = pSprite->GetProxy();;
		Sprite::ForceRelease(pProxy);
		delete pSprite;
	}

	void SpriteGL::SetBitmap(Bitmap *& pBitmap) {
		if (m_pBitmap) {
			Bitmap::Release(m_pBitmap);
		}

		if (!pBitmap || pBitmap == m_pBitmap) {
			return;
		}

		GetProxied<BitmapGL*>(pBitmap)->IncreamRefCount();

		m_pBitmap = pBitmap;

		if (!CreateVertexBuffer()) {
			return;
		}
	}

	Bitmap * SpriteGL::GetBitmap() const {
		return m_pBitmap;
	}

	void SpriteGL::SetX(float fX) {
		m_v3Position[0] = fX;
	}

	float SpriteGL::GetX() const {
		return m_v3Position[0];
	}

	void SpriteGL::SetY(float fY) {
		m_v3Position[1] = fY;
	}

	float SpriteGL::GetY() const {
		return m_v3Position[1];
	}

	void SpriteGL::SetZ(float fZ) {
		m_v3Position[2] = fZ;
	}

	float SpriteGL::GetZ() const {
		return m_v3Position[2];
	}

	void SpriteGL::SetAngle(float fAngle) {
		m_fAngle = fAngle;
	}

	float SpriteGL::GetAngle() const {
		return m_fAngle;
	}

	void SpriteGL::SetZoomX(float fZoomX) {
		m_v2Zoom[0] = fZoomX;
	}

	float SpriteGL::GetZoomX() const {
		return m_v2Zoom[0];
	}

	void SpriteGL::SetZoomY(float fZoomY) {
		m_v2Zoom[1] = fZoomY;
	}

	float SpriteGL::GetZoomY() const {
		return m_v2Zoom[1];
	}

	void SpriteGL::SetOX(float fOX) {
		m_v2OrgPosition[0] = fOX;
	}

	float SpriteGL::GetOX() {
		return m_v2OrgPosition[0];
	}

	void SpriteGL::SetOY(float fOY) {
		m_v2OrgPosition[1] = fOY;
	}

	float SpriteGL::GetOY() {
		return m_v2OrgPosition[1];
	}

	void SpriteGL::SetMirror(bool bMirror) {
		m_bMirror = bMirror;
	}

	bool SpriteGL::GetMirror() {
		return m_bMirror;
	}

	void SpriteGL::SetVisible(bool bVisible) {
		m_bVisible = bVisible;
	}

	bool SpriteGL::GetVisible() {
		return m_bVisible;
	}

	void SpriteGL::SetOpacity(float fOpacity) {
		m_fOpacity = fOpacity;
	}

	float SpriteGL::GetOpacity() {
		return m_fOpacity;
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
		const auto pBitmap = GetProxied<BitmapGL*>(m_pBitmap);

		const auto nWidth = pBitmap->GetWidth();
		const auto nHeight = pBitmap->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ {static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f}, {1.0f, 1.0f} },
			{ {static_cast<float>(nWidth),  0.0f,						 0.0f, 1.0f}, {1.0f, 0.0f} },
			{ {0.0f,					    0.0f,						 0.0f, 1.0f}, {0.0f, 0.0f} },
			{ {0.0f,					    static_cast<float>(nHeight), 0.0f, 1.0f}, {0.0f, 1.0f} },
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

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);
		glBindVertexArray(0);

		m_nVAO = VAO;
		m_nVBO = VBO;
		m_nEBO = EBO;

		return true;
	}

	bool SpriteGL::Render() {

		if (!m_bVisible || !m_pBitmap) {
			return true;
		}

		static auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GraphicsGL::Instance()->GetWidth()), static_cast<float>(GraphicsGL::Instance()->GetHeight()), 0.0f, -1.0f, 1.0f);

		auto pShader = SpriteShaderGL::Instance();

		m_svbfBuffer.m_mt4Translate = glm::translate(m_svbfBuffer.m_mt4Translate, m_v3Position);

		//TODO: Optimize for dirty check
		pShader->Use();
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetTranslationMatrix(m_svbfBuffer.m_mt4Translate);

		// pShader->Unuse();
		// GetProxied<BitmapGL*>(m_pBitmap)->GetTexture()->SaveToFile(L"temp/a.png");

		GetProxied<BitmapGL*>(m_pBitmap)->GetTexture()->UseTexture();

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		return true;
	}

	SpriteGL::~SpriteGL() {
		Bitmap::Release(m_pBitmap);
	}
}
