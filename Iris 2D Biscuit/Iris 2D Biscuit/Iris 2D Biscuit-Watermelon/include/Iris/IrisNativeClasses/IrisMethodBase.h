#ifndef _H_IRISMETHODBASE_
#define _H_IRISMETHODBASE_

#include "IrisClass.h"
#include "IrisMethodBaseTag.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisString.h"

class IrisMethodBase : public IrisClass
{

public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetMethodName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisMethodBaseTag* pModule = (IrisMethodBaseTag*)ivObj.GetInstanceNativePointer();
		const string& strModuleName = pModule->GetMethodName();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(strModuleName);
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisMethodBaseTag);
	}

	void* NativeAlloc() {
		return new IrisMethodBaseTag(nullptr);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisMethodBaseTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("method_name", GetMethodName, 0, false));
	}

	IrisMethodBase(IrisClass* pSuperClass = nullptr);
	~IrisMethodBase();
};

#endif