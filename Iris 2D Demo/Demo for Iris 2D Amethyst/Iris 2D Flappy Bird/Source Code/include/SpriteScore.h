#ifndef _H_SPRITESCORE_
#define _H_SPRITESCORE_

#include "GameResource.h"
#include "SceneBase.h"
#include "Windows.h"
#include "Iris 2D Library.h"

class SpriteScore
{
private:
	IIrisBitmap* bitmapScoreFont;
	IIrisSprite* spriteScore;

public:
	SpriteScore();
	void DrawScore();
	void Dispose();
	~SpriteScore();
};

#endif