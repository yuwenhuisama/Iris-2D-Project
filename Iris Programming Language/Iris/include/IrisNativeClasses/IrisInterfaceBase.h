#ifndef _H_IRISINTERFACEBASE_
#define _H_IRISINTERFACEBASE_

#include "IrisInterfaceBaseTag.h"
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisString.h"

class IrisInterfaceBase : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetInterfaceName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisInterfaceBaseTag* pInterface = (IrisInterfaceBaseTag*)ivObj.GetInstanceNativePointer();
		const string& strModuleName = pInterface->GetInterfaceName();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(strModuleName);
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisInterfaceBaseTag);
	}

	void* NativeAlloc() {
		return new IrisInterfaceBaseTag(nullptr);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisInterfaceBaseTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("interface_name", GetInterfaceName, 0, false));
	}

	IrisInterfaceBase(IrisClass* pSuperClass = nullptr);
	~IrisInterfaceBase();
};

#endif