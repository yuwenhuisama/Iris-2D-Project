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

#include "Iris 2D Library.h"
#include "Iris2DSupports.h"
//#include "IrisError.h"

#include <list>
#include <vector>

namespace Iris2D{
	class IrisSprite;
	class IrisColor;
	class IrisTone;
	class IrisRect;
	class ModuleIrisGraphics;

	using std::list;

	class IrisViewport : public IIrisViewport
	{
	protected:
		list<IIrisSprite*> sprites;
		IDirect3DDevice9* Device;
		IDirect3DVertexBuffer9 *renderVertex;
		IDirect3DTexture9 *renderTexture;
		IDirect3DSurface9 *renderSurface;

		bool MakeBuffer();
		bool MakeTexture();

		float z;

		IIrisRect *rect;
		IIrisTone *tone;
		IIrisColor *color;

		bool visible;
		float ox, oy;
		float x, y;
		bool isBatching;

		//IrisSprite* backSprite;

		void addSprite(IIrisSprite* sprite);
		void deleteSprite(IIrisSprite* sprite);

		void sortSprites() { this->sprites.sort(SpriteSortFunction); }

	protected:
		static bool SpriteSortFunction(IIrisSprite* sp1, IIrisSprite* sp2);

	public:
		static void BeginBatchSpriteProcess(IIrisViewport* vp);
		static void EndBatchSpriteProcess(IIrisViewport* vp);

	public:

		void OnDeviceLost();
		void OnDeviceRecover();

		IIrisRect* GetSrcRect() { return this->rect; }
		void SetSrcRect(IIrisRect* rect, bool isRelease = true){
			if (this->rect != rect){
				if (this->rect != NULL && isRelease)
					delete this->rect;
				this->rect = rect;
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

		IIrisColor* GetColor() { return this->color; }
		void SetColor(IIrisColor* color, bool isRelease = true) {
			if (this->color != color){
				if (this->color != NULL && isRelease){
					delete this->color;
				}
				this->color = color;
			}
		}

		list<IIrisSprite*>& GetSprites() { return this->sprites; }

		CPP_GETTER_SETTER(Visible, visible, bool)
		CPP_GETTER_SETTER(Ox, ox, float)
		CPP_GETTER_SETTER(Oy, oy, float)

		IrisViewport(float x, float y, float width, float height, IR_PARAM_RESULT);
		IrisViewport(const IIrisRect *rect, IR_PARAM_RESULT);

		IrisViewport(IR_PARAM_RESULT);
		void SetInitData(float x, float y, float width, float height, IR_PARAM_RESULT);
		void SetInitData(const IIrisRect *rect, IR_PARAM_RESULT);

		void RenderSurface();
		void AutoDispose();

		void Dispose(IR_PARAM_RESULT);
		bool Disposed(IR_PARAM_RESULT);
		
		void Flash(const IIrisColor *color, int duration);
		void Update();

		float GetX() { return this->x; }
		float GetY() { return this->y; }
		int GetWidth();
		int GetHeight();

		float GetZ() { return this->z; }
		void SetZ(float tz);

		//void Draw();

		~IrisViewport(void);

		friend class IrisShader;
		friend class IrisSprite;
	};

}
#endif
