// Iris Extension.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Iris Extension.h"
#include "IrisMapping/IrisSprite.h"
#include "IrisPointer.h"
#include "IrisMapping/IrisRectD.h"
#include "IrisMapping/IrisBitmap.h"
#include "IrisMapping/IrisColor.h"
#include "IrisMapping/IrisGraphics.h"

IRISEXTENSION_API bool IR_Initialize() {
	IrisDev_RegistClass("Sprite", new IrisSprite());
	IrisDev_RegistClass("Pointer", new IrisPointer());
	IrisDev_RegistClass("Rect", new IrisRectD());
	IrisDev_RegistClass("Bitmap", new IrisBitmap());
	IrisDev_RegistClass("Color", new IrisColor());
	
	IrisDev_RegistModule("Graphics", new IrisGraphics());

	return true;
}

IRISEXTENSION_API bool IR_Release() {
	return true;
}


