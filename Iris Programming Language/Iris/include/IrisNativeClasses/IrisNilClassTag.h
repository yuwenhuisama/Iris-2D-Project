#ifndef _H_IRISNILCLASSTAG_
#define _H_IRISNILCLASSTAG_

#include <string>
using namespace std;

class IrisNilClassTag
{
private:
	string m_strName = "nil";

public:

	const string& GetName();

	bool GetTrueValue() { return false; }
	bool LogicNot() { return true; }

	IrisNilClassTag();
	~IrisNilClassTag();
};

#endif