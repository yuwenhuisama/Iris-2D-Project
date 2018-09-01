#include "Common/Iris2D/Graphics.h"

namespace Iris2D {

	Graphics* Graphics::Instance() {
		static Graphics graph;
		return &graph;
	}

	Graphics::Graphics() : Proxy(nullptr) {}

	ResultCode Graphics::Update() {
		return m_pProxied->Update();
	}

	ResultCode Graphics::UpdateNoLock() {
		return m_pProxied->UpdateNoLock();
	}

	ResultCode Graphics::Wait(unsigned int nDuration) {
		return m_pProxied->Wait(nDuration);
	}

	ResultCode Graphics::FadeOut(unsigned int nDuration) {
		return m_pProxied->FadeIn(nDuration);
	}

	ResultCode Graphics::FadeIn(unsigned int nDuration) {
		return m_pProxied->FadeOut(nDuration);
	}

	ResultCode Graphics::Freeze() {
		return m_pProxied->Freeze();
	}

	ResultCode Graphics::Transition(unsigned int nDuration, const std::wstring& wstrFilename, unsigned int nVague) {
		return m_pProxied->Transition(nDuration, wstrFilename, nVague);
	}

	void Graphics::FrameReset() {
		return m_pProxied->FrameReset();
	}

	ResultCode Graphics::ResizeScreen(unsigned int nWidth, unsigned int nHeight) {
		return m_pProxied->ResizeScreen(nWidth, nHeight);
	}

	unsigned int Graphics::GetWidth() const {
		return m_pProxied->GetWidth();
	}

	unsigned int Graphics::GetHeight() const {
		return m_pProxied->GetHeight();
	}

	unsigned int Graphics::GetFrameCount() const {
		return m_pProxied->GetFrameCount();
	}

	float Graphics::GetBrightness() const {
		return m_pProxied->GetBrightness();
	}

	void Graphics::SetBrightness(float fBrightness) {
		m_pProxied->SetBrightness(fBrightness);
	}

	void Graphics::SetFrameRate(float fFrameRate) {
		m_pProxied->SetFrameRate(fFrameRate);
	}

	float Graphics::GetFrameRate() const {
		return m_pProxied->GetFrameRate();
	}

	void Graphics::Release() {
		m_pProxied->Release();
	}

	float Graphics::GetMsPerUpdate() {
		return m_pProxied->GetMsPerUpdate();
	}
}
