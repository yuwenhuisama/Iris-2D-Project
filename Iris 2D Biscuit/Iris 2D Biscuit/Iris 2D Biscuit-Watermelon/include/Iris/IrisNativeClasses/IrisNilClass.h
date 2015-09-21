#ifndef _H_IRISNILCLASS_
#define _H_IRISNILCLASS_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisNilClassTag.h"

class IrisNilClass : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisNilClassTag* pTrue = (IrisNilClassTag*)ivObj.GetInstanceNativePointer();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(pTrue->GetName());
	}

	static IrisValue LogicNot(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return IrisInterpreter::CurInstance()->True();
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisNilClassTag);
	}

	void* NativeAlloc() {
		return new IrisNilClassTag();
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisNilClassTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("name", GetName, 0, false));
		AddInstanceMethod(new IrisMethod("!", LogicNot, 0, false));
	}

	IrisNilClass(IrisClass* pSuperClass);
	~IrisNilClass();
};

#endif