#include "defines.h"

std::string WStringToString(const std::wstring &wstr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

std::wstring StringToWString(const std::string &str)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), 0, 0);
	if (nSize <= 0) return NULL;
	WCHAR *pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst) return NULL;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pwszDst, nSize);
	pwszDst[nSize] = 0;
	if (pwszDst[0] == 0xFEFF)                    // skip Oxfeff
		for (int i = 0; i < nSize; i++)
			pwszDst[i] = pwszDst[i + 1];
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}

void EncodeWriteProcess(HANDLE hFile, const char* pInData, int nLength, SafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2) {
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

void DecodeWriteProcess(char* pInData, int nLength, SafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2) {
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