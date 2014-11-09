#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
}

void SceneGameOver::Update(){
	if (IrisInputMouseTrigger(Left)){
		IIrisRect* rect = GetIrisRect(130, 285, 155, 90);
		if (IrisInputCursorInRect(rect)){
			SceneBase::CurScene = new SceneGame();
			ReleaseIrisRect(rect);
			return;
		}
		else
		{
			rect->Set(310, 285, 155, 90);
			if (IrisInputCursorInRect(rect)){
				::MessageBox(0, MESSAGE_CONTENT, MESSAGE_TITLE, 0);
				ReleaseIrisRect(rect);
				return;
			}
		}
	}
}

void SceneGameOver::PostUpdate(){
	spriteBackground->GetBitmap()->Dispose();
	spriteBackground->Dispose();
	spriteContent->GetBitmap()->Dispose();
	spriteContent->Dispose();
	spritePoint->GetBitmap()->Dispose();
	spritePoint->Dispose();
}

void SceneGameOver::PreUpdate(){

	fstream file(POINT_FILE_NAME, ios::ate | ios::out);
	if (!file){
		file << SceneBase::MaxScore;
	}
	else {
		if (SceneBase::NowScore > SceneBase::MaxScore){
			SceneBase::MaxScore = SceneBase::NowScore;
			file.clear();
			file << SceneBase::MaxScore;
		}
	}
	file.close();

	spriteBackground = GetIrisSprite();
	spriteContent = GetIrisSprite();
	spritePoint = GetIrisSprite();

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

	/* Make Content Begin */
	spriteContent->SetBitmap(GetIrisBitmap(350, 380));
	spriteContent->SetX(125);
	spriteContent->SetY(20);
	
	IIrisBitmap* s1 = GetIrisBitmap(IMAGE_HINT);
	IIrisBitmap* s2 = GetIrisBitmap(IMAGE_SCOREBOARD);
	IIrisBitmap* s3 = GetIrisBitmap(IMAGE_BUTTONS);
	IIrisRect* over = GetIrisRect(0, 80, 300, 80);
	IIrisRect* board = GetIrisRect(0, 0, 349, 180);
	IIrisRect* button = GetIrisRect(0, 0, 350, 105);
	spriteContent->GetBitmap()->Blt(0, 0, s1, over, 255);
	spriteContent->GetBitmap()->Blt(0, 80, s2, board, 255);
	spriteContent->GetBitmap()->Blt(0, 260, s3, button, 255);

	ReleaseIrisBitmap(s1);
	ReleaseIrisBitmap(s2);
	ReleaseIrisBitmap(s3);
	ReleaseIrisRect(over);
	ReleaseIrisRect(board);
	ReleaseIrisRect(button);
	/* Make Content End */

	/* Make Point Start*/
	IIrisBitmap* pointBitmap = GetIrisBitmap(50, 90);

	wostringstream ost1;
	wostringstream ost2;

	ost1 << SceneBase::NowScore;
	ost2 << SceneBase::MaxScore;

	IIrisFont* font = GetIrisFont(POINT_FONT_NAME, 15);
	font->SetColor(GetIrisColor(255, 0, 0, 255));
	font->SetBold(true);

	pointBitmap->IrisDrawText(font, 0, 0, 50, 30, ost1.str(), 0);
	pointBitmap->IrisDrawText(font, 0, 60, 50, 30, ost2.str(), 0);

	spritePoint->SetBitmap(pointBitmap);
	spritePoint->SetX(265);
	spritePoint->SetY(160);

	ReleaseIrisFont(font);
	/* Make Point End*/
}

SceneGameOver::~SceneGameOver()
{
	delete spriteBackground;
	delete spriteContent;
	delete spritePoint;
}
