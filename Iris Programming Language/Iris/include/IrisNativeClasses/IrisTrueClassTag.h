#ifndef _H_IRISTRUECLASSTAG_
#define _H_IRISTRUECLASSTAG_

#include <string>
using namespace std;

class IrisTrueClassTag
{
private:
	string m_strName = "true";

public:

	const string& GetName();
	bool GetTrueValue() { return true; }
	bool LogicNot() { return false; }

	IrisTrueClassTag();
	~IrisTrueClassTag();
};

#endif