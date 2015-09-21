#ifndef _IRISGCCLASS_
#define _IRISGCCLASS_

#include "IrisModule.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisGC.h"

class IrisGCModule : public IrisModule
{
public:

	static IrisValue ForceStart(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisGC::ForceStart();
		return IrisInterpreter::CurInstance()->Nil();
	}

	static IrisValue SetFlag(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivFlag = (*ivsValues)[0];
		IrisGC::SetGCFlag(ivFlag == IrisInterpreter::CurInstance()->True() ? true : false);
		return IrisInterpreter::CurInstance()->Nil();;
	}

public:
	
	void NativeClassDefine() {
		AddClassMethod(new IrisMethod("start", ForceStart, 0, false));
		AddInstanceMethod(new IrisMethod("set_flag", SetFlag, 1, false));
	};


	IrisGCModule(IrisModule* pUpperModule = nullptr);
	~IrisGCModule();
};

#endif