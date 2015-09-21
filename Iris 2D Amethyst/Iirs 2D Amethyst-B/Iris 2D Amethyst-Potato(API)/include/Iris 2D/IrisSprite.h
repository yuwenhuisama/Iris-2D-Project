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

class IrisSprite : public IIrisSprite
{
private:
	IDirect3DDevice9 *Device;
	IIrisViewport *viewport;
	int opacity;
	float z;

	IIrisColor *color;
	IIrisTone *tone;
	IIrisRect* srcRect;
	IIrisBitmap *bitmap;

	bool isFlash;
	IIrisColor* flashColor;
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

	//IrisSprite();
	//IrisSprite(IDirect3DDevice9 *Device);
	IrisSprite(IIrisViewport *viewport = NULL);

	void SetInitData(IIrisViewport *viewport = NULL);

	void SetViewport(IIrisViewport *tviewport);
	IIrisViewport* GetViewport();

	IIrisColor* GetColor();
	void SetColor(IIrisColor* color);

	IIrisTone* GetTone();
	void SetTone(IIrisTone* tone);

	IIrisRect* GetSrcRect();
	void SetSrcRect(IIrisRect* srcRect);

	IIrisBitmap* GetBitmap();
	void SetBitmap(IIrisBitmap* bitmap);

    void Dispose();
	bool Disposed();

	void AutoDispose();
	void AutoSetViewport(IIrisViewport *tviewport);

	void Flash(const IIrisColor *color, int duration);

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
};

#endif
