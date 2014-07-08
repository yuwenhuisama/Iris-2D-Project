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

#include "Iris2D.h"
//#include "CppDsToRubyMacro.h"


class IrisViewport;
class IrisTone;
class IrisBitmap;
class IrisColor;
class IrisRect;

class IrisSprite
{
private:
	IDirect3DDevice9 *Device;
	IrisViewport *viewport;
	int opacity;
	float z;

	IrisColor *color;
	IrisTone *tone;
	IrisRect* srcRect;
	IrisBitmap *bitmap;

	bool isFlash;
	IrisColor* flashColor;
	int flashDuration;
	int realFlashDuration;

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

	//IrisSprite();
	//IrisSprite(IDirect3DDevice9 *Device);
	IrisSprite(IrisViewport *viewport = NULL);

	void SetViewport(IrisViewport *tviewport);
	IrisViewport* GetViewport();

	IrisColor* GetColor();
	void SetColor(IrisColor* color);

	IrisTone* GetTone();
	void SetTone(IrisTone* tone);

	IrisRect* GetSrcRect();
	void SetSrcRect(IrisRect* srcRect);

	IrisBitmap* GetBitmap();
	void SetBitmap(IrisBitmap* bitmap);

    void Dispose();
	bool Disposed();

	void AutoDispose();
	void AutoSetViewport(IrisViewport *tviewport);

	void Flash(IrisColor *color, int duration);

	void Update();

	void Draw();

	int GetWidth();

	int GetHeight();

	void SetOpacity(int tOpacity);
	int GetOpacity();

	void SetZ(float tZ);
	float GetZ();

	void SetDevice(IDirect3DDevice9 *Device);

	~IrisSprite(void);

	//DECLAR_FRIEND_CLASS(IrisSprite)
	friend class IrisSpriteToRuby;
};

#ifdef MINGW_WITH_RUBY
DEFINE_CONVER_CLASS_BEGIN(IrisSprite)
    // 分配函数
    DEFINE_RUBY_CLASS_ALLOC_FUNC(IrisSprite)

    // 映射方法
	DEFINE_CONVER_METHOD(initialize)(VALUE self, VALUE viewport = Qnil){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		// Get Viewport
		if(viewport != Qnil) {
			IrisViewport* irvp;
			Data_Get_Struct(viewport, IrisViewport, irvp);
			tc->SetViewport(irvp);
		}

		return self;
	}

	DEFINE_CONVER_METHOD(dispose)(VALUE self){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		tc->Dispose();
		return Qnil;
	}

	DEFINE_CONVER_METHOD(disposed)(VALUE self){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		if(tc->Disposed())
			return Qtrue;
		else
			return Qfalse;
	}

	DEFINE_CONVER_METHOD(flash)(VALUE self, VALUE color, VALUE duration){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		// Get Color
		IrisColor* ircl;
		Data_Get_Struct(ircl, IrisColor, ircl);
		tc->Flash(ircl, NUM2INT(duration));

		return Qnil;
	}

	DEFINE_CONVER_METHOD(update)(VALUE self){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		tc->Update();
		return Qnil;
	}

	DEFINE_CONVER_METHOD(width)(VALUE self){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		return (INT2NUM(tc->GetWidth()));
	}

	DEFINE_CONVER_METHOD(height)(VALUE self){
		// Get Sprite
		IrisSprite* tc;
		Data_Get_Struct(self, IrisSprite, tc);

		return (INT2NUM(tc->GetHeight()));
	}

	MACRO_VARIABLE_GETTER(bitmap)
	MACRO_VARIABLE_SETTER_WITH_OBJ(bitmap, IrisSprite, IrisBitmap, cppobj->bitmap = robj)
	MACRO_VARIABLE_GETTER(viewport)
	MACRO_VARIABLE_SETTER_WITH_OBJ(viewport, IrisSprite, IrisViewport, cppobj->SetViewport(robj))
	MACRO_VARIABLE_GETTER(x);
	MACRO_VARIABLE_SETTER_WITH_QV(x, IrisSprite, cppobj->x = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(y);
	MACRO_VARIABLE_SETTER_WITH_QV(y, IrisSprite, cppobj->y = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(z);
	MACRO_VARIABLE_SETTER_WITH_QV(z, IrisSprite, cppobj->z = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(ox);
	MACRO_VARIABLE_SETTER_WITH_QV(ox, IrisSprite, cppobj->ox = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(oy);
	MACRO_VARIABLE_SETTER_WITH_QV(oy, IrisSprite, cppobj->oy = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(zoom_x);
	MACRO_VARIABLE_SETTER_WITH_QV(zoom_x, IrisSprite, cppobj->zoomY = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(zoom_y);
	MACRO_VARIABLE_SETTER_WITH_QV(zoom_y, IrisSprite, cppobj->zoomX = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(angle);
	MACRO_VARIABLE_SETTER_WITH_QV(angle, IrisSprite, cppobj->angle = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(wave_amp)
	MACRO_VARIABLE_SETTER_WITH_QV(wave_amp, IrisSprite, cppobj->waveAmp = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(wave_length)
	MACRO_VARIABLE_SETTER_WITH_QV(wave_length, IrisSprite, cppobj->waveLength = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(wave_speed)
	MACRO_VARIABLE_SETTER_WITH_QV(wave_speed, IrisSprite, cppobj->waveSpeed = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(wave_phase)
	MACRO_VARIABLE_SETTER_WITH_QV(wave_phase, IrisSprite, cppobj->wavePhase = (float)NUM2DBL(v));
	MACRO_VARIABLE_GETTER(mirror)
	MACRO_VARIABLE_SETTER_WITH_QV(mirror, IrisSprite, cppobj->mirror = (v == Qtrue ? true : false));
	MACRO_VARIABLE_GETTER(bush_depth)
	MACRO_VARIABLE_SETTER_WITH_QV(bush_depth, IrisSprite, cppobj->bushDepth = NUM2INT(v));
	MACRO_VARIABLE_GETTER(bush_opacity)
	MACRO_VARIABLE_SETTER_WITH_QV(bush_opacity, IrisSprite, cppobj->bushOpacity = NUM2INT(v));
	MACRO_VARIABLE_GETTER(opacity)
	MACRO_VARIABLE_SETTER_WITH_QV(opacity, IrisSprite, cppobj->SetOpacity(NUM2INT(v)));
	MACRO_VARIABLE_GETTER(blend_type)
	MACRO_VARIABLE_SETTER_WITH_QV(blend_type, IrisSprite, cppobj->blendType = NUM2INT(v));
	MACRO_VARIABLE_GETTER(color)
	MACRO_VARIABLE_SETTER_WITH_OBJ(color, IrisSprite, IrisColor, cppobj->color = robj)
	MACRO_VARIABLE_GETTER(tone)
	MACRO_VARIABLE_SETTER_WITH_OBJ(tone, IrisSprite, IrisTone, cppobj->tone = robj)

    // 开始实现类
    REALIZE_RUBY_CLASS_BEGIN(IrisSprite)
    REALIZE_RUBY_CLASS(IrisSprite)
    REALIZE_RUBY_ALLOC_FUNC(IrisSprite)

    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, bitmap)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, viewport)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, x)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, y)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, z)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, ox)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, oy)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, zoom_x)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, zoom_y)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, angle)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, wave_amp)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, wave_length)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, wave_speed)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, wave_phase)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, mirror)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, bush_depth)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, bush_opacity)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, blend_type)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, color)
    REALIZE_RUBY_VARIABLE_GETTER_SETTER(IrisSprite, tone)

    REALIZE_RUBY_METHOD_FUNC(IrisSprite, initialize, 0)
    REALIZE_RUBY_METHOD_FUNC(IrisSprite, dispose, 0)
    REALIZE_RUBY_METHOD_FUNC_WITH_SINGBOL(IrisSprite, dispose, ?, 0)
    REALIZE_RUBY_METHOD_FUNC(IrisSprite, flash, 2)
    REALIZE_RUBY_METHOD_FUNC(IrisSprite, update, 0)
    REALIZE_RUBY_METHOD_FUNC(IrisSprite, width, 0)
    REALIZE_RUBY_METHOD_FUNC(IrisSprite, height, 0)
    REALIZE_RUBY_CLASS_END
    // 结束实现类
DEFINE_CONVER_CLASS_END
#endif // MINGW_WITH_RUBY
#endif
