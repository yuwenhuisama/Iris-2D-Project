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

//#include "Iris2D.h"
#include "Iris 2D Library.h"
#include "IrisBitmap.h"
#include "IrisViewport.h"
#include "IrisColor.h"
#include "IrisTone.h"
#include "IrisSprite.h"

namespace Iris2D{
	class IrisBitmap;
	class IrisViewPort;
	class IrisColor;
	class IrisTone;

	class IrisPlane : public IIrisPlane
	{
	protected:

		IIrisSprite *sprite;

		IIrisBitmap *bitmap;
		IIrisViewport *viewport;
		bool visible;
		float z;
		float ox, oy;
		float zoomX, zoomY;
		int opacity;
		int blendType;
		IIrisColor *color;
		IIrisTone *tone;

	public:

		CPP_GETTER_SETTER(Bitmap, bitmap, IIrisBitmap*)
		CPP_GETTER_SETTER(Viewport, viewport, IIrisViewport*)
		CPP_GETTER_SETTER(Visible, visible, bool)
		CPP_GETTER_SETTER(Z, z, float)
		CPP_GETTER_SETTER(Ox, ox, float)
		CPP_GETTER_SETTER(Oy, oy, float)
		CPP_GETTER_SETTER(ZoomX, zoomX, float)
		CPP_GETTER_SETTER(ZoomY, zoomY, float)
		CPP_GETTER_SETTER(Opacity, opacity, int)
		CPP_GETTER_SETTER(BlendType, blendType, int)
		CPP_GETTER_SETTER(Color, color, IIrisColor*)
		CPP_GETTER_SETTER(Tone, tone, IIrisTone*)

		IrisPlane(void);
		void SetInitData(IIrisViewport* viewport);

		IrisPlane(IIrisViewport* viewport);

		bool Disposed(IR_PARAM_RESULT);
		void Dispose(IR_PARAM_RESULT);

		~IrisPlane(void);
	};
}
#endif
