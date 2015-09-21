#ifndef _H_IRISTRUECLASS_
#define _H_IRISTRUECLASS_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisTrueClassTag.h"

class IrisTrueClass : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisTrueClassTag* pTrue = (IrisTrueClassTag*)ivObj.GetInstanceNativePointer();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(pTrue->GetName());
	}

	static IrisValue LogicNot(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return IrisInterpreter::CurInstance()->False();
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisTrueClassTag);
	}

	void* NativeAlloc() {
		return new IrisTrueClassTag();
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisTrueClassTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("name", GetName, 0, false));
		AddInstanceMethod(new IrisMethod("!", LogicNot, 0, false));
	}

	IrisTrueClass(IrisClass* pSuperClass);
	~IrisTrueClass();
};

#endif