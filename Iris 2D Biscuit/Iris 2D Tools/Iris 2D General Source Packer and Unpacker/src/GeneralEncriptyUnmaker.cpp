#include "GeneralEncriptyUnmaker.h"


GeneralEncriptyUnmaker::GeneralEncriptyUnmaker()
{
}

bool GeneralEncriptyUnmaker::UnmakePackage(string& strPackageName, GeneralSafetyFunc pfDecodeFunc) {

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
	if (!_UnpackPackage()) { ::CloseHandle(m_hPackageFile); return false; }

	::CloseHandle(m_hPackageFile);
	return true;
}

bool GeneralEncriptyUnmaker::_ReadPackageHeader(){

	::ReadFile(m_hPackageFile, (char*)&m_xphHeader, sizeof(GeneralPackageHeader), 0, 0);
	for (int i = 0; i < sizeof(m_xphHeader.m_szMagic); ++i){
		if (m_xphHeader.m_szMagic[i] != c_szGeneralMagic[i]) return false;
	}
	m_dwKey1 = m_xphHeader.m_dwReserve1;
	m_dwKey2 = m_xphHeader.m_dwReserve2;

	return true;
}

bool GeneralEncriptyUnmaker::_EssensialDataProcess(){

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
		}
	}

	delete pData;
	return true;
}

bool GeneralEncriptyUnmaker::_UnpackPackage(){
	CLZSS lzLzss;
	for (int i = 0; i < m_xphHeader.m_dwFileNumber; ++i){
		const string& strFilePath = m_vcFilePaths[i];
		GeneralHeader& xhHeader = m_vcXmlHeaders[i];
		_CheckMakePath((char*)strFilePath.c_str());
		// 读取目标数据
		::SetFilePointer(m_hPackageFile, xhHeader.m_dwOff, 0, FILE_BEGIN);
		//// 读入数据中
		char* pCmpData = new char[xhHeader.m_dwCmpSize];
		if (FAILED(::ReadFile(m_hPackageFile, pCmpData, xhHeader.m_dwCmpSize, 0, 0)))
			return false;

		// 解密
		if (m_dwKey1 || m_dwKey1){
			DecodeWriteProcess(pCmpData, xhHeader.m_dwCmpSize, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
		}

		// 解压
		char* pOutData = NULL;
		DWORD nOutSize = 0;
		lzLzss.DecodeData(pCmpData, &pOutData, xhHeader.m_dwCmpSize, xhHeader.m_dwSize);

		// 写入文件
		HANDLE hCurFile = ::CreateFileA(strFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, 0, 0);
		::WriteFile(hCurFile, pOutData, xhHeader.m_dwSize, 0, 0);
		::CloseHandle(hCurFile);

		delete[] pOutData;

	}

	return true;
}

void GeneralEncriptyUnmaker::_CheckMakePath(char* pFileName) {
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

void GeneralEncriptyUnmaker::DecodeWriteProcess(char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2){
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

GeneralEncriptyUnmaker::~GeneralEncriptyUnmaker()
{
}
