#ifndef _H_VERTEXT_SHADERBASE_
#define _H_VERTEXT_SHADERBASE_

#include "ShaderBase.h"
namespace Iris2D
{
	class VertexShaderBase : public ShaderBase
	{
	public:
		VertexShaderBase() = default;
		virtual ~VertexShaderBase() = default;

		virtual bool CreateInputLayout() = 0;
		virtual ID3D11InputLayout* GetInputLayout() = 0;
		virtual ID3D11VertexShader* GetVertexShader() = 0;
	};
}

#endif // !_H_VERTEXT_SHADERBASE_
