#include "SceneTitle.h"


SceneTitle::SceneTitle()
{
}

void SceneTitle::Update(){
	if (IrisInputMouseTrigger(Left))
		SceneBase::CurScene = new SceneGame;
}

void SceneTitle::PreUpdate(){
	spriteBackground = GetIrisSprite();
	//spriteGround = GetIrisSprite();
	spriteHint = GetIrisSprite();

	/* Make Background  Start */
	IIrisBitmap* srcBG = GetIrisBitmap(IMAGE_BACKGROUND);
	IIrisBitmap* destBG = GetIrisBitmap(WINDOW_WIDTH, WINDOW_HEIGHT);
	IIrisRect* rSRC = GetIrisRect(0, 0, srcBG->GetWidth(), srcBG->GetHeight());
	IIrisRect* tDEST = GetIrisRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	destBG->Clear();
	destBG->StretchBlt(tDEST, srcBG, rSRC, 255);

	ReleaseIrisRect(rSRC);
	ReleaseIrisRect(tDEST);
	ReleaseIrisBitmap(srcBG);

	spriteBackground->SetBitmap(destBG);
	/* Make Background End */

	/* Make Hint Start*/
	IIrisBitmap* hint = GetIrisBitmap(300, 240);

	IIrisBitmap* srcHint = GetIrisBitmap(IMAGE_HINT);
	IIrisRect* srcRStart = GetIrisRect(0, 0, 300, 75);
	IIrisRect* srcRClick = GetIrisRect(0, 170, 300, 150);

	hint->Blt(0, 0, srcHint, srcRStart, 255);
	hint->Blt(30, 80, srcHint, srcRClick, 255);

	ReleaseIrisBitmap(srcHint);
	ReleaseIrisRect(srcRStart);
	ReleaseIrisRect(srcRClick);

	spriteHint->SetBitmap(hint);
	/* Make Hint End */

	spriteHint->SetX(150.0f);
	spriteHint->SetY(60.0f);

	fstream file(POINT_FILE_NAME, ios::app | ios::in);
	if (file){
		file >> SceneBase::MaxScore;
	}
	else {
		SceneBase::MaxScore = 0;
	}
	file.close();

}

void SceneTitle::PostUpdate(){
	spriteBackground->GetBitmap()->Dispose();
	spriteBackground->Dispose();

	spriteHint->GetBitmap()->Dispose();
	spriteHint->Dispose();
}

SceneTitle::~SceneTitle()
{
	ReleaseIrisSprite(spriteBackground);
	ReleaseIrisSprite(spriteHint);
}
