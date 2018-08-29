#define LIBRARY_EXPORTS
#include "GraphicsWrapper.h"

EXPORT_API GRAPHICS_HANDLE Graphics_GetInstance() {
	return Iris2D::AppFactory::GetGraphics();
}

EXPORT_API ResultCode Graphics_Update(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->Update();
}

EXPORT_API ResultCode Graphics_UpdateNoLock(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->UpdateNoLock();
}

EXPORT_API ResultCode Graphics_Wait(GRAPHICS_HANDLE hGraphics, unsigned int nDuration) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->Wait(nDuration);
}

EXPORT_API ResultCode Graphics_FadeOut(GRAPHICS_HANDLE hGraphics, unsigned int nDuration) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->FadeOut(nDuration);
}

EXPORT_API ResultCode Graphics_FadeIn(GRAPHICS_HANDLE hGraphics, unsigned int nDuration) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->FadeIn(nDuration);
}

EXPORT_API ResultCode Graphics_Freeze(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->Freeze();
}

EXPORT_API ResultCode Graphics_Transition(GRAPHICS_HANDLE hGraphics, unsigned int nDuration, wchar_t * wstrFilename, unsigned int nVague) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->Transition(nDuration, wstrFilename, nVague);
}

EXPORT_API void Graphics_FrameReset(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->FrameReset();
}

EXPORT_API ResultCode Graphics_ResizeScreen(GRAPHICS_HANDLE hGraphics, unsigned int nWidth, unsigned int nHeight) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->ResizeScreen(nWidth, nHeight);
}

EXPORT_API void Graphics_SetWidth(GRAPHICS_HANDLE hGraphics, unsigned int nWidth) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->SetWidth(nWidth);
}

EXPORT_API unsigned int Graphics_GetWidth(GRAPHICS_HANDLE hGraphics) {
	const auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetWidth();
}

EXPORT_API void Graphics_SetHeight(GRAPHICS_HANDLE hGraphics, unsigned int nHeight) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->SetHeight(nHeight);
}

EXPORT_API unsigned int Graphics_GetHeight(GRAPHICS_HANDLE hGraphics) {
	const auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetHeight();
}

EXPORT_API unsigned int Graphics_GetFrameCount(GRAPHICS_HANDLE hGraphics) {
	const auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetFrameCount();
}

EXPORT_API float Graphics_GetBrightness(GRAPHICS_HANDLE hGraphics) {
	const auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetBrightness();
}

EXPORT_API void Graphics_SetBrightness(GRAPHICS_HANDLE hGraphics, float fBrightness) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->SetBrightness(fBrightness);
}

EXPORT_API void Graphics_SetFrameRate(GRAPHICS_HANDLE hGraphics, float fFrameRate) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->SetFrameRate(fFrameRate);
}

EXPORT_API float Graphics_GetFrameRate(GRAPHICS_HANDLE hGraphics) {
	const auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetFrameRate();
}

EXPORT_API void Graphics_Release(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	pGraphics->Release();
}

EXPORT_API float Graphics_GetMsPerUpdate(GRAPHICS_HANDLE hGraphics) {
	auto pGraphics = reinterpret_cast<Iris2D::Graphics*>(hGraphics);
	return pGraphics->GetMsPerUpdate();
}
