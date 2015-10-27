#include "IrisSprite.h"
#include <cmath>

namespace Iris2D{
	using namespace Gdiplus;

	const double PI = 3.14159;

	IrisViewport* IrisSprite::GetViewport(){
		return this->viewport == ModuleIrisGraphics::GetGViewport() ? NULL : this->viewport;
	}

	void IrisSprite::SetInitData(IrisViewport *viewport, IR_PARAM_RESULT_CT){
		if (viewport)
			this->SetViewport(viewport);
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	IrisSprite::IrisSprite(IrisViewport *viewport, IR_PARAM_RESULT_CT){
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
		this->viewport->addSprite(this);
		if (!this->viewport->isBatching)
			this->viewport->sortSprites();

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
		this->viewport->deleteSprite(this);
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

	void IrisSprite::Flash(const IrisColor *color, int duration){
		this->isFlash = true;
		if (this->flashColor != NULL){
			delete this->flashColor;
			this->flashColor = NULL;
		}
		if (color)
			this->flashColor = new IrisColor(color->red, color->green, color->blue, color->alpha);
		this->flashDuration = 0;
		if (this->flashColor != NULL){
			this->realFlashDuration = duration * color->alpha / 255;
			this->flashDuration = this->realFlashDuration;// alpha������˸ʱ��
			//this->bitmap->PrevFlash(color);
		}
		else{
			this->visible = false;
			this->realFlashDuration = duration;
			this->flashDuration = this->realFlashDuration;
		}
	}

	void IrisSprite::Update(IR_PARAM_RESULT_CT){
		// ���ش� this->flashColor ����/�ݼ� �� ��ǰ������
		// �Ƚ�ԭͼÿ�����ر�ΪflashColor
		// ÿһ֡�仯������ flashColor -= (flashColor - ԭcolor) / ֡��
		// ����仯������� flashColor != ԭcolor������Ϊԭcolor
		// ���
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

	void IrisSprite::AutoSetViewport(IrisViewport *tviewport){
		this->viewport = tviewport;
		this->viewport->addSprite(this);
	}

	void IrisSprite::SetViewport(IrisViewport *tviewport){
		this->viewport->deleteSprite(this);
		this->viewport = tviewport;
		this->viewport->addSprite(this);
		if (!this->viewport->isBatching)
			this->viewport->sortSprites();
	}

	void IrisSprite::SetZ(float tZ){
		if (tZ < 0.0f || tZ > 9999.0f)
			return;
		if (tZ == this->z)
			return;
		this->z = tZ;
		if (!this->viewport->isBatching)
			this->viewport->sortSprites();
	}

	void IrisSprite::SetBitmap(IrisBitmap* bitmap, bool isRelease) {
		if (this->bitmap != bitmap){
			if (this->bitmap != NULL && isRelease)
				delete this->bitmap;
			this->bitmap = bitmap;
		}
		this->SetSrcRect(new IrisRect(0.0f, 0.0f, (float)bitmap->width, (float)bitmap->height));
		this->bitmap->Draw(this->srcRect);
	}

	void IrisSprite::SetSrcRect(IrisRect* srcRect, bool isRelease) {
		if (this->srcRect != srcRect){
			if (this->srcRect != NULL && isRelease)
				delete this->srcRect;
			this->srcRect = srcRect;
		}
		this->bitmap->Draw(this->srcRect);
	}

	IrisSprite::~IrisSprite(void)
	{
		if (!this->Disposed())
			this->Dispose();
	}
}