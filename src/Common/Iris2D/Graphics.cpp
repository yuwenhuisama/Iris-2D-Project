#include "Common/Iris2D/Graphics.h"

namespace Iris2D {

	Graphics* Graphics::Instance() {
		static Graphics graph;
		return &graph;
	}

	Graphics::Graphics() : Proxy(nullptr) {}

	void Graphics::Update(IR_PARAM_RESULT_CT) {
		m_pProxied->Update(IR_PARAM);
	}

	void Graphics::UpdateNoLock(IR_PARAM_RESULT_CT) {
		m_pProxied->UpdateNoLock(IR_PARAM);
	}

	void Graphics::Wait(unsigned int nDuration, IR_PARAM_RESULT_CT) {
		m_pProxied->Wait(nDuration, IR_PARAM);
	}

	void Graphics::FadeOut(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void Graphics::FadeIn(unsigned int nDuration, IR_PARAM_RESULT_CT) {
	}

	void Graphics::Freeze(IR_PARAM_RESULT_CT) {
	}

	void Graphics::Transition(unsigned int nDuration, std::wstring wstrFilename, unsigned int nVague, IR_PARAM_RESULT_CT) {
	}

	void Graphics::FrameReset() {
	}

	void Graphics::ResizeScreen(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
	}

	void Graphics::SetWidth(unsigned int nWidth) {
		m_pProxied->SetWidth(nWidth);
	}

	unsigned int Graphics::GetWidth() const {
		return m_pProxied->GetWidth();
	}

	void Graphics::SetHeight(unsigned int nHeight) {
		m_pProxied->SetHeight(nHeight);
	}

	unsigned int Graphics::GetHeight() const {
		return m_pProxied->GetHeight();
	}

	unsigned int Graphics::GetFrameCount() const {
		return m_pProxied->GetFrameCount();
	}

	unsigned int Graphics::GetBrightness() const {
		return m_pProxied->GetBrightness();
	}

	void Graphics::SetBrightness(unsigned int nBrightness) {
		m_pProxied->SetBrightness(nBrightness);
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
