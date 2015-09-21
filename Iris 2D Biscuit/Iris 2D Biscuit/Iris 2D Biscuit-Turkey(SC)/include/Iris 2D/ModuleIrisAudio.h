/************************************************************************
*
* Header File Name: ModuleIrisAudio
* Class Name :ModuleIrisAudio
* Function : This is a static moudle-like class that will be used globoly which has functions of audio resource oparating and organizing.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _MODULEIRISAUDIO_H_
#define _MODULEIRISAUDIO_H_

#include "Iris2DSupports.h"

#ifdef _MSC_VER
#include "Fmod Ex/fmod.hpp"
#include "Fmod Ex/fmod_errors.h"
using namespace FMOD;
#endif
#ifndef _MSC_VER
#include "Fmod Ex/fmod.h"
#include "Fmod Ex/fmod_errors.h"
#endif

namespace Iris2D{

#include <string>
	using namespace std;

	class ModuleIrisAudio
	{
	protected:
#ifndef _MSC_VER
		static FMOD_SYSTEM* fmodSystem;
		static FMOD_SOUND* bgm;
		static FMOD_SOUND* bgs;
		static FMOD_SOUND* se;
		static FMOD_SOUND* me;
		static int channels;
		static FMOD_CHANNEL* bgmChannel;
		static FMOD_CHANNEL* bgsChannel;
		static FMOD_CHANNEL* seChannel;
		static FMOD_CHANNEL* meChannel;
#endif
#ifdef _MSC_VER
		static System* fmodSystem;
		static Sound* bgm;
		static Sound* bgs;
		static Sound* se;
		static Sound* me;
		static int channels;
		static Channel* bgmChannel;
		static Channel* bgsChannel;
		static Channel* seChannel;
		static Channel* meChannel;
#endif

		static bool bgmIsFading;
		static bool bgsIsFading;
		static bool seIsFading;

	public:
		ModuleIrisAudio(void);

		static bool InitAudio(int channels);
		static bool ReleaseAudio();

		static bool BgmPlay(wstring filePath, int volume, int rate);
		static bool BgmFade(int fadeTime);
		static bool BgmStop();

		static bool BgsPlay(wstring filePath, int volume, int rate);
		static bool BgsFade(int fadeTime);
		static bool BgsStop();

		static bool SePlay(wstring filePath, int volume, int rate);
		static bool SeFade(int fadeTime);
		static bool SeStop();

		static bool MePlay(wstring filePath, int volume, int rate);
		static bool MeStop();

		static void FadeBgmThreadProc(int duration);
		static void FadeBgsThreadProc(int duration);
		static void FadeSeThreadProc(int duration);

		static void Update();

		virtual ~ModuleIrisAudio(void) = 0;

	};
}
#endif
