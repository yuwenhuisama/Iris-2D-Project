/************************************************************************
*
* Header File Name: IrisRect
* Class Name : IrisRect
* Function : This class can symbol rect to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISRECT_H_
#define _IRISRECT_H_
#include "Iris2D.h"

using namespace Gdiplus;

class IrisRect : public IIrisRect
{
private:
	float x, y, width, height;

public:
	CPP_GETTER_SETTER(X, x, float)
	CPP_GETTER_SETTER(Y, y, float)
	CPP_GETTER_SETTER(Height, height, float)
	CPP_GETTER_SETTER(Width, width, float)
	IrisRect();
	void SetInitData(float x, float y, float width, float height);

	IrisRect(float x, float y, float width, float height);

	void Set(float x, float y, float width, float height);

	~IrisRect(void);

	friend class IrisBitmap;
	friend class IrisColor;
	friend class IrisSprite;
	friend class IrisViewport;
	friend class ModuleIrisInput;
};
#endif
