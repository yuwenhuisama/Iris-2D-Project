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

#include "Iris2DSupports.h"
#include "ModuleIrisGraphics.h"
#include "IrisRect.h"

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

#define MOUSE_REPEAD_DURATION 10

namespace Iris2D {

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

		static bool CursorInRect(const IrisRect*);

		static void SecKeyStateUpdate();

		ModuleIrisInput(void);
		virtual ~ModuleIrisInput(void) = 0;
	};
}
#endif
