#ifndef _H_SPRITE_VERTEX_SHADER_
#define _H_SPRITE_VERTEX_SHADER_
#include "VertexShaderBase.h"
#include "DirectX/Util/SpriteShaderBuffersDX.h"

namespace Iris2D
{
	class SpriteVertexShader : public VertexShaderBase
	{
	public:
		static SpriteVertexShader* Instance();

	private:
		ID3D11VertexShader* m_pVertextShader = nullptr;

		ID3DBlob* m_pBlob = nullptr;
		ID3D11InputLayout* m_pInputLayout = nullptr;

		ID3D11Buffer* m_pMatrixBuffer = nullptr;
		ID3D11Buffer* m_pViewProjectMatrixBuffer = nullptr;

	private:
		SpriteVertexShader() = default;
		~SpriteVertexShader() = default;

	protected:
		// Í¨¹ý VertexShaderBase ¼Ì³Ð
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
		void SetWorldMatrix(const SpriteVertexShaderBufferDX& mbBuffer);

		virtual bool Release() override;
	};
}
#endif // _H_SPRITE_VERTEX_SHADER_
