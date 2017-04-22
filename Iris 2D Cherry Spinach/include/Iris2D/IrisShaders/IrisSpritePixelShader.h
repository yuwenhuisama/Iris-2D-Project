#ifndef _H_IRISSPRITEPIXELSHADER_
#define _H_IRISSPRITEPIXELSHADER_
#include "IrisPixelShaderBase.h"
#include "Iris2D Util/IrisSpriteShaderBuffers.h"

namespace Iris2D
{
	class IrisSpritePixelShader : public IrisPixelShaderBase
	{
	private:
		ID3D11PixelShader* m_pPixelShader = nullptr;
		ID3D11Buffer* m_pColorProcessBuffer = nullptr;

	public:
		static IrisSpritePixelShader* Instance();

	private:
		IrisSpritePixelShader() = default;
		~IrisSpritePixelShader() = default;

	private:
		// Í¨¹ý IrisPixelShaderBase ¼Ì³Ð
		virtual std::wstring ShaderFileDefine() override;
		virtual std::string ShaderEntryFuncDefine() override;
		virtual std::string ShaderVersionDefine() override;
		virtual bool ShaderSubResourceDefine() override;
		virtual bool CreateShader(ID3DBlob * pBlob) override;
		virtual ID3D11PixelShader * GetPixelShader() override;

	public:
		virtual bool SetToContext() override;
		virtual bool Release() override;

		void SetColorProcessInfo(const IrisSpritePixelShaderBuffer& ispsInfo);
	};
}
#endif // !_H_IRISSPRITEPIXELSHADER_
