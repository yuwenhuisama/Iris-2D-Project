#include "EncryptionDefines.h"

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