// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 IRIS2DLIBRARY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// IRIS2DLIBRARY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#pragma once

#ifdef IRIS2DLIBRARY_EXPORTS
#define IRIS2DLIBRARY_API __declspec(dllexport)
#else
#define IRIS2DLIBRARY_API __declspec(dllimport)
#endif

#define CPP_GETTER_DECLARE(pn, dtp) virtual dtp Get##pn() = 0;
#define CPP_SETTER_DECLARE(pn, dtp) virtual void Set##pn(dtp) = 0;
#define CPP_GETTER_SETTER_DECLARE(pn, dtp) \
	CPP_GETTER_DECLARE(pn, dtp) \
	CPP_SETTER_DECLARE(pn, dtp)

#include <string>
using namespace std;

class IIrisApp;
class IIrisFont;
class IIrisColor;
class IIrisRect;
class IIrisViewport;
class IIrisBitmap;
class IIrisTone;

enum MouseKey{
	Left = 0,
	Right,
};

class IIrisApp{
public:
	virtual bool Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title) = 0;
	virtual void Run() = 0;
	virtual void Release() = 0;
	virtual bool IsRunning() = 0;
	virtual bool IsQuited() = 0;
	virtual float GetTimeDelta() = 0;
#ifdef _MSC_VER
	virtual ~IIrisApp() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisApp() = 0;
#endif
};

class IIrisBitmap{
public:
	virtual void Dispose() = 0;
	virtual bool Disposed() = 0;
	virtual bool Blt(int x, int y, const IIrisBitmap *srcIrisBitmap, const IIrisRect *rect, int opactiy) = 0;
	virtual bool StretchBlt(const IIrisRect *destIrisRect, const IIrisBitmap *srcIrisBitmap, const IIrisRect *srcIrisRect, int opacity) = 0;
	virtual void FillRect(int x, int y, int width, int height, const IIrisColor *color) = 0;
	virtual void FillRect(const IIrisRect *rect, const IIrisColor *color) = 0;
	virtual void GradientFillRect(int x, int y, int width, int height, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false) = 0;
	virtual void GradientFillRect(const IIrisRect *rect, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false) = 0;
	virtual void Clear() = 0;
	virtual void ClearRect(int x, int y, int width, int height) = 0;
	virtual void ClearRect(IIrisRect* rect) = 0;
	virtual IIrisColor* GetPixel(int x, int y) = 0;
	virtual void SetPixel(int x, int y, const IIrisColor *color) = 0;
	virtual void hueChange(float hue) = 0;
	virtual void blur() = 0;
	virtual void RadialBlur(float angle, int division) = 0;
	virtual int TextSize(const IIrisFont* fontIris, wstring str) = 0;
	virtual void IrisDrawText(const IIrisFont* fontIris, int x, int y, int width, int height, wstring str, int align) = 0;
	virtual void IrisDrawText(const IIrisFont* fontIris, const IIrisRect *rect, wstring str, int align) = 0;
	virtual void SaveToFile(wstring fileName) = 0;
	virtual void SetInitData(wstring fileName) = 0;		 // Initialize Interface for Ruby...
	virtual void SetInitData(int width, int height) = 0; // Initialize Interface for Ruby...
	CPP_GETTER_DECLARE(Width, int)
	CPP_GETTER_DECLARE(Height, int)
	CPP_GETTER_SETTER_DECLARE(Font, IIrisFont*)
#ifdef _MSC_VER
	virtual ~IIrisBitmap() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisBitmap() = 0;
#endif
};

class IIrisColor{
public:
	virtual void SetInitData(int red, int green, int blue, int alpha) = 0;
	virtual void set(int red, int green, int blue) = 0;
	virtual void set(int red, int green, int blue, int alpha) = 0;
	CPP_GETTER_SETTER_DECLARE(Red, int);
	CPP_GETTER_SETTER_DECLARE(Green, int);
	CPP_GETTER_SETTER_DECLARE(Blue, int);
	CPP_GETTER_SETTER_DECLARE(Alpha, int);
#ifdef _MSC_VER
	virtual ~IIrisColor() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisColor() = 0;
#endif
};

class IIrisFont
{
public:
	virtual void SetInitData(wstring name, int size) = 0;
	CPP_GETTER_SETTER_DECLARE(Name, wstring)
	CPP_GETTER_SETTER_DECLARE(Size, int)
	CPP_GETTER_SETTER_DECLARE(Bold, bool)
	CPP_GETTER_SETTER_DECLARE(Italic, bool)
	CPP_GETTER_SETTER_DECLARE(Shadow, bool)
	CPP_GETTER_SETTER_DECLARE(Color, IIrisColor*)
#ifdef _MSC_VER
	virtual ~IIrisFont() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisFont() = 0;
#endif
};

class IIrisPlane{
public:
	virtual void SetInitData(IIrisViewport* viewport) = 0;
	CPP_GETTER_SETTER_DECLARE(Bitmap, IIrisBitmap*)
	CPP_GETTER_SETTER_DECLARE(Viewport, IIrisViewport*)
	CPP_GETTER_SETTER_DECLARE(Visible, bool)
	CPP_GETTER_SETTER_DECLARE(Z, float)
	CPP_GETTER_SETTER_DECLARE(Ox, float)
	CPP_GETTER_SETTER_DECLARE(Oy, float)
	CPP_GETTER_SETTER_DECLARE(ZoomX, float)
	CPP_GETTER_SETTER_DECLARE(ZoomY, float)
	CPP_GETTER_SETTER_DECLARE(Opacity, int)
	CPP_GETTER_SETTER_DECLARE(BlendType, int)
	CPP_GETTER_SETTER_DECLARE(Color, IIrisColor*)
	CPP_GETTER_SETTER_DECLARE(Tone, IIrisTone*)
	virtual bool Disposed() = 0;
	virtual void Dispose() = 0;
#ifdef _MSC_VER
	virtual ~IIrisPlane() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisPlane() = 0;
#endif
};

class IIrisRect {
public:
	CPP_GETTER_SETTER_DECLARE(X, float)
	CPP_GETTER_SETTER_DECLARE(Y, float)
	CPP_GETTER_SETTER_DECLARE(Height, float)
	CPP_GETTER_SETTER_DECLARE(Width, float)
	virtual void Set(float x, float y, float width, float height) = 0;
	virtual void SetInitData(float x, float y, float width, float height) = 0;
#ifdef _MSC_VER
	virtual ~IIrisRect() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisRect() = 0;
#endif
};

class IIrisSprite {
public:
	CPP_GETTER_SETTER_DECLARE(Bitmap, IIrisBitmap*)
	CPP_GETTER_SETTER_DECLARE(Visible, bool)
	CPP_GETTER_SETTER_DECLARE(X, float)
	CPP_GETTER_SETTER_DECLARE(Y, float)
	CPP_GETTER_SETTER_DECLARE(Z, float)
	CPP_GETTER_SETTER_DECLARE(Ox, float)
	CPP_GETTER_SETTER_DECLARE(Oy, float)
	CPP_GETTER_SETTER_DECLARE(ZoomX, float)
	CPP_GETTER_SETTER_DECLARE(ZoomY, float)
	CPP_GETTER_SETTER_DECLARE(Angle, float)
	CPP_GETTER_SETTER_DECLARE(WaveAmp, float)
	CPP_GETTER_SETTER_DECLARE(WaveLength, float)
	CPP_GETTER_SETTER_DECLARE(WaveSpeed, float)
	CPP_GETTER_SETTER_DECLARE(WavePhase, float)
	CPP_GETTER_SETTER_DECLARE(BushDepth, int)
	CPP_GETTER_SETTER_DECLARE(BushOpacity, int)
	CPP_GETTER_SETTER_DECLARE(BlendType, int)
	CPP_GETTER_SETTER_DECLARE(Color, IIrisColor*)
	CPP_GETTER_SETTER_DECLARE(Tone, IIrisTone*)
	CPP_GETTER_SETTER_DECLARE(SrcRect, IIrisRect*)
	virtual void SetViewport(IIrisViewport *tviewport) = 0;
	virtual IIrisViewport* GetViewport() = 0;
	virtual void Dispose() = 0;
	virtual bool Disposed() = 0;
	virtual void Flash(const IIrisColor *color, int duration) = 0;
	virtual void Update() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void SetOpacity(int tOpacity) = 0;
	virtual int GetOpacity() = 0;
	virtual void SetInitData(IIrisViewport *viewport = NULL) = 0;
#ifdef _MSC_VER
	virtual ~IIrisSprite() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisSprite() = 0;
#endif
};

class IIrisTilemap{
public:
#ifdef _MSC_VER
	virtual ~IIrisTilemap() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisTilemap() = 0;
#endif
};

class IIrisTone{
public:
	virtual void set(int red, int green, int blue) = 0;
	virtual void set(int red, int green, int blue, int alpha) = 0;
	virtual void SetInitData(int red, int green, int blue, int alpha) = 0;
	CPP_GETTER_SETTER_DECLARE(Red, int)
	CPP_GETTER_SETTER_DECLARE(Green, int)
	CPP_GETTER_SETTER_DECLARE(Blue, int)
	CPP_GETTER_SETTER_DECLARE(Alpha, int)
#ifdef _MSC_VER
	virtual ~IIrisTone() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisTone() = 0;
#endif
};

class IIrisViewport {
public:
	virtual void Dispose() = 0;
	virtual bool Disposed() = 0;
	virtual void Flash(const IIrisColor *color, int duration) = 0;
	virtual void Update() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual UINT GetWidth() = 0;
	virtual UINT GetHeight() = 0;
	virtual void SetInitData(float x, float y, float width, float height) = 0;
	virtual void SetInitData(const IIrisRect *rect) = 0;
	CPP_GETTER_SETTER_DECLARE(Rect, IIrisRect*)
	CPP_GETTER_SETTER_DECLARE(Visible, bool)
	CPP_GETTER_SETTER_DECLARE(Z, float)
	CPP_GETTER_SETTER_DECLARE(Ox, float)
	CPP_GETTER_SETTER_DECLARE(Oy, float)
	CPP_GETTER_SETTER_DECLARE(Tone, IIrisTone*)
	CPP_GETTER_SETTER_DECLARE(Color, IIrisColor*)
#ifdef _MSC_VER
	virtual ~IIrisViewport() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisViewport() = 0;
#endif
};

class IIrisWindow {
public:
#ifdef _MSC_VER
	virtual ~IIrisWindow() = 0 {};
#endif
#ifdef __GNUC__
	virtual ~IIrisWindow() = 0;
#endif
};

// Iris Object
IRIS2DLIBRARY_API IIrisApp* GetIrisApp();
IRIS2DLIBRARY_API void ReleaseIrisApp(IIrisApp* app);
IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(wstring fileName);
IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(int width, int height);
IRIS2DLIBRARY_API IIrisBitmap* GetTravialIIrisBitmap();
IRIS2DLIBRARY_API void ReleaseIrisBitmap(IIrisBitmap* bmp);
IRIS2DLIBRARY_API IIrisColor* GetIrisColor(int red, int green, int blue, int alpha);
IRIS2DLIBRARY_API IIrisColor* GetTravialIIrisColor();
IRIS2DLIBRARY_API void ReleaseIrisColor(IIrisColor* color);
IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name);
IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name, int size);
IRIS2DLIBRARY_API IIrisFont* GetTravialIIrisFont();
IRIS2DLIBRARY_API void ReleaseIrisFont(IIrisFont* font);
IRIS2DLIBRARY_API IIrisSprite* GetIrisSprite(IIrisViewport *viewport);
IRIS2DLIBRARY_API IIrisSprite* GetIrisSprite();
IRIS2DLIBRARY_API IIrisSprite* GetTravialIIrisSprite();
IRIS2DLIBRARY_API void ReleaseIrisSprite(IIrisSprite* sp);
IRIS2DLIBRARY_API IIrisRect* GetIrisRect(float x, float y, float width, float height);
IRIS2DLIBRARY_API IIrisRect* GetTravialIIrisRect();
IRIS2DLIBRARY_API void ReleaseIrisRect(IIrisRect *sp);
IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(float x, float y, float width, float height);
IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(const IIrisRect *rect);
IRIS2DLIBRARY_API IIrisViewport* GetTravialIIrisViewport();
IRIS2DLIBRARY_API void ReleaseIrisViewport(IIrisViewport *vp);
IRIS2DLIBRARY_API IIrisTone* GetIrisTone(int r, int g, int b, int a);
IRIS2DLIBRARY_API IIrisTone* GetTravialIIrisTone();
IRIS2DLIBRARY_API void ReleaseIrisTone(IIrisTone* tn);

// Module Function
IRIS2DLIBRARY_API bool IrisFontExisted(wstring name);
IRIS2DLIBRARY_API wstring IrisFontGetDefaultName();
IRIS2DLIBRARY_API int IrisFontGetDefaultSize();
IRIS2DLIBRARY_API bool IrisFontGetDefaultBold();
IRIS2DLIBRARY_API bool IrisFontGetDefaultItalic();
IRIS2DLIBRARY_API bool IrisFontGetDefaultShadow();
IRIS2DLIBRARY_API IIrisColor* IrisFontGetDefaultColor();
IRIS2DLIBRARY_API void IrisFontSetDefaultName(wstring name);
IRIS2DLIBRARY_API void IrisFontSetDefaultSize(int size);
IRIS2DLIBRARY_API void IrisFontSetDefaultBold(bool bold);
IRIS2DLIBRARY_API void IrisFontSetDefaultItalic(bool italic);
IRIS2DLIBRARY_API void IrisFontSetDefaultShadow(bool italic);
IRIS2DLIBRARY_API void IrisFontSetDefaultColor(IIrisColor* color);
IRIS2DLIBRARY_API HWND IrisGraphicsGetHwnd();
IRIS2DLIBRARY_API int IrisGraphicsGetWidth();
IRIS2DLIBRARY_API int IrisGraphicsGetHeight();
IRIS2DLIBRARY_API void IrisGraphicsUpdate();
IRIS2DLIBRARY_API void IrisGraphicsWait(int duration);
IRIS2DLIBRARY_API void IrisGraphicsFadeOut(int duration);
IRIS2DLIBRARY_API void IrisGraphicsFadeIn(int duration);
IRIS2DLIBRARY_API void IrisGraphicsFreeze();
IRIS2DLIBRARY_API void IrisGraphicsTransition(int duration, wstring filename, int vague);
IRIS2DLIBRARY_API void IrisGraphicsSnap2Bitmap(IIrisBitmap* bitmap);
IRIS2DLIBRARY_API void IrisGraphicsFrameReset();
IRIS2DLIBRARY_API void IrisGraphicsResizeScreen(int width, int height);
IRIS2DLIBRARY_API float IrisGraphicsGetFrameRate();
IRIS2DLIBRARY_API void IrisGraphicsSetFrameRate(int fr);
IRIS2DLIBRARY_API unsigned long IrisGraphicsGetFrameCount();
IRIS2DLIBRARY_API void IrisGraphicsSetFrameCount(int ct);
IRIS2DLIBRARY_API int IrisGraphicsGetBrightness();
IRIS2DLIBRARY_API void IrisGraphicsSetBrightness(int bn);
IRIS2DLIBRARY_API void IrisInputUpdate();
IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyPress(DWORD key);
IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyTrigger(DWORD key);
IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyRepeat(DWORD key);
IRIS2DLIBRARY_API bool IrisInputMousePress(MouseKey botton);
IRIS2DLIBRARY_API bool IrisInputMouseTrigger(MouseKey botton);
IRIS2DLIBRARY_API bool IrisInputMouseRepeat(MouseKey botton);
IRIS2DLIBRARY_API long IrisInputMouseMiddleRoll();
IRIS2DLIBRARY_API long IrisInputMouseXMove();
IRIS2DLIBRARY_API long IrisInputMouseYMove();
IRIS2DLIBRARY_API int IrisInputGetCursorX();
IRIS2DLIBRARY_API int IrisInputGetCursorY();
IRIS2DLIBRARY_API bool IrisInputCursorInRect(IIrisRect* rect);
IRIS2DLIBRARY_API bool IrisAudioBgmPlay(wstring filePath, int volume, int rate);
IRIS2DLIBRARY_API bool IrisAudioBgmFade(int fadeTime);
IRIS2DLIBRARY_API bool IrisAudioBgmStop();
IRIS2DLIBRARY_API bool IrisAudioBgsPlay(wstring filePath, int volume, int rate);
IRIS2DLIBRARY_API bool IrisAudioBgsFade(int fadeTime);
IRIS2DLIBRARY_API bool IrisAudioBgsStop();
IRIS2DLIBRARY_API bool IrisAudioSePlay(wstring filePath, int volume, int rate);
IRIS2DLIBRARY_API bool IrisAudioSeFade(int fadeTime);
IRIS2DLIBRARY_API bool IrisAudioSeStop();
IRIS2DLIBRARY_API bool IrisAudioMePlay(wstring filePath, int volume, int rate);
IRIS2DLIBRARY_API bool IrisAudioMeStop();
