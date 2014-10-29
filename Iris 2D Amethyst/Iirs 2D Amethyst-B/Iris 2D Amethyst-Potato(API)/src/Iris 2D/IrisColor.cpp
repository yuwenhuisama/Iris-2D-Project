#include "IrisColor.h"
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

void IrisColor::set(int red, int green, int blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void IrisColor::set(int red, int green, int blue, int alpha){
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

IrisColor::~IrisColor(void)
{
}
