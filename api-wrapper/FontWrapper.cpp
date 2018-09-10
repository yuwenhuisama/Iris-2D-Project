#define LIBRARY_EXPORTS
#include "FontWrapper.h"

EXPORT_API bool Font_Existed(const wchar_t* wstrFontName) {
	return Iris2D::Font::Existed(wstrFontName);
}

EXPORT_API FONT_HANDLE Font_Create(const wchar_t* wstrFontName) {
	return Iris2D::Font::Create(wstrFontName);
}

EXPORT_API void Font_Release(FONT_HANDLE* pFont) {
	auto pCastedFont = reinterpret_cast<Iris2D::Font*&>(pFont);
	Iris2D::Font::Release(pCastedFont);
}

EXPORT_API wchar_t* Font_GetDefaultName() {
	const auto& wstrName = Iris2D::Font::GetDefaultName();
	const auto wszName = new wchar_t[wstrName.size()]{0,};
	wcscpy(wszName, wstrName.c_str());
	return wszName;
}

EXPORT_API unsigned int Font_GetDefaultSize() {
	return Iris2D::Font::GetDefaultSize();
}

EXPORT_API bool Font_GetDefaultBold() {
	return Iris2D::Font::GetDefaultBold();
}

EXPORT_API bool Font_GetDefaultItalic() {
	return Iris2D::Font::GetDefaultItalic();
}

EXPORT_API bool Font_GetDefaultShadow() {
	return Iris2D::Font::GetDefaultShadow();
}

EXPORT_API COLOR_HANDLE Font_GetDefaultColor() {
	return Iris2D::Font::GetDefaultColor();
}

EXPORT_API void Font_SetName(FONT_HANDLE hHandle, const wchar_t* wstrFontName) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	pFont->SetName(wstrFontName);
}

EXPORT_API const wchar_t* Font_GetName(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);

	const auto& wstrName = pFont->GetName();
	const auto wszName = new wchar_t[wstrName.size()]{ 0, };
	wcscpy(wszName, wstrName.c_str());
	return wszName;
}

EXPORT_API void Font_SetSize(FONT_HANDLE hHandle, unsigned int nSize) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	pFont->SetSize(nSize);
}

EXPORT_API unsigned int Font_GetSize(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	return pFont->GetSize();
}

EXPORT_API void Font_SetBold(FONT_HANDLE hHandle, bool bBold) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	pFont->SetBold(bBold);
}

EXPORT_API bool Font_GetBold(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	return pFont->GetBold();
}

EXPORT_API void Font_SetItalic(FONT_HANDLE hHandle, bool bItalic) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	pFont->SetItalic(bItalic);
}

EXPORT_API bool Font_GetItalic(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	return pFont->GetItalic();
}

EXPORT_API void Font_SetShadow(FONT_HANDLE hHandle, bool bShadow) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	pFont->SetShadow(bShadow);
}
EXPORT_API bool Font_GetShadow(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	return pFont->GetShadow();
}

EXPORT_API void Font_SetColor(FONT_HANDLE hHandle, COLOR_HANDLE* pColor) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	auto pCastedColor = reinterpret_cast<Iris2D::Color*&>(pColor);
	pFont->SetColor(pCastedColor);
}

EXPORT_API COLOR_HANDLE Font_GetColor(FONT_HANDLE hHandle) {
	const auto pFont = reinterpret_cast<Iris2D::Font*>(hHandle);
	return pFont->GetColor();
}
