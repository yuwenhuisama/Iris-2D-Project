#include "Common/Iris2D/Rect.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/RectGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/RectDX.h"
#endif // _WIN32


namespace Iris2D {
	Rect::Rect(IRect* pRect) : Proxy(pRect) {}

	Rect * Rect::Create(float fX, float fY, float fWidth, float fHeight) {
		Rect* pRect = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = RectDX::Create(fX, fY, fWidth, fHeight);
			pRect = new Rect(pTmp);
			pTmp->SetProxy(pRect);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = RectGL::Create(fX, fY, fWidth, fHeight);
			pRect = new Rect(pTmp);
			pTmp->SetProxy(pRect);
		}
			break;
		default:
			break;
		}

		return pRect;
	}

	Rect * Rect::Create2(float fLeft, float fTop, float fRight, float fBottom) {
		Rect* pRect = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = RectDX::Create2(fLeft, fTop, fRight, fBottom);
			pRect = new Rect(pTmp);
			pTmp->SetProxy(pRect);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = RectGL::Create2(fLeft, fTop, fRight, fBottom);
			pRect = new Rect(pTmp);
			pTmp->SetProxy(pRect);
		}
			break;
		default:
			break;
		}

		return pRect;
	}

	void Rect::Release(Rect *& pRect) {
		if (!pRect) {
			return;
		}

		auto pProxied = pRect->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			RectDX::Release(reinterpret_cast<RectDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			RectGL::Release(reinterpret_cast<RectGL*&>(pProxied));
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
		return m_pProxied->GetY();
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
		m_pProxied->SetTop(fTop);
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
