#include "Common/Iris2D.h"

using namespace Iris2D;

bool GameCallBack() {

	auto pGraphics = AppFactory::GetGraphics();
	auto pApp = AppFactory::GetApplication();

	//auto pViewport = ViewportDX::Create(20.0f, 20.0f, 600, 600);
	auto pBitmap = Bitmap::Create(L"image\\kurumi.jpg");
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

	pBitmap->DrawText(0, 0, 200, 200, L"Hello, World!", AlignType::Center);

	auto pSprite = Sprite::Create();
	pSprite->SetBitmap(pBitmap);
	Bitmap::Release(pBitmap);

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

	auto angle = 0.0f;
	while (!pApp->IsQuited()) {
		//pSprite->SetAngle(angle += 2.0f);
		pGraphics->Update();
	}

	//BEGIN_SAFE_LOOP()
	//	pSprite->SetAngle(angle += 1.0f);
	//END_SAFE_LOOP()
	Sprite::Release(pSprite);


	return true;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
int main(int argc, char* argv[]) {
#endif
	AppStartupInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };

	// auto pApp = ApplicationDX::Instance(); 
	AppFactory::InitApiType(ApiType::DirectX);
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
