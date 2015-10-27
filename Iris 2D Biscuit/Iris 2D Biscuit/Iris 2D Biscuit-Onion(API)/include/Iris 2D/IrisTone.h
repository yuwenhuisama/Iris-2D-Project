/************************************************************************
*
* Header File Name: IrisTone
* Class Name : IrisTone
* Function : This class can symbol tone to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/

#ifndef _IRISTONE_H_
#define _IRISTONE_H_

//#include "Iris2D.h"
#include "Iris 2D Library.h"
#include "Iris2DSupports.h"

namespace Iris2D{

	class IrisTone : public IIrisTone
	{
	private:
		int red, green, blue, alpha;
	public:

		CPP_GETTER_SETTER(Red, red, int)
		CPP_GETTER_SETTER(Green, green, int)
		CPP_GETTER_SETTER(Blue, blue, int)
		CPP_GETTER_SETTER(Alpha, alpha, int)

		IrisTone();
		IrisTone(int red, int green, int blue, int alpha = 0);

		void SetInitData(int red, int green, int blue, int alpha);

		void set(int red, int green, int blue);
		void set(int red, int green, int blue, int alpha);

		friend class IrisBitmap;
		friend class IrisViewport;

		~IrisTone(void);
	};
}
#endif
