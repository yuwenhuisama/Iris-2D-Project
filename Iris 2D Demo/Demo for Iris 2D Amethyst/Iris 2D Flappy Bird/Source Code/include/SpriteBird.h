#ifndef _H_SPRITEBIRD_
#define _H_SPRITEBIRD_

#include "Windows.h"
#include "Iris 2D Library.h"
#include "GameResource.h"

class SpriteBird
{
private:
	IIrisSprite* birdSprite;
	IIrisBitmap* srcBird;
	int flyTime;
	int speed;
	IIrisRect* birdRect;

public:
	SpriteBird();
	void Update();
	void Dispose();
	IIrisRect* GetBirdRect() const;
	IIrisBitmap* GetBirdBitmap() const;

	~SpriteBird();
};

#endif