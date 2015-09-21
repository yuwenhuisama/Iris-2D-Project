#ifndef _H_IRISSPRITETOSCRIPT_
#define _H_IRISSPRITETOSCRIPT_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisSpriteToScript : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		((IIrisSprite*)ivObj.GetInstanceNativePointer())->SetInitData(NULL);
		ivObj.GetObjectPointer()->AddInstanceValue("@bitmap", IrisInterpreter::CurInstance()->Nil());
		return ivObj;
	}

	static IrisValue GetBitmap(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		bool bResult;
		return ivObj.GetObjectPointer()->GetInstanceValue("@bitmap", bResult);
	}

	static IrisValue SetBitmap(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		bool bResult;
		((IrisValue&)ivObj.GetObjectPointer()->GetInstanceValue("@bitmap", bResult)).SetObject((*ivsValues)[0].GetObjectPointer());
		((IIrisSprite*)ivObj.GetInstanceNativePointer())->SetBitmap(((IIrisBitmap*)(*ivsValues)[0].GetInstanceNativePointer()));
		return ((*ivsValues)[0]);
	}


public:

	int GetTrustteeSize() {
		return sizeof(IIrisSprite*);
	}

	void* NativeAlloc() {
		return GetTravialIIrisSprite();
	}

	void NativeFree(void* pNativePointer) {
		ReleaseIrisSprite((IIrisSprite*)pNativePointer);
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, true));

		AddGetter("@bitmap", GetBitmap);
		AddSetter("@bitmap", SetBitmap);
	}

	IrisSpriteToScript(IrisClass* pSuperClass = nullptr);
	~IrisSpriteToScript();
};

#endif