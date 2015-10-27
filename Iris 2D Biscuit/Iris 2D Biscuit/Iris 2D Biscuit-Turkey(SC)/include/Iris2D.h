#ifndef _IRIS2D_H_
#define _IRIS2D_H_

#define IRIS2D_VERSION 0x02061301

#define BEGIN_IRIS_SAFE_WHILE_WITH_CONDITION(condition) \
		while (IrisApp::Instance()->IsRunning() && condition) {

#define END_IRIS_SAFE_WHILE_WITH_CONDITION() }

#define BEGIN_IRIS_SAFE_WHILE() \
		while (IrisApp::Instance()->IsRunning()) {

#define END_IRIS_SAFE_WHILE() }

#define BEGIN_SPRITE_BATCH_PROCESS(viewport) IrisViewport::BeginBatchSpriteProcess(viewport)
#define END_SPRITE_BATCH_PROCESS(viewport) IrisViewport::EndBatchSpriteProcess(viewport)

#include "XMLDefine.h"
#include "IrisError.h"
#include "IrisBitmap.h"
#include "IrisViewport.h"
#include "IrisSprite.h"
#include "IrisFont.h"
#include "IrisColor.h"
#include "IrisTone.h"
#include "IrisRect.h"
#include "IrisApp.h"
#include "IrisShader.h"
#include "IrisEncripedResourceManager.h"

#include "ModuleIrisAudio.h"
#include "ModuleIrisGraphics.h"
#include "ModuleIrisInput.h"

#endif