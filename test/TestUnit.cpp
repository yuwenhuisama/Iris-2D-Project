#include "TestUnit.h"

using namespace Iris2D;

#ifdef _WIN32
void TestUnit::Run(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
void TestUnit::Run() {
#endif
	AppStartupInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900,
		[this]() -> bool {
			this->TestInitialize();
			this->TestMain();
			this->TestTerminate();
			return true;
		},
		L"My Iris App"
	};

	AppFactory::InitApiType(ApiType::OpenGL);
	auto pApp = AppFactory::GetApplication();

	if (IR_FAILED(pApp->Initialize(&iasiStartInfo))) {
		pApp->Release();
		return;
	}

	if (!pApp->Run()) {
		pApp->Release();
		return;
	}

	pApp->Release();
}
