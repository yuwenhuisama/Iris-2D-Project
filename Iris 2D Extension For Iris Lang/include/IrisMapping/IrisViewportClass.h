#ifndef _H_IRISVIEWPORT_
#define _H_IRISVIEWPOTY_

#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisViewportClass : public IIrisClass {
public:
	static IrisValue Initialize(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Dispose(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Disposed(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Flash(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Update(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	/*******************************************GET*****************************************************/

	static IrisValue GetX(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetY(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetWidth(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetHeight(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetRect(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetVisible(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetZ(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetOx(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetOy(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetTone(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetColor(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	/*************************************SET******************************************************/

	static IrisValue SetRect(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetVisible(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetZ(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetOx(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetOy(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetTone(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetColor(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

public:
	void Mark(void * pNativePointer);;

	const char* NativeClassNameDefine() const;

	IIrisClass* NativeSuperClassDefine() const;

	int GetTrustteeSize(void* pNativePointer);

	void* NativeAlloc();

	void NativeFree(void* pNativePointer);

	void NativeClassDefine();

	IrisViewportClass();
	~IrisViewportClass();
};
#endif