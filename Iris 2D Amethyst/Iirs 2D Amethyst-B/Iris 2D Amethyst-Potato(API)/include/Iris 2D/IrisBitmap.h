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

#include "Iris2D.h"

using namespace std;
using namespace Gdiplus;

#define min3v(v1, v2, v3)   ((v1)>(v2)? ((v2)>(v3)?(v3):(v2)):((v1)>(v3)?(v3):(v1)))
#define max3v(v1, v2, v3)   ((v1)<(v2)? ((v2)<(v3)?(v3):(v2)):((v1)<(v3)?(v3):(v1)))
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

class IrisBitmap : public IIrisBitmap
{
private:
	IDirect3DVertexBuffer9 *vb;
	IDirect3DIndexBuffer9 *ib;
	IDirect3DDevice9 *Device;
	IDirect3DTexture9 *texture;
	//D3DMATERIAL9      mtrl;

	bool IrisBitmapBitBlt(int x, int y, Bitmap *destBitmap, Bitmap* srcBitmap, Rect *srcRect, int opacity = 255);
	bool IrisBitmapStretchBlt(Rect *destRect, Bitmap* destBitmap, Rect *srcRect, Bitmap* srcBitmap, int opacity = 255);
	Bitmap* ScaleBitmap(Bitmap* srcBitmap, int width, int height);

	void MakeBuffer(int width, int height);
	void MakeTexture(const IIrisTone* tone, const IIrisRect* limitRect, int opacity = 255);

	void SetOpacity(int opacity);

	IIrisViewport *inhoodViewport;

	bool needRefreshTexture;

	static void BitmapRGBtoHSL(const COLOR_RGB *rgb, COLOR_HSL *hsl);
	static void BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb);

	IIrisFont *font;
	Bitmap *bitmap;

	IIrisRect* limitRect;
	IIrisTone* tone;
	IIrisTone* viewportTone;

public:

	friend class IrisSprite;

	int width, height;

	IIrisFont* GetFont();
	void SetFont(IIrisFont* font);

	IrisBitmap();
	void SetInitData(wstring fileName);		 // Initialize Interface for Ruby...
	void SetInitData(int width, int height); // Initialize Interface for Ruby...

	IrisBitmap(wstring fileName);
	IrisBitmap(int width, int height);

	void SaveToFile(wstring fileName);

	void Dispose();
	bool Disposed();

	bool Blt(int x, int y, const IIrisBitmap *srcIrisBitmap, const IIrisRect *rect, int opactiy);
	bool StretchBlt(const IIrisRect *destIrisRect, const IIrisBitmap *srcIrisBitmap, const IIrisRect *srcIrisRect, int opacity);

	void FillRect(int x, int y, int width, int height, const IIrisColor *color);
	void FillRect(const IIrisRect *rect, const IIrisColor *color);

	void GradientFillRect(int x, int y, int width, int height, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false);
	void GradientFillRect(const IIrisRect *rect, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false);

	void Clear();

	void ClearRect(int x, int y, int width, int height);
	void ClearRect(IIrisRect* rect);

	IIrisColor* GetPixel(int x, int y) ;

	void SetPixel(int x, int y, const IIrisColor *color);

	void hueChange(float hue);

	void blur();

	void RadialBlur(float angle, int division);

	int TextSize(const IIrisFont* fontIris, wstring str);

	void IrisDrawText(const IIrisFont* fontIris, int x, int y, int width, int height, wstring str, int align);
	void IrisDrawText(const IIrisFont* fontIris, const IIrisRect *rect, wstring str, int align);

	IDirect3DVertexBuffer9* GetVb();
	IDirect3DTexture9* GetTexture();

	void Draw(int opacity, IIrisViewport *viewport, IIrisRect* limitRect, IIrisTone* tone);

	IDirect3DDevice9* GetDevice();

	void PrevFlash(const IIrisColor* color);
	void DoFlash(const IIrisColor* color ,int duration);
	void EndFlash();

	int GetWidth();
	int GetHeight();

	~IrisBitmap(void);

	static bool GraphicsChange;

	friend class IrisBitmapToRuby;
};
#endif
