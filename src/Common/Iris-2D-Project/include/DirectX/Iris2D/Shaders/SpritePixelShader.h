#ifndef _H_SPRITE_PIXEL_SHADER_
#define _H_SPRITE_PIXEL_SHADER_
#include "PixelShaderBase.h"
#include "DirectX/Util/SpriteShaderBuffersDX.h"

namespace Iris2D
{
	class SpritePixelShader : public PixelShaderBase
	{
	private:
		ID3D11PixelShader* m_pPixelShader = nullptr;
		ID3D11Buffer* m_pColorProcessBuffer = nullptr;

	public:
		static SpritePixelShader* Instance();

	private:
		SpritePixelShader() = default;
		~SpritePixelShader() = default;

	private:
		// Í¨¹ý PixelShaderBase ¼Ì³Ð
		virtual std::wstring ShaderFileDefine() override;
		virtual std::string ShaderEntryFuncDefine() override;
		virtual std::string ShaderVersionDefine() override;
		virtual bool ShaderSubResourceDefine() override;
		virtual bool CreateShader(ID3DBlob * pBlob) override;

	public:
		virtual bool SetToContext() override;
		virtual bool Release() override;
		virtual ID3D11PixelShader * GetPixelShader() override;
		void SetColorProcessInfo(const SpritePixelShaderBufferDX& ispsInfo);
	};
}
#endif // !_H_SPRITE_PIXEL_SHADER_
