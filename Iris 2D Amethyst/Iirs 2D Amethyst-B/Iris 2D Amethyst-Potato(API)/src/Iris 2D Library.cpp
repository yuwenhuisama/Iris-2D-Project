// Iris 2D Library.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Iris 2D Library.h"

#ifdef __GNUC__
IIrisWindow::~IIrisWindow() {}
IIrisSprite::~IIrisSprite() {}
IIrisColor::~IIrisColor() {}
IIrisPlane::~IIrisPlane() {}
IIrisRect::~IIrisRect() {}
IIrisTilemap::~IIrisTilemap() {}
IIrisFont::~IIrisFont() {}
IIrisTone::~IIrisTone() {}
IIrisBitmap::~IIrisBitmap() {}
IIrisApp::~IIrisApp(){}
IIrisViewport::~IIrisViewport(){}
#endif

IRIS2DLIBRARY_API IIrisApp* GetIrisApp(){
	IIrisApp* p = IrisApp::Instance();
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisApp(IIrisApp* app){
	delete app;
}

IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(wstring fileName){
	IIrisBitmap *p = new IrisBitmap(fileName);
	return p;
}

IRIS2DLIBRARY_API IIrisBitmap* GetTravialIIrisBitmap(){
	IIrisBitmap *p = new IrisBitmap();
	return p;
}

IRIS2DLIBRARY_API IIrisBitmap* GetIrisBitmap(int width, int height){
	IIrisBitmap *p = new IrisBitmap(width, height);
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisBitmap(IIrisBitmap* bmp){
	delete bmp;
}

IRIS2DLIBRARY_API IIrisColor* GetIrisColor(int red, int green, int blue, int alpha){
	IIrisColor* p = new IrisColor(red, green, blue, alpha);
	return p;
}

IRIS2DLIBRARY_API IIrisColor* GetTravialIIrisColor(){
	IIrisColor* p = new IrisColor();
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisColor(IIrisColor* color){
	delete color;
}

IRIS2DLIBRARY_API IIrisFont* GetTravialIIrisFont(){
	IrisFont* p = new IrisFont();
	return p;
}

IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name){
	IrisFont* p = new IrisFont(name);
	return p;
}

IRIS2DLIBRARY_API IIrisFont* GetIrisFont(wstring name, int size){
	IrisFont* p = new IrisFont(name, size);
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisFont(IIrisFont* font){
	delete font;
}

IRIS2DLIBRARY_API IIrisSprite* GetTravialIIrisSprite(){
	IIrisSprite *p = new IrisSprite();
	return p;
}

IRIS2DLIBRARY_API IIrisSprite* GetIrisSprite(IIrisViewport *viewport){
	IIrisSprite *p = new IrisSprite(viewport);
	return p;
}

IRIS2DLIBRARY_API IIrisSprite* GetIrisSprite(){
	IIrisSprite *p = new IrisSprite();
	return p;
}


IRIS2DLIBRARY_API void ReleaseIrisSprite(IIrisSprite* sp){
	delete sp;
}

IRIS2DLIBRARY_API IIrisRect* GetTravialIIrisRect(){
	IIrisRect* p = new IrisRect();
	return p;
}

IRIS2DLIBRARY_API IIrisRect* GetIrisRect(float x, float y, float width, float height){
	IIrisRect* p = new IrisRect(x, y, width, height);
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisRect(IIrisRect *sp){
	delete sp;
}

IRIS2DLIBRARY_API IIrisViewport* GetTravialIIrisViewport(){
	IIrisViewport *p = new IrisViewport();
	return p;
}

IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(float x, float y, float width, float height){
	IIrisViewport *p = new IrisViewport(x, y, width, height);
	return p;
}

IRIS2DLIBRARY_API IIrisViewport* GetIrisViewport(const IIrisRect *rect){
	IIrisViewport *p = new IrisViewport(rect);
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisViewport(IIrisViewport *vp){
	delete vp;
}

IRIS2DLIBRARY_API IIrisTone* GetTravialIIrisTone(){
	IIrisTone* p = new IrisTone();
	return p;
}

IRIS2DLIBRARY_API IIrisTone* GetIrisTone(int r, int g, int b, int a){
	IIrisTone* p = new IrisTone(r, g, b, a);
	return p;
}

IRIS2DLIBRARY_API void ReleaseIrisTone(IIrisTone* tn){
	delete tn;
}

IRIS2DLIBRARY_API bool IrisFontExisted(wstring name){
	return IrisFont::Existed(name);
}

IRIS2DLIBRARY_API wstring IrisFontGetDefaultName(){
	return IrisFont::defaultName;
}

IRIS2DLIBRARY_API int IrisFontGetDefaultSize(){
	return IrisFont::defaultSize;
}

IRIS2DLIBRARY_API bool IrisFontGetDefaultBold(){
	return IrisFont::defaultBold;
}

IRIS2DLIBRARY_API bool IrisFontGetDefaultItalic(){
	return IrisFont::defaultItalic;
}

IRIS2DLIBRARY_API bool IrisFontGetDefaultShadow(){
	return IrisFont::defaultShadow;
}

IRIS2DLIBRARY_API IIrisColor* IrisFontGetDefaultColor(){
	return (IIrisColor*)IrisFont::defaultColor;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultName(wstring name){
	IrisFont::defaultName = name;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultSize(int size){
	IrisFont::defaultSize = size;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultBold(bool bold){
	IrisFont::defaultBold = bold;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultItalic(bool italic){
	IrisFont::defaultItalic = italic;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultShadow(bool italic){
	IrisFont::defaultShadow = italic;
}

IRIS2DLIBRARY_API void IrisFontSetDefaultColor(IIrisColor* color){
	delete IrisFont::defaultColor;
	IrisFont::defaultColor = color;
}

IRIS2DLIBRARY_API HWND IrisGraphicsGetHwnd(){
	return ModuleIrisGraphics::hwnd;
}

IRIS2DLIBRARY_API int IrisGraphicsGetWidth(){
	return ModuleIrisGraphics::width;
}

IRIS2DLIBRARY_API int IrisGraphicsGetHeight(){
	return ModuleIrisGraphics::height;
}

IRIS2DLIBRARY_API void IrisGraphicsUpdate(){
	ModuleIrisGraphics::Update();
}

IRIS2DLIBRARY_API void IrisGraphicsWait(int duration){
	ModuleIrisGraphics::Wait(duration);
}

IRIS2DLIBRARY_API void IrisGraphicsFadeOut(int duration){
	ModuleIrisGraphics::fadeOut(duration);
}

IRIS2DLIBRARY_API void IrisGraphicsFadeIn(int duration){
	ModuleIrisGraphics::fadeIn(duration);
}

IRIS2DLIBRARY_API void IrisGraphicsFreeze(){
	ModuleIrisGraphics::freeze();
}
IRIS2DLIBRARY_API void IrisGraphicsTransition(int duration, wstring filename, int vague){
	ModuleIrisGraphics::transition(duration, filename, vague);
}

IRIS2DLIBRARY_API void IrisGraphicsSnap2Bitmap(IIrisBitmap* bitmap){
	ModuleIrisGraphics::snap2Bitmap(bitmap);
}

IRIS2DLIBRARY_API void IrisGraphicsFrameReset(){
	ModuleIrisGraphics::frameReset();
}

IRIS2DLIBRARY_API void IrisGraphicsResizeScreen(int width, int height){
	ModuleIrisGraphics::resizeScreen(width, height);
}

IRIS2DLIBRARY_API float IrisGraphicsGetFrameRate(){
	return ModuleIrisGraphics::frameRate;
}

IRIS2DLIBRARY_API void IrisGraphicsSetFrameRate(int fr){
	ModuleIrisGraphics::frameRate = fr;
}

IRIS2DLIBRARY_API unsigned long IrisGraphicsGetFrameCount(){
	return ModuleIrisGraphics::frameCount;
}

IRIS2DLIBRARY_API void IrisGraphicsSetFrameCount(int ct){
	ModuleIrisGraphics::frameCount = ct;
}

IRIS2DLIBRARY_API int IrisGraphicsGetBrightness(){
	return ModuleIrisGraphics::getBrightness();
}

IRIS2DLIBRARY_API void IrisGraphicsSetBrightness(int bn){
	ModuleIrisGraphics::setBrightness(bn);
}

IRIS2DLIBRARY_API void IrisInputUpdate(){
	ModuleIrisInput::Update();
}

IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyPress(DWORD key){
	return ModuleIrisInput::KeyBoardKeyPress(key);
}

IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyTrigger(DWORD key){
	return ModuleIrisInput::KeyBoardKeyTrigger(key);
}

IRIS2DLIBRARY_API bool IrisInputKeyBoardKeyRepeat(DWORD key){
	return ModuleIrisInput::KeyBoardKeyRepeat(key);
}

IRIS2DLIBRARY_API bool IrisInputMousePress(MouseKey botton){
	return ModuleIrisInput::MousePress(botton);
}

IRIS2DLIBRARY_API bool IrisInputMouseTrigger(MouseKey botton){
	return ModuleIrisInput::MouseTrigger(botton);
}

IRIS2DLIBRARY_API bool IrisInputMouseRepeat(MouseKey botton){
	return ModuleIrisInput::MouseRepeat(botton);
}

IRIS2DLIBRARY_API long IrisInputMouseMiddleRoll(){
	return ModuleIrisInput::MouseMiddleRoll();
}

IRIS2DLIBRARY_API long IrisInputMouseXMove(){
	return ModuleIrisInput::MouseXMove();
}

IRIS2DLIBRARY_API long IrisInputMouseYMove(){
	return ModuleIrisInput::MouseYMove();
}

IRIS2DLIBRARY_API int IrisInputGetCursorX(){
	return ModuleIrisInput::GetCursorX();
}

IRIS2DLIBRARY_API int IrisInputGetCursorY(){
	return ModuleIrisInput::GetCursorY();
}

IRIS2DLIBRARY_API bool IrisInputCursorInRect(IIrisRect* rect){
	return ModuleIrisInput::CursorInRect(rect);
}

IRIS2DLIBRARY_API bool IrisAudioBgmPlay(wstring filePath, int volume, int rate){
	return ModuleIrisAudio::BgmPlay(filePath, volume, rate);
}

IRIS2DLIBRARY_API bool IrisAudioBgmFade(int fadeTime){
	return ModuleIrisAudio::BgmFade(fadeTime);
}

IRIS2DLIBRARY_API bool IrisAudioBgmStop(){
	return ModuleIrisAudio::BgmStop();
}

IRIS2DLIBRARY_API bool IrisAudioBgsPlay(wstring filePath, int volume, int rate){
	return ModuleIrisAudio::BgmPlay(filePath, volume, rate);
}

IRIS2DLIBRARY_API bool IrisAudioBgsFade(int fadeTime){
	return ModuleIrisAudio::BgmFade(fadeTime);
}

IRIS2DLIBRARY_API bool IrisAudioBgsStop(){
	return ModuleIrisAudio::BgsStop();
}

IRIS2DLIBRARY_API bool IrisAudioSePlay(wstring filePath, int volume, int rate){
	return ModuleIrisAudio::SePlay(filePath, volume, rate);
}

IRIS2DLIBRARY_API bool IrisAudioSeFade(int fadeTime){
	return ModuleIrisAudio::SeFade(fadeTime);
}


IRIS2DLIBRARY_API bool IrisAudioSeStop(){
	return ModuleIrisAudio::SeStop();
}

IRIS2DLIBRARY_API bool IrisAudioMePlay(wstring filePath, int volume, int rate){
	return ModuleIrisAudio::MePlay(filePath, volume, rate);
}

IRIS2DLIBRARY_API bool IrisAudioMeStop(){
	return ModuleIrisAudio::MeStop();
}
