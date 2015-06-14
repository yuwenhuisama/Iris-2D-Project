#include "IrisFont.h"

namespace Iris2D{

	wstring IrisFont::defaultName = L"ËÎÌו";
	int IrisFont::defaultSize = 20;
	bool IrisFont::defaultBold = false;
	bool IrisFont::defaultItalic = false;
	bool IrisFont::defaultShadow = false;
	IrisColor *IrisFont::defaultColor = new IrisColor(255, 255, 255, 255);

	IrisFont::IrisFont(){
		this->italic = false;
		this->bold = false;
		this->color = new IrisColor(*IrisFont::color);
		this->name = L"ËÎÌו";
		this->shadow = false;
		this->size = 20;
	}

	void IrisFont::SetInitData(wstring name, int size){
		this->italic = IrisFont::defaultItalic;
		this->bold = IrisFont::bold;
		this->color = new IrisColor(*IrisFont::color);
		this->name = name;
		this->shadow = IrisFont::defaultShadow;
		this->size = size < 0 ? IrisFont::defaultSize : size;
	}

	IrisColor* IrisFont::GetColor(){
		return this->color;
	}

	void IrisFont::SetColor(IrisColor* color, bool isReleased){
		if (this->color && isReleased){
			delete this->color;
		}
		this->color = color;
	}

	IrisFont::IrisFont(wstring name, int size)
	{
		this->italic = IrisFont::defaultItalic;
		this->bold = IrisFont::bold;
		this->color = new IrisColor(*IrisFont::defaultColor);
		this->name = name;
		this->shadow = IrisFont::defaultShadow;
		this->size = size < 0 ? IrisFont::defaultSize : size;
	}

	int CALLBACK IrisFont::EnumFontsProc(LOGFONT* lplf, TEXTMETRIC* lptm, DWORD dwType, LPARAM lpData){
		return 1;
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
}