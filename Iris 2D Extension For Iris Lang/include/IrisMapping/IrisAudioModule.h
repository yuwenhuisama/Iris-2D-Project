#ifndef _H_IRISAUDIO_
#define _H_IRISAUDIO_

#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

#include "Iris 2D Library.h"
using namespace Iris2D;

class IrisAudioModule : public IIrisModule {
public:
	static IrisValue ModuleIrisAudioBgmPlay(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioBgsPlay(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioSePlay(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioMePlay(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioBgmStop(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioBgsStop(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioSeStop(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioMeStop(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioBgmFade(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue ModuleIrisAudioBgsFade(IrisValue& ivObj, IIrisValues* ivsValue, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	IrisAudioModule();
	~IrisAudioModule();

private:
	const char* NativeModuleNameDefine() const;

	IIrisModule* NativeUpperModuleDefine() const;

	void NativeModuleDefine();
};
#endif