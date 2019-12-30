#include "TestUnit.h"

using namespace Iris2D;

#ifdef _WIN32
void TestUnit::Run(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
void TestUnit::Run() {
#endif
#ifdef _WIN32
	AppStartupInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 800,
		[this]() -> bool {
			this->TestInitialize();
			this->TestMain();
			this->TestTerminate();
			return true;
		},
		L"My Iris App"
	};
#else
	AppStartupInfo iasiStartInfo = { 60u, 60u, 800, 600,
									 [this]() -> bool {
										 this->TestInitialize();
										 this->TestMain();
										 this->TestTerminate();
										 return true;
									 },
									 L"My Iris App"
	};
#endif

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
