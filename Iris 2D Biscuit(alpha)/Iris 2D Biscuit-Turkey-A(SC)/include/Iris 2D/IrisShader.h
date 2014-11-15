#ifndef _IRISSHADER_H_
#define _IRISSHADER_H_

#include "Iris2D.h"
#include <string>
using namespace std;

class IrisShader
{
public:

	bool InitShader(IDirect3DDevice9* td, wstring spriteShaderFileName,
		wstring viewportShaderFileName, wstring backBufferShaderFileName, wstring transitionShaderFileName);

	void SetSpriteProjMatrix(const D3DXMATRIX& projMatrix);
	void SetViewportProjMatrix(const D3DXMATRIX& projMatrix);
	void SetBackbufferProjMatrix(const D3DXMATRIX& projMatrix);
	void SetTransitionProjMatrix(const D3DXMATRIX& proj);
	void SetTransitionType(int type);

	bool DoSpriteShade(list<IrisSprite*>& spriteList);
	bool DoViewportShade(list<IrisViewport*>& viewportList);
	bool DoBackBufferShade();
	bool DoTransitionShade(IDirect3DTexture9* mask, const float& cmp);

	bool ReleaseShaderSource();

	~IrisShader();

	static IrisShader* Instance();

private:

	bool InitShader(string shaderName, int index);

	static IrisShader* instance;

	IrisShader();

	IDirect3DDevice9* Device;

	ID3DXEffect* spriteEffect;
	ID3DXEffect* viewportEffect;
	ID3DXEffect* backBufferEffect;
	ID3DXEffect* transitionEffect;

	D3DXHANDLE spriteWorldMatrixHandle;
	D3DXHANDLE spriteProjMatrixHandle;
	D3DXHANDLE viewportWorldMatrixHandle;
	D3DXHANDLE viewportProjMatrixHandle;
	D3DXHANDLE backBufferWorldMatrixHandle;
	D3DXHANDLE backBufferProjMatrixHandle;
	
	D3DXHANDLE transitionWorldMatrixHandle;
	D3DXHANDLE transitionProjMatrixHandle;
	D3DXHANDLE transitionPreTexHandle;
	D3DXHANDLE transitionMaskTexHandle;
	D3DXHANDLE transitionTargetTexHandle;
	D3DXHANDLE transitionCmpPixelHandle;
	D3DXHANDLE transitionTypeHandle;

	D3DXHANDLE spriteToneVectorHandle;
	D3DXHANDLE spriteOpacityHandle;

	D3DXHANDLE viewportToneVectorHandle;

	D3DXHANDLE spriteTexHandle;
	D3DXHANDLE viewportTexHandle;
	D3DXHANDLE backBufferTexHandle;

	D3DXHANDLE spriteTechHandle;
	D3DXHANDLE viewportTechHandle;
	D3DXHANDLE backBufferTechHandle;
	D3DXHANDLE transitionTechHandle;
};
#endif