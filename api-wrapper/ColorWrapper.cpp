#define LIBRARY_EXPORTS
#include "ColorWrapper.h"

EXPORT_API COLOR_HANDLE Color_Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
	return Iris2D::Color::Create(cRed, cGreen, cBlue, cAlpha);
}

EXPORT_API void Color_Release(COLOR_HANDLE* pColor) {
	auto pCastedColor = reinterpret_cast<Iris2D::Color*>(pColor);
	Iris2D::Color::Release(pCastedColor);
}

EXPORT_API void Color_SetRed(COLOR_HANDLE hHandle, unsigned char cRed) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	pColor->SetRed(cRed);
}

EXPORT_API unsigned char Color_GetRed(COLOR_HANDLE hHandle) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	return pColor->GetRed();
}

EXPORT_API void Color_SetGreen(COLOR_HANDLE hHandle, unsigned char cGreen) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	pColor->SetGreen(cGreen);
}

EXPORT_API unsigned char Color_GetGreen(COLOR_HANDLE hHandle) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	return pColor->GetGreen();
}

EXPORT_API void Color_SetBlue(COLOR_HANDLE hHandle, unsigned char cBlue) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	pColor->SetBlue(cBlue);
}

EXPORT_API unsigned char Color_GetBlue(COLOR_HANDLE hHandle) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	return pColor->GetBlue();
}

EXPORT_API void Color_SetAlpha(COLOR_HANDLE hHandle, unsigned char cAlpha) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	pColor->SetAlpha(cAlpha);
}

EXPORT_API unsigned char Color_GetAlpha(COLOR_HANDLE hHandle) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	return pColor->GetAlpha();
}

EXPORT_API void Color_Set(COLOR_HANDLE hHandle, unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) {
	const auto pColor = reinterpret_cast<Iris2D::Color*>(hHandle);
	pColor->Set(cRed, cGreen, cBlue, cAlpha);
}