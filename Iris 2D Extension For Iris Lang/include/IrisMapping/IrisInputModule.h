#ifndef _H_IRISINPUT_
#define _H_IRISINPUT_

#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisInputModule : public IIrisModule {
public:
	static IrisValue ModuleIrisInputUpdate(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputKeyBoardKeyPress(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputKeyBoardKeyTrigger(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputKeyBoardKeyRepeat(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMousePress(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMouseTrigger(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMouseRepeat(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMouseMiddleRoll(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMouseXMove(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputMouseYMove(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputGetCursorX(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputGetCursorY(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	static IrisValue ModuleIrisInputCursorInRect(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContetxtEnvironment);

	IrisInputModule();
	~IrisInputModule();

private:
	const char* NativeModuleNameDefine() const;

	IIrisModule* NativeUpperModuleDefine() const;

	void NativeModuleDefine();
};
#endif