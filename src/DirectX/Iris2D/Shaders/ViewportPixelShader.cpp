#include "DirectX/Iris2D/Shaders/ViewportPixelShader.h"
#include "DirectX/Iris2D/D3DResourceManager.h"


namespace Iris2D {
	ViewportPixelShader * ViewportPixelShader::Instance()
	{
		static auto pShader = ViewportPixelShader();
		return &pShader;
	}
	std::wstring ViewportPixelShader::ShaderFileDefine()
	{
		return L"shaders\\HLSL\\iris2d_viewport_pixel_shader.fx";
	}

	std::string ViewportPixelShader::ShaderEntryFuncDefine()
	{
		return "PSMain";
	}

	std::string ViewportPixelShader::ShaderVersionDefine()
	{
		return "ps_4_0";
	}

	bool ViewportPixelShader::ShaderSubResourceDefine()
	{
		auto pDevice = D3DResourceManager::Instance()->GetD3D11Device();

		D3D11_BUFFER_DESC dbdMatrix;
		memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
		dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		dbdMatrix.ByteWidth = sizeof(ViewportPixelShaderBufferDX);
		dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

		auto hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pColorProcessBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pColorProcessBuffer);
			return false;
		}

		return true;
	}

	bool ViewportPixelShader::CreateShader(ID3DBlob * pBlob)
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

	bool ViewportPixelShader::SetToContext()
	{
		D3DResourceManager::Instance()->
			GetD3DDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
		return true;
	}

	bool ViewportPixelShader::Release()
	{
		SafeCOMRelease(m_pPixelShader);
		SafeCOMRelease(m_pColorProcessBuffer);
		return true;
	}

	ID3D11PixelShader * ViewportPixelShader::GetPixelShader()
	{
		return m_pPixelShader;
	}

	void ViewportPixelShader::SetColorProcessInfo(const ViewportPixelShaderBufferDX & ivpsInfo)
	{
		auto pContext = D3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pColorProcessBuffer, 0, nullptr, &ivpsInfo, 0, 0);
		pContext->PSSetConstantBuffers(0, 1, &m_pColorProcessBuffer);
	}
}