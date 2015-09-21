#ifndef _H_IRISKERNEL_
#define _H_IRISKERNEL_
#include "IrisModule.h"
#include "IrisObject.h"
#include "IrisClass.h"
#include "IrisStringTag.h"
#include "IrisGC.h"
#include <iostream>
using namespace std;

extern int yyparse(void);
extern FILE *yyin;

class IrisKernel : public IrisModule
{
public:

	static IrisValue Print(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivString;
		if (ivsVariableValues) {
			for (auto elem : (*ivsVariableValues)) {
				if (elem.GetObjectPointer()->GetClass()->GetClassName() == "String") {
					ivString = elem;
				}
				else {
					ivString = elem.GetObjectPointer()->CallInstanceFunction("to_string", pContextEnvironment, nullptr);
				}
				cout << ((IrisStringTag*)ivString.GetInstanceNativePointer())->GetString();
			}
		}
		return IrisInterpreter::CurInstance()->Nil();
	}

	static IrisValue Require(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {

		IrisValue ivFile;
		IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

		if (ivsVariableValues) {
			for (auto elem : (*ivsVariableValues)) {
				const string& strFileName = ((IrisStringTag*)elem.GetInstanceNativePointer())->GetString();

				if (pInterpreter->HaveFileRequired(strFileName)) {
					continue;
				}

				IrisGC::SetGCFlag(false);

				pInterpreter->LoadScript(strFileName);

				IrisGC::ResetNextThreshold();
				IrisGC::SetGCFlag(true);

				pInterpreter->ExcuteStatements();
			}
		}

		return IrisInterpreter::CurInstance()->Nil();
	}

	static IrisValue Eval(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {

		IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
		const string& strScript = ((IrisStringTag*)((*ivsValues)[0]).GetInstanceNativePointer())->GetString();

		IrisGC::SetGCFlag(false);

		pInterpreter->LoadScriptString(strScript);

		IrisGC::ResetNextThreshold();
		IrisGC::SetGCFlag(true);

		return pInterpreter->ExcuteStatements(pContextEnvironment);
	}

public:
	IrisKernel(IrisModule* pUpperModule = nullptr);
	~IrisKernel();

private:
	void NativeClassDefine() {

		AddClassMethod(new IrisMethod("print", Print, 0, true));
		AddInstanceMethod(new IrisMethod("print", Print, 0, true));
		
		AddClassMethod(new IrisMethod("eval", Eval, 1, false));
		AddInstanceMethod(new IrisMethod("eval", Eval, 1, false));

		AddClassMethod(new IrisMethod("require", Require, 0, true));
	};

};

#endif