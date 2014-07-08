#include "ModuleIrisAudio.h"

int ModuleIrisAudio::channels = 64;
#ifndef _MSC_VER
#define TRUE 1
#define FALSE 0
FMOD_SYSTEM* ModuleIrisAudio::fmodSystem = 0;
FMOD_SOUND* ModuleIrisAudio::bgm = 0;
FMOD_SOUND* ModuleIrisAudio::bgs = 0;
FMOD_SOUND* ModuleIrisAudio::se = 0;
FMOD_SOUND* ModuleIrisAudio::me = 0;
FMOD_CHANNEL* ModuleIrisAudio::bgmChannel = 0;
FMOD_CHANNEL* ModuleIrisAudio::bgsChannel = 0;
FMOD_CHANNEL* ModuleIrisAudio::seChannel = 0;
FMOD_CHANNEL* ModuleIrisAudio::meChannel = 0;
#endif

#ifdef _MSC_VER
System* ModuleIrisAudio::fmodSystem = NULL;
Sound* ModuleIrisAudio::bgm = NULL;
Sound* ModuleIrisAudio::bgs = NULL;
Sound* ModuleIrisAudio::se = NULL;
Sound* ModuleIrisAudio::me = NULL;
Channel* ModuleIrisAudio::bgmChannel = NULL;
Channel* ModuleIrisAudio::bgsChannel = NULL;
Channel* ModuleIrisAudio::seChannel = NULL;
Channel* ModuleIrisAudio::meChannel = NULL;
#endif

ModuleIrisAudio::ModuleIrisAudio(void)
{
}

ModuleIrisAudio::~ModuleIrisAudio(void)
{
}

#ifndef _MSC_VER
bool ModuleIrisAudio::InitAudio(int cs){

	channels = cs;
	FMOD_RESULT result;

	result = FMOD_System_Create(&fmodSystem); 	// Create the main system object.

	if(result != FMOD_OK)
		return false;

	result = FMOD_System_Init(fmodSystem, channels, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		return false;
	}
	return true;
}

bool ModuleIrisAudio::ReleaseAudio(){
	FMOD_RESULT result = FMOD_System_Release(fmodSystem);
	return (result == FMOD_OK ? true : false);
}

bool ModuleIrisAudio::BgmPlay(wstring filePath, int volume, int rate){
	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (bgmChannel != NULL){
			BOOL isPlaying;
			FMOD_Channel_IsPlaying(bgmChannel, &isPlaying);
			if (isPlaying)
				FMOD_Channel_Stop(bgmChannel);
		}
	}

	FMOD_RESULT result;

	result = FMOD_System_CreateStream(fmodSystem, fpath, FMOD_DEFAULT, 0, &bgm);
	if (result != FMOD_OK)
		return false;

	result = FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, bgm, true, &bgmChannel);
	if (result != FMOD_OK)
		return false;

	FMOD_Channel_SetMode(bgmChannel, FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(bgmChannel, volume / 100.0f);

	float frequancy;

	FMOD_Channel_GetFrequency(bgmChannel, &frequancy);
	FMOD_Channel_SetFrequency(bgmChannel, frequancy * (rate / 100.0));
	FMOD_Channel_SetPaused(bgmChannel, FALSE);

	return true;
}

bool ModuleIrisAudio::BgmFade(int fadeTime){
	return true;
}

bool ModuleIrisAudio::BgmStop(){
	if(bgmChannel != NULL)
		FMOD_Channel_Stop(bgmChannel);
	return true;
}

bool ModuleIrisAudio::BgsPlay(wstring filePath, int volume, int rate){
	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (bgsChannel != NULL){
			BOOL isPlaying;
			FMOD_Channel_IsPlaying(bgsChannel, &isPlaying);
			if (isPlaying)
				FMOD_Channel_Stop(bgsChannel);
		}
	}

	FMOD_RESULT result;

	result = FMOD_System_CreateStream(fmodSystem, fpath, FMOD_DEFAULT, 0, &bgs);
	if (result != FMOD_OK)
		return false;

	result = FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, bgs, true, &bgsChannel);
	if (result != FMOD_OK)
		return false;

	FMOD_Channel_SetMode(bgsChannel, FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(bgsChannel, volume / 100.0f);

	float frequancy;

	FMOD_Channel_GetFrequency(bgsChannel, &frequancy);
	FMOD_Channel_SetFrequency(bgsChannel, frequancy * (rate / 100.0));
	FMOD_Channel_SetPaused(bgsChannel, FALSE);

	return true;
}

bool ModuleIrisAudio::BgsFade(int fadeTime){
	return true;
}

bool ModuleIrisAudio::BgsStop(){
	if(bgsChannel != NULL)
		FMOD_Channel_Stop(bgsChannel);
	return true;
}

bool ModuleIrisAudio::SePlay(wstring filePath, int volume, int rate){
	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (seChannel != NULL){
			BOOL isPlaying;
			FMOD_Channel_IsPlaying(seChannel, &isPlaying);
			if (isPlaying)
				FMOD_Channel_Stop(seChannel);
		}
	}

	FMOD_RESULT result;

	result = FMOD_System_CreateStream(fmodSystem, fpath, FMOD_DEFAULT, 0, &se);
	if (result != FMOD_OK)
		return false;

	result = FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, se, true, &seChannel);
	if (result != FMOD_OK)
		return false;

	FMOD_Channel_SetMode(seChannel, FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(seChannel, volume / 100.0f);

	float frequancy;

	FMOD_Channel_GetFrequency(seChannel, &frequancy);
	FMOD_Channel_SetFrequency(seChannel, frequancy * (rate / 100.0));
	FMOD_Channel_SetPaused(seChannel, FALSE);

	return true;
}

bool ModuleIrisAudio::SeStop(){
	if(seChannel != NULL)
		FMOD_Channel_Stop(seChannel);
	return true;
}

bool ModuleIrisAudio::MePlay(wstring filePath, int volume, int rate){
	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (meChannel != NULL){
			BOOL isPlaying;
			FMOD_Channel_IsPlaying(meChannel, &isPlaying);
			if (isPlaying)
				FMOD_Channel_Stop(meChannel);
		}
	}

	FMOD_RESULT result;

	result = FMOD_System_CreateStream(fmodSystem, fpath, FMOD_DEFAULT, 0, &me);
	if (result != FMOD_OK)
		return false;

	result = FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, me, true, &meChannel);
	if (result != FMOD_OK)
		return false;

	FMOD_Channel_SetMode(meChannel, FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(meChannel, volume / 100.0f);

	float frequancy;

	FMOD_Channel_GetFrequency(meChannel, &frequancy);
	FMOD_Channel_SetFrequency(meChannel, frequancy * (rate / 100.0));
	FMOD_Channel_SetPaused(meChannel, FALSE);

	return true;
}

bool ModuleIrisAudio::MeStop(){
	if(meChannel != NULL)
		FMOD_Channel_Stop(meChannel);
	return true;
}
#endif

#ifdef _MSC_VER
bool ModuleIrisAudio::InitAudio(int cs){

	channels = cs;
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmodSystem);		// Create the main system object.
	if (result != FMOD_OK)
	{
		return false;
	}
	result = fmodSystem->init(channels, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK)
	{
		return false;
	}
	return true;
}

bool ModuleIrisAudio::ReleaseAudio(){
	FMOD_RESULT result = fmodSystem->release();
	return (result == FMOD_OK ? true : false);
}

bool ModuleIrisAudio::BgmPlay(wstring filePath, int volume, int rate){

	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (bgmChannel != NULL){
			bool isPlaying;
			bgmChannel->isPlaying(&isPlaying);
			if (isPlaying)
				bgmChannel->stop();
		}
	}

	FMOD_RESULT result;

	result = fmodSystem->createStream(fpath, FMOD_DEFAULT, 0, &bgm);
	if (result != FMOD_OK)
		return false;

	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, bgm, true, &bgmChannel);
	if (result != FMOD_OK)
		return false;

	bgmChannel->setMode(FMOD_LOOP_NORMAL);;
	bgmChannel->setVolume(volume / 100.0);

	float frequancy;

	bgmChannel->getFrequency(&frequancy);
	bgmChannel->setFrequency(frequancy * (rate / 100.0));
	bgmChannel->setPaused(false);

	return true;
}

bool ModuleIrisAudio::BgmFade(int fadeTime){
	return true;
}

bool ModuleIrisAudio::BgmStop(){
	if (bgmChannel != NULL)
		bgmChannel->stop();
	return true;
}

bool ModuleIrisAudio::BgsPlay(wstring filePath, int volume, int rate){

	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	if (channels == 0){
		if (bgsChannel != NULL){
			bool isPlaying;
			bgsChannel->isPlaying(&isPlaying);
			if (isPlaying)
				bgsChannel->stop();
		}
	}

	FMOD_RESULT result;

	result = fmodSystem->createStream(fpath, FMOD_DEFAULT, 0, &bgs);
	if (result != FMOD_OK)
		return false;

	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, bgs, true, &bgsChannel);
	if (result != FMOD_OK)
		return false;

	bgsChannel->setMode(FMOD_LOOP_NORMAL);;
	bgsChannel->setVolume(volume / 100.0);

	float frequancy;

	bgsChannel->getFrequency(&frequancy);
	bgsChannel->setFrequency(frequancy * (rate / 100.0));
	bgsChannel->setPaused(false);

	return true;
}

bool ModuleIrisAudio::BgsFade(int fadeTime){
	return true;
}

bool ModuleIrisAudio::BgsStop(){
	if (bgsChannel != NULL)
		bgsChannel->stop();
	return true;
}

bool ModuleIrisAudio::SePlay(wstring filePath, int volume, int rate){

	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	float frequency;
	bool playing;
	seChannel->isPlaying(&playing);
	if (channels == 0){
		if (seChannel != NULL){
			seChannel->isPlaying(&playing);
			if (playing == true){
				seChannel->stop();
			}
		}
	}

	FMOD_RESULT result;

	result = fmodSystem->createSound(fpath, FMOD_HARDWARE, 0, &se);
	if (result != FMOD_OK){
		return false;
	}
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, se, true, &seChannel);
	if (result != FMOD_OK){
		return false;
	}
	se->setMode(FMOD_LOOP_OFF);
	seChannel->setVolume(volume / 100.0);
	seChannel->getFrequency(&frequency);
	seChannel->setFrequency(frequency * (rate / 100.0));
	seChannel->setPaused(false);
	return true;
}

bool ModuleIrisAudio::SeStop(){
	if (seChannel != NULL)
		seChannel->stop();
	return true;
}

bool ModuleIrisAudio::MePlay(wstring filePath, int volume, int rate){

	string sfilepath = WStringToString(filePath);
	const char* fpath = sfilepath.c_str();

	float frequency;
	bool playing;
	meChannel->isPlaying(&playing);
	if (channels == 0){
		if (meChannel != NULL){
			meChannel->isPlaying(&playing);
			if (playing == true){
				meChannel->stop();
			}
		}
	}

	FMOD_RESULT result;

	result = fmodSystem->createSound(fpath, FMOD_HARDWARE, 0, &me);
	if (result != FMOD_OK){
		return false;
	}
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, me, true, &meChannel);
	if (result != FMOD_OK){
		return false;
	}
	me->setMode(FMOD_LOOP_OFF);
	meChannel->setVolume(volume / 100.0);
	meChannel->getFrequency(&frequency);
	meChannel->setFrequency(frequency * (rate / 100.0));
	meChannel->setPaused(false);
	return true;
}

bool ModuleIrisAudio::MeStop(){
	if (meChannel != NULL)
		meChannel->stop();
	return true;
}
#endif
