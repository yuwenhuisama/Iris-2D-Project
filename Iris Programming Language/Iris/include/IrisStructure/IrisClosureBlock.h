#ifndef _H_IRISCLOSUREBLOCK_
#define _H_IRISCLOSUREBLOCK_

#include "IrisContextEnvironment.h"
#include "IrisValue.h"
#include "IrisObject.h"
#include "IrisGC.h"
#include "IrisBlock.h"

class IrisClosureBlock
{
private:
	IrisContextEnvironment* m_pCurContextEnvironment = nullptr;
	IrisContextEnvironment* m_pUpperContextEnvironment = nullptr;
	IrisObject* m_pNativeObject = nullptr;
	//IrisBlock* m_pBlock = nullptr;

	IrisList<IrisIdentifier*>* m_pParameters = nullptr;
	IrisList<IrisStatement*>* m_pStatements = nullptr;

private:
	typedef map<string, IrisVariable> _VariableMap;
	typedef pair<string, IrisVariable> _VariablePair;

private:
	IrisContextEnvironment* _CreateNewContextEnvironment();

private:
	_VariableMap m_mpOtherVariables;

public:

	const IrisValue& GetLocalVariable(const string& strVariableName, bool& bResult);
	const IrisValue& GetInstanceVariable(const string& strVariableNaem, bool& bResult);
	const IrisValue& GetClassVariable(const string& strVariableNaem, bool& bResult);
	const IrisValue& GetConstance(const string& strConstanceName, bool& bResult);

	void AddLocalVariable(const string& strVariableName, const IrisValue& ivValue);
	void AddOtherVariable(const string& strVariableName, const IrisValue& ivValue);

	void Mark();

	IrisStatementResult Excute(IrisValues* pValues);

	IrisClosureBlock(IrisContextEnvironment* pUpperContexEnvironment, IrisList<IrisIdentifier*>* pParameters, IrisList<IrisStatement*>* pStatements);
	~IrisClosureBlock();

	friend class IrisClosureBlockBase;
	friend class IrisExpression;
};

#endif