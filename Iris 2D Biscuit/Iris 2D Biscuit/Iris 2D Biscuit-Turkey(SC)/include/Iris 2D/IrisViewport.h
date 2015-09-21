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

#include "Iris2DSupports.h"
#include "IrisError.h"
#include "IrisSprite.h"
#include "IrisColor.h"
#include "IrisRect.h"
#include "ModuleIrisGraphics.h"

#include <list>
#include <vector>

namespace Iris2D{
	class IrisSprite;
	class IrisColor;
	class IrisTone;
	class IrisRect;
	class ModuleIrisGraphics;

	using std::list;

	class IrisViewport
	{
	protected:
		list<IrisSprite*> sprites;
		IDirect3DDevice9* Device;
		IDirect3DVertexBuffer9 *renderVertex;
		IDirect3DTexture9 *renderTexture;
		IDirect3DSurface9 *renderSurface;

		bool MakeBuffer();
		bool MakeTexture();

		float z;

		IrisRect *rect;
		IrisTone *tone;
		IrisColor *color;

		bool visible;
		float ox, oy;
		float x, y;
		bool isBatching;

		//IrisSprite* backSprite;

		void addSprite(IrisSprite* sprite);
		void deleteSprite(IrisSprite* sprite);

		void sortSprites() { this->sprites.sort(SpriteSortFunction); }

	protected:
		static bool SpriteSortFunction(IrisSprite* sp1, IrisSprite* sp2);

	public:
		static void BeginBatchSpriteProcess(IrisViewport* vp);
		static void EndBatchSpriteProcess(IrisViewport* vp);

	public:

		void OnDeviceLost();
		void OnDeviceRecover();

		IrisRect* GetRect() { return this->rect; }
		void SetRect(IrisRect* rect, bool isRelease = true){
			if (this->rect != rect){
				if (this->rect != NULL && isRelease)
					delete this->rect;
				this->rect = rect;
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

		IrisColor* GetColor() { return this->color; }
		void SetColor(IrisColor* color, bool isRelease = true) {
			if (this->color != color){
				if (this->color != NULL && isRelease){
					delete this->color;
				}
				this->color = color;
			}
		}

		list<IrisSprite*>& GetSprites() { return this->sprites; }

		CPP_GETTER_SETTER(Visible, visible, bool)
		CPP_GETTER_SETTER(Ox, ox, float)
		CPP_GETTER_SETTER(Oy, oy, float)

		IrisViewport(float x, float y, float width, float height, IR_PARAM_RESULT);
		IrisViewport(const IrisRect *rect, IR_PARAM_RESULT);

		IrisViewport(IR_PARAM_RESULT);
		void SetInitData(float x, float y, float width, float height, IR_PARAM_RESULT);
		void SetInitData(const IrisRect *rect, IR_PARAM_RESULT);

		void RenderSurface();
		void AutoDispose();

		void Dispose(IR_PARAM_RESULT);
		bool Disposed(IR_PARAM_RESULT);
		
		void Flash(IrisColor *color, int duration);
		void Update();

		float GetX() { return this->x; }
		float GetY() { return this->y; }
		int GetWidth() { return (int)this->rect->width; }
		int GetHeight() { return (int)this->rect->height; }

		float GetZ() { return this->z; }
		void SetZ(float tz);

		//void Draw();

		~IrisViewport(void);

		friend class IrisShader;
		friend class IrisSprite;
	};

}
#endif
