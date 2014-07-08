/************************************************************************
*
* Header File Name: IrisViewport
* Class Name : IrisViewport
* Function : This class can limit the showing of all sprites set in which.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISVIEWPORT_H_
#define _IRISVIEWPORT_H_

#include "Iris2D.h"
#include <list>
#include <vector>

class IrisSprite;
class IrisColor;
class IrisTone;
class IrisRect;

using std::list;

class IrisViewport
{
private:
	list<IrisSprite*> sprites;
	IDirect3DDevice9* Device;
	IDirect3DVertexBuffer9 *renderVertex;
	IDirect3DTexture9 *renderTexture;
	IDirect3DSurface9 *renderSurface;

	void MakeBuffer();
	void MakeTexture();
	void ToneDeal();

	float z;

	IrisRect *rect;
	IrisTone *tone;
	IrisColor *color;

	bool visible;
	float ox, oy;

	//IrisSprite* backSprite;

public:

	IrisRect* GetRect();
	void SetRect(IrisRect* rect);

	IrisTone* GetTone();
	void SetTone(IrisTone* tone);

	IrisColor* GetColor();
	void SetColor(IrisColor* color);

	list<IrisSprite*> GetSprites();

	void RenderSurface();
	void RenderToBackbuffer();

	CPP_GETTER_SETTER(Visible, visible, bool)
	CPP_GETTER_SETTER(Ox, ox, float)
	CPP_GETTER_SETTER(Oy, oy, float)

	IrisViewport(float x, float y, float width, float height);
	IrisViewport(IrisRect *rect);

	static bool compareSpriteWithZ(IrisSprite *v1, IrisSprite *v2);
	void sortSprites();
	void AutoDispose();

	void Dispose();
	bool Disposed();

	void addSprite(IrisSprite* sprite);
	void deleteSprite(IrisSprite* sprite);

	void Flash(IrisColor *color, int duration);
	void Update();

	float GetX();
	float GetY();
	UINT GetWidth();
	UINT GetHeight();

	float GetZ();
	void SetZ(float tz);

	//void Draw();

	~IrisViewport(void);

};
#endif
