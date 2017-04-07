#include "Iris2D/IrisBitmap.h"
#include "Iris2D Util/IrisTexture.h"


namespace Iris2D
{
	IrisBitmap * IrisBitmap::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new IrisBitmap();

		pBitmap->m_pTexture = IrisTexture::Create(wstrFileName);
		if (pBitmap->m_pTexture == nullptr) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	IrisBitmap * IrisBitmap::Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
		auto pBitmap = new IrisBitmap();

		pBitmap->m_pTexture = IrisTexture::Create(nWidth, nHeight);
		if (pBitmap->m_pTexture == nullptr) {
			delete pBitmap;
			return nullptr;
		}

		return pBitmap;
	}

	void IrisBitmap::Release(IrisBitmap *& pBitmap)
	{
		delete pBitmap;
		pBitmap = nullptr;
	}

	IrisTexture * IrisBitmap::GetTexture()
	{
		return m_pTexture;
	}

	unsigned int IrisBitmap::GetWidth()
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().width);
	}

	unsigned int IrisBitmap::GetHeight()
	{
		return static_cast<unsigned int>(m_pTexture->GetRenderTargetBitmap()->GetPixelSize().height);
	}

	IrisBitmap::~IrisBitmap()
	{
		if (m_pTexture) {
			IrisTexture::Release(m_pTexture);
		}
	}
}