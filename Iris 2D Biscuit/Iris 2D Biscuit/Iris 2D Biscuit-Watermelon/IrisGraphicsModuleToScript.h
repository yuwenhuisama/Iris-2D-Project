#ifndef _H_IRISGRAPHICSMODULETOSCRIPT_
#define _H_IRISGRAPHICSMODULETOSCRIPT_

#include "IrisModule.h"
#include "IrisObject.h"
#include "IrisClass.h"
#include "IrisInterpreter.h"

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisGraphicsModuleToScript : public IrisModule
{
public:
	static IrisValue Update(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisGraphicsUpdate();
		return  IrisInterpreter::CurInstance()->Nil();
	}


public:
	IrisGraphicsModuleToScript(IrisModule* pUpperModule = nullptr);
	~IrisGraphicsModuleToScript();

private:
	void NativeClassDefine() {
		AddClassMethod(new IrisMethod("update", Update, 0, false));
	};

};

#endif