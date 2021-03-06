#include "DirectX/Iris2D/GraphicsDX.h"
#include "DirectX/Iris2D/AppDX.h"
#include "DirectX/Iris2D/ViewportDX.h"
#include "DirectX/Iris2D/Shaders/SpriteVertexShader.h"
#include "DirectX/Iris2D/Shaders/SpritePixelShader.h"
#include "DirectX/Iris2D/Shaders/ViewportVertexShader.h"
#include "DirectX/Iris2D/Shaders/ViewportPixelShader.h"
#include "DirectX/Iris2D/D3DResourceManager.h"

namespace Iris2D {
	GraphicsDX * GraphicsDX::Instance()
	{
		static auto pInstance = GraphicsDX();
		return &pInstance;
	}

	void GraphicsDX::AddViewport(ViewportDX * pViewport)
	{
		m_stViewports.insert(pViewport);
	}

	void GraphicsDX::RemoveViewport(ViewportDX * pViewport)
	{
		m_stViewports.erase(pViewport);
	}

	ResultCode GraphicsDX::Update()
	{
		auto pApp = ApplicationDX::Instance();
		auto pD3DManager = D3DResourceManager::Instance();

		while (!m_bUpdateLockFlag) {
			MSG msg = { 0 };
			if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);

				if (msg.message == WM_QUIT) {
					pApp->Quite();
					return IRR_Success;;
				}
			}
			else {
				m_fCurrentTime = static_cast<float>(::timeGetTime());
				if (m_fCurrentTime >= m_fLastTime) {
					//const auto fTimeDelta = (m_fCurrentTime - m_fLastTime);
					m_fLastTime = m_fCurrentTime + m_fMsPerUpdate;
					m_bUpdateLockFlag = true;
				}

				Render();
				pD3DManager->GetSwapChain()->Present(1, 0);
			}
		}
		m_bUpdateLockFlag = false;
		++m_nFrameCount;

		return IRR_Success;
	}

	ResultCode GraphicsDX::UpdateNoLock()
	{
		auto pApp = ApplicationDX::Instance();
		auto pD3DManager = D3DResourceManager::Instance();

		MSG msg = { 0 };
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				pApp->Quite();
				return IRR_Success;
			}
		}
		else {
			Render();
			pD3DManager->GetSwapChain()->Present(0, 0);
		}
		++m_nFrameCount;

		return IRR_Success;
	}

	ResultCode GraphicsDX::Wait(unsigned int nDuration)
	{
		return IRR_Success;
	}

	ResultCode GraphicsDX::FadeOut(unsigned int nDuration)
	{
		return IRR_Success;
	}

	ResultCode GraphicsDX::FadeIn(unsigned int nDuration)
	{
		return IRR_Success;
	}

	ResultCode GraphicsDX::Freeze()
	{
		return IRR_Success;
	}

	ResultCode GraphicsDX::Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague)
	{
		return IRR_Success;
	}

	void GraphicsDX::FrameReset()
	{
		m_nFrameCount = 0;
	}

	ResultCode GraphicsDX::ResizeScreen(unsigned int nWidth, unsigned int nHeight)
	{
		return IRR_Success;
	}

	void GraphicsDX::SetWidth(unsigned int nWidth)
	{
		m_nWidth = nWidth;
	}

	unsigned int GraphicsDX::GetWidth() const
	{
		return m_nWidth;
	}

	void GraphicsDX::SetHeight(unsigned int nHeight)
	{
		m_nHeight = nHeight;
	}

	unsigned int GraphicsDX::GetHeight() const
	{
		return m_nHeight;
	}

	unsigned int GraphicsDX::GetFrameCount() const
	{
		return 0;
	}

	float GraphicsDX::GetBrightness() const
	{
		return 0;
	}

	void GraphicsDX::SetBrightness(float fBrightness)
	{
	}

	void GraphicsDX::SetFrameRate(float nFrameRate)
	{
		m_fFrameRate = nFrameRate;
		m_fMsPerUpdate = 1000.0f / nFrameRate;
	}

	float GraphicsDX::GetFrameRate() const
	{
		return m_fFrameRate;
	}

	void GraphicsDX::Release()
	{
		for (auto& pViewport : m_stViewports)
		{
			ViewportDX::ForceRelease(const_cast<ViewportDX*&>(pViewport));
		}
	}

	float GraphicsDX::GetMsPerUpdate()
	{
		return m_fMsPerUpdate;
	}

	bool GraphicsDX::Render()
	{
		const float arrClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		auto pD3DManager = D3DResourceManager::Instance();
		auto pD3DContext = pD3DManager->GetD3DDeviceContext();

		pD3DContext->ClearRenderTargetView(pD3DManager->GetRenderTargetView(), arrClearColor);

		ViewportVertexShader::Instance()->SetViewProjectMatrix(pD3DManager->GetViewMatrix());
		pD3DManager->SetVertexShader(SpriteVertexShader::Instance());
		pD3DManager->SetPixelShader(SpritePixelShader::Instance());
		for (auto& pViewport : m_stViewports)
		{
			pViewport->RenderSprite();
		}

		SpriteVertexShader::Instance()->SetViewProjectMatrix(pD3DManager->GetViewMatrix());
		pD3DManager->SetVertexShader(ViewportVertexShader::Instance());
		pD3DManager->SetPixelShader(ViewportPixelShader::Instance());
		for (auto& pViewport : m_stViewports)
		{
			pViewport->RenderSelf();
		}

		return true;
	}
}
