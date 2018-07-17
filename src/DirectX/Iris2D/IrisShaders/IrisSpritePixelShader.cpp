#include "DirectX/Iris2D/IrisShaders/IrisSpritePixelShader.h"
#include "DirectX/Iris2D/IrisD3DResourceManager.h"


namespace Iris2D
{
	IrisSpritePixelShader * IrisSpritePixelShader::Instance()
	{
		static IrisSpritePixelShader ispsInstance;
		return &ispsInstance;
	}

	std::wstring IrisSpritePixelShader::ShaderFileDefine()
	{
		return L"shaders\\HLSL\\iris2d_sprite_pixel_shader.fx";
	}

	std::string IrisSpritePixelShader::ShaderEntryFuncDefine()
	{
		return "PSMain";
	}

	std::string IrisSpritePixelShader::ShaderVersionDefine()
	{
		return "ps_4_0";
	}

	bool IrisSpritePixelShader::ShaderSubResourceDefine()
	{
		auto pDevice = IrisD3DResourceManager::Instance()->GetD3D11Device();

		D3D11_BUFFER_DESC dbdMatrix;
		memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
		dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		dbdMatrix.ByteWidth = sizeof(IrisSpriteVertexShaderBuffer);
		dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

		auto hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pColorProcessBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pColorProcessBuffer);
			return false;
		}

		return true;
	}

	bool IrisSpritePixelShader::CreateShader(ID3DBlob * pBlob)
	{
		auto hResult = IrisD3DResourceManager::Instance()->
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

	bool IrisSpritePixelShader::SetToContext()
	{
		IrisD3DResourceManager::Instance()->
			GetD3DDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
		return true;
	}

	bool IrisSpritePixelShader::Release()
	{
		SafeCOMRelease(m_pPixelShader);
		SafeCOMRelease(m_pColorProcessBuffer);
		return true;
	}

	void IrisSpritePixelShader::SetColorProcessInfo(const IrisSpritePixelShaderBuffer & ispsInfo)
	{
		auto pContext = IrisD3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pColorProcessBuffer, 0, nullptr, &ispsInfo, 0, 0);
		pContext->PSSetConstantBuffers(0, 1, &m_pColorProcessBuffer);
	}

	ID3D11PixelShader * IrisSpritePixelShader::GetPixelShader()
	{
		return m_pPixelShader;
	}

}