#include "IrisContextEnvironment.h"
#include "IrisInterpreter.h"

IrisContextEnvironment::IrisContextEnvironment() : m_mpVariables()
{
}

IrisClosureBlock* IrisContextEnvironment::GetClosureBlock() {
	return m_pClosureBlock;
}

const IrisValue& IrisContextEnvironment::GetVariableValue(const string& strVariableName, bool& bResult) {
	if (m_mpVariables.find(strVariableName) == m_mpVariables.end()){
		bResult = false;
		return IrisInterpreter::CurInstance()->Nil();
	}
	bResult = true;
	return m_mpVariables[strVariableName].m_ivValue;
}

void IrisContextEnvironment::AddLoaclVariable(const string& strVariableName, const IrisValue& ivValue){
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = ivValue;
	ivbVariable.m_strName = strVariableName;
	m_mpVariables.insert(_VariablePair(strVariableName, ivbVariable));
}


IrisContextEnvironment::~IrisContextEnvironment()
{
}
