#include "GeneralEncriptySourceExtract.h"


GeneralEncriptySourceExtract::GeneralEncriptySourceExtract()
{
}

bool GeneralEncriptySourceExtract::InitPackageData(string& strPackageName, GeneralSafetyFunc pfDecodeFunc) {

	m_hPackageFile = 0;
	m_pfDecodeFunc = pfDecodeFunc;
	m_dwKey1 = 0;
	m_dwKey2 = 0;

	m_hPackageFile = ::CreateFileA(strPackageName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (FAILED(m_hPackageFile)){
		cout << "Error when creating file : " << strPackageName.c_str() << endl;
		return false;
	}

	if (!_ReadPackageHeader()) { ::CloseHandle(m_hPackageFile); return false; }
	if (!_EssensialDataProcess()) { ::CloseHandle(m_hPackageFile); return false; }
	
	return true;
}

bool GeneralEncriptySourceExtract::_ReadPackageHeader(){

	::ReadFile(m_hPackageFile, (char*)&m_xphHeader, sizeof(GeneralPackageHeader), 0, 0);
	for (int i = 0; i < sizeof(m_xphHeader.m_szMagic); ++i){
		if (m_xphHeader.m_szMagic[i] != c_szGeneralMagic[i]) return false;
	}
	m_dwKey1 = m_xphHeader.m_dwReserve1;
	m_dwKey2 = m_xphHeader.m_dwReserve2;

	return true;
}

bool GeneralEncriptySourceExtract::_EssensialDataProcess(){

	m_vcXmlHeaders.resize(m_xphHeader.m_dwFileNumber);
	m_vcFilePaths.resize(m_xphHeader.m_dwFileNumber);

	GeneralHeader ogghHeader;
	// 读取索引表
	int nLength = m_xphHeader.m_dwFileNumber * sizeof(GeneralHeader);
	char* pData = new char[nLength];
	::ReadFile(m_hPackageFile, pData, nLength, 0, 0);

	if (m_dwKey1 || m_dwKey1){
		DecodeWriteProcess(pData, nLength, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
		for (int i = 0; i < m_xphHeader.m_dwFileNumber; ++i) {
			memcpy(&ogghHeader, pData + i * sizeof(GeneralHeader), sizeof(GeneralHeader));
			m_vcXmlHeaders[i] = ogghHeader;
		}
		// 读取文件路径表
		int nBasePos = m_xphHeader.m_dwFileNamesBeginOff;
		char szBuffer[FILENAME_MAX];
		for (int i = 0; i < m_xphHeader.m_dwFileNumber; ++i) {
			::ReadFile(m_hPackageFile, szBuffer, m_vcXmlHeaders[i].m_dwFilePathLength, 0, 0);
			DecodeWriteProcess(szBuffer, m_vcXmlHeaders[i].m_dwFilePathLength, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
			szBuffer[m_vcXmlHeaders[i].m_dwFilePathLength] = '\0';
			m_vcFilePaths[i] = string(szBuffer);
			nBasePos += m_vcXmlHeaders[i].m_dwSize;
			m_mpFileNameGeneralData.insert(PairStringGeneralHeader(m_vcFilePaths[i], m_vcXmlHeaders[i]));
		}
	}
	else {
		for (int i = 0; i < m_xphHeader.m_dwFileNumber; ++i) {
			memcpy(&ogghHeader, pData + i * sizeof(GeneralHeader), sizeof(GeneralHeader));
			m_vcXmlHeaders[i] = ogghHeader;
		}
		// 读取文件路径表
		int nBasePos = m_xphHeader.m_dwFileNamesBeginOff;
		char szBuffer[FILENAME_MAX];
		for (int i = 0; i < m_xphHeader.m_dwFileNumber; ++i) {
			::ReadFile(m_hPackageFile, szBuffer, m_vcXmlHeaders[i].m_dwFilePathLength, 0, 0);
			szBuffer[m_vcXmlHeaders[i].m_dwFilePathLength] = '\0';
			m_vcFilePaths[i] = string(szBuffer);
			nBasePos += m_vcXmlHeaders[i].m_dwSize;
			m_mpFileNameGeneralData.insert(PairStringGeneralHeader(m_vcFilePaths[i], m_vcXmlHeaders[i]));
		}
	}

	delete pData;
	return true;
}

void GeneralEncriptySourceExtract::_CheckMakePath(char* pFileName) {
	char *t = pFileName;
	while (t = strchr(++t, '\\')) {
		*t = 0;
		if (_access(pFileName, 0) != -1) {
			*t = '\\';
			continue;
		}
		_mkdir(pFileName);
		*t = '\\';
	}
}

void GeneralEncriptySourceExtract::DecodeWriteProcess(char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2){
	int nIndex = 0;
	DWORD dwData = 0x00000000;
	do {
		dwData = 0x00000000;
		if (nLength >= sizeof(DWORD)) {
			memcpy(&dwData, pInData + nIndex, sizeof(DWORD));
			pFunc(dwData, dwData, dwKey1, dwKey2);
			memcpy(pInData + nIndex, &dwData, sizeof(DWORD));
		}
		else {
			memcpy(&dwData, pInData + nIndex, nLength);
			pFunc(dwData, dwData, dwKey1, dwKey2);
			memcpy(pInData + nIndex, &dwData, nLength);
		}
		nLength -= sizeof(DWORD);
		nIndex += sizeof(DWORD);
	} while (nLength > 0);
}

bool GeneralEncriptySourceExtract::GetGeneralData(string strFilePath, char** ppData, int* pSize) {
	if (m_mpFileNameGeneralData.find(strFilePath) == m_mpFileNameGeneralData.end()) {
		*ppData = NULL;
		return false;
	}
	GeneralHeader& igghHeader = m_mpFileNameGeneralData[strFilePath];
	// 读取目标像素
	::SetFilePointer(m_hPackageFile, igghHeader.m_dwOff, 0, FILE_BEGIN);
	// 读入数据
	char* pCmpData = new char[igghHeader.m_dwCmpSize];
	if (FAILED(::ReadFile(m_hPackageFile, pCmpData, igghHeader.m_dwCmpSize, 0, 0)))
		return false;

	// 解密
	if (m_dwKey1 || m_dwKey2){
		DecodeWriteProcess(pCmpData, igghHeader.m_dwCmpSize, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
	}

	// 解压
	CLZSS lzLzss;
	char* pOutData = NULL;
	DWORD nOutSize = 0;
	lzLzss.DecodeData(pCmpData, &pOutData, igghHeader.m_dwCmpSize, igghHeader.m_dwSize);

	*ppData = pOutData;
	*pSize = igghHeader.m_dwSize;
	
	return true;
}

bool GeneralEncriptySourceExtract::IsHaveFile(string strFilePath){
	return (m_mpFileNameGeneralData.find(strFilePath) != m_mpFileNameGeneralData.end());
}

GeneralEncriptySourceExtract::~GeneralEncriptySourceExtract()
{
	::CloseHandle(m_hPackageFile);
}
