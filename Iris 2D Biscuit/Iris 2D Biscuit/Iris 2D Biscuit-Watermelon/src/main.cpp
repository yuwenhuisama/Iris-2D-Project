#include "Iris 2D Library.h"
using namespace Iris2D;
#pragma comment(lib, "Iris 2D Biscuit-Onion(API).lib") 
IIrisApp* app = NULL;
IIrisSprite* sp = NULL;

void DecodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey2;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey1;
}

void InitResource(){
	//GetIrisEncripedResourceManager()->AddGraphResource(L"image.dat", DecodeFunction);

	sp = GetIrisSprite();
	sp->SetBitmap(GetIrisBitmap(L"image\\1.png"));
}

bool Display(){
	InitResource();
	BEGIN_IRIS_SAFE_WHILE()
		IrisGraphicsUpdate();
		IrisInputUpdate();
	END_IRIS_SAFE_WHILE()
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd){

	app = GetIrisApp();
	if (app->Init(hInstance, 800, 600, Display, L"My Iris App")){
		//ResourceInit();
		//ModuleIrisAudio::BgmPlay(L"media\\music\\おく はなこ - 兜禅.mp3", 100, 100);
		app->Run();
	}
	app->Release();
	delete app;

	return 0;
}
