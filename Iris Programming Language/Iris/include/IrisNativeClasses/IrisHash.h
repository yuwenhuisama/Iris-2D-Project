#ifndef _H_IRISHASH_
#define _H_IRISHASH_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisHashTag.h"
#include "IrisInteger.h"

class IrisHash : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		((IrisHashTag*)ivObj.GetInstanceNativePointer())->Initialize(ivsVariableValues);
		return ivObj;
	}

	static IrisValue At(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivIndex = (*ivsValues)[0];
		return ((IrisHashTag*)ivObj.GetInstanceNativePointer())->At(ivIndex);
	}

	static IrisValue Set(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivIndex = (*ivsValues)[0];
		IrisValue ivValue = (*ivsValues)[1];
		return ((IrisHashTag*)ivObj.GetInstanceNativePointer())->Set(ivIndex, ivValue);
	}

public:

	void Mark(void* pNativeObjectPointer) {
		IrisHashTag* pHash = (IrisHashTag*)pNativeObjectPointer;
		for (auto pair : pHash->m_mpHash) {
			((IrisValue)pair.first).GetObject()->Mark();
			pair.second.GetObject()->Mark();
		}
	}

	int GetTrustteeSize() {
		return sizeof(IrisHashTag);
	}

	void* NativeAlloc() {
		return new IrisHashTag();
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisHashTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, true));
		AddInstanceMethod(new IrisMethod("[]", At, 1, false));
		AddInstanceMethod(new IrisMethod("[]=", Set, 2, false));
	}

	IrisHash(IrisClass* pSuperClass);
	~IrisHash();
};

#endif