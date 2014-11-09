#include "classes.h"

IIrisApp* app;

bool Display(){
	SceneBase::CurScene = new SceneTitle();
	while (app->IsRunning()){
		while (SceneBase::CurScene && app->IsRunning()){
			SceneBase::CurScene->Main();
		}
		break;
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	app = GetIrisApp();
	app->Init(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, Display, GAME_TITLE);

	/* Set window in the middle begin*/
	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect;
	GetWindowRect(IrisGraphicsGetHwnd(), &rect);
	SetWindowPos(IrisGraphicsGetHwnd(), 
		0,
		(scrWidth - rect.right) / 2,
		(scrHeight - rect.bottom) / 2,
		rect.right - rect.left,
		rect.bottom - rect.top,
		SWP_SHOWWINDOW);
	/* Set window in the middle end */

	app->Run();
	app->Release();

	return 0;
}