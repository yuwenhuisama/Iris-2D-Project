#include "IrisMapping\IrisToneClass.h"
float GetFloatWhateverFloatOrInteger(const IrisValue& ivValue);

IrisValue IrisToneClass::Set(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvitonment) {
	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivObj);

	auto& ivRed = ivsValue->GetValue(0);
	auto& ivGreen = ivsValue->GetValue(1);
	auto& ivBlue = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsInteger(ivRed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Integer");
		return ivObj;
	}

	if (!IrisDev_CheckClassIsInteger(ivGreen)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return ivObj;
	}

	if (!IrisDev_CheckClassIsInteger(ivBlue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		return ivObj;
	}

	auto nRed = IrisDev_GetInt(ivRed);
	auto nGreen = IrisDev_GetInt(ivGreen);
	auto nBlue = IrisDev_GetInt(ivBlue);

	if (ivsVariableValues->GetSize() == 0) {
		pTone->set(nRed, nGreen, nBlue);

		IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);
		IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);
		IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);
		IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", IrisDev_CreateIntegerInstanceByInstantValue(255));

		return ivObj;
	}
	else if (ivsVariableValues && ivsVariableValues->GetSize() == 1) {
		auto& ivAlpha = ivsVariableValues->GetValue(0);

		if (!IrisDev_CheckClassIsInteger(ivAlpha)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
			return IrisDev_Nil();
		}

		auto nAlpha = IrisDev_GetInt(ivAlpha);

		pTone->set(nRed, nRed, nRed, nAlpha);

		IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);
		IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);
		IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);
		IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", ivAlpha);

		return ivObj;
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list");

		return ivObj;
	}
}

IrisValue IrisToneClass::GetRed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@red");
}

IrisValue IrisToneClass::GetGreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@green");
}

IrisValue IrisToneClass::GetBlue(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@blue");
}

IrisValue IrisToneClass::GetAlpha(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@alpha");
}

IrisValue IrisToneClass::SetRed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	auto& ivRed = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivRed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a float");
		return IrisDev_Nil();
	}

	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivObj);
	auto nRed = IrisDev_GetInt(ivRed);

	pTone->SetRed(nRed);
	IrisDev_SetObjectInstanceVariable(ivObj, "@red", ivRed);

	return IrisDev_Nil();
}

IrisValue IrisToneClass::SetGreen(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	auto& ivGreen = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivGreen)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a float");
		return IrisDev_Nil();
	}

	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivObj);
	auto nGreen = IrisDev_GetInt(ivGreen);

	pTone->SetRed(nGreen);
	IrisDev_SetObjectInstanceVariable(ivObj, "@green", ivGreen);

	return IrisDev_Nil();
}

IrisValue IrisToneClass::SetBlue(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	auto& ivBlue = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivBlue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a float");
		return IrisDev_Nil();
	}

	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivObj);
	auto nBlue = IrisDev_GetInt(ivBlue);

	pTone->SetRed(nBlue);
	IrisDev_SetObjectInstanceVariable(ivObj, "@blue", ivBlue);

	return IrisDev_Nil();
}

IrisValue IrisToneClass::SetAlpha(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironmet) {
	auto& ivAlpha = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivAlpha)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a float");
		return IrisDev_Nil();
	}

	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivObj);
	auto nAlpha = IrisDev_GetInt(ivAlpha);

	pTone->SetRed(nAlpha);
	IrisDev_SetObjectInstanceVariable(ivObj, "@alpha", ivAlpha);

	return IrisDev_Nil();
}

void IrisToneClass::Mark(void * pNativePointer) {}

inline const char * IrisToneClass::NativeClassNameDefine() const {
	return "Tone";
}

IIrisClass * IrisToneClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisToneClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisTone);
}

void * IrisToneClass::NativeAlloc() {
	return GetTravialIIrisTone();
}

void IrisToneClass::NativeFree(void * pNativePointer) {
	ReleaseIrisTone(static_cast<IIrisTone*>(pNativePointer));
}

void IrisToneClass::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "set", Set, 3, true);

	IrisDev_AddGetter(this, "@red", GetRed);
	IrisDev_AddGetter(this, "@green", GetGreen);
	IrisDev_AddGetter(this, "@blue", GetBlue);
	IrisDev_AddGetter(this, "@alpha", GetAlpha);

	IrisDev_AddSetter(this, "@red", SetRed);
	IrisDev_AddSetter(this, "@green", SetGreen);
	IrisDev_AddSetter(this, "@blue", SetBlue);
	IrisDev_AddSetter(this, "@alpha", SetAlpha);
}

IrisToneClass::IrisToneClass() {

}

IrisToneClass::~IrisToneClass() {

}