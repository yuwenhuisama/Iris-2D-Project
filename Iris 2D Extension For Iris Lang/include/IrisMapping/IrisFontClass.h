#ifndef _H_IRISFONTCLASS_
#define _H_IRISFONTCLASS_

#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

#include "Iris 2D Library.h"
using namespace Iris2D;


class IrisFontClass : public IIrisClass {
public:
	static IrisValue Initialize(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetName(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetSize(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetBold(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetItalic(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetShadow(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetColor(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetName(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetSize(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetBold(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetItalic(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetShadow(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue SetColor(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisFontExisted(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment);

	static IrisValue ModuleIrisFontGetDefaultName(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);
	
	static IrisValue ModuleIrisFontGetDefaultSize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);
	
	static IrisValue ModuleIrisFontGetDefaultBold(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);
	
	static IrisValue ModuleIrisFontGetDefaultItalic(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);
	
	static IrisValue ModuleIrisFontGetDefaultShadow(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);
	
	static IrisValue ModuleIrisFontGetDefaultColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment);

public:
	void Mark(void* pNativePointer);

	const char* NativeClassNameDefine() const;

	IIrisClass* NativeSuperClassDefine() const;

	int GetTrustteeSize(void* pNativePointer);

	void* NativeAlloc();

	void NativeFree(void* pNativePointer);

	void NativeClassDefine();

	IrisFontClass();
	~IrisFontClass();
};
#endif