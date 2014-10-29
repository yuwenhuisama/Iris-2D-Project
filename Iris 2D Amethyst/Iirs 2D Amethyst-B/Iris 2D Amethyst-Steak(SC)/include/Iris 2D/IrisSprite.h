/************************************************************************
*
* Header File Name: IrisSprite
* Class Name : IrisSprite
* Function : This class can show graphics onto the screen in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISSPRITE_H_
#define _IRISSPRITE_H_

#include "Iris2D.h"
//#include "CppDsToRubyMacro.h"


class IrisViewport;
class IrisTone;
class IrisBitmap;
class IrisColor;
class IrisRect;

class IrisSprite
{
private:
	IDirect3DDevice9 *Device;
	IrisViewport *viewport;
	int opacity;
	float z;

	IrisColor *color;
	IrisTone *tone;
	IrisRect* srcRect;
	IrisBitmap *bitmap;

	bool isFlash;
	IrisColor* flashColor;
	int flashDuration;
	int realFlashDuration;

	bool visible;

	float x, y;

	float ox, oy;

	float zoomX, zoomY;

	float angle;

	float waveAmp;
	float waveLength;
	float waveSpeed;
	float wavePhase;

	bool mirror;

	int bushDepth;
	int bushOpacity;

	int blendType;

public:

	CPP_GETTER_SETTER(Visible, visible, bool)
	CPP_GETTER_SETTER(X, x, float)
	CPP_GETTER_SETTER(Y, y, float)
	CPP_GETTER_SETTER(Ox, ox, float)
	CPP_GETTER_SETTER(Oy, oy, float)
	CPP_GETTER_SETTER(ZoomX, zoomX, float)
	CPP_GETTER_SETTER(ZoomY, zoomY, float)
	CPP_GETTER_SETTER(Angle, angle, float)
	CPP_GETTER_SETTER(WaveAmp, waveAmp, float)
	CPP_GETTER_SETTER(WaveLength, waveLength, float)
	CPP_GETTER_SETTER(WaveSpeed, waveSpeed, float)
	CPP_GETTER_SETTER(WavePhase, wavePhase, float)
	CPP_GETTER_SETTER(BushDepth, bushDepth, int)
	CPP_GETTER_SETTER(Mirror, mirror, bool)
	CPP_GETTER_SETTER(BushOpacity, bushOpacity, int)
	CPP_GETTER_SETTER(BlendType, blendType, int)

	IrisSprite(IrisViewport *viewport = NULL);

	void SetInitData(IrisViewport *viewport = NULL);

	void SetViewport(IrisViewport *tviewport);
	IrisViewport* GetViewport();

	IrisColor* GetColor();
	void SetColor(IrisColor* color);

	IrisTone* GetTone();
	void SetTone(IrisTone* tone);

	IrisRect* GetSrcRect();
	void SetSrcRect(IrisRect* srcRect);

	IrisBitmap* GetBitmap();
	void SetBitmap(IrisBitmap* bitmap);

    void Dispose();
	bool Disposed();

	void AutoDispose();
	void AutoSetViewport(IrisViewport *tviewport);

	void Flash(const IrisColor *color, int duration);

	void Update();

	void Draw();

	int GetWidth();

	int GetHeight();

	void SetOpacity(int tOpacity);
	int GetOpacity();

	void SetZ(float tZ);
	float GetZ();

	void SetDevice(IDirect3DDevice9 *Device);

	~IrisSprite(void);

	//DECLAR_FRIEND_CLASS(IrisSprite)
	friend class IrisSpriteToRuby;
};

#endif
