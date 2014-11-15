#include "Iris2D.h"
#include "MyLayout.h"

#include <sstream>

IrisApp* app;
MyLayout layout;

DWORD FramCnt = 0;
float TimeElapsed = 0;
float FPS = 0;

IrisSprite* sprite;
IrisSprite* sprite2;
IrisSprite* sprite3 = NULL;
IrisViewport* viewport;

const int Width = 800;
const int Height = 600;

void CalcFPS(float timeDelta){

	sprite->GetBitmap()->Clear();

	FPS = 1000.0f / timeDelta;

	wostringstream ost;
	ost << FPS;
	//ost << ModuleIrisInput::GetCursorX() << "," << ModuleIrisInput::GetCursorY();
	wstring str(ost.str());
	wstring str2 = L"FPS:";

	sprite->GetBitmap()->IrisDrawText(NULL, 0, 0, 200, 500, str2 + str, 0);
}

void ResourceInit(){

//	layout.LoadXML("layout\\Layout.xml");
//
	sprite3 = new IrisSprite();
	sprite3->SetBitmap(new IrisBitmap(L"image\\leimu.jpg"));

	sprite2 = new IrisSprite();
	sprite2->SetBitmap(new IrisBitmap(L"image\\saber.jpg"));

	sprite = new IrisSprite();
	sprite->SetBitmap(new IrisBitmap(L"image\\kurumi.jpg"));
	sprite->SetTone(new IrisTone(0, 0, 0, 255));

}

bool Display(){

	ModuleIrisGraphics::transition(40, L"image\\001-Blind01.png", 0);
	//ModuleIrisGraphics::transition(40, L"", 0);

	BEGIN_IRIS_SAFE_WHILE()
		if (ModuleIrisInput::KeyBoardKeyTrigger(DIK_P))
			ModuleIrisAudio::BgmFade(10000);

		ModuleIrisGraphics::Update();
		ModuleIrisInput::Update();

		static bool tflag = false;

		if (!tflag){
			if (sprite->GetX() < 200)
				sprite->SetX(sprite->GetX() + 1);
			else
				tflag = true;
		}
		if (tflag){
			if (sprite->GetX() > 20)
				sprite->SetX(sprite->GetX() - 1);
			else
				tflag = false;
		}

		//CalcFPS(app->GetTimeDelta());
	END_IRIS_SAFE_WHILE()
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd){

	app = IrisApp::Instance();
	if (app->Init(hInstance, 800, 600, Display, L"My Iris App")){
		ResourceInit();
		ModuleIrisAudio::BgmPlay(L"media\\music\\おく はなこ - 兜禅.mp3", 100, 100);
		app->Run();
	}
	app->Release();
	delete app;

	return 0;
}
