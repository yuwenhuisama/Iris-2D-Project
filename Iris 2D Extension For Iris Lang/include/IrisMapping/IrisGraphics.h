#ifndef _H_IRISGRAPHICS_
#define _H_IRISGRAPHICS_

#include "IrisInterfaces/IIrisModule.h"
#include "IrisLangLibrary.h"
#include "Iris 2D Library.h"
using namespace Iris2D;



class IrisGraphics : public IIrisModule {
public:
	static IrisValue ModuleIrisGraphicsGetHwnd(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsGetWidth(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsGetHeight(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsUpdate(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsWait(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsFadeOut(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsFadeIn(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsFreeze(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsTransition(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsSnap2Bitmap(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsFrameReset(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsResizeScreen(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsGetFrameRate(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	/*static IrisValue ModuleIrisGraphicsSetFrameRate(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment) {
		auto& ivFrame = ivsValue->GetValue(0);

		if (!IrisDev_CheckClass(ivFrame, "Integer")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		IrisGraph

		return IrisDev_Nil();
	}*/

	static IrisValue ModuleIrisGraphicsGetFrameCount(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	/*static IrisValue ModuleIrisGraphicsSetFrameCount(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment) {
		auto& ivCount = ivsValue->GetValue(0);

		if (!IrisDev_CheckClass(ivCount, "Integer")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		auto nCount = IrisDev_GetInt(ivCount);

		IrisGraphicsSetFrameCount(nCount);

		return IrisDev_Nil();
	}*/
	
	static IrisValue ModuleIrisGraphicsGetBrightness(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisGraphicsSetBrightness(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	//------

	IrisGraphics();
	~IrisGraphics();

private:
	const char* NativeModuleNameDefine() const;

	IIrisModule* NativeUpperModuleDefine() const;

	void NativeModuleDefine();
};
#endif