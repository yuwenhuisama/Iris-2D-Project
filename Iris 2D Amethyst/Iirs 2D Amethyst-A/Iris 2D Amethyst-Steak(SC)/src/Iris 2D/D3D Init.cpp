#include "Iris2D.h"
#include "MyLayout.h"

#include <sstream>

//IDirect3DDevice9 *Device = 0;

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
	//if(!(sprite2->bitmap->Disposed())){
	//	sprite2->bitmap->Dispose();
	//	sprite2->bitmap = new IrisBitmap(app->GetDevice(), 600, 100);
	//}

	sprite2->GetBitmap()->Clear();

	//FPS = 1000.0f / timeDelta;

	wostringstream ost;
	//ost << FPS;
	ost << ModuleIrisInput::GetCursorX() << "," << ModuleIrisInput::GetCursorY();
	wstring str(ost.str());
	wstring str2 = L"Cursor Position:";

	sprite2->GetBitmap()->IrisDrawText(NULL, 0, 0, 200, 500, str2 + str, 0);
}

void ResourceInit(){

	layout.LoadXML("layout\\Layout.xml");
//
//	sprite3 = new IrisSprite();
//	//viewport = new IrisViewport(0.0f, 0.0f, 800, 600);
//	//viewport->SetTone(new IrisTone(0, 0, 0, 255));
//	//sprite3->SetViewport(viewport);
//	sprite3->SetBitmap(new IrisBitmap(L"Leimu.jpg"));
//	//sprite3->SetTone(new IrisTone(0, 0, 0, 255));
//
//	//sprite3->ox = sprite3->GetBitmap()->width / 2;
//	//sprite3->oy = sprite3->GetBitmap()->height / 2;
//
//	//sprite3->SetOpacity(100.0f);
//
//	sprite2 = new IrisSprite();
//	viewport = new IrisViewport(0.0f, 0.0f, 600, 50);
//	sprite2->SetViewport(viewport);
//	sprite2->SetBitmap(new IrisBitmap(600, 50));
//
//	IrisBitmap* rbp = new IrisBitmap(20, 20);
//	IrisRect rc(200, 200, 50, 50);
//	rbp->Blt(0, 0, sprite3->GetBitmap(), &rc, 255);
//	sprite = new IrisSprite();
//	sprite->SetBitmap(rbp);
//	//sprite = new IrisSprite();
//	//sprite->SetBitmap(new IrisBitmap(L"Leimu.jpg"));
//	//sprite->SetBitmap(new IrisBitmap(app->GetDevice(), 800, 600));
//	//sprite->SetX(20);
//	//sprite->SetY(80);
//	//sprite->bitmap->IrisDrawText(NULL, 0, 0, 100, 500, L"Hello!", 0);
}

bool Display(){

	//ResourceInit();
	//sprite3->Flash(new IrisColor(120, 84, 180, 255), 60);
	
	//ModuleIrisGraphics::setBrightness(100);

	while (app->IsRunning()){

		if (ModuleIrisInput::KeyBoardKeyTrigger(DIK_P))
			ModuleIrisAudio::BgmFade(10000);

			ModuleIrisGraphics::Update();
			ModuleIrisInput::Update();

		//if (ModuleIrisInput::KeyBoardKeyRepeat(DIK_A))
		//if (ModuleIrisInput::KeyBoardKeyPress(DIK_LSHIFT)){
		//	sprite3->x += ModuleIrisInput::MouseXMove();
		//	sprite3->y += ModuleIrisInput::MouseYMove();
		//}
		//IrisRect *rect = new IrisRect(sprite3->x, sprite3->y, sprite3->GetSrcRect()->width, sprite3->GetSrcRect()->width);

		//if (ModuleIrisInput::MousePress(Left)){
		//	if (ModuleIrisInput::CursorInRect(rect)){
		//		MessageBox(0, "1", "1", 0);
		//	}
		//	IrisBitmap* bp = sprite->GetBitmap();
		//	ModuleIrisGraphics::snap2Bitmap(bp);
		//}

		//delete rect;
		//sprite->y += ModuleIrisInput::MouseMiddleRoll();
		//sprite3->angle -= 0.002;
		//sprite->angle += 0.001;
		//sprite->x += 0.01f;
		//sprite3->x -= 0.01f;

		//CalcFPS(app->GetTimeDelta());
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd){
	//app = new IrisApp;
	app = IrisApp::Instance();

	app->hInstance = hInstance;

	app->Init(hInstance, 800, 600, Display, L"My Iris App");

	ResourceInit();
	ModuleIrisAudio::BgmPlay(L"media\\music\\おく はなこ - 兜禅.mp3", 100, 100);

	app->Run();

	app->Release();

	delete app;

	return 0;
}
