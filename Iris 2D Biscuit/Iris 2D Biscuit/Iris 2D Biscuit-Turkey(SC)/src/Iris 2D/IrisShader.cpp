#include "IrisShader.h"

namespace Iris2D{
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
		transitionTypeHandle = 0;
		transitionVagueHandle = 0;

		spriteToneVectorHandle = 0;
		spriteOpacityHandle = 0;
		spriteFlashVisibleHandle = 0;
		spriteFlashDurationHandle = 0;
		spriteFlashColorHandle = 0;
		spriteCurDurationHandle = 0;
		spriteBlendTypeHandle = 0;
		spriteBackgroundHandle = 0;

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

		HRESULT hr;
		if (IrisEncripedResourceManager::Instance()->HaveGeneralSource(StringToWString(shaderName))){
			char* pData = NULL;
			int nSize = 0;
			IrisEncripedResourceManager::Instance()->GetGeneralData(StringToWString(shaderName), &pData, &nSize);
			hr = D3DXCreateEffect(
				Device,
				pData,
				nSize,
				0,
				0,
				D3DXSHADER_DEBUG,
				0,
				effect,
				&errorBuffer);

		}
		else{
			hr = D3DXCreateEffectFromFileA(
				Device,
				shaderName.c_str(),
				0,                // no preprocessor definitions
				0,                // no ID3DXInclude interface
				D3DXSHADER_DEBUG, // compile flags
				0,                // don't share parameters
				effect,
				&errorBuffer);
		}

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
			//IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Initializing Sprite Shader !")
			return false;
		result = InitShader(WStringToString(viewportShaderFileName), 1);
		if (!result)
			//IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Initializing Viewport Shader !")
			return false;
		result = InitShader(WStringToString(backBufferShaderFileName), 2);
		if (!result)
			//IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Initializing Backbuffer Shader !")
			return false;
		result = InitShader(WStringToString(transitionShaderFileName), 3);
		if (!result)
			//IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Initializing Transition Shader !")
			return false;

		spriteWorldMatrixHandle = spriteEffect->GetParameterByName(0, "WorldMatrix");
		spriteProjMatrixHandle = spriteEffect->GetParameterByName(0, "ProjMatrix");
		spriteTexHandle = spriteEffect->GetParameterByName(0, "Tex");
		spriteToneVectorHandle = spriteEffect->GetParameterByName(0, "ToneVector");
		spriteOpacityHandle = spriteEffect->GetParameterByName(0, "Opacity");
		spriteSpriteXYHandle = spriteEffect->GetParameterByName(0, "SpriteXY");
		spriteBlendTypeHandle = spriteEffect->GetParameterByName(0, "BlendType");
		spriteBackgroundHandle = spriteEffect->GetParameterByName(0, "BackgroundTex");

		spriteFlashVisibleHandle = spriteEffect->GetParameterByName(0, "FlashVisible");
		spriteFlashDurationHandle = spriteEffect->GetParameterByName(0, "Duration");
		spriteFlashColorHandle = spriteEffect->GetParameterByName(0, "FlashColor");
		spriteCurDurationHandle = spriteEffect->GetParameterByName(0, "CurDuration");
		spriteMultiTextureSize = spriteEffect->GetParameterByName(0, "MultiTextureSize");
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
		transitionTypeHandle = transitionEffect->GetParameterByName(0, "Type");
		transitionVagueHandle = transitionEffect->GetParameterByName(0, "Vague");

		transitionTechHandle = transitionEffect->GetTechniqueByName("LightAndTexture");

		spriteEffect->SetTechnique(spriteTechHandle);
		viewportEffect->SetTechnique(viewportTechHandle);
		backBufferEffect->SetTechnique(backBufferTechHandle);
		transitionEffect->SetTechnique(transitionTechHandle);

		//IR_PARAM_SET_RESULT(IR_RSUCCESS, L"");
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

			sp->bitmap->Draw(sp->srcRect);
			//-------------Material && Texture Setting-------------
			IDirect3DTexture9* text = sp->bitmap->GetTexture();
			spriteEffect->SetTexture(spriteTexHandle, text);

			//-------------Tone && Opacity-------------
			D3DXVECTOR4 tone((float)sp->tone->GetRed(), (float)sp->tone->GetBlue(), (float)sp->tone->GetGreen(), (float)sp->tone->GetAlpha());
			spriteEffect->SetVector(spriteToneVectorHandle, &tone);
			spriteEffect->SetInt(spriteOpacityHandle, sp->opacity);

			//------------BlendType-------------
			//pSurface->Text
			spriteEffect->SetTexture(spriteBackgroundHandle, sp->viewport->renderTexture);
			//D3DXSaveTextureToFile(L"a.bmp", D3DXIFF_BMP, sp->viewport->renderTexture, 0);
			spriteEffect->SetInt(spriteBlendTypeHandle, sp->blendType); 
			D3DXVECTOR4 sizeVector = { (float)sp->bitmap->GetWidth(), (float)sp->bitmap->GetHeight(), (float)sp->viewport->GetWidth(), (float)sp->viewport->GetHeight() };
			spriteEffect->SetVector(spriteMultiTextureSize, &sizeVector);

			//------------ Flash -----------
			if (sp->isFlash){
				if (sp->flashColor){
					D3DXVECTOR4 fcolor(sp->flashColor->GetRed() / 255.0f,
						sp->flashColor->GetGreen() / 255.0f,
						sp->flashColor->GetBlue() / 255.0f,
						sp->flashColor->GetAlpha() / 255.0f);
					spriteEffect->SetVector(spriteFlashColorHandle, &fcolor);
					spriteEffect->SetInt(spriteFlashDurationHandle, sp->realFlashDuration);
					spriteEffect->SetInt(spriteCurDurationHandle, sp->flashDuration);
					spriteEffect->SetInt(spriteFlashVisibleHandle, 1);
				}
				else{
					spriteEffect->SetInt(spriteFlashVisibleHandle, 0);
				}
			}
			else{
				spriteEffect->SetInt(spriteFlashVisibleHandle, 0);
			}

			//-------------Matrix Math-------------

			D3DXMATRIX translationMatrix;
			//D3DXMATRIX translationMatrix2;

			D3DXMATRIX rotationMatrix;
			D3DXMATRIX scalingMatrix;
			D3DXMATRIX resultMatrix;

			D3DXMatrixIdentity(&translationMatrix);
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixIdentity(&scalingMatrix);
			//D3DXMatrixIdentity(&translationMatrix2);

			if (sp->angle != 0.0f)
				D3DXMatrixRotationZ(&rotationMatrix, sp->angle);

			D3DXMatrixTranslation(&translationMatrix, -sp->ox, -sp->oy, 0.0f);
			//D3DXMatrixTranslation(&translationMatrix2, sp->x, sp->y, sp->z);

			if (sp->zoomX != 1.0f || sp->zoomY != 1.0f)
				D3DXMatrixScaling(&scalingMatrix, sp->zoomX, sp->zoomY, 1.0f);

			resultMatrix = scalingMatrix * translationMatrix * rotationMatrix;

			D3DXVECTOR4 vcSprite = { sp->x, sp->y, 0.0f, 0.0f };

			spriteEffect->SetMatrix(spriteWorldMatrixHandle, &resultMatrix);
			spriteEffect->SetVector(spriteSpriteXYHandle, &vcSprite);

			spriteEffect->Begin(&numPasses, 0);

			for (UINT i = 0; i < numPasses; i++)
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
			D3DXVECTOR4 tone((float)vp->tone->GetRed(),// / 255.0f,
				(float)vp->tone->GetBlue(),// / 255.0f,
				(float)vp->tone->GetGreen(),// / 255.0f,
				(float)vp->tone->GetAlpha());// / 255.0f);
			viewportEffect->SetVector(viewportToneVectorHandle, &tone);

			viewportEffect->Begin(&numPasses, 0);
			for (UINT i = 0; i < numPasses; i++)
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
		
		if (ModuleIrisGraphics::isTransition)
			backBufferEffect->SetTexture(backBufferTexHandle, ModuleIrisGraphics::TransitionTexture);
		else
			backBufferEffect->SetTexture(backBufferTexHandle, ModuleIrisGraphics::ExchangeTexture);

		D3DMATERIAL9 mtrl;// = d3d::WHITE_MTRL;

		int x = ModuleIrisGraphics::GetBrightness();

		mtrl.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		mtrl.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		mtrl.Specular = D3DXCOLOR(D3DCOLOR_XRGB(x, x, x));
		mtrl.Emissive = d3d::BLACK;
		mtrl.Power = 5.0f;
		Device->SetMaterial(&mtrl);

		D3DXMATRIX M;
		D3DXMatrixIdentity(&M);
		backBufferEffect->SetMatrix(backBufferWorldMatrixHandle, &M);

		backBufferEffect->Begin(&numPasses, 0);
		for (UINT i = 0; i < numPasses; i++)
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

	void IrisShader::SetTransitionType(int type){
		transitionEffect->SetInt(transitionTypeHandle, type);
	}

	bool IrisShader::DoTransitionShade(IDirect3DTexture9* mask, const float& cmp, const float& vague){

		transitionEffect->SetTechnique(transitionTechHandle);

		D3DXMATRIX M;
		D3DXMatrixIdentity(&M);
		transitionEffect->SetMatrix(transitionWorldMatrixHandle, &M);
		transitionEffect->SetTexture(transitionPreTexHandle, ModuleIrisGraphics::FreezedTexture);
		transitionEffect->SetTexture(transitionMaskTexHandle, mask);
		transitionEffect->SetTexture(transitionTargetTexHandle, ModuleIrisGraphics::ExchangeTexture);
		transitionEffect->SetFloat(transitionCmpPixelHandle, cmp);
		transitionEffect->SetFloat(transitionVagueHandle, vague);

		UINT numPasses = 0;

		transitionEffect->Begin(&numPasses, 0);
		for (UINT i = 0; i < numPasses; i++)
		{
			transitionEffect->BeginPass(i);

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
			d3d::Release<ID3DXEffect*>(transitionEffect);
			transitionEffect = NULL;
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
}