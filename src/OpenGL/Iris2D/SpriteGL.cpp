#include "OpenGL/Common.h"
#include "OpenGL/Iris2D/SpriteGL.h"
#include "OpenGL/Iris2D/BitmapGL.h"
#include "Common/Iris2D/Viewport.h"
#include "Common/Iris2D/Sprite.h"
#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Common/Iris2D/Bitmap.h"
#include "Common/Util/ProxyConvert.h"

#include "OpenGL/OpenGLUtil/SpriteVertexGL.h"

#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"

#include "OpenGL/Iris2D/GraphicsGL.h"
#include "OpenGL/Iris2D/ViewportGL.h"

#include "OpenGL/OpenGLUtil/TextureGL.h"

#include "Common/Util/Util.h"

#include "OpenGL/Iris2D/ColorGL.h"
#include "OpenGL/Iris2D/RectGL.h"

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
		if (pBitmap == m_pBitmap) {
			return;
		}

		Bitmap::Release(m_pBitmap);

		if (!pBitmap) {
			m_pBitmap = nullptr;
			return;
		}

		GetProxied<BitmapGL*>(pBitmap)->IncreamRefCount();

		m_pBitmap = pBitmap;

		CreateVertexBuffer();
	}

	Bitmap * SpriteGL::GetBitmap() const {
		return m_pBitmap;
	}

	void SpriteGL::SetX(float fX) {
		// m_v3Position.x = fX;
		m_dcDirtyChecker.Assign(m_v3Position.x, fX, m_hTranslate);
	}

	float SpriteGL::GetX() const {
		return m_v3Position.x;
	}

	void SpriteGL::SetY(float fY) {
		// m_v3Position.y = fY;
		m_dcDirtyChecker.Assign(m_v3Position.y, fY, m_hTranslate);
	}

	float SpriteGL::GetY() const {
		return m_v3Position.y;
	}

	void SpriteGL::SetZ(float fZ) {
		// m_v3Position.z = fZ;
		m_dcDirtyChecker.Assign(m_v3Position.z, fZ, m_hTranslate);
	}

	float SpriteGL::GetZ() const {
		return m_v3Position.z;
	}

	void SpriteGL::SetAngle(float fAngle) {
		// m_fAngle = fAngle;
		m_dcDirtyChecker.Assign(m_fAngle, fAngle, m_hRotate);
	}

	float SpriteGL::GetAngle() const {
		return m_fAngle;
	}

	void SpriteGL::SetZoomX(float fZoomX) {
		//m_v2Zoom.x = fZoomX;
		m_dcDirtyChecker.Assign(m_v2Zoom.x, fZoomX, m_hZoom);
	}

	float SpriteGL::GetZoomX() const {
		return m_v2Zoom.x;
	}

	void SpriteGL::SetZoomY(float fZoomY) {
		//m_v2Zoom.y = fZoomY;
		m_dcDirtyChecker.Assign(m_v2Zoom.y, fZoomY, m_hZoom);
	}

	float SpriteGL::GetZoomY() const {
		return m_v2Zoom.y;
	}

	void SpriteGL::SetOX(float fOX) {
		//m_v2OrgPosition.x = fOX;
		m_dcDirtyChecker.Assign(m_svbfBuffer.m_v2OrgPosition.x, fOX, m_hOrgPos);
	}

	float SpriteGL::GetOX() {
		return m_svbfBuffer.m_v2OrgPosition.x;
	}

	void SpriteGL::SetOY(float fOY) {
		// m_v2OrgPosition.y = fOY;
		m_dcDirtyChecker.Assign(m_svbfBuffer.m_v2OrgPosition.y, fOY, m_hOrgPos);
	}

	float SpriteGL::GetOY() {
		return m_svbfBuffer.m_v2OrgPosition.y;
	}

	void SpriteGL::SetMirror(bool bMirror) {
		// m_bMirror = bMirror;
		m_dcDirtyChecker.Assign(m_bMirror, bMirror, m_hMirror);
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
		// m_f32Opacity = fOpacity;
		fOpacity = clip(fOpacity, 0.0f, 1.0f);
		m_dcDirtyChecker.Assign(m_fOpacity, fOpacity, m_hOpacity);
	}

	float SpriteGL::GetOpacity() {
		return m_fOpacity;
	}

	void SpriteGL::SetSrcRect(Rect *& pSrcRect) {
		if (pSrcRect == m_pSrcRect) {
			return;
		}

		Rect::Release(m_pSrcRect);

		if (!pSrcRect) {
			m_pSrcRect = nullptr;
			return;
		}

		GetProxied<RectGL*>(pSrcRect)->IncreamRefCount();

		m_pSrcRect = pSrcRect;
	}

	Rect * SpriteGL::GetSrcRect() const {
		return m_pSrcRect;
	}

	void SpriteGL::SetTone(Tone *& pTone) {
		if (pTone == m_pTone) {
			return;
		}

		Tone::Release(m_pTone);

		if (!pTone) {
			m_pTone = nullptr;
			return;
		}

		GetProxied<ToneGL*>(pTone)->IncreamRefCount();

		m_pTone = pTone;
	}

	Tone * SpriteGL::GetTone() const {
		return m_pTone;
	}

	void SpriteGL::Update() {
	}

	bool SpriteGL::CreateVertexBuffer() {
		const auto pBitmap = GetProxied<BitmapGL*>(m_pBitmap);

		const auto nWidth = pBitmap->GetWidth();
		const auto nHeight = pBitmap->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f },{ 1.0f, 1.0f } },
			{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f },{ 1.0f, 0.0f } },
			{ { 0.0f,					     0.0f,						   0.0f, 1.0f },{ 0.0f, 0.0f } },
			{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f },{ 0.0f, 1.0f } },
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

		if (!m_bVisible || !m_pBitmap || m_fOpacity == 0.0f) {
			return true;
		}

		static auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(GraphicsGL::Instance()->GetWidth()), static_cast<float>(GraphicsGL::Instance()->GetHeight()), 0.0f, -1.0f, 1.0f);

		auto pShader = SpriteShaderGL::Instance();

		m_dcDirtyChecker.DoIfDirty(m_hTranslate, [&]() -> void {
			m_svbfBuffer.m_mt4Translate = glm::translate(glm::mat4{ 1.0f, }, m_v3Position);
		});
		
		m_dcDirtyChecker.DoIfDirty(m_hRotate, [&]() -> void {
			m_svbfBuffer.m_mtRotation = glm::rotate(glm::mat4{ 1.0f }, m_fAngle * glm::pi<float>() / 180.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hZoom, [&]() -> void {
			m_svbfBuffer.m_mtZoom = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ m_v2Zoom.x, m_v2Zoom.y, 1.0f });
		});

		m_dcDirtyChecker.DoIfDirty(m_hOpacity, [&]() -> void {
			m_svbfBuffer.m_f32Opacity = m_fOpacity;
		});

		m_dcDirtyChecker.DoIfDirty(m_hMirror, [&]() -> void {
			m_svbfBuffer.m_i32Mirror = m_bMirror ? 1 : 0;
		});

		if (m_pSrcRect && GetProxied<RectGL*>(m_pSrcRect)->Modified()) {
			const auto fLeft = m_pSrcRect->GetLeft() / m_pBitmap->GetWidth();
			const auto fTop = m_pSrcRect->GetTop() / m_pBitmap->GetHeight();
			const auto fRight = m_pSrcRect->GetRight() / m_pBitmap->GetWidth();
			const auto fBottom = m_pSrcRect->GetBottom() / m_pBitmap->GetHeight();

			m_svbfBuffer.m_v4Rect = {
				clip(fLeft, 0.0f, 1.0f),
				clip(fTop, 0.0f, 1.0f),
				clip(fRight, 0.0f, 1.0f),
				clip(fBottom, 0.0f, 1.0f),
			};

			GetProxied<RectGL*>(m_pSrcRect)->ModifyDone();
		} else if (!m_pSrcRect){
			m_svbfBuffer.m_v4Rect = { 0.0f, 0.0f, 1.0f, 1.0f };
		}

		if (m_pTone && GetProxied<ToneGL*>(m_pTone)->Modified()) {

			m_svbfBuffer.m_v4Tone = {
				m_pTone->GetRed(),
				m_pTone->GetGreen(),
				m_pTone->GetBlue(),
				m_pTone->GetAlpha(),
			};

			GetProxied<ToneGL*>(m_pTone)->ModifyDone();
		} else if (!m_pTone) {
			m_svbfBuffer.m_v4Tone = { 0, 0, 0, 0 };
		}

		//TODO: Optimize for dirty check
		pShader->SetProjectionMatrix(c_mt4Projection);
		pShader->SetTranslationMatrix(m_svbfBuffer.m_mt4Translate);
		pShader->SetRotationMatrix(m_svbfBuffer.m_mtRotation);
		pShader->SetZoomMatrix(m_svbfBuffer.m_mtZoom);
		pShader->SetOpacity(m_svbfBuffer.m_f32Opacity);
		pShader->SetMirror(m_svbfBuffer.m_i32Mirror);
		pShader->SetOrgPosition(m_svbfBuffer.m_v2OrgPosition);
		pShader->SetRect(m_svbfBuffer.m_v4Rect);
		pShader->SetTone(m_svbfBuffer.m_v4Tone);

		GetProxied<BitmapGL*>(m_pBitmap)->GetTexture()->UseTexture();

		glBindVertexArray(m_nVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		return true;
	}

	SpriteGL::SpriteGL() {
		m_hTranslate = m_dcDirtyChecker.Register();
		m_hZoom = m_dcDirtyChecker.Register();
		m_hOrgPos = m_dcDirtyChecker.Register();
		m_hRotate = m_dcDirtyChecker.Register();
		m_hMirror = m_dcDirtyChecker.Register();
		m_hOpacity = m_dcDirtyChecker.Register();
	}

	SpriteGL::~SpriteGL() {
		Bitmap::Release(m_pBitmap);
		Rect::Release(m_pSrcRect);
		Tone::Release(m_pTone);
	}
}
