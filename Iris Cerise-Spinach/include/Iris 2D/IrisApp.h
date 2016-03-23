#ifndef _IRISAPP_H_
#define _IRISAPP_H_

#include "Iris 2D Library.h"
#include "Iris2DSupports.h"

namespace Iris2D{

	enum IrisAppRunningState{
		Running = 0,
		Quit,
	};

	class IrisApp : public IIrisApp{
	public:
		IDirect3DDevice9* Device;
		IDirectInputDevice8 * KeyBoardInputDevice;
		IDirectInputDevice8 * MouseInputDevice;

		bool Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title, IR_PARAM_RESULT);
		void Run(IR_PARAM_RESULT);
		void Release(IR_PARAM_RESULT);
		void Display(IR_PARAM_RESULT);
		void ToggleWindowMode();

		IDirect3DDevice9* GetDevice() { return this->Device; };

		bool IsRunning(){ return RuningState == Running; }
		bool IsQuited(){  return RuningState == Quit; }
		int MessageLoop();
		void GoQuit() { RuningState = Quit; };

		bool CanDisplay;
		D3DPRESENT_PARAMETERS curD3DParameters;

		HINSTANCE hInstance;

		static IrisApp* Instance();

		float GetTimeDelta(){ return this->timeDelta; }

		RECT windowRect;

		~IrisApp();

	private:
		IrisApp();

		void SetWindowSize();

		void OnDeviceLost();
		void OnDeviceRecover();

		static IrisApp* instance;
		IrisAppRunningState RuningState;
		ULONG_PTR m_pGdiToken;
		bool(*ptr_display)();
		bool Setup(int width, int height);
		float timeDelta;
		DWORD lastTime;
		DWORD currentTime;

		friend class ModuleIrisGraphics;
	};
}
#endif