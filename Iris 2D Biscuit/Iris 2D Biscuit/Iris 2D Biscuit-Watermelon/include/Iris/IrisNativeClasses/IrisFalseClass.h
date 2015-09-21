#ifndef _H_IRISFALSECLASS_
#define _H_IRISFALSECLASS_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisFalseClassTag.h"

class IrisFalseClass : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisFalseClassTag* pTrue = (IrisFalseClassTag*)ivObj.GetInstanceNativePointer();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(pTrue->GetName());
	}

	static IrisValue LogicNot(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return IrisInterpreter::CurInstance()->True();
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisFalseClassTag);
	}

	void* NativeAlloc() {
		return new IrisFalseClassTag();
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisFalseClassTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("name", GetName, 0, false));
		AddInstanceMethod(new IrisMethod("!", LogicNot, 0, false));
	}

	IrisFalseClass(IrisClass* pSuperClass);
	~IrisFalseClass();
};

#endif