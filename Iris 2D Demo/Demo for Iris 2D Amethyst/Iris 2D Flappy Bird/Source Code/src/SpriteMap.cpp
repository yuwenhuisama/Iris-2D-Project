#include "SpriteMap.h"


SpriteMap::SpriteMap()
{
	map1 = GetIrisSprite();
	map2 = GetIrisSprite();
	map2->SetX(MAP_WIDTH);

	map1->SetBitmap(GetIrisBitmap(MAP_WIDTH, MAP_HEIGHT));
	map2->SetBitmap(GetIrisBitmap(MAP_WIDTH, MAP_HEIGHT));

	frontMap = &map1;
	lastMap = &map2;

	topPipeBitmap = GetIrisBitmap(IMAGE_PIPE_TOP);
	bottomPipeBitmap = GetIrisBitmap(IMAGE_PIPE_BOTTOM);

	srand((unsigned)GetTickCount());

	MakeRandMap(map2->GetBitmap());
}

int SpriteMap::RandFromTo(int from, int to){
	return (int)(rand() * 1.0f / RAND_MAX * (float)(to - from) + (float)from);
}

void SpriteMap::MakeRandMap(IIrisBitmap* mapBit){

	mapBit->Clear();

	int topHeight = topPipeBitmap->GetHeight();
	int bottomHeight = bottomPipeBitmap->GetHeight();

	int topPipeHeight = RandFromTo(MIN_PIPE_HEIGHT, MAX_PIPE_HEIGHT);
	int bottomPipeHeight = OTHER_PIPE_HEIGHT(topPipeHeight);

	/* Make First Top Pipe Begin */
	IIrisRect* rect = GetIrisRect(0, topHeight - topPipeHeight, PIPE_WIDTH, topPipeHeight);
	mapBit->Blt(FIRST_PIPE_X, 0, topPipeBitmap, rect, 255);
	/* Make First Top Pipe End */

	/* Make First Bottom Pipe Start */
	rect->Set(0, 0, PIPE_WIDTH, bottomPipeHeight);
	mapBit->Blt(FIRST_PIPE_X, MAP_HEIGHT - bottomPipeHeight, bottomPipeBitmap, rect, 255);
	/* Make First Bottom Pipe End */
	Pipe pipes1 = { MAP_WIDTH + FIRST_PIPE_X, topPipeHeight, bottomPipeHeight };
	pipes.push_back(pipes1);

	topPipeHeight = RandFromTo(MIN_PIPE_HEIGHT, MAX_PIPE_HEIGHT);
	bottomPipeHeight = OTHER_PIPE_HEIGHT(topPipeHeight);

	/* Make Second Top Pipe Begin */
	rect->Set(0, topHeight - topPipeHeight, PIPE_WIDTH, topPipeHeight);
	mapBit->Blt(SECOND_PIPE_X, 0, topPipeBitmap, rect, 255);
	/* Make First Top Pipe End */

	/* Make Second Bottom Pipe Start */
	rect->Set(0, 0, PIPE_WIDTH, bottomPipeHeight);
	mapBit->Blt(SECOND_PIPE_X, MAP_HEIGHT - bottomPipeHeight, bottomPipeBitmap, rect, 255);
	/* Make First Bottom Pipe End */
	Pipe pipes2 = { MAP_WIDTH + SECOND_PIPE_X, topPipeHeight, bottomPipeHeight };
	pipes.push_back(pipes2);

	ReleaseIrisRect(rect);
}

void SpriteMap::Update(){
	deque<Pipe>::iterator it;
	for (it = pipes.begin(); it != pipes.end(); ++it){
		(*it).x -= 5;
	}
	
	map1->SetX(map1->GetX() - 5);
	map2->SetX(map2->GetX() - 5);

	IIrisSprite** temp;
	if ((*lastMap)->GetX() == 0){
		temp = frontMap;
		frontMap = lastMap;
		lastMap = temp;

		(*lastMap)->SetX(MAP_WIDTH);
		MakeRandMap((*lastMap)->GetBitmap());
	}
}

void SpriteMap::Dispose(){
	pipes.clear();

	map1->GetBitmap()->Dispose();
	map1->Dispose();

	map2->GetBitmap()->Dispose();
	map2->Dispose();

	topPipeBitmap->Dispose();
	bottomPipeBitmap->Dispose();
}

bool SpriteMap::FirstPipeRectIntersectWith(IIrisRect* rect, PipeType type){
	IIrisRect* pipeTopRect = GetIrisRect(pipes.front().x, 0, 
		PIPE_WIDTH, pipes.front().heightTop);
	IIrisRect* pipeBottomRect = GetIrisRect(pipes.front().x, MAP_HEIGHT - pipes.front().heightBottom,
		PIPE_WIDTH, pipes.front().heightBottom);

	bool flag = false;

	/* Top Intersection */
	if (type == Top){
		if (!((rect->GetX() + rect->GetWidth() < pipeTopRect->GetX())
			|| (rect->GetY() > pipeTopRect->GetY() + pipeTopRect->GetHeight())
			|| (rect->GetX() > pipeTopRect->GetX() + PIPE_WIDTH))){
			flag = true;
		}
	}
	/* Bottom Intersection */
	else{
		if (!((rect->GetX() + rect->GetWidth() < pipeBottomRect->GetX())
			|| (rect->GetY() + rect->GetHeight() < pipeBottomRect->GetY())
			|| (rect->GetX() > pipeBottomRect->GetX() + PIPE_WIDTH))){
			flag = true;
		}
	}

	ReleaseIrisRect(pipeTopRect);
	ReleaseIrisRect(pipeBottomRect);

	return flag;
}

bool SpriteMap::FirstPipeTouch(SpriteBird* bird){
	int destLeft, destRight, destTop, destBottom;
	int srcLeft, srcRight, srcTop, srcBottom;
	int iLeft, iRight, iTop, iBottom;

	srcLeft = pipes.front().x, srcRight = pipes.front().x + PIPE_WIDTH;
	if (FirstPipeRectIntersectWith(bird->GetBirdRect(), Top)) {
		srcTop = 0, srcBottom = pipes.front().heightTop;
	}
	else if (FirstPipeRectIntersectWith(bird->GetBirdRect(), Bottom)){
		srcTop = MAP_HEIGHT - pipes.front().heightBottom, srcBottom = MAP_HEIGHT;
	}
	else {
		return false;
	}

	destLeft = bird->GetBirdRect()->GetX(), destRight = bird->GetBirdRect()->GetX() + bird->GetBirdRect()->GetWidth(),
		destTop = bird->GetBirdRect()->GetY(), destBottom = bird->GetBirdRect()->GetY() + bird->GetBirdRect()->GetHeight();

	/* intersect rect */
	iLeft = destLeft > srcLeft ? destLeft : srcLeft;
	iRight = destRight > srcRight ? srcRight : destRight;
	iTop = destTop > srcTop ? destTop : srcTop;
	iBottom = destBottom > srcBottom ? srcBottom : destBottom;

	/* pixel check */
	int rectWidth = iRight - iLeft;
	int rectHeight = iBottom - iTop;
	IIrisBitmap* bmp1 = GetIrisBitmap(rectWidth, rectHeight);
	IIrisBitmap* bmp2 = GetIrisBitmap(rectWidth, rectHeight);
	IIrisRect* rectInBirdBitmap = GetIrisRect(iLeft - bird->GetBirdRect()->GetX(), iTop - bird->GetBirdRect()->GetY(),
		rectWidth, rectHeight);
	int left = iLeft - (*frontMap)->GetX();
	IIrisSprite** nowMap = frontMap;
	if ((*lastMap)->GetX() < iLeft){
		left = iLeft - (*lastMap)->GetX();
		nowMap = lastMap;
	}
	IIrisRect* rectInMapBitmap = GetIrisRect(left, iTop - (*nowMap)->GetY(),
		rectWidth, rectHeight);

	bmp1->Blt(0, 0, bird->GetBirdBitmap(), rectInBirdBitmap, 255);
	bmp2->Blt(0, 0, (*nowMap)->GetBitmap(), rectInMapBitmap, 255);
	bool flag = false;

	for (int i = 0; i < rectWidth; ++i){
		for (int j = 0; j < rectHeight; ++j){
			if (bmp1->GetPixel(i, j)->GetAlpha() != 0 &&
				bmp2->GetPixel(i, j)->GetAlpha() != 0)
				flag = true;
		}
	}

	ReleaseIrisRect(rectInBirdBitmap);
	ReleaseIrisRect(rectInMapBitmap);
	ReleaseIrisBitmap(bmp1);
	ReleaseIrisBitmap(bmp2);

	return flag;

}

bool SpriteMap::FirstPipesXOverPostion(int x){
	return pipes.front().x + PIPE_WIDTH < x;
}

void SpriteMap::RemoveFirstPipes(){
	pipes.pop_front();
}

SpriteMap::~SpriteMap()
{
	ReleaseIrisSprite(map1);
	ReleaseIrisSprite(map2);
	ReleaseIrisBitmap(topPipeBitmap);
	ReleaseIrisBitmap(bottomPipeBitmap);
}
