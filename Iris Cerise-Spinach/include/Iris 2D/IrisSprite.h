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

#include "Iris 2D Library.h"
#include "Iris2DSupports.h"
//#include "IrisError.h"

namespace Iris2D{
	class IrisViewport;
	class IrisTone;
	class IrisBitmap;
	class IrisColor;
	class IrisRect;
	class ModuleIrisGraphics;

	class IrisSprite : public IIrisSprite
	{
	protected:
		IDirect3DDevice9 *Device;
		IIrisViewport *viewport;
		IIrisColor *color;
		IIrisTone *tone;
		IIrisRect* srcRect;
		IIrisBitmap *bitmap;

		bool isFlash;
		IrisColor* flashColor;
		int flashDuration;
		int realFlashDuration;

		int opacity;
		float z;
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
		CPP_GETTER_SETTER(Opacity, opacity, int)

		IrisSprite(IIrisViewport *viewport = NULL, IR_PARAM_RESULT);

		void SetInitData(IIrisViewport *viewport = NULL, IR_PARAM_RESULT);

		void SetViewport(IIrisViewport *tviewport);
		IIrisViewport* GetViewport();

		IIrisColor* GetColor() { return this->color; }
		void SetColor(IIrisColor* color, bool isRelease = true) {
			if (this->color != color){
				if (this->color != NULL && isRelease)
					delete this->color;
				this->color = color;
			}
		}

		IIrisTone* GetTone() { return this->tone; }
		void SetTone(IIrisTone* tone, bool isRelease = true) {
			if (this->tone != tone){
				if (this->tone != NULL && isRelease)
					delete this->tone;
				this->tone = tone;
			}
		}

		IIrisRect* GetSrcRect() { return this->srcRect; }
		void SetSrcRect(IIrisRect* srcRect, bool isRelease = true);

		IIrisBitmap* GetBitmap(){ return this->bitmap; }
		void SetBitmap(IIrisBitmap* bitmap, bool isRelease = true);

		void Dispose(IR_PARAM_RESULT);
		bool Disposed(IR_PARAM_RESULT);

		void AutoDispose();
		void AutoSetViewport(IIrisViewport *tviewport);

		void OnDeviceLost();
		void OnDeviceRecover();

		void Flash(const IIrisColor *color, int duration);

		void Update(IR_PARAM_RESULT);

		int GetWidth();
		int GetHeight();

		void SetZ(float tZ);

		float GetZ() { return this->z; }

		~IrisSprite(void);

		friend class IrisShader;
	};
}

#endif
