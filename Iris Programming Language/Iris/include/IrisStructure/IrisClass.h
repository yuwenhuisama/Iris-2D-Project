#ifndef _H_IRISCLASS_
#define _H_IRISCLASS_

#include <string>
#include <map>
using namespace std;

#include "IrisVariable.h"
#include "IrisInterface.h"
#include "IrisMethod.h"
#include "IrisModule.h"

class IrisInterpreter;

class IrisClass {
private:
	typedef map<string, IrisMethod*> _MethodHash;
	typedef pair<string, IrisMethod*> _MethodPair;

	typedef map<string, IrisVariable> _VariableHash;
	typedef pair<string, IrisVariable> _VariablePair;

	typedef map<string, IrisInterface*> _InterfaceHash;
	typedef pair<string, IrisInterface*> _InterfacePair;

	typedef map<string, IrisModule*> _ModuleHash;
	typedef pair<string, IrisModule*> _ModulePair;

	typedef map<string, IrisInterface::InterfaceFunctionDeclare> _InterfaceFunctionDeclareMap;
	typedef pair<string, IrisInterface::InterfaceFunctionDeclare> _InterfaceFunctionDeclarePair;

	typedef IrisValue(*IrisNativeFunction)(IrisValue&, IrisValues*, IrisValues*, IrisContextEnvironment*);

protected:
	string m_strClassName = "";
	IrisClass* m_pSuperClass = nullptr;
	IrisModule* m_pUpperModule = nullptr;
	_InterfaceHash m_hsInterfaces;
	_ModuleHash m_hsModules;
	_MethodHash m_hsClassMethods;
	_MethodHash m_hsInstanceMethods;
	_VariableHash m_hsClassVariables;
	_VariableHash m_hsConstances;
	bool m_bIsCompleteClass = false;;

	IrisObject* m_pClassObject = nullptr;

public:
	enum class SearchMethodType {
		InstanceMethod = 0,
		ClassMethod,
	};

	enum class SearchVariableType{
		Constance = 0,
		ClassInstance,
	};

private:
	void _FunctionCollect(IrisInterface* pInterface, _InterfaceFunctionDeclareMap& mpFunctionDeclare);
	bool _FunctionAchieved();

	void _ModuleMethodSearch(SearchMethodType eSearchType, const string& strFunctionName, IrisModule* pCurModule, IrisMethod** ppMethod);
	void _ClassModuleMethodSearch(SearchMethodType eSearchType, IrisClass* pCurClass, const string& strMethodName, IrisMethod** ppMethod);
	void _SearchModuleConstance(SearchVariableType eType, const string& strVariableName, IrisModule* pCurModule, IrisValue** pValue);

public:

	virtual void ClearInvolvingModules();
	virtual void ClearJointingInterfaces();

	virtual void AddConstance(const string& strConstName, const IrisValue& ivInitialValue);
	virtual const IrisValue&  SearchConstance(const string& strConstName, bool& bResult);

	virtual void AddClassMethod(IrisMethod* pMethod);
	virtual void AddInstanceMethod(IrisMethod* pMethod);

	virtual void AddSetter(const string& strProperName, IrisNativeFunction pfMethod);
	virtual void AddGetter(const string& strProperName, IrisNativeFunction pfMethod);

	virtual void AddInterface(IrisInterface* pInterface);
	virtual void AddModule(IrisModule* pModule);
	virtual void AddClassVariable(const string& strClassVariableName);
	virtual void AddClassVariable(const string& strClassVariableName, const IrisValue& ivInitialValue);
	virtual const IrisValue& SearchClassVariable(const string& strClassVariableName, bool& bResult);
	
	virtual IrisValue CreateInstance(IrisValues* ivsParams, IrisContextEnvironment* pContexEnvironment);
	virtual IrisValue CreateInstanceFromLiteral(char* pLiteral);
	virtual IrisValue CreateInstanceByInstantValue(int nValue) { IrisValue ivValue; ivValue.m_pObject = nullptr; return ivValue; }
	virtual IrisValue CreateInstanceByInstantValue(double dValue) { IrisValue ivValue; ivValue.m_pObject = nullptr; return ivValue; }
	virtual IrisValue CreateInstanceByInstantValue(const string& strString) { IrisValue ivValue; ivValue.m_pObject = nullptr; return ivValue; }

	virtual const string& GetClassName() { return m_strClassName; }
	virtual IrisValue CallClassMethod(const string& strMethodName, IrisContextEnvironment* pContexEnvironment, IrisValues* ivParameters, CallerSide eSide = CallerSide::Outside);

	virtual IrisMethod* GetMethod(SearchMethodType eSearchType, const string& strMethodName, bool& bIsCurClassMethod);

	virtual IrisMethod* GetCurrentClassMethod(SearchMethodType eSearchType, const string& strMethodName);

	virtual void ResetNativeObject();
	virtual void SetSuperClass(IrisClass* pSuperClass) { m_pSuperClass = pSuperClass; }

	IrisClass(const string& strClassName, IrisClass* pSuperClass = nullptr, IrisModule* pUpperModule = nullptr);
	virtual ~IrisClass();

	// 为字面量准备的（Integer/Float/String）
	virtual void* GetLiteralObject(char* pLiterral) { return nullptr; }

	virtual void ResetAllMethodsObject();

	virtual int GetTrustteeSize() { return 0; }

private:
	virtual void* NativeAlloc() { return nullptr; }
	virtual void NativeFree(void* pNativePointer) {}
	virtual void NativeClassDefine() {}
	virtual void Mark(void* pNativePointer) {}

	friend class IrisInterpreter;
	friend class IrisObject;
	friend class IrisObjectBase;
	friend class IrisExpression;
	friend class IrisStatement;
	friend class IrisGC;
};

#endif