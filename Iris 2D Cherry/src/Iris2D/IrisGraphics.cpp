#include "Iris2D/IrisGraphics.h"
#include "Iris2D/IrisApp.h"
#include "Iris2D/IrisSprite.h"
#include "Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "Iris2D/IrisShaders/IrisSimplePixelShader.h"
#include "Iris2D/IrisD3DResourceManager.h"

namespace Iris2D {
	IrisGraphics * IrisGraphics::Instance()
	{
		static auto pInstance = IrisGraphics();
		return &pInstance;
	}

	void IrisGraphics::AddSprite(IrisSprite * pSprite)
	{
		m_stSprites.insert(pSprite);
	}

	void IrisGraphics::RemoveSprite(IrisSprite * pSprite)
	{
		m_stSprites.erase(pSprite);
	}

	void IrisGraphics::Update(IR_PARAM_RESULT_CT)
	{
		const float arrClearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

		auto pApp = IrisApplication::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto pD3DContenx = pD3DManager->GetD3DDeviceContext();

		// switch shader
		auto pVertexShader = IrisSpriteVertexShader::Instance();
		auto pPixelShader = IrisSimplePixelShader::Instance();

		pD3DManager->SetVertexShader(pVertexShader);
		pD3DManager->SetPixelShader(pPixelShader);

		pD3DContenx->ClearRenderTargetView(pD3DManager->GetRenderTargetView(), arrClearColor);

		for (auto& sprite : m_stSprites)
		{
			sprite->Render();
		}

		if (pApp->WindowMessageLoop() == WM_QUIT) {
			pApp->Quite();
			return;
		}
	}

	void IrisGraphics::Wait(unsigned int nDuration, IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::FadeOut(unsigned int nDuration, IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::FadeIn(unsigned int nDuration, IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::Freeze(IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::FrameReset()
	{
	}

	void IrisGraphics::ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT)
	{
	}

	void IrisGraphics::SetWidth(unsigned int nWidth)
	{
		m_nWidth = nWidth;
	}

	unsigned int IrisGraphics::GetWidth()
	{
		return m_nWidth;
	}

	void IrisGraphics::SetHeight(unsigned int nHeight)
	{
		m_nHeight = nHeight;
	}

	unsigned int IrisGraphics::GetHeight()
	{
		return m_nHeight;
	}

	unsigned int IrisGraphics::GetFrameCount()
	{
		return 0;
	}

	unsigned int IrisGraphics::GetBrightness()
	{
		return 0;
	}

	void IrisGraphics::SetBrightness(unsigned int nBrightness)
	{
	}

	float IrisGraphics::GetFrameRate()
	{
		return 0.0f;
	}

	void IrisGraphics::Release()
	{
		for (auto& sprite : m_stSprites)
		{
			IrisSprite::InnerRelease(sprite);
		}
	}

}
