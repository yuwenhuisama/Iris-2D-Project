#ifndef _H_IRISPIXELSHADERBASE_
#define _H_IRISPIXELSHADERBASE_

#include "IrisShaderBase.h"

namespace Iris2D
{
	class IrisPixelShaderBase : public IrisShaderBase
	{
	public:
		IrisPixelShaderBase() = default;
		virtual ~IrisPixelShaderBase() = default;

		virtual ID3D11PixelShader* GetPixelShader() = 0;
	};
}
#endif // !_H_IRISPIXELSHADERBASE_
