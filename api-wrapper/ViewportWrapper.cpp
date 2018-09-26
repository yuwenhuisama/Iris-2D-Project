#define LIBRARY_EXPORTS
#include "ViewportWrapper.h"

EXPORT_API VIEWPORT_HANDLE Viewport_Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight) {
	return Iris2D::Viewport::Create(fX, fY, nWidth, nHeight);
}

EXPORT_API VIEWPORT_HANDLE Viewport_Create2(const RECT_HANDLE pRect) {
	const auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(pRect);

	return Iris2D::Viewport::Create(pCastedRect);
}

EXPORT_API void Viewport_Release(VIEWPORT_HANDLE* pViewport) {
	auto pCastedViewport = reinterpret_cast<Iris2D::Viewport*&>(*pViewport);

	Iris2D::Viewport::Release(pCastedViewport);
}

EXPORT_API void Viewport_ForceRelease(VIEWPORT_HANDLE* pViewport) {
	auto pCastedViewport = reinterpret_cast<Iris2D::Viewport*&>(*pViewport);

	Iris2D::Viewport::ForceRelease(pCastedViewport);
}

EXPORT_API void Viewport_SetOX(VIEWPORT_HANDLE hHandle, float fOX) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	pViewport->SetOX(fOX);
}
EXPORT_API float Viewport_GetOX(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetOX();
}

EXPORT_API void Viewport_SetOY(VIEWPORT_HANDLE hHandle, float fOY) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	pViewport->SetOY(fOY);
}
EXPORT_API float Viewport_GetOY(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetOY();
}

EXPORT_API void Viewport_SetSrcRect(VIEWPORT_HANDLE hHandle, RECT_HANDLE* pSrcRect) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);
	auto pCastedSrcRect = reinterpret_cast<Iris2D::Rect*&>(*pSrcRect);

	pViewport->SetSrcRect(pCastedSrcRect);
}

EXPORT_API RECT_HANDLE Viewport_GetSrcRect(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetSrcRect();
}

EXPORT_API void Viewport_SetTone(VIEWPORT_HANDLE hHandle, COLOR_HANDLE* pTone) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);
	auto pCastedTone = reinterpret_cast<Iris2D::Color*&>(*pTone);

	pViewport->SetTone(pCastedTone);
}

EXPORT_API COLOR_HANDLE Viewport_GetTone(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);
	
	return pViewport->GetTone();
}

EXPORT_API void Viewport_SetZ(VIEWPORT_HANDLE hHandle, float fZ) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	pViewport->SetZ(fZ);
}

EXPORT_API float Viewport_GetZ(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetZ();
}

EXPORT_API unsigned int Viewport_GetWidth(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetWidth();
}

EXPORT_API unsigned int Viewport_GetHeight(VIEWPORT_HANDLE hHandle) {
	const auto pViewport = reinterpret_cast<Iris2D::Viewport*>(hHandle);

	return pViewport->GetHeight();
}