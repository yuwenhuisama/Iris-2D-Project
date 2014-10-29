#include "IrisSprite.h"
#include <cmath>
using namespace Gdiplus;

const double PI = 3.14159;

void IrisSprite::SetInitData(IrisViewport *viewport){
	if (viewport != NULL)
		this->SetViewport(viewport);
}

IrisSprite::IrisSprite(IrisViewport *viewport){
	this->Device = this->Device = ModuleIrisGraphics::Device;

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
		this->viewport = ModuleIrisGraphics::getGViewport();
	this->viewport->addSprite(this);
	this->viewport->sortSprites();

	this->srcRect = new IrisRect(0, 0, 0, 0);
	this->color = NULL;
	this->bitmap = NULL;
	this->tone = new IrisTone(0, 0, 0, 0);

	this->isFlash = false;
	this->flashColor = NULL;
	this->flashDuration = 0;
	this->realFlashDuration = 0;
}

void IrisSprite::SetDevice(IDirect3DDevice9 *Device){
	this->Device = Device;
}

void IrisSprite::Dispose(){
	this->bitmap->Dispose();
	delete this->tone;
	this->tone = NULL;
	delete this->srcRect;
	this->srcRect = NULL;
	if (this->color != NULL){
		delete this->color;
		this->color = NULL;
	}
	delete this->bitmap;
	this->bitmap = NULL;
	this->viewport->deleteSprite(this);
	this->viewport = NULL;
	this->Device = NULL;
}

bool IrisSprite::Disposed(){
	if(this->Device == NULL)
		return true;
	return false;
}

void IrisSprite::AutoDispose(){
	this->bitmap->Dispose();
	delete this->bitmap;
	this->bitmap = NULL;
	this->viewport = NULL;
	this->Device = NULL;
}

void IrisSprite::Flash(const IrisColor *color, int duration){
	this->isFlash = true;
	if (this->flashColor != NULL)
		delete this->flashColor;
	this->flashColor = new IrisColor(color->red, color->green, color->blue, color->alpha);
	this->flashDuration = duration;
	if (this->flashColor != NULL){
		this->flashDuration = this->flashDuration * this->flashColor->alpha / 255;
		this->realFlashDuration = this->flashDuration;// alpha控制闪烁时间
		this->bitmap->PrevFlash(color);
	}
	else{
		this->realFlashDuration = this->flashDuration;
	}
}

void IrisSprite::Update(){
	// 像素从 this->flashColor 递增/递减 到 当前的像素
	// 先将原图每个像素变为flashColor
	// 每一帧变化的像素 flashColor -= (flashColor - 原color) / 帧数
	// 如果变化完毕像素 flashColor != 原color，修正为原color
	// 完毕
	int durationTime = this->flashDuration;

	if (this->isFlash){
		if (this->flashDuration == 0){
			if (this->flashColor != NULL){
				delete this->flashColor;
				this->bitmap->EndFlash();
			}
			else
				this->visible = true;
			this->isFlash = false;
		}
		else {
			if (this->flashColor == NULL){
				this->visible = false;
			}
			else{
				this->bitmap->DoFlash(this->flashColor, this->realFlashDuration);
			}
			this->flashDuration--;
		}
	}
}

void IrisSprite::Draw(){
	if(this->bitmap == NULL)
		return;

	if(this->visible == false)
		return;

 	this->bitmap->Draw(this->opacity, this->viewport, this->srcRect, this->tone);
	/*
	D3DXMATRIX proj;
	Device->SetViewport(&(this->viewport->GetD3DViewport()));
	D3DXMatrixOrthoOffCenterLH(&proj, this->viewport->GetX(), this->viewport->GetWidth(), this->viewport->GetHeight(), this->viewport->GetY(), 0.0f, 9999.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);
	*/
	//-------------Material && Texture Setting-------------
	//this->bitmap->SetOpacity(opacity / 255.0);
	//this->Device->SetMaterial(&(this->bitmap->mtrl));
	IDirect3DTexture9* text = this->bitmap->GetTexture();
	Device->SetTexture(0, text);
	//-------------Matrix Math-------------

	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->SetFVF(Iris2DVertex::FVF);

	D3DXMATRIX translationMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX scalingMatrix;
	D3DXMATRIX resultMatrix;

	D3DXMatrixIdentity(&translationMatrix);
	D3DXMatrixIdentity(&rotationMatrix);
	D3DXMatrixIdentity(&scalingMatrix);

	if(this->angle != 0.0f)
		D3DXMatrixRotationZ(&rotationMatrix, this->angle);

	D3DXMatrixTranslation(&translationMatrix, this->x - this->ox, this->y - this->oy, 0.0f);

	if(this->zoomX != 1.0f || this->zoomY != 1.0f)
		D3DXMatrixScaling(&scalingMatrix, this->zoomX, this->zoomY, 1.0f);

	resultMatrix = rotationMatrix * translationMatrix * scalingMatrix;
	Device->SetTransform(D3DTS_WORLD, &resultMatrix);

	D3DMATERIAL9 mtrl;// = d3d::WHITElibfmodex_MTRL;

	int x = ModuleIrisGraphics::getBrightness();

	mtrl.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
	mtrl.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
	mtrl.Specular = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
	mtrl.Emissive = d3d::BLACK;
	mtrl.Power = 5.0f;

	Device->SetMaterial(&mtrl);

	Device->SetStreamSource(0, this->bitmap->GetVb(), 0, sizeof(Iris2DVertex));
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

}

void IrisSprite::SetViewport(IrisViewport *tviewport){
	this->viewport->deleteSprite(this);
	this->viewport = tviewport;
	this->viewport->addSprite(this);
}

void IrisSprite::AutoSetViewport(IrisViewport *tviewport){
	this->viewport = tviewport;
	this->viewport->addSprite(this);
}

IrisViewport* IrisSprite::GetViewport(){
	return this->viewport;
}

void IrisSprite::SetOpacity(int tOpacity){
	this->opacity = tOpacity;
	this->bitmap->SetOpacity(this->opacity);
}

int IrisSprite::GetOpacity(){
	return this->opacity;
}

void IrisSprite::SetZ(float tZ){
	this->z = tZ;
	this->viewport->sortSprites();
}
float IrisSprite::GetZ(){
	return this->z;
}

IrisColor* IrisSprite::GetColor(){
	return this->color;
}

void IrisSprite::SetColor(IrisColor* color){
	if (this->color != color){
		if (this->color != NULL)
			delete this->color;
		this->color = color;
	}
}

IrisTone* IrisSprite::GetTone(){
	return this->tone;
}

void IrisSprite::SetTone(IrisTone* tone){
	if (this->tone != tone){
		delete this->tone;
		this->tone = tone;
	}
}

IrisRect* IrisSprite::GetSrcRect(){
	return this->srcRect;
}

void IrisSprite::SetSrcRect(IrisRect* srcRect){
	if (this->srcRect != srcRect){
		delete this->srcRect;
		this->srcRect = srcRect;
	}
}

IrisBitmap* IrisSprite::GetBitmap(){
	return this->bitmap;
}

void IrisSprite::SetBitmap(IrisBitmap* bitmap){
	if (this->bitmap != bitmap){
		delete this->bitmap;
		this->bitmap = bitmap;
	}
	this->SetSrcRect(new IrisRect(0.0f, 0.0f, (float)bitmap->width, (float)bitmap->height));
	this->bitmap->Draw(this->opacity, this->viewport, this->srcRect, this->tone);
}

int IrisSprite::GetWidth(){
	return (int)this->srcRect->width;
}

int IrisSprite::GetHeight(){
	return (int)this->srcRect->height;
}

IrisSprite::~IrisSprite(void)
{
	if(!this->Disposed())
		this->Dispose();
	//if(!this->bitmap->Disposed())
	//	this->bitmap->Dispose();
}
