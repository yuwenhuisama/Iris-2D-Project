#include "IrisRect.h"

IrisRect::IrisRect(){
	x = y = width = height = 0.0f;
}

void IrisRect::SetInitData(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}

IrisRect::IrisRect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}

void IrisRect::Set(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}

IrisRect::~IrisRect(void)

{
}
