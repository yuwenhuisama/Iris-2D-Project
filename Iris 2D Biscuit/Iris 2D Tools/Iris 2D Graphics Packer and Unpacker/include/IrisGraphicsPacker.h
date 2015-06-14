#include "defines.h"
#ifndef _H_IRISGRAPHICSPACKER_
#define _H_IRISGRAPHICSPACKER_

class IrisGraphicsPacker
{
protected:
	string m_strPackageName;
	string m_strGraphFolderName;

	IrisGraphicsPackageHeader m_irphHeader;

	VectorString m_vcFilePaths;
	VectorGraphicsGraphHeader m_vcGraphHeaders;
	int m_nWholeFilePathLength;
	int m_nPreGraphLength;
	int m_nRecordedGraphLength;
	int m_nCmpedSize;

	HANDLE m_hTmpFile;

	SafetyFunc m_pfEncodeFunc;

	DWORD m_dwKey1;
	DWORD m_dwKey2;

protected:
	void _MakeHeader();

	void _FilePathCut(string& strFullPath);
	int _CalcGraphOffLength(int nCurLength);

	bool _PathRecord(const char* lpPath);
	bool _FileProcess(const char* lpFilePath);

	bool _IndexAndFilePathDataMake();

	bool _WriteFile();

public:

	bool MakePackage(string& strPackageName, string& strGraphFolderName, DWORD dwKey1 = 0x0000000, DWORD dwKey2 = 0x0000000, SafetyFunc pfEncodeFunc = NULL);

	IrisGraphicsPacker();
	~IrisGraphicsPacker();
};

#endif;