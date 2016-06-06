#include "IrisMapping/IrisSpriteClass.h"

float GetFloatWhateverFloatOrInteger(const IrisValue& ivValue);

IrisValue IrisSpriteClass::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	if (!ivsValue) {
		IrisDev_SetObjectInstanceVariable(ivObj, "@viewport", IrisDev_Nil());
	}
	else if(ivsValue->GetSize() == 1){
		auto& ivViewport = ivsValue->GetValue(0);

		if (!IrisDev_CheckClass(ivViewport, "Viewport")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Viewport");
			return IrisDev_Nil();
		}
		auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivViewport);

		pSprite->SetInitData(pViewport);
		IrisDev_SetObjectInstanceVariable(ivObj, "@viewport", ivViewport);
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list.");
		return IrisDev_Nil();
	}

	IrisDev_SetObjectInstanceVariable(ivObj, "@bitmap", IrisDev_Nil());
	IrisDev_SetObjectInstanceVariable(ivObj, "@rect", IrisDev_Nil());
	IrisDev_SetObjectInstanceVariable(ivObj, "@visible", IrisDev_True());
	IrisDev_SetObjectInstanceVariable(ivObj, "@x", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetX())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@y", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetX())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@z", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetZ())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@ox", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetOx())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@oy", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetOy())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@zoom_x", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetZoomX())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@zoom_y", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetZoomY())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@angle", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetAngle())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_amp", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveAmp())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_length", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveLength())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_speed", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveSpeed())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_phase", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWavePhase())));

	return ivObj;
}

IrisValue IrisSpriteClass::SetViewport(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivViewport = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivViewport, "Viewport")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Viewport");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pViewport = IrisDev_GetNativePointer<IIrisViewport*>(ivViewport);

	pSprite->SetViewport(pViewport);

	IrisDev_SetObjectInstanceVariable(ivObj, "@viewport", ivViewport);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::GetViewport(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@viewport");
}

IrisValue IrisSpriteClass::Dispose(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValue, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	pSprite->Dispose();

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::Disposed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValue, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	if (pSprite->Disposed()) {
		return IrisDev_True();
	}
	else {
		return IrisDev_False();
	}
}

IrisValue IrisSpriteClass::Flash(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);
	auto nDuration = IrisDev_GetInt(ivDuration);

	pSprite->Flash(pColor, nDuration);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::Update(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	pSprite->Update();

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::GetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvrionment) {
	auto ivBitmap = IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");

	return IrisDev_GetObjectInstanceVariable(ivBitmap, "@width");
}

IrisValue IrisSpriteClass::GetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvrionment) {
	auto ivBitmap = IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");

	return IrisDev_GetObjectInstanceVariable(ivBitmap, "@height");
}

IrisValue IrisSpriteClass::SetOpacity(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOpacity = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivOpacity)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto nOpacity = IrisDev_GetInt(ivOpacity);

	pSprite->SetOpacity(nOpacity);

	IrisDev_SetObjectInstanceVariable(ivObj, "@opacity", ivOpacity);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::GetOpacity(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@opacity");
}

IrisValue IrisSpriteClass::GetBitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");
}

IrisValue IrisSpriteClass::GetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@rect");
}

IrisValue IrisSpriteClass::GetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@visible");
}

IrisValue IrisSpriteClass::GetX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@x");
}

IrisValue IrisSpriteClass::GetY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@y");
}

IrisValue IrisSpriteClass::GetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@z");
}

IrisValue IrisSpriteClass::GetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@ox");
}

IrisValue IrisSpriteClass::GetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@oy");
}

IrisValue IrisSpriteClass::GetZoomX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@zoom_x");
}

IrisValue IrisSpriteClass::GetZoomY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@zoom_y");
}

IrisValue IrisSpriteClass::GetAngle(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@angle");
}

IrisValue IrisSpriteClass::GetWaveAmp(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wave_amp");
}

IrisValue IrisSpriteClass::GetWaveLength(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wave_length");
}

IrisValue IrisSpriteClass::GetWaveSpeed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wave_speed");
}

IrisValue IrisSpriteClass::GetWavePhase(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wave_phase");
}

IrisValue IrisSpriteClass::SetBitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBitmap = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bitmap");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivBitmap);

	pSprite->SetBitmap(pBitmap);

	IrisDev_SetObjectInstanceVariable(ivObj, "@bitmap", ivBitmap);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRect = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);

	pSprite->SetSrcRect(pRect);

	IrisDev_SetObjectInstanceVariable(ivObj, "@rect", ivRect);
	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivVisible = ivsValue->GetValue(0);

	if (ivVisible != IrisDev_True() && ivVisible != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto bVisible = ivVisible == IrisDev_True() ? true : false;

	pSprite->SetVisible(bVisible);

	IrisDev_SetObjectInstanceVariable(ivObj, "@visible", ivVisible);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fX = GetFloatWhateverFloatOrInteger(ivX);

	pSprite->SetX(fX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivY = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
//	auto fY = static_cast<float>(IrisDev_GetFloat(ivY));
	//auto fY = IrisDev_CheckClassIsFloat(ivY) ? static_cast<float>(IrisDev_GetFloat(ivY)) : static_cast<float>(IrisDev_GetInt(ivY));
	auto fY = GetFloatWhateverFloatOrInteger(ivY);

	pSprite->SetY(fY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZ = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZ) && !IrisDev_CheckClassIsFloat(ivZ)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZ = GetFloatWhateverFloatOrInteger(ivZ);

	pSprite->SetZ(fZ);

	IrisDev_SetObjectInstanceVariable(ivObj, "@z", ivZ);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOx = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivOx) && !IrisDev_CheckClassIsFloat(ivOx)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fOx = GetFloatWhateverFloatOrInteger(ivOx);

	pSprite->SetOx(fOx);

	IrisDev_SetObjectInstanceVariable(ivObj, "@ox", ivOx);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOy = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivOy) && !IrisDev_CheckClassIsFloat(ivOy)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fOy = GetFloatWhateverFloatOrInteger(ivOy);

	pSprite->SetOy(fOy);

	IrisDev_SetObjectInstanceVariable(ivObj, "@oy", ivOy);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetZoomX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZoomX = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZoomX) && !IrisDev_CheckClassIsFloat(ivZoomX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZoomX = GetFloatWhateverFloatOrInteger(ivZoomX);

	pSprite->SetZoomX(fZoomX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@zoom_x", ivZoomX);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetZoomY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZoomY = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZoomY) && !IrisDev_CheckClassIsFloat(ivZoomY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZoomY = GetFloatWhateverFloatOrInteger(ivZoomY);

	pSprite->SetZoomY(fZoomY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@zoom_y", ivZoomY);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetAngle(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivAngle = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivAngle)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or an Integer");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fAngle = static_cast<float>(IrisDev_GetInt(ivAngle));

	pSprite->SetAngle(fAngle);

	IrisDev_SetObjectInstanceVariable(ivObj, "@angle", ivAngle);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetWaveAmp(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveAmp = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveAmp) && !IrisDev_CheckClassIsFloat(ivWaveAmp)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveAmp = GetFloatWhateverFloatOrInteger(ivWaveAmp);

	pSprite->SetWaveAmp(fWaveAmp);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_amp", ivWaveAmp);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetWaveLength(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveLength = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveLength) && !IrisDev_CheckClassIsFloat(ivWaveLength)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveLength = GetFloatWhateverFloatOrInteger(ivWaveLength);

	pSprite->SetWaveLength(fWaveLength);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_length", ivWaveLength);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetWaveSpeed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveSpeed = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveSpeed) && !IrisDev_CheckClassIsFloat(ivWaveSpeed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveSpeed = GetFloatWhateverFloatOrInteger(ivWaveSpeed);

	pSprite->SetWaveSpeed(fWaveSpeed);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_speed", ivWaveSpeed);

	return IrisDev_Nil();
}

IrisValue IrisSpriteClass::SetWavePhase(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWavePhase = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWavePhase) && !IrisDev_CheckClassIsFloat(ivWavePhase)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
		return IrisDev_Nil();
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWavePhase = GetFloatWhateverFloatOrInteger(ivWavePhase);

	pSprite->SetWavePhase(fWavePhase);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wave_phase", ivWavePhase);

	return IrisDev_Nil();
}

const char * IrisSpriteClass::NativeClassNameDefine() const {
	return "Sprite";
}

IIrisClass * IrisSpriteClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisSpriteClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisSprite);
}

void * IrisSpriteClass::NativeAlloc() {
	return GetTravialIIrisSprite();
}

void IrisSpriteClass::NativeFree(void * pNativePointer) {
	ReleaseIrisSprite(static_cast<IIrisSprite*>(pNativePointer));
}

void IrisSpriteClass::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 0, true);
	IrisDev_AddInstanceMethod(this, "flash", Flash, 2, false);
	IrisDev_AddInstanceMethod(this, "dispose", Dispose, 0, false);
	IrisDev_AddInstanceMethod(this, "disposed", Disposed, 0, false);
	IrisDev_AddInstanceMethod(this, "update", Update, 0, false);
	//IrisDev_AddInstanceMethod(this, "width", GetWidth, 0, false);
	//IrisDev_AddInstanceMethod(this, "height", GetHeight, 0, false);

	IrisDev_AddGetter(this, "@width", GetWidth);
	IrisDev_AddGetter(this, "@height", GetHeight);
	IrisDev_AddGetter(this, "@bitmap", GetBitmap);
	IrisDev_AddGetter(this, "@rect", GetRect);
	IrisDev_AddGetter(this, "@visible", GetVisible);
	IrisDev_AddGetter(this, "@x", GetX);
	IrisDev_AddGetter(this, "@y", GetY);
	IrisDev_AddGetter(this, "@z", GetZ);
	IrisDev_AddGetter(this, "@ox", GetOx);
	IrisDev_AddGetter(this, "@oy", GetOy);
	IrisDev_AddGetter(this, "@zoomx", GetZoomX);
	IrisDev_AddGetter(this, "@zoomy", GetZoomY);
	IrisDev_AddGetter(this, "@angle", GetAngle);
	IrisDev_AddGetter(this, "@waveamp", GetWaveAmp);
	IrisDev_AddGetter(this, "@wavelength", GetWaveLength);
	IrisDev_AddGetter(this, "@wavespeed", GetWaveSpeed);
	IrisDev_AddGetter(this, "@wavephase", GetWavePhase);

	IrisDev_AddSetter(this, "@bitmap", SetBitmap);
	IrisDev_AddSetter(this, "@rect", SetRect);
	IrisDev_AddSetter(this, "@visible", SetVisible);
	IrisDev_AddSetter(this, "@x", SetX);
	IrisDev_AddSetter(this, "@y", SetY);
	IrisDev_AddSetter(this, "@z", SetZ);
	IrisDev_AddSetter(this, "@ox", SetOx);
	IrisDev_AddSetter(this, "@oy", SetOy);
	IrisDev_AddSetter(this, "@zoomx", SetZoomX);
	IrisDev_AddSetter(this, "@zoomy", SetZoomY);
	IrisDev_AddSetter(this, "@angle", SetAngle);
	IrisDev_AddSetter(this, "@waveamp", SetWaveAmp);
	IrisDev_AddSetter(this, "@wavelength", SetWaveLength);
	IrisDev_AddSetter(this, "@wavespeed", SetWaveSpeed);
	IrisDev_AddSetter(this, "@wavephase", SetWavePhase);
}

IrisSpriteClass::IrisSpriteClass() {

}

IrisSpriteClass::~IrisSpriteClass() {
	
}