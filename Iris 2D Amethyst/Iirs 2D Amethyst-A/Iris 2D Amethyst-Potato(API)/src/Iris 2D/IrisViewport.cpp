#include "IrisViewport.h"

typedef union
{
    ARGB Color;
    struct
    {
        BYTE Blue;
        BYTE Green;
        BYTE Red;
        BYTE Alpha;
    };
}ARGBQuad, *PARGBQuad;

IrisViewport::IrisViewport(float x, float y, float width, float height){
	this->rect = new IrisRect(x, y, width, height);
	this->Device = this->Device = ModuleIrisGraphics::Device;

	this->visible = true;
	this->z = 0.0f;
	this->ox = this->oy = 0.0f;
	this->tone = new IrisTone(0, 0, 0, 0);
	this->color = NULL;

	MakeBuffer();
	MakeTexture();
	this->Device->CreateOffscreenPlainSurface(this->GetWidth(), this->GetHeight(), D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&this->renderSurface,
		NULL);

	ModuleIrisGraphics::addViewport(this);
	ModuleIrisGraphics::sortViewports();
}

IrisViewport::IrisViewport(const IIrisRect *rect) : IrisViewport(((IrisRect*)rect)->x,
		((IrisRect*)rect)->y, ((IrisRect*)rect)->width, ((IrisRect*)rect)->height){
}

IrisViewport::IrisViewport(){
	this->Device = this->Device = ModuleIrisGraphics::Device;

	this->visible = true;
	this->z = 0.0f;
	this->ox = this->oy = 0.0f;
	this->tone = new IrisTone(0, 0, 0, 0);
	this->color = NULL;
}

void IrisViewport::SetInitData(const IIrisRect *rect){
	SetInitData(((IrisRect*)rect)->x,
		((IrisRect*)rect)->y, ((IrisRect*)rect)->width, ((IrisRect*)rect)->height);
}

void IrisViewport::SetInitData(float x, float y, float width, float height){
	this->rect = new IrisRect(x, y, width, height);
	MakeBuffer();
	MakeTexture();

	this->Device->CreateOffscreenPlainSurface(this->GetWidth(), this->GetHeight(), D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&this->renderSurface,
		NULL);

	ModuleIrisGraphics::addViewport(this);
	ModuleIrisGraphics::sortViewports();

}

IIrisRect* IrisViewport::GetRect(){
	return this->rect;
}

void IrisViewport::SetRect(IIrisRect* rect){
	if (this->rect != rect){
		delete this->rect;
		this->rect = rect;
	}
}

IIrisTone* IrisViewport::GetTone(){
	return this->tone;
}

void IrisViewport::SetTone(IIrisTone* tone){
	if (this->tone != tone){
		delete this->tone;
		this->tone = tone;
	}
}

IIrisColor* IrisViewport::GetColor(){
	return this->color;
}

void IrisViewport::SetColor(IIrisColor* color){
	if (this->color != color){
		if (this->color != NULL){
			delete this->color;
		}
		this->color = color;
	}
}

list<IIrisSprite*> IrisViewport::GetSprites(){
	return this->sprites;
}

bool IrisViewport::compareSpriteWithZ(IIrisSprite *s1, IIrisSprite *s2){
	return s1->GetZ() < s2->GetZ();
}

void IrisViewport::sortSprites(){
	this->sprites.sort(IrisViewport::compareSpriteWithZ);
}

void IrisViewport::MakeBuffer(){
	HRESULT r = this->Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(this->renderVertex), 0);

	if (FAILED(r))
	{
		MessageBox(NULL, L"Create buffer failed!", L"Error", 0);
	}

	Iris2DVertex* v;
	this->renderVertex->Lock(0, 0, (void**)&v, 0);
	v[0] = Iris2DVertex(0.0f - 1,					(float)this->GetHeight() - 1,  0.0f, 0.0f, 1.0f);
	v[1] = Iris2DVertex(0.0f - 1,					  0.0f - 1,					   0.0f, 0.0f, 0.0f);
	v[2] = Iris2DVertex((float)this->GetWidth() - 1,  0.0f - 1,				   	   0.0f, 1.0f, 0.0f);

	v[3] = Iris2DVertex(0.0f - 1,			        (float)this->GetHeight() - 1,  0.0f, 0.0f, 1.0f);
	v[4] = Iris2DVertex((float)this->GetWidth() - 1,  0.0f - 1,					   0.0f, 1.0f, 0.0f);
	v[5] = Iris2DVertex((float)this->GetWidth() - 1,(float)this->GetHeight() - 1,  0.0f, 1.0f, 1.0f);

	this->renderVertex->Unlock();
}

void IrisViewport::MakeTexture(){
	this->Device->CreateTexture(this->GetWidth(), this->GetHeight(), 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &(this->renderTexture), NULL);
}

void IrisViewport::Dispose(){
	list<IIrisSprite*>::iterator it;
	for(it = this->sprites.begin(); it != this->sprites.end(); it++){
		//(*it)->Dispose();
		(*it)->SetViewport(ModuleIrisGraphics::getGViewport());
	}
	//this->sprites.clear();
	ModuleIrisGraphics::deleteViewport(this);
	d3d::Release<IDirect3DVertexBuffer9*>(this->renderVertex);
	d3d::Release<IDirect3DTexture9*>(this->renderTexture);
	delete this->rect;
	delete this->tone;
	if (this->color != NULL)
		delete this->color;
}


void IrisViewport::AutoDispose(){
	list<IIrisSprite*>::iterator it;
	for(it = this->sprites.begin(); it != this->sprites.end(); it++){
		//(*it)->Dispose();
		((IrisSprite*)(*it))->AutoSetViewport(ModuleIrisGraphics::getGViewport());
	}
	//this->sprites.clear();
	d3d::Release<IDirect3DVertexBuffer9*>(this->renderVertex);
	d3d::Release<IDirect3DTexture9*>(this->renderTexture);
}

bool IrisViewport::Disposed(){
	return this->sprites.empty();
}

void IrisViewport::Flash(const IIrisColor *color, int duration){
}

void IrisViewport::Update(){
	//list<IrisSprite*>::iterator it;
	//for(it = this->sprites.begin(); it != this->sprites.end(); it++){
	//	(*it)->Update();
	//}
}

void IrisViewport::addSprite(IIrisSprite* sprite){
	this->sprites.push_back(sprite);
}

void IrisViewport::deleteSprite(IIrisSprite* sprite){
	this->sprites.remove(sprite);
}

void IrisViewport::RenderSurface(){

	if (!this->visible)
		return;

	IDirect3DSurface9 *oldSurface;
	IDirect3DSurface9 *eSurface;

	//Make Link
	this->renderTexture->GetSurfaceLevel(0, &(eSurface));

	//Save old surface
	this->Device->GetRenderTarget(0, &oldSurface);

	//Set new render target
	this->Device->SetRenderTarget(0, eSurface);
	D3DXMATRIX proj;
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)this->GetWidth(), (float)this->GetHeight(), 0.0f, 0, 9999.0f);

	Device->SetTransform(D3DTS_PROJECTION, &proj);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	Device->BeginScene();
	list<IIrisSprite*>::iterator it;
	for(it = this->sprites.begin(); it != this->sprites.end(); it++){
		((IrisSprite*)(*it))->Draw();
	}
	Device->EndScene();

	this->Device->SetRenderTarget(0, oldSurface);
	d3d::Release<IDirect3DSurface9*>(eSurface);
}

void IrisViewport::RenderToBackbuffer(){

	if (!this->visible)
		return;

	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	Device->SetTransform(D3DTS_WORLD, &W);

	D3DXMATRIX translationMatrix;
	D3DXMatrixIdentity(&translationMatrix);
	D3DXMatrixTranslation(&translationMatrix, this->GetX() - this->ox, this->GetY() - this->oy, 0.0f);

	Device->SetTransform(D3DTS_WORLD, &translationMatrix);

	Device->SetTexture(0, this->renderTexture);
	Device->SetFVF(Iris2DVertex::FVF);
	Device->SetStreamSource(0, this->renderVertex, 0, sizeof(Iris2DVertex));
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void IrisViewport::ToneDeal(){

	D3DLOCKED_RECT rect;
	//this->renderTexture->LockRect(0, &rect, NULL, 0);
	IDirect3DSurface9 *eSurface;
	this->renderTexture->GetSurfaceLevel(0, &eSurface);

	this->Device->GetRenderTargetData(eSurface, this->renderSurface);

	HRESULT h = this->renderSurface->LockRect(&rect, 0, D3DLOCK_DISCARD);

	PARGBQuad p2 = (PARGBQuad)rect.pBits;
	PARGBQuad c2 = 0;
	int grayfull;
	for (unsigned int x = 0; x < this->GetWidth(); x++){
		for (unsigned int y = 0; y < this->GetHeight(); y++){
			c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);
			grayfull = (c2->Red * 38 + c2->Green * 75 + c2->Blue * 15) >> 7;
			c2->Red = ((IrisTone*)tone)->red + c2->Red + (grayfull - c2->Red) * ((IrisTone*)tone)->alpha / 255;
			c2->Green = ((IrisTone*)tone)->green + c2->Green + (grayfull - c2->Green) * ((IrisTone*)tone)->alpha / 255;
			c2->Blue = ((IrisTone*)tone)->blue + c2->Blue + (grayfull - c2->Blue) * ((IrisTone*)tone)->alpha / 255;
		}
	}
	this->renderSurface->UnlockRect();
	d3d::Release<IDirect3DSurface9*>(eSurface);
}

float IrisViewport::GetX(){
	return ((IrisRect*)this->rect)->x;
}

float IrisViewport::GetY(){
	return ((IrisRect*)this->rect)->y;
}

UINT IrisViewport::GetWidth(){
	return (UINT)((IrisRect*)this->rect)->width;
}

UINT IrisViewport::GetHeight(){
	return (UINT)((IrisRect*)this->rect)->height;
}

float IrisViewport::GetZ(){
	return this->z;
}
void IrisViewport::SetZ(float tz){
	this->z = tz;
	ModuleIrisGraphics::sortViewports();
}

IrisViewport::~IrisViewport(void)
{
	if(!this->Disposed())
		this->Dispose();
}
