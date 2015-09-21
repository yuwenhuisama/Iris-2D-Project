#ifndef _H_SCENEGAME_
#define _H_SCENEGAME_

#include "SceneBase.h"
#include "SpriteBird.h"
#include "SpriteMap.h"
#include "SpriteScore.h"
#include "SceneGameOver.h"

class SceneGame : public SceneBase
{
private:
	SpriteBird* bird;
	SpriteMap* map;
	SpriteScore* score;
	IIrisSprite* spriteBackground;

public:
	SceneGame();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreUpdate();
	~SceneGame();
};
#endif