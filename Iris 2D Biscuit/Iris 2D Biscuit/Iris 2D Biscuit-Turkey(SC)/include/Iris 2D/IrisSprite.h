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

#include "Iris2DSupports.h"
#include "IrisError.h"
#include "IrisViewport.h"
#include "IrisTone.h"
#include "IrisBitmap.h"
#include "IrisColor.h"
#include "IrisRect.h"
#include "ModuleIrisGraphics.h"

namespace Iris2D{
	class IrisViewport;
	class IrisTone;
	class IrisBitmap;
	class IrisColor;
	class IrisRect;
	class ModuleIrisGraphics;

	class IrisSprite
	{
	protected:
		IDirect3DDevice9 *Device;
		IrisViewport *viewport;
		IrisColor *color;
		IrisTone *tone;
		IrisRect* srcRect;
		IrisBitmap *bitmap;

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

		IrisSprite(IrisViewport *viewport = NULL, IR_PARAM_RESULT);

		void SetInitData(IrisViewport *viewport = NULL, IR_PARAM_RESULT);

		void SetViewport(IrisViewport *tviewport);
		IrisViewport* GetViewport();

		IrisColor* GetColor() { return this->color; }
		void SetColor(IrisColor* color, bool isRelease = true) {
			if (this->color != color){
				if (this->color != NULL && isRelease)
					delete this->color;
				this->color = color;
			}
		}

		IrisTone* GetTone() { return this->tone; }
		void SetTone(IrisTone* tone, bool isRelease = true) {
			if (this->tone != tone){
				if (this->tone != NULL && isRelease)
					delete this->tone;
				this->tone = tone;
			}
		}

		IrisRect* GetSrcRect() { return this->srcRect; }
		void SetSrcRect(IrisRect* srcRect, bool isRelease = true);

		IrisBitmap* GetBitmap(){ return this->bitmap; }
		void SetBitmap(IrisBitmap* bitmap, bool isRelease = true);

		void Dispose(IR_PARAM_RESULT);
		bool Disposed(IR_PARAM_RESULT);

		void AutoDispose();
		void AutoSetViewport(IrisViewport *tviewport);

		void Flash(const IrisColor *color, int duration);

		void Update(IR_PARAM_RESULT);

		int GetWidth() { return (int)this->srcRect->width; }
		int GetHeight() { return (int)this->srcRect->height; }

		void SetZ(float tZ);

		float GetZ() { return this->z; }

		~IrisSprite(void);

		friend class IrisShader;
	};
}

#endif
