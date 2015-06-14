#ifndef _GENERALENCRIPTYDEFINES_
#define _GENERALENCRIPTYDEFINES_

#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <io.h>
#include "direct.h"
#include <iostream>
#include "LZSS.h"
using namespace std;

const int c_nGeneralCopyBufferSize = 128;
const char c_szGeneralMagic[4] = { 'g', 'e', 'n', 'p' };
const string c_strGeneralTmpFileName = "__xmltmp__.tmp";

typedef void(*GeneralSafetyFunc)(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2);

std::string WStringToString(const std::wstring &wstr);
std::wstring StringToWString(const std::string &str);

struct GeneralPackageHeader {
	char m_szMagic[4];
	DWORD m_dwFileNumber;
	DWORD m_dwReserve1;
	DWORD m_dwReserve2;
	DWORD m_dwFileNamesBeginOff;

	GeneralPackageHeader() {
		memset(m_szMagic, 0, sizeof(m_szMagic));
		m_dwFileNumber = 0;
		m_dwReserve1 = m_dwReserve2 = 0x00000000;
		m_dwFileNamesBeginOff = 0;
	}
};

struct GeneralHeader {
	DWORD m_dwOff;
	DWORD m_dwSize;
	DWORD m_dwCmpSize;
	DWORD m_dwFilePathLength;

	GeneralHeader(){
		m_dwOff = 0;
		m_dwSize = 0;
		m_dwCmpSize = 0;
		m_dwFilePathLength = 0;
	}
};

typedef vector<string> GeneralVectorString;
typedef GeneralVectorString::iterator GeneralVectorStringIterator;
typedef vector<GeneralHeader> GeneralVectorXmlHeader;
typedef GeneralVectorXmlHeader::iterator GeneralVectorXmlHeaderIterator;

typedef map<string, GeneralHeader> MapStringGeneralHeader;
typedef pair<string, GeneralHeader> PairStringGeneralHeader;

#endif