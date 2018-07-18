#include "DirectX/Util/DataConvertHelperDX.h"
#include "DirectX/Iris2D/RectDX.h"
#include "DirectX/Iris2D/ColorDX.h"

namespace Iris2D {
	D2D1_RECT_F DataConvertHelperDX::ConvertToD2DRectF(const RectDX * pRect)
	{
		return D2D1::RectF(pRect->GetLeft(), pRect->GetTop(), pRect->GetRight(), pRect->GetBottom());
	}

	D2D1_RECT_U DataConvertHelperDX::ConvertToD2DRectU(const RectDX * pRect)
	{
		return D2D1::RectU(static_cast<unsigned int>(pRect->GetLeft()),
			static_cast<unsigned int>(pRect->GetTop()),
			static_cast<unsigned int>(pRect->GetRight()),
			static_cast<unsigned int>(pRect->GetBottom()));
	}

	D2D1::ColorF DataConvertHelperDX::ConvertToD2DColor(const ColorDX * pColor)
	{
		return D2D1::ColorF(static_cast<float>(pColor->GetRed()) / 255.0f,
			static_cast<float>(pColor->GetBlue()) / 255.0f,
			static_cast<float>(pColor->GetBlue()) / 255.0f,
			static_cast<float>(pColor->GetAlpha()) / 255.0f);
	}
}