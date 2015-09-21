#ifndef _H_IRISMODULE_
#define _H_IRISMODULE_

#include <string>
#include <map>
using namespace std;

#include "IrisValue.h"
#include "IrisVariable.h"
#include "IrisObject.h"
#include "IrisMethod.h"
#include "IrisClass.h"
#include "IrisInterface.h"

class IrisModule {
private:
	typedef map<string, IrisMethod*> _MethodHash;
	typedef pair<string, IrisMethod*> _MethodPair;

	typedef map<string, IrisVariable> _VariableHash;
	typedef pair<string, IrisVariable> _VariablePair;

	typedef map<string, IrisModule*> _ModuleHash;
	typedef pair<string, IrisModule*> _ModulePair;

	typedef map<string, IrisClass*> _ClassHash;
	typedef pair<string, IrisClass*> _ClassPair;

	typedef map<string, IrisInterface*> _InterfaceHash;
	typedef pair<string, IrisInterface*> _InterfacePair;

public:
	enum class SearchMethodType {
		InstanceMethod = 0,
		ClassMethod,
	};

private:
	string m_strModuleName = "";
	IrisModule* m_pUpperModule = nullptr;
	_ModuleHash m_hsModules;
	_MethodHash m_hsClassMethods;
	_MethodHash m_hsInstanceMethods;
	//_VariableHash m_hsInstanceVariables;
	_VariableHash m_hsClassVariables;
	_VariableHash m_hsConstances;

	_InterfaceHash m_hsInvolvedInterfaces;

	_ClassHash m_hsClasses;

	void _SearchModuleMethod(const string& strFunctionName, IrisModule* pCurModule, IrisMethod** ppMethod);
	void _SearchConstance(const string& strConstanceName, IrisModule* pCurModule, IrisValue** pValue);
	void _SearchClassVariable(const string& strVariableName, IrisModule* pCurModule, IrisValue** pValue);

private:
	IrisObject* m_pModuleObject = nullptr;

public:

	virtual void ClearInvolvingModules();

	virtual void AddConstance(const string& strConstName, const IrisValue& ivInitialValue);
	virtual const IrisValue&  SearchConstance(const string& strConstName, bool& bResult);

	virtual void AddClassMethod(IrisMethod* pMethod);
	virtual void AddInstanceMethod(IrisMethod* pMethod);
	virtual void AddModule(IrisModule* pModule);
	//virtual void AddInstanceVariable(const string& strClassVariableName);
	virtual void AddClassVariable(const string& strClassVariableName);
	virtual void AddClassVariable(const string& strClassVariableName, const IrisValue& ivInitialValue);
	virtual const IrisValue& SearchClassVariable(const string& strClassVariableName, bool& bResult);

	virtual void AddClass(IrisClass* pClass);

	virtual void AddInvolvedInterface(IrisInterface* pInterface);

	virtual IrisClass* GetClass(const string& strClassName);
	virtual IrisInterface* GetInterface(const string& strInterfaceName);

	virtual const string& GetModuleName() { return m_strModuleName; }
	virtual IrisValue CallClassMethod(const string& strMethodName, IrisContextEnvironment* pContexEnvironment, IrisValues* ivParameters, CallerSide eSide = CallerSide::Outside);

	virtual void ResetAllMethodsObject();

	virtual IrisMethod* GetCurrentModuleMethod(SearchMethodType eSearchType, const string& strMethodName);

	IrisModule(const string& strModuleName, IrisModule* pUpperModule = nullptr);
	virtual ~IrisModule();

private:
	virtual void NativeClassDefine() {};

	friend class IrisInterpreter;
	friend class IrisClass;
	friend class IrisObject;
	friend class IrisStatement;
	friend class IrisExpression;
	friend class IrisGC;
	friend class IrisInterface;
	friend class IrisModule;
};

#endif