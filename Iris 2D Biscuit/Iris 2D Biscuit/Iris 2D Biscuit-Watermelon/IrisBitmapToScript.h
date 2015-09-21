#ifndef _H_IRISBITMAPTOSCRIPT_
#define _H_IRISBITMAPTOSCRIPT_
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisStringTag.h"
#include "IrisInterpreter.h"

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisBitmapToScript : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		//ivObj.GetObjectPointer()->AddInstanceValue("@bitmap", IrisInterpreter::CurInstance()->Nil());
		const string& strFileName = ((IrisStringTag*)(*ivsValues)[0].GetInstanceNativePointer())->GetString();
		const wstring strWFileName = ((IrisStringTag*)(*ivsValues)[0].GetInstanceNativePointer())->s2ws(strFileName);
		((IIrisBitmap*)ivObj.GetInstanceNativePointer())->SetInitData(strWFileName);
		return ivObj;
	}

public:

	int GetTrustteeSize() {
		return sizeof(IIrisBitmap*);
	}

	void* NativeAlloc() {
		return GetTravialIIrisBitmap();
	}

	void NativeFree(void* pNativePointer) {
		ReleaseIrisBitmap((IIrisBitmap*)pNativePointer);
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 1, false));
	}

	IrisBitmapToScript(IrisClass* pSuperClass = nullptr);
	~IrisBitmapToScript();
};

#endif