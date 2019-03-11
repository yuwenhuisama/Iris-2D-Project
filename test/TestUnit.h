#ifndef _H_TEST_UNIT_
#define _H_TEST_UNIT_

#include "Common/Iris2D.h"

using namespace Iris2D;

class TestUnit {

public:
#ifdef _WIN32
	virtual void Run(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd);
#else
	virtual void Run();
#endif
	virtual void TestInitialize() = 0;
	virtual void TestMain() = 0;
	virtual void TestTerminate() = 0;

	TestUnit() = default;
	virtual ~TestUnit() = default;
};

#endif
