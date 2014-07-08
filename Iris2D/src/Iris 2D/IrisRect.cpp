#include "IrisRect.h"


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

Rect* IrisRect::Conver2GDIRect(){
	Rect *rect = new Rect((int)this->x, (int)this->y, (int)this->width, (int)this->height);
	return rect;
}

IrisRect::~IrisRect(void)

{
}
