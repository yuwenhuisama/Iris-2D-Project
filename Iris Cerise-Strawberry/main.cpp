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

int ExitCondition() {
	return app->IsQuited();
}

void ShowFatalErrorMessage(char* pMessage) {
	::MessageBoxA(0, pMessage, "Fatal Error", 0);
}

IrisValue NewPrint(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisValue ivString;
	string strOut;
	if (ivsVariableValues) {
		for (size_t i = 0; i < ivsVariableValues->GetSize(); ++i) {
			auto& elem = ivsVariableValues->GetValue(i);
			if (IrisDev_CheckClassIsString(elem)) {
				strOut += IrisDev_GetString(elem);
			}
			else if (IrisDev_CheckClassIsUniqueString(elem)) {
				strOut += IrisDev_GetString(elem);
			}
			else {
				ivString = IrisDev_CallMethod(elem, nullptr, "to_string");
				strOut += IrisDev_GetString(ivString);
			}
		}
	}
	::MessageBoxA(0, strOut.c_str(), "Message", 0);
	return IrisDev_Nil();
}

void CoverPrintMethod() {
	IIrisModule* pKernelModule = IrisDev_GetModule("Kernel");
	IrisDev_AddInstanceMethod(pKernelModule, "print", NewPrint, 0, true);
	IrisDev_AddClassMethod(pKernelModule, "print", NewPrint, 0, true);
}

bool InitInterpreter() {
	IrisInitializeStruct iisInit;
	iisInit.m_pfExitConditionFunction = ExitCondition;
	iisInit.m_pfFatalErrorMessageFunction = ShowFatalErrorMessage;

	if (!IR_Initialize(&iisInit)) {
		::MessageBoxA(0, "Error when initializing Iris!", "Fatal Error", 0);
		return false;
	}

	IR_LoadExtention("Iris 2D Extension For Iris Lang.dll");

	CoverPrintMethod();

	return true;
}

bool Display() {
	InitInterpreter();

	if (!IR_LoadScriptFromPath("script/main.ir")) {
		::MessageBoxA(0, "Error when loading script!", "Fatal Error", 0);
		return 0;
	}
	         
	if (!IR_Run()) {
		::MessageBoxA(0, "Error when running script!", "Fatal Error", 0);
		return 0;
	}

	if (!IR_ShutDown()) {
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
		app->Run();
	}
	app->Release();
	delete app;

	return 0;
}
