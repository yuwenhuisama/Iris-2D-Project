#include "IrisGraphicsUnpacker.h"


IrisGraphicsUnpacker::IrisGraphicsUnpacker() : m_hPackageFile(0), m_pfDecodeFunc(NULL), m_dwKey1(0), m_dwKey2(0)
{
}

bool IrisGraphicsUnpacker::UnmakePackage(string& strPackageName, SafetyFunc pfDecodeFunc) {

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

bool IrisGraphicsUnpacker::_ReadPackageHeader(){

	::ReadFile(m_hPackageFile, (char*)&m_irphHeader, sizeof(IrisGraphicsPackageHeader), 0, 0);
	for (int i = 0; i < sizeof(m_irphHeader.m_szMagic); ++i){
		if (m_irphHeader.m_szMagic[i] != c_szMagic[i]) return false;
	}
	m_dwKey1 = m_irphHeader.m_dwReserve1;
	m_dwKey2 = m_irphHeader.m_dwReserve2;

	return true;
}

bool IrisGraphicsUnpacker::_EssensialDataProcess(){
	
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
		}
	} else {
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
		}
	}

	delete pData;
	return true;
}

bool IrisGraphicsUnpacker::_UnpackPackage(){
	CLZSS lzLzss;
	for (int i = 0; i < m_irphHeader.m_dwFileNumber; ++i){
		const string& strFilePath = m_vcFilePaths[i];
		IrisGraphicsGraphHeader& igghHeader = m_vcGraphHeaders[i];
		_CheckMakePath((char*)strFilePath.c_str());
		Bitmap bpBmp(m_vcGraphHeaders[i].m_dwWidth, m_vcGraphHeaders[i].m_dwHeight, PixelFormat32bppARGB);
		// 读取目标像素
		::SetFilePointer(m_hPackageFile, igghHeader.m_dwGraphOff, 0, FILE_BEGIN);
		BitmapData bmpdtData;
		Rect bpRect(0, 0, bpBmp.GetWidth(), bpBmp.GetHeight());
		if (FAILED(bpBmp.LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdtData))){
			::CloseHandle(m_hPackageFile);
			return false;
		}
		// 读入图片中
		char* pCmpData = new char[igghHeader.m_dwCmpSize];
		if (FAILED(::ReadFile(m_hPackageFile, pCmpData, igghHeader.m_dwCmpSize, 0, 0)))
			return false; 

		// 解密
		if (m_dwKey1 || m_dwKey1){
			DecodeWriteProcess(pCmpData, igghHeader.m_dwCmpSize, m_pfDecodeFunc, m_dwKey1, m_dwKey2);
		}

		// 解压
		char* pOutData = NULL;
		DWORD nOutSize = 0;
		lzLzss.DecodeData(pCmpData, &pOutData, igghHeader.m_dwCmpSize, igghHeader.m_dwSize);
		memcpy(bmpdtData.Scan0, pOutData, igghHeader.m_dwSize);
		delete[] pOutData;
		bpBmp.UnlockBits(&bmpdtData);

		int nPos = strFilePath.find_first_of(".");
		if (nPos == -1) return false;
		string strExtend = strFilePath.substr(nPos + 1, strFilePath.size() - nPos);
		if (strExtend == "jpg")
			strExtend = "jpeg";
		strExtend = "image/" + strExtend;
		CLSID encoderClsid;
		GetEncoderClsid(StringToWString(strExtend).c_str(), &encoderClsid);
		// 写到文件
		bpBmp.Save(StringToWString(strFilePath).c_str(), &encoderClsid, NULL);
	}

	return true;
}

int IrisGraphicsUnpacker::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}

void IrisGraphicsUnpacker::_CheckMakePath(char* pFileName) {
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

IrisGraphicsUnpacker::~IrisGraphicsUnpacker()
{
}
