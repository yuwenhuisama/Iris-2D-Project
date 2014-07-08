#include "IrisTone.h"

IrisTone::IrisTone(int red, int green, int blue, int alpha = 0){
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
