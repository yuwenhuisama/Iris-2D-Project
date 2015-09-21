#ifndef _H_IRISCLOSUREBLOCKBASE_
#define _H_IRISCLOSUREBLOCKBASE_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisClosureBlockBaseTag.h"

class IrisClosureBlockBase : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {

		IrisClosureBlock* pClosureBlock = nullptr;
		if (pContextEnvironment) {
			pClosureBlock = pContextEnvironment->m_pClosureBlock;
		} else {
			pClosureBlock = IrisInterpreter::CurInstance()->GetMainClosureBlock();
		}
		((IrisClosureBlockBaseTag*)ivObj.GetInstanceNativePointer())->SetClosureBlock(pClosureBlock);

		IrisContextEnvironment* pTmpEnv =  pClosureBlock->m_pCurContextEnvironment;
		while (pTmpEnv) {
			++pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}

		pContextEnvironment->m_pClosureBlock = nullptr;

		return ivObj;
	}

	static IrisValue Call(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ((IrisClosureBlockBaseTag*)ivObj.GetInstanceNativePointer())->GetClosureBlock()->Excute(ivsVariableValues).m_ivValue;
	}

public:

	void Mark(void* pNativeObjectPointer) {
		IrisClosureBlockBaseTag* pClosureBlock = (IrisClosureBlockBaseTag*)pNativeObjectPointer;
		pClosureBlock->GetClosureBlock()->Mark();
	}

	int GetTrustteeSize() {
		return sizeof(IrisClosureBlockBaseTag);
	}

	void* NativeAlloc() {
		return new IrisClosureBlockBaseTag(nullptr);
	}

	void NativeFree(void* pNativePointer) {

		IrisContextEnvironment* pTmpEnv = ((IrisClosureBlockBaseTag*)pNativePointer)->GetClosureBlock()->m_pCurContextEnvironment;
		while (pTmpEnv) {
			//pTmpEnv->m_bIsReferenced = false;
			--pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}

		delete ((IrisClosureBlockBaseTag*)pNativePointer)->GetClosureBlock();
		delete (IrisClosureBlockBaseTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("call", Call, 0, true));
	}

	IrisClosureBlockBase(IrisClass* pSuperClass);
	~IrisClosureBlockBase();
};

#endif