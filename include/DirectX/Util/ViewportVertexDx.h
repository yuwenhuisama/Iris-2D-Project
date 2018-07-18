#ifndef _H_VIEWPORT_VERTEX_
#define _H_VIEWPORT_VERTEX_

#include "DirectX/Common.h"

using namespace DirectX;

namespace Iris2D
{
	struct ViewportVertexDX {
		XMFLOAT4 m_vcPos;
		XMFLOAT2 m_vcTex0;
	};
}

#endif // !_H_VIEWPORT_VERTEX_
