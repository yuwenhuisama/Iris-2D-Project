/************************************************************************
*
* Header File Name: ModuleIrisAudio
* Class Name :ModuleIrisAudio
* Function : This is a static moudle-like class that will be used globoly which has functions of graphics resource oparating and organizing.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _MODULEIRISGARAPHICS_H_
#define _MODULEIRISGARAPHICS_H_

#include "Iris2D.h"
#include <list>

using std::list;

class IrisBitmap;
class IrisViewport;
class IrisSprite;

class ModuleIrisGraphics
{
public:

	static int width;
	static int height;
	static IDirect3DDevice9 *Device;

	static list<IrisViewport*> viewports;
	static IrisViewport* gViewport;

	static bool isFreeze;

	//public:
	ModuleIrisGraphics(void);

	static void Init();
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	static IrisViewport* getGViewport();
	static void setDevice(IDirect3DDevice9 *Device);
	static void Update();
	static void Wait(int duration);
	static void fadeOut(int duration);
	static void fadeIn(int duration);
	static void freeze();
	static void transition(int duration, wstring filename, int vague);
	static void snap2Bitmap(IrisBitmap *bitmap);
	static void frameReset();
	static void resizeScreen(int width, int height);
	static int getWidth();
	static int getHeight();
	static bool compareViewprotWithZ(IrisViewport *v1, IrisViewport *v2);
	static void sortViewports();

	static void disposeAllGraphicsSource();

	static void addViewport(IrisViewport *viewport);
	static void deleteViewport(IrisViewport *viewport);

	static void MakeExchangeTexture();
	static void MakeExchangeVertex();

	static float frameRate;
	static unsigned long frameCount;
	static float brightness;

	static HWND hwnd;

	static IDirect3DTexture9* ExchangeTexture;
	static IDirect3DVertexBuffer9* ExchangeVertex;

	static IDirect3DTexture9* PreTexture;
	static IDirect3DTexture9* TargetTexture;

	static IDirect3DTexture9* FreezedTexture;
	static IDirect3DTexture9* TransitionTexture;

	static int getBrightness();
	static void setBrightness(int brightness);

	static void UpdateSpritesAndViewports(IrisShader*& shader, D3DXMATRIX& proj);
	static void UpdateBackBuffer(IrisShader*& shader, D3DXMATRIX& proj);

	virtual ~ModuleIrisGraphics(void) = 0;
};

#endif
