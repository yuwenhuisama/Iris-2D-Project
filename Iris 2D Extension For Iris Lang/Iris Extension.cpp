// Iris Extension.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Iris Extension.h"
#include "IrisMapping/IrisSpriteClass.h"
#include "IrisMapping/IrisRectClass.h"
#include "IrisMapping/IrisBitmapClass.h"
#include "IrisMapping/IrisColorClass.h"
#include "IrisMapping/IrisFontClass.h"
#include "IrisMapping/IrisToneClass.h"
#include "IrisMapping/IrisGraphicsModule.h"
#include "IrisMapping/IrisInputModule.h"
#include "IrisMapping/IrisAudioModule.h"

IRISEXTENSION_API bool IR_Initialize() {
	IrisDev_RegistClass("Sprite", new IrisSpriteClass());
	IrisDev_RegistClass("Rect", new IrisRectClass());
	IrisDev_RegistClass("Bitmap", new IrisBitmapClass());
	IrisDev_RegistClass("Color", new IrisColorClass());
	IrisDev_RegistClass("Font", new IrisFontClass());
	IrisDev_RegistClass("Tone", new IrisToneClass());
	
	IrisDev_RegistModule("Graphics", new IrisGraphicsModule());
	IrisDev_RegistModule("Input", new IrisInputModule());
	IrisDev_RegistModule("Audio", new IrisInputModule());

	return true;
}

IRISEXTENSION_API bool IR_Release() {
	return true;
}


