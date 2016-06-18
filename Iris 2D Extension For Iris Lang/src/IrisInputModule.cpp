#include "IrisMapping\IrisInputModule.h"

IrisValue IrisInputModule::ModuleIrisInputUpdate(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	IrisInputUpdate();

	return IrisDev_Nil();
}

IrisValue IrisInputModule::ModuleIrisInputKeyBoardKeyPress(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<DWORD>(IrisDev_GetInt(ivKey));

	return IrisInputKeyBoardKeyPress(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputKeyBoardKeyTrigger(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<DWORD>(IrisDev_GetInt(ivKey));

	return IrisInputKeyBoardKeyTrigger(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputKeyBoardKeyRepeat(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<DWORD>(IrisDev_GetInt(ivKey));

	return IrisInputKeyBoardKeyRepeat(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputMousePress(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<MouseKey>(IrisDev_GetInt(ivKey));
	return IrisInputMousePress(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputMouseTrigger(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<MouseKey>(IrisDev_GetInt(ivKey));

	return IrisInputMouseTrigger(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputMouseRepeat(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivKey = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivKey)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		return IrisDev_Nil();
	}

	auto unKey = static_cast<MouseKey>(IrisDev_GetInt(ivKey));

	return IrisInputMouseRepeat(unKey) ? IrisDev_True() : IrisDev_False();
}

IrisValue IrisInputModule::ModuleIrisInputMouseMiddleRoll(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(static_cast<int>(IrisInputMouseMiddleRoll()));
}

IrisValue IrisInputModule::ModuleIrisInputMouseXMove(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(static_cast<int>(IrisInputMouseXMove()));
}

IrisValue IrisInputModule::ModuleIrisInputMouseYMove(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(static_cast<int>(IrisInputMouseYMove()));
}

IrisValue IrisInputModule::ModuleIrisInputGetCursorX(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisInputGetCursorX());
}

IrisValue IrisInputModule::ModuleIrisInputGetCursorY(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	return IrisDev_CreateIntegerInstanceByInstantValue(IrisInputGetCursorY());
}

IrisValue IrisInputModule::ModuleIrisInputCursorInRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContetxtEnvironment) {
	auto& ivRect = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		return IrisDev_Nil();
	}

	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);
	return IrisInputCursorInRect(pRect) ? IrisDev_True() : IrisDev_False();
}

const char * IrisInputModule::NativeModuleNameDefine() const {
	return "Input";
}

IIrisModule * IrisInputModule::NativeUpperModuleDefine() const {
	return nullptr;
}

void IrisInputModule::NativeModuleDefine() {
	IrisDev_AddClassMethod(this, "update", ModuleIrisInputUpdate, 0, false);
	IrisDev_AddClassMethod(this, "keyboard_press", ModuleIrisInputKeyBoardKeyPress, 1, false);
	IrisDev_AddClassMethod(this, "keyboard_trigger", ModuleIrisInputKeyBoardKeyTrigger, 1, false);
	IrisDev_AddClassMethod(this, "keyboard_repeat", ModuleIrisInputKeyBoardKeyRepeat, 1, false);
	IrisDev_AddClassMethod(this, "mouse_press", ModuleIrisInputMousePress, 1, false);
	IrisDev_AddClassMethod(this, "mouse_trigger", ModuleIrisInputMouseTrigger, 1, false);
	IrisDev_AddClassMethod(this, "mouse_repeat", ModuleIrisInputMouseRepeat, 1, false);
	IrisDev_AddClassMethod(this, "mouse_middle_roll", ModuleIrisInputMouseMiddleRoll, 0, false);
	IrisDev_AddClassMethod(this, "mouse_x_move", ModuleIrisInputMouseXMove, 0, false);
	IrisDev_AddClassMethod(this, "mouse_y_move", ModuleIrisInputMouseYMove, 0, false);
	IrisDev_AddClassMethod(this, "mouse_x", ModuleIrisInputGetCursorX, 0, false);
	IrisDev_AddClassMethod(this, "mouse_y", ModuleIrisInputGetCursorY, 0, false);
	IrisDev_AddClassMethod(this, "mouse_in_rect", ModuleIrisInputCursorInRect, 1, false);
}

IrisInputModule::IrisInputModule() {
	
}

IrisInputModule::~IrisInputModule() {

}