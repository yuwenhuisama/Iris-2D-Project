#include "IrisShader.h"

IrisShader* IrisShader::instance = NULL;

IrisShader::IrisShader()
{
	Device = NULL;

	spriteEffect = NULL;
	viewportEffect = NULL;
	backBufferEffect = NULL;
	transitionEffect = NULL;

	spriteWorldMatrixHandle = 0;
	spriteProjMatrixHandle = 0;
	viewportWorldMatrixHandle = 0;
	viewportProjMatrixHandle = 0;
	backBufferWorldMatrixHandle = 0;
	backBufferProjMatrixHandle = 0;

	transitionProjMatrixHandle = 0;
	transitionWorldMatrixHandle = 0;
	transitionPreTexHandle = 0;
	transitionMaskTexHandle = 0;
	transitionTargetTexHandle = 0;
	transitionCmpPixelHandle = 0;

	spriteToneVectorHandle = 0;
	spriteOpacityHandle = 0;
	spriteBrightnessHandle = 0;

	spriteTexHandle = 0;
	viewportTexHandle = 0;
	backBufferTexHandle = 0;
	spriteTechHandle = 0;
	viewportTechHandle = 0;
	backBufferTechHandle = 0;
}

bool IrisShader::InitShader(string shaderName, int index){

	//
	// Create effect.
	//

	ID3DXEffect** effect = NULL;
	ID3DXBuffer* errorBuffer = 0;
	switch (index)
	{
	case 0:
		effect = &spriteEffect;
		break;
	case 1:
		effect = &viewportEffect;
		break;
	case 2:
		effect = &backBufferEffect;
		break;
	case 3:
		effect = &transitionEffect;
	}
	HRESULT hr = D3DXCreateEffectFromFileA(
		Device,
		shaderName.c_str(),
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_DEBUG, // compile flags
		0,                // don't share parameters
		effect,
		&errorBuffer);

	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		d3d::Release<ID3DXBuffer*>(errorBuffer);
	}

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXCreateEffectFromFile() - FAILED", 0, 0);
		return false;
	}

	return true;
}

bool IrisShader::InitShader(IDirect3DDevice9* td, wstring spriteShaderFileName,
	wstring viewportShaderFileName, wstring backBufferShaderFileName, wstring transitionShaderFileName){

	this->Device = td;

	bool result;

	result = InitShader(WStringToString(spriteShaderFileName), 0);
	if (!result)
		return false;
	result = InitShader(WStringToString(viewportShaderFileName), 1);
	if (!result)
		return false;
	result = InitShader(WStringToString(backBufferShaderFileName), 2);
	if (!result)
		return false;
	result = InitShader(WStringToString(transitionShaderFileName), 3);
	if (!result)
		return false;

	spriteWorldMatrixHandle = spriteEffect->GetParameterByName(0, "WorldMatrix");
	spriteProjMatrixHandle = spriteEffect->GetParameterByName(0, "ProjMatrix");
	spriteTexHandle = spriteEffect->GetParameterByName(0, "Tex");
	spriteToneVectorHandle = spriteEffect->GetParameterByName(0, "ToneVector");
	spriteOpacityHandle = spriteEffect->GetParameterByName(0, "Opacity");
	spriteBrightnessHandle = spriteEffect->GetParameterByName(0, "Brightness");

	spriteTechHandle = spriteEffect->GetTechniqueByName("LightAndTexture");

	viewportWorldMatrixHandle = viewportEffect->GetParameterByName(0, "WorldMatrix");
	viewportProjMatrixHandle = viewportEffect->GetParameterByName(0, "ProjMatrix");
	viewportTexHandle = viewportEffect->GetParameterByName(0, "Tex");
	viewportToneVectorHandle = viewportEffect->GetParameterByName(0, "ToneVector");

	viewportTechHandle = viewportEffect->GetTechniqueByName("LightAndTexture");

	backBufferWorldMatrixHandle = backBufferEffect->GetParameterByName(0, "WorldMatrix");
	backBufferProjMatrixHandle = backBufferEffect->GetParameterByName(0, "ProjMatrix");
	backBufferTexHandle = backBufferEffect->GetParameterByName(0, "Tex");
	backBufferTechHandle = backBufferEffect->GetTechniqueByName("LightAndTexture");

	transitionWorldMatrixHandle = transitionEffect->GetParameterByName(0, "WorldMatrix");
	transitionProjMatrixHandle = transitionEffect->GetParameterByName(0, "ProjMatrix");
	transitionPreTexHandle = transitionEffect->GetParameterByName(0, "PreTex");
	transitionMaskTexHandle = transitionEffect->GetParameterByName(0, "MaskTex");
	transitionTargetTexHandle = transitionEffect->GetParameterByName(0, "TargetTex");
	transitionCmpPixelHandle = transitionEffect->GetParameterByName(0, "CmpPixel");

	transitionTechHandle = transitionEffect->GetTechniqueByName("LightAndTexture");

	spriteEffect->SetTechnique(spriteTechHandle);
	viewportEffect->SetTechnique(viewportTechHandle);
	backBufferEffect->SetTechnique(backBufferTechHandle);
	transitionEffect->SetTechnique(transitionTechHandle);

	return true;
}

void IrisShader::SetSpriteProjMatrix(const D3DXMATRIX& projMatrix){
	spriteEffect->SetMatrix(spriteProjMatrixHandle, &projMatrix);
}

void IrisShader::SetViewportProjMatrix(const D3DXMATRIX& projMatrix){
	viewportEffect->SetMatrix(viewportProjMatrixHandle, &projMatrix);

}
void IrisShader::SetBackbufferProjMatrix(const D3DXMATRIX& projMatrix){
	backBufferEffect->SetMatrix(backBufferProjMatrixHandle, &projMatrix);
}

bool IrisShader::DoSpriteShade(list<IrisSprite*>& sprites){

	UINT numPasses = 0;
	//spriteEffect->SetTechnique(spriteTechHandle);

	IrisSprite* sp = NULL;

	list<IrisSprite*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); it++){
		sp = *it;

		if (sp->bitmap == NULL)
			continue;

		if (sp->visible == false)
			continue;

		sp->bitmap->Draw(sp->viewport, sp->srcRect);
		//-------------Material && Texture Setting-------------
		IDirect3DTexture9* text = sp->bitmap->GetTexture();
		spriteEffect->SetTexture(spriteTexHandle, text);

		//-------------Tone && Opacity-------------
		D3DXVECTOR4 tone(sp->tone->GetRed(), sp->tone->GetBlue(), sp->tone->GetGreen(), sp->tone->GetAlpha());
		spriteEffect->SetVector(spriteToneVectorHandle, &tone);
		spriteEffect->SetInt(spriteOpacityHandle, sp->opacity);

		//-------------Matrix Math-------------

		D3DXMATRIX translationMatrix;
		D3DXMATRIX rotationMatrix;
		D3DXMATRIX scalingMatrix;
		D3DXMATRIX resultMatrix;

		D3DXMatrixIdentity(&translationMatrix);
		D3DXMatrixIdentity(&rotationMatrix);
		D3DXMatrixIdentity(&scalingMatrix);

		if (sp->angle != 0.0f)
			D3DXMatrixRotationZ(&rotationMatrix, sp->angle);

		D3DXMatrixTranslation(&translationMatrix, sp->x - sp->ox, sp->y - sp->oy, 0.0f);

		if (sp->zoomX != 1.0f || sp->zoomY != 1.0f)
			D3DXMatrixScaling(&scalingMatrix, sp->zoomX, sp->zoomY, 1.0f);

		resultMatrix = rotationMatrix * translationMatrix * scalingMatrix;

		spriteEffect->SetMatrix(spriteWorldMatrixHandle, &resultMatrix);

		//D3DMATERIAL9 mtrl;// = d3d::WHITElibfmodex_MTRL;

		//int x = ModuleIrisGraphics::getBrightness();

		//mtrl.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		//mtrl.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		//mtrl.Specular = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		//mtrl.Emissive = d3d::BLACK;
		//mtrl.Power = 5.0f;
		//Device->SetMaterial(&mtrl);

		spriteEffect->SetInt(spriteBrightnessHandle, ModuleIrisGraphics::getBrightness());

		spriteEffect->Begin(&numPasses, 0);

		for (int i = 0; i < numPasses; i++)
		{
			spriteEffect->BeginPass(i);
			Device->SetStreamSource(0, sp->bitmap->GetVb(), 0, sizeof(Iris2DVertex));
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			spriteEffect->EndPass();
		}

		spriteEffect->End();
	}

	return true;
}

bool IrisShader::DoViewportShade(list<IrisViewport*>& viewports){

	UINT numPasses = 0;
	IrisViewport* vp = NULL;

	list<IrisViewport*>::iterator it;
	for (it = viewports.begin(); it != viewports.end(); it++){
		vp = *it;

		if (!vp->visible)
			continue;

		viewportEffect->SetTexture(viewportTexHandle, vp->renderTexture);

		D3DXMATRIX translationMatrix;
		D3DXMatrixIdentity(&translationMatrix);
		D3DXMatrixTranslation(&translationMatrix, vp->GetX() - vp->ox, vp->GetY() - vp->oy, 0.0f);
		viewportEffect->SetMatrix(viewportWorldMatrixHandle, &translationMatrix);

		//-------------Tone-------------
		D3DXVECTOR4 tone(vp->tone->GetRed(), vp->tone->GetBlue(), vp->tone->GetGreen(), vp->tone->GetAlpha());
		viewportEffect->SetVector(viewportToneVectorHandle, &tone);

		viewportEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			viewportEffect->BeginPass(i);
			Device->SetStreamSource(0, vp->renderVertex, 0, sizeof(Iris2DVertex));
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			viewportEffect->EndPass();
		}
		viewportEffect->End();
	}

	return true;
}

bool IrisShader::DoBackBufferShade(){

	UINT numPasses = 0;
	backBufferEffect->SetTechnique(backBufferTechHandle);
	backBufferEffect->SetTexture(backBufferTexHandle, ModuleIrisGraphics::ExchangeTexture);

	D3DXMATRIX M;
	D3DXMatrixIdentity(&M);
	backBufferEffect->SetMatrix(backBufferWorldMatrixHandle, &M);

	backBufferEffect->Begin(&numPasses, 0);
	for (int i = 0; i < numPasses; i++)
	{
		backBufferEffect->BeginPass(i);

		Device->SetStreamSource(0, ModuleIrisGraphics::ExchangeVertex, 0, sizeof(Iris2DVertex));
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		
		backBufferEffect->EndPass();
	}
	backBufferEffect->End();

	return true;
}

void IrisShader::SetTransitionProjMatrix(const D3DXMATRIX& proj){
	transitionEffect->SetMatrix(transitionProjMatrixHandle, &proj);
}

bool IrisShader::DoTransitionShade(
	IDirect3DTexture9* pre, IDirect3DTexture9* mask, IDirect3DTexture9* target, const float& cmp){
	
	D3DXMATRIX M;
	D3DXMatrixIdentity(&M);
	transitionEffect->SetTexture(transitionPreTexHandle, pre);
	transitionEffect->SetTexture(transitionMaskTexHandle, mask);
	transitionEffect->SetTexture(transitionTargetTexHandle, target);
	transitionEffect->SetFloat(transitionCmpPixelHandle, cmp);

	UINT numPasses = 0;
	transitionEffect->SetTechnique(transitionTechHandle);

	transitionEffect->Begin(&numPasses, 0);
	for (int i = 0; i < numPasses; i++)
	{
		backBufferEffect->BeginPass(i);

		//Device->SetFVF(d3d::Vertex::FVF);
		transitionEffect->SetMatrix(backBufferWorldMatrixHandle, &M);
		//transitionEffect->SetTexture(backBufferTexHandle, ModuleIrisGraphics::ExchangeTexture);
		Device->SetStreamSource(0, ModuleIrisGraphics::ExchangeVertex, 0, sizeof(Iris2DVertex));
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		transitionEffect->EndPass();
	}
	transitionEffect->End();

	return true;
}

bool IrisShader::ReleaseShaderSource(){
	if (spriteEffect != NULL){
		d3d::Release<ID3DXEffect*>(spriteEffect);
		d3d::Release<ID3DXEffect*>(viewportEffect);
		d3d::Release<ID3DXEffect*>(backBufferEffect);
		spriteEffect = NULL;
		viewportEffect = NULL;
		backBufferEffect = NULL;
	}
	return true;
}

IrisShader* IrisShader::Instance(){
	if (instance == NULL){
		instance = new IrisShader();
	}
	return instance;
}

IrisShader::~IrisShader()
{
	if (spriteEffect != NULL){
		ReleaseShaderSource();
	}
}