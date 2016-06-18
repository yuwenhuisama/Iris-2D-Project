#include "IrisMapping\IrisAudioModule.h"


std::string WStringToString(const std::wstring &wstr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

std::wstring StringToWString(const std::string &str)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), 0, 0);
	if (nSize <= 0) return NULL;
	WCHAR *pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst) return NULL;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pwszDst, nSize);
	pwszDst[nSize] = 0;
	if (pwszDst[0] == 0xFEFF)                    // skip Oxfeff
		for (int i = 0; i < nSize; i++)
			pwszDst[i] = pwszDst[i + 1];
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}

float GetFloatWhateverFloatOrInteger(const IrisValue& ivValue) {
	if (IrisDev_CheckClassIsFloat(ivValue)) {
		return static_cast<float>(IrisDev_GetFloat(ivValue));
	}
	else if (IrisDev_CheckClassIsInteger(ivValue)) {
		return static_cast<float>(IrisDev_GetInt(ivValue));
	}
	return 0.0f;
}

IrisValue IrisAudioModule::ModuleIrisAudioBgmPlay(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFilePath = ivsValue->GetValue(0);
	auto& ivVolume = ivsValue->GetValue(1);
	auto& ivRate = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsString(ivFilePath)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivVolume)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivRate)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		return IrisDev_Nil();
	}

	auto cFilePath = IrisDev_GetString(ivFilePath);
	string sFilePath = string(cFilePath);
	wstring wsFilePath = StringToWString(sFilePath);
	auto nVolume = IrisDev_GetInt(ivVolume);
	auto nRate = IrisDev_GetInt(ivRate);

	return IrisAudioBgmPlay(wsFilePath, nVolume, nRate) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioBgsPlay(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFilePath = ivsValue->GetValue(0);
	auto& ivVolume = ivsValue->GetValue(1);
	auto& ivRate = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsString(ivFilePath)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivVolume)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivRate)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		return IrisDev_Nil();
	}

	auto cFilePath = IrisDev_GetString(ivFilePath);
	string sFilePath = string(cFilePath);
	wstring wsFilePath = StringToWString(sFilePath);
	auto nVolume = IrisDev_GetInt(ivVolume);
	auto nRate = IrisDev_GetInt(ivRate);

	return IrisAudioBgsPlay(wsFilePath, nVolume, nRate) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioSePlay(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFilePath = ivsValue->GetValue(0);
	auto& ivVolume = ivsValue->GetValue(1);
	auto& ivRate = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsString(ivFilePath)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivVolume)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivRate)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		return IrisDev_Nil();
	}

	auto cFilePath = IrisDev_GetString(ivFilePath);
	string sFilePath = string(cFilePath);
	wstring wsFilePath = StringToWString(sFilePath);
	auto nVolume = IrisDev_GetInt(ivVolume);
	auto nRate = IrisDev_GetInt(ivRate);

	return IrisAudioSePlay(wsFilePath, nVolume, nRate) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioMePlay(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFilePath = ivsValue->GetValue(0);
	auto& ivVolume = ivsValue->GetValue(1);
	auto& ivRate = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsString(ivFilePath)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivVolume)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivRate)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		return IrisDev_Nil();
	}

	auto cFilePath = IrisDev_GetString(ivFilePath);
	string sFilePath = string(cFilePath);
	wstring wsFilePath = StringToWString(sFilePath);
	auto nVolume = IrisDev_GetInt(ivVolume);
	auto nRate = IrisDev_GetInt(ivRate);

	return IrisAudioMePlay(wsFilePath, nVolume, nRate) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioBgmStop(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisAudioBgmStop() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioBgsStop(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisAudioBgsStop() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioSeStop(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisAudioSeStop() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioMeStop(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisAudioMeStop() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioBgmFade(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFadeTime = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivFadeTime)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto nFadeTime = IrisDev_GetInt(ivFadeTime);

	return IrisAudioBgmFade(nFadeTime) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisAudioModule::ModuleIrisAudioBgsFade(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFadeTime = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivFadeTime)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto nFadeTime = IrisDev_GetInt(ivFadeTime);

	return IrisAudioBgsFade(nFadeTime) ? IrisDev_True() : IrisDev_False();
}

const char * IrisAudioModule::NativeModuleNameDefine() const {
	return "Audio";
}

IIrisModule * IrisAudioModule::NativeUpperModuleDefine() const {
	return nullptr;
}

void IrisAudioModule::NativeModuleDefine() {
	IrisDev_AddClassMethod(this, "bgm_play", ModuleIrisAudioBgmPlay, 3, false);
	IrisDev_AddClassMethod(this, "bgs_play", ModuleIrisAudioBgsPlay, 3, false);
	IrisDev_AddClassMethod(this, "se_play", ModuleIrisAudioSePlay, 3, false);
	IrisDev_AddClassMethod(this, "me_play", ModuleIrisAudioMePlay, 3, false);
	IrisDev_AddClassMethod(this, "bgm_stop", ModuleIrisAudioBgmStop, 0, false);
	IrisDev_AddClassMethod(this, "bgs_stop", ModuleIrisAudioBgsStop, 0, false);
	IrisDev_AddClassMethod(this, "se_stop", ModuleIrisAudioSeStop, 0, false);
	IrisDev_AddClassMethod(this, "me_stop", ModuleIrisAudioMeStop, 0, false);
	IrisDev_AddClassMethod(this, "bgm_fade", ModuleIrisAudioBgmFade, 1, false);
	IrisDev_AddClassMethod(this, "bgs_fade", ModuleIrisAudioBgsFade, 1, false);
}

IrisAudioModule::IrisAudioModule() {

}

IrisAudioModule::~IrisAudioModule() {

}