#ifndef _H_IRISSIMPLEVERTEXSHADER_
#include "IrisVertexShaderBase.h"
 
namespace Iris2D
{
	class IrisSimpleVertexShader : public IrisVertexShaderBase
	{
	private:
		ID3D11VertexShader* m_pVertextShader = nullptr;

		ID3DBlob* m_pBlob = nullptr;
		ID3D11InputLayout* m_pInputLayout = nullptr;
		ID3D11Buffer* m_pMatrixBuffer = nullptr;

	public:
		static IrisSimpleVertexShader* Instance();

	public:
		~IrisSimpleVertexShader() = default;

	protected:
		// 通过 IrisShaderBase 继承
		virtual std::wstring ShaderFileDefine() override;
		virtual std::string ShaderEntryFuncDefine() override;
		virtual std::string ShaderVersionDefine() override;
		virtual bool CreateShader(ID3DBlob * pBlob) override;
		virtual bool ShaderSubResourceDefine() override;

	public:

		// 通过 IrisVertexShaderBase 继承
		virtual ID3D11VertexShader * GetVertexShader() override;
		virtual bool CreateInputLayout(ID3D11Device * pDevice) override;
		virtual ID3D11InputLayout* GetInputLayout() override;

		virtual bool SetToContext() override;
		virtual bool Release() override;

	private:
		IrisSimpleVertexShader() = default;
	};
}
#endif // !_H_IRISSIMPLEVERTEXSHADER_