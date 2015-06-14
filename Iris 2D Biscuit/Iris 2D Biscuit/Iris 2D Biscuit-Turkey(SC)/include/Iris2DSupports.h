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

#ifndef _IRIS2DSUPPORT_H_
#define _IRIS2DSUPPORT_H_

#define DIRECTINPUT_VERSION 0x0800
#define DINPUT_BUFFERSIZE 16

#define CPP_GETTER(pn, vn, dtp) \
	dtp Get##pn() { \
		return this->vn; \
	}
#define CPP_SETTER(pn, vn, dtp) \
	void Set##pn(dtp v){ \
		this->vn = v; \
	}
#define CPP_GETTER_SETTER(pn, vn, dtp) \
	CPP_GETTER(pn, vn, dtp) \
	CPP_SETTER(pn, vn, dtp)

#include <d3dx9.h>
#include <d3d9.h>
#include <DInput.h>

#include <windows.h>
#include <GdiPlus.h>
#include <MMSystem.h>

#ifdef _MSC_VER
#pragma comment(lib, "GdiPlus.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "fmodex_vc.lib")
#endif

#include <string>
using namespace std;

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

namespace Iris2D {
	// Define Max FPS
	const float FPSMax = 60.0f;

	// Iris2D vertex
	struct Iris2DVertex {
		Iris2DVertex() {}
		Iris2DVertex(float x, float y, float z,
			//float nx, float ny, float nz,
			float u, float v)
		{
			_x = x;  _y = y;  _z = z;
			//_nx = nx; _ny = ny; _nz = nz;
			_u = u;  _v = v;
		}

		float _x, _y, _z;
		//float _nx, _ny, _nz;
		float _u, _v;
		//static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};
}
#endif