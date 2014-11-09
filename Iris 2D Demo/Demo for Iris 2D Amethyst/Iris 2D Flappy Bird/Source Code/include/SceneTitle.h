#ifndef _H_SCENETITLE_
#define _H_SCENETITLE_

#include "GameResource.h"
#include "SceneGame.h"
#include "SceneBase.h"
#include "Iris 2D Library.h"
#include <fstream>

class SceneTitle : public SceneBase
{
private:

	IIrisSprite* spriteBackground;
	//IIrisSprite* spriteGround;
	IIrisSprite* spriteHint;

public:
	SceneTitle();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreUpdate();
	virtual ~SceneTitle();
};
#endif