#include "TestUnit.h"
#include <string>
#include <unordered_map>
#include <map>

#include "AnimationTest.hpp"


const std::unordered_map<std::string, TestUnit*> g_umapTestMap = {
	{ "animation", new AnimationTest() }
};


#ifdef _WIN32
void RunTest(const std::string& strTestName, HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
void RunTest(const std::string& strTestName) {
#endif
	if (g_umapTestMap.find(strTestName) != g_umapTestMap.end()) {
		auto pTestUnit = g_umapTestMap.at(strTestName);

#ifdef _WIN32
		pTestUnit->Run(hInstance, prevInstance, cmdLine, showCmd);
#else
		pTestUnit->Run();
#endif
	}
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
#else
int main(int argc, char* argv[]) {
#endif


#ifdef _WIN32
	RunTest("animation", hInstance, prevInstance, cmdLine, showCmd);
#else
	RunTest("animation");
#endif

	return 0;
}
