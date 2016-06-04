#include "IrisMapping/IrisRectClass.h"
float GetFloatWhateverFloatOrInteger(const IrisValue& ivValue);

IrisValue IrisRectClass::Initialize(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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
	auto fX = static_cast<float>(GetFloatWhateverFloatOrInteger(ivX));
	auto fY = static_cast<float>(GetFloatWhateverFloatOrInteger(ivY));
	auto fWidth = static_cast<float>(GetFloatWhateverFloatOrInteger(ivWidth));
	auto fHeight = static_cast<float>(GetFloatWhateverFloatOrInteger(ivHeight));

	pRect->SetInitData(fX, fY, fWidth, fHeight);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);
	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return ivObj;
}

IrisValue IrisRectClass::Set(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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
	float nX = static_cast<float>(GetFloatWhateverFloatOrInteger(ivX));
	float nY = static_cast<float>(GetFloatWhateverFloatOrInteger(ivY));
	float nWidth = static_cast<float>(GetFloatWhateverFloatOrInteger(ivWidth));
	float nHeight = static_cast<float>(GetFloatWhateverFloatOrInteger(ivHeight));

	pRect->Set(nX, nY, nWidth, nHeight);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);
	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return IrisDev_Nil();
}

IrisValue IrisRectClass::SetX(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fX = static_cast<float>(GetFloatWhateverFloatOrInteger(ivX));

	pRect->SetX(fX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);

	return IrisDev_Nil();
}

IrisValue IrisRectClass::SetY(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivY = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fY = static_cast<float>(GetFloatWhateverFloatOrInteger(ivY));

	pRect->SetY(fY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);

	return IrisDev_Nil();
}

IrisValue IrisRectClass::SetWidth(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWidth = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWidth) && !IrisDev_CheckClassIsFloat(ivWidth)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fWidth = static_cast<float>(GetFloatWhateverFloatOrInteger(ivWidth));

	pRect->SetWidth(fWidth);

	
	IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);

	return IrisDev_Nil();
}

IrisValue IrisRectClass::SetHeight(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivHeight = ivsValues->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivHeight) && !IrisDev_CheckClassIsFloat(ivHeight)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1 : it must be an Integer or a float.");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivObj);
	float fHeight = static_cast<float>(GetFloatWhateverFloatOrInteger(ivHeight));

	pRect->SetHeight(fHeight);
	
	IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

	return IrisDev_Nil();
}

IrisValue IrisRectClass::GetX(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@x");
}

IrisValue IrisRectClass::GetY(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@y");
}

IrisValue IrisRectClass::GetWidth(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@width");
}

IrisValue IrisRectClass::GetHeight(IrisValue & ivObj, IIrisValues * ivsValues, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@height");
}

const char * IrisRectClass::NativeClassNameDefine() const {
	return "Rect";
}

IIrisClass * IrisRectClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisRectClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisRect);
}

void * IrisRectClass::NativeAlloc() {
	return GetTravialIIrisRect();
}

void IrisRectClass::NativeFree(void * pNativePointer) {
	ReleaseIrisRect(static_cast<IIrisRect*>(pNativePointer));
}

void IrisRectClass::NativeClassDefine() {
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

IrisRectClass::IrisRectClass() {

}

IrisRectClass::~IrisRectClass() {

}
