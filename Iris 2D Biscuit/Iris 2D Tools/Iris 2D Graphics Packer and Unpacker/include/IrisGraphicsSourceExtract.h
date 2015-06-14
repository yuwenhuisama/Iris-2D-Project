#ifndef _H_IRISGRAPHICSSOURCEEXTRACT_
#define _H_IRISGRAPHICSSOURCEEXTRACT_

#include "defines.h"

class IrisGraphicsSourceExtract
{
protected:

	IrisGraphicsPackageHeader m_irphHeader;

	VectorString m_vcFilePaths;
	VectorGraphicsGraphHeader m_vcGraphHeaders;
	MapStringGraphicsGraphHeader m_mpFileNameGraphics;

	HANDLE m_hPackageFile;

	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	SafetyFunc m_pfDecodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

protected:
	int _CalcPathNamePos();
	int _CalcGraphPos();

	bool _ReadPackageHeader();
	bool _EssensialDataProcess();

public:

	bool InitPackageData(string strPackagePath, SafetyFunc pfDecodeFunc = NULL);
	bool GetBitmapData(string strFilePath, char** ppData, int* nWidth, int* nHeight);

	IrisGraphicsSourceExtract();
	~IrisGraphicsSourceExtract();
};

#endif