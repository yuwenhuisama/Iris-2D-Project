#ifndef _H_IRISSPRITEVERTEX_
#define _H_IRISSPRITEVERTEX_

#include "DirectX/Common.h"

using namespace DirectX;

namespace Iris2D
{
	struct SpriteVertex {
		XMFLOAT4 m_vcPos;
		XMFLOAT2 m_vcTex0;
	};
}

#endif // !_H_IRISSPRITEVERTEX_
