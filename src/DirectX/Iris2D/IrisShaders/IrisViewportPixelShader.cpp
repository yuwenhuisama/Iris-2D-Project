#include "DirectX/Iris2D/IrisShaders/IrisViewportPixelShader.h"
#include "DirectX/Iris2D/IrisD3DResourceManager.h"


namespace Iris2D {
	IrisViewportPixelShader * IrisViewportPixelShader::Instance()
	{
		static auto pShader = IrisViewportPixelShader();
		return &pShader;
	}
	std::wstring IrisViewportPixelShader::ShaderFileDefine()
	{
		return L"shaders\\HLSL\\iris2d_viewport_pixel_shader.fx";
	}

	std::string IrisViewportPixelShader::ShaderEntryFuncDefine()
	{
		return "PSMain";
	}

	std::string IrisViewportPixelShader::ShaderVersionDefine()
	{
		return "ps_4_0";
	}

	bool IrisViewportPixelShader::ShaderSubResourceDefine()
	{
		auto pDevice = IrisD3DResourceManager::Instance()->GetD3D11Device();

		D3D11_BUFFER_DESC dbdMatrix;
		memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
		dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		dbdMatrix.ByteWidth = sizeof(IrisViewportPixelShaderBuffer);
		dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

		auto hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pColorProcessBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pColorProcessBuffer);
			return false;
		}

		return true;
	}

	bool IrisViewportPixelShader::CreateShader(ID3DBlob * pBlob)
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

	bool IrisViewportPixelShader::SetToContext()
	{
		IrisD3DResourceManager::Instance()->
			GetD3DDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
		return true;
	}

	bool IrisViewportPixelShader::Release()
	{
		SafeCOMRelease(m_pPixelShader);
		SafeCOMRelease(m_pColorProcessBuffer);
		return true;
	}

	ID3D11PixelShader * IrisViewportPixelShader::GetPixelShader()
	{
		return m_pPixelShader;
	}

	void IrisViewportPixelShader::SetColorProcessInfo(const IrisViewportPixelShaderBuffer & ivpsInfo)
	{
		auto pContext = IrisD3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pColorProcessBuffer, 0, nullptr, &ivpsInfo, 0, 0);
		pContext->PSSetConstantBuffers(0, 1, &m_pColorProcessBuffer);
	}
}