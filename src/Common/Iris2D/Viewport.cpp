#include "Common/Iris2D/Viewport.h"

#ifdef _WIN32
#include "DirectX/Iris2D/ViewportDX.h"
#endif // !_WIN32

namespace Iris2D {
	Viewport::Viewport(IViewport* pViewport) : Proxy(pViewport) {}

	Viewport * Viewport::Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		IViewport* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = ViewportDX::Create(fX, fY, nWidth, nHeight);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Viewport(pProxied);
	}

	ViewportDX * Viewport::Create(const Rect * pRect, IR_PARAM_RESULT_CT) {
		IViewport* pProxied = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			auto pTmp = ViewportDX::Create(pRect, IR_PARAM);
			pTmp->SetProxy(this);
			pProxied = pTmp;
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			break;
		default:
			break;
		}

		return new Viewport(pProxied);
	}

	void Viewport::Release(Viewport *& pViewport) {
		auto pProxied = pViewport->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			ViewportDX::Release(static_cast<ViewportDX*>(pProxied));
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

	static void Viewport::ForceRelease(Viewport*& pViewport) {
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
		return m_pProxied->GetSrcRect()
	}

	void Viewport::SetTone(Tone *& pTone) {
		m_pProxied->SetTone(pTone);
	}

	Tone * Viewport::GetTone() const {
		return m_pProxied->GetTone();
	}
}
