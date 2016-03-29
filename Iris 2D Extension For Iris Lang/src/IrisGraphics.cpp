#include "IrisMapping/IrisGraphics.h"

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

IrisValue IrisGraphics::ModuleIrisGraphicsGetHwnd(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue((int)IrisGraphicsGetHwnd());
}

IrisValue IrisGraphics::ModuleIrisGraphicsGetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetWidth());
}

IrisValue IrisGraphics::ModuleIrisGraphicsGetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetHeight());
}

IrisValue IrisGraphics::ModuleIrisGraphicsUpdate(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsUpdate();
	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsWait(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsWait(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsFadeOut(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsFadeOut(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsFadeIn(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsFadeIn(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsFreeze(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsFreeze();
	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsTransition(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);
	auto& ivFilename = ivsValue->GetValue(1);
	auto& ivVague = ivsValue->GetValue(2);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClass(ivFilename, "String")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a String");
	}

	if (!IrisDev_CheckClass(ivVague, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);
	auto cFilename = IrisDev_GetString(ivFilename);

	string sFilename = string(cFilename);
	wstring wsFilename = StringToWString(sFilename);

	auto nVague = IrisDev_GetInt(ivVague);

	IrisGraphicsTransition(nDuration, wsFilename, nVague);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsSnap2Bitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBitmap = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bitmap");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivBitmap);

	IrisGraphicsSnap2Bitmap(pBitmap);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsFrameReset(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsFrameReset();
	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsResizeScreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWidth = ivsValue->GetValue(0);
	auto& ivHeight = ivsValue->GetValue(1);

	if (!IrisDev_CheckClass(ivWidth, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClass(ivHeight, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	auto nWidth = IrisDev_GetInt(ivWidth);
	auto nHeight = IrisDev_GetInt(ivHeight);

	IrisGraphicsResizeScreen(nWidth, nHeight);

	return IrisDev_Nil();
}

IrisValue IrisGraphics::ModuleIrisGraphicsGetFrameRate(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(static_cast<int>(IrisGraphicsGetFrameRate()));
}

IrisValue IrisGraphics::ModuleIrisGraphicsGetFrameCount(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetFrameCount());
}

IrisValue IrisGraphics::ModuleIrisGraphicsGetBrightness(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetBrightness());
}

IrisValue IrisGraphics::ModuleIrisGraphicsSetBrightness(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBrightness = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBrightness, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nBrightness = IrisDev_GetInt(ivBrightness);

	IrisGraphicsSetBrightness(nBrightness);

	return IrisDev_Nil();
}

const char * IrisGraphics::NativeModuleNameDefine() const {
	return "IrisGraphics";
}

IIrisModule * IrisGraphics::NativeUpperModuleDefine() const {
	return nullptr;
}

void IrisGraphics::NativeModuleDefine() {
	IrisDev_AddClassMethod(this, "get_hwnd", ModuleIrisGraphicsGetHwnd, 0, false);
	IrisDev_AddClassMethod(this, "get_width", ModuleIrisGraphicsGetWidth, 0, false);
	IrisDev_AddClassMethod(this, "get_height", ModuleIrisGraphicsGetHeight, 0, false);
	IrisDev_AddClassMethod(this, "update", ModuleIrisGraphicsUpdate, 0, false);
	IrisDev_AddClassMethod(this, "wait", ModuleIrisGraphicsWait, 1, false);
	IrisDev_AddClassMethod(this, "fade_out", ModuleIrisGraphicsFadeOut, 1, false);
	IrisDev_AddClassMethod(this, "fade_in", ModuleIrisGraphicsFadeIn, 1, false);
	IrisDev_AddClassMethod(this, "freeze", ModuleIrisGraphicsFreeze, 0, false);
	IrisDev_AddClassMethod(this, "transition", ModuleIrisGraphicsTransition, 3, false);
	IrisDev_AddClassMethod(this, "snap_2_bitmap", ModuleIrisGraphicsSnap2Bitmap, 1, false);
	IrisDev_AddClassMethod(this, "frame_reset", ModuleIrisGraphicsFrameReset, 0, false);
	IrisDev_AddClassMethod(this, "resize_screen", ModuleIrisGraphicsResizeScreen, 2, false);
	IrisDev_AddClassMethod(this, "get_frame_rate", ModuleIrisGraphicsGetFrameRate, 0, false);
	IrisDev_AddClassMethod(this, "get_frame_count", ModuleIrisGraphicsGetFrameCount, 0, false);
	IrisDev_AddClassMethod(this, "get_brightness", ModuleIrisGraphicsGetBrightness, 0, false);
	IrisDev_AddClassMethod(this, "set_brightness", ModuleIrisGraphicsSetBrightness, 1, false);

	IrisDev_AddInstanceMethod(this, "get_hwnd", ModuleIrisGraphicsGetHwnd, 0, false);
	IrisDev_AddInstanceMethod(this, "get_width", ModuleIrisGraphicsGetWidth, 0, false);
	IrisDev_AddInstanceMethod(this, "get_height", ModuleIrisGraphicsGetHeight, 0, false);
	IrisDev_AddInstanceMethod(this, "update", ModuleIrisGraphicsUpdate, 0, false);
	IrisDev_AddInstanceMethod(this, "wait", ModuleIrisGraphicsWait, 1, false);
	IrisDev_AddInstanceMethod(this, "fade_out", ModuleIrisGraphicsFadeOut, 1, false);
	IrisDev_AddInstanceMethod(this, "fade_in", ModuleIrisGraphicsFadeIn, 1, false);
	IrisDev_AddInstanceMethod(this, "freeze", ModuleIrisGraphicsFreeze, 0, false);
	IrisDev_AddInstanceMethod(this, "transition", ModuleIrisGraphicsTransition, 3, false);
	IrisDev_AddInstanceMethod(this, "snap_2_bitmap", ModuleIrisGraphicsSnap2Bitmap, 1, false);
	IrisDev_AddInstanceMethod(this, "frame_reset", ModuleIrisGraphicsFrameReset, 0, false);
	IrisDev_AddInstanceMethod(this, "resize_screen", ModuleIrisGraphicsResizeScreen, 2, false);
	IrisDev_AddInstanceMethod(this, "get_frame_rate", ModuleIrisGraphicsGetFrameRate, 0, false);
	IrisDev_AddInstanceMethod(this, "get_frame_count", ModuleIrisGraphicsGetFrameCount, 0, false);
	IrisDev_AddInstanceMethod(this, "get_brightness", ModuleIrisGraphicsGetBrightness, 0, false);
	IrisDev_AddInstanceMethod(this, "set_brightness", ModuleIrisGraphicsSetBrightness, 1, false);
}

IrisGraphics::IrisGraphics() {

}

IrisGraphics::~IrisGraphics() {

}