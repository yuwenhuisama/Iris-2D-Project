#include "Iris 2D Library.h"
#include "Iris.h"
#include "IrisGC.h"

#include "IrisBitmapToScript.h"
#include "IrisSpriteToScript.h"
#include "IrisGraphicsModuleToScript.h"

using namespace Iris2D;
#pragma comment(lib, "Iris 2D Biscuit-Onion(API).lib") 
IIrisApp* app = NULL;
//IIrisSprite* sp = NULL;

char* g_pCurrentString = NULL;
int g_nCurrentStringLength = 0;
int g_nReadLength = 0;

IrisInterpreter* pInterpreter = NULL;

void DecodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey2;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey1;
}

void InitResource(){
	//GetIrisEncripedResourceManager()->AddGraphResource(L"image.dat", DecodeFunction);

	//sp = GetIrisSprite();
	//sp->SetBitmap(GetIrisBitmap(L"image\\1.png"));
}

void InitInterpreter() {

	pInterpreter = new IrisInterpreter();
	IrisInterpreter::SetCurInterpreter(pInterpreter);
	IrisGC::SetGCFlag(false);

	IrisInterpreter::CurInstance()->Initialize();

	//if (argc < 2) {
	//	return 0;
	//}

	pInterpreter->RegistClass("Bitmap", new IrisBitmapToScript(pInterpreter->GetIrisClass("Object")));
	pInterpreter->RegistClass("Sprite", new IrisSpriteToScript(pInterpreter->GetIrisClass("Object")));
	
	pInterpreter->RegistModule("Graphics", new IrisGraphicsModuleToScript());

	char* pFileName = "script\\main.ir";
	pInterpreter->LoadScript(pFileName);

	IrisGC::ResetNextThreshold();
	IrisGC::SetGCFlag(true);

}

bool Display(){
	//InitResource();
	//BEGIN_IRIS_SAFE_WHILE()
		//IrisGraphicsUpdate();
		//IrisInputUpdate();
	//END_IRIS_SAFE_WHILE()

	InitInterpreter();

	pInterpreter->ExcuteStatements();
	IrisInterpreter::CurInstance()->ShutDown();

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
