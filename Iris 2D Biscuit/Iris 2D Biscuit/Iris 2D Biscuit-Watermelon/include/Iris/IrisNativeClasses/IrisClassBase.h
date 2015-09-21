#ifndef _H_IRISCLASSBASE_
#define _H_IRISCLASSBASE_

#include "IrisClassBaseTag.h"
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisString.h"

class IrisClassBase : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetClassName(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		// 获取类指针
		IrisClassBaseTag* pClass = (IrisClassBaseTag*)ivObj.GetInstanceNativePointer();
		const string& strClassName = pClass->GetClassName();
		//创建String
		IrisClass* pStringClass = IrisInterpreter::CurInstance()->GetIrisClass("String");
		return pStringClass->CreateInstanceByInstantValue(strClassName);
	}

	static IrisValue New(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisClassBaseTag* pClass = (IrisClassBaseTag*)ivObj.GetInstanceNativePointer();
		IrisValues* pAllValues = nullptr;
		IrisValues ivsAllValues;
		if (ivsVariableValues){
			ivsAllValues.assign(ivsVariableValues->begin(), ivsVariableValues->end());
			pAllValues = &ivsAllValues;
		}
		return pClass->GetClass()->CreateInstance(pAllValues, pContextEnvironment);
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisClassBaseTag);
	}

	void* NativeAlloc() {
		return new IrisClassBaseTag(nullptr);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisClassBaseTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("class_name", GetClassName, 0, false));

		AddClassMethod(new IrisMethod("new", New, 0, false));
	}

	IrisClassBase(IrisClass* pSuperClass = nullptr);
	~IrisClassBase();
};

#endif