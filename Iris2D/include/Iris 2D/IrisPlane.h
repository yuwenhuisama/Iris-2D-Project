/************************************************************************
*
* Header File Name: IrisPlane
* Class Name : IrisPlane
* Function : This class can symbol plane to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/


#ifndef _IRISPLANE_H_
#define _IRISPLANE_H_

#include "Iris2D.h"
class IrisView;

class IrisPlane
{
private:
	IrisBitmap *bitmap;

	IrisViewport *viewport;

	bool visible;

	float z;

	float ox, oy;

	float zoomX, zoomY;

	int opacity;

	int blendType;

	IrisColor *color;

	IrisTone *tone;
public:

	CPP_GETTER_SETTER(Bitmap, bitmap, IrisBitmap*)
	CPP_GETTER_SETTER(Viewport, viewport, IrisViewport*)
	CPP_GETTER_SETTER(Visible, visible, bool)
	CPP_GETTER_SETTER(Z, z, float)
	CPP_GETTER_SETTER(Ox, ox, float)
	CPP_GETTER_SETTER(Oy, oy, float)
	CPP_GETTER_SETTER(ZoomX, zoomX, float)
	CPP_GETTER_SETTER(ZoomY, zoomY, float)
	CPP_GETTER_SETTER(Opacity, opacity, int)
	CPP_GETTER_SETTER(BlendType, blendType, int)
	CPP_GETTER_SETTER(Color, color, IrisColor*)
	CPP_GETTER_SETTER(Tone, tone, IrisTone*)

	IrisPlane(void);
	IrisPlane(IrisViewport viewport);

	bool Disposed();
	void Dispose();

	~IrisPlane(void);
};
#endif
