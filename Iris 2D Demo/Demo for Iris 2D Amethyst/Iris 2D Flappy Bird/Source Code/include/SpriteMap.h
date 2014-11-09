#ifndef _H_SPRITEMAP_
#define _H_SPRITEMAP_

#include "Windows.h"
#include "Iris 2D Library.h"
#include "GameResource.h"
#include "SpriteBird.h"
#include <deque>

using namespace std;

enum PipeType {
	Top = 0,
	Bottom,
};

struct Pipe{
	int x;
	int heightTop;
	int heightBottom;
};

class SpriteMap
{
private:

	IIrisSprite* map1;
	IIrisSprite* map2;

	IIrisSprite** frontMap;
	IIrisSprite** lastMap;

	IIrisBitmap* topPipeBitmap;
	IIrisBitmap* bottomPipeBitmap;

	deque<Pipe> pipes;

	void MakeRandMap(IIrisBitmap* mapBit);

	int RandFromTo(int from, int to);
	int birdPos;

	bool FirstPipeRectIntersectWith(IIrisRect* rect, PipeType type);

public:
	SpriteMap();
	void Update();
	void Dispose();

	bool FirstPipeTouch(SpriteBird* bird);

	bool FirstPipesXOverPostion(int x);
	void RemoveFirstPipes();

	~SpriteMap();
};

#endif