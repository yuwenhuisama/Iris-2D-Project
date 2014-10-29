/************************************************************************
*
* Header File Name: D3DUtility
* Function : Define structures and functions to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _MSC_VER
#define UNICODE
#endif

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

//#include <ruby.h>

//#define MINGW_WITH_RUBY
#ifndef _IRIS2D_H_
#define _IRIS2D_H_
#ifdef MINGW_WITH_RUBY
#include "CppDsToRubyMacro.h"
#endif // MINGW_WITH_RUBY

#define DIRECTINPUT_VERSION 0x0800
#define DINPUT_BUFFERSIZE 16

#define IRIS2D_VERSION 0x04080801

#include <d3dx9.h>
#include <string>
using namespace std;

#include <d3d9.h>
#include <DInput.h>
#include "XMLDefine.h"

#include <windows.h>
#include <GdiPlus.h>
#include <MMSystem.h>

#include "IrisBitmap.h"
#include "IrisViewport.h"
#include "IrisSprite.h"
#include "IrisFont.h"
#include "IrisColor.h"
#include "IrisTone.h"
#include "IrisRect.h"
#include "IrisApp.h"
#include "IrisD3DNamespace.h"

#include "ModuleIrisAudio.h"
#include "ModuleIrisGraphics.h"
#include "ModuleIrisInput.h"

#include "ModuleIrisAudio.h"
#include "ModuleIrisGraphics.h"
#include "ModuleIrisInput.h"

#ifdef _MSC_VER
#pragma comment(lib, "GdiPlus.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "fmodex_vc.lib")
#endif

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

class IrisApp;

// Define Max FPS
const float FPSMax = 60.0f;

// Iris2D vertex
struct Iris2DVertex {
	Iris2DVertex() {}
	Iris2DVertex(float x, float y, float z, float u, float v){
		_x = x;
		_y = y;
		_z = z;
		_u = u;
		_v = v;
	}

	float _x, _y, _z;
	float _u, _v;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};
#endif
