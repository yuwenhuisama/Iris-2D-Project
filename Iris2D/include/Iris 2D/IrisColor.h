/************************************************************************
*
* Header File Name: IrisColor
* Class Name : IrisColor
* Function : This class can symbol color to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISCOLOR_H_
#define _IRISCOLOR_H_

#include "Iris2D.h"
class IrisColor
{
private:
	int red, green, blue, alpha;
public:
	CPP_GETTER_SETTER(Red, red, int);
	CPP_GETTER_SETTER(Green, green, int);
	CPP_GETTER_SETTER(Blue, blue, int);
	CPP_GETTER_SETTER(Alpha, alpha, int);
	IrisColor(int red, int green, int blue, int alpha);

	void set(int red, int green, int blue);
	void set(int red, int green, int blue, int alpha);

	friend class IrisBitmap;
	friend class IrisSprite;

	~IrisColor(void);
};
#endif
