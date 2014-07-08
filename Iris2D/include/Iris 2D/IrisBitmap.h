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
	void MakeTexture(IrisTone* tone, IrisRect* limitRect, int opacity = 255);

	void SetOpacity(int opacity);

	IrisViewport *inhoodViewport;

	bool needRefreshTexture;

	static void BitmapRGBtoHSL(const COLOR_RGB *rgb, COLOR_HSL *hsl);
	static void BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb);

	IrisFont *font;
	Bitmap *bitmap;

	IrisRect* limitRect;
	IrisTone* tone;
	IrisTone* viewportTone;

public:

	friend class IrisSprite;

	int width, height;

	IrisFont* GetFont();
	void SetFont(IrisFont* font);

	IrisBitmap();
	IrisBitmap(wstring fileName);
	IrisBitmap(int width, int height);

	void Dispose();
	bool Disposed();

	bool Blt(int x, int y, IrisBitmap *srcIrisBitmap, IrisRect *rect, int opactiy);
	bool StretchBlt(IrisRect *destIrisRect, IrisBitmap *srcIrisBitmap, IrisRect *srcIrisRect, int opacity);

	void FillRect(int x, int y, int width, int height, IrisColor *color);
	void FillRect(IrisRect *rect, IrisColor *color);

	void GradientFillRect(int x, int y, int width, int height, IrisColor *color1, IrisColor *color2, bool vertical = false);
	void GradientFillRect(IrisRect *rect, IrisColor *color1, IrisColor *color2, bool vertical = false);

	void Clear();

	void ClearRect(int x, int y, int width, int height);
	void ClearRect(IrisRect* rect);

	IrisColor* GetPixel(int x, int y) ;

	void SetPixel(int x, int y, IrisColor *color);

	void hueChange(float hue);

	void blur();

	void RadialBlur(float angle, int division);

	int TextSize(IrisFont* fontIris, wstring str);

	void IrisDrawText(IrisFont* fontIris, int x, int y, int width, int height, wstring str, int align);
	void IrisDrawText(IrisFont* fontIris, IrisRect *rect, wstring str, int align);

	IDirect3DVertexBuffer9* GetVb();
	IDirect3DTexture9* GetTexture();

	void Draw(int opacity, IrisViewport *viewport, IrisRect* limitRect, IrisTone* tone);

	IDirect3DDevice9* GetDevice();

	void PrevFlash(IrisColor* color);
	void DoFlash(IrisColor* color ,int duration);
	void EndFlash();

	int GetWidth();
	int GetHeight();

	~IrisBitmap(void);

	void SaveToFile(wstring fileName);

	static bool GraphicsChange;

	friend class IrisBitmapToRuby;
};

#ifdef MINGW_WITH_RUBY
DEFINE_CONVER_CLASS_BEGIN(IrisBitmap)
	// 分配函数
    DEFINE_RUBY_CLASS_ALLOC_FUNC(IrisBitmap)

	// 映射方法
	DEFINE_CONVER_METHOD(initialize)(VALUE self, VALUE filename){
		// Get Sprite
		IrisBitmap* tc;
		Data_Get_Struct(self, IrisBitmap, tc);

        // Get String of Filename
		VALUE fn = StringValue(filename);
        char* p = RSTRING(fn)->as.heap.ptr;
		tc->bitmap = new Bitmap((wstring)p, FALSE);
		tc->graphics = new Graphics(tc->bitmap);
		tc->width = tc->bitmap->GetWidth();
		tc->height = tc->bitmap->GetHeight();

		return self;
	}

	DEFINE_CONVER_METHOD(initialize)(VALUE self, VALUE twidth, VALUE theight){
		// Get Sprite
		IrisBitmap* tc;
		Data_Get_Struct(self, IrisBitmap, tc);

		tc->width = NUM2INT(twidth);
		tc->height = NUM2INT(theight);
        // Get String of Filename
		tc->bitmap = new Bitmap(NUM2INT(twidth), NUM2INT(theight), PixelFormat32bppARGB);
		tc->graphics = new Graphics(tc->bitmap);

		return self;
	}

	DEFINE_CONVER_METHOD(dispose)(VALUE self) {
	}

DEFINE_CONVER_CLASS_END
#endif // MINGW_WITH_RUBY
#endif
