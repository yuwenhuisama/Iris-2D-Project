#include "Iris.h"
#include "IrisGC.h"
#include <iostream>
using namespace std;

extern int yyparse(void);
extern FILE *yyin;

char* g_pCurrentString = NULL;
int g_nCurrentStringLength = 0;
int g_nReadLength = 0;

int main(int argc, char* argv[]) {

	IrisInterpreter* pInterpreter = new IrisInterpreter();
	IrisInterpreter::SetCurInterpreter(pInterpreter);
	IrisGC::SetGCFlag(false);

	IrisInterpreter::CurInstance()->Initialize();

	//if (argc < 2) {
	//	return 0;
	//}

	char* pFileName = "script\\test1.ir";
	pInterpreter->LoadScript(pFileName);

	IrisGC::ResetNextThreshold();
	IrisGC::SetGCFlag(true);

	pInterpreter->ExcuteStatements();
 	IrisInterpreter::CurInstance()->ShutDown();

	return 0;
}