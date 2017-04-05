#include "Iris2D\IrisShaders\IrisSimpleVertexShader.h"
#include "Iris2D\IrisD3DResourceManager.h"


std::wstring Iris2D::IrisSimpleVertexShader::ShaderFileDefine()
{
	return L"shaders\\iris2d_simple_vertex_shader.fx";
}

std::string Iris2D::IrisSimpleVertexShader::ShaderEntryFuncDefine()
{
	return "VSMain";
}

std::string Iris2D::IrisSimpleVertexShader::ShaderVersionDefine()
{
	return "vs_4_0";
}

bool Iris2D::IrisSimpleVertexShader::CreateShader(ID3DBlob * pBlob)
{
	auto hResult = IrisD3DResourceManager::Instance()->
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

bool Iris2D::IrisSimpleVertexShader::SetToContext()
{
	auto pContext = IrisD3DResourceManager::Instance()->GetD3DDeviceContext();
	
	pContext->VSSetShader(m_pVertextShader, nullptr, 0);

	auto& mVP = const_cast<DirectX::XMMATRIX&>(IrisD3DResourceManager::Instance()->GetViewMatrix());
	mVP = DirectX::XMMatrixTranspose(mVP);

	pContext->UpdateSubresource(m_pMatrixBuffer, 0, nullptr, &mVP, 0, 0);
	pContext->VSSetConstantBuffers(0, 1, &m_pMatrixBuffer);

	return true;
}

bool Iris2D::IrisSimpleVertexShader::Release()
{
	SafeCOMRelease(m_pVertextShader);
	SafeCOMRelease(m_pInputLayout);
	SafeCOMRelease(m_pMatrixBuffer);
	return true;
}

bool Iris2D::IrisSimpleVertexShader::ShaderSubResourceDefine()
{

	D3D11_BUFFER_DESC dbdMatrix;
	memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
	dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	dbdMatrix.ByteWidth = sizeof(DirectX::XMMATRIX);
	dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

	auto hResult = IrisD3DResourceManager::Instance()->
		GetD3D11Device()->CreateBuffer(&dbdMatrix, 0, &m_pMatrixBuffer);

	return true;
}

bool Iris2D::IrisSimpleVertexShader::CreateInputLayout(ID3D11Device * pDevice)
{
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

ID3D11InputLayout * Iris2D::IrisSimpleVertexShader::GetInputLayout()
{
	return m_pInputLayout;
}

ID3D11VertexShader * Iris2D::IrisSimpleVertexShader::GetVertexShader()
{
	return m_pVertextShader;
}

Iris2D::IrisSimpleVertexShader * Iris2D::IrisSimpleVertexShader::Instance()
{
	static auto pShader = IrisSimpleVertexShader();
	return &pShader;
}