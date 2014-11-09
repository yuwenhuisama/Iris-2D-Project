#include "SpriteBird.h"

SpriteBird::SpriteBird()
{
	srcBird = GetIrisBitmap(IMAGE_BIRD);
	birdSprite = GetIrisSprite();

	birdSprite->SetBitmap(GetIrisBitmap(40, 40));

	birdSprite->SetX(150.0f);
	birdSprite->SetY(185.0f);

	birdRect = GetIrisRect(150.0f, 185.0f, 40.0f, 40.0f);

	flyTime = 2;
	speed = 0;
}

IIrisBitmap* SpriteBird::GetBirdBitmap() const {
	return this->birdSprite->GetBitmap();
}

IIrisRect* SpriteBird::GetBirdRect() const {
	this->birdRect->SetY(this->birdSprite->GetY());
	return this->birdRect;
}

void SpriteBird::Update(){
	++flyTime;
	flyTime = flyTime % 3;

	birdSprite->GetBitmap()->Clear();
	IIrisRect* rect = GetIrisRect(flyTime * 40, 0, 40, 40);
	birdSprite->GetBitmap()->Blt(0, 0, srcBird, rect, 255);
	ReleaseIrisRect(rect);

	++speed;

	if (IrisInputMouseTrigger(Left)){
		speed = -8;
	}

	birdSprite->SetY(birdSprite->GetY() + speed);
}

void SpriteBird::Dispose(){
	ReleaseIrisRect(birdRect);
	srcBird->Dispose();
	birdSprite->GetBitmap()->Dispose();
	birdSprite->Dispose();
}

SpriteBird::~SpriteBird()
{
	ReleaseIrisBitmap(srcBird);
	ReleaseIrisSprite(birdSprite);
}
