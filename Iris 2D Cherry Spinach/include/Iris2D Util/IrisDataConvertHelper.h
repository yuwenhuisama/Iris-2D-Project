#ifndef _H_IRISDATACONVERTHELPER_
#define _H_IRISDATACONVERTHELPER_

#include "IrisCommon.h"

namespace Iris2D
{
	class IrisRect;
	class IrisColor;
	class IrisDataConvertHelper
	{
	public:
		static D2D1_RECT_F ConvertToD2DRectF(IrisRect* pRect);
		static D2D1_RECT_U ConvertToD2DRectU(IrisRect* pRect);
		static D2D1::ColorF ConvertToD2DColor(IrisColor* pColor);

	private:
		IrisDataConvertHelper() = default;
		~IrisDataConvertHelper() = default;
	};

}

#endif // !_H_IRISDATACONVERTHELPER_
