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

using std::list;

class IrisViewport : public IIrisViewport
{
private:
	list<IIrisSprite*> sprites;
	IDirect3DDevice9* Device;
	IDirect3DVertexBuffer9 *renderVertex;
	IDirect3DTexture9 *renderTexture;
	IDirect3DSurface9 *renderSurface;

	void MakeBuffer();
	void MakeTexture();
	void ToneDeal();

	float z;

	IIrisRect *rect;
	IIrisTone *tone;
	IIrisColor *color;

	bool visible;
	float ox, oy;

	//IrisSprite* backSprite;

public:

	IIrisRect* GetRect();
	void SetRect(IIrisRect* rect);

	IIrisTone* GetTone();
	void SetTone(IIrisTone* tone);

	IIrisColor* GetColor();
	void SetColor(IIrisColor* color);

	list<IIrisSprite*> GetSprites();

	void RenderSurface();
	void RenderToBackbuffer();

	CPP_GETTER_SETTER(Visible, visible, bool)
	CPP_GETTER_SETTER(Ox, ox, float)
	CPP_GETTER_SETTER(Oy, oy, float)

	IrisViewport(float x, float y, float width, float height);
	IrisViewport(const IIrisRect *rect);

	IrisViewport();
	void SetInitData(float x, float y, float width, float height);
	void SetInitData(const IIrisRect *rect);

	static bool compareSpriteWithZ(IIrisSprite *v1, IIrisSprite *v2);
	void sortSprites();
	void AutoDispose();

	void Dispose();
	bool Disposed();

	void addSprite(IIrisSprite* sprite);
	void deleteSprite(IIrisSprite* sprite);

	void Flash(const IIrisColor *color, int duration);
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
