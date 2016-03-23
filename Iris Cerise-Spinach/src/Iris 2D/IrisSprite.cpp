#include "Iris 2D/IrisSprite.h"
#include "Iris 2D/IrisViewport.h"
#include "Iris 2D/IrisTone.h"
#include "Iris 2D/IrisBitmap.h"
#include "Iris 2D/IrisColor.h"
#include "Iris 2D/IrisRect.h"
#include "Iris 2D/ModuleIrisGraphics.h"
#include <cmath>

namespace Iris2D{
	using namespace Gdiplus;

	const double PI = 3.14159;

	IIrisViewport* IrisSprite::GetViewport(){
		return this->viewport == ModuleIrisGraphics::GetGViewport() ? NULL : this->viewport;
	}

	void IrisSprite::SetInitData(IIrisViewport *viewport, IR_PARAM_RESULT_CT){
		if (viewport)
			this->SetViewport(viewport);
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	IrisSprite::IrisSprite(IIrisViewport *viewport, IR_PARAM_RESULT_CT){
		this->Device = this->Device = ModuleIrisGraphics::GetDevice();

		this->angle = 0.0f;
		this->blendType = 0;
		this->bushDepth = 0;
		this->bushOpacity = 255;
		this->mirror = false;
		this->opacity = 255;
		this->ox = 0.0f;
		this->oy = 0.0f;
		this->visible = true;
		this->waveAmp = 0.0f;
		this->waveLength = 0.0f;
		this->wavePhase = 0.0f;
		this->waveSpeed = 0.0f;
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->zoomX = 1.0f;
		this->zoomY = 1.0f;

		if (viewport != NULL)
			this->viewport = viewport;
		else
			this->viewport = ModuleIrisGraphics::GetGViewport();
		static_cast<IrisViewport*>(this->viewport)->addSprite(static_cast<IIrisSprite*>(this));
		if (!static_cast<IrisViewport*>(this->viewport)->isBatching)
			static_cast<IrisViewport*>(this->viewport)->sortSprites();

		this->srcRect = new IrisRect(0, 0, 0, 0);
		this->color = NULL;
		this->bitmap = NULL;
		this->tone = new IrisTone(0, 0, 0, 0);

		this->isFlash = false;
		this->flashColor = NULL;
		this->flashDuration = 0;
		this->realFlashDuration = 0;

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisSprite::Dispose(IR_PARAM_RESULT_CT){
		//this->bitmap->Dispose();
		delete this->tone;
		this->tone = NULL;
		delete this->srcRect;
		this->srcRect = NULL;
		if (this->color != NULL){
			delete this->color;
			this->color = NULL;
		}
		//delete this->bitmap;
		//this->bitmap = NULL;
		static_cast<IrisViewport*>(this->viewport)->deleteSprite(static_cast<IIrisSprite*>(this));
		this->viewport = NULL;
		this->Device = NULL;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	bool IrisSprite::Disposed(IR_PARAM_RESULT_CT){
		if (this->Device == NULL){
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
			return true;
		}
		IR_PARAM_SET_RESULT(IR_RMEM_ERROR, L"Bitmap Was Already Disposed")
		return false;
	}

	void IrisSprite::AutoDispose(){
		//this->bitmap->Dispose();
		//delete this->bitmap;
		//this->bitmap = NULL;
		//this->viewport = NULL;
		this->Device = NULL;
	}

	void IrisSprite::Flash(const IIrisColor *color, int duration){
		this->isFlash = true;
		if (this->flashColor != NULL){
			delete this->flashColor;
			this->flashColor = NULL;
		}
		TYPE_CHANGE_TO_VARIABLE(icolor, color, const IrisColor*)
		if (color)
			this->flashColor = new IrisColor(icolor->red, icolor->green, icolor->blue, icolor->alpha);
		this->flashDuration = 0;
		if (this->flashColor != NULL){
			this->realFlashDuration = duration * icolor->alpha / 255;
			this->flashDuration = this->realFlashDuration;// alpha控制闪烁时间
			//this->bitmap->PrevFlash(color);
		}
		else{
			this->visible = false;
			this->realFlashDuration = duration;
			this->flashDuration = this->realFlashDuration;
		}
	}

	void IrisSprite::Update(IR_PARAM_RESULT_CT){
		// 像素从 this->flashColor 递增/递减 到 当前的像素
		// 先将原图每个像素变为flashColor
		// 每一帧变化的像素 flashColor -= (flashColor - 原color) / 帧数
		// 如果变化完毕像素 flashColor != 原color，修正为原color
		// 完毕
		//int durationTime = this->flashDuration;

		if (this->isFlash){
			if (this->flashDuration == 0){
				this->realFlashDuration = 0;
				if (this->flashColor){
					delete this->flashColor;
					this->flashColor = NULL;
				}
				else
					this->visible = true;
				this->isFlash = false;
			}
			else{
				--this->flashDuration;
			}
		}

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisSprite::AutoSetViewport(IIrisViewport *tviewport){
		this->viewport = tviewport;
		static_cast<IrisViewport*>(this->viewport)->addSprite(this);
	}

	void IrisSprite::SetViewport(IIrisViewport *tviewport){
		static_cast<IrisViewport*>(this->viewport)->deleteSprite(this);
		this->viewport = tviewport;
		static_cast<IrisViewport*>(this->viewport)->addSprite(this);
		if (!static_cast<IrisViewport*>(this->viewport)->isBatching)
			static_cast<IrisViewport*>(this->viewport)->sortSprites();
	}

	inline int IrisSprite::GetWidth() { return (int)static_cast<IrisRect*>(this->srcRect)->width; }

	inline int IrisSprite::GetHeight() { return (int)static_cast<IrisRect*>(this->srcRect)->height; }

	void IrisSprite::SetZ(float tZ){
		if (tZ < 0.0f || tZ > 9999.0f)
			return;
		if (tZ == this->z)
			return;
		this->z = tZ;
		if (!static_cast<IrisViewport*>(this->viewport)->isBatching)
			static_cast<IrisViewport*>(this->viewport)->sortSprites();
	}

	void IrisSprite::SetBitmap(IIrisBitmap* bitmap, bool isRelease) {
		TYPE_CHANGE_TO_VARIABLE(ibitmap, bitmap, IrisBitmap*)
		if (this->bitmap != bitmap){
			if (this->bitmap != NULL && isRelease)
				delete this->bitmap;
			this->bitmap = bitmap;
		}
		this->SetSrcRect(new IrisRect(0.0f, 0.0f, (float)ibitmap->width, (float)ibitmap->height));
		static_cast<IrisBitmap*>(this->bitmap)->Draw(this->srcRect);
	}

	void IrisSprite::SetSrcRect(IIrisRect* srcRect, bool isRelease) {
		if (this->srcRect != srcRect){
			if (this->srcRect != NULL && isRelease)
				delete this->srcRect;
			this->srcRect = srcRect;
		}
		static_cast<IrisBitmap*>(this->bitmap)->Draw(this->srcRect);
	}

	IrisSprite::~IrisSprite(void)
	{
		if (!this->Disposed())
			this->Dispose();
	}
}