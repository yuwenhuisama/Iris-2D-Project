#include "Iris2D Util\IrisDataConvertHelper.h"
#include "Iris2D\IrisRect.h"
#include "Iris2D\IrisColor.h"

namespace Iris2D {
	D2D1_RECT_F IrisDataConvertHelper::ConvertToD2DRectF(const IrisRect * pRect)
	{
		return D2D1::RectF(pRect->GetLeft(), pRect->GetTop(), pRect->GetRight(), pRect->GetBottom());
	}

	D2D1_RECT_U IrisDataConvertHelper::ConvertToD2DRectU(const IrisRect * pRect)
	{
		return D2D1::RectU(static_cast<unsigned int>(pRect->GetLeft()),
			static_cast<unsigned int>(pRect->GetTop()),
			static_cast<unsigned int>(pRect->GetRight()),
			static_cast<unsigned int>(pRect->GetBottom()));
	}

	D2D1::ColorF IrisDataConvertHelper::ConvertToD2DColor(const IrisColor * pColor)
	{
		return D2D1::ColorF(static_cast<float>(pColor->GetRed()) / 255.0f,
			static_cast<float>(pColor->GetBlue()) / 255.0f,
			static_cast<float>(pColor->GetBlue()) / 255.0f,
			static_cast<float>(pColor->GetAlpha()) / 255.0f);
	}
}