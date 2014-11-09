#include "SpriteScore.h"


SpriteScore::SpriteScore()
{
	spriteScore = GetIrisSprite();
	bitmapScoreFont = GetIrisBitmap(IMAGE_SCOREFONT);
	spriteScore->SetBitmap(GetIrisBitmap(FONT_WIDTH * 4, FONT_HEIGHT));

	spriteScore->SetX(WINDOW_WIDTH / 2);
	spriteScore->SetY(40);
}

void SpriteScore::DrawScore(){
	int digitNum = 0;
	int digit;
	int nowScore = SceneBase::NowScore;

	IIrisRect* rect = GetIrisRect(0, 0, FONT_WIDTH, FONT_HEIGHT);

	do {
		nowScore /= 10;
		++digitNum;
	} while (nowScore != 0);

	nowScore = SceneBase::NowScore;
	int i = 1;
	do {
		digit = nowScore % 10;
		nowScore /= 10;
		rect->SetX((digit % 5) * FONT_WIDTH);
		rect->SetY((digit / 5) * FONT_HEIGHT);
		spriteScore->GetBitmap()->Blt((digitNum - i) * FONT_WIDTH, 0, bitmapScoreFont, rect, 255);
		++i;
	} while (nowScore != 0);

	int realWidth = digitNum * FONT_WIDTH;

	spriteScore->SetX((WINDOW_WIDTH - realWidth) / 2);
}

void SpriteScore::Dispose(){
	bitmapScoreFont->Dispose();
	spriteScore->GetBitmap()->Dispose();
	spriteScore->Dispose();
}

SpriteScore::~SpriteScore()
{
}
