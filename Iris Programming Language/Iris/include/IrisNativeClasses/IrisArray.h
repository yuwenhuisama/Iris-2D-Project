#ifndef _H_IRISARRAY_
#define _H_IRISARRAY_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisArrayTag.h"
#include "IrisInteger.h"
#include "IrisClosureBlock.h"

class IrisArray : public IrisClass
{

public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		((IrisArrayTag*)ivObj.GetInstanceNativePointer())->Initialize(ivsVariableValues);
		return ivObj;
	}

	static IrisValue At(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivIndex = (*ivsValues)[0];
		return ((IrisArrayTag*)ivObj.GetInstanceNativePointer())->At(IrisInteger::GetIntData(ivIndex));
	}

	static IrisValue Set(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivIndex = (*ivsValues)[0];
		IrisValue ivValue = (*ivsValues)[1];
		return ((IrisArrayTag*)ivObj.GetInstanceNativePointer())->Set(IrisInteger::GetIntData(ivIndex), ivValue);
	}

	static IrisValue Each(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pClosureBlock;
		IrisValues ivValues;
		for (auto elem : ((IrisArrayTag*)ivObj.GetInstanceNativePointer())->m_vcValues) {
			ivValues.push_back(elem);
			pClosureBlock->Excute(&ivValues);
			ivValues.clear();
		}
		return IrisInterpreter::CurInstance()->Nil();
	}

	static IrisValue Push(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ((IrisArrayTag*)ivObj.GetInstanceNativePointer())->Push((*ivsValues)[0]);
	}

	static IrisValue Pop(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ((IrisArrayTag*)ivObj.GetInstanceNativePointer())->Pop();
	}

	static IrisValue Size(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstanceByInstantValue(((IrisArrayTag*)ivObj.GetInstanceNativePointer())->Size());
	}

public:

	int GetTrustteeSize() {
		return sizeof(IrisArrayTag);
	}

	void Mark(void* pNativeObjectPointer) {
		IrisArrayTag* pArray = (IrisArrayTag*)pNativeObjectPointer;
		for (auto value : pArray->m_vcValues) {
			value.GetObject()->Mark();
		}
	}

	void* NativeAlloc() {
		return new IrisArrayTag();
	}

	void NativeFree(void* pNativePointer){
		delete (IrisArrayTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, true));
		AddInstanceMethod(new IrisMethod("[]", At, 1, false));
		AddInstanceMethod(new IrisMethod("[]=", Set, 2, false));

		AddInstanceMethod(new IrisMethod("push", Push, 1, false));
		AddInstanceMethod(new IrisMethod("pop", Pop, 0, false));
		AddInstanceMethod(new IrisMethod("each", Each, 0, false));

		AddGetter("@size", Size);
	}

	IrisArray(IrisClass* pSuperClasss = nullptr);
	~IrisArray();
};

#endif