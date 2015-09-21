#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <io.h>
#include "direct.h"
#include "LZSS.h"

using namespace std;
using namespace Gdiplus;
#pragma comment(lib, "GdiPlus.lib")

#ifndef _H_DEFINES_
#define _H_DEFINES_

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

const char c_szMagic[] = { 'i', 'r', 'g', 'p' };
const char c_szTmpFileName[] = "__igtmp__.tmp";

const int c_nCopyBufferSize = 128;

struct IrisGraphicsPackageHeader {
	char m_szMagic[4];
	DWORD m_dwFileNumber;
	DWORD m_dwReserve1;
	DWORD m_dwReserve2;
	DWORD m_dwFileNamesBeginOff;

	IrisGraphicsPackageHeader() {
		memset(m_szMagic, 0, sizeof(m_szMagic));
		m_dwFileNumber = 0;
		m_dwReserve1 = m_dwReserve2 = 0x00000000;
		m_dwFileNamesBeginOff = 0;
	}
};

struct IrisGraphicsGraphHeader {
	DWORD m_dwGraphOff;
	DWORD m_dwSize;
	DWORD m_dwCmpSize;
	DWORD m_dwWidth;
	DWORD m_dwHeight;
	DWORD m_dwFilePathLength;

	IrisGraphicsGraphHeader(){
		m_dwGraphOff = 0;
		m_dwSize = 0;
		m_dwCmpSize = 0;
		m_dwWidth = 0;
		m_dwHeight = 0;
		m_dwFilePathLength = 0;
	}
};

typedef void(*SafetyFunc)(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2);
typedef vector<string> VectorString;
typedef VectorString::iterator VectorStringIterator;
typedef vector<IrisGraphicsGraphHeader> VectorGraphicsGraphHeader;
typedef VectorGraphicsGraphHeader::iterator VectorGraphicsGraphHeaderIterator;

typedef map<string, IrisGraphicsGraphHeader> MapStringGraphicsGraphHeader;
typedef pair<string, IrisGraphicsGraphHeader> PairStringGraphicsGraphHeader;


void EncodeWriteProcess(HANDLE hFile, const char* pInData, int nLength, SafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2);
void DecodeWriteProcess(char* pInData, int nLength, SafetyFunc pFunc, DWORD dwKey1, DWORD dwKey2);

#endif