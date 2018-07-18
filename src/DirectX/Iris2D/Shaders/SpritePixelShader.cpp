#include "DirectX/Iris2D/Shaders/SpritePixelShader.h"
#include "DirectX/Iris2D/D3DResourceManager.h"


namespace Iris2D
{
	SpritePixelShader * SpritePixelShader::Instance()
	{
		static SpritePixelShader ispsInstance;
		return &ispsInstance;
	}

	std::wstring SpritePixelShader::ShaderFileDefine()
	{
		return L"shaders\\HLSL\\iris2d_sprite_pixel_shader.fx";
	}

	std::string SpritePixelShader::ShaderEntryFuncDefine()
	{
		return "PSMain";
	}

	std::string SpritePixelShader::ShaderVersionDefine()
	{
		return "ps_4_0";
	}

	bool SpritePixelShader::ShaderSubResourceDefine()
	{
		auto pDevice = D3DResourceManager::Instance()->GetD3D11Device();

		D3D11_BUFFER_DESC dbdMatrix;
		memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
		dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		dbdMatrix.ByteWidth = sizeof(SpriteVertexShaderBufferDX);
		dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

		auto hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pColorProcessBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pColorProcessBuffer);
			return false;
		}

		return true;
	}

	bool SpritePixelShader::CreateShader(ID3DBlob * pBlob)
	{
		auto hResult = D3DResourceManager::Instance()->
			GetD3D11Device()->
			CreatePixelShader(
				pBlob->GetBufferPointer(),
				pBlob->GetBufferSize(),
				nullptr,
				&m_pPixelShader
			);

		if (FAILED(hResult)) {
			SafeCOMRelease(m_pPixelShader);
			SafeCOMRelease(pBlob);
			return false;
		}

		SafeCOMRelease(pBlob);
		return true;
	}

	bool SpritePixelShader::SetToContext()
	{
		D3DResourceManager::Instance()->
			GetD3DDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
		return true;
	}

	bool SpritePixelShader::Release()
	{
		SafeCOMRelease(m_pPixelShader);
		SafeCOMRelease(m_pColorProcessBuffer);
		return true;
	}

	void SpritePixelShader::SetColorProcessInfo(const SpritePixelShaderBufferDX & ispsInfo)
	{
		auto pContext = D3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pColorProcessBuffer, 0, nullptr, &ispsInfo, 0, 0);
		pContext->PSSetConstantBuffers(0, 1, &m_pColorProcessBuffer);
	}

	ID3D11PixelShader * SpritePixelShader::GetPixelShader()
	{
		return m_pPixelShader;
	}

}