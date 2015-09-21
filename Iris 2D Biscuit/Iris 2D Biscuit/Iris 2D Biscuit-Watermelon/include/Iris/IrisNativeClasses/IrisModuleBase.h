#ifndef _H_IRISMODULEBASE_
#define _H_IRISMODULEBASE_
#include "IrisClass.h"
#include "IrisModuleBaseTag.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisString.h"

class IrisModuleBase : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetModuleName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisModuleBaseTag* pModule = (IrisModuleBaseTag*)ivObj.GetInstanceNativePointer();
		const string& strModuleName = pModule->GetModuleName();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(strModuleName);
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisModuleBaseTag);
	}

	void* NativeAlloc() {
		return new IrisModuleBaseTag(nullptr);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisModuleBase*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("module_name", GetModuleName, 0, false));
	}

	IrisModuleBase(IrisClass* pSuperClass = nullptr);
	~IrisModuleBase();
};

#endif