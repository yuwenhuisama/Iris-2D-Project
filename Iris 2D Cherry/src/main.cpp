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
#include <sstream>

using namespace Iris2D;
using namespace DirectX;

bool GameCallBack() {

	auto pGraphics = IrisGraphics::Instance();
	auto pApp = IrisApplication::Instance();

	auto pBitmap = IrisBitmap::Create(L"image\\kurumi.jpg");
	auto pSprite = IrisSprite::Create();
	pSprite->SetBitmap(pBitmap);
	pSprite->SetX(500.0f);
	pSprite->SetY(500.0f);
	//pSprite->SetAngle(0.5f);
	pSprite->SetRoomX(0.5f);
	pSprite->SetRoomY(0.5f);

	auto angle = 0.0f;
	//while (!pApp->IsQuited()) {
	//	pSprite->SetAngle(angle += 1.0f);
	//	pGraphics->Update();
	//}

	BEGIN_SAFE_LOOP()
		pSprite->SetAngle(angle += 1.0f);
	END_SAFE_LOOP()

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

	pApp->Release();

	return 0;
}