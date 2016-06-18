#include "IrisMapping/IrisFontClass.h"

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

IrisValue IrisFontClass::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);

	if (ivsVariableValues->GetSize() == 2) {
		auto& ivName = ivsVariableValues->GetValue(0);
		auto& ivSize = ivsVariableValues->GetValue(1);

		if (!IrisDev_CheckClassIsString(ivName)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
			return IrisDev_Nil();
		}
		if (!IrisDev_CheckClassIsInteger(ivSize)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
			return IrisDev_Nil();
		}

		auto cName = IrisDev_GetString(ivName);
		string sName = string(cName);
		wstring wsName = StringToWString(sName);

		auto nSize = IrisDev_GetInt(ivSize);

		pFont->SetInitData(wsName, nSize);

		IrisDev_SetObjectInstanceVariable(ivObj, "@name", ivName);
		IrisDev_SetObjectInstanceVariable(ivObj, "@size", ivSize);
		IrisDev_SetObjectInstanceVariable(ivObj, "@bold", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@italic", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@shadow", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@color", IrisDev_Nil());

		return ivObj;
	}
	else if (ivsVariableValues->GetSize() == 1) {
		auto& ivName = ivsVariableValues->GetValue(0);

		if (!IrisDev_CheckClassIsString(ivName)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
			return IrisDev_Nil();
		}

		auto cName = IrisDev_GetString(ivName);
		string sName = string(cName);
		wstring wsName = StringToWString(sName);

		pFont->SetName(wsName);

		IrisDev_SetObjectInstanceVariable(ivObj, "@name", ivName);
		IrisDev_SetObjectInstanceVariable(ivObj, "@size", IrisDev_CreateIntegerInstanceByInstantValue(pFont->GetSize()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@bold", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@italic", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@shadow", IrisDev_False());
		IrisDev_SetObjectInstanceVariable(ivObj, "@color", IrisDev_Nil());

		return ivObj;
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list");
		return ivObj;
	}
}

IrisValue IrisFontClass::GetName(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@name");
}

IrisValue IrisFontClass::GetSize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@size");
}

IrisValue IrisFontClass::GetBold(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@bold");
}

IrisValue IrisFontClass::GetItalic(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@shadow");
}

IrisValue IrisFontClass::GetShadow(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@shadow");
}

IrisValue IrisFontClass::GetColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@color");
}

IrisValue IrisFontClass::SetName(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivName = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsString(ivName)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto cName = IrisDev_GetString(ivName);
	string sName = string(cName);
	wstring wsName = StringToWString(sName);

	pFont->SetName(wsName);
	IrisDev_SetObjectInstanceVariable(ivObj, "@name", ivName);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::SetSize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivSize = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivSize)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Integer");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto nSize = IrisDev_GetInt(ivSize);

	pFont->SetSize(nSize);
	IrisDev_SetObjectInstanceVariable(ivObj, "@size", ivSize);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::SetBold(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivBold = ivsValue->GetValue(0);

	if (ivBold != IrisDev_True() && ivBold != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto bBold = ivBold == IrisDev_True() ? true : false;

	pFont->SetBold(bBold);
	IrisDev_SetObjectInstanceVariable(ivObj, "@bold", ivBold);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::SetItalic(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivItalic = ivsValue->GetValue(0);

	if (ivItalic != IrisDev_True() && ivItalic != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto bItalic = ivItalic == IrisDev_True() ? true : false;

	pFont->SetItalic(bItalic);
	IrisDev_SetObjectInstanceVariable(ivObj, "@italic", ivItalic);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::SetShadow(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivShadow = ivsValue->GetValue(0);

	if (ivShadow != IrisDev_True() && ivShadow != IrisDev_False()) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Bool");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto bShadow = ivShadow == IrisDev_True() ? true : false;

	pFont->SetShadow(bShadow);
	IrisDev_SetObjectInstanceVariable(ivObj, "@shadow", ivShadow);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::SetColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivColor = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivColor, "Color")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a color");
		return IrisDev_Nil();
	}

	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivObj);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);

	pFont->SetColor(pColor);
	IrisDev_SetObjectInstanceVariable(ivObj, "@color", ivColor);

	return IrisDev_Nil();
}

IrisValue IrisFontClass::ModuleIrisFontExisted(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivName = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsString(ivName)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		return IrisDev_Nil();
	}

	auto cName = IrisDev_GetString(ivName);
	string sName = string(cName);
	wstring wsName = StringToWString(sName);

	return IrisFontExisted(wsName) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultName(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	wstring wsDefault = IrisFontGetDefaultName();
	string sDefault = WStringToString(wsDefault);
	const char* cDefault = sDefault.c_str();

	return IrisDev_CreateStringInstanceByInstantValue(cDefault);
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultSize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisFontGetDefaultSize());
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultBold(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisFontGetDefaultBold() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultItalic(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisFontGetDefaultItalic() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultShadow(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisFontGetDefaultShadow() ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisFontClass::ModuleIrisFontGetDefaultColor(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto pColor = IrisFontGetDefaultColor();
	auto ivParam = IrisDev_CreateIrisValuesList(4);

	ivParam->SetValue(0, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetRed()));
	ivParam->SetValue(1, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetGreen()));
	ivParam->SetValue(2, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetBlue()));
	ivParam->SetValue(3, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetAlpha()));

	auto ivValue = IrisDev_CreateNormalInstance(IrisDev_GetClass("Color"), ivParam, nullptr);

	IrisDev_ReleaseIrisValuesList(ivParam);

	return ivValue;
}

void IrisFontClass::Mark(void * pNativePointer) {}

const char * IrisFontClass::NativeClassNameDefine() const {
	return "Font";
}

IIrisClass * IrisFontClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisFontClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisFont);
}

void * IrisFontClass::NativeAlloc() {
	return GetTravialIIrisFont();
}

void IrisFontClass::NativeFree(void * pNativePointer) {
	ReleaseIrisFont(static_cast<IIrisFont*>(pNativePointer));
}

void IrisFontClass::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 0, true);

	IrisDev_AddGetter(this, "@name", GetName);
	IrisDev_AddGetter(this, "@size", GetSize);
	IrisDev_AddGetter(this, "@bold", GetBold);
	IrisDev_AddGetter(this, "@italic", GetItalic);
	IrisDev_AddGetter(this, "@shadow", GetShadow);
	IrisDev_AddGetter(this, "@color", GetColor);

	IrisDev_AddSetter(this, "@name", SetName);
	IrisDev_AddSetter(this, "@size", SetSize);
	IrisDev_AddSetter(this, "@bold", SetBold);
	IrisDev_AddSetter(this, "@italic", SetItalic);
	IrisDev_AddSetter(this, "@shadow", SetShadow);
	IrisDev_AddSetter(this, "@color", SetColor);

	IrisDev_AddClassMethod(this, "existe", ModuleIrisFontExisted, 1, false);
	IrisDev_AddClassMethod(this, "default_name", ModuleIrisFontGetDefaultName, 0, false);
	IrisDev_AddClassMethod(this, "default_size", ModuleIrisFontGetDefaultSize, 0, false);
	IrisDev_AddClassMethod(this, "default_bold", ModuleIrisFontGetDefaultBold, 0, false);
	IrisDev_AddClassMethod(this, "default_italic", ModuleIrisFontGetDefaultItalic, 0, false);
	IrisDev_AddClassMethod(this, "default_shadow", ModuleIrisFontGetDefaultShadow, 0, false);
	IrisDev_AddClassMethod(this, "default_color", ModuleIrisFontGetDefaultColor, 0, false);
}

IrisFontClass::IrisFontClass() {

}

IrisFontClass::~IrisFontClass() {

}