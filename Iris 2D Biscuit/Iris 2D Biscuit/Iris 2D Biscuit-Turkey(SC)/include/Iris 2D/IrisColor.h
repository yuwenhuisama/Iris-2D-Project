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

//#include "Iris2D.h"
#include "Iris2DSupports.h"

namespace Iris2D{
	class IrisColor
	{
	protected:
		int red, green, blue, alpha;
	public:
		CPP_GETTER_SETTER(Red, red, int);
		CPP_GETTER_SETTER(Green, green, int);
		CPP_GETTER_SETTER(Blue, blue, int);
		CPP_GETTER_SETTER(Alpha, alpha, int);
		IrisColor(int red, int green, int blue, int alpha);

		IrisColor();
		void SetInitData(int red, int green, int blue, int alpha);

		void Set(int red, int green, int blue, int alpha = 255);

		friend class IrisBitmap;
		friend class IrisSprite;

		~IrisColor(void);
	};
}
#endif
