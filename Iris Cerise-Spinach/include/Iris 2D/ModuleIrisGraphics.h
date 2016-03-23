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

#include "Iris 2D Library.h"
#include "Iris2DSupports.h"
//#include "IrisError.h"
#include <list>

namespace Iris2D {
	using namespace std;
	using namespace Gdiplus;

	class IrisShader;
	class IrisBitmap;
	class IrisViewport;
	class IrisSprite;
	class IrisApp;
	class IrisColor;

	class ModuleIrisGraphics
	{
	protected:
		static IDirect3DDevice9 *Device;
		static int width;
		static int height;
		static list<IIrisViewport*> viewports;

		static bool isFreeze;
		static bool isTransition;
		static float frameRate;
		static unsigned long frameCount;
		static float brightness;

		static IIrisViewport* gViewport;

		static HWND hwnd;

		static IDirect3DTexture9* ExchangeTexture;
		static IDirect3DVertexBuffer9* ExchangeVertex;

		static IDirect3DTexture9* PreTexture;
		static IDirect3DTexture9* TargetTexture;

		static IDirect3DTexture9* FreezedTexture;
		static IDirect3DTexture9* TransitionTexture;

		static bool UpdateSpritesAndViewports(IrisShader*& shader, D3DXMATRIX& proj);
		static bool UpdateBackBuffer(IrisShader*& shader, D3DXMATRIX& proj);
		static bool ViewportSortFunc(IIrisViewport*& vp1, IIrisViewport*& vp2);

	public:

		ModuleIrisGraphics(void);

		static void SortViewports();

		static bool Init();
		static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
		
		static void Update(IR_PARAM_RESULT);
		static void Wait(int duration, IR_PARAM_RESULT);
		static void FadeOut(int duration, IR_PARAM_RESULT);
		static void FadeIn(int duration, IR_PARAM_RESULT);
		static void Freeze(IR_PARAM_RESULT);
		static void Transition(int duration, wstring filename, int vague, IR_PARAM_RESULT);
		static void Snap2Bitmap(IIrisBitmap *bitmap, IR_PARAM_RESULT);
		static void FrameReset();
		static void ResizeScreen(int width, int height, IR_PARAM_RESULT);

		static void SetWidth(int w);
		static int GetWidth();
		static void SetHeight(int h);
		static int GetHeight();

		static void DisposeAllGraphicsSource();
		static void AddViewport(IIrisViewport *viewport);
		static void DeleteViewport(IIrisViewport *viewport);

		static bool MakeExchangeTexture();
		static bool MakeExchangeVertex();

		static IIrisViewport* GetGViewport();
		static void SetDevice(IDirect3DDevice9 *Device);
		static IDirect3DDevice9* GetDevice();

		static void SetHwnd(HWND hWnd);
		static HWND GetHwnd();

		static unsigned long GetFrameCount();

		static int GetBrightness();
		static void SetBrightness(int brightness);

		static float GetFrameRate();

		static void OnDeviceLost();
		static void OnDeviceRecover();

		virtual ~ModuleIrisGraphics(void) = 0;

		friend class IrisShader;
		friend class IrisApp;
	};
}
#endif
