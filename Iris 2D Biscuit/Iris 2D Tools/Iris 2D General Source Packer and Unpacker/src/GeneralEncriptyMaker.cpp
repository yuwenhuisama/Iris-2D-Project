#include "GeneralEncriptyMaker.h"


GeneralEncriptyMaker::GeneralEncriptyMaker()
{
}

void GeneralEncriptyMaker::_MakeHeader(){
	memcpy(m_xphHeader.m_szMagic, c_szGeneralMagic, sizeof(c_szGeneralMagic));
	m_xphHeader.m_dwReserve1 = m_dwKey1;
	m_xphHeader.m_dwReserve2 = m_dwKey2;
}


int GeneralEncriptyMaker::_CalcGraphOffLength(int nCurLength) {
	int nTmpLength = m_nRecordedGraphLength + sizeof(GeneralPackageHeader) + m_xphHeader.m_dwFileNumber * sizeof(GeneralHeader) + m_nWholeFilePathLength;
	m_nRecordedGraphLength += nCurLength;
	return nTmpLength;
}

bool GeneralEncriptyMaker::MakePackage(string& strPackageName, string& strFolderName, DWORD dwKey1, DWORD dwKey2, GeneralSafetyFunc pfEncodeFunc){

	m_nWholeFilePathLength = 0;
	m_nPreGraphLength = 0;
	m_nRecordedGraphLength = 0;
	m_nCmpedSize = 0;
	m_strFolderName = strFolderName;
	m_strPackageName = strPackageName;
	m_pfEncodeFunc = pfEncodeFunc;
	m_dwKey1 = dwKey1;
	m_dwKey2 = dwKey2;

	_MakeHeader();
	cout << "Path Processing..." << endl;
	if (!_PathRecord(m_strFolderName.c_str())) return false;
	cout << "Completed !" << endl;
	cout << "Index And File Path Processing..." << endl;
	if (!_IndexAndFilePathDataMake()) return false;
	cout << "Completed !" << endl;
	cout << "Write Data..." << endl;
	if (!_WriteFile()) return false;
	cout << "Completed !" << endl;
	return true;
}

bool GeneralEncriptyMaker::_PathRecord(const char * lpPath){
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

void GeneralEncriptyMaker::_FilePathCut(string& strFullPath) {
	int nPos = strFullPath.find_first_of(m_strFolderName);
	if (nPos == -1) return;
	strFullPath = strFullPath.substr(nPos, strFullPath.size() - nPos);
}

bool GeneralEncriptyMaker::_FileProcess(const char* lpFilePath){
	m_vcFilePaths.push_back(string(lpFilePath));
	++m_xphHeader.m_dwFileNumber;
	m_nWholeFilePathLength += strnlen_s(lpFilePath, FILENAME_MAX);
	return true;
}

bool GeneralEncriptyMaker::_IndexAndFilePathDataMake(){

	if (_access(c_strGeneralTmpFileName.c_str(), 0) != -1)
		::DeleteFileA(c_strGeneralTmpFileName.c_str());

	m_hTmpFile = ::CreateFileA(c_strGeneralTmpFileName.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, 0);
	if (FAILED(m_hTmpFile)){
		cout << "Error when creating temp file !" << endl;
		::CloseHandle(m_hTmpFile);
		return false;
	}

	m_xphHeader.m_dwFileNamesBeginOff = sizeof(GeneralPackageHeader) + m_xphHeader.m_dwFileNumber * sizeof(GeneralPackageHeader);

	GeneralHeader rgghHeader;
	CLZSS lzLzss;

	GeneralVectorStringIterator it;
	int nIndex = 0;
	for (it = m_vcFilePaths.begin(); it != m_vcFilePaths.end(); ++it){
		cout << "\tMake Process : " << nIndex << " / " << m_vcFilePaths.size() << "...";
		//Bitmap bpBmp(StringToWString(*it).c_str());
		HANDLE hCurFile = ::CreateFileA(it->c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		memset(&rgghHeader, 0, sizeof(GeneralHeader));
		DWORD dwSize = ::GetFileSize(hCurFile, 0);
		rgghHeader.m_dwSize = dwSize;
		rgghHeader.m_dwFilePathLength = it->size();

		char* pData = new char[dwSize];
		if (FAILED(::ReadFile(hCurFile, pData, dwSize, 0, 0)))
			return false;
		::CloseHandle(hCurFile);

		// 压缩
		DWORD nCmpSize = 0;
		char* pOutData;
		lzLzss.EncodeData((const char*)pData, &pOutData, rgghHeader.m_dwSize, &nCmpSize);
		delete[] pData;

		rgghHeader.m_dwCmpSize = nCmpSize;
		rgghHeader.m_dwOff = _CalcGraphOffLength(rgghHeader.m_dwCmpSize);
		m_nCmpedSize += nCmpSize;

		// 加密
		if (m_dwKey1 || m_dwKey1){
			EncodeWriteProcess(m_hTmpFile, pOutData, nCmpSize, m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
		else{
			::WriteFile(m_hTmpFile, (char*)pOutData, nCmpSize, 0, 0);
		}

		delete[] pOutData;
		//bpBmp.UnlockBits(&bmpdtData);

		m_vcXmlHeaders.push_back(rgghHeader);

		cout << "Completed !\n";
		++nIndex;
	}
	return true;
}

bool GeneralEncriptyMaker::_WriteFile(){
	HANDLE hFile = ::CreateFileA(m_strPackageName.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, 0, 0);
	if (FAILED(hFile)){
		cout << "Error when creating file : " << m_strPackageName.c_str() << endl;
		return false;
	}

	// 写文件头
	::WriteFile(hFile, (char*)&m_xphHeader, sizeof(m_xphHeader), 0, 0);
	// 如果有加密
	if (m_dwKey1 || m_dwKey1) {
		// 写XML索引
		GeneralVectorXmlHeaderIterator it;
		for (it = m_vcXmlHeaders.begin(); it != m_vcXmlHeaders.end(); ++it){
			EncodeWriteProcess(hFile, (const char*)&(*it), sizeof(GeneralHeader), m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
		// 写文件名
		GeneralVectorStringIterator it2;
		for (it2 = m_vcFilePaths.begin(); it2 != m_vcFilePaths.end(); ++it2){
			EncodeWriteProcess(hFile, it2->c_str(), it2->length(), m_pfEncodeFunc, m_dwKey1, m_dwKey2);
		}
	}
	else {
		// 写XML索引
		GeneralVectorXmlHeaderIterator it;
		for (it = m_vcXmlHeaders.begin(); it != m_vcXmlHeaders.end(); ++it){
			::WriteFile(hFile, (char*)&(*it), sizeof(GeneralHeader), 0, 0);
		}
		// 写文件名
		GeneralVectorStringIterator it2;
		for (it2 = m_vcFilePaths.begin(); it2 != m_vcFilePaths.end(); ++it2) {
			::WriteFile(hFile, (char*)(it2->c_str()), it2->length(), 0, 0);
		}
	}


	cout << "Packaging Graphics Data... " << endl;

	// 写图片数据
	::SetFilePointer(m_hTmpFile, 0, 0, FILE_BEGIN);
	char szBuffer[c_nGeneralCopyBufferSize] = { 0 };
	DWORD nRealReadSize = 0;
	while (m_nCmpedSize > 0){
		if (m_nCmpedSize > c_nGeneralCopyBufferSize){
			::ReadFile(m_hTmpFile, szBuffer, c_nGeneralCopyBufferSize, 0, 0);
			::WriteFile(hFile, szBuffer, c_nGeneralCopyBufferSize, 0, 0);
		}
		else{
			::ReadFile(m_hTmpFile, szBuffer, m_nCmpedSize, 0, 0);
			::WriteFile(hFile, szBuffer, m_nCmpedSize, 0, 0);
		}
		m_nCmpedSize -= c_nGeneralCopyBufferSize;
	}

	cout << "Package Complete !" << endl;

	::CloseHandle(m_hTmpFile);
	::CloseHandle(hFile);
	return true;
}

void GeneralEncriptyMaker::EncodeWriteProcess(HANDLE hFile, const char* pInData, int nLength, GeneralSafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2){
	int nIndex = 0;
	DWORD dwData = 0x00000000;
	do {
		dwData = 0x00000000;
		if (nLength >= sizeof(DWORD)) {
			memcpy(&dwData, pInData + nIndex, sizeof(DWORD));
			pFunc(dwData, dwData, dwKey1, dwKey2);
			::WriteFile(hFile, (char*)&dwData, sizeof(DWORD), 0, 0);
		}
		else {
			memcpy(&dwData, pInData + nIndex, nLength);
			pFunc(dwData, dwData, dwKey1, dwKey2);
			::WriteFile(hFile, (char*)&dwData, nLength, 0, 0);
		}
		nLength -= sizeof(DWORD);
		nIndex += sizeof(DWORD);
	} while (nLength > 0);
}

GeneralEncriptyMaker::~GeneralEncriptyMaker()
{
}
