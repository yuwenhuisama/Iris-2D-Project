#include "IrisGraphicsSourceExtract.h"


IrisGraphicsSourceExtract::IrisGraphicsSourceExtract()
{
}

bool IrisGraphicsSourceExtract::_ReadPackageHeader(){

	::ReadFile(m_hPackageFile, (char*)&m_irphHeader, sizeof(IrisGraphicsPackageHeader), 0, 0);
	for (int i = 0; i < sizeof(m_irphHeader.m_szMagic); ++i){
		if (m_irphHeader.m_szMagic[i] != c_szMagic[i]) return false;
	}
	m_dwKey1 = m_irphHeader.m_dwReserve1;
	m_dwKey2 = m_irphHeader.m_dwReserve2;

	return true;
}

bool IrisGraphicsSourceExtract::_EssensialDataProcess(){

	m_vcGraphHeaders.resize(m_irphHeader.m_dwFileNumber);
	m_vcFilePaths.resize(m_irphHeader.m_dwFileNumber);

	IrisGraphicsGraphHeader ogghHeader;
	// 读取索引表
	int nLength = m_irphHeader.m_dwFileNumber * sizeof(IrisGraphicsGraphHeader);
	char* pData = new char[nLength];
	::ReadFile(m_hPackageFile, pData, nLength, 0, 0);

	if (m_dwKey1 || m_dwKey1){
		DecodeWriteProcess(pData, nLength, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
		for (int i = 0; i < m_irphHeader.m_dwFileNumber; ++i) {
			memcpy(&ogghHeader, pData + i * sizeof(IrisGraphicsGraphHeader), sizeof(IrisGraphicsGraphHeader));
			m_vcGraphHeaders[i] = ogghHeader;
		}
		// 读取文件路径表
		int nBasePos = m_irphHeader.m_dwFileNamesBeginOff;
		char szBuffer[FILENAME_MAX];
		for (int i = 0; i < m_irphHeader.m_dwFileNumber; ++i) {
			::ReadFile(m_hPackageFile, szBuffer, m_vcGraphHeaders[i].m_dwFilePathLength, 0, 0);
			DecodeWriteProcess(szBuffer, m_vcGraphHeaders[i].m_dwFilePathLength, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
			szBuffer[m_vcGraphHeaders[i].m_dwFilePathLength] = '\0';
			m_vcFilePaths[i] = string(szBuffer);
			nBasePos += m_vcGraphHeaders[i].m_dwSize;
			m_mpFileNameGraphics.insert(PairStringGraphicsGraphHeader(m_vcFilePaths[i], m_vcGraphHeaders[i]));
		}
	}
	else {
		for (int i = 0; i < m_irphHeader.m_dwFileNumber; ++i) {
			memcpy(&ogghHeader, pData + i * sizeof(IrisGraphicsGraphHeader), sizeof(IrisGraphicsGraphHeader));
			m_vcGraphHeaders[i] = ogghHeader;
		}
		// 读取文件路径表
		int nBasePos = m_irphHeader.m_dwFileNamesBeginOff;
		char szBuffer[FILENAME_MAX];
		for (int i = 0; i < m_irphHeader.m_dwFileNumber; ++i) {
			::ReadFile(m_hPackageFile, szBuffer, m_vcGraphHeaders[i].m_dwFilePathLength, 0, 0);
			szBuffer[m_vcGraphHeaders[i].m_dwFilePathLength] = '\0';
			m_vcFilePaths[i] = string(szBuffer);
			nBasePos += m_vcGraphHeaders[i].m_dwSize;
			m_mpFileNameGraphics.insert(PairStringGraphicsGraphHeader(m_vcFilePaths[i], m_vcGraphHeaders[i]));
		}
	}

	delete pData;
	return true;
}

bool IrisGraphicsSourceExtract::InitPackageData(string strPackagePath, SafetyFunc pfDecodeFunc) {
	m_hPackageFile = 0;
	m_pfDecodeFunc = pfDecodeFunc;
	m_dwKey1 = 0;
	m_dwKey2 = 0;

	m_vcGraphHeaders.clear();
	m_vcFilePaths.clear();
	m_mpFileNameGraphics.clear();

	m_hPackageFile = ::CreateFileA(strPackagePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (FAILED(m_hPackageFile)){
		cout << "Error when creating file : " << strPackagePath.c_str() << endl;
		return false;
	}

	if (!_ReadPackageHeader()) { ::CloseHandle(m_hPackageFile); return false; }
	if (!_EssensialDataProcess()) { ::CloseHandle(m_hPackageFile); return false; }

	::CloseHandle(m_hPackageFile);

	return true;
}

bool IrisGraphicsSourceExtract::GetBitmapData(string strFilePath, char** ppData, int* nWidth, int* nHeight) {
	if (m_mpFileNameGraphics.find(strFilePath) == m_mpFileNameGraphics.end()) {
		*ppData = NULL;
		*nWidth = *nHeight = 0;
		return false;
	}
	IrisGraphicsGraphHeader& igghHeader = m_mpFileNameGraphics[strFilePath];
	// 读取目标像素
	::SetFilePointer(m_hPackageFile, igghHeader.m_dwGraphOff, 0, FILE_BEGIN);
	// 读入图片中
	char* pCmpData = new char[igghHeader.m_dwCmpSize];
	if (FAILED(::ReadFile(m_hPackageFile, pCmpData, igghHeader.m_dwCmpSize, 0, 0)))
		return false;

	// 解密
	if (m_dwKey1 || m_dwKey1){
		DecodeWriteProcess(pCmpData, igghHeader.m_dwCmpSize, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
	}

	// 解压
	CLZSS lzLzss;
	char* pOutData = NULL;
	DWORD nOutSize = 0;
	lzLzss.DecodeData(pCmpData, &pOutData, igghHeader.m_dwCmpSize, igghHeader.m_dwSize);

	*ppData = pOutData;
	*nWidth = igghHeader.m_dwWidth;
	*nHeight = igghHeader.m_dwHeight;

	return true;
}

IrisGraphicsSourceExtract::~IrisGraphicsSourceExtract()
{
}
