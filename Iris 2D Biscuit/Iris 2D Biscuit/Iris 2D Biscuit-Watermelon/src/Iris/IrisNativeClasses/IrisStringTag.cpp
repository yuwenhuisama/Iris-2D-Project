#include "IrisStringTag.h"
#include <codecvt>
#include <string>
#include <iostream>
using namespace std;

IrisStringTag::IrisStringTag(const string& strString) {
	wstring_convert<codecvt_utf8_utf16<unsigned short>, unsigned short> convert;
	auto b = convert.from_bytes(strString);
	m_strWString.assign((wchar_t*)b.c_str());
	m_strString = ws2s(m_strWString);
}

IrisStringTag IrisStringTag::Add(IrisStringTag& istRightString) {
	IrisStringTag istResult("");
	istResult.m_strWString = m_strWString + istRightString.m_strWString;
	istResult.m_strString = ws2s(istResult.m_strWString);
	return istResult;
}

const string& IrisStringTag::GetString() {
	return m_strString;
}

string IrisStringTag::ws2s(const std::wstring& ws) {
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";  
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

wstring IrisStringTag::s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}

IrisStringTag::~IrisStringTag()
{
}
