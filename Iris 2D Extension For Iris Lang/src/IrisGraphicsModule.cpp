#include "IrisMapping/IrisGraphicsModule.h"

std::string WStringToString(const std::wstring &wstr);

std::wstring StringToWString(const std::string &str);

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetHwnd(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue((int)IrisGraphicsGetHwnd());
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetWidth());
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetHeight());
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsUpdate(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsUpdate();
	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsWait(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsWait(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsFadeOut(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsFadeOut(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsFadeIn(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDuration = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivDuration, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nDuration = IrisDev_GetInt(ivDuration);

	IrisGraphicsFadeIn(nDuration);

	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsFreeze(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsFreeze();
	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsTransition(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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

IrisValue IrisGraphicsModule::ModuleIrisGraphicsSnap2Bitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBitmap = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bitmap");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivBitmap);

	IrisGraphicsSnap2Bitmap(pBitmap);

	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsFrameReset(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	IrisGraphicsFrameReset();
	return IrisDev_Nil();
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsResizeScreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetFrameRate(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(static_cast<int>(IrisGraphicsGetFrameRate()));
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetFrameCount(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetFrameCount());
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsGetBrightness(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisGraphicsGetBrightness());
}

IrisValue IrisGraphicsModule::ModuleIrisGraphicsSetBrightness(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBrightness = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBrightness, "Integer")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto nBrightness = IrisDev_GetInt(ivBrightness);

	IrisGraphicsSetBrightness(nBrightness);

	return IrisDev_Nil();
}

const char * IrisGraphicsModule::NativeModuleNameDefine() const {
	return "Graphics";
}

IIrisModule * IrisGraphicsModule::NativeUpperModuleDefine() const {
	return nullptr;
}

void IrisGraphicsModule::NativeModuleDefine() {
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

IrisGraphicsModule::IrisGraphicsModule() {

}

IrisGraphicsModule::~IrisGraphicsModule() {

}