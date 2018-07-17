#ifndef _H_IRISVIEWPORTPIXELSHADER_
#define _H_IRISVIEWPORTPIXELSHADER_
#include "IrisPixelShaderBase.h"
#include "DirectX/Iris2DUtil/IrisViewportShaderBuffers.h"

namespace Iris2D
{
	class IrisViewportPixelShader : public IrisPixelShaderBase
	{
	private:
		ID3D11PixelShader* m_pPixelShader = nullptr;
		ID3D11Buffer* m_pColorProcessBuffer = nullptr;

	private:
		IrisViewportPixelShader() = default;
		~IrisViewportPixelShader() = default;

	public:
		static IrisViewportPixelShader* Instance();

		// Í¨¹ý IrisPixelShaderBase ¼Ì³Ð
		virtual std::wstring ShaderFileDefine() override;
		virtual std::string ShaderEntryFuncDefine() override;
		virtual std::string ShaderVersionDefine() override;
		virtual bool ShaderSubResourceDefine() override;
		virtual bool CreateShader(ID3DBlob * pBlob) override;

	public:
		virtual bool SetToContext() override;
		virtual bool Release() override;
		virtual ID3D11PixelShader * GetPixelShader() override;

		void SetColorProcessInfo(const IrisViewportPixelShaderBuffer& ivpsInfo);
	};
}
#endif // _H_IRISVIEWPORTPIXELSHADER_
