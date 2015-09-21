#include "SceneBase.h"

SceneBase* SceneBase::CurScene = 0;
int SceneBase::NowScore = 0;
int SceneBase::MaxScore = 0;

SceneBase::SceneBase()
{
}

void SceneBase::Main(){

	PreUpdate();
	while (true) {
		IrisGraphicsUpdate();
		IrisInputUpdate();
		Update();
		if (CurScene != this || GetIrisApp()->IsQuited()){
			break;
		}
	}
	PostUpdate();
	delete this;

}

void SceneBase::PreUpdate() {

}

void SceneBase::PostUpdate() {

}

SceneBase::~SceneBase()
{

}
