#include "Common/Iris2D/Sprites/SpriteIndexed.h"
#include "Common/Iris2D/AppFactory.h"
#include "OpenGL/Iris2D/Sprites/SpriteIndexedGL.h"

namespace Iris2D {

	SpriteIndexed* SpriteIndexed::Create(const std::vector<Rect*>& vcAreas, Viewport* pViewport) {
		SpriteIndexed* pSprite = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			//auto pTmp = SpriteDX::Create(pViewport);
			//if (!pTmp) {
			//	return nullptr;
			//}
			//pSprite = new SpriteStatic(pTmp);
			//pTmp->SetProxy(pSprite);
		}
		break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = SpriteIndexedGL::Create(vcAreas, pViewport);
			if (!pTmp) {
				return nullptr;
			}
			pSprite = new SpriteIndexed(pTmp);
			pTmp->SetProxy(pSprite);
		}
		break;
		default:
			break;
		}

		return pSprite;
	}

	SpriteIndexed* SpriteIndexed::Create(unsigned nRow, unsigned nColumn, Viewport* pViewport) {
		SpriteIndexed* pSprite = nullptr;
		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
		{
			//auto pTmp = SpriteDX::Create(pViewport);
			//if (!pTmp) {
			//	return nullptr;
			//}
			//pSprite = new SpriteStatic(pTmp);
			//pTmp->SetProxy(pSprite);
		}
		break;
#endif // _WIN32
		case ApiType::OpenGL:
		{
			auto pTmp = SpriteIndexedGL::Create(nRow, nColumn, pViewport);
			if (!pTmp) {
				return nullptr;
			}
			pSprite = new SpriteIndexed(pTmp);
			pTmp->SetProxy(pSprite);
		}
		break;
		default:
			break;
		}

		return pSprite;
	}

	void SpriteIndexed::Release(SpriteIndexed*& pSprite) {
		if (!pSprite) {
			return;
		}

		auto pProxied = pSprite->GetProxied();

		switch (AppFactory::GetApiType()) {
#ifdef _WIN32
		case ApiType::DirectX:
			//SpriteDX::Release(reinterpret_cast<SpriteDX*&>(pProxied));
			break;
#endif // _WIN32
		case ApiType::OpenGL:
			SpriteIndexedGL::Release(reinterpret_cast<SpriteIndexedGL*&>(pProxied));
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

	void SpriteIndexed::SetIndex(unsigned nIndex) {
		m_pProxied->SetIndex(nIndex);
	}

	unsigned SpriteIndexed::GetIndex() const {
		return m_pProxied->GetIndex();
	}

	ISprite* SpriteIndexed::GetAbstractProxied() const {
		return  m_pProxied;
	}

	SpriteIndexed::SpriteIndexed(ISpriteIndexed* pSprite): Proxy(pSprite) {
	}
}
