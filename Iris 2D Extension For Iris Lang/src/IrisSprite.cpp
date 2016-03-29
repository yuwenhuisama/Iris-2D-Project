#include "IrisMapping/IrisSprite.h"

IrisValue IrisSprite::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	
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
	IrisDev_SetObjectInstanceVariable(ivObj, "@zoomx", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetZoomX())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@zoomy", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetZoomY())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@angle", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetAngle())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@waveamp", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveAmp())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wavelength", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveLength())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wavespeed", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWaveSpeed())));
	IrisDev_SetObjectInstanceVariable(ivObj, "@wavephase", IrisDev_CreateFloatInstanceByInstantValue(static_cast<double>(pSprite->GetWavePhase())));

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetViewport(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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

IrisValue IrisSprite::GetViewport(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@viewport");
}

IrisValue IrisSprite::Dispose(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValue, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	pSprite->Dispose();

	return IrisDev_Nil();
}

IrisValue IrisSprite::Disposed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValue, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	if (pSprite->Disposed()) {
		return IrisDev_True();
	}
	else {
		return IrisDev_False();
	}
}

IrisValue IrisSprite::Flash(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivColor = ivsValue->GetValue(0);
	auto& ivDuration = ivsValue->GetValue(1);

	if (!IrisDev_CheckClass(ivColor, "Color")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Color");
		return IrisDev_Nil();
	}

	if (!IrisDev_CheckClassIsInteger(ivDuration)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);
	auto nDuration = IrisDev_GetInt(ivDuration);

	pSprite->Flash(pColor, nDuration);

	return IrisDev_Nil();
}

IrisValue IrisSprite::Update(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);

	pSprite->Update();

	return IrisDev_Nil();
}

IrisValue IrisSprite::GetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvrionment) {
	auto ivBitmap = IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");

	return IrisDev_GetObjectInstanceVariable(ivBitmap, "@width");
}

IrisValue IrisSprite::GetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvrionment) {
	auto ivBitmap = IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");

	return IrisDev_GetObjectInstanceVariable(ivBitmap, "@height");
}

IrisValue IrisSprite::SetOpacity(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
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

IrisValue IrisSprite::GetOpacity(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@opacity");
}

IrisValue IrisSprite::GetBitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@bitmap");
}

IrisValue IrisSprite::GetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@rect");
}

IrisValue IrisSprite::GetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@visible");
}

IrisValue IrisSprite::GetX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@x");
}

IrisValue IrisSprite::GetY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@y");
}

IrisValue IrisSprite::GetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@z");
}

IrisValue IrisSprite::GetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@ox");
}

IrisValue IrisSprite::GetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@oy");
}

IrisValue IrisSprite::GetZoomX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@zoomx");
}

IrisValue IrisSprite::GetZoomY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@zoomy");
}

IrisValue IrisSprite::GetAngle(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@angle");
}

IrisValue IrisSprite::GetWaveAmp(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@waveamp");
}

IrisValue IrisSprite::GetWaveLength(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wavelength");
}

IrisValue IrisSprite::GetWaveSpeed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wavespeed");
}

IrisValue IrisSprite::GetWavePhase(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@wavephase");
}

IrisValue IrisSprite::SetBitmap(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBitmap = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bitmap");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivBitmap);

	pSprite->SetBitmap(pBitmap);

	IrisDev_SetObjectInstanceVariable(ivObj, "@bitmap", ivBitmap);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivRect = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);

	pSprite->SetSrcRect(pRect);

	IrisDev_SetObjectInstanceVariable(ivObj, "@rect", ivRect);
	return IrisDev_Nil();
}

IrisValue IrisSprite::SetVisible(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivVisible = ivsValue->GetValue(0);

	if (ivVisible != IrisDev_True() && ivVisible != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	//auto bVisible = static_cast<bool>(IrisDev_GetInt(ivVisible));
	auto bVisible = ivVisible == IrisDev_True() ? true : false;

	pSprite->SetVisible(bVisible);

	IrisDev_SetObjectInstanceVariable(ivObj, "@visible", ivVisible);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivX) && !IrisDev_CheckClassIsFloat(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fX = IrisDev_CheckClassIsFloat(ivX) ? static_cast<float>(IrisDev_GetFloat(ivX)) : static_cast<float>(IrisDev_GetInt(ivX));

	pSprite->SetX(fX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@x", ivX);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivY = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivY) && !IrisDev_CheckClassIsFloat(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
//	auto fY = static_cast<float>(IrisDev_GetFloat(ivY));
	auto fY = IrisDev_CheckClassIsFloat(ivY) ? static_cast<float>(IrisDev_GetFloat(ivY)) : static_cast<float>(IrisDev_GetInt(ivY));

	pSprite->SetY(fY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@y", ivY);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetZ(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZ = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZ) && !IrisDev_CheckClassIsFloat(ivZ)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZ = static_cast<float>(IrisDev_GetFloat(ivZ));

	pSprite->SetZ(fZ);

	IrisDev_SetObjectInstanceVariable(ivObj, "@z", ivZ);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetOx(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOx = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivOx) && !IrisDev_CheckClassIsFloat(ivOx)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fOx = static_cast<float>(IrisDev_GetFloat(ivOx));

	pSprite->SetOx(fOx);

	IrisDev_SetObjectInstanceVariable(ivObj, "@ox", ivOx);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetOy(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivOy = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivOy) && !IrisDev_CheckClassIsFloat(ivOy)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fOy = static_cast<float>(IrisDev_GetFloat(ivOy));

	pSprite->SetOy(fOy);

	IrisDev_SetObjectInstanceVariable(ivObj, "@oy", ivOy);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetZoomX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZoomX = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZoomX) && !IrisDev_CheckClassIsFloat(ivZoomX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZoomX = static_cast<float>(IrisDev_GetFloat(ivZoomX));

	pSprite->SetZoomX(fZoomX);

	IrisDev_SetObjectInstanceVariable(ivObj, "@zoomx", ivZoomX);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetZoomY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivZoomY = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivZoomY) && !IrisDev_CheckClassIsFloat(ivZoomY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fZoomY = static_cast<float>(IrisDev_GetFloat(ivZoomY));

	pSprite->SetZoomY(fZoomY);

	IrisDev_SetObjectInstanceVariable(ivObj, "@zoomy", ivZoomY);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetAngle(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivAngle = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivAngle) && !IrisDev_CheckClassIsFloat(ivAngle)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fAngle = static_cast<float>(IrisDev_GetFloat(ivAngle));

	pSprite->SetAngle(fAngle);

	IrisDev_SetObjectInstanceVariable(ivObj, "@angle", ivAngle);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetWaveAmp(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveAmp = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveAmp) && !IrisDev_CheckClassIsFloat(ivWaveAmp)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveAmp = static_cast<float>(IrisDev_GetFloat(ivWaveAmp));

	pSprite->SetWaveAmp(fWaveAmp);

	IrisDev_SetObjectInstanceVariable(ivObj, "@waveamp", ivWaveAmp);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetWaveLength(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveLength = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveLength) && !IrisDev_CheckClassIsFloat(ivWaveLength)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveLength = static_cast<float>(IrisDev_GetFloat(ivWaveLength));

	pSprite->SetWaveLength(fWaveLength);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wavelength", ivWaveLength);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetWaveSpeed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWaveSpeed = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWaveSpeed) && !IrisDev_CheckClassIsFloat(ivWaveSpeed)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWaveSpeed = static_cast<float>(IrisDev_GetFloat(ivWaveSpeed));

	pSprite->SetWaveSpeed(fWaveSpeed);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wavespeed", ivWaveSpeed);

	return IrisDev_Nil();
}

IrisValue IrisSprite::SetWavePhase(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivWavePhase = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivWavePhase) && !IrisDev_CheckClassIsFloat(ivWavePhase)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer or a Float");
	}

	auto pSprite = IrisDev_GetNativePointer<IIrisSprite*>(ivObj);
	auto fWavePhase = static_cast<float>(IrisDev_GetFloat(ivWavePhase));

	pSprite->SetWavePhase(fWavePhase);

	IrisDev_SetObjectInstanceVariable(ivObj, "@wavephase", ivWavePhase);

	return IrisDev_Nil();
}

const char * IrisSprite::NativeClassNameDefine() const {
	return "IrisSprite";
}

IIrisClass * IrisSprite::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisSprite::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisSprite);
}

void * IrisSprite::NativeAlloc() {
	return GetTravialIIrisSprite();
}

void IrisSprite::NativeFree(void * pNativePointer) {
	ReleaseIrisSprite(static_cast<IIrisSprite*>(pNativePointer));
}

void IrisSprite::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 0, true);
	IrisDev_AddInstanceMethod(this, "flash", Flash, 2, false);
	IrisDev_AddInstanceMethod(this, "dispose", Dispose, 0, false);
	IrisDev_AddInstanceMethod(this, "disposed", Disposed, 0, false);
	IrisDev_AddInstanceMethod(this, "update", Update, 0, false);
	IrisDev_AddInstanceMethod(this, "get_width", GetWidth, 0, false);
	IrisDev_AddInstanceMethod(this, "get_height", GetHeight, 0, false);

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

IrisSprite::IrisSprite() {

}

IrisSprite::~IrisSprite() {
	
}