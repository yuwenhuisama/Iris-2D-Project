#include "Common/Iris2D.h"

using namespace Iris2D;

bool GameCallBack() {

	auto pGraphics = AppFactory::GetGraphics();
	auto pApp = AppFactory::GetApplication();
	
	//auto pViewport = ViewportDX::Create(20.0f, 20.0f, 600, 600);
	auto pBitmap = Bitmap::Create(L"image\\kurumi.jpg");
	//auto pBitmap = Bitmap::Create(L"image\\awesomeface.png");
	//pBitmap->HueChange(90.0f);
	//auto pBitmap2 = BitmapDX::Create(L"image\\leimu.jpg");

	// pBitmap->TextSize(nullptr, L"Hello, World!");

	//auto pSrcRect = RectDX::Create2(10.0f, 10.0f, 300.0f, 300.0f);
	//pViewport->SetSrcRect(pSrcRect);
	//RectDX::Release(pSrcRect);

	//auto pColor = ColorDX::Create(0, 0, 255, 0);
	//pViewport->SetTone(pColor);
	//pBitmap->Blt(30, 320, pBitmap2, pSrcRect, 255);

	//pBitmap->FillRect(pSrcRect, pColor);

	//pBitmap->Clear();

	//auto pPixelColor = pBitmap->GetPixel(0, 0);
	//pBitmap->SetPixel(0, 0, pColor);

	// pBitmap->DrawText(0, 0, 200, 200, L"Hello, World!", AlignType::Center);

	auto pSprite = Sprite::Create();
	pSprite->SetBitmap(pBitmap);

	auto pColor = Color::Create(255, 255, 255, 255);
	auto pEffect = Effect::EffectFlash::Create(pColor, 5, true);

	pSprite->SetEffect(pEffect);

	// pSprite->SetX(400.f);
	// pSprite->SetY(300.f);
	// pSprite->SetMirror(true);
	// pSprite->SetOX(pBitmap->GetWidth() / 2);
	// pSprite->SetOY(pBitmap->GetHeight() / 2);
	 // auto pRect = Rect::Create(150.0f, 150.0f, 3000.0f, 3000.0f);
	// pSprite->SetSrcRect(pRect);

	// auto pTone = Tone::Create(0, 0, 0, 255);
	// pSprite->SetTone(pTone);

	//pSprite->SetOpacity(0.5f);
	// Bitmap::Release(pBitmap);

	//RectDX::Release(pSrcRect);
	//ColorDX::Release(pColor);
	//pSprite->SetX(800.0f);
	//pSprite->SetY(450.0f);
	//pSprite->SetAngle(0.5f);
	//pSprite->SetZoomX(0.5f);
	//pSprite->SetZoomY(0.5f);
	//pSprite->SetOX(pBitmap->GetWidth() / 2);
	//pSprite->SetOY(pBitmap->GetHeight() / 2);
	//pSprite->SetMirror(true);
	//pSprite->SetOpacity(100.0f);

	//pSprite->SetSrcRect(RectDX::Create(30.0f, 30.0f, 300.0f, 600.0f));
	//pSprite->SetTone(ToneDX::Create(128, 0, 128, 0));

	auto fAngle = 0.0f;
	auto fOpacity = 0.5f;
	unsigned char nRed = 0;
	auto bUp = true;

	while (!pApp->IsQuited()) {
		// pSprite->SetAngle(fAngle += 2.0f);

		//if (bUp) {
		//	if (nRed < 255) {
		//		nRed += 1;
		//	} else {
		//		bUp = false;
		//	}
		//} else {
		//	if (nRed > 0) {
		//		nRed -= 1;
		//	} else {
		//		bUp = true;
		//	}
		//}

		// pSprite->SetZoomX(fOpacity * 2.f);
		// pSprite->SetZoomY(fOpacity * 2.f);
		// pSprite->SetOpacity(fOpacity);
		// pSprite->GetTone()->SetRed(nRed);

		pSprite->Update();
		pGraphics->Update();
	}

	Sprite::Release(pSprite);
	//Rect::Release(pRect);
	Bitmap::Release(pBitmap);
	Effect::EffectFlash::Release(pEffect);
	Color::Release(pColor);

	return true;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
int main(int argc, char* argv[]) {
#endif
	AppStartupInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };

	AppFactory::InitApiType(ApiType::OpenGL);
	auto pApp = AppFactory::GetApplication();

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
