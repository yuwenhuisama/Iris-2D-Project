#include "IrisTone.h"

namespace Iris2D{
	IrisTone::IrisTone(){
		red = green = blue = alpha = 0;
	}

	void IrisTone::SetInitData(int red, int green, int blue, int alpha){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	IrisTone::IrisTone(int red, int green, int blue, int alpha){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	void IrisTone::set(int red, int green, int blue){
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	void IrisTone::set(int red, int green, int blue, int alpha){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	IrisTone::~IrisTone(void)
	{
	}
}