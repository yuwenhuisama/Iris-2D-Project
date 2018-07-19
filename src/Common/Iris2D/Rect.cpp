#include "Common/Iris2D/Rect.h"

#ifdef _WIN32
#include "DirectX/Iris2D/RectDX.h"
#endif // _WIN32


namespace Iris2D {
	Rect::Rect(IRect* pRect) : Proxy(pRect) {}

	Rect * Rect::Create(float fX, float fY, float fWidth, float fHeight) {
		IRect* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = RectDX::Create(cRed, cGreen, cBlue, cAlpha);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Rect(pProxied);
	}

	Rect * Rect::Create2(float fLeft, float fTop, float fRight, float fBottom) {
		IRect* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = pProxied = RectDX::Create2(fLeft, fTop, fRight, fBottom);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Rect(pProxied);
	}

	void Rect::Release(Rect *& pRect) {
		auto pProxied = pRect->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			RectDX::Release(static_cast<RectDX*>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pRect;
			pRect = nullptr;
		}
	}

	void Rect::SetX(float fX) {
		m_pProxied->SetX(fX);
	}

	float Rect::GetX() const {
		return m_pProxied->GetX();
	}

	void Rect::SetY(float fY) {
		m_pProxied->SetY(fY);
	}

	float Rect::GetY() const {
		return m_pProxied->GetY()
	}

	void Rect::SetWidth(float fWidth) {
		m_pProxied->SetWidth(fWidth);
	}

	float Rect::GetWidth() const {
		return m_pProxied->GetWidth();
	}

	void Rect::SetHeight(float fHeight) {
		m_pProxied->SetHeight(fHeight);
	}

	float Rect::GetHeight() const {
		return m_pProxied->GetHeight();
	}

	void Rect::SetLeft(float fLeft) {
		m_pProxied->SetLeft(fLeft);
	}

	float Rect::GetLeft() const {
		return m_pProxied->GetLeft();
	}

	void Rect::SetTop(float fTop) {
		m_pProxied->SetTop(fLeft);
	}

	float Rect::GetTop() const {
		return m_pProxied->GetTop();
	}

	void Rect::SetRight(float fRight) {
		m_pProxied->SetRight(fRight);
	}

	float Rect::GetRight() const {
		return m_pProxied->GetRight();
	}

	void Rect::SetBottom(float fBottom) {
		m_pProxied->SetBottom(fBottom);
	}

	float Rect::GetBottom() const {
		return m_pProxied->GetBottom();
	}

	void Rect::Set(float fX, float fY, float fWidth, float fHeight) {
		m_pProxied->Set(fX, fY, fWidth, fHeight);
	}

	void Rect::Set2(float fLeft, float fTop, float fRight, float fBottom) {
		m_pProxied->Set2(fLeft, fTop, fRight, fBottom);
	}
};