#include "IrisGraphicsPacker.h"


IrisGraphicsPacker::IrisGraphicsPacker() : m_strPackageName(), m_strGraphFolderName(), m_irphHeader(), m_nWholeFilePathLength(0), m_nPreGraphLength(0), m_nRecordedGraphLength(0), m_hTmpFile(0), m_nCmpedSize(0), m_pfEncodeFunc(NULL), m_dwKey1(0), m_dwKey2(0)
{
}

void IrisGraphicsPacker::_MakeHeader(){
	memcpy(m_irphHeader.m_szMagic, c_szMagic, sizeof(c_szMagic));
	m_irphHeader.m_dwReserve1 = m_dwKey1;
	m_irphHeader.m_dwReserve2 = m_dwKey2;
}


int IrisGraphicsPacker::_CalcGraphOffLength(int nCurLength) {
	int nTmpLength = m_nRecordedGraphLength + sizeof(IrisGraphicsPackageHeader) + m_irphHeader.m_dwFileNumber * sizeof(IrisGraphicsGraphHeader) + m_nWholeFilePathLength;
	m_nRecordedGraphLength += nCurLength;
	return nTmpLength;
}

bool IrisGraphicsPacker::MakePackage(string& strPackageName, string& strGraphFolderName, DWORD dwKey1, DWORD dwKey2, SafetyFunc pfEncodeFunc){

	m_nWholeFilePathLength = 0;
	m_nPreGraphLength = 0;
	m_nRecordedGraphLength = 0;
	m_nCmpedSize = 0;
	m_strGraphFolderName = strGraphFolderName;
	m_strPackageName = strPackageName;
	m_pfEncodeFunc = pfEncodeFunc;
	m_dwKey1 = dwKey1;
	m_dwKey2 = dwKey2;

	_MakeHeader();
	cout << "Path Processing..." << endl;
	if(!_PathRecord(m_strGraphFolderName.c_str())) return false;
	cout << "Completed !" << endl;
	cout << "Index And File Path Processing..." << endl;
	if(!_IndexAndFilePathDataMake()) return false;
	cout << "Completed !" << endl;
	cout << "Write Data..." << endl;
	if(!_WriteFile()) return false;
	cout << "Completed !" << endl;
	return true;
}

bool IrisGraphicsPacker::_PathRecord(const char * lpPath){
	char szFind[MAX_PATH];
	char szProcessFile[MAX_PATH];
	WIN32_FIND_DATAA FindFileData;
	strcpy_s(szFind, lpPath);
	strcat_s(szFind, "\\*.*");
	HANDLE hFind = ::FindFirstFileA(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind) return false;
	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
				//发现子目录，递归之
				char szFile[MAX_PATH] = { 0 };
				strcpy_s(szFile, lpPath);
				strcat_s(szFile, "\\");
				strcat_s(szFile, FindFileData.cFileName);
				_PathRecord(szFile);
			}
		}
		else {
			//找到文件，处理之
			memset(szProcessFile, 0, FILENAME_MAX);
			memcpy(szProcessFile, lpPath, FILENAME_MAX);
			strcat_s(szProcessFile, "\\");
			strcat_s(szProcessFile, FindFileData.cFileName);
			string strCutPath(szProcessFile);
			//_FilePathCut(strCutPath);
			_FileProcess(szProcessFile);
		}
	} while (::FindNextFileA(hFind, &FindFileData));
	::FindClose(hFind);
	return true;
}

void IrisGraphicsPacker::_FilePathCut(string& strFullPath) {
	int nPos = strFullPath.find_first_of(m_strGraphFolderName);
	if (nPos == -1) return;
	strFullPath = strFullPath.substr(nPos, strFullPath.size() - nPos);
}

bool IrisGraphicsPacker::_FileProcess(const char* lpFilePath){
	m_vcFilePaths.push_back(string(lpFilePath));
	++m_irphHeader.m_dwFileNumber;
	m_nWholeFilePathLength += strnlen_s(lpFilePath, FILENAME_MAX);
	return true;
}

bool IrisGraphicsPacker::_IndexAndFilePathDataMake(){

	if (_access(c_szTmpFileName, 0) != -1)
		::DeleteFileA(c_szTmpFileName);

	m_hTmpFile = ::CreateFileA(c_szTmpFileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, 0);
	if (FAILED(m_hTmpFile)){
		cout << "Error when creating temp file !" << endl;
		::CloseHandle(m_hTmpFile);
		return false;
	}

	m_irphHeader.m_dwFileNamesBeginOff = sizeof(IrisGraphicsPackageHeader) + m_irphHeader.m_dwFileNumber * sizeof(IrisGraphicsGraphHeader);

	IrisGraphicsGraphHeader rgghHeader;
	CLZSS lzLzss;

	VectorStringIterator it;
	int nIndex = 0;
	for (it = m_vcFilePaths.begin(); it != m_vcFilePaths.end(); ++it){
		cout << "\tMake Process : " << nIndex << " / " << m_vcFilePaths.size() << "...";
		Bitmap bpBmp(StringToWString(*it).c_str());
		memset(&rgghHeader, 0, sizeof(IrisGraphicsGraphHeader));
		rgghHeader.m_dwFilePathLength = it->size();
		rgghHeader.m_dwWidth = bpBmp.GetWidth();
		rgghHeader.m_dwHeight = bpBmp.GetHeight();
		rgghHeader.m_dwSize = rgghHeader.m_dwWidth * rgghHeader.m_dwHeight * sizeof(RGBQUAD);

		BitmapData bmpdtData;
		Rect bpRect(0, 0, bpBmp.GetWidth(), bpBmp.GetHeight());
		if (FAILED(bpBmp.LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdtData))){
			::CloseHandle(m_hTmpFile);
			return false;
		}

		// 压缩
		DWORD nCmpSize = 0;
		char* pOutData;
		lzLzss.EncodeData((const char*)bmpdtData.Scan0, &pOutData, rgghHeader.m_dwSize, &nCmpSize);

		rgghHeader.m_dwCmpSize = nCmpSize;
		rgghHeader.m_dwGraphOff = _CalcGraphOffLength(rgghHeader.m_dwCmpSize);
		m_nCmpedSize += nCmpSize;

		// 加密
		if (m_dwKey1 || m_dwKey1){
			EncodeWriteProcess(m_hTmpFile, pOutData, nCmpSize, m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
		else{
			::WriteFile(m_hTmpFile, (char*)pOutData, nCmpSize, 0, 0);
		}

		delete[] pOutData;
		bpBmp.UnlockBits(&bmpdtData);

		m_vcGraphHeaders.push_back(rgghHeader);

		cout << "Completed !\n";
		++nIndex;
	}
	return true;
}

bool IrisGraphicsPacker::_WriteFile(){
	HANDLE hFile = ::CreateFileA(m_strPackageName.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, 0, 0);
	if (FAILED(hFile)){
		cout << "Error when creating file : " << m_strPackageName.c_str() << endl;
		return false;
	}

	// 写文件头
	::WriteFile(hFile, (char*)&m_irphHeader, sizeof(m_irphHeader), 0, 0);
	// 如果有加密
	if (m_dwKey1 || m_dwKey1) {
		// 写图片索引
		VectorGraphicsGraphHeaderIterator it;
		for (it = m_vcGraphHeaders.begin(); it != m_vcGraphHeaders.end(); ++it){
			EncodeWriteProcess(hFile, (const char*)&(*it), sizeof(IrisGraphicsGraphHeader), m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
		// 写文件名
		VectorStringIterator it2;
		for (it2 = m_vcFilePaths.begin(); it2 != m_vcFilePaths.end(); ++it2){
			EncodeWriteProcess(hFile, it2->c_str(), it2->length(), m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
	} else {
		// 写图片索引
		VectorGraphicsGraphHeaderIterator it;
		for (it = m_vcGraphHeaders.begin(); it != m_vcGraphHeaders.end(); ++it){
			::WriteFile(hFile, (char*)&(*it), sizeof(IrisGraphicsGraphHeader), 0, 0);
		}
		// 写文件名
		VectorStringIterator it2;
		for (it2 = m_vcFilePaths.begin(); it2 != m_vcFilePaths.end(); ++it2) {
			::WriteFile(hFile, (char*)(it2->c_str()), it2->length(), 0, 0);
		}
	}


	cout << "Packaging Graphics Data... " << endl;

	// 写图片数据
	::SetFilePointer(m_hTmpFile, 0, 0, FILE_BEGIN);
	char szBuffer[c_nCopyBufferSize] = { 0 };
	DWORD nRealReadSize = 0;
	while (m_nCmpedSize > 0){
		if (m_nCmpedSize > c_nCopyBufferSize){
			::ReadFile(m_hTmpFile, szBuffer, c_nCopyBufferSize, 0, 0);
			::WriteFile(hFile, szBuffer, c_nCopyBufferSize, 0, 0);
		}
		else{
			::ReadFile(m_hTmpFile, szBuffer, m_nCmpedSize, 0, 0);
			::WriteFile(hFile, szBuffer, m_nCmpedSize, 0, 0);
		}
		m_nCmpedSize -= c_nCopyBufferSize;
	}

	cout << "Package Complete !" << endl;
	
	::CloseHandle(m_hTmpFile);
	::CloseHandle(hFile);
	return true;
}

IrisGraphicsPacker::~IrisGraphicsPacker()
{
}
