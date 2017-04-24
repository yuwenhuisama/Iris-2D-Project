#include "Iris2D.h"
using namespace Iris2D;

bool GameCallBack() {

	auto pGraphics = IrisGraphics::Instance();
	auto pApp = IrisApplication::Instance();

	auto pBitmap = IrisBitmap::Create(L"image\\kurumi.jpg");
	//auto pBitmap2 = IrisBitmap::Create(L"image\\leimu.jpg");

	//auto pSrcRect = IrisRect::Create2(10.0f, 10.0f, 500.0f, 400.0f);
	auto pColor = IrisColor::Create(255, 255, 255, 255);
	//pBitmap->Blt(30, 320, pBitmap2, pSrcRect, 255);

	//pBitmap->FillRect(pSrcRect, pColor);

	//pBitmap->Clear();

	//auto pPixelColor = pBitmap->GetPixel(0, 0);
	//pBitmap->SetPixel(0, 0, pColor);

	//IrisRect::Release(pSrcRect);
	IrisColor::Release(pColor);

	auto pSprite = IrisSprite::Create();
	pSprite->SetBitmap(pBitmap);
	//pSprite->SetX(800.0f);
	//pSprite->SetY(450.0f);
	//pSprite->SetAngle(0.5f);
	//pSprite->SetZoomX(0.5f);
	//pSprite->SetZoomY(0.5f);
	//pSprite->SetOX(pBitmap->GetWidth() / 2);
	//pSprite->SetOY(pBitmap->GetHeight() / 2);
	//pSprite->SetMirror(true);
	//pSprite->SetOpacity(100.0f);

	//pSprite->SetSrcRect(IrisRect::Create(30.0f, 30.0f, 300.0f, 600.0f));
	//pSprite->SetTone(IrisTone::Create(128, 0, 128, 0));

	auto angle = 0.0f;
	while (!pApp->IsQuited()) {
		//pSprite->SetAngle(angle += 1.0f);
		pGraphics->Update();
	}

	//BEGIN_SAFE_LOOP()
	//	pSprite->SetAngle(angle += 1.0f);
	//END_SAFE_LOOP()

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