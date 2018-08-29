#include "Common/Iris2D.h"

using namespace Iris2D;

bool GameCallBack() {

	auto pGraphics = AppFactory::GetGraphics();
	auto pApp = AppFactory::GetApplication();
	
	auto pViewport = Viewport::Create(20.0f, 20.0f, 1000, 1000);
	pViewport->SetZ(1.0f);

	auto pBitmap = Bitmap::Create(L"image\\kurumi.jpg");
	auto pSprite = Sprite::Create(pViewport);
	pSprite->SetBitmap(pBitmap);
	pSprite->SetZ(4.0f);

	auto pBitmap2 = Bitmap::Create(L"image\\leimu.jpg");
	auto pSprite2 = Sprite::Create(pViewport);
	pSprite2->SetX(50.0f);
	pSprite2->SetBitmap(pBitmap2);
	pSprite2->SetZ(5.0f);

	auto pColor = Color::Create(255, 255, 255, 255);
	auto pEffect = Effect::EffectFlash::Create(pColor, 2, true);

	pSprite->SetEffect(pEffect);

	auto fAngle = 0.0f;
	auto fBrightness = 0.0f;
	auto bUp = true;
	auto nCounter = 0;

	//pGraphics->FadeIn(50);
	//pGraphics->FadeOut(50);

	while (!pApp->IsQuited()) {
		//fAngle += 2.0f;
		//pSprite->SetAngle(fAngle);
		//pSprite2->SetAngle(-fAngle);

		//if (bUp) {
		//	if (fBrightness < 1.0f) {
		//		fBrightness += 0.01f;
		//	} else {
		//		bUp = false;
		//	}
		//} else {
		//	if (fBrightness > 0.0f) {
		//		fBrightness -= 0.01f;
		//	} else {
		//		bUp = true;
		//	}
		//}

		// pSprite->SetZoomX(fOpacity * 2.f);
		// pSprite->SetZoomY(fOpacity * 2.f);
		// pSprite->SetOpacity(fOpacity);
		// pSprite->GetTone()->SetRed(nRed);

		pSprite->Update();
		//pGraphics->SetBrightness(fBrightness);
		pGraphics->Update();

		//if (nCounter == 10) {
		//	pGraphics->Freeze();
		//}

		//if (nCounter == 20) {
		//	pGraphics->Transition(240, L"", 10);
		//}

		if (nCounter == 60) {
			pGraphics->ResizeScreen(300, 300);
		} else if (nCounter == 120) {
			pGraphics->ResizeScreen(600, 600);
		} else if (nCounter == 180) {
			pGraphics->ResizeScreen(1200, 1200);
		}

		++nCounter;
	}

	Sprite::Release(pSprite);
	Sprite::Release(pSprite2);
	//Rect::Release(pRect);
	Bitmap::Release(pBitmap);
	Bitmap::Release(pBitmap2);
	Effect::EffectFlash::Release(pEffect);
	Color::Release(pColor);
	Viewport::Release(pViewport);

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

	if (IR_FAILED(pApp->Initialize(&iasiStartInfo))) {
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
