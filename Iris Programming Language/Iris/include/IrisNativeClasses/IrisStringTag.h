#ifndef _H_IRISSTRINGTAG_
#define _H_IRISSTRINGTAG_

#include <string>
using namespace std;

class IrisStringTag
{
private:
	wstring m_strWString;
	string m_strString;

public:
	IrisStringTag(const string& strString);

	IrisStringTag Add(IrisStringTag& istRightString);
	const string& GetString();

	string IrisStringTag::ws2s(const std::wstring& ws);
	wstring IrisStringTag::s2ws(const std::string& s);

	~IrisStringTag();
};

#endif