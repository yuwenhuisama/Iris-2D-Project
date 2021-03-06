#include "DirectX/Iris2D/Shaders/ViewportVertexShader.h"
#include "DirectX/Iris2D/D3DResourceManager.h"


namespace Iris2D {
	ViewportVertexShader * ViewportVertexShader::Instance()
	{
		static auto pShader = ViewportVertexShader();
		return &pShader;
	}

	std::wstring ViewportVertexShader::ShaderFileDefine()
	{
		return L"shaders\\HLSL\\iris2d_viewport_vertex_shader.fx";
	}

	std::string ViewportVertexShader::ShaderEntryFuncDefine()
	{
		return "VSMain";
	}

	std::string ViewportVertexShader::ShaderVersionDefine()
	{
		return "vs_4_0";
	}

	bool ViewportVertexShader::ShaderSubResourceDefine()
	{
		auto pDevice = D3DResourceManager::Instance()->GetD3D11Device();

		D3D11_BUFFER_DESC dbdMatrix;
		memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
		dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		dbdMatrix.ByteWidth = sizeof(ViewportVertexShaderBufferDX);
		dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

		auto hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pMatrixBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pMatrixBuffer);
			return false;
		}

		dbdMatrix.ByteWidth = sizeof(DirectX::XMMATRIX);
		hResult = pDevice->CreateBuffer(&dbdMatrix, nullptr, &m_pViewProjectMatrixBuffer);
		if (FAILED(hResult)) {
			SafeCOMRelease(m_pMatrixBuffer);
			SafeCOMRelease(m_pViewProjectMatrixBuffer);
			return false;
		}

		return true;
	}

	bool ViewportVertexShader::CreateShader(ID3DBlob * pBlob)
	{
		auto hResult = D3DResourceManager::Instance()->
			GetD3D11Device()->
			CreateVertexShader(
				pBlob->GetBufferPointer(),
				pBlob->GetBufferSize(),
				nullptr,
				&m_pVertextShader);

		if (FAILED(hResult)) {
			SafeCOMRelease(m_pVertextShader);
			return false;
		}
		m_pBlob = pBlob;

		return true;
	}

	bool ViewportVertexShader::SetToContext()
	{
		D3DResourceManager::Instance()->GetD3DDeviceContext()->VSSetShader(m_pVertextShader, nullptr, 0);
		return true;
	}

	bool ViewportVertexShader::Release()
	{
		SafeCOMRelease(m_pMatrixBuffer);
		SafeCOMRelease(m_pViewProjectMatrixBuffer);
		SafeCOMRelease(m_pVertextShader);
		SafeCOMRelease(m_pInputLayout);
		return true;
	}

	bool ViewportVertexShader::CreateInputLayout()
	{
		auto pDevice = D3DResourceManager::Instance()->GetD3D11Device();

		D3D11_INPUT_ELEMENT_DESC arrVertexLayout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA , 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		 0, 16, D3D11_INPUT_PER_VERTEX_DATA , 0 },
		};
		auto nLayoutElementCount = ARRAYSIZE(arrVertexLayout);

		auto hResult = pDevice->CreateInputLayout(
			arrVertexLayout,
			nLayoutElementCount,
			m_pBlob->GetBufferPointer(),
			m_pBlob->GetBufferSize(),
			&m_pInputLayout);

		SafeCOMRelease(m_pBlob);

		if (FAILED(hResult)) {
			SafeCOMRelease(m_pInputLayout);
			return false;
		}

		return true;
	}

	ID3D11InputLayout * ViewportVertexShader::GetInputLayout()
	{
		return m_pInputLayout;
	}

	ID3D11VertexShader * ViewportVertexShader::GetVertexShader()
	{
		return m_pVertextShader;
	}

	void ViewportVertexShader::SetViewProjectMatrix(const DirectX::XMMATRIX & mxVPMatrix)
	{
		auto pContext = D3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pViewProjectMatrixBuffer, 0, nullptr, &mxVPMatrix, 0, 0);
		pContext->VSSetConstantBuffers(1, 1, &m_pViewProjectMatrixBuffer);
	}

	void ViewportVertexShader::SetWorldMatrix(const ViewportVertexShaderBufferDX & mbBuffer)
	{
		auto pContext = D3DResourceManager::Instance()->GetD3DDeviceContext();
		pContext->UpdateSubresource(m_pMatrixBuffer, 0, nullptr, &mbBuffer, 0, 0);
		pContext->VSSetConstantBuffers(0, 1, &m_pMatrixBuffer);
	}
}