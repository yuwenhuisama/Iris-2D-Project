#ifndef _H_SCENEBASE_
#define _H_SCENEBASE_

#include "Windows.h"
#include "Iris 2D Library.h"

class SceneBase
{
public:
	static SceneBase* CurScene;
	static int NowScore;
	static int MaxScore;

	SceneBase();
	virtual void PreUpdate() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Main();
	virtual ~SceneBase() = 0;
};

#endif