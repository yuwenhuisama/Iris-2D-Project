#ifndef _H_IRISVERTEXTSHADERBASE_
#define _H_IRISVERTEXTSHADERBASE_

#include "IrisShaderBase.h"
namespace Iris2D
{
	class IrisVertexShaderBase : public IrisShaderBase
	{
	public:
		IrisVertexShaderBase() = default;
		virtual ~IrisVertexShaderBase() = default;

		virtual bool CreateInputLayout(ID3D11Device * pDevice) = 0;
		virtual ID3D11InputLayout* GetInputLayout() = 0;
		virtual ID3D11VertexShader* GetVertexShader() = 0;
	};
}

#endif // !_H_IRISVERTEXTSHADERBASE_
