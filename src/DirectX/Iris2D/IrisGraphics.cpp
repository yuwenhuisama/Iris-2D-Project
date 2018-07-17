#include "DirectX/Iris2D/IrisGraphics.h"
#include "DirectX/Iris2D/IrisApp.h"
#include "DirectX/Iris2D/IrisViewport.h"
#include "DirectX/Iris2D/IrisShaders/IrisSpriteVertexShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisSpritePixelShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisViewportVertexShader.h"
#include "DirectX/Iris2D/IrisShaders/IrisViewportPixelShader.h"
#include "DirectX/Iris2D/IrisD3DResourceManager.h"

namespace Iris2D {
	IrisGraphics * IrisGraphics::Instance()
	{
		static auto pInstance = IrisGraphics();
		return &pInstance;
	}

	void IrisGraphics::AddViewport(IrisViewport * pViewport)
	{
		m_stViewports.insert(pViewport);
	}

	void IrisGraphics::RemoveViewport(IrisViewport * pViewport)
	{
		m_stViewports.erase(pViewport);
	}

	void IrisGraphics::Update(IR_PARAM_RESULT_CT)
	{
		auto pApp = IrisApplication::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();

		while (!m_bUpdateLockFlag) {
			MSG msg = { 0 };
			if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);

				if (msg.message == WM_QUIT) {
					pApp->Quite();
					return;
				}
			}
			else {
				m_fCurrentTime = static_cast<float>(::timeGetTime());
				if (m_fCurrentTime >= m_fLastTime) {
					auto fTimeDelta = (m_fCurrentTime - m_fLastTime);
					m_fLastTime = m_fCurrentTime + m_fMsPerUpdate;
					m_bUpdateLockFlag = true;
				}

				Render();
				pD3DManager->GetSwapChain()->Present(1, 0);
			}
		}
		m_bUpdateLockFlag = false;
	}

	void IrisGraphics::UpdateNoLock(IR_PARAM_RESULT_CT)
	{
		auto pApp = IrisApplication::Instance();
		auto pD3DManager = IrisD3DResourceManager::Instance();

		MSG msg = { 0 };
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				pApp->Quite();
				return;
			}
		}
		else {
			Render();
			pD3DManager->GetSwapChain()->Present(0, 0);
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

	void IrisGraphics::SetFrameRate(float nFrameRate)
	{
		m_fFrameRate = nFrameRate;
		m_fMsPerUpdate = 1000.0f / nFrameRate;
	}

	float IrisGraphics::GetFrameRate() const
	{
		return m_fFrameRate;
	}

	void IrisGraphics::Release()
	{
		for (auto& pViewport : m_stViewports)
		{
			IrisViewport::InnerRelease(const_cast<IrisViewport*>(pViewport));
		}
	}

	float IrisGraphics::GetMsPerUpdate()
	{
		return m_fMsPerUpdate;
	}

	bool IrisGraphics::Render()
	{
		const float arrClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		auto pD3DManager = IrisD3DResourceManager::Instance();
		auto pD3DContext = pD3DManager->GetD3DDeviceContext();

		pD3DContext->ClearRenderTargetView(pD3DManager->GetRenderTargetView(), arrClearColor);

		IrisViewportVertexShader::Instance()->SetViewProjectMatrix(pD3DManager->GetViewMatrix());
		pD3DManager->SetVertexShader(IrisSpriteVertexShader::Instance());
		pD3DManager->SetPixelShader(IrisSpritePixelShader::Instance());
		for (auto& pViewport : m_stViewports)
		{
			pViewport->RenderSprite();
		}

		IrisSpriteVertexShader::Instance()->SetViewProjectMatrix(pD3DManager->GetViewMatrix());
		pD3DManager->SetVertexShader(IrisViewportVertexShader::Instance());
		pD3DManager->SetPixelShader(IrisViewportPixelShader::Instance());
		for (auto& pViewport : m_stViewports)
		{
			pViewport->RenderSelf();
		}

		return true;
	}
}
