#ifndef _H_GENERALENCRIPTYSOURCEEXTRACT_
#define _H_GENERALENCRIPTYSOURCEEXTRACT_
#include "GeneralEncriptyDefines.h"
class GeneralEncriptySourceExtract
{
protected:

	GeneralPackageHeader m_xphHeader;

	GeneralVectorString m_vcFilePaths;
	GeneralVectorXmlHeader m_vcXmlHeaders;
	MapStringGeneralHeader m_mpFileNameGeneralData;

	HANDLE m_hPackageFile;

	GeneralSafetyFunc m_pfDecodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

protected:
	void _CheckMakePath(char* pFileName);

	bool _ReadPackageHeader();
	bool _EssensialDataProcess();

	static void DecodeWriteProcess(char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2);

public:

	bool InitPackageData(string& strPackagePath, GeneralSafetyFunc pfDecodeFunc = NULL);
	bool GetGeneralData(string strFilePath, char** ppData, int* pSize);
	bool IsHaveFile(string strFilePath);

public:
	GeneralEncriptySourceExtract();
	~GeneralEncriptySourceExtract();
};

#endif