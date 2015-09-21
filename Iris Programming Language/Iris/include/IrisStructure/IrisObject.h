#ifndef _H_IRISOBJECT_
#define _H_IRISOBJECT_

#include "IrisVariable.h"
#include "IrisInterpreter.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

class IrisMethod;
class IrisClass;

class IrisObject {
private:
	typedef map<string, IrisMethod*> _MethodHash;
	typedef pair<string, IrisMethod*> _MethodPair;

	typedef map<string, IrisVariable> _VariableHash;
	typedef pair<string, IrisVariable> _VariablePair;

private:
	static int s_nMaxID;

private:
	//typedef vector<IrisValue> IrisValues;

	IrisClass* m_pClass = nullptr;
	_MethodHash m_mpInstanceMethods;
	_VariableHash m_mpInstanceVariables;
	void* m_pNativeObject = nullptr;

	int m_nObjectID = 0;

	bool m_bIsMaked = false;
	bool m_bLiteralObject = false;
	bool m_bLiteralObjectAssigned = false;

public:
	IrisObject();

	int GetObjectID() { return m_nObjectID; }
	IrisValue CallInstanceFunction(const string& strFunctionName, IrisContextEnvironment* pContexEnvironment, IrisValues* ivsValues, CallerSide eSide = CallerSide::Outside);
	IrisClass* GetClass() { return m_pClass; }

	const IrisValue& GetInstanceValue(const string& strInstanceValueName, bool& bResult);
	void AddInstanceValue(const string& strInstanceValueName, const IrisValue& ivValue);

	void Mark();
	void ClearMark() { m_bIsMaked = false; }

	~IrisObject();

	friend class IrisClass;
	friend class IrisModule;
	friend class IrisMethod;
	friend class IrisInteger;
	friend class IrisFloat;
	friend class IrisString;
	friend class IrisValue;
	friend class IrisObjectBase;
	friend class IrisExpression;
	friend class IrisStatement;
	friend class IrisGC;
	friend class IrisClosureBlock;
};

#endif