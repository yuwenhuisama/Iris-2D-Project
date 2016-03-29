#include "Iris 2D Library.h"
#include "IrisLangLibrary.h"
using namespace Iris2D;
#pragma comment(lib, "Iris Cerise-Spinach.lib") 
#pragma comment(lib, "IrisLangLibrary.lib")

IIrisApp* app = NULL;
IIrisSprite* sp = NULL;
void DecodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey2;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey1;
}

void InitResource() {
	//GetIrisEncripedResourceManager()->AddGraphResource(L"image.dat", DecodeFunction);

	//sp = GetIrisSprite();
	//sp->SetBitmap(GetIrisBitmap(L"image\\1.jpg"));
}

int ExitCondition() {
	return 0;
}

void ShowFatalErrorMessage(char* pMessage) {
	//cout << pMessage << endl;
	::MessageBoxA(0, pMessage, "Fatal Error", 0);
}

bool InitInterpreter() {
	IrisInitializeStruct iisInit;
	iisInit.m_pfExitConditionFunction = ExitCondition;
	iisInit.m_pfFatalErrorMessageFunction = ShowFatalErrorMessage;

	if (!IR_Initialize(&iisInit)) {
		//cout << "Error when initializing Iris!" << endl;
		::MessageBoxA(0, "Error when initializing Iris!", "Fatal Error", 0);
		return false;
	}

	IR_LoadExtention("Iris 2D Extension For Iris Lang.dll");

	return true;
}

bool Display() {
	//InitResource();
	//BEGIN_IRIS_SAFE_WHILE()
	//	IrisGraphicsUpdate();
	//	IrisInputUpdate();
	//END_IRIS_SAFE_WHILE()

	InitInterpreter();

	if (!IR_LoadScriptFromPath("script.ir")) {
		//cout << "Error when loading script!" << endl;
		::MessageBoxA(0, "Error when loading script!", "Fatal Error", 0);
		return 0;
	}
	         
	if (!IR_Run()) {
		//cout << "Error when running script!" << endl;
		::MessageBoxA(0, "Error when running script!", "Fatal Error", 0);
		return 0;
	}

	if (!IR_ShutDown()) {
		//cout << "Error when Shutting down script!" << endl;
		::MessageBoxA(0, "Error when Shutting down script!", "Fatal Error", 0);
		return 0;
	}

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd) {

	app = GetIrisApp();
	if (app->Init(hInstance, 800, 600, Display, L"My Iris App")) {
		//ResourceInit();
		//ModuleIrisAudio::BgmPlay(L"media\\music\\おく はなこ - 兜禅.mp3", 100, 100);
		app->Run();
	}
	app->Release();
	delete app;

	return 0;
}
