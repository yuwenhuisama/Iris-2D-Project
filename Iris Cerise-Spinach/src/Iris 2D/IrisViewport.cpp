#include "Iris 2D/IrisViewport.h"
#include "Iris 2D/IrisSprite.h"
#include "Iris 2D/IrisColor.h"
#include "Iris 2D/IrisRect.h"
#include "Iris 2D/IrisTone.h"
#include "Iris 2D/ModuleIrisGraphics.h"
#include "Iris 2D/IrisD3DNamespace.h"
#include "Iris 2D/IrisShader.h"

namespace Iris2D{

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

	bool IrisViewport::SpriteSortFunction(IIrisSprite* sp1, IIrisSprite* sp2){ return sp1->GetZ() < sp2->GetZ(); }

	void IrisViewport::BeginBatchSpriteProcess(IIrisViewport* vp) { 
		vp == NULL ? static_cast<IrisViewport*>(ModuleIrisGraphics::GetGViewport())->isBatching = true : static_cast<IrisViewport*>(vp)->isBatching = true;
	}
	void IrisViewport::EndBatchSpriteProcess(IIrisViewport* vp){
		IIrisViewport* tvp = vp == NULL ? ModuleIrisGraphics::GetGViewport() : vp;
		TYPE_CHANGE_TO_VARIABLE(itvp, tvp, IrisViewport*)
		itvp->isBatching = false;
		itvp->sortSprites();
	}

	IrisViewport::IrisViewport(float x, float y, float width, float height, IR_PARAM_RESULT_CT){
		this->rect = new IrisRect(x, y, width, height);

		this->Device = this->Device = ModuleIrisGraphics::GetDevice();
		this->visible = true;
		this->z = 0.0f;
		this->ox = this->oy = 0.0f;
		this->tone = new IrisTone(0, 0, 0, 0);
		this->color = NULL;
		this->isBatching = false;

		if (!MakeBuffer()){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Buffer of Viewport !");
			return;
		}

		if (!MakeTexture()){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Texture of Viewport !");
			return;
		}
		if (FAILED(this->Device->CreateOffscreenPlainSurface(this->GetWidth(), this->GetHeight(), D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&this->renderSurface,
			NULL))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Render Surface of Viewport !");
			return;
		}

		ModuleIrisGraphics::AddViewport(this);
		ModuleIrisGraphics::SortViewports();

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"");
	}

	IrisViewport::IrisViewport(const IIrisRect *rect, IR_PARAM_RESULT_CT) : IrisViewport(static_cast<const IrisRect*>(rect)->x, static_cast<const IrisRect*>(rect)->y, static_cast<const IrisRect*>(rect)->width, static_cast<const IrisRect*>(rect)->height, IR_PARAM)
	{
	}

	IrisViewport::IrisViewport(IR_PARAM_RESULT_CT){
		this->Device = this->Device = ModuleIrisGraphics::GetDevice();

		this->visible = true;
		this->z = 0.0f;
		this->ox = this->oy = 0.0f;
		this->tone = new IrisTone(0, 0, 0, 0);
		this->color = NULL;
		this->isBatching = false;

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"");
	}

	void IrisViewport::SetInitData(const IIrisRect *rect, IR_PARAM_RESULT_CT){
		TYPE_CHANGE_TO_VARIABLE(irect, rect, const IrisRect*)
		SetInitData(irect->x, irect->y, irect->height, irect->width, IR_PARAM);
	}

	void IrisViewport::SetInitData(float x, float y, float width, float height, IR_PARAM_RESULT_CT){
		this->rect = new IrisRect(x, y, width, height);
		if (!MakeBuffer()){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Buffer of Viewport !");
			return;
		}

		if (!MakeTexture()){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Texture of Viewport !");
			return;
		}
		if (FAILED(this->Device->CreateOffscreenPlainSurface(this->GetWidth(), this->GetHeight(), D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&this->renderSurface,
			NULL))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Render Surface of Viewport !");
			return;
		}

		ModuleIrisGraphics::AddViewport(this);
		ModuleIrisGraphics::SortViewports();

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"");
	}

	bool IrisViewport::MakeBuffer(){
		bool flag = true;
		HRESULT r = this->Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(this->renderVertex), 0);

		if (FAILED(r))
		{
			MessageBox(NULL, L"Create buffer failed!", L"Error", 0);
			return false;
		}

		Iris2DVertex* v;
		if(FAILED(this->renderVertex->Lock(0, 0, (void**)&v, 0))) flag = false;
		/* persist to change*/
		/*
		v[0] = Iris2DVertex(0.0f - 1,					(float)this->GetHeight() - 1,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f - 1,					  0.0f - 1,					   0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)this->GetWidth() - 1,  0.0f - 1,				   	   0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f - 1,			        (float)this->GetHeight() - 1,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)this->GetWidth() - 1,  0.0f - 1,					   0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)this->GetWidth() - 1,(float)this->GetHeight() - 1,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
		*/

		v[0] = Iris2DVertex(0.0f - 1, (float)this->GetHeight() - 1, 0.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f - 1, 0.0f - 1, 0.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)this->GetWidth() - 1, 0.0f - 1, 0.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f - 1, (float)this->GetHeight() - 1, 0.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)this->GetWidth() - 1, 0.0f - 1, 0.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)this->GetWidth() - 1, (float)this->GetHeight() - 1, 0.0f, 1.0f, 1.0f);

		if(FAILED(this->renderVertex->Unlock())) flag = false;
		return flag;
	}

	bool IrisViewport::MakeTexture(){
		if (FAILED(this->Device->CreateTexture(this->GetWidth(), this->GetHeight(), 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &(this->renderTexture), NULL)))
			return false;
		return true;
	}

	void IrisViewport::Dispose(IR_PARAM_RESULT_CT){
		list<IIrisSprite*>::iterator it;
		for (it = this->sprites.begin(); it != this->sprites.end(); it++){
			//(*it)->Dispose();
			(*it)->SetViewport(ModuleIrisGraphics::GetGViewport());
		}
		//this->sprites.clear();
		ModuleIrisGraphics::DeleteViewport(this);
		d3d::Release<IDirect3DVertexBuffer9*>(this->renderVertex);
		d3d::Release<IDirect3DTexture9*>(this->renderTexture);
		delete this->rect;
		delete this->tone;
		if (this->color != NULL)
			delete this->color;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"");
	}


	void IrisViewport::AutoDispose(){
		list<IIrisSprite*>::iterator it;
		for (it = this->sprites.begin(); it != this->sprites.end(); it++){
			//(*it)->Dispose();
			static_cast<IrisSprite*>((*it))->AutoSetViewport(ModuleIrisGraphics::GetGViewport());
		}
		//this->sprites.clear();
		d3d::Release<IDirect3DVertexBuffer9*>(this->renderVertex);
		d3d::Release<IDirect3DTexture9*>(this->renderTexture);
	}

	bool IrisViewport::Disposed(IR_PARAM_RESULT_CT){
		bool r = this->sprites.empty();
		if (r)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Alread Disposed")
		return r;
	}

	void IrisViewport::Flash(const IIrisColor *color, int duration){
	}

	void IrisViewport::Update(){
		//list<IrisSprite*>::iterator it;
		//for(it = this->sprites.begin(); it != this->sprites.end(); it++){
		//	(*it)->Update();
		//}
	}

	inline int IrisViewport::GetWidth() { return (int)static_cast<IrisRect*>(this->rect)->width; }

	inline int IrisViewport::GetHeight() { return (int)static_cast<IrisRect*>(this->rect)->height; }

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
		this->renderTexture->GetSurfaceLevel(0, &eSurface);

		//Save old surface
		this->Device->GetRenderTarget(0, &oldSurface);

		//Set new render target
		this->Device->SetRenderTarget(0, eSurface);
		D3DXMATRIX proj;
		D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)this->GetWidth(), (float)this->GetHeight(), 0.0f, 0, 9999.0f);

		// shader
		IrisShader* shader = IrisShader::Instance();
		shader->SetSpriteProjMatrix(proj);

		//Device->SetTransform(D3DTS_PROJECTION, &proj);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		shader->DoSpriteShade(this->sprites);

		Device->EndScene();

		this->Device->SetRenderTarget(0, oldSurface);
		d3d::Release<IDirect3DSurface9*>(eSurface);
		d3d::Release<IDirect3DSurface9*>(oldSurface);

	}

	void IrisViewport::SetZ(float tz) {
		if (tz < 0.0f || tz >= 9999.0f)
			return;
		this->z = tz;
		ModuleIrisGraphics::SortViewports();
	}

	void IrisViewport::OnDeviceLost() {
		this->renderVertex->Release();
		this->renderTexture->Release();
		this->renderSurface->Release();
		//list<IrisSprite*>::iterator it;
		//for (it = this->sprites.begin(); it != this->sprites.end(); ++it){
		//	(*it)->OnDeviceLost();
		//}
	}
	void IrisViewport::OnDeviceRecover() {
		this->MakeBuffer();
		this->MakeTexture();
		if (FAILED(this->Device->CreateOffscreenPlainSurface(this->GetWidth(), this->GetHeight(), D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&this->renderSurface,
			NULL))){
			return;
		}
		//list<IrisSprite*>::iterator it;
		//for (it = this->sprites.begin(); it != this->sprites.end(); ++it){
		//	(*it)->OnDeviceRecover();
		//}
	}

	IrisViewport::~IrisViewport(void)
	{
		if (!this->Disposed())
			this->Dispose();
	}
}