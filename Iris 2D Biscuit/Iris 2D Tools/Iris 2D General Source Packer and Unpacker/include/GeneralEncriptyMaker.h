#ifndef _H_XMLENCRIPTYMAKERANDDEMAKER_
#define _H_XMLENCRIPTYMAKERANDDEMAKER_

#include "GeneralEncriptyDefines.h"

class GeneralEncriptyMaker
{
protected:

	GeneralVectorString m_vcFilePaths;
	GeneralVectorXmlHeader m_vcXmlHeaders;
	GeneralPackageHeader m_xphHeader;

	int m_nWholeFilePathLength;
	int m_nPreGraphLength;
	int m_nRecordedGraphLength;
	int m_nCmpedSize;

	HANDLE m_hTmpFile;

	GeneralSafetyFunc m_pfEncodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

	string m_strPackageName;
	string m_strFolderName;

protected:

	static void EncodeWriteProcess(HANDLE hFile, const char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2);

	void _MakeHeader();

	void _FilePathCut(string& strFullPath);
	int _CalcGraphOffLength(int nCurLength);

	bool _PathRecord(const char* lpPath);
	bool _FileProcess(const char* lpFilePath);

	bool _IndexAndFilePathDataMake();

	bool _WriteFile();

public:
	GeneralEncriptyMaker();
	bool MakePackage(string& strPackageName, string& strFolderName, DWORD dwKey1, DWORD dwKey2, GeneralSafetyFunc pfEncodeFunc);

	~GeneralEncriptyMaker();
};

#endif