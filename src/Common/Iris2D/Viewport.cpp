#include "Common/Iris2D/Viewport.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/ViewportGL.h"

#ifdef _WIN32
#include "DirectX/Iris2D/ViewportDX.h"
#endif // !_WIN32

namespace Iris2D {
	Viewport::Viewport(IViewport* pViewport) : Proxy(pViewport) {}

	Viewport * Viewport::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight) {
		Viewport* pViewport = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = ViewportDX::Create(fX, fY, nWidth, nHeight);
			pViewport = new Viewport(pTmp);
			pTmp->SetProxy(pViewport);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = ViewportGL::Create(fX, fY, nWidth, nHeight);
			pViewport = new Viewport(pTmp);
			pTmp->SetProxy(pViewport);
		}
			break;
		default:
			break;
		}

		return pViewport;
	}

	Viewport * Viewport::Create(const Rect * pRect) {
		Viewport* pViewport = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = ViewportDX::Create(pRect);
			pViewport = new Viewport(pTmp);
			pTmp->SetProxy(pViewport);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = ViewportGL::Create(pRect, IR_PARAM);
			pViewport = new Viewport(pTmp);
			pTmp->SetProxy(pViewport);
		}
			break;
		default:
			break;
		}

		return pViewport;
	}

	void Viewport::Release(Viewport *& pViewport) {
		if (!pViewport) {
			return;
		}

		auto pProxied = pViewport->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			ViewportDX::Release(reinterpret_cast<ViewportDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			ViewportGL::Release(reinterpret_cast<ViewportGL*&>(pProxied));
			break;
		default:
			break;
		}

		// Delete proxy object when proxied object has been released.
		if (!pProxied) {
			delete pViewport;
			pViewport = nullptr;
		}
	}

	void Viewport::ForceRelease(Viewport*& pViewport) {
		delete pViewport;
		pViewport = nullptr;
	}

	void Viewport::SetOX(float fOX) {
		m_pProxied->SetOX(fOX);
	}

	float Viewport::GetOX() const {
		return m_pProxied->GetOX();
	}

	void Viewport::SetOY(float fOY) {
		m_pProxied->SetOY(fOY);
	}

	float Viewport::GetOY() const {
		return m_pProxied->GetOY();
	}

	void Viewport::SetSrcRect(Rect *& pSrcRect) {
		m_pProxied->SetSrcRect(pSrcRect);
	}

	Rect * Viewport::GetSrcRect() const {
		return m_pProxied->GetSrcRect();
	}

	void Viewport::SetTone(Tone *& pTone) {
		m_pProxied->SetTone(pTone);
	}

	Tone * Viewport::GetTone() const {
		return m_pProxied->GetTone();
	}

	void Viewport::SetZ(float fZ) {
		m_pProxied->SetZ(fZ);
	}

	float Viewport::GetZ() {
		return m_pProxied->GetZ();
	}

	unsigned int Viewport::GetWidth() const {
		return m_pProxied->GetWidth();
	}

	unsigned int Viewport::GetHeight() const {
		return m_pProxied->GetHeight();
	}
}
