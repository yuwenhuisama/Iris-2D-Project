#include "Iris2D/IrisApp.h"
#include "Iris2D/IrisGraphics.h"
#include "Iris2D Util/IrisSpriteVertex.h"
#include "Iris2D/IrisD3DresourceManager.h"
#include "Iris2D Util/IrisTexture.h"
#include "Iris2D/IrisShaders/IrisSimplePixelShader.h"
#include "Iris2D/IrisShaders/IrisSimpleVertexShader.h"
#include "Iris2D/IrisBitmap.h"
#include "Iris2D/IrisSprite.h"
#include <DirectXMath.h>

using namespace Iris2D;
using namespace DirectX;

ID3D11Buffer* g_pVertexBuffer = nullptr;
IrisTexture* g_pTexture = nullptr;
bool CreateSprite() {

	//** Vertex Buffer
	IrisSpriteVertex arrVertices[] = {
		{ XMFLOAT4(100.0f, 100.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT4(100.0f, -100.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT4(-100.0f, -100.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT4(-100.0f, -100.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT4(-100.0f, 100.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT4(100.0f, 100.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
	};

	D3D11_BUFFER_DESC dbdVertextDesc;
	memset(&dbdVertextDesc, 0, sizeof(D3D11_BUFFER_DESC));

	dbdVertextDesc.Usage = D3D11_USAGE_DEFAULT;
	dbdVertextDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	dbdVertextDesc.ByteWidth = sizeof(IrisSpriteVertex) * 6;

	D3D11_SUBRESOURCE_DATA dsdResourceData;
	memset(&dsdResourceData, 0, sizeof(D3D11_SUBRESOURCE_DATA));

	dsdResourceData.pSysMem = arrVertices;

	auto pD3DManager = IrisD3DResourceManager::Instance();
	auto hResult = pD3DManager->GetD3D11Device()->CreateBuffer(&dbdVertextDesc, &dsdResourceData, &g_pVertexBuffer);
	if (FAILED(hResult)) {
		SafeCOMRelease(g_pVertexBuffer);
		return false;
	}

	//** Shader
	auto pVertexShader = IrisSimpleVertexShader::Instance();
	
	if (!pVertexShader->Initialize()) {
		return false;
	}

	if (!pVertexShader->CreateInputLayout(pD3DManager->GetD3D11Device())) {
		return false;
	}
	pD3DManager->SetVertexShader(pVertexShader);
	
	auto pPixelShader = IrisSimplePixelShader::Instance();

	if (!pPixelShader->Initialize()) {
		return false;
	}
	pD3DManager->SetPixelShader(pPixelShader);

	unsigned int nStride = sizeof(IrisSpriteVertex);
	unsigned int nOffset = 0;

	pD3DManager->SetCurrentVertexBufferInfo(nStride, nOffset, g_pVertexBuffer);

	g_pTexture = IrisTexture::Create(L"image\\kurumi.jpg");
	pD3DManager->SetCurrentTexture(g_pTexture);

	return true;
}

bool GameCallBack() {

	auto pGraphics = IrisGraphics::Instance();
	auto pApp = IrisApplication::Instance();
	//auto pD3DManager = IrisD3DResourceManager::Instance();

	//auto pContext = pD3DManager->GetD3DDeviceContext();
	//auto pBackBuffer = pD3DManager->GetRenderTargetView();
	//auto pSwapChain = pD3DManager->GetSwapChain();

	//CreateSprite();
	auto pBitmap = IrisBitmap::Create(L"image\\kurumi.jpg");
	auto pSprite = IrisSprite::Create();
	pSprite->SetBitmap(pBitmap);
	pSprite->SetX(500.0f);
	pSprite->SetY(500.0f);
	//pSprite->SetAngle(0.5f);
	pSprite->SetRoomX(0.5f);
	pSprite->SetRoomY(0.5f);

	auto angle = 0.0f;
	while (!pApp->IsQuited()) {
		pSprite->SetAngle(angle += 1.0f);
		pGraphics->Update();
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

	IrisApplication::IrisAppStartInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };

	auto pApp = IrisApplication::Instance(); 

	if (!pApp->Initialize(&iasiStartInfo)) {
		pApp->Release();
		return -1;
	}

	if (!pApp->Run()) {
		pApp->Release();
		return -1;
	}


	//SafeCOMRelease(g_pVertexBuffer);
	//IrisTexture::Release(g_pTexture);
	pApp->Release();
	//delete IrisSimplePixelShader::Instance();
	//delete IrisSimpleVertexShader::Instance();

	/*
	delete VertexShader
	delete VertexShader
	delete Buffer
	delete InputLayout
	
	*/

	return 0;
}