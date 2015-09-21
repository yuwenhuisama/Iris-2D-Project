#ifndef _H_IRISCONTENXENVIRIONMENT_
#define _H_IRISCONTENXENVIRIONMENT_
#include "IrisVariable.h"
#include "IrisObject.h"
#include <string>
#include <map>
using namespace std;

class IrisClosureBlock;
class IrisBlock;
class IrisMethod;

class IrisContextEnvironment
{
private:
	typedef map<string, IrisVariable> _VariableMap;
	typedef pair<string, IrisVariable> _VariablePair;

public:
	enum class EnvironmentType {
		ClassDefineTime = 0,
		ModuleDefineTime,
		InterfaceDefineTime,
		//MethodDefineTime,
		Runtime,
	};

	enum class EnvironmentUpperType {
		Normal = 0,
		Loop,
	};

	union {
		IrisObject* m_pCurObject = nullptr;
		IrisClass* m_pClass;
		IrisModule* m_pModule;
		IrisInterface* m_pInterface;
		//IrisMethod* m_pMethod;
	} m_uType;

public:
	//IrisObject* m_pCurObject;
	_VariableMap m_mpVariables;
	EnvironmentType m_eType = EnvironmentType::Runtime;
	EnvironmentUpperType m_eUpperType = EnvironmentUpperType::Normal;
	//bool m_bIsReferenced = false;

	IrisContextEnvironment* m_pUpperContextEnvironment = nullptr;
	bool m_bIsClosure = false;

	IrisClosureBlock* m_pClosureBlock = nullptr;
	IrisClosureBlock* m_pTransferBlock = nullptr;
	IrisClosureBlock* m_pExcuteBlock = nullptr;

	IrisBlock* m_pWithBlock = nullptr;
	IrisBlock* m_pWithouBlock = nullptr;

	IrisMethod* m_pCurMethod = nullptr;

	int m_nReferenced = 0;

public:

	IrisClosureBlock* GetClosureBlock();

	const IrisValue& GetVariableValue(const string& strVariableName, bool& bResult);
	void AddLoaclVariable(const string& strVariableName, const IrisValue& ivValue);

	IrisContextEnvironment();
	~IrisContextEnvironment();
};

#endif