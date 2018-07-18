#ifndef _H_DATA_CONVERT_HELPER_
#define _H_DATA_CONVERT_HELPER_

#include "DirectX/Common.h"

namespace Iris2D
{
	class RectDX;
	class ColorDX;
	class DataConvertHelperDX
	{
	public:
		static D2D1_RECT_F ConvertToD2DRectF(const RectDX* pRect);
		static D2D1_RECT_U ConvertToD2DRectU(const RectDX* pRect);
		static D2D1::ColorF ConvertToD2DColor(const ColorDX* pColor);

	private:
		DataConvertHelperDX() = default;
		~DataConvertHelperDX() = default;
	};

}

#endif // !_H_DATA_CONVERT_HELPER_
