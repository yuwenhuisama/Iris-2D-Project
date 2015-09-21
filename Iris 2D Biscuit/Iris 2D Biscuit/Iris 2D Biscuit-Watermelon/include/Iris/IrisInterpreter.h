#ifndef _H_IRIS_INTERPRETER_
#define _H_IRIS_INTERPRETER_

#include <map>
#include <list>
#include <set>
using namespace std;

#include "IrisVariable.h"
#include "IrisClass.h"
#include "IrisModule.h"
#include "IrisInterface.h"
#include "IrisStatement.h"
#include "IrisMethod.h"
#include "IrisContextEnvironment.h"
#include "IrisHeap.h"
#include "IrisStack.h"
#include "IrisTree.h"

class IrisInteger;
class IrisClosureBlock;

class IrisInterpreter {
private:
	typedef map<string, IrisVariable> _VariableMap;
	typedef pair<string, IrisVariable> _VariablePair;
	typedef map<string, IrisClass*> _ClassMap;
	typedef pair<string, IrisClass*> _ClassPair;
	typedef map<string, IrisInterface*> _InterfaceMap;
	typedef pair<string, IrisInterface*> _InterfacePair;

	//typedef IrisTree<IrisClass*> _ClassTree;
	typedef IrisTree<IrisModule*> _ModuleTree;

	typedef map<string, IrisMethod*> _MethodMap;
	typedef pair<string, IrisMethod*> _MethodPair;

	typedef list<IrisStatement*> _StatementList;

	typedef map<string, _StatementList*> _StatementsMap;
	typedef pair<string, _StatementList*> _StatementsPair;

	typedef list<IrisContextEnvironment*> _EnvironmentList;

private:
	static IrisInterpreter* s_pCurInstance;

public:
	static IrisInterpreter* CurInstance();
	static void SetCurInterpreter(IrisInterpreter* pInterpreter);

public:
	enum class EnvironmentUpperType {
		Normal = 0,
		Loop,
	};

private:
	_VariableMap m_mpGlobalVariables;
	_VariableMap m_mpConstances;
	_VariableMap m_mpMainEnvironmentVariables;

	_ClassMap m_mpClassMap;
	_ModuleTree m_trModuleTree;
	_InterfaceMap m_mpInterfaceMap;

	_MethodMap m_mpMainMethodMap;

	_StatementList m_lsStatement;
	_StatementsMap m_mpStatements;
	_StatementList* m_pCurrentStatements = nullptr;
	_StatementList m_pEvalStatements;

	int m_nCurLineNumber = 1;

	IrisHeap m_ihHeap;
	IrisStack m_isStack;

	_EnvironmentList m_evEnvironmentHeap;

	IrisValue m_ivTrue;
	IrisValue m_ivFalse;
	IrisValue m_ivNil;

	string m_strParseString = "";

	string m_strCurFileName = "";

	IrisValue m_ivIrregularObject;
	bool m_bHaveIrregular = false;
	bool m_bIrregularFlag = true;
	
	bool m_bEvalFlag = false;

	int m_nExcutedLineNumber = 0;

	EnvironmentUpperType m_uUpperType = EnvironmentUpperType::Normal;

	IrisClosureBlock* m_pClosureBlock = nullptr;

private:

	int _Split(const string& str, list<string>& ret_, string sep = ",");

public:

	bool HaveFileRequired(const string& strFilePath) { return m_mpStatements.find(strFilePath) != m_mpStatements.end(); }

	EnvironmentUpperType GetUpperType() { return m_uUpperType; }
	void SetUpperType(EnvironmentUpperType eUpperType) { m_uUpperType = eUpperType; }

	void SetMainClosureBlock(IrisClosureBlock* pClosureBlock) { m_pClosureBlock = pClosureBlock; }
	IrisClosureBlock* GetMainClosureBlock() { return m_pClosureBlock; }

	void SetExcutedLineNumber(int nNumber) { m_nExcutedLineNumber = nNumber; }
	int GetExcutedLineNumber() { return m_nExcutedLineNumber; }

	int GetCurrentLineNumber() { return m_nCurLineNumber; }

	void AddStatement(IrisStatement* pStatement) { m_bEvalFlag ? m_pEvalStatements.push_back(pStatement) : m_pCurrentStatements->push_back(pStatement); }
	void IncreamLineNumber() { ++m_nCurLineNumber; }

	void StartStringProcess() { m_strParseString.clear(); }
	void AddStringChar(char c) { m_strParseString += c; }
	const string& EndStringProcess() { return m_strParseString; }

	void Initialize();
	void ShutDown();

	IrisClass* GetIrisClass(const string& strClassFullFieldName);
	IrisModule* GetIrisModule(const string& strModuleFullFiledName);
	IrisInterface* GetIrisInterface(const string& strInterfaceFullFiledName);

	IrisClass* GetIrisClass(const list<string>& lsRoute);
	IrisModule* GetIrisModule(const list<string>& lsRoute);
	IrisInterface* GetIrisInterface(const list<string>& lsRoute);

	bool RegistClass(const string& strClassFullFieldName, IrisClass* pClass);
	bool RegistModule(const string& strModuleFullFieldName, IrisModule* pModule);
	bool RegistInterface(const string& strInterfaceFullFieldName, IrisInterface* pInterface);

	bool AddNewInstanceToHeap(IrisValue& ivValue);
	bool AddNewEnvironmentToHeap(IrisContextEnvironment* pEnvironment);
	
	void AddConstance(const string& strValueName, const IrisValue& ivValue){
		if (m_mpConstances.find(strValueName) != m_mpConstances.end()){
			return;
		}
		IrisVariable ivbVariable;
		ivbVariable.m_ivValue = ivValue;
		ivbVariable.m_strName = strValueName;
		m_mpConstances.insert(_VariablePair(strValueName, ivbVariable));
	}

	void AddGlobalValue(const string& strValueName, const IrisValue& ivValue){
		IrisVariable ivbVariable;
		ivbVariable.m_ivValue = ivValue;
		ivbVariable.m_strName = strValueName;
		m_mpGlobalVariables.insert(_VariablePair(strValueName, ivbVariable));
	}

	void AddOtherValue(const string& strValueName, const IrisValue& ivValue){
		IrisVariable ivbVariable;
		ivbVariable.m_ivValue = ivValue;
		ivbVariable.m_strName = strValueName;
		m_mpMainEnvironmentVariables.insert(_VariablePair(strValueName, ivbVariable));
	}

	const IrisValue& GetConstance(const string& strValueName, bool& bResult){
		bResult = true;
		if (m_mpConstances.find(strValueName) == m_mpConstances.end()){
			bResult = false;
			return m_ivNil;
		}
		return m_mpConstances[strValueName].m_ivValue;
	}

	const IrisValue& GetGlobalValue(const string& strValueName, bool& bResult){
		bResult = true;
		if (m_mpGlobalVariables.find(strValueName) == m_mpGlobalVariables.end()){
			bResult = false;
			return m_ivNil;
		}
		return m_mpGlobalVariables[strValueName].m_ivValue;
	}
	
	const IrisValue& GetOtherValue(const string& strValueName, bool& bResult){
		bResult = true;
		if (m_mpMainEnvironmentVariables.find(strValueName) == m_mpMainEnvironmentVariables.end()){
			bResult = false;
			return m_ivNil;
		}
		return m_mpMainEnvironmentVariables[strValueName].m_ivValue;
	}
	
	IrisMethod* GetMainMethod(const string& strMethodName);
	void AddMainMethod(const string& strMethodName, IrisMethod* pMethod);

	const IrisValue& True() { return m_ivTrue; }
	const IrisValue& False() { return m_ivFalse; }
	const IrisValue& Nil() { return m_ivNil; }

	void SaveTempValue(const IrisValue& ivValue) {
		m_isStack.Push(ivValue);
	}

	void ClearTempValue(int nTimes) {
		//m_isStack.Clear();
		for (int i = 0; i < nTimes; ++i) {
			m_isStack.Pop();
		}
	}

	IrisValue ExcuteStatements(IrisContextEnvironment* pContextEnvironment = nullptr);

	IrisValue GetIrregularObejet() {
		return m_ivIrregularObject;
	}

	IrisValue RegistIrregularObject(IrisValue& ivIrregularObject) {
		m_ivIrregularObject = ivIrregularObject;
		m_bHaveIrregular = true;
		return ivIrregularObject;
	}

	IrisValue UnregistIrregularObject() {
		m_ivIrregularObject = m_ivNil;
		m_bHaveIrregular = false;
		return m_ivNil;
	}

	bool HaveIrregular() {
		if (m_bIrregularFlag) {
			return m_bHaveIrregular;
		}
		else {
			return false;
		}
	}

	void SetIrregularFlag(bool bFlag) {
		m_bIrregularFlag = bFlag;
	}

	enum class FatalIrregular {
		SyntaxIrregular = 0,
		IdenfierTypeIrregular,
		NoMethodIrregular,
		IrregularNotDealedIrregular,
		SourceObjectIrregular,
		IdentifierNotFoundIrregular,
		ReturnIrregular,
		LeftValueIrregular,
		SelfPointerIrregular,
		ConstanceReassignIrregular,
		ConstanceDeclareIrregular,
		ClassVariableDeclareIrregular,
		MethodAuthorityIrregular,
		ClassNotCompleteIrregular,
		ParameterNotFitIrregular,
		NoMethodCanSuperIrregular,
	};

	void GroanFatalIrregular(FatalIrregular eIrregularType, int nLineno, const string& strTipMessage);

	void SetCurrentFile(const string& strFile);

	void LoadScript(const string& strFile);
	void LoadScriptString(const string& strScript);

	IrisInterpreter();
	~IrisInterpreter();

	friend class IrisGC;
};

#endif