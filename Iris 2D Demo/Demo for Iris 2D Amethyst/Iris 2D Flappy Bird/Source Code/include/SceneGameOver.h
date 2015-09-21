#ifndef _H_SCENEGAMEOVER_
#define _H_SCENEGAMEOVER_

#include "Windows.h"
#include "Iris 2D Library.h"
#include "GameResource.h"
#include "SceneBase.h"
#include "SceneGame.h"
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class SceneGameOver : public SceneBase
{
private:
	IIrisSprite* spriteBackground;
	IIrisSprite* spriteContent;
	IIrisSprite* spritePoint;

public:
	SceneGameOver();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreUpdate();
	~SceneGameOver();
};
#endif