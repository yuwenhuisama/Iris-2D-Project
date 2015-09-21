#include "SceneGame.h"


SceneGame::SceneGame()
{
}

void SceneGame::Update(){
	bird->Update();
	map->Update();

	if (bird->GetBirdRect()->GetY() >= 400
		|| bird->GetBirdRect()->GetY() <= 0){
		SceneBase::CurScene = new SceneGameOver();
		return;
	}
	else {
		if (map->FirstPipesXOverPostion(bird->GetBirdRect()->GetX())){
			map->RemoveFirstPipes();
			++SceneBase::NowScore;
			score->DrawScore();
			return;
		}
		else {
			if (map->FirstPipeTouch(bird)){
				SceneBase::CurScene = new SceneGameOver();
				return;
			}
		}
	}
}

void SceneGame::PostUpdate(){
	bird->Dispose();
	map->Dispose();
	score->Dispose();
	spriteBackground->GetBitmap()->Dispose();
	spriteBackground->Dispose();
}

void SceneGame::PreUpdate(){

	SceneBase::NowScore = 0;

	spriteBackground = GetIrisSprite();

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

	map = new SpriteMap;
	bird = new SpriteBird;
	score = new SpriteScore;
}

SceneGame::~SceneGame()
{
	delete spriteBackground;
	delete bird;
	delete map;
	delete score;
}
