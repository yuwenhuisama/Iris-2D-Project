#ifndef _H_IRISFALSECLASSTAG_
#define _H_IRISFALSECLASSTAG_

#include <string>
using namespace std;

class IrisFalseClassTag
{
private:
	string m_strName = "false";

public:
	const string& GetName();
	bool GetTrueValue() { return false; }
	bool LogicNot() { return true; }

public:
	IrisFalseClassTag();
	~IrisFalseClassTag();
};

#endif