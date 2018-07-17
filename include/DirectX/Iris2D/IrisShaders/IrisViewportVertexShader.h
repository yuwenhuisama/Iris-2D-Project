#ifndef _H_IRISVIEWPORTVERTEXSHADER_
#define _H_IRISVIEWPORTVERTEXSHADER_
#include "IrisVertexShaderBase.h"
#include "DirectX/Iris2DUtil/IrisViewportShaderBuffers.h"

namespace Iris2D
{
	class IrisViewportVertexShader : public IrisVertexShaderBase
	{
	private:
		ID3D11VertexShader* m_pVertextShader = nullptr;

		ID3DBlob* m_pBlob = nullptr;
		ID3D11InputLayout* m_pInputLayout = nullptr;

		ID3D11Buffer* m_pMatrixBuffer = nullptr;
		ID3D11Buffer* m_pViewProjectMatrixBuffer = nullptr;

	private:
		IrisViewportVertexShader() = default;
		~IrisViewportVertexShader() = default;
	
	public:
		static IrisViewportVertexShader* Instance();

	protected:
		// Í¨¹ý IrisVertexShaderBase ¼Ì³Ð
		virtual std::wstring ShaderFileDefine() override;
		virtual std::string ShaderEntryFuncDefine() override;
		virtual std::string ShaderVersionDefine() override;
		virtual bool ShaderSubResourceDefine() override;
		virtual bool CreateShader(ID3DBlob * pBlob) override;
		virtual bool SetToContext() override;

	public:
		virtual bool CreateInputLayout() override;
		virtual ID3D11InputLayout * GetInputLayout() override;
		virtual ID3D11VertexShader * GetVertexShader() override;

		void SetViewProjectMatrix(const DirectX::XMMATRIX& mxVPMatrix);
		void SetWorldMatrix(const IrisViewportVertexShaderBuffer& mbBuffer);

		virtual bool Release() override;
	};
}
#endif // !_H_IRISVIEWPORTVERTEXSHADER_
