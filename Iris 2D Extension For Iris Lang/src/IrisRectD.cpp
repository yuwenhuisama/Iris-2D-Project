#include "IrisMapping/IrisRectD.h"

IrisValue IrisRectD::Initialize(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValues->GetValue(0);
	auto& ivY = ivsValues->GetValue(1);
	auto& ivWidth = ivsValues->GetValue(2);
	auto& ivHeight = ivsValues->GetValue(3);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivWidth) && !IrisDev_CheckClassIsFloat(ivWidth)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivHeight) && !IrisDev_CheckClassIsFloat(ivHeight)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	auto fX = static_cast<float>(IrisDev_GetFloat(ivX));
	auto fY = static_cast<float>(IrisDev_GetFloat(ivY));
	auto fWidth = static_cast<float>(IrisDev_GetFloat(ivWidth));
	auto fHeight = static_cast<float>(IrisDev_GetFloat(ivHeight));

	pRect->SetInitData(fX, fY, fWidth, fHeight);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);
	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return IrisDev_Nil();
}

IrisValue IrisRectD::Set(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValues->GetValue(0);
	auto& ivY = ivsValues->GetValue(1);
	auto& ivWidth = ivsValues->GetValue(2);
	auto& ivHeight = ivsValues->GetValue(3);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivWidth) && !IrisDev_CheckClassIsFloat(ivWidth)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}
	if (!IrisDev_CheckClassIsInteger(ivHeight) && !IrisDev_CheckClassIsInteger(ivHeight)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float nX = static_cast<float>(IrisDev_GetFloat(ivX));
	float nY = static_cast<float>(IrisDev_GetFloat(ivY));
	float nWidth = static_cast<float>(IrisDev_GetFloat(ivWidth));
	float nHeight = static_cast<float>(IrisDev_GetFloat(ivHeight));

	pRect->Set(nX, nY, nWidth, nHeight);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);
	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return IrisDev_Nil();
}

IrisValue IrisRectD::SetX(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fX = static_cast<float>(IrisDev_GetFloat(ivX));

	pRect->SetX(fX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);

	return IrisDev_Nil();
}

IrisValue IrisRectD::SetY(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivY = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fY = static_cast<float>(IrisDev_GetFloat(ivY));

	pRect->SetY(fY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);

	return IrisDev_Nil();
}

IrisValue IrisRectD::SetWidth(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWidth = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWidth) && !IrisDev_CheckClassIsFloat(ivWidth)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fWidth = static_cast<float>(IrisDev_GetFloat(ivWidth));

	pRect->SetWidth(fWidth);

	
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);

	return IrisDev_Nil();
}

IrisValue IrisRectD::SetHeight(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivHeight = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivHeight) && !IrisDev_CheckClassIsFloat(ivHeight)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fHeight = static_cast<float>(IrisDev_GetFloat(ivHeight));

	pRect->SetHeight(fHeight);

	
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return IrisDev_Nil();
}

IrisValue IrisRectD::GetX(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@x");
}

IrisValue IrisRectD::GetY(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@y");
}

IrisValue IrisRectD::GetWidth(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@width");
}

IrisValue IrisRectD::GetHeight(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@height");
}

const char * IrisRectD::NativeClassNameDefine() const {
	return "IrisRect";
}

IIrisClass * IrisRectD::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisRectD::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisRect);
}

void * IrisRectD::NativeAlloc() {
	return GetTravialIIrisRect();
}

void IrisRectD::NativeFree(void * pNativePointer) {
	ReleaseIrisRect(static_cast<IIrisRect*>(pNativePointer));
}

void IrisRectD::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 4, false);
	IrisDev_AddInstanceMethod(this, "set", Set, 4, false);

	IrisDev_AddGetter(this, "@x", GetX);
	IrisDev_AddGetter(this, "@y", GetY);
	IrisDev_AddGetter(this, "@width", GetWidth);
	IrisDev_AddGetter(this, "@height", GetHeight);

	IrisDev_AddSetter(this, "@x", SetX);
	IrisDev_AddSetter(this, "@y", SetY);
	IrisDev_AddSetter(this, "@width", SetWidth);
	IrisDev_AddSetter(this, "@height", SetHeight);
}

IrisRectD::IrisRectD() {

}

IrisRectD::~IrisRectD() {

}
