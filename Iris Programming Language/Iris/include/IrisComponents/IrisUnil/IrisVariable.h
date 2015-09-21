#ifndef _H_IRISVARIABLE_
#define _H_IRISVARIABLE_
#include "IrisValue.h"
#include <string>
using namespace std;
class IrisVariable
{
private:
	string m_strName = "";
	IrisValue m_ivValue;

public:

	IrisVariable();
	~IrisVariable();

	friend class IrisClass;
	friend class IrisModule;
	friend class IrisInterpreter;
	friend class IrisContextEnvironment;
	friend class IrisObject;
	friend class IrisGC;
	friend class IrisClosureBlock;
};

#endif