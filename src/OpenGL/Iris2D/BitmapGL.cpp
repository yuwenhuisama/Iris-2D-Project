#include "OpenGL/Iris2D/BitmapGL.h"

namespace Iris2D {
	BitmapGL * BitmapGL::Create(const std::wstring & wstrFileName, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	BitmapGL * BitmapGL::Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	BitmapGL * BitmapGL::Create(Bitmap * pSrcBitmapGL, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	BitmapGL * BitmapGL::CopyFrom(Bitmap * pSrcBitmapGL, IR_PARAM_RESULT_CT) {
		return nullptr;
	}

	void BitmapGL::Release(BitmapGL *& pBitmapGL) {
	}

	unsigned int BitmapGL::GetWidth() const {
		return 0;
	}

	unsigned int BitmapGL::GetHeight() const {
		return 0;
	}

	bool BitmapGL::Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap * pSrcBitmapGL, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::StretchBlt(const Rect * pDestRect, const Bitmap * pSrcBitmapGL, const Rect * pSrcRect, float fOpacity, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color * pColor, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::FillRect(const Rect * pRect, const Color * pColor, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::Clear(IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::ClearRect(const Rect * pRect, IR_PARAM_RESULT_CT) {
		return false;
	}

	Color * BitmapGL::GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT_CT) const {
		return nullptr;
	}

	bool BitmapGL::SetPixel(unsigned int nX, unsigned int nY, const Color * pColor, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::SaveToFile(const std::wstring & wstrFilePath) {
		return false;
	}

	bool BitmapGL::HueChange(float fHue, IR_PARAM_RESULT_CT) {
		return false;
	}

	void BitmapGL::SetFont(Font *& pFont) {
	}

	Font * BitmapGL::GetFont() const {
		return nullptr;
	}

	unsigned int BitmapGL::TextSize(const Font * pFont, const std::wstring & wstrText, IR_PARAM_RESULT_CT) {
		return 0;
	}

	bool BitmapGL::DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::DrawText(const Rect * pRect, const std::wstring & wstrText, AlignType nAlign, IR_PARAM_RESULT_CT) {
		return false;
	}

	bool BitmapGL::Dispose() {
		return false;
	}
}
