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

class IrisFont;
class IrisColor;
class IrisRect;
class IrisViewport;
class IrisTone;

class IrisBitmap
{
private:
	IDirect3DVertexBuffer9 *vb;
	IDirect3DVertexBuffer9* outVb;
	IDirect3DIndexBuffer9 *ib;
	IDirect3DDevice9 *Device;
	IDirect3DTexture9* texture;

	//D3DMATERIAL9      mtrl;

	bool IrisBitmapBitBlt(int x, int y, Bitmap *destBitmap, Bitmap* srcBitmap, Rect *srcRect, int opacity = 255);
	bool IrisBitmapStretchBlt(Rect *destRect, Bitmap* destBitmap, Rect *srcRect, Bitmap* srcBitmap, int opacity = 255);
	Bitmap* ScaleBitmap(Bitmap* srcBitmap, int width, int height);

	void MakeBuffer(int width, int height);
	void MakeTexture(const IrisRect* limitRect);

	void SetOpacity(int opacity);

	IrisViewport *inhoodViewport;

	bool needRefreshTexture;

	static void BitmapRGBtoHSL(const COLOR_RGB *rgb, COLOR_HSL *hsl);
	static void BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb);

	IrisFont *font;
	Bitmap *bitmap;

	IrisRect* limitRect;

public:

	friend class IrisSprite;

	int width, height;

	IrisFont* GetFont();
	void SetFont(IrisFont* font);

	IrisBitmap();
	void SetInitData(wstring fileName);		 // Initialize Interface for Ruby...
	void SetInitData(int width, int height); // Initialize Interface for Ruby...

	IrisBitmap(wstring fileName);
	IrisBitmap(int width, int height);

	void Dispose();
	bool Disposed();

	bool Blt(int x, int y, const IrisBitmap *srcIrisBitmap, const IrisRect *rect, int opactiy);
	bool StretchBlt(const IrisRect *destIrisRect, const IrisBitmap *srcIrisBitmap, const IrisRect *srcIrisRect, int opacity);

	void FillRect(int x, int y, int width, int height, const IrisColor *color);
	void FillRect(const IrisRect *rect, const IrisColor *color);

	void GradientFillRect(int x, int y, int width, int height, const IrisColor *color1, const IrisColor *color2, bool vertical = false);
	void GradientFillRect(const IrisRect *rect, const IrisColor *color1, const IrisColor *color2, bool vertical = false);

	void Clear();

	void ClearRect(int x, int y, int width, int height);
	void ClearRect(const IrisRect* rect);

	IrisColor* GetPixel(int x, int y);

	void SetPixel(int x, int y, const IrisColor *color);

	void hueChange(float hue);

	void blur();

	void RadialBlur(float angle, int division);

	int TextSize(const IrisFont* fontIris, wstring str);

	void IrisDrawText(const IrisFont* fontIris, int x, int y, int width, int height, wstring str, int align);
	void IrisDrawText(const IrisFont* fontIris, const IrisRect *rect, wstring str, int align);

	IDirect3DVertexBuffer9* GetVb();
	IDirect3DTexture9* GetTexture();

	void Draw(IrisViewport *viewport, const IrisRect* limitRect);

	IDirect3DDevice9* GetDevice();

	void PrevFlash(const IrisColor* color);
	void DoFlash(const IrisColor* color, int duration);
	void EndFlash();

	int GetWidth();
	int GetHeight();

	~IrisBitmap(void);

	void SaveToFile(wstring fileName);

	static bool GraphicsChange;
};
#endif
