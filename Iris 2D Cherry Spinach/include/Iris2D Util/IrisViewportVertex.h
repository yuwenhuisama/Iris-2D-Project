#ifndef _H_IRISVIEWPORTVERTEX_
#define _H_IRISVIEWPORTVERTEX_

#include "../IrisCommon.h"

using namespace DirectX;

namespace Iris2D
{
	struct IrisViewportVertex {
		XMFLOAT4 m_vcPos;
		XMFLOAT2 m_vcTex0;
	};
}

#endif // !_H_IRISVIEWPORTVERTEX_
