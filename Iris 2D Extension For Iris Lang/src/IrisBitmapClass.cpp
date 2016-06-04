#include "IrisMapping/IrisBitmapClass.h"

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

IrisValue IrisBitmapClass::Initialize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	if (ivsVariableValues->GetSize() == 2) {
		auto& ivWidth = ivsVariableValues->GetValue(0);
		auto& ivHeight = ivsVariableValues->GetValue(1);

		if (!IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto nWidth = IrisDev_GetInt(ivWidth);
		auto nHeight = IrisDev_GetInt(ivHeight);

		pBitmap->SetInitData(nWidth, nHeight);

		IrisDev_SetObjectInstanceVariable(ivObj, "@width", ivWidth);
		IrisDev_SetObjectInstanceVariable(ivObj, "@height", ivHeight);
		IrisDev_SetObjectInstanceVariable(ivObj, "@font", IrisDev_Nil());

		return ivObj;
	}
	else if (ivsVariableValues->GetSize() == 1) {
		auto& ivFilename = ivsVariableValues->GetValue(0);

		if (!IrisDev_CheckClassIsString(ivFilename)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a String");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto cFilename = IrisDev_GetString(ivFilename);

		string sFilename = string(cFilename);
		wstring wsFilename = StringToWString(sFilename);

		pBitmap->SetInitData(wsFilename);

		IrisDev_SetObjectInstanceVariable(ivObj, "@width", IrisDev_CreateIntegerInstanceByInstantValue(pBitmap->GetWidth()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@height", IrisDev_CreateIntegerInstanceByInstantValue(pBitmap->GetHeight()));
		IrisDev_SetObjectInstanceVariable(ivObj, "@font", IrisDev_Nil());

		return ivObj;
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list");
		return ivObj;
	}
}

IrisValue IrisBitmapClass::Dispose(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);

	pBitmap->Dispose();

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::Disposed(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);

	if (pBitmap->Disposed()) {
		return IrisDev_True();
	}
	else {
		return IrisDev_False();
	}
}

IrisValue IrisBitmapClass::Blt(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValue->GetValue(0);
	auto& ivY = ivsValue->GetValue(1);
	auto& ivSrcBitmap = ivsValue->GetValue(2);
	auto& ivRect = ivsValue->GetValue(3);
	auto& ivOpacity = ivsValue->GetValue(4);

	if (!IrisDev_CheckClassIsInteger(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	if (!IrisDev_CheckClass(ivSrcBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be a Bitmap");
	}

	if (!IrisDev_CheckClass(ivRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be a Rect");
	}

	if (!IrisDev_CheckClassIsInteger(ivOpacity)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 5: it must be an Integer");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto nX = IrisDev_GetInt(ivX);
	auto nY = IrisDev_GetInt(ivY);
	auto pSrcBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivSrcBitmap);
	auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);
	auto nOpacity = IrisDev_GetInt(ivOpacity);

	pBitmap->Blt(nX, nY, pSrcBitmap, pRect, nOpacity);

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::StretchBlt(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivDestRect = ivsValue->GetValue(0);
	auto& ivSrcBitmap = ivsValue->GetValue(1);
	auto& ivSrcRect = ivsValue->GetValue(2);
	auto& ivOpacity = ivsValue->GetValue(3);

	if (!IrisDev_CheckClass(ivDestRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
	}

	if (!IrisDev_CheckClass(ivSrcBitmap, "Bitmap")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a Bitmap");
	}

	if (!IrisDev_CheckClass(ivSrcRect, "Rect")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be a Rect");
	}

	if (!IrisDev_CheckClassIsInteger(ivOpacity)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be a Integer");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto pDestRect = IrisDev_GetNativePointer<IIrisRect*>(ivDestRect);
	auto pSrcBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivSrcBitmap);
	auto pSrcRect = IrisDev_GetNativePointer<IIrisRect*>(ivSrcRect);
	auto nOpacity = IrisDev_GetInt(ivOpacity);

	pBitmap->StretchBlt(pDestRect, pSrcBitmap, pSrcRect, nOpacity);

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::FillRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	if (ivsVariableValues->GetSize() == 5) {
		auto& ivX = ivsVariableValues->GetValue(0);
		auto& ivY = ivsVariableValues->GetValue(1);
		auto& ivWidth = ivsVariableValues->GetValue(2);
		auto& ivHeight = ivsVariableValues->GetValue(3);
		auto& ivColor = ivsVariableValues->GetValue(4);

		if (!IrisDev_CheckClassIsInteger(ivX)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivY)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
		}

		if (!IrisDev_CheckClass(ivColor, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 5: it must be a Color");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto nX = IrisDev_GetInt(ivX);
		auto nY = IrisDev_GetInt(ivY);
		auto nWidth = IrisDev_GetInt(ivWidth);
		auto nHeight = IrisDev_GetInt(ivHeight);
		auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);

		pBitmap->FillRect(nX, nY, nWidth, nHeight, pColor);

		return IrisDev_Nil();
	}
	else if (ivsVariableValues->GetSize() == 2) {
		auto& ivRect = ivsVariableValues->GetValue(0);
		auto& ivColor = ivsVariableValues->GetValue(1);

		if (!IrisDev_CheckClass(ivRect, "Rect")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		}

		if (!IrisDev_CheckClass(ivColor, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a Color");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);
		auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);

		pBitmap->FillRect(pRect, pColor);

		return IrisDev_Nil();
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list.");
		return IrisDev_Nil();
	}
}

IrisValue IrisBitmapClass::GradientFillRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	if (ivsVariableValues->GetSize() == 7) {
		auto& ivX = ivsVariableValues->GetValue(0);
		auto& ivY = ivsVariableValues->GetValue(1);
		auto& ivWidth = ivsVariableValues->GetValue(2);
		auto& ivHeight = ivsVariableValues->GetValue(3);
		auto& ivColor1 = ivsVariableValues->GetValue(4);
		auto& ivColor2 = ivsVariableValues->GetValue(5);
		auto& ivVertical = ivsVariableValues->GetValue(6);

		if (!IrisDev_CheckClassIsInteger(ivX)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivY)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
		}

		if (!IrisDev_CheckClass(ivColor1, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 5: it must be a Color");
		}

		if (!IrisDev_CheckClass(ivColor2, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 6: it must be a Color");
		}

		if (ivVertical != IrisDev_True() && ivVertical != IrisDev_False()) {
			IrisDev_GroanIrregularWithString("Invaild parameter 7: it must be a Bool");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto nX = IrisDev_GetInt(ivX);
		auto nY = IrisDev_GetInt(ivY);
		auto nWidth = IrisDev_GetInt(ivWidth);
		auto nHeight = IrisDev_GetInt(ivHeight);
		auto pColor1 = IrisDev_GetNativePointer<IIrisColor*>(ivColor1);
		auto pColor2 = IrisDev_GetNativePointer<IIrisColor*>(ivColor2);
		//auto bVertical = static_cast<bool>(IrisDev_GetInt(ivVertical));
		auto bVertical = ivVertical == IrisDev_True() ? true : false;
		pBitmap->GradientFillRect(nX, nY, nWidth, nHeight, pColor1, pColor2, bVertical);

		return IrisDev_Nil();
	}
	else if (ivsVariableValues->GetSize() == 4) {
		auto& ivRect = ivsVariableValues->GetValue(0);
		auto& ivColor1 = ivsVariableValues->GetValue(1);
		auto& ivColor2 = ivsVariableValues->GetValue(2);
		auto& ivVertical = ivsVariableValues->GetValue(3);

		if (!IrisDev_CheckClass(ivRect, "Rect")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		}

		if (!IrisDev_CheckClass(ivColor1, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a Color");
		}

		if (!IrisDev_CheckClass(ivColor2, "Color")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be a Color");
		}

		if (ivVertical != IrisDev_True() && ivVertical != IrisDev_False()) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be a Bool");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);
		auto pColor1 = IrisDev_GetNativePointer<IIrisColor*>(ivColor1);
		auto pColor2 = IrisDev_GetNativePointer<IIrisColor*>(ivColor2);
		//auto bVertical = static_cast<bool>(IrisDev_GetInt(ivVertical));
		auto bVertical = ivVertical == IrisDev_True() ? true : false;

		pBitmap->GradientFillRect(pRect, pColor1, pColor2, bVertical);

		return IrisDev_Nil();
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list.");
		return IrisDev_Nil();
	}
}

IrisValue IrisBitmapClass::Clear(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);

	pBitmap->Clear();

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::ClearRect(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	if (ivsVariableValues->GetSize() == 4) {
		auto& ivX = ivsVariableValues->GetValue(0);
		auto& ivY = ivsVariableValues->GetValue(1);
		auto& ivWidth = ivsVariableValues->GetValue(2);
		auto& ivHeight = ivsVariableValues->GetValue(3);

		if (!IrisDev_CheckClassIsInteger(ivX)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivY)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto nX = IrisDev_GetInt(ivX);
		auto nY = IrisDev_GetInt(ivY);
		auto nWidth = IrisDev_GetInt(ivWidth);
		auto nHeight = IrisDev_GetInt(ivHeight);

		pBitmap->ClearRect(nX, nY, nWidth, nHeight);

		return IrisDev_Nil();
	}
	else if (ivsVariableValues->GetSize() == 1) {
		auto& ivRect = ivsVariableValues->GetValue(0);

		if (!IrisDev_CheckClass(ivRect, "Rect")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);

		pBitmap->ClearRect(pRect);

		return IrisDev_Nil();
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list.");
		return IrisDev_Nil();
	}
}

IrisValue IrisBitmapClass::GetPixel(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValue->GetValue(0);
	auto& ivY = ivsValue->GetValue(1);

	if (!IrisDev_CheckClassIsInteger(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto nX = IrisDev_GetInt(ivX);
	auto nY = IrisDev_GetInt(ivY);
	auto pColor = pBitmap->GetPixel(nX, nY);

	auto ivsParam = IrisDev_CreateIrisValuesList(4);
	ivsParam->SetValue(0, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetRed()));
	ivsParam->SetValue(1, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetGreen()));
	ivsParam->SetValue(2, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetBlue()));
	ivsParam->SetValue(3, IrisDev_CreateIntegerInstanceByInstantValue(pColor->GetAlpha()));

	auto ivResult = IrisDev_CreateNormalInstance(IrisDev_GetClass("Color"), ivsParam, nullptr);
	IrisDev_ReleaseIrisValuesList(ivsParam);

	return ivResult;
}

IrisValue IrisBitmapClass::SetPixel(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivX = ivsValue->GetValue(0);
	auto& ivY = ivsValue->GetValue(1);
	auto& ivColor = ivsValue->GetValue(2);

	if (!IrisDev_CheckClassIsInteger(ivX)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (!IrisDev_CheckClassIsInteger(ivY)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	if (!IrisDev_CheckClass(ivColor, "Color")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be a Color");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto nX = IrisDev_GetInt(ivX);
	auto nY = IrisDev_GetInt(ivY);
	auto pColor = IrisDev_GetNativePointer<IIrisColor*>(ivColor);

	pBitmap->SetPixel(nX, nY, pColor);

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::HueChange(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivHue = ivsValue->GetValue(0);

	if (!IrisDev_CheckClassIsInteger(ivHue)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto nHue = IrisDev_GetInt(ivHue);

	pBitmap->HueChange(static_cast<float>(nHue));

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::Blur(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);

	pBitmap->Blur();

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::RadialBlur(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivAngle = ivsValue->GetValue(0);
	auto& ivDivision = ivsValue->GetValue(1);

	if (!IrisDev_CheckClassIsInteger(ivAngle)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
	}

	if (IrisDev_CheckClassIsInteger(ivDivision)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto fAngle = static_cast<float>(IrisDev_GetFloat(ivAngle));
	auto nDivision = IrisDev_GetInt(ivDivision);

	pBitmap->RadialBlur(fAngle, nDivision);

	return IrisDev_Nil();
}

IrisValue IrisBitmapClass::TextSize(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFont = ivsValue->GetValue(0);
	auto& ivStr = ivsValue->GetValue(1);

	if (!IrisDev_CheckClass(ivFont, "Font")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Font");
	}

	if (!IrisDev_CheckClassIsString(ivStr)) {
		IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a String");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivFont);
	auto cStr = IrisDev_GetString(ivStr);

	string sStr = string(cStr);
	wstring wsStr = StringToWString(sStr);
	auto nSize = pBitmap->TextSize(pFont, wsStr);

	return IrisDev_CreateIntegerInstanceByInstantValue(nSize);
}

IrisValue IrisBitmapClass::IrisDrawText(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	if (ivsVariableValues->GetSize() == 6) {
		auto& ivX = ivsVariableValues->GetValue(0);
		auto& ivY = ivsVariableValues->GetValue(1);
		auto& ivWidth = ivsVariableValues->GetValue(2);
		auto& ivHeight = ivsVariableValues->GetValue(3);
		auto& ivStr = ivsVariableValues->GetValue(4);
		auto& ivAlign = ivsVariableValues->GetValue(5);

		if (!IrisDev_CheckClassIsInteger(ivX)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivY)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivWidth)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsInteger(ivHeight)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 4: it must be an Integer");
		}

		if (!IrisDev_CheckClassIsString(ivStr)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 5: it must be a String");
		}

		if (!IrisDev_CheckClassIsInteger(ivAlign)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 6: it must be an Integer");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto nX = IrisDev_GetInt(ivX);
		auto nY = IrisDev_GetInt(ivY);
		auto nWidth = IrisDev_GetInt(ivWidth);
		auto nHeight = IrisDev_GetInt(ivHeight);
		auto cStr = IrisDev_GetString(ivStr);

		string sStr = string(cStr);
		wstring wsStr = StringToWString(sStr);

		auto nAlign = IrisDev_GetInt(ivAlign);

		pBitmap->IrisDrawText(nX, nY, nWidth, nHeight, wsStr, nAlign);

		return IrisDev_Nil();
	}
	else if (ivsVariableValues->GetSize() == 3) {
		auto& ivRect = ivsVariableValues->GetValue(0);
		auto& ivStr = ivsVariableValues->GetValue(1);
		auto& ivAlign = ivsVariableValues->GetValue(2);

		if (!IrisDev_CheckClass(ivRect, "Rect")) {
			IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Rect");
		}

		if (!IrisDev_CheckClassIsString(ivStr)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 2: it must be a String");
		}

		if (!IrisDev_CheckClassIsInteger(ivAlign)) {
			IrisDev_GroanIrregularWithString("Invaild parameter 3: it must be an Integer");
		}

		auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
		auto pRect = IrisDev_GetNativePointer<IIrisRect*>(ivRect);
		auto cStr = IrisDev_GetString(ivStr);

		string sStr = string(cStr);
		wstring wsStr = StringToWString(sStr);

		auto nAlign = IrisDev_GetInt(ivAlign);

		pBitmap->IrisDrawText(pRect, wsStr, nAlign);

		return IrisDev_Nil();
	}
	else {
		IrisDev_GroanIrregularWithString("Invaild parameter list.");
		return IrisDev_Nil();
	}
}

IrisValue IrisBitmapClass::GetWidth(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@width");
}

IrisValue IrisBitmapClass::GetHeight(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@height");
}

IrisValue IrisBitmapClass::GetFont(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	return IrisDev_GetObjectInstanceVariable(ivObj, "@font");
}

IrisValue IrisBitmapClass::SetFont(IrisValue & ivObj, IIrisValues * ivsValue, IIrisValues * ivsVariableValues, IIrisContextEnvironment * pContextEnvironment) {
	auto& ivFont = ivsValue->GetValue(0);

	if (!IrisDev_CheckClass(ivFont, "Font")) {
		IrisDev_GroanIrregularWithString("Invaild parameter 1: it must be a Font");
	}

	auto pBitmap = IrisDev_GetNativePointer<IIrisBitmap*>(ivObj);
	auto pFont = IrisDev_GetNativePointer<IIrisFont*>(ivFont);

	pBitmap->SetFont(pFont);

	IrisDev_SetObjectInstanceVariable(ivObj, "@font", ivFont);

	return IrisDev_Nil();
}

void IrisBitmapClass::Mark(void * pNativePointer) {}

const char * IrisBitmapClass::NativeClassNameDefine() const {
	return "Bitmap";
}

IIrisClass * IrisBitmapClass::NativeSuperClassDefine() const {
	return IrisDev_GetClass("Object");
}

int IrisBitmapClass::GetTrustteeSize(void * pNativePointer) {
	return sizeof(IIrisBitmap);
}

void * IrisBitmapClass::NativeAlloc() {
	return GetTravialIIrisBitmap();
}

void IrisBitmapClass::NativeFree(void * pNativePointer) {
	ReleaseIrisBitmap(static_cast<IIrisBitmap*>(pNativePointer));
}

void IrisBitmapClass::NativeClassDefine() {
	IrisDev_AddInstanceMethod(this, "__format", Initialize, 0, true);
	IrisDev_AddInstanceMethod(this, "dispose", Dispose, 0, false);
	IrisDev_AddInstanceMethod(this, "disposed", Disposed, 0, false);
	IrisDev_AddInstanceMethod(this, "blt", Blt, 5, false);
	IrisDev_AddInstanceMethod(this, "stretch_blt", StretchBlt, 4, false);
	IrisDev_AddInstanceMethod(this, "fill_rect", FillRect, 0, true);
	IrisDev_AddInstanceMethod(this, "gradient_fill_rect", GradientFillRect, 0, true);
	IrisDev_AddInstanceMethod(this, "clear", Clear, 0, false);
	IrisDev_AddInstanceMethod(this, "clear_rect", ClearRect, 0, true);
	IrisDev_AddInstanceMethod(this, "get_pixel", GetPixel, 2, false);
	IrisDev_AddInstanceMethod(this, "set_pixel", SetPixel, 3, false);
	IrisDev_AddInstanceMethod(this, "hue_change", HueChange, 1, false);
	IrisDev_AddInstanceMethod(this, "blur", Blur, 0, false);
	IrisDev_AddInstanceMethod(this, "radial_blur", RadialBlur, 2, false);
	IrisDev_AddInstanceMethod(this, "text_size", TextSize, 2, false);
	IrisDev_AddInstanceMethod(this, "draw_text", IrisDrawText, 0, true);

	IrisDev_AddGetter(this, "@width", GetWidth);
	IrisDev_AddGetter(this, "@height", GetHeight);
	IrisDev_AddGetter(this, "@font", GetFont);

	IrisDev_AddSetter(this, "@font", SetFont);
}

IrisBitmapClass::IrisBitmapClass() {

}

IrisBitmapClass::~IrisBitmapClass() {

}
