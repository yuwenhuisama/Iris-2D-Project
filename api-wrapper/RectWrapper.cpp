#define LIBRARY_EXPORTS
#include "RectWrapper.h"

EXPORT_API RECT_HANDLE Rect_Create(float fX, float fY, float fWidth, float fHeight) {
	return Iris2D::Rect::Create(fX, fY, fWidth, fHeight);
}

EXPORT_API RECT_HANDLE Rect_Create2(float fLeft, float fTop, float fRight, float fBottom) {
	return Iris2D::Rect::Create2(fLeft, fTop, fRight, fBottom);
}

EXPORT_API void Rect_Release(RECT_HANDLE* pRect) {
	auto pCastedRect = reinterpret_cast<Iris2D::Rect*&>(*pRect);
	Iris2D::Rect::Release(pCastedRect);
}

EXPORT_API void Rect_SetX(RECT_HANDLE hHandle, float fX) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetX(fX);
}

EXPORT_API float Rect_GetX(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetX();
}

EXPORT_API void Rect_SetY(RECT_HANDLE hHandle, float fY) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetY(fY);
}

EXPORT_API float Rect_GetY(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetY();
}

EXPORT_API void Rect_SetWidth(RECT_HANDLE hHandle, float fWidth) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetWidth(fWidth);
}

EXPORT_API float Rect_GetWidth(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetWidth();
}

EXPORT_API void Rect_SetHeight(RECT_HANDLE hHandle, float fHeight) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetHeight(fHeight);
}
EXPORT_API float Rect_GetHeight(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetHeight();
}

EXPORT_API void Rect_SetLeft(RECT_HANDLE hHandle, float fLeft) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetLeft(fLeft);
}
EXPORT_API float Rect_GetLeft(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetLeft();
}

EXPORT_API void Rect_SetTop(RECT_HANDLE hHandle, float fTop) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetTop(fTop);
}

EXPORT_API float Rect_GetTop(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetTop();
}

EXPORT_API void Rect_SetRight(RECT_HANDLE hHandle, float fRight) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetRight(fRight);
}

EXPORT_API float Rect_GetRight(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetRight();
}

EXPORT_API void Rect_SetBottom(RECT_HANDLE hHandle, float fBottom) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->SetBottom(fBottom);
}

EXPORT_API float Rect_GetBottom(RECT_HANDLE hHandle) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	return pRect->GetBottom();
}

EXPORT_API void Rect_Set(RECT_HANDLE hHandle, float fX, float fY, float fWidth, float fHeight) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->Set(fX, fY, fWidth, fHeight);
}
EXPORT_API void Rect_Set2(RECT_HANDLE hHandle, float fLeft, float fTop, float fRight, float fBottom) {
	const auto pRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	pRect->Set2(fLeft, fTop, fRight, fBottom);
}

EXPORT_API bool Rect_CheckInsectionWith(RECT_HANDLE hHandle, const RECT_HANDLE pRect) {
	const auto pCastedRect = reinterpret_cast<Iris2D::Rect*>(hHandle);
	const auto pCheckedRect = reinterpret_cast<Iris2D::Rect*>(pRect);

	return pCastedRect->CheckInsectionWith(pCheckedRect);
}
