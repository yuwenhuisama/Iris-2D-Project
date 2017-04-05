#include "Iris2D/IrisShaders/IrisSimplePixelShader.h"
#include "Iris2D\IrisD3DResourceManager.h"


Iris2D::IrisSimplePixelShader * Iris2D::IrisSimplePixelShader::Instance()
{
	static auto pInstance = IrisSimplePixelShader();
	return &pInstance;
}

std::wstring Iris2D::IrisSimplePixelShader::ShaderFileDefine()
{
	return L"shaders\\iris2d_simple_pixel_shader.fx";
}

std::string Iris2D::IrisSimplePixelShader::ShaderEntryFuncDefine()
{
	return "PSMain";
}

std::string Iris2D::IrisSimplePixelShader::ShaderVersionDefine()
{
	return "ps_4_0";
}

bool Iris2D::IrisSimplePixelShader::ShaderSubResourceDefine()
{
	return true;
}

bool Iris2D::IrisSimplePixelShader::CreateShader(ID3DBlob * pBlob)
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

bool Iris2D::IrisSimplePixelShader::SetToContext()
{
	IrisD3DResourceManager::Instance()->
		GetD3DDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
	return true;
}

ID3D11PixelShader * Iris2D::IrisSimplePixelShader::GetPixelShader()
{
	return m_pPixelShader;
}

bool Iris2D::IrisSimplePixelShader::Release()
{
	SafeCOMRelease(m_pPixelShader);
	return true;
}

Iris2D::IrisSimplePixelShader::~IrisSimplePixelShader()
{
	SafeCOMRelease(m_pPixelShader);
}