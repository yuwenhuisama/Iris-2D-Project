// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 IRIS2DBISCUITONIONAPI_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// IRIS2DBISCUITONIONAPI_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#ifdef IRIS2DLIBRARY_EXPORTS
#define IRIS2DLIBRARY_API __declspec(dllexport)
#else
#define IRIS2DLIBRARY_API __declspec(dllimport)
#endif

#ifndef _H_IRIS2DLIBRARY_
#define _H_IRIS2DLIBRARY_

#define IRIS2D_VERSION 0x02061301

#define CPP_GETTER_DECLARE(pn, dtp) virtual dtp Get##pn() = 0;
#define CPP_SETTER_DECLARE(pn, dtp) virtual void Set##pn(dtp) = 0;
#define CPP_GETTER_SETTER_DECLARE(pn, dtp) \
	CPP_GETTER_DECLARE(pn, dtp) \
	CPP_SETTER_DECLARE(pn, dtp)

#define IR_SUCCESS(r) ((r).resultType == IR_RSUCCESS)
#define IR_FAILD(r) ((r).resultType != IR_RSUCCESS)
#define IR_MEM_ERROR(r) ((r).resultType == IR_RMEM_ERROR)
#define IR_SHOW_ERROR(r) ::MessageBox(NULL, L"Error!", (r).resultMsg, NULL);

#define IR_PARAM _rParam
#define IR_PARAM_RESULT IrisResult* IR_PARAM = NULL
#define IR_PARAM_RESULT_CT IrisResult* IR_PARAM
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->resultType = res; \
			_rParam->resultMsg = msg; \
						} \
			} while (0); \

#define BEGIN_IRIS_SAFE_WHILE_WITH_CONDITION(condition) \
				while (GetIrisApp()->IsRunning() && condition) {

#define END_IRIS_SAFE_WHILE_WITH_CONDITION() }

#define BEGIN_IRIS_SAFE_WHILE() \
				while (GetIrisApp()->IsRunning()) {

#define END_IRIS_SAFE_WHILE() }

#define BEGIN_SPRITE_BATCH_PROCESS(viewport) IrisViewportBeginBatchSpriteProcess(viewport)
#define END_SPRITE_BATCH_PROCESS(viewport) IrisViewportEndBatchSpriteProcess(viewport)

#include <Windows.h>
#include <string>
using namespace std;

namespace Iris2D {
	class IIrisApp;
	class IIrisFont;
	class IIrisColor;
	class IIrisRect;
	class IIrisViewport;
	class IIrisBitmap;
	class IIrisTone;

	enum IR_RESULT{
		IR_RSUCCESS = 0,
		IR_RFAILED,
		IR_RMEM_ERROR,
	};

	struct IrisResult {
	public:
		IR_RESULT resultType;
		wstring resultMsg;

		IrisResult(){
			resultType = IR_RSUCCESS;
			resultMsg = L"";
		}
	};

	enum MouseKey{
		Left = 0,
		Right,
		Middle,
		Reserve1,
		Reserve2,
		Reserve3,
		Reserve4,
		Reserve5,
	};

	class IIrisApp{
	public:
		virtual bool Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title, IR_PARAM_RESULT) = 0;
		virtual void Run(IR_PARAM_RESULT) = 0;
		virtual void Release(IR_PARAM_RESULT) = 0;
		virtual bool IsRunning() = 0;
		virtual bool IsQuited() = 0;
		virtual float GetTimeDelta() = 0;
		virtual void ToggleWindowMode() = 0;
#ifdef _MSC_VER
		virtual ~IIrisApp() = 0 {};
#endif
#ifdef __GNUC__
		virtual ~IIrisApp() = 0;
#endif
};

	class IIrisEncripedResourceManager
	{
	public:
		typedef void(*SafetyFunc)(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2);
		virtual void AddGraphResource(wstring strPackagePath, SafetyFunc pfFunc = NULL) = 0;
		virtual void AddGeneralResource(wstring strPackagePath, SafetyFunc pfFunc = NULL) = 0;
		virtual bool GetBitmapData(wstring wstrFilePath, char** ppData, int* nWidth, int* nHeight) = 0;
		virtual bool GetGeneralData(wstring wstrFilePath, char** ppData, int* nSize) = 0;
		virtual bool HaveGeneralSource(wstring wstrFilePath) = 0;
		virtual bool HaveSource(wstring wstrFilePath) = 0;
#ifdef _MSC_VER
		virtual ~IIrisEncripedResourceManager() = 0 {}
#endif
#ifdef __GNUC__
		virtual ~IIrisEncripedResourceManager() = 0;
#endif
	};

	class IIrisBitmap{
	public:
		virtual void Dispose(IR_PARAM_RESULT) = 0;
		virtual bool Disposed(IR_PARAM_RESULT) = 0;
		virtual bool Blt(int x, int y, const IIrisBitmap *srcIrisBitmap, const IIrisRect *rect, int opactiy, IR_PARAM_RESULT) = 0;
		virtual bool StretchBlt(const IIrisRect *destIrisRect, const IIrisBitmap *srcIrisBitmap, const IIrisRect *srcIrisRect, int opacity, IR_PARAM_RESULT) = 0;
		virtual void FillRect(int x, int y, int width, int height, const IIrisColor *color, IR_PARAM_RESULT) = 0;
		virtual void FillRect(const IIrisRect *rect, const IIrisColor *color, IR_PARAM_RESULT) = 0;
		virtual void GradientFillRect(int x, int y, int width, int height, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false, IR_PARAM_RESULT) = 0;
		virtual void GradientFillRect(const IIrisRect *rect, const IIrisColor *color1, const IIrisColor *color2, bool vertical = false, IR_PARAM_RESULT) = 0;
		virtual void Clear(IR_PARAM_RESULT) = 0;
		virtual void ClearRect(int x, int y, int width, int height, IR_PARAM_RESULT) = 0;
		virtual void ClearRect(const IIrisRect* rect, IR_PARAM_RESULT) = 0;
		virtual IIrisColor* GetPixel(int x, int y, IR_PARAM_RESULT) = 0;
		virtual void SetPixel(int x, int y, const IIrisColor *color, IR_PARAM_RESULT) = 0;
		virtual void HueChange(float hue, IR_PARAM_RESULT) = 0;
		virtual void Blur(IR_PARAM_RESULT) = 0;
		virtual void RadialBlur(float angle, int division, IR_PARAM_RESULT) = 0;
		virtual int TextSize(const IIrisFont* fontIris, wstring str, IR_PARAM_RESULT) = 0;
		virtual void IrisDrawText(int x, int y, int width, int height, wstring str, int align, IR_PARAM_RESULT) = 0;
		virtual void IrisDrawText(const IIrisRect *rect, wstring str, int align, IR_PARAM_RESULT) = 0;
		virtual void SaveToFile(wstring fileName, IR_PARAM_RESULT) = 0;
		virtual void SetInitData(wstring fileName, IR_PARAM_RESULT) = 0;		 // Initialize Interface for Ruby...
		virtual void SetInitData(int width, int height, IR_PARAM_RESULT) = 0; // Initialize Interface for Ruby...
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
		virtual void Set(int red, int green, int blue, int alpha) = 0;
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
		//CPP_GETTER_SETTER_DECLARE(Color, IIrisColor*)
		virtual IIrisColor* GetColor() = 0;
		virtual void SetColor(IIrisColor* color, bool isReleased = true) = 0;
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
		virtual IIrisBitmap* GetBitmap() = 0;
		virtual void SetBitmap(IIrisBitmap* bitmap, bool isRelease = true) = 0;
		virtual IIrisColor* GetColor() = 0;
		virtual void SetColor(IIrisColor* color, bool isRelease = true) = 0;
		virtual IIrisTone* GetTone() = 0;
		virtual void SetTone(IIrisTone* tone, bool isRelease = true) = 0;
		virtual IIrisRect* GetSrcRect() = 0;
		virtual void SetSrcRect(IIrisRect* rect, bool isRelease = true) = 0;
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
		virtual void SetViewport(IIrisViewport *tviewport) = 0;
		virtual IIrisViewport* GetViewport() = 0;
		virtual void Dispose(IR_PARAM_RESULT) = 0;
		virtual bool Disposed(IR_PARAM_RESULT) = 0;
		virtual void Flash(const IIrisColor *color, int duration) = 0;
		virtual void Update(IR_PARAM_RESULT) = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual void SetOpacity(int tOpacity) = 0;
		virtual int GetOpacity() = 0;
		virtual void SetInitData(IIrisViewport *viewport = NULL, IR_PARAM_RESULT) = 0;
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
		virtual void Dispose(IR_PARAM_RESULT) = 0;
		virtual bool Disposed(IR_PARAM_RESULT) = 0;
		virtual void Flash(const IIrisColor *color, int duration) = 0;
		virtual void Update() = 0;
		virtual float GetX() = 0;
		virtual float GetY() = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual void SetInitData(float x, float y, float width, float height, IR_PARAM_RESULT) = 0;
		virtual void SetInitData(const IIrisRect *rect, IR_PARAM_RESULT) = 0;
		virtual void SetSrcRect(IIrisRect* rect, bool isRelease = true) = 0;
		virtual IIrisRect* GetSrcRect() = 0;
		virtual void SetTone(IIrisTone* rect, bool isRelease = true) = 0;
		virtual IIrisTone* GetTone() = 0;
		virtual void SetColor(IIrisColor* rect, bool isRelease = true) = 0;
		virtual IIrisColor* GetColor() = 0;
		CPP_GETTER_SETTER_DECLARE(Visible, bool)
		CPP_GETTER_SETTER_DECLARE(Z, float)
		CPP_GETTER_SETTER_DECLARE(Ox, float)
		CPP_GETTER_SETTER_DECLARE(Oy, float)
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
	IRIS2DLIBRARY_API IIrisEncripedResourceManager* GetIrisEncripedResourceManager();
	IRIS2DLIBRARY_API void ReleaseIrisEncripedResourceManager(IIrisEncripedResourceManager* manager);
	IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(wstring fileName, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(int width, int height, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(char* bmpData, int width, int height, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisBitmap* GetTravialIIrisBitmap(IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void ReleaseIrisBitmap(IIrisBitmap* bmp);
	IRIS2DLIBRARY_API IIrisColor* GetIrisColor(int red, int green, int blue, int alpha);
	IRIS2DLIBRARY_API IIrisColor* GetTravialIIrisColor();
	IRIS2DLIBRARY_API void ReleaseIrisColor(IIrisColor* color);
	IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name);
	IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name, int size);
	IRIS2DLIBRARY_API IIrisFont* GetTravialIIrisFont();
	IRIS2DLIBRARY_API void ReleaseIrisFont(IIrisFont* font);
	IRIS2DLIBRARY_API IIrisSprite* GetIrisSprite(IIrisViewport *viewport = NULL, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisSprite* GetTravialIIrisSprite();
	IRIS2DLIBRARY_API void ReleaseIrisSprite(IIrisSprite* sp);
	IRIS2DLIBRARY_API IIrisRect* GetIrisRect(float x, float y, float width, float height);
	IRIS2DLIBRARY_API IIrisRect* GetTravialIIrisRect();
	IRIS2DLIBRARY_API void ReleaseIrisRect(IIrisRect *sp);
	IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(float x, float y, float width, float height, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(const IIrisRect *rect, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API IIrisViewport* GetTravialIIrisViewport(IR_PARAM_RESULT);
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

	IRIS2DLIBRARY_API void IrisViewportBeginBatchSpriteProcess();
	IRIS2DLIBRARY_API void IrisViewportEndBatchSpriteProcess();

	IRIS2DLIBRARY_API HWND IrisGraphicsGetHwnd();
	IRIS2DLIBRARY_API int IrisGraphicsGetWidth();
	IRIS2DLIBRARY_API int IrisGraphicsGetHeight();
	IRIS2DLIBRARY_API void IrisGraphicsUpdate(IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsWait(int duration, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsFadeOut(int duration, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsFadeIn(int duration, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsFreeze(IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsTransition(int duration, wstring filename, int vague, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsSnap2Bitmap(IIrisBitmap* bitmap, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API void IrisGraphicsFrameReset();
	IRIS2DLIBRARY_API void IrisGraphicsResizeScreen(int width, int height, IR_PARAM_RESULT);
	IRIS2DLIBRARY_API float IrisGraphicsGetFrameRate();
	IRIS2DLIBRARY_API unsigned long IrisGraphicsGetFrameCount();
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

};

/*********** KeyBoard Virtual Key Code Of Iris 2D *************/

#define IR_DIK_ESCAPE		   0x01
#define IR_DIK_1               0x02
#define IR_DIK_2               0x03
#define IR_DIK_3               0x04
#define IR_DIK_4               0x05
#define IR_DIK_5               0x06
#define IR_DIK_6               0x07
#define IR_DIK_7               0x08
#define IR_DIK_8               0x09
#define IR_DIK_9               0x0A
#define IR_DIK_0               0x0B
#define IR_DIK_MINUS           0x0C    /* - on main keyboard */
#define IR_DIK_EQUALS          0x0D
#define IR_DIK_BACK            0x0E    /* backspace */
#define IR_DIK_TAB             0x0F
#define IR_DIK_Q               0x10
#define IR_DIK_W               0x11
#define IR_DIK_E               0x12
#define IR_DIK_R               0x13
#define IR_DIK_T               0x14
#define IR_DIK_Y               0x15
#define IR_DIK_U               0x16
#define IR_DIK_I               0x17
#define IR_DIK_O               0x18
#define IR_DIK_P               0x19
#define IR_DIK_LBRACKET        0x1A
#define IR_DIK_RBRACKET        0x1B
#define IR_DIK_RETURN          0x1C    /* Enter on main keyboard */
#define IR_DIK_LCONTROL        0x1D
#define IR_DIK_A               0x1E
#define IR_DIK_S               0x1F
#define IR_DIK_D               0x20
#define IR_DIK_F               0x21
#define IR_DIK_G               0x22
#define IR_DIK_H               0x23
#define IR_DIK_J               0x24
#define IR_DIK_K               0x25
#define IR_DIK_L               0x26
#define IR_DIK_SEMICOLON       0x27
#define IR_DIK_APOSTROPHE      0x28
#define IR_DIK_GRAVE           0x29    /* accent grave */
#define IR_DIK_LSHIFT          0x2A
#define IR_DIK_BACKSLASH       0x2B
#define IR_DIK_Z               0x2C
#define IR_DIK_X               0x2D
#define IR_DIK_C               0x2E
#define IR_DIK_V               0x2F
#define IR_DIK_B               0x30
#define IR_DIK_N               0x31
#define IR_DIK_M               0x32
#define IR_DIK_COMMA           0x33
#define IR_DIK_PERIOD          0x34    /* . on main keyboard */
#define IR_DIK_SLASH           0x35    /* / on main keyboard */
#define IR_DIK_RSHIFT          0x36
#define IR_DIK_MULTIPLY        0x37    /* * on numeric keypad */
#define IR_DIK_LMENU           0x38    /* left Alt */
#define IR_DIK_SPACE           0x39
#define IR_DIK_CAPITAL         0x3A
#define IR_DIK_F1              0x3B
#define IR_DIK_F2              0x3C
#define IR_DIK_F3              0x3D
#define IR_DIK_F4              0x3E
#define IR_DIK_F5              0x3F
#define IR_DIK_F6              0x40
#define IR_DIK_F7              0x41
#define IR_DIK_F8              0x42
#define IR_DIK_F9              0x43
#define IR_DIK_F10             0x44
#define IR_DIK_NUMLOCK         0x45
#define IR_DIK_SCROLL          0x46    /* Scroll Lock */
#define IR_DIK_NUMPAD7         0x47
#define IR_DIK_NUMPAD8         0x48
#define IR_DIK_NUMPAD9         0x49
#define IR_DIK_SUBTRACT        0x4A    /* - on numeric keypad */
#define IR_DIK_NUMPAD4         0x4B
#define IR_DIK_NUMPAD5         0x4C
#define IR_DIK_NUMPAD6         0x4D
#define IR_DIK_ADD             0x4E    /* + on numeric keypad */
#define IR_DIK_NUMPAD1         0x4F
#define IR_DIK_NUMPAD2         0x50
#define IR_DIK_NUMPAD3         0x51
#define IR_DIK_NUMPAD0         0x52
#define IR_DIK_DECIMAL         0x53    /* . on numeric keypad */
#define IR_DIK_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define IR_DIK_F11             0x57
#define IR_DIK_F12             0x58
#define IR_DIK_F13             0x64    /*                     (NEC PC98) */
#define IR_DIK_F14             0x65    /*                     (NEC PC98) */
#define IR_DIK_F15             0x66    /*                     (NEC PC98) */
#define IR_DIK_KANA            0x70    /* (Japanese keyboard)            */
#define IR_DIK_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define IR_DIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define IR_DIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define IR_DIK_YEN             0x7D    /* (Japanese keyboard)            */
#define IR_DIK_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define IR_DIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define IR_DIK_PREVTRACK       0x90    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
#define IR_DIK_AT              0x91    /*                     (NEC PC98) */
#define IR_DIK_COLON           0x92    /*                     (NEC PC98) */
#define IR_DIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define IR_DIK_KANJI           0x94    /* (Japanese keyboard)            */
#define IR_DIK_STOP            0x95    /*                     (NEC PC98) */
#define IR_DIK_AX              0x96    /*                     (Japan AX) */
#define IR_DIK_UNLABELED       0x97    /*                        (J3100) */
#define IR_DIK_NEXTTRACK       0x99    /* Next Track */
#define IR_DIK_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define IR_DIK_RCONTROL        0x9D
#define IR_DIK_MUTE            0xA0    /* Mute */
#define IR_DIK_CALCULATOR      0xA1    /* Calculator */
#define IR_DIK_PLAYPAUSE       0xA2    /* Play / Pause */
#define IR_DIK_MEDIASTOP       0xA4    /* Media Stop */
#define IR_DIK_VOLUMEDOWN      0xAE    /* Volume - */
#define IR_DIK_VOLUMEUP        0xB0    /* Volume + */
#define IR_DIK_WEBHOME         0xB2    /* Web home */
#define IR_DIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define IR_DIK_DIVIDE          0xB5    /* / on numeric keypad */
#define IR_DIK_SYSRQ           0xB7
#define IR_DIK_RMENU           0xB8    /* right Alt */
#define IR_DIK_PAUSE           0xC5    /* Pause */
#define IR_DIK_HOME            0xC7    /* Home on arrow keypad */
#define IR_DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define IR_DIK_PRIOR           0xC9    /* PgUp on arrow keypad */
#define IR_DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define IR_DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define IR_DIK_END             0xCF    /* End on arrow keypad */
#define IR_DIK_DOWN            0xD0    /* DownArrow on arrow keypad */
#define IR_DIK_NEXT            0xD1    /* PgDn on arrow keypad */
#define IR_DIK_INSERT          0xD2    /* Insert on arrow keypad */
#define IR_DIK_DELETE          0xD3    /* Delete on arrow keypad */
#define IR_DIK_LWIN            0xDB    /* Left Windows key */
#define IR_DIK_RWIN            0xDC    /* Right Windows key */
#define IR_DIK_APPS            0xDD    /* AppMenu key */
#define IR_DIK_POWER           0xDE    /* System Power */
#define IR_DIK_SLEEP           0xDF    /* System Sleep */
#define IR_DIK_WAKE            0xE3    /* System Wake */
#define IR_DIK_WEBSEARCH       0xE5    /* Web Search */
#define IR_DIK_WEBFAVORITES    0xE6    /* Web Favorites */
#define IR_DIK_WEBREFRESH      0xE7    /* Web Refresh */
#define IR_DIK_WEBSTOP         0xE8    /* Web Stop */
#define IR_DIK_WEBFORWARD      0xE9    /* Web Forward */
#define IR_DIK_WEBBACK         0xEA    /* Web Back */
#define IR_DIK_MYCOMPUTER      0xEB    /* My Computer */
#define IR_DIK_MAIL            0xEC    /* Mail */
#define IR_DIK_MEDIASELECT     0xED    /* Media Select */

/*********** KeyBoard Virtual Key Code Of Iris 2D *************/

/*********** Joy Virtual Key Code Of Iris 2D *************/

/*********** Joy Virtual Key Code Of Iris 2D *************/

#endif