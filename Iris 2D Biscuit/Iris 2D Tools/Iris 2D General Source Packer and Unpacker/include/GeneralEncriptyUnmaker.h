#ifndef _H_XMLENCRIPTYUNMAKER_
#define _H_XMLENCRIPTYUNMAKER_

#include "GeneralEncriptyDefines.h"

class GeneralEncriptyUnmaker
{
protected:

	GeneralPackageHeader m_xphHeader;

	GeneralVectorString m_vcFilePaths;
	GeneralVectorXmlHeader m_vcXmlHeaders;

	HANDLE m_hPackageFile;


	GeneralSafetyFunc m_pfDecodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

protected:
	void _CheckMakePath(char* pFileName);

	bool _ReadPackageHeader();
	bool _EssensialDataProcess();
	bool _UnpackPackage();

	static void DecodeWriteProcess(char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2);

public:
	GeneralEncriptyUnmaker();

	bool UnmakePackage(string& strPackageName, GeneralSafetyFunc pfDecodeFunc = NULL);

	~GeneralEncriptyUnmaker();
};

#endif;