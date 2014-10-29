/************************************************************************
*
* Header File Name: IrisFont
* Class Name : IrisFont
* Function : This class can symbol font to use in this engine.
* Complite Tick: Unkown
* Compliter : Hui
* Dialogure Log :
*    2014.01.02 : Add this introduction.
*
*************************************************************************/
#ifndef _IRISFONT_H_
#define _IRISFONT_H_

#include "Iris2D.h"

class IrisFont : public IIrisFont
{
private:
	wstring name;
	int size;
	bool bold;
	bool italic;
	bool shadow;
	IIrisColor *color;

public:
	IrisFont(wstring name, int size = -1);

	IrisFont();
	void SetInitData(wstring name, int size = -1);

	static bool Existed(wstring name);
	static int CALLBACK EnumFontsProc(
		LOGFONT*    lplf,
		TEXTMETRIC* lptm,
		DWORD	 dwType,
		LPARAM	 lpData
		);

	static wstring defaultName;
	static int defaultSize;
	static bool defaultBold;
	static bool defaultItalic;
	static bool defaultShadow;
	static IIrisColor *defaultColor;

	CPP_GETTER_SETTER(Name, name, wstring)
	CPP_GETTER_SETTER(Size, size, int)
	CPP_GETTER_SETTER(Bold, bold, bool)
	CPP_GETTER_SETTER(Italic, italic, bool)
	CPP_GETTER_SETTER(Shadow, shadow, bool)
	CPP_GETTER_SETTER(Color, color, IIrisColor*)

	friend class IrisBitmap;


	~IrisFont(void);
};
#endif
