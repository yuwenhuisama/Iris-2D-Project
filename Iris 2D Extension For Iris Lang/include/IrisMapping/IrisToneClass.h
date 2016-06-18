#ifndef _H_IRISTONE_
#define _H_IRISTONE_

#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisToneClass : public IIrisClass {
public:
	static IrisValue Set(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvitonment);

	static IrisValue GetRed(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue GetGreen(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue GetBlue(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue GetAlpha(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue SetRed(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue SetGreen(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue SetBlue(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

	static IrisValue SetAlpha(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironmet);

public:
	void Mark(void * pNativePointer);

	const char* NativeClassNameDefine() const;

	IIrisClass* NativeSuperClassDefine() const;

	int GetTrustteeSize(void* pNativePointer);

	void* NativeAlloc();

	void NativeFree(void* pNativePointer);

	void NativeClassDefine();

	IrisToneClass();
	~IrisToneClass();
};
#endif