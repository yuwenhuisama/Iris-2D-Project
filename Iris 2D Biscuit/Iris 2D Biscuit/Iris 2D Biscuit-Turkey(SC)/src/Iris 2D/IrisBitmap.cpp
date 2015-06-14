#include "IrisBitmap.h"
#include "ModuleIrisGraphics.h"

namespace Iris2D{

	list<IrisBitmap*> IrisBitmap::bitmapList;

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
		float h = 0, s = 0, l = 0;
		// normalizes red-green-blue values
		float r = rgb->red / 255.f;
		float g = rgb->green / 255.f;
		float b = rgb->blue / 255.f;
		float maxVal = max3v(r, g, b);
		float minVal = min3v(r, g, b);

		// hue

		if (maxVal == minVal)
		{
			h = 0; // undefined
		}

		else if (maxVal == r && g >= b)
		{
			h = 60.0f*(g - b) / (maxVal - minVal);
		}

		else if (maxVal == r && g < b)
		{
			h = 60.0f*(g - b) / (maxVal - minVal) + 360.0f;
		}

		else if (maxVal == g)
		{
			h = 60.0f*(b - r) / (maxVal - minVal) + 120.0f;
		}
		else if (maxVal == b)
		{
			h = 60.0f*(r - g) / (maxVal - minVal) + 240.0f;
		}

		// luminance
		l = (maxVal + minVal) / 2.0f;
		// saturation

		if (l == 0 || maxVal == minVal)
		{
			s = 0;
		}

		else if (0 < l && l <= 0.5f)
		{
			s = (maxVal - minVal) / (maxVal + minVal);
		}
		else if (l > 0.5f)
		{
			s = (maxVal - minVal) / (2 - (maxVal + minVal)); //(maxVal-minVal > 0)?
		}
		hsl->hue = (h > 360) ? 360 : ((h < 0) ? 0 : h);
		hsl->saturation = ((s>1) ? 1 : ((s < 0) ? 0 : s)) * 100;
		hsl->luminance = ((l>1) ? 1 : ((l < 0) ? 0 : l)) * 100;
	}

	// Converts HSL to RGB
	void IrisBitmap::BitmapHSLtoRGB(const COLOR_HSL *hsl, COLOR_RGB *rgb)
	{
		float h = hsl->hue;                  // h must be [0, 360]
		float s = hsl->saturation / 100.f; // s must be [0, 1]
		float l = hsl->luminance / 100.f;      // l must be [0, 1]
		float R, G, B;

		if (hsl->saturation == 0)
		{
			// achromatic color (gray scale)
			R = G = B = l*255.f;
		}
		else
		{
			float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - (l*s));
			float p = (2.0f * l) - q;
			float Hk = h / 360.0f;
			float T[3];
			T[0] = Hk + 0.3333333f; // Tr   0.3333333f=1.0/3.0
			T[1] = Hk;              // Tb
			T[2] = Hk - 0.3333333f; // Tg

			for (int i = 0; i < 3; i++)
			{
				if (T[i] < 0) T[i] += 1.0f;
				if (T[i] > 1) T[i] -= 1.0f;

				if ((T[i] * 6) < 1)
				{
					T[i] = p + ((q - p)*6.0f*T[i]);
				}
				else if ((T[i] * 2.0f) < 1) //(1.0/6.0)<=T[i] && T[i]<0.5
				{
					T[i] = q;
				}
				else if ((T[i] * 3.0f) < 2) // 0.5<=T[i] && T[i]<(2.0/3.0)
				{
					T[i] = p + (q - p) * ((2.0f / 3.0f) - T[i]) * 6.0f;
				}
				else T[i] = p;
			}
			R = T[0] * 255.0f;
			G = T[1] * 255.0f;
			B = T[2] * 255.0f;

		}
		rgb->red = (BYTE)((R > 255) ? 255 : ((R < 0) ? 0 : R));
		rgb->green = (BYTE)((G>255) ? 255 : ((G < 0) ? 0 : G));
		rgb->blue = (BYTE)((B>255) ? 255 : ((B < 0) ? 0 : B));
	}

	bool IrisBitmap::MakeBuffer(int width, int height){
		HRESULT r = this->Device->CreateVertexBuffer(6 * sizeof(Iris2DVertex), D3DUSAGE_WRITEONLY, Iris2DVertex::FVF, D3DPOOL_MANAGED, &(this->vb), 0);

		if (FAILED(r)) return false;

		Iris2DVertex* v;
		if(FAILED(this->vb->Lock(0, 0, (void**)&v, 0))) return false;
		/* persist to change*/
		/*
		v[0] = Iris2DVertex(0.0f,			   (float)height,		   0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f,			       0.0f,			   0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)width,		   0.0f,			   0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f - 1,		       (float)height,	   0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)width,         	   0.0f,		   0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)width,      (float)height,		   0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
		*/

		v[0] = Iris2DVertex(0.0f, (float)height, 0.0f, 0.0f, 1.0f);
		v[1] = Iris2DVertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Iris2DVertex((float)width, 0.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Iris2DVertex(0.0f - 1, (float)height, 0.0f, 0.0f, 1.0f);
		v[4] = Iris2DVertex((float)width, 0.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Iris2DVertex((float)width, (float)height, 0.0f, 1.0f, 1.0f);
		
		v[0]._u += 0.5f / width; v[0]._v += 0.5f / height;
		v[1]._u += 0.5f / width; v[1]._v += 0.5f / height;
		v[2]._u += 0.5f / width; v[2]._v += 0.5f / height;
		v[3]._u += 0.5f / width; v[3]._v += 0.5f / height;
		v[4]._u += 0.5f / width; v[4]._v += 0.5f / height;
		v[5]._u += 0.5f / width; v[5]._v += 0.5f / height;

		if (FAILED(this->vb->Unlock())) return false;

		return true;
	}

	bool IrisBitmap::MakeTexture(const IrisRect* limitRect){

		bool remake = false;
		if (limitRect->x != this->limitRect->x
			|| limitRect->y != this->limitRect->y
			|| limitRect->width != this->limitRect->width
			|| limitRect->height != this->limitRect->height){
			remake = true;
			delete this->limitRect;
			this->limitRect = new IrisRect(*limitRect);
		}

		IrisRect srcRect(0, 0, (float)this->bitmap->GetWidth(), (float)this->bitmap->GetHeight());
		// 计算相交矩形
		int ix = (int)(srcRect.x > limitRect->x ? srcRect.x : limitRect->x);
		int iy = (int)(srcRect.y > limitRect->y ? srcRect.y : limitRect->y);
		int iwidth = (int)(limitRect->x + limitRect->width > srcRect.width ? srcRect.width - limitRect->x : limitRect->width);
		int iheight = (int)(limitRect->y + limitRect->height > srcRect.height ? srcRect.height - limitRect->y : limitRect->height);

		if (this->vb == 0){
			MakeBuffer(iwidth, iheight);
		}
		else {
			if (remake){
				Iris2DVertex* v;
				if (FAILED(this->vb->Lock(0, 0, (void**)&v, 0))) return false;

				v[0]._y = (float)iheight;
				v[2]._x = (float)iwidth;
				v[3]._y = (float)iheight;
				v[4]._x = (float)iwidth;
				v[5]._x = (float)iwidth; v[5]._y = (float)iheight;

				if (FAILED(this->vb->Unlock())) return false;
			}
		}

		// Define Action
		if (this->texture == 0){
			if(FAILED(D3DXCreateTexture(this->Device, iwidth, iheight,
				1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(this->texture)))) return false;
		}
		else{
			if (remake){
				d3d::Release<IDirect3DTexture9*>(this->texture);
				if (FAILED(D3DXCreateTexture(this->Device, iwidth, iheight,
					1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(this->texture)))) return false;
			}
		}

		if (this->needRefreshTexture == false)
			return true;

		this->needRefreshTexture = false;

		D3DLOCKED_RECT rect;
		if(FAILED(this->texture->LockRect(0, &rect, NULL, 0))) return false;

		BitmapData bmpdt;
		Rect bpRect(ix, iy, iwidth, iheight);
		if (FAILED(this->bitmap->LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt))) return false;

		PARGBQuad p = (PARGBQuad)bmpdt.Scan0;
		PARGBQuad p2 = (PARGBQuad)rect.pBits;

		PARGBQuad c1 = 0;
		PARGBQuad c2 = 0;

		//int grayfull;

		/*
		grayfull = (r * 38 + g * 75 + b * 15) >> 7
		r = tone.red  + r + (grayfull - r) * tone.gray / 256
		g = tone.green+ g + (grayfull - g) * tone.gray / 256
		b = tone.blue + b + (grayfull - b) * tone.gray / 256
		*/

		//memcpy(p2, p, bmpdt.Width * bmpdt.Height * sizeof(ARGBQuad));

		for (unsigned int x = 0; x < bmpdt.Width; x++){
			for (unsigned int y = 0; y < bmpdt.Height; y++){
				c1 = p + x + y * bmpdt.Stride / sizeof(ARGBQuad);
				c2 = p2 + x + y * rect.Pitch / sizeof(ARGBQuad);
				*c2 = *c1;
				//c2->Alpha = c1->Alpha;
				//c2->Red = c1->Red;
				//c2->Green = c1->Green;
				//c2->Blue = c1->Blue;
			}
		}

		if(FAILED(this->bitmap->UnlockBits(&bmpdt))) return false;
		if(FAILED(this->texture->UnlockRect(0))) return false;

		return true;
	}

	void IrisBitmap::SaveToFile(wstring fileName, IR_PARAM_RESULT_CT){
		CLSID encoderClsid;
		ModuleIrisGraphics::GetEncoderClsid(L"image/png", &encoderClsid);
		if (FAILED((this->bitmap->Save(fileName.c_str(), &encoderClsid, NULL))))
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Writing to File!")
		else
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	//------ Initialize Interface for Ruby...
	void IrisBitmap::SetInitData(wstring fileName, IR_PARAM_RESULT_CT){
		this->bitmap = new Bitmap(fileName.c_str(), FALSE);
		if (this->bitmap->GetWidth())
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"" > 0)
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Creating Bitmap!")
		this->width = this->bitmap->GetWidth();
		this->height = this->bitmap->GetHeight();
	}

	void IrisBitmap::SetInitData(int width, int height, IR_PARAM_RESULT_CT){
		this->width = width;
		this->height = height;
		this->bitmap = new Bitmap(width, height, PixelFormat32bppARGB);
		if (this->bitmap->GetWidth() > 0)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Creating Bitmap!")
	}
	//------

	IrisBitmap::IrisBitmap(IR_PARAM_RESULT_CT) {
		this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);
		this->texture = 0;
		this->vb = 0;
		//this->mtrl = d3d::WHITE_MTRL;
		this->bitmap = NULL;
		this->needRefreshTexture = true;
		this->limitRect = NULL;
		this->recoverFlag = false;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	IrisBitmap::IrisBitmap(int width, int height, IR_PARAM_RESULT_CT){
		this->Device = ModuleIrisGraphics::GetDevice();
		this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);
		this->width = width;
		this->height = height;
		this->bitmap = new Bitmap(width, height, PixelFormat32bppARGB);
		if (this->bitmap->GetWidth() > 0)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else{
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"Error in Creating Bitmap!")
			return;
		}
		this->texture = 0;
		this->vb = 0;
		this->recoverFlag = false;
		//this->mtrl = d3d::WHITE_MTRL;
		this->limitRect = new IrisRect((float)0, (float)0, (float)width, (float)height);
	}

	IrisBitmap::IrisBitmap(wstring fileName, IR_PARAM_RESULT_CT){
		this->Device = ModuleIrisGraphics::GetDevice();
		this->font = new IrisFont(IrisFont::defaultName, IrisFont::defaultSize);
		if (IrisEncripedResourceManager::Instance()->HaveSource(fileName)){
			char* pData = NULL;
			int nWidth = 0;
			int nHeight = 0;
			IrisEncripedResourceManager::Instance()->GetBitmapData(fileName, &pData, &nWidth, &nHeight);
			this->bitmap = new Bitmap(nWidth, nHeight, PixelFormat32bppARGB);
			BitmapData bmpdt1;
			Rect rect(0, 0, nWidth, nHeight);
			if (FAILED(this->bitmap->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt1))){
				IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Creating Bitmap!")
					return;
			}
			memcpy(bmpdt1.Scan0, pData, nWidth * nHeight * sizeof(RGBQUAD));
			this->bitmap->UnlockBits(&bmpdt1);
		}
		else{
			this->bitmap = new Bitmap(fileName.c_str(), FALSE);
		}
		if (this->bitmap->GetWidth() > 0)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else {
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"Error in Creating Bitmap!")
			return;
		}
		this->width = this->bitmap->GetWidth();
		this->height = this->bitmap->GetHeight();
		this->texture = 0;
		this->vb = 0;
		this->recoverFlag = false;
		//this->mtrl = d3d::WHITE_MTRL;
		this->needRefreshTexture = true;
		this->limitRect = new IrisRect((float)0, (float)0, (float)this->width, (float)this->height);
	}

	IrisBitmap::IrisBitmap(const char* bmpData, int width, int height, IR_PARAM_RESULT_CT) : IrisBitmap(width, height, IR_PARAM){
		BitmapData bmpdt1;
		Rect rect(0, 0, width, height);
		if (FAILED(this->bitmap->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt1))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Creating Bitmap!")
			return;
		}

		memcpy(bmpdt1.Scan0, bmpData, width * height * sizeof(RGBQUAD));

		this->bitmap->UnlockBits(&bmpdt1);
	}

	void IrisBitmap::Dispose(IR_PARAM_RESULT_CT){
		delete this->bitmap;
		delete this->font;
		delete this->limitRect;
		//delete this->tone;
		d3d::Release<IDirect3DVertexBuffer9*>(this->vb);
		d3d::Release<IDirect3DTexture9*>(this->texture);
		this->texture = 0;
		this->vb = 0;
		this->bitmap = 0;
		this->font = 0;
		this->limitRect = 0;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	bool IrisBitmap::Disposed(IR_PARAM_RESULT_CT){
		if (this->bitmap == 0){
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
			return true;
		}
		IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Disposing Bitmap")
		return false;
	}

	Bitmap* IrisBitmap::ScaleBitmap(Bitmap* srcBitmap, int width, int height){
		Bitmap* tpBitmap = new Bitmap(width, height, srcBitmap->GetPixelFormat());
		if (tpBitmap){
			Graphics* g = new Graphics(tpBitmap);
			if (g){
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
		bool flag = true;
		if (x < 0 || x > (int)destBitmap->GetWidth() || y < 0 || y > (int)destBitmap->GetHeight())
			return false;

		if (opacity > 255)
			opacity = 255;
		if (opacity < 0)
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
		int rw = srcRect->Width < (int)destBitmap->GetWidth() - x ? srcRect->Width : (int)destBitmap->GetWidth() - x;
		int rh = srcRect->Height < (int)destBitmap->GetHeight() - y ? srcRect->Height : (int)destBitmap->GetHeight() - y;
		Rect *rect2 = new Rect(rx, ry, rw, rh);

		//----
		if (FAILED(bmp1->LockBits(rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, bmpdt1))) flag = false;
		if (FAILED(bmp2->LockBits(rect2, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, bmpdt2))) flag = false;

		PARGBQuad p = (PARGBQuad)bmpdt1->Scan0;
		PARGBQuad p2 = (PARGBQuad)bmpdt2->Scan0;

		// 像素地址 = 基地址 + 单行扫描光栅宽度 * y + 像素长度 * x
		BYTE* tp1 = (BYTE*)p;
		BYTE* tp2 = (BYTE*)p2;

		for (UINT y = 0; y < bmpdt2->Height; y++){
			for (UINT x = 0; x <bmpdt2->Width; x++){
				PARGBQuad c1 = (PARGBQuad)tp1 + x + y * bmpdt1->Stride / sizeof(ARGBQuad);
				PARGBQuad c2 = (PARGBQuad)tp2 + x + y * bmpdt2->Stride / sizeof(ARGBQuad);
				*c2 = *c1;
			}
		}

		//memcpy(tp2, tp1, bmpdt2->Width * bmpdt2->Height * sizeof(ARGBQuad));

		if (FAILED(bmp1->UnlockBits(bmpdt1))) flag = false;
		if (FAILED(bmp2->UnlockBits(bmpdt2))) flag = false;

		delete bmpdt1;
		delete bmpdt2;
		delete rect2;

		return flag;
	}

	bool IrisBitmap::IrisBitmapStretchBlt(Rect *destRect, Bitmap* destBitmap, Rect *srcRect, Bitmap* srcBitmap, int opacity){

		if (opacity > 255)
			opacity = 255;
		if (opacity < 0)
			opacity = 0;

		// 先获取截取位图
		Bitmap *tpBitmap = new Bitmap(srcRect->Width, srcRect->Height, PixelFormat32bppARGB);
		IrisBitmapBitBlt(0, 0, tpBitmap, srcBitmap, srcRect, 255);

		// 再缩放之
		Bitmap *scaleBitmap = ScaleBitmap(tpBitmap, destRect->Width, destRect->Height);

		// 复制过去
		Rect *rect = new Rect(0, 0, scaleBitmap->GetWidth(), scaleBitmap->GetHeight());
		bool r = IrisBitmapBitBlt(destRect->X, destRect->Y, destBitmap, scaleBitmap, rect, opacity);

		delete scaleBitmap;
		delete tpBitmap;
		delete rect;
		return r;
	}
	//----end private

	bool IrisBitmap::Blt(int x, int y, const IrisBitmap *srcIrisBitmap, const IrisRect *srcIrisRect, int opacity, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		Rect rc((int)srcIrisRect->x, (int)srcIrisRect->y, (int)srcIrisRect->width, (int)srcIrisRect->height);
		bool r = IrisBitmapBitBlt(x, y, this->bitmap, srcIrisBitmap->bitmap, &rc, opacity);
		if (r)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Blting!")
		return r;
	}

	bool IrisBitmap::StretchBlt(const IrisRect *destIrisRect, const IrisBitmap *srcIrisBitmap, const IrisRect *srcIrisRect, int opacity, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		Rect rc((int)srcIrisRect->x, (int)srcIrisRect->y, (int)srcIrisRect->width, (int)srcIrisRect->height);
		Rect drc((int)destIrisRect->x, (int)destIrisRect->y, (int)destIrisRect->width, (int)destIrisRect->height);
		bool r = IrisBitmapStretchBlt(&drc, this->bitmap, &rc, srcIrisBitmap->bitmap, opacity);
		if (r)
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		else
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in StretchBlting!")
		return r;
	}

	void IrisBitmap::FillRect(int x, int y, int width, int height, const IrisColor *color, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		Bitmap* tbitmap = this->bitmap->Clone(0, 0, this->width, this->height, PixelFormat32bppARGB);
		SolidBrush *tpBrush = new SolidBrush(Color(color->alpha, color->red, color->green, color->blue));

		delete this->bitmap;
		Graphics g(tbitmap);
		g.FillRectangle(tpBrush, x, y, width, height);

		this->bitmap = tbitmap->Clone(0, 0, tbitmap->GetWidth(), tbitmap->GetHeight(), PixelFormat32bppARGB);

		delete tbitmap;
		delete tpBrush;

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisBitmap::FillRect(const IrisRect *rect, const IrisColor *color, IR_PARAM_RESULT_CT){
		this->FillRect((int)rect->x, (int)rect->y, (int)rect->width, (int)rect->height, color, IR_PARAM);
	}

	void IrisBitmap::Clear(IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;

		Bitmap* tp = this->bitmap->Clone(0, 0, this->width, this->height, PixelFormat32bppARGB);
		Graphics* tg = new Graphics(tp);
		delete this->bitmap;
		tg->Clear(Color(0, 0, 0, 0));
		this->bitmap = tp->Clone(0, 0, tp->GetWidth(), tp->GetHeight(), PixelFormat32bppARGB);

		delete tp;
		delete tg;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisBitmap::ClearRect(int x, int y, int width, int height, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		IrisColor color(0, 0, 0, 0);
		this->FillRect(x, y, width, height, &color, IR_PARAM);
	}

	void IrisBitmap::ClearRect(const IrisRect* rect, IR_PARAM_RESULT_CT){
		this->ClearRect((int)rect->x, (int)rect->y, (int)rect->width, (int)rect->height, IR_PARAM);
	}

	IrisColor* IrisBitmap::GetPixel(int x, int y, IR_PARAM_RESULT_CT){
		Color color;
		if (FAILED(this->bitmap->GetPixel(x, y, &color))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Getting Pixel")
			color.SetValue(0x00000000);
		}
		else
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		return new IrisColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	}

	void IrisBitmap::SetPixel(int x, int y, const IrisColor *color, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		Color *gdiColor = new Color(color->alpha, color->red, color->green, color->blue);
		if (FAILED(this->bitmap->SetPixel(x, y, *gdiColor)))
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Setting Pixel")
		else
			IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")

		delete gdiColor;
	}

	void IrisBitmap::HueChange(float hue, IR_PARAM_RESULT_CT){

		this->needRefreshTexture = true;

		BitmapData bmpdt;
		Rect rect(0, 0, this->bitmap->GetWidth(), this->bitmap->GetHeight());
		if (FAILED(this->bitmap->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &bmpdt))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Hue Changing !")
			return;
		}

		PARGBQuad p = (PARGBQuad)bmpdt.Scan0;
		INT offset = bmpdt.Stride - bmpdt.Width * sizeof(ARGBQuad);

		BYTE* tp = (BYTE*)p;

		for (UINT y = 0; y < bmpdt.Height; y++, tp += offset){

			for (UINT x = 0; x < bmpdt.Width; x++, p++){
				COLOR_RGB colorRGB = { p->Red, p->Green, p->Blue };
				COLOR_HSL colorHSL = { 0, 0, 0 };

				IrisBitmap::BitmapRGBtoHSL(&colorRGB, &colorHSL);
				colorHSL.hue = hue;
				IrisBitmap::BitmapHSLtoRGB(&colorHSL, &colorRGB);

				p->Red = colorRGB.red;
				p->Green = colorRGB.green;
				p->Blue = colorRGB.blue;
			}
		}

		if (FAILED(this->bitmap->UnlockBits(&bmpdt))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Hue Changing !")
			return;
		}
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisBitmap::GradientFillRect(int x, int y, int width, int height, const IrisColor *color1, const IrisColor *color2, bool vertical, IR_PARAM_RESULT_CT){
	}

	void IrisBitmap::GradientFillRect(const IrisRect *rect, const IrisColor *color1, const IrisColor *color2, bool vertical, IR_PARAM_RESULT_CT){
	}

	void IrisBitmap::Blur(IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisBitmap::RadialBlur(float angle, int division, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;
		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	int IrisBitmap::TextSize(const IrisFont* fontIris, wstring str, IR_PARAM_RESULT_CT){
		int size = IrisFont::defaultSize;
		IrisColor *color = IrisFont::defaultColor;
		wstring name;
		bool bold, shadow, italic;

		if (fontIris == NULL){
			name = IrisFont::defaultName;
			bold = IrisFont::defaultBold;
			shadow = IrisFont::defaultShadow;
			italic = IrisFont::defaultItalic;
		}
		else
		{
			name = fontIris->name;
			bold = fontIris->bold;
			shadow = fontIris->shadow;
			italic = fontIris->italic;
		}

		wstring text(str);

		FontFamily fontFamily(name.c_str());
		int fs = FontStyleRegular;

		if (bold)
			fs |= FontStyleBold;

		if (italic)
			fs |= FontStyleItalic;

		Font font(&fontFamily, (REAL)size, fs, UnitWorld);

		RectF boundRect;
		Graphics g(this->bitmap);

		if (FAILED(g.MeasureString(str.c_str(), text.length(), &font, PointF(0, 0), &boundRect))){
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Measuring String !")
			return 0;
		}

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
		return (int)boundRect.Width;
	}

	void IrisBitmap::IrisDrawText(int x, int y, int width, int height, wstring str, int align, IR_PARAM_RESULT_CT){
		this->needRefreshTexture = true;

		if (x > this->width || y > this->height || x < 0 || y < 0)
			return;

		IrisFont* fontIris = this->font;
		IrisColor *color = NULL;

		int size = IrisFont::defaultSize;
		wstring name;
		bool bold, shadow, italic;

 		if (fontIris == NULL){
			name = IrisFont::defaultName;
			bold = IrisFont::defaultBold;
			shadow = IrisFont::defaultShadow;
			italic = IrisFont::defaultItalic;
			color = IrisFont::defaultColor;
		}
		else
		{
			size = fontIris->size;
			name = fontIris->name;
			bold = fontIris->bold;
			shadow = fontIris->shadow;
			italic = fontIris->italic;
			color = fontIris->color;
		}

		// release

		Gdiplus::Bitmap *tBitmap = this->bitmap->Clone(0, 0, this->bitmap->GetWidth(), this->bitmap->GetHeight(), PixelFormat32bppARGB);
		Graphics tg(tBitmap);

		Gdiplus::FontFamily fontFamily(name.c_str());
		int fs = FontStyleRegular;

		if (bold)
			fs |= FontStyleBold;

		if (italic)
			fs |= FontStyleItalic;

		//lfont.lfWeight = 1000;
		Gdiplus::Font font(&fontFamily, (REAL)size, fs, UnitPixel);

		StringFormat strFormat;

		switch (align){
		case 0:
			strFormat.SetAlignment(StringAlignmentNear);
			break;
		case 1:
			strFormat.SetAlignment(StringAlignmentCenter);
			break;
		}

		Brush *brush;

		if (shadow)
			brush = new HatchBrush(HatchStyle90Percent, Color(color->red, color->green, color->blue));
		else
			brush = new SolidBrush(Color(color->red, color->green, color->blue));

		strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
		Gdiplus::RectF r((REAL)x, (REAL)y, (REAL)width, (REAL)height);
		tg.SetSmoothingMode(SmoothingModeAntiAlias);
		tg.SetInterpolationMode(InterpolationModeHighQualityBicubic);
		Gdiplus::GraphicsPath path;
		if (FAILED(path.AddString(str.c_str(), str.size(), &fontFamily, FontStyleRegular, (REAL)size, r, &strFormat))){
			delete brush;
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in AddingString of Drawing Text!")
			return;
		}
		Gdiplus::Pen pen(Color(color->red, color->green, color->blue), 1);
		if (FAILED(tg.DrawPath(&pen, &path))){
			delete brush;
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Drawing Path of Drawing Text !")
			return;
		}
		if (FAILED(tg.FillPath(brush, &path))){
			delete brush;
			IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Filling Path of Drawing Text !")
			return;
		}

		if (this->bitmap != 0){
			delete this->bitmap;
			this->bitmap = 0;
		}

		this->bitmap = tBitmap->Clone(0, 0, tBitmap->GetWidth(), tBitmap->GetHeight(), PixelFormat32bppARGB);

		//CLSID encoderClsid;
		//ModuleIrisGraphics::GetEncoderClsid(L"image/png", &encoderClsid);
		//this->bitmap->Save(L"string.png", &encoderClsid, NULL);

		delete brush;
		delete tBitmap;

	}

	void IrisBitmap::IrisDrawText(const IrisRect *rect, const wstring str, const int align, IR_PARAM_RESULT_CT){
		IrisDrawText((int)rect->x, (int)rect->y, (int)rect->width, (int)rect->height, str, align, IR_PARAM);
	}

	void IrisBitmap::Draw(const IrisRect* Rect, IR_PARAM_RESULT_CT){
		bool flag = false;
		if (this->needRefreshTexture == true){
			flag = true;
		}

		if (this->limitRect->x != Rect->x || this->limitRect->y != Rect->y
			|| this->limitRect->width != Rect->width || this->limitRect->height != Rect->height){
			//delete this->limitRect;
			//this->limitRect = new IrisRect(*Rect);
			this->needRefreshTexture = true;
			flag = true;
		}

		if (!this->vb){
			flag = true;
			this->needRefreshTexture = true;
		}

		if (flag)
			if (!this->MakeTexture(Rect)){
				IR_PARAM_SET_RESULT(IR_RFAILED, L"Error in Making Texture !")
				return;
			}

		IR_PARAM_SET_RESULT(IR_RSUCCESS, L"")
	}

	void IrisBitmap::OnRelease() {
		list<IrisBitmap*>::iterator it;
		for (it = bitmapList.begin(); it != bitmapList.end(); ++it) {
			if ((*it)->vb){
				(*it)->recoverFlag = true;
				(*it)->vb->Release();
				(*it)->vb = NULL;
				(*it)->texture->Release();
				(*it)->texture = NULL;
			}
		}
	}

	void IrisBitmap::OnRecover() {
		list<IrisBitmap*>::iterator it;
		for (it = bitmapList.begin(); it != bitmapList.end(); ++it) {
			if ((*it)->recoverFlag) {
				(*it)->needRefreshTexture = true;
				(*it)->Draw((*it)->limitRect);
			}
		}
	}

	void IrisBitmap::ReleaseBitmaps() {
		list<IrisBitmap*>::iterator itbmp;
		for (itbmp = bitmapList.begin(); itbmp != bitmapList.end(); ++itbmp) {
			delete *itbmp;
		}
	}

	IrisBitmap::~IrisBitmap(void)
	{
		if (!this->Disposed())
			this->Dispose();
	}
}