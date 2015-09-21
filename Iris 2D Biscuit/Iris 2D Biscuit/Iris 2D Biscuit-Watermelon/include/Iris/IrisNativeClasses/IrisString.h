#ifndef _H_IRISSTRING_
#define _H_IRISSTRING_
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisStringTag.h"
#include "IrisGC.h"

class IrisString : public IrisClass
{
public:

	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue Add(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment){
		IrisValue ivValue;
		IrisStringTag* pString = (IrisStringTag*)ivObj.GetInstanceNativePointer();
		IrisStringTag* pAddedString = (IrisStringTag*)(*ivsValues)[0].GetInstanceNativePointer();
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstance(nullptr, pContextEnvironment);
		IrisStringTag* pResultString = (IrisStringTag*)ivValue.GetInstanceNativePointer();
		(*pResultString) = pString->Add(*pAddedString);
		return ivValue;
	}

public:

	static string GetString(IrisValue& ivValue) {
		return ((IrisStringTag*)ivValue.GetInstanceNativePointer())->GetString();
	}

	IrisString(IrisClass* pSuperClass = nullptr);

	int GetTrustteeSize() {
		return sizeof(IrisStringTag);
	}

	void* NativeAlloc() {
		return new IrisStringTag("");
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisStringTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("+", Add, 1, false));
	}

	IrisValue CreateInstanceByInstantValue(const string& strString) {
		IrisValue ivValue;
		IrisObject* pObject = new IrisObject();
		pObject->m_pClass = this;
		IrisStringTag* pString = new IrisStringTag(strString);
		pObject->m_pNativeObject = pString;
		ivValue.m_pObject = pObject;

		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
		IrisGC::Start();

		// 将新对象保存到堆里
		IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);
		return ivValue;
	}

	~IrisString();
};

#endif