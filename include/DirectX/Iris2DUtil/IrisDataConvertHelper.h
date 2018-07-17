#ifndef _H_IRISDATACONVERTHELPER_
#define _H_IRISDATACONVERTHELPER_

#include "DirectX/IrisCommon.h"

namespace Iris2D
{
	class IrisRect;
	class IrisColor;
	class IrisDataConvertHelper
	{
	public:
		static D2D1_RECT_F ConvertToD2DRectF(const IrisRect* pRect);
		static D2D1_RECT_U ConvertToD2DRectU(const IrisRect* pRect);
		static D2D1::ColorF ConvertToD2DColor(const IrisColor* pColor);

	private:
		IrisDataConvertHelper() = default;
		~IrisDataConvertHelper() = default;
	};

}

#endif // !_H_IRISDATACONVERTHELPER_
