#include "OpenGL/Iris2D/BitmapGL.h"

namespace Iris2D {
	unsigned int Bitmap::GetWidth() const {
		return 0;
	}

	unsigned int Bitmap::GetHeight() const {
		return 0;
	}

	bool Bitmap::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmap, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::FillRect(const Rect * pRect, const Color * pColor, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::Clear(IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::ClearRect(const Rect * pRect, IR_PARAM_RESULT) {
		return false;
	}

	Color * Bitmap::GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const {
		return nullptr;
	}

	bool Bitmap::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::SaveToFile(const std::wstring & wstrFilePath) {
		return false;
	}

	bool Bitmap::HueChange(float fHue, IR_PARAM_RESULT) {
		return false;
	}

	void Bitmap::SetFont(Font *& pFont) {
	}

	Font * Bitmap::GetFont() const {
		return nullptr;
	}

	unsigned int Bitmap::TextSize(const Font * pFont, const std::wstring & wstrText, IR_PARAM_RESULT) {
		return 0;
	}

	bool Bitmap::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT) {
		return false;
	}

	bool Bitmap::Dispose() {
		return false;
	}
}
