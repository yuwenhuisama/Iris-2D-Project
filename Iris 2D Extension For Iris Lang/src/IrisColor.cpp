#include "IrisMapping/IrisColor.h"

IrisValue IrisColor::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRed = ivsValue->GetValue(0);
	auto& ivGreen = ivsValue->GetValue(1);
	auto& ivBlue = ivsValue->GetValue(2);
	auto& ivAlpha = ivsValue->GetValue(3);

	if (!IrisDev_CheckClassIsInteger(ivRed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivGreen)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivBlue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivAlpha)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nRed = IrisDev_GetInt(ivRed);
	auto nGreen = IrisDev_GetInt(ivGreen);
	auto nBlue = IrisDev_GetInt(ivBlue);
	auto nAlpha = IrisDev_GetInt(ivAlpha);

	pColor->SetInitData(nRed, nGreen, nBlue, nAlpha);

	IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);
	IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);
	IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);
	IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", ivAlpha);

	return IrisDev_Nil();
}

IrisValue IrisColor::Set(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRed = ivsValue->GetValue(0);
	auto& ivGreen = ivsValue->GetValue(1);
	auto& ivBlue = ivsValue->GetValue(2);
	auto& ivAlpha = ivsValue->GetValue(3);

	if (!IrisDev_CheckClassIsInteger(ivRed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivGreen)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivBlue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivAlpha)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nRed = IrisDev_GetInt(ivRed);
	auto nGreen = IrisDev_GetInt(ivGreen);
	auto nBlue = IrisDev_GetInt(ivBlue);
	auto nAlpha = IrisDev_GetInt(ivAlpha);

	pColor->Set(nRed, nGreen, nBlue, nAlpha);

	IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);
	IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);
	IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);
	IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", ivAlpha);

	return IrisDev_Nil();
}

IrisValue IrisColor::GetRed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@red");
}

IrisValue IrisColor::GetGreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@green");
}

IrisValue IrisColor::GetBlue(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@blue");
}

IrisValue IrisColor::GetAlpha(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@alpha");
}

IrisValue IrisColor::SetRed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRed = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivRed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nRed = IrisDev_GetInt(ivRed);

	pColor->SetRed(nRed);

	IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);

	return IrisDev_Nil();
}

IrisValue IrisColor::SetGreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivGreen = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivGreen)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nGreen = IrisDev_GetInt(ivGreen);

	pColor->SetGreen(nGreen);

	IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);

	return IrisDev_Nil();
}

IrisValue IrisColor::SetBlue(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBlue = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivBlue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nBlue = IrisDev_GetInt(ivBlue);

	pColor->SetBlue(nBlue);

	IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);

	return IrisDev_Nil();
}

IrisValue IrisColor::SetAlpha(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivAlpha = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivAlpha)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivObj);
	auto nAlpha = IrisDev_GetInt(ivAlpha);

	pColor->SetAlpha(nAlpha);

	IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", ivAlpha);

	return IrisDev_Nil();
}

void IrisColor::Mark(void * pNativePointer) {

}

const char * IrisColor::NativeClassNameDefine() const {
	return "IrisColor";
}

IIrisClass * IrisColor::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisColor::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisColor);
}
void * IrisColor::NativeAlloc() {
	return GetTravialIIrisColor();
}

void IrisColor::NativeFree(void * pNativePointer) {
	ReleaseIrisColor(static_cast<IIrisColor*>(pNativePointer));
}

void IrisColor::NativeClassDefine() {
	IrisDev_AddClassMethod(this, "__format", Initialize, 4, false);
	IrisDev_AddClassMethod(this, "set", Set, 4, false);

	IrisDev_AddGetter(this, "@red", GetRed);
	IrisDev_AddGetter(this, "@green", GetGreen);
	IrisDev_AddGetter(this, "@blue", GetBlue);
	IrisDev_AddGetter(this, "@alpha", GetAlpha);

	IrisDev_AddSetter(this, "@red", SetRed);
	IrisDev_AddSetter(this, "@green", SetGreen);
	IrisDev_AddSetter(this, "@blue", SetBlue);
	IrisDev_AddSetter(this, "@alpha", SetAlpha);
}

IrisColor::IrisColor() {

}

IrisColor::~IrisColor() {

}