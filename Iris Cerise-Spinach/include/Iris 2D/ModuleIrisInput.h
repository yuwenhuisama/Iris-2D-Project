/************************************************************************
*
* Header File Name: ModuleIrisAudio
* Class Name :ModuleIrisAudio
* Function : This is a static moudle-like class that will be used globoly which has functions of inputing oparating. , 
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _MODULEIRISINPUT_H_
#define _MODULEIRISINPUT_H_

#include "Iris 2D Library.h"
#include "Iris2DSupports.h"

#define MOUSE_REPEAD_DURATION 10

namespace Iris2D {

	struct KeyState{
		BOOL trigger;
		long secTime;
		DWORD state;
	};

	class IrisRect;
	class ModuleIrisGraphics;

	class ModuleIrisInput
	{
	public:

		static IDirectInputDevice8 * KeyBoardInputDevice;
		static IDirectInputDevice8 * MouseInputDevice;

		static bool DeviceRead(IDirectInputDevice8* pDIDevice, void* pBuffer, long lSize);
		static void Update();

		static char KeyStateBuffer[256];
		static char LastKeyStateBuffer[256];

		static DIMOUSESTATE MouseStateBuffer;
		static DIMOUSESTATE LastMouseStateBuffer;
		static KeyState TimeSecStateBufferLeftKey;
		static KeyState TimeSecStateBufferRightKey;
		static KeyState TimeSecStateBufferKeyBoard[256];

		//static DIDEVICEOBJECTDATA kbdidod[DINPUT_BUFFERSIZE];
		//static DIDEVICEOBJECTDATA msdidod[DINPUT_BUFFERSIZE];

		static bool KeyBoardKeyPress(DWORD key);
		static bool KeyBoardKeyTrigger(DWORD key);
		static bool KeyBoardKeyRepeat(DWORD key);

		static bool MousePress(MouseKey botton);
		static bool MouseTrigger(MouseKey botton);
		static bool MouseRepeat(MouseKey botton);

		static long MouseMiddleRoll();
		static long MouseXMove();
		static long MouseYMove();

		static int GetCursorX();
		static int GetCursorY();

		static bool CursorInRect(const IIrisRect*);

		static void SecKeyStateUpdate();

		ModuleIrisInput(void);
		virtual ~ModuleIrisInput(void) = 0;
	};
}
#endif
