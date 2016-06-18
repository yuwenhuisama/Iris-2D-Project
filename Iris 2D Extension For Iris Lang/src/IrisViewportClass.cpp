#include "IrisMapping\IrisViewportClass.h"

float GetFloatWhateverFloatOrInteger(const IrisValue& ivValue);

IrisValue IrisViewportClass::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);

	if (ivsVariableValues->GetSize() == 4) {
		auto& ivX = ivsVariableValues->GetValue(0);
		auto& ivY = ivsVariableValues->GetValue(1);
		auto& ivWidth = ivsVariableValues->GetValue(2);
		auto& ivHeight = ivsVariableValues->GetValue(3);

		if (!IrisDev_CheckClassIsFloat(ivX) && !IrisDev_CheckClassIsInteger(ivX)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a float");
			return IrisDev_Nil();
		}

		if (!IrisDev_CheckClassIsFloat(ivY) && !IrisDev_CheckClassIsInteger(ivY)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a float");
			return IrisDev_Nil();
		}

		if (!IrisDev_CheckClassIsFloat(ivWidth) && !IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be a float");
			return IrisDev_Nil();
		}

		if (!IrisDev_CheckClassIsFloat(ivHeight) && !IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be a float");
			return IrisDev_Nil();
		}

		auto fX = GetFloatWhateverFloatOrInteger(ivX);
		auto fY = GetFloatWhateverFloatOrInteger(ivY);
		auto fWidth = GetFloatWhateverFloatOrInteger(ivWidth);
		auto fHeight = GetFloatWhateverFloatOrInteger(ivHeight);

		pViewport->SetInitData(fX, fY, fWidth, fHeight);

		auto ivsParam = IrisDev_CreateIrisValuesList(4);
		ivsParam->SetValue(0, IrisDev_CreateFloatInstanceByInstantValue(fX));
		ivsParam->SetValue(1, IrisDev_CreateFloatInstanceByInstantValue(fY));
		ivsParam->SetValue(2, IrisDev_CreateFloatInstanceByInstantValue(fWidth));
		ivsParam->SetValue(3, IrisDev_CreateFloatInstanceByInstantValue(fHeight));

		IrisDev_SetObjectInstanceVariable(ivObj, "@rect", IrisDev_CreateNormalInstance(IrisDev_GetClass("Rect"), ivsParam, nullptr));
		IrisDev_SetObjectInstanceVariable(ivObj, "@visible", IrisDev_True());
		IrisDev_SetObjectInstanceVariable(ivObj, "@z", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetZ()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@ox", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetOx()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@oy", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetOy()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@tone", IrisDev_Nil());
		IrisDev_SetObjectInstanceVariable(ivObj, "@color", IrisDev_Nil());
		IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);
		IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);
		IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
		IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);

		IrisDev_ReleaseIrisValuesList(ivsParam);

		return IrisDev_Nil();
	}
	else if (ivsVariableValues->GetSize() == 1) {
		auto& ivRect = ivsVariableValues->GetValue(0);

		if (!IrisDev_CheckClass(ivRect, "Rect")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		}

		auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);

		pViewport->SetInitData(pRect);

		IrisDev_SetObjectInstanceVariable(ivObj, "@rect", ivRect);
		IrisDev_SetObjectInstanceVariable(ivObj, "@visible", IrisDev_True());
		IrisDev_SetObjectInstanceVariable(ivObj, "@z", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetZ()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@ox", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetOx()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@oy", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetOy()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@tone", IrisDev_Nil());
		IrisDev_SetObjectInstanceVariable(ivObj, "@color", IrisDev_Nil());
		IrisDev_SetObjectInstanceVariable(ivObj, "@x", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetX()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@y", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetY()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@width", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetWidth()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@height", IrisDev_CreateFloatInstanceByInstantValue(pViewport->GetHeight()));

		return IrisDev_Nil();
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list");

		return IrisDev_Nil();
	}
	return IrisDev_Nil();
}

IrisValue IrisViewportClass::Dispose(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);

	pViewport->Dispose();

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::Disposed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);

	return pViewport->Disposed() == true ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisViewportClass::Flash(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivColor = ivsValue->GetValue(0);
	auto& ivDuration = ivsValue->GetValue(1);

	if (!IrisDev_CheckClass(ivColor, "Color")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Color");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivDuration)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);
	auto nDuration = IrisDev_GetInt(ivDuration);

	pViewport->Flash(pColor, nDuration);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::Update(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);

	pViewport->Update();

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::GetX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@x");
}

IrisValue IrisViewportClass::GetY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@y");
}

IrisValue IrisViewportClass::GetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@width");
}

IrisValue IrisViewportClass::GetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@height");
}

IrisValue IrisViewportClass::GetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@rect");
}

IrisValue IrisViewportClass::GetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@visible");
}

IrisValue IrisViewportClass::GetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@z");
}

IrisValue IrisViewportClass::GetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@ox");
}

IrisValue IrisViewportClass::GetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@oy");
}

IrisValue IrisViewportClass::GetTone(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@tone");
}

IrisValue IrisViewportClass::GetColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@color");
}

IrisValue IrisViewportClass::SetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRect = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);

	pViewport->SetSrcRect(pRect);

	IrisDev_SetObjectInstanceVariable(ivObj, "@rect", ivRect);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivVisible = ivsValue->GetValue(0);

	if (ivVisible != IrisDev_True() && ivVisible != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto bVisible = ivVisible == IrisDev_True() ? true : false;

	pViewport->SetVisible(bVisible);

	IrisDev_SetObjectInstanceVariable(ivObj, "@visible", ivVisible);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZ = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsFloat(ivZ) && !IrisDev_CheckClassIsInteger(ivZ)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Float or an Integer");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto fZ = GetFloatWhateverFloatOrInteger(ivZ);

	pViewport->SetZ(fZ);

	IrisDev_SetObjectInstanceVariable(ivObj, "@z", ivZ);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOx = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsFloat(ivOx) && !IrisDev_CheckClassIsInteger(ivOx)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Float or an Integer");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto fOx = GetFloatWhateverFloatOrInteger(ivOx);

	pViewport->SetOx(fOx);

	IrisDev_SetObjectInstanceVariable(ivObj, "@ox", ivOx);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOy = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsFloat(ivOy) && !IrisDev_CheckClassIsInteger(ivOy)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Float or an Integer");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto fOy = GetFloatWhateverFloatOrInteger(ivOy);

	pViewport->SetOy(fOy);

	IrisDev_SetObjectInstanceVariable(ivObj, "@oy", ivOy);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetTone(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivTone = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivTone, "Tone")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Tone");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto pTone = IrisDev_GetNativePointer<IIrisTone*>(ivTone);

	pViewport->SetTone(pTone);

	IrisDev_SetObjectInstanceVariable(ivObj, "@tone", ivTone);

	return IrisDev_Nil();
}

IrisValue IrisViewportClass::SetColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivColor = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivColor, "Color")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Color");
		return IrisDev_Nil();
	}

	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivObj);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);

	pViewport->SetColor(pColor);

	IrisDev_SetObjectInstanceVariable(ivObj, "@color", ivColor);

	return IrisDev_Nil();
}

void IrisViewportClass::Mark(void * pNativePointer) {}

inline const char * IrisViewportClass::NativeClassNameDefine() const {
	return "Viewport";
}

IIrisClass * IrisViewportClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisViewportClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisViewport);
}

void * IrisViewportClass::NativeAlloc() {
	return GetTravialIIrisViewport();
}

void IrisViewportClass::NativeFree(void * pNativePointer) {
	ReleaseIrisViewport(static_cast<IIrisViewport*>(pNativePointer));
}

void IrisViewportClass::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 0, true);
	IrisDev_AddInstanceMethod(this, "dispose", Dispose, 0, false);
	IrisDev_AddInstanceMethod(this, "disposed", Disposed, 0, false);
	IrisDev_AddInstanceMethod(this, "flash", Flash, 2, false);
	IrisDev_AddInstanceMethod(this, "update", Update, 0, false);

	IrisDev_AddGetter(this, "@x", GetX);
	IrisDev_AddGetter(this, "@y", GetY);
	IrisDev_AddGetter(this, "@width", GetWidth);
	IrisDev_AddGetter(this, "@height", GetHeight);
	IrisDev_AddGetter(this, "@rect", GetRect);
	IrisDev_AddGetter(this, "@visible", GetVisible);
	IrisDev_AddGetter(this, "@z", GetZ);
	IrisDev_AddGetter(this, "@ox", GetOx);
	IrisDev_AddGetter(this, "@oy", GetOy);
	IrisDev_AddGetter(this, "@tone", GetTone);
	IrisDev_AddGetter(this, "@color", GetColor);

	IrisDev_AddSetter(this, "@rect", SetRect);
	IrisDev_AddSetter(this, "@visible", SetVisible);
	IrisDev_AddSetter(this, "@z", SetZ);
	IrisDev_AddSetter(this, "@ox", SetOx);
	IrisDev_AddSetter(this, "@oy", SetOy);
	IrisDev_AddSetter(this, "@tone", SetTone);
	IrisDev_AddSetter(this, "@color", SetColor);
}

IrisViewportClass::IrisViewportClass() {

}

IrisViewportClass::~IrisViewportClass() {

}