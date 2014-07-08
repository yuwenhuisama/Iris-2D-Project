#include "IrisFont.h"

wstring IrisFont::defaultName = L"ËÎÌו";
int IrisFont::defaultSize = 20;
bool IrisFont::defaultBold = false;
bool IrisFont::defaultItalic = false;
bool IrisFont::defaultShadow = false;
IrisColor *IrisFont::defaultColor = new IrisColor(255, 255, 255, 255);

IrisFont::IrisFont(wstring name)
{
	this->italic = IrisFont::defaultItalic;
	this->bold = IrisFont::bold;
	this->color = IrisFont::color;
	this->name = name;
	this->shadow = IrisFont::defaultShadow;
	this->size = IrisFont::defaultSize;
}

int CALLBACK IrisFont::EnumFontsProc(LOGFONT* lplf, TEXTMETRIC* lptm, DWORD dwType, LPARAM lpData){
	return 1;
}

IrisFont::IrisFont(wstring name, int size){
	this->italic = IrisFont::defaultItalic;
	this->bold = IrisFont::bold;
	this->color = IrisFont::color;
	this->name = name;
	this->shadow = IrisFont::defaultShadow;
	this->size = size;
}

bool IrisFont::Existed(wstring name){
	LPARAM  lp = 0;
	lp = EnumFonts(NULL, name.c_str(), (FONTENUMPROC)EnumFontsProc, lp);

	if (lp == 0){
		return false;
	}
	else {
		return true;
	}
}

IrisFont::~IrisFont(void)
{
}
