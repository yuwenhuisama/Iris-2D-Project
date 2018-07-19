#include "Common/Iris2D/Sprite.h"

#if _WIN32
#include "DirectX/Iris2D/SpriteDX.h"
#endif // _WIN32


namespace Iris2D {
	Sprite::Sprite(ISprite* pSprite) : Proxy(pSprite) {}

	Sprite * Sprite::Create(Viewport * pViewport) {
		ISprite* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = SpriteDX::Create(pViewport);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Sprite(pProxied);
	}

	void Sprite::Release(Sprite *& pSprite) {
		auto pProxied = pSprite->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			SpriteDX::Release(static_cast<SpriteDX*>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pSprite;
			pSprite = nullptr;
		}
	}

	static void Sprite::ForceRelease(Sprite*& pSprite) {
		delete pSprite;
		pSprite = nullptr;
	}

	void Sprite::SetBitmap(Bitmap *& pBitmap) {
		m_pProxied->SetBitmap(pBitmap);
	}

	Bitmap * Sprite::GetBitmap() const {
		return m_pProxied->GetBitmap();
	}

	void Sprite::SetX(float fX) {
		m_pProxied->SetX(fX);
	}

	float Sprite::GetX() const {
		return m_pProxied->GetX();
	}

	void Sprite::SetY(float fY) {
		m_pProxied->SetY(fY);
	}

	float Sprite::GetY() const {
		return m_pProxied->GetY();
	}

	void Sprite::SetZ(float fZ) {
		m_pProxied->SetZ(fZ);
	}

	float Sprite::GetZ() const {
		return m_pProxied->GetZ();
	}

	void Sprite::SetAngle(float fAngle) {
		m_pProxied->SetAngle(fAngle);
	}

	float Sprite::GetAngle() const {
		return m_pProxied->GetAngle();
	}

	void Sprite::SetZoomX(float fZoomX) {
		m_pProxied->SetZoomX(fZoomX);
	}

	float Sprite::GetZoomX() const {
		return m_pProxied->GetZoomX();
	}

	void Sprite::SetZoomY(float fZoomY) {
		m_pProxied->SetZoomY(fZoomY);
	}

	float Sprite::GetZoomY() const {
		return m_pProxied->GetZoomY();
	}

	void Sprite::SetOX(float fOX) {
		m_pProxied->SetOX(fOX);
	}

	float Sprite::GetOX() {
		return m_pProxied->GetOX();
	}

	void Sprite::SetOY(float fOY) {
		m_pProxied->SetOY(fOY);
	}

	float Sprite::GetOY() {
		return m_pProxied->GetOY();
	}

	void Sprite::SetMirror(bool bMirror) {
		m_pProxied->SetMirror(bMirror);
	}

	bool Sprite::GetMirror() {
		return m_pProxied->GetMirror();
	}

	void Sprite::SetVisible(bool bVisible) {
		m_pProxied->SetVisible(bVisible);
	}

	bool Sprite::GetVisible() {
		return m_pProxied->GetVisible();
	}

	void Sprite::SetOpacity(float fOpacity) {
		m_pProxied->SetOpacity(fOpacity);
	}

	float Sprite::GetOpacity() {
		return m_pProxied->GetOpacity();
	}

	void Sprite::SetSrcRect(Rect *& pSrcRect) {
		m_pProxied->SetSrcRect(pSrcRect);
	}

	Rect * Sprite::GetSrcRect() const {
		return m_pProxied->GetSrcRect();
	}

	void Sprite::SetTone(Tone *& pTone) {
		m_pProxied->SetTone(pTone);
	}

	Tone * Sprite::GetTone() const {
		return m_pProxied->GetTone();
	}

	void Sprite::Update() {
		m_pProxied->Update();
	}
}
