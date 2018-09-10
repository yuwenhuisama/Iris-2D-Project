#include "Common/Iris2D/Sprites/SpriteStatic.h"
#include "Common/Iris2D/AppFactory.h"

#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"

#if _WIN32
#include "DirectX/Iris2D/SpriteDX.h"
#endif // _WIN32


namespace Iris2D {
	SpriteStatic::SpriteStatic(ISpriteStatic* pSprite) : Proxy(pSprite) {}

	SpriteStatic * SpriteStatic::Create(Viewport * pViewport) {
		SpriteStatic* pSprite = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			auto pTmp = SpriteDX::Create(pViewport);
			if (!pTmp) {
				return nullptr;
			}
			//pSprite = new SpriteStatic(pTmp);
			//pTmp->SetProxy(pSprite);
		}
			break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = SpriteStaticGL::Create(pViewport);
			if (!pTmp) {
				return nullptr;
			}
			pSprite = new SpriteStatic(pTmp);
			pTmp->SetProxy(pSprite);
		}
			break;
		default:
			break;
		}

		return pSprite;
	}

	void SpriteStatic::Release(SpriteStatic *& pSprite) {
		if (!pSprite) {
			return;
		}

		auto pProxied = pSprite->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			SpriteDX::Release(reinterpret_cast<SpriteDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			SpriteStaticGL::Release(reinterpret_cast<SpriteStaticGL*&>(pProxied));
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

	void SpriteStatic::ForceRelease(SpriteStatic*& pSprite) {
		delete pSprite;
		pSprite = nullptr;
	}

	void SpriteStatic::SetSrcRect(Rect *& pSrcRect) {
		m_pProxied->SetSrcRect(pSrcRect);
	}

	Rect * SpriteStatic::GetSrcRect() const {
		return m_pProxied->GetSrcRect();
	}

	ISprite* SpriteStatic::GetAbstractProxied() const {
		return m_pProxied;
	}
}
