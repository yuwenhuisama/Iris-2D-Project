#include "defines.h"

#ifndef _H_IRISGRAPHICSUNPACKER_
#define _H_IRISGRAPHICSUNPACKER_

class IrisGraphicsUnpacker
{
protected:

	IrisGraphicsPackageHeader m_irphHeader;

	VectorString m_vcFilePaths;
	VectorGraphicsGraphHeader m_vcGraphHeaders;

	HANDLE m_hPackageFile;


	SafetyFunc m_pfDecodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

protected:

	void _CheckMakePath(char* pFileName);

	bool _ReadPackageHeader();
	bool _EssensialDataProcess();
	bool _UnpackPackage();

public:

	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	bool UnmakePackage(string& strPackageName, SafetyFunc pfDecodeFunc = NULL);

	IrisGraphicsUnpacker();
	~IrisGraphicsUnpacker();
};

#endif