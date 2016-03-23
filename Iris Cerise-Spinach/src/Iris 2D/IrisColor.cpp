#include "Iris 2D/IrisColor.h"

namespace Iris2D{

	using namespace Gdiplus;

	IrisColor::IrisColor(){
		red = green = blue = alpha = 0;
	}

	void IrisColor::SetInitData(int red, int green, int blue, int alpha){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}


	IrisColor::IrisColor(int red, int green, int blue, int alpha = 255){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}


	void IrisColor::Set(int red, int green, int blue, int alpha){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	IrisColor::~IrisColor(void)
	{
	}
}