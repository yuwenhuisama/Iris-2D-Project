#ifndef _H_PIXEL_SHADER_BASE_
#define _H_PIXEL_SHADER_BASE_

#include "ShaderBase.h"

namespace Iris2D
{
	class PixelShaderBase : public ShaderBase
	{
	public:
		PixelShaderBase() = default;
		virtual ~PixelShaderBase() = default;

		virtual ID3D11PixelShader* GetPixelShader() = 0;
	};
}
#endif // !_H_PIXEL_SHADER_BASE_
