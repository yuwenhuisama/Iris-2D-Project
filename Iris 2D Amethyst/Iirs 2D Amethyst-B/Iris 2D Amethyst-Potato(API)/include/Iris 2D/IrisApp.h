#ifndef _IRISAPP_H_
#define _IRISAPP_H_
#include "Iris2D.h"

enum IrisAppRunningState{
	Running = 0,
	Quit,
};

class IrisApp : public IIrisApp{
public:
	IDirect3DDevice9* Device;
	IDirectInputDevice8 * KeyBoardInputDevice;
	IDirectInputDevice8 * MouseInputDevice;

	bool Init(HINSTANCE hInstance, int width, int height, bool(*pf)(), wstring title);
	void Run();
	void Release();
	void Display();
	IDirect3DDevice9* GetDevice();

	bool IsRunning(){ return RuningState == Running; }
	bool IsQuited(){ return RuningState == Quit; }
	int MessageLoop();
	void GoQuit();

	bool CanDisplay;

	HINSTANCE hInstance;

	static IrisApp* Instance();

	float GetTimeDelta(){ return this->timeDelta; }

	virtual ~IrisApp();

private:
	IrisApp();

	void SetWindowSize();

	static IrisApp* instance;
	IrisAppRunningState RuningState;
	ULONG_PTR m_pGdiToken;
	bool(*ptr_display)();
	bool Setup(int width, int height);
	float timeDelta;
	DWORD lastTime;
	DWORD currentTime;
};
#endif
