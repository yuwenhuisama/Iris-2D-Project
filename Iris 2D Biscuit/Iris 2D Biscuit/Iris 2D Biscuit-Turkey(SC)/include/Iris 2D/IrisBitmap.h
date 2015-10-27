/************************************************************************
*
* Header File Name: IrisBitmap
* Class Name : IrisBitmap
* Function : This class can oparate bitmap data to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISBITMAP_H_
#define _IRISBITMAP_H_

#include <list>
#include <string>
using namespace std;
#include "Iris2DSupports.h"
#include "IrisError.h"
#include "IrisFont.h"
#include "IrisColor.h"
#include "IrisRect.h"
#include "IrisViewport.h"
#include "IrisTone.h"
#include "IrisEncripedResourceManager.h"

#define min3v(v1, v2, v3)   ((v1)>(v2)? ((v2)>(v3)?(v3):(v2)):((v1)>(v3)?(v3):(v1)))
#define max3v(v1, v2, v3)   ((v1)<(v2)? ((v2)<(v3)?(v3):(v2)):((v1)<(v3)?(v3):(v1)))

namespace Iris2D{

	using namespace std;
	using namespace Gdiplus;

	typedef struct
	{
		BYTE  red;              // [0,255]
		BYTE  green;            // [0,255]
		BYTE  blue;             // [0,255]

	}COLOR_RGB;

	typedef struct
	{
		float hue;              // [0,360]
		float saturation;       // [0,100]
		float luminance;        // [0,100]
	}COLOR_HSL;

	using namespace Gdiplus;

	class IrisFont;
	class IrisColor;
	class IrisRect;
	class IrisViewport;
	class IrisTone;

	class IrisBitmap
	{
	protected:
		IDirect3DVertexBuffer9 *vb;
		IDirect3DIndexBuffer9 *ib;
		IDirect3DDevice9 *Device;
		IDirect3DTexture9* texture;

		Bitmap *bitmap;
		IrisFont *font;
		IrisRect* limitRect;
		int width, height;
		bool needRefreshTexture;
		bool recoverFlag;

		//D3DMATERIAL9      mtrl;

		bool IrisBitmapBitBlt(int x, int y, Bitmap *destBitmap, Bitmap* srcBitmap, Rect *srcRect, int opacity = 255);
		bool IrisBitmapStretchBlt(Rect *destRect, Bitmap* destBitmap, Rect *srcRect, Bitmap* srcBitmap, int opacity = 255);
		Bitmap* ScaleBitmap(Bitmap* srcBitmap, int width, int height);

		bool MakeBuffer(int width, int height);
		bool MakeTexture(const IrisRect* limitRect);

		static void BitmapRGBtoHSL(const COLOR_RGB *rgb, COLOR_HSL *hsl);
		static void BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb);

		static list<IrisBitmap*> bitmapList;

	public:
		static void OnRelease();
		static void OnRecover();
		static void ReleaseBitmaps();

	public:

		IrisBitmap(IR_PARAM_RESULT);
		void SetInitData(wstring fileName, IR_PARAM_RESULT);		 // Initialize Interface for Ruby...
		void SetInitData(int width, int height, IR_PARAM_RESULT); // Initialize Interface for Ruby...

		IrisBitmap(wstring fileName, IR_PARAM_RESULT);
		IrisBitmap(int width, int height, IR_PARAM_RESULT);
		IrisBitmap(const char* bmpData, int width, int height, IR_PARAM_RESULT);

		void Dispose(IR_PARAM_RESULT);
		bool Disposed(IR_PARAM_RESULT);

		bool Blt(int x, int y, const IrisBitmap *srcIrisBitmap, const IrisRect *rect, int opactiy = 255, IR_PARAM_RESULT);
		bool StretchBlt(const IrisRect *destIrisRect, const IrisBitmap *srcIrisBitmap, const IrisRect *srcIrisRect, int opacity, IR_PARAM_RESULT);

		void FillRect(int x, int y, int width, int height, const IrisColor *color, IR_PARAM_RESULT);
		void FillRect(const IrisRect *rect, const IrisColor *color, IR_PARAM_RESULT);

		void GradientFillRect(int x, int y, int width, int height, const IrisColor *color1, const IrisColor *color2, bool vertical = false, IR_PARAM_RESULT);
		void GradientFillRect(const IrisRect *rect, const IrisColor *color1, const IrisColor *color2, bool vertical = false, IR_PARAM_RESULT);

		void Clear(IR_PARAM_RESULT);

		void ClearRect(int x, int y, int width, int height, IR_PARAM_RESULT);
		void ClearRect(const IrisRect* rect, IR_PARAM_RESULT);

		IrisColor* GetPixel(int x, int y, IR_PARAM_RESULT);
		void SetPixel(int x, int y, const IrisColor *color, IR_PARAM_RESULT);

		void HueChange(float hue, IR_PARAM_RESULT);
		void Blur(IR_PARAM_RESULT);
		void RadialBlur(float angle, int division, IR_PARAM_RESULT);

		int TextSize(const IrisFont* fontIris, wstring str, IR_PARAM_RESULT);

		void IrisDrawText(int x, int y, int width, int height, wstring str, int align, IR_PARAM_RESULT);
		void IrisDrawText(const IrisRect *rect, wstring str, int align, IR_PARAM_RESULT);

		void Draw(const IrisRect* limitRect, IR_PARAM_RESULT);
		void SaveToFile(wstring fileName, IR_PARAM_RESULT);

		IDirect3DVertexBuffer9* GetVb() { return this->vb; }
		IDirect3DTexture9* GetTexture() { return this->texture; }
		IrisFont* GetFont() { return this->font; }
		void SetFont(IrisFont* font) {
			if (this->font != font) {
				delete this->font;
				this->font = font;
			}
		}
		IDirect3DDevice9* GetDevice() {	return this->Device; }
		int GetWidth() { return this->bitmap ? this->bitmap->GetWidth() : 0; }
		int GetHeight() { return this->bitmap ? this->bitmap->GetHeight() : 0; };

		~IrisBitmap(void);

		friend class IrisSprite;
		friend class ModuleIrisGraphics;
	};
}
#endif
