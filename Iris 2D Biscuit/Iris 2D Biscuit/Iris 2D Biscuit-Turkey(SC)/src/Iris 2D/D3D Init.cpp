#include "Iris2D.h"
#include "MyLayout.h"
#include <sstream>

using namespace Iris2D;
using namespace std;

IrisApp* app;
MyLayout layout;

DWORD FramCnt = 0;
float TimeElapsed = 0;
float FPS = 0;

IrisSprite* sprite;
IrisSprite* sprite2;
IrisSprite* sprite3 = NULL;
IrisViewport* viewport1;
IrisViewport* viewport2;

IrisSprite* pSprites[100];

const int Width = 800;
const int Height = 600;

void CalcFPS(float timeDelta){

	//sprite->GetBitmap()->Clear();
	static int count = 1;
	static float fcount = 0;
	
	if (count % 60 != 0){
		++count;
		fcount += timeDelta;
		return;
	}
	else{
		count = 1;
	}

	FPS = 1000.0f / (fcount / 60);
	fcount = 0.0f;

	wostringstream ost;
	ost << FPS;
	//ost << ModuleIrisInput::GetCursorX() << "," << ModuleIrisInput::GetCursorY();
	wstring str(ost.str());
	wstring str2 = L"FPS:";
	wstring str3 = str2 + str;

	::SetWindowText(ModuleIrisGraphics::GetHwnd(), str3.c_str());

	//IrisFont* font = new IrisFont(L"宋体", 50);
	//sprite->GetBitmap()->SetFont(font);
	//sprite->GetBitmap()->IrisDrawText(0, 0, 200, 500, str2 + str, 0);
}

void DecodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey2;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey1;
}

void ResourceInit(){

//	layout.LoadXML("layout\\Layout.xml");
//
	//char* pData;
	//int nWidth, nHeight;
	//IrisEncripedResourceManager::Instance()->AddGraphResource(L"image.dat", DecodeFunction);

	BEGIN_SPRITE_BATCH_PROCESS(NULL);

	sprite3 = new IrisSprite();
	sprite3->SetBitmap(new IrisBitmap(L"image\\kurumi.jpg"));
	//sprite3->SetBlendType(1);
	//sprite3->SetBitmap(new IrisBitmap(L"image\\1.jpg"));
	//sprite3->GetBitmap()->IrisDrawText(20, 20, 200, 100, L"微软大法好", 0);
	//sprite3->SetBitmap(new IrisBitmap(pData, nWidth, nHeight));

	sprite2 = new IrisSprite();
	sprite2->SetBitmap(new IrisBitmap(L"image\\saber.jpg"));
	sprite2->SetBlendType(1);
	//sprite2->GetBitmap()->GetFont()->SetColor(new IrisColor(0, 0, 0, 255));

	//sprite = new IrisSprite();
	//sprite->SetBitmap(new IrisBitmap(78, 10));
	//sprite->SetOx(sprite->GetBitmap()->GetWidth() / 2);
	//sprite->SetOy(sprite->GetBitmap()->GetHeight() / 2);

	//sprite->SetX(200.0f);
	//sprite->SetX(0.0f);
	//sprite->SetY(0.0f);
	//sprite->SetY(200.0f);
	//sprite->SetZ(500.0f);
	//sprite->SetTone(new IrisTone(120, 0, 0, 255));

	END_SPRITE_BATCH_PROCESS(NULL);

//	sprite3 = new IrisSprite();
//	sprite3->SetBitmap(new IrisBitmap(L"image\\image\\element\\C100.png"));
//	sprite3->SetZ(100.0f);
//
//	sprite2 = new IrisSprite();
//	sprite2->SetBitmap(new IrisBitmap(L"image\\image\\element\\Ca100.png"));
//	sprite2->SetX(20.0f);
//	sprite2->SetY(20.0f);
//	sprite2->SetZ(90.0f);
}

void ResourceInit2(){

	//	layout.LoadXML("layout\\Layout.xml");
	//

	BEGIN_SPRITE_BATCH_PROCESS(NULL);

	delete sprite;
	delete sprite2;
	delete sprite3;

	//sprite3 = new IrisSprite();
	//sprite3->SetBitmap(new IrisBitmap(L"image\\kurumi.jpg"));

	//sprite2 = new IrisSprite();
	//sprite2->SetBitmap(new IrisBitmap(L"image\\saber.jpg"));

	sprite = new IrisSprite();
	sprite->SetBitmap(new IrisBitmap(L"image\\leimu.jpg"));
	sprite->SetOx(sprite->GetBitmap()->GetWidth() / 2);
	sprite->SetOy(sprite->GetBitmap()->GetHeight() / 2);

	sprite->SetX(400.0f);
	sprite->SetY(200.0f);
	sprite->SetZ(500.0f);
	sprite->SetTone(new IrisTone(120, 0, 0, 255));

	END_SPRITE_BATCH_PROCESS(NULL);

	//	sprite3 = new IrisSprite();
	//	sprite3->SetBitmap(new IrisBitmap(L"image\\image\\element\\C100.png"));
	//	sprite3->SetZ(100.0f);
	//
	//	sprite2 = new IrisSprite();
	//	sprite2->SetBitmap(new IrisBitmap(L"image\\image\\element\\Ca100.png"));
	//	sprite2->SetX(20.0f);
	//	sprite2->SetY(20.0f);
	//	sprite2->SetZ(90.0f);
}

bool Display(){
	//ModuleIrisGraphics::Transition(180, L"image\\002-Blind02.png", 40);
	//ModuleIrisGraphics::Transition(180, L"image\\1.png", 40); 
	//ModuleIrisGraphics::Transition(180, L"", 0);

	//IrisColor c(255, 255, 255, 255);
	//sprite->Flash(&c, 360);
	//sprite->Flash(NULL, 60);
	ResourceInit();
	//ModuleIrisGraphics::OnDeviceLost();
	//ModuleIrisGraphics::OnDeviceRecover();

	//ModuleIrisGraphics::Wait(30);
	//ModuleIrisGraphics::Freeze();
	//ResourceInit2();
	//ModuleIrisGraphics::Transition(180, L"image\\002-Blind02.png", 40);

	//ModuleIrisInput::Update();

	BEGIN_IRIS_SAFE_WHILE()
		//if (ModuleIrisInput::KeyBoardKeyTrigger(IR_DIK_P))
		//	ModuleIrisAudio::BgmFade(10000);

		ModuleIrisGraphics::Update();
		ModuleIrisInput::Update();

		if (ModuleIrisInput::KeyBoardKeyPress(IR_DIK_1)){
			app->ToggleWindowMode();
		}

		if (ModuleIrisInput::KeyBoardKeyPress(IR_DIK_2)){
			bool r = ModuleIrisAudio::SePlay(L"media\\se\\se.ogg", 100, 100);
			if (!r)
				::MessageBox(0, L"2", L"1", 0);
		}

		if (ModuleIrisInput::KeyBoardKeyPress(IR_DIK_3)){
			bool r = ModuleIrisAudio::SePlay(L"media\\se\\se2.ogg", 100, 100);
			if (!r)
				::MessageBox(0, L"2", L"1", 0);
		}

		//sprite->Update();

		//static bool tflag = false;

		//sprite2->SetX(ModuleIrisInput::GetCursorX());
		//sprite2->SetY(ModuleIrisInput::GetCursorY());
		//sprite->SetAngle(sprite->GetAngle() + 0.1f);

		//if (!tflag){
		//	if (sprite->GetX() < 200)
		//		sprite->SetX(sprite->GetX() + 1);
		//	else
		//		tflag = true;
		//}
		//if (tflag){
		//	if (sprite->GetX() > 20)
		//		sprite->SetX(sprite->GetX() - 1);
		//	else
		//		tflag = false;
		//}

		CalcFPS(app->GetTimeDelta());
	END_IRIS_SAFE_WHILE()
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd){

	app = IrisApp::Instance();
	IrisEncripedResourceManager::Instance()->AddGeneralResource(L"shader.dat", DecodeFunction);
	if (app->Init(hInstance, 800, 600, Display, L"My Iris App")){
		//ResourceInit();
		//ModuleIrisAudio::BgmPlay(L"media\\music\\おく はなこ - 初恋.mp3", 100, 100);
		app->Run();
	}
	app->Release();
	delete app;

	return 0;
}
