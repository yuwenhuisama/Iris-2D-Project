#include "IrisBitmap.h"
#include "ModuleIrisGraphics.h"

typedef union
{
    ARGB Color;
    struct
    {
        BYTE Blue;
        BYTE Green;
        BYTE Red;
        BYTE Alpha;
    };
}ARGBQuad, *PARGBQuad;

// Converts RGB to HSL

void IrisBitmap::BitmapRGBtoHSL(const COLOR_RGB *rgb, COLOR_HSL *hsl)
{
    float h=0, s=0, l=0;
    // normalizes red-green-blue values
    float r = rgb->red/255.f;
    float g = rgb->green/255.f;
    float b = rgb->blue/255.f;
    float maxVal = max3v(r, g, b);
    float minVal = min3v(r, g, b);

    // hue

    if(maxVal == minVal)
    {
        h = 0; // undefined
    }

    else if(maxVal==r && g>=b)
    {
        h = 60.0f*(g-b)/(maxVal-minVal);
    }

    else if(maxVal==r && g<b)
    {
        h = 60.0f*(g-b)/(maxVal-minVal) + 360.0f;
    }

    else if(maxVal==g)
    {
        h = 60.0f*(b-r)/(maxVal-minVal) + 120.0f;
    }
    else if(maxVal==b)
    {
        h = 60.0f*(r-g)/(maxVal-minVal) + 240.0f;
    }

    // luminance
    l = (maxVal+minVal)/2.0f;
    // saturation

    if(l == 0 || maxVal == minVal)
    {
        s = 0;
    }

    else if(0<l && l<=0.5f)
    {
        s = (maxVal-minVal)/(maxVal+minVal);
    }
    else if(l>0.5f)
    {
        s = (maxVal-minVal)/(2 - (maxVal+minVal)); //(maxVal-minVal > 0)?
    }
    hsl->hue = (h>360)? 360 : ((h<0)?0:h);
    hsl->saturation = ((s>1)? 1 : ((s<0)?0:s))*100;
    hsl->luminance = ((l>1)? 1 : ((l<0)?0:l))*100;
}

// Converts HSL to RGB
void IrisBitmap::BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb)
{
    float h = hsl->hue;                  // h must be [0, 360]
    float s = hsl->saturation/100.f; // s must be [0, 1]
    float l = hsl->luminance/100.f;      // l must be [0, 1]
    float R, G, B;

    if(hsl->saturation == 0)
    {
        // achromatic color (gray scale)
        R = G = B = l*255.f;
	}
	else
    {
        float q = (l<0.5f)?(l * (1.0f+s)):(l+s - (l*s));
        float p = (2.0f * l) - q;
        float Hk = h/360.0f;
        float T[3];
        T[0] = Hk + 0.3333333f; // Tr   0.3333333f=1.0/3.0
        T[1] = Hk;              // Tb
        T[2] = Hk - 0.3333333f; // Tg

        for(int i=0; i<3; i++)
        {
            if(T[i] < 0) T[i] += 1.0f;
            if(T[i] > 1) T[i] -= 1.0f;

            if((T[i]*6) < 1)
            {
                T[i] = p + ((q-p)*6.0f*T[i]);
            }
            else if((T[i]*2.0f) < 1) //(1.0/6.0)<=T[i] && T[i]<0.5
            {
                T[i] = q;
            }
            else if((T[i]*3.0f) < 2) // 0.5<=T[i] && T[i]<(2.0/3.0)
            {
                T[i] = p + (q-p) * ((2.0f/3.0f) - T[i]) * 6.0f;
            }
            else T[i] = p;
        }
        R = T[0]*255.0f;
        G = T[1]*255.0f;
        B = T[2]*255.0f;

    }
    rgb->red = (BYTE)((R>255)? 255 : ((R<0)?0 : R));
    rgb->green = (BYTE)((G>255)? 255 : ((G<0)?0 : G));
    rgb->blue = (BYTE)((B>255)? 255 : ((B<0)?0 : B));
}

void IrisBitmap::MakeBuffer(int width, int height){
	HRESULT r = this->Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(this->vb), 0);

	Iris2DVertex* v;
	this->vb->Lock(0, 0, (void**)&v, 0);
	v[0] = Iris2DVertex(0.0f,			   (float)height,		   0.0f, 0.0f, 1.0f);
	v[1] = Iris2DVertex(0.0f,			       0.0f,			   0.0f, 0.0f, 0.0f);
	v[2] = Iris2DVertex((float)width,		   0.0f,			   0.0f, 1.0f, 0.0f);

	v[3] = Iris2DVertex(0.0f - 1,		       (float)height,		   0.0f, 0.0f, 1.0f);
	v[4] = Iris2DVertex((float)width,         	   0.0f,		   0.0f, 1.0f, 0.0f);
	v[5] = Iris2DVertex((float)width,      (float)height,		   0.0f, 1.0f, 1.0f);

	this->vb->Unlock();
}

void IrisBitmap::MakeTexture(const IIrisTone* tone, const IIrisRect* limitRect, int opacity){
	IrisRect srcRect(0, 0, (float)this->bitmap->GetWidth(), (float)this->bitmap->GetHeight());
	// 计算相交矩形
	int ix = (int)(srcRect.x > ((IrisRect*)((IrisRect*)limitRect))->x ? srcRect.x : ((IrisRect*)((IrisRect*)limitRect))->x);
	int iy = (int)(srcRect.y > ((IrisRect*)((IrisRect*)limitRect))->y ? srcRect.y : ((IrisRect*)((IrisRect*)limitRect))->y);
	int iwidth = (int)(((IrisRect*)((IrisRect*)limitRect))->x + ((IrisRect*)((IrisRect*)limitRect))->width > srcRect.width ? srcRect.width - ((IrisRect*)((IrisRect*)limitRect))->x : ((IrisRect*)((IrisRect*)limitRect))->width);
	int iheight = (int)(((IrisRect*)((IrisRect*)limitRect))->y + ((IrisRect*)((IrisRect*)limitRect))->height > srcRect.height ? srcRect.height - ((IrisRect*)limitRect)->y : ((IrisRect*)((IrisRect*)limitRect))->height);

	if (this->vb == 0){
		MakeBuffer(iwidth, iheight);
	}

	// Define Action
	if (this->texture == 0){
		D3DXCreateTexture(this->Device, iwidth, iheight,
			1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(this->texture));
	}

	if (this->needRefreshTexture == false)
		return;

	this->needRefreshTexture = false;

	Bitmap *tBitmap = this->bitmap;

	D3DLOCKED_RECT rect;
	this->texture->LockRect(0, &rect, NULL, 0);

	BitmapData bmpdt;
	Rect bpRect(ix, iy, iwidth, iheight);
	this->bitmap->LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt);

	PARGBQuad p = (PARGBQuad)bmpdt.Scan0;
	PARGBQuad p2 = (PARGBQuad)rect.pBits;

	PARGBQuad c1 = 0;
	PARGBQuad c2 = 0;

	int grayfull;

	/*
	grayfull = (r * 38 + g * 75 + b * 15) >> 7
	r = ((IrisTone*)tone).red  + r + (grayfull - r) * ((IrisTone*)tone).gray / 256
	g = ((IrisTone*)tone).green+ g + (grayfull - g) * ((IrisTone*)tone).gray / 256
	b = ((IrisTone*)tone).blue + b + (grayfull - b) * ((IrisTone*)tone).gray / 256
	*/

	for(unsigned int x = 0; x < bmpdt.Width; x++){
		for(unsigned int y = 0; y < bmpdt.Height; y++){
			c1 = p + x + y * bmpdt.Stride / sizeof(ARGBQuad);
			c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);
			c2->Alpha = c1->Alpha * opacity / 255;

			grayfull = (c1->Red * 38 + c1->Green * 75 + c1->Blue * 15) >> 7;
			c2->Red = ((IrisTone*)((IrisTone*)tone))->red + c1->Red + (grayfull - c1->Red) * ((IrisTone*)tone)->alpha / 255;
			c2->Green = ((IrisTone*)tone)->green + c1->Green + (grayfull - c1->Green) * ((IrisTone*)tone)->alpha / 255;
			c2->Blue = ((IrisTone*)tone)->blue + c1->Blue + (grayfull - c1->Blue) * ((IrisTone*)tone)->alpha / 255;

			grayfull = (c1->Red * 38 + c1->Green * 75 + c1->Blue * 15) >> 7;
			IrisTone* tt = (IrisTone*)this->inhoodViewport->GetTone();
			c2->Red = tt->red + c1->Red + (grayfull - c1->Red) * tt->alpha / 255;
			c2->Green = tt->green + c1->Green + (grayfull - c1->Green) * tt->alpha / 255;
			c2->Blue = tt->blue + c1->Blue + (grayfull - c1->Blue) * tt->alpha / 255;
		}
	}

	//memcpy(rect.pBits, bmpdt.Scan0, bmpdt.Width * bmpdt.Height * 4);

	this->bitmap->UnlockBits(&bmpdt);
	this->texture->UnlockRect(0);
}

//------ Initialize Interface for Ruby...
void IrisBitmap::SetInitData(wstring fileName){
	this->bitmap = new Bitmap(fileName.c_str(), FALSE);
	this->width = this->bitmap->GetWidth();
	this->height = this->bitmap->GetHeight();
}

void IrisBitmap::SetInitData(int width, int height){
	this->width = width;
	this->height = height;
	this->bitmap = new Bitmap(width, height, PixelFormat32bppARGB);
}
//------

IrisBitmap::IrisBitmap() {
	this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);
	this->texture = 0;
	this->vb = 0;
	//this->mtrl = d3d::WHITE_MTRL;
	this->inhoodViewport = 0;
	this->needRefreshTexture = true;
	this->limitRect = NULL;
	this->tone = new IrisTone(0, 0, 0, 0);
	this->viewportTone = new IrisTone(0, 0, 0, 0);
}

IrisBitmap::IrisBitmap(int width, int height){
	this->Device = ModuleIrisGraphics::Device;
	this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);
	this->width = width;
	this->height = height;
	this->bitmap = new Bitmap(width, height, PixelFormat32bppARGB);
	this->texture = 0;
	this->vb = 0;
	//this->mtrl = d3d::WHITE_MTRL;
	this->inhoodViewport = 0;
	this->needRefreshTexture = true;
	this->limitRect = new IrisRect((float)0, (float)0, (float)width, (float)height);
	this->tone = new IrisTone(0, 0, 0, 0);
	this->viewportTone = new IrisTone(0, 0, 0, 0);
}

IrisBitmap::IrisBitmap(wstring fileName){
	this->Device = ModuleIrisGraphics::Device;
	this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);

	this->bitmap = new Bitmap(fileName.c_str(), FALSE);

	this->width = this->bitmap->GetWidth();
	this->height = this->bitmap->GetHeight();
	this->texture = 0;
	this->vb = 0;
	//this->mtrl = d3d::WHITE_MTRL;
	this->inhoodViewport = 0;
	this->needRefreshTexture = true;
	this->limitRect = new IrisRect((float)0, (float)0, (float)this->width, (float)this->height);
	this->tone = new IrisTone(0, 0, 0, 0);
	this->viewportTone = new IrisTone(0, 0, 0, 0);
}

IIrisFont* IrisBitmap::GetFont(){
	return this->font;
}

void IrisBitmap::SetFont(IIrisFont* font){
	if (this->font != font){
		delete this->font;
		this->font = font;
	}
}

void IrisBitmap::Dispose(){
	if (Disposed()){
		return;
	}
	delete this->bitmap;
	delete this->font;
	delete this->limitRect;
	delete this->tone;
	delete this->viewportTone;
	d3d::Release<IDirect3DVertexBuffer9*>(this->vb);
	d3d::Release<IDirect3DTexture9*>(this->texture);
	this->texture = 0;
	this->vb = 0;
	this->font = 0;
	this->bitmap = 0;
	this->limitRect = 0;
	this->viewportTone = 0;
}

bool IrisBitmap::Disposed(){
	if(this->bitmap == 0)
		return true;
	return false;
}

Bitmap* IrisBitmap::ScaleBitmap(Bitmap* srcBitmap, int width, int height){
	Bitmap* tpBitmap = new Bitmap(width, height, srcBitmap->GetPixelFormat());
	if(tpBitmap){
		Graphics* g = new Graphics(tpBitmap);
		if(g){
			// use the best interpolation mode
			g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
			g->DrawImage(srcBitmap, 0, 0, width, height);
			delete g;
		}
	}
	return tpBitmap;
}

//start private----
bool IrisBitmap::IrisBitmapBitBlt(int x, int y, Bitmap *destBitmap, Bitmap* srcBitmap, Rect *srcRect, int opacity){
	////fail it if the width or height of src rect is larger than those of dect bimtap.
	//if(UINT(srcRect->Width + x) > destBitmap->GetWidth() || UINT(srcRect->Height + y) > destBitmap->GetHeight())
	//	return false;
	if (x < 0 || x > destBitmap->GetWidth() || y < 0 || y > destBitmap->GetHeight())
		return false;

	if(opacity > 255)
		opacity = 255;
	if(opacity < 0)
		opacity = 0;

	//----
	Bitmap *bmp1 = srcBitmap;
	BitmapData *bmpdt1 = new BitmapData();
	Rect *rect = srcRect;

	//----
	Bitmap *bmp2 = destBitmap;
	BitmapData* bmpdt2 = new BitmapData();

	int rx = x;
	int ry = y;
	int rw = srcRect->Width < destBitmap->GetWidth() - x ? srcRect->Width : destBitmap->GetWidth() - x;
	int rh = srcRect->Height < destBitmap->GetHeight() - y ? srcRect->Height : destBitmap->GetHeight() - y;
	Rect *rect2 = new Rect(rx, ry, rw, rh);

	//----
	bmp1->LockBits(rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, bmpdt1);
	bmp2->LockBits(rect2, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, bmpdt2);

	PARGBQuad p = (PARGBQuad)bmpdt1->Scan0;
	PARGBQuad p2 = (PARGBQuad)bmpdt2->Scan0;

	// 像素地址 = 基地址 + 单行扫描光栅宽度 * y + 像素长度 * x
	BYTE* tp1 = (BYTE*)p;
	BYTE* tp2 = (BYTE*)p2;

	for (UINT y = 0; y < bmpdt2->Height; y++){
		for (UINT x = 0; x <bmpdt2->Width; x++){
			PARGBQuad c1 = (PARGBQuad)tp1 + x + y * bmpdt1->Stride / sizeof(ARGBQuad);
			PARGBQuad c2 = (PARGBQuad)tp2 + x + y * bmpdt2->Stride / sizeof(ARGBQuad);
			c2->Alpha = c1->Alpha;
			c2->Blue = c1->Blue * opacity / 255 + c2->Blue * (1 - opacity / 255);
			c2->Green = c1->Green * opacity / 255 + c2->Green * (1 - opacity / 255);
			c2->Red = c1->Red * opacity / 255 + c2->Red * (1 - opacity / 255);
		}
	}

	bmp1->UnlockBits(bmpdt1);
	bmp2->UnlockBits(bmpdt2);

	delete bmpdt1;
	delete bmpdt2;
	delete rect2;

	return true;
}

void IrisBitmap::PrevFlash(const IIrisColor* color){
	IrisRect srcRect(0, 0, (float)this->bitmap->GetWidth(), (float)this->bitmap->GetHeight());
	// 计算相交矩形
	int iwidth = (int)(((IrisRect*)limitRect)->x + ((IrisRect*)limitRect)->width > srcRect.width ? srcRect.width - ((IrisRect*)limitRect)->x : ((IrisRect*)limitRect)->width);
	int iheight = (int)(((IrisRect*)limitRect)->y + ((IrisRect*)limitRect)->height > srcRect.height ? srcRect.height - ((IrisRect*)limitRect)->y : ((IrisRect*)limitRect)->height);

	D3DLOCKED_RECT rect;
	this->texture->LockRect(0, &rect, NULL, 0);
	PARGBQuad p2 = (PARGBQuad)rect.pBits;
	PARGBQuad c2 = 0;

	for (int x = 0; x < iwidth; x++){
		for (int y = 0; y < iheight; y++){
			c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);
			c2->Red = ((IrisColor*)color)->red;
			c2->Blue = ((IrisColor*)color)->blue;
			c2->Green = ((IrisColor*)color)->green;
		}
	}
	this->texture->UnlockRect(0);
}

void IrisBitmap::DoFlash(const IIrisColor* color, int duration){
	IrisRect srcRect(0, 0, (float)this->bitmap->GetWidth(), (float)this->bitmap->GetHeight());
	// 计算相交矩形
	int ix = (int)(srcRect.x > ((IrisRect*)limitRect)->x ? srcRect.x : ((IrisRect*)limitRect)->x);
	int iy = (int)(srcRect.y > ((IrisRect*)limitRect)->y ? srcRect.y : ((IrisRect*)limitRect)->y);
	int iwidth = (int)(((IrisRect*)limitRect)->x + ((IrisRect*)limitRect)->width > srcRect.width ? srcRect.width - ((IrisRect*)limitRect)->x : ((IrisRect*)limitRect)->width);
	int iheight = (int)(((IrisRect*)limitRect)->y + ((IrisRect*)limitRect)->height > srcRect.height ? srcRect.height - ((IrisRect*)limitRect)->y : ((IrisRect*)limitRect)->height);

	D3DLOCKED_RECT rect;
	this->texture->LockRect(0, &rect, NULL, 0);

	BitmapData bmpdt;
	Rect bpRect(ix, iy, iwidth, iheight);
	this->bitmap->LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt);

	PARGBQuad p = (PARGBQuad)bmpdt.Scan0;
	PARGBQuad p2 = (PARGBQuad)rect.pBits;

	PARGBQuad c1 = 0;
	PARGBQuad c2 = 0;

	for (unsigned int x = 0; x < bmpdt.Width; x++){
		for (unsigned int y = 0; y < bmpdt.Height; y++){
			c1 = p + x + y * bmpdt.Stride / sizeof(ARGBQuad);
			c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);

			c2->Red += (c1->Red - ((IrisColor*)color)->red) / duration;
			c2->Green += (c1->Green - ((IrisColor*)color)->green) / duration;
			c2->Blue += (c1->Blue - ((IrisColor*)color)->blue) / duration;
		}
	}

	//memcpy(rect.pBits, bmpdt.Scan0, bmpdt.Width * bmpdt.Height * 4);

	this->bitmap->UnlockBits(&bmpdt);
	this->texture->UnlockRect(0);
}

void IrisBitmap::EndFlash(){
	this->needRefreshTexture = true;
	this->MakeTexture(this->tone, this->limitRect);
}

bool IrisBitmap::IrisBitmapStretchBlt(Rect *destRect, Bitmap* destBitmap, Rect *srcRect, Bitmap* srcBitmap, int opacity){
	//safety check

//	if(srcBitmap->GetWidth() < UINT(srcRect->Width + srcRect->X) || srcBitmap->GetHeight() < UINT(srcRect->Height + srcRect->Y))
//		return false;
//	if(destBitmap->GetWidth() < UINT(destRect->Width + destRect->X) || destBitmap->GetHeight() < UINT(destRect->Height + destRect->Y))
//		return false;

	if(opacity > 255)
		opacity = 255;
	if(opacity < 0)
		opacity = 0;

	// 先获取截取位图
	Bitmap *tpBitmap = new Bitmap(srcRect->Width, srcRect->Height, PixelFormat32bppARGB);
	IrisBitmapBitBlt(0, 0, tpBitmap, srcBitmap, srcRect, 255);

	// 再缩放之
	Bitmap *scaleBitmap = ScaleBitmap(tpBitmap, destRect->Width, destRect->Height);

	// 复制过去
	Rect *rect = new Rect(0, 0, scaleBitmap->GetWidth(), scaleBitmap->GetHeight());
	IrisBitmapBitBlt(destRect->X, destRect->Y, destBitmap, scaleBitmap, rect, opacity);

	delete scaleBitmap;
	delete tpBitmap;
	delete rect;
	return true;
}
//----end private

bool IrisBitmap::Blt(int x, int y, const IIrisBitmap *srcIrisBitmap, const IIrisRect *srcIrisRect, int opacity = 255){
	this->needRefreshTexture = true;
	Rect rc(((IrisRect*)srcIrisRect)->x, ((IrisRect*)srcIrisRect)->y, ((IrisRect*)srcIrisRect)->width, ((IrisRect*)srcIrisRect)->height);
	return IrisBitmapBitBlt(x, y, this->bitmap, ((IrisBitmap*)srcIrisBitmap)->bitmap, &rc, opacity);
}

bool IrisBitmap::StretchBlt(const IIrisRect *destIrisRect, const IIrisBitmap *srcIrisBitmap, const IIrisRect *srcIrisRect, int opacity){
	this->needRefreshTexture = true;
	Rect rc(((IrisRect*)srcIrisRect)->x, ((IrisRect*)srcIrisRect)->y, ((IrisRect*)srcIrisRect)->width, ((IrisRect*)srcIrisRect)->height);
	Rect drc(((IrisRect*)destIrisRect)->x, ((IrisRect*)destIrisRect)->y, ((IrisRect*)destIrisRect)->width, ((IrisRect*)destIrisRect)->height);
	return IrisBitmapStretchBlt(&drc, this->bitmap, &rc, ((IrisBitmap*)srcIrisBitmap)->bitmap, opacity);
}

void IrisBitmap::FillRect(int x, int y, int width, int height, const IIrisColor *color){
	this->needRefreshTexture = true;
	Bitmap* tbitmap = this->bitmap->Clone(0, 0, this->width, this->height, PixelFormat32bppARGB);
	SolidBrush *tpBrush = new SolidBrush(Color(((IrisColor*)color)->alpha, ((IrisColor*)color)->red, ((IrisColor*)color)->green, ((IrisColor*)color)->blue));
	
	Graphics g(tbitmap);
	g.FillRectangle(tpBrush, x, y, width, height);

	delete this->bitmap;

	this->bitmap = tbitmap->Clone(0, 0, tbitmap->GetWidth(), tbitmap->GetHeight(), PixelFormat32bppARGB);

	delete tbitmap;
	delete tpBrush;
}

void IrisBitmap::FillRect(const IIrisRect *rect, const IIrisColor *color){
	this->FillRect((int)((IrisRect*)rect)->x, (int)((IrisRect*)rect)->y, (int)((IrisRect*)rect)->width, (int)((IrisRect*)rect)->height, color);
}

void IrisBitmap::GradientFillRect(int x, int y, int width, int height, const IIrisColor *color1, const IIrisColor *color2, bool vertical){
}

void IrisBitmap::GradientFillRect(const IIrisRect *rect, const IIrisColor *color1, const IIrisColor *color2, bool vertical){
}

void IrisBitmap::Clear(){
	this->needRefreshTexture = true;
	//graphics->Clear(Color(100, 100, 100));

	Bitmap* tp = this->bitmap->Clone(0, 0, this->width, this->height, PixelFormat32bppARGB);
	Graphics* tg = new Graphics(tp);

	delete this->bitmap;

	tg->Clear(Color(0, 0, 0, 0));
	
	this->bitmap = tp->Clone(0, 0, tp->GetWidth(), tp->GetHeight(), PixelFormat32bppARGB);

	delete tp;
	delete tg;

}

void IrisBitmap::ClearRect(int x, int y, int width, int height){
	//SolidBrush *tpBrush = new SolidBrush(Color(0, 0, 0));
	this->needRefreshTexture = true;
	IrisColor color(0, 0, 0, 0);
	this->FillRect(x, y, width, height, &color);
	
}

void IrisBitmap::ClearRect(IIrisRect* rect){
	this->ClearRect((int)((IrisRect*)rect)->x, (int)((IrisRect*)rect)->y, (int)((IrisRect*)rect)->width, (int)((IrisRect*)rect)->height);
}

IIrisColor* IrisBitmap::GetPixel(int x, int y){
	Color color;
	this->bitmap->GetPixel(x, y, &color);
	return new IrisColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void IrisBitmap::SetPixel(int x, int y, const IIrisColor *color){
	this->needRefreshTexture = true;
	Color *gdiColor = new Color(((IrisColor*)color)->alpha, ((IrisColor*)color)->red, ((IrisColor*)color)->green, ((IrisColor*)color)->blue);
	this->bitmap->SetPixel(x, y, *gdiColor);
	delete gdiColor;
}

void IrisBitmap::hueChange(float hue){

	this->needRefreshTexture = true;

	BitmapData bmpdt;
	Rect rect(0, 0, this->bitmap->GetWidth(), this->bitmap->GetHeight());
	this->bitmap->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt);

	PARGBQuad p = (PARGBQuad)bmpdt.Scan0;
    INT offset = bmpdt.Stride - bmpdt.Width * sizeof(ARGBQuad);

	BYTE* tp = (BYTE*)p;

	for(UINT y = 0; y < bmpdt.Height; y++, tp += offset){

		for(UINT x = 0; x < bmpdt.Width; x++, p++){
			COLOR_RGB colorRGB = {p->Red, p->Green, p->Blue};
			COLOR_HSL colorHSL = {0, 0, 0};

			IrisBitmap::BitmapRGBtoHSL(&colorRGB, &colorHSL);
			colorHSL.hue = hue;
			IrisBitmap::BitmapHSLtoRGB(&colorHSL, &colorRGB);

			p->Red = colorRGB.red;
			p->Green = colorRGB.green;
			p->Blue = colorRGB.blue;
		}
	}

	this->bitmap->UnlockBits(&bmpdt);
}

void IrisBitmap::blur(){
	this->needRefreshTexture = true;
}

void IrisBitmap::RadialBlur(float angle, int division){
	this->needRefreshTexture = true;
}

int IrisBitmap::TextSize(const IIrisFont* fontIris, wstring str){
	int size = IrisFont::defaultSize;
	IrisColor *color;
	wstring name;
	bool bold, shadow, italic;

	if(fontIris == NULL){
		name = IrisFont::defaultName;
		bold = IrisFont::defaultBold;
		shadow = IrisFont::defaultShadow;
		italic = IrisFont::defaultItalic;
		color = (IrisColor*)IrisFont::defaultColor;
	}
	else
	{
		name = ((IrisFont*)fontIris)->name;
		bold = ((IrisFont*)fontIris)->bold;
		shadow = ((IrisFont*)fontIris)->shadow;
		italic = ((IrisFont*)fontIris)->italic;
		color = (IrisColor*)((IrisFont*)fontIris)->color;
	}

	wstring text(str);

	FontFamily fontFamily(name.c_str());
	int fs = FontStyleRegular;

	if(bold)
		fs |= FontStyleBold;

	if(italic)
		fs |= FontStyleItalic;

	Font font(&fontFamily, (REAL)size, fs, UnitWorld);

	RectF boundRect;
	Graphics g(this->bitmap);

	g.MeasureString(str.c_str(), text.length(), &font, PointF(0, 0), &boundRect);

	return (int)boundRect.Width;
}


void IrisBitmap::IrisDrawText(const IIrisFont* fontIris, int x, int y, int width, int height, wstring str, int align){
	this->needRefreshTexture = true;
	Gdiplus::Bitmap *tBitmap = this->bitmap->Clone(0, 0, this->bitmap->GetWidth(), this->bitmap->GetHeight(), PixelFormat32bppARGB);

	Graphics tg(tBitmap);

	int size = IrisFont::defaultSize;
	IrisColor *color;
	wstring name;
	bool bold, shadow, italic;

	if(fontIris == NULL){
		name = IrisFont::defaultName;
		bold = IrisFont::defaultBold;
		shadow = IrisFont::defaultShadow;
		italic = IrisFont::defaultItalic;
		color = (IrisColor*)IrisFont::defaultColor;
	}
	else
	{
		name = ((IrisFont*)fontIris)->name;
		bold = ((IrisFont*)fontIris)->bold;
		shadow = ((IrisFont*)fontIris)->shadow;
		italic = ((IrisFont*)fontIris)->italic;
		color = (IrisColor*)((IrisFont*)fontIris)->color;
	}

	FontFamily fontFamily(name.c_str());
	int fs = FontStyleRegular;

	if(bold)
		fs |= FontStyleBold;

	if(italic)
		fs |= FontStyleItalic;

	Font font(&fontFamily, (REAL)size, fs, UnitWorld);

	StringFormat strFormat;

	switch(align){
	case 0:
		strFormat.SetAlignment(StringAlignmentNear);
		break;
	case 1:
		strFormat.SetAlignment(StringAlignmentCenter);
		break;
	}

	Brush *brush;

	if(shadow)
		brush = new HatchBrush(HatchStyle90Percent, Color(color->red, color->green, color->blue));
	else
		brush = new SolidBrush(Color(color->red, color->green, color->blue));

	Color keyColor;
	if(color->red == 0 || color->blue == 0 || color-> green == 0)
		keyColor = Color::MakeARGB(255, 255, 255, 255);
	else
		keyColor = Color::MakeARGB(255, color->red - 1, color->green - 1, color->blue - 1);

	Gdiplus::PointF point((REAL)x, (REAL)y);
	strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
	Gdiplus::RectF r((REAL)x, (REAL)y, (REAL)width, (REAL)height);

	tg.DrawString(str.c_str(), str.length(), &font, r, &strFormat, brush);

	if(this->bitmap != 0){
		delete this->bitmap;
		this->bitmap = 0;
	}

	this->bitmap = tBitmap->Clone(0, 0, tBitmap->GetWidth(), tBitmap->GetHeight(), PixelFormat32bppARGB);

	delete brush;
	delete tBitmap;

}

void IrisBitmap::IrisDrawText(const IIrisFont* fontIris, const IIrisRect *rect, wstring str, int align){
	IrisDrawText(fontIris, (int)((IrisRect*)rect)->x, (int)((IrisRect*)rect)->y, (int)((IrisRect*)rect)->width, (int)((IrisRect*)rect)->height, str, align);
}

void IrisBitmap::Draw(int opacity, IIrisViewport *tViewport, IIrisRect* Rect, IIrisTone* tone){
	bool flag = false;
	if (this->needRefreshTexture == true){
		flag = true;
	}

	if (this->inhoodViewport != tViewport){
		this->inhoodViewport = tViewport;
		this->needRefreshTexture = true;
		flag = true;
	}

	if (((IrisRect*)(this->limitRect))->x != ((IrisRect*)Rect)->x || ((IrisRect*)(this->limitRect))->y != ((IrisRect*)Rect)->y
		|| ((IrisRect*)(this->limitRect))->width != ((IrisRect*)Rect)->width || ((IrisRect*)(this->limitRect))->height != ((IrisRect*)Rect)->height){
		delete this->limitRect;
		this->limitRect = new IrisRect(*((IrisRect*)Rect));
		this->needRefreshTexture = true;
		flag = true;
	}

	if (((IrisTone*)(this->tone))->red != ((IrisTone*)tone)->red || ((IrisTone*)(this->tone))->blue != ((IrisTone*)tone)->blue
		|| ((IrisTone*)(this->tone))->green != ((IrisTone*)tone)->green || ((IrisTone*)(this->tone))->alpha != ((IrisTone*)tone)->alpha){
		delete this->tone;
		this->tone = new IrisTone(*((IrisTone*)tone));
		this->needRefreshTexture = true;
		flag = true;
	}

	if (((IrisTone*)(this->viewportTone))->red != ((IrisTone*)(this->inhoodViewport->GetTone()))->red
		|| ((IrisTone*)(this->viewportTone))->blue != ((IrisTone*)(this->inhoodViewport->GetTone()))->blue
		|| ((IrisTone*)(this->viewportTone))->green != ((IrisTone*)(this->inhoodViewport->GetTone()))->green
		|| ((IrisTone*)(this->viewportTone))->alpha != ((IrisTone*)(this->inhoodViewport->GetTone()))->alpha){
		delete this->viewportTone;
		this->viewportTone = new IrisTone(*((IrisTone*)(this->inhoodViewport->GetTone())));
		this->needRefreshTexture = true;
		flag = true;
	}

	if (flag)
		this->MakeTexture(tone, this->limitRect, opacity);

}

IDirect3DVertexBuffer9* IrisBitmap::GetVb(){
	return this->vb;
}

IDirect3DTexture9* IrisBitmap::GetTexture(){
	return this->texture;
}

IDirect3DDevice9* IrisBitmap::GetDevice(){
	return this->Device;
}

void IrisBitmap::SetOpacity(int opacity){

	IrisRect srcRect(0, 0, (float)this->bitmap->GetWidth(), (float)this->bitmap->GetHeight());
	// 计算相交矩形
	int iwidth = (int)(((IrisRect*)limitRect)->x + ((IrisRect*)limitRect)->width > srcRect.width ? srcRect.width - ((IrisRect*)limitRect)->x : ((IrisRect*)limitRect)->width);
	int iheight = (int)(((IrisRect*)limitRect)->y + ((IrisRect*)limitRect)->height > srcRect.height ? srcRect.height - ((IrisRect*)limitRect)->y : ((IrisRect*)limitRect)->height);

	D3DLOCKED_RECT rect;
	this->texture->LockRect(0, &rect, NULL, 0);

	PARGBQuad p2 = (PARGBQuad)rect.pBits;

	PARGBQuad c2 = 0;

	for (int x = 0; x < iwidth; x++){
		for (int y = 0; y < iheight; y++){
			c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);
			c2->Alpha = c2->Alpha * opacity / 255;

		}
	}

	this->texture->UnlockRect(0);
}

int IrisBitmap::GetWidth(){
	return this->bitmap->GetWidth();
}

int IrisBitmap::GetHeight(){
	return this->bitmap->GetHeight();
}

void IrisBitmap::SaveToFile(wstring fileName){
	CLSID encoderClsid;
	ModuleIrisGraphics::GetEncoderClsid(L"image/png", &encoderClsid);
	this->bitmap->Save(fileName.c_str(), &encoderClsid, 0);
	ModuleIrisGraphics::Device;
}


IrisBitmap::~IrisBitmap(void)
{
	if(!this->Disposed())
		this->Dispose();
}
