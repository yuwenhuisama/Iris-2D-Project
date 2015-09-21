#include "IrisClosureBlock.h"
#include "IrisModuleBaseTag.h"
#include "IrisClassBaseTag.h"


IrisClosureBlock::IrisClosureBlock(IrisContextEnvironment* pUpperContexEnvironment, IrisList<IrisIdentifier*>* pParameters, IrisList<IrisStatement*>* pStatements) : m_pUpperContextEnvironment(pUpperContexEnvironment), m_pParameters(pParameters), m_pStatements(pStatements), m_mpOtherVariables()
{
	m_pCurContextEnvironment = _CreateNewContextEnvironment();
}

IrisContextEnvironment* IrisClosureBlock::_CreateNewContextEnvironment() {
	IrisContextEnvironment* pNewEnvironment = new IrisContextEnvironment();
	pNewEnvironment->m_eType = IrisContextEnvironment::EnvironmentType::Runtime;
	pNewEnvironment->m_uType.m_pCurObject = m_pNativeObject;

	IrisGC::AddContextEnvironmentSize();
	IrisGC::ContextEnvironmentGC();

	pNewEnvironment->m_bIsClosure = true;
	//pNewEnvironment->m_bIsReferenced = true;
	pNewEnvironment->m_pUpperContextEnvironment = m_pUpperContextEnvironment;

	IrisInterpreter::CurInstance()->AddNewEnvironmentToHeap(pNewEnvironment);
	return pNewEnvironment;
}

const IrisValue& IrisClosureBlock::GetLocalVariable(const string& strVariableName, bool& bResult) {
	//IrisValue ivResult{ IrisInterpreter::CurInstance()->Nil() };
	IrisValue* pValue = nullptr;

	bResult = false;
	IrisContextEnvironment* pTmpContextEnvrionment = m_pCurContextEnvironment;
	while (pTmpContextEnvrionment && !bResult) {
		pValue = (IrisValue*)&(pTmpContextEnvrionment->GetVariableValue(strVariableName, bResult));
		pTmpContextEnvrionment = pTmpContextEnvrionment->m_pUpperContextEnvironment;
	}

	if (bResult) {
		return *pValue;
	}
	else {
		pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strVariableName, bResult);
		if (bResult) {
			return *pValue;
		}
		return IrisInterpreter::CurInstance()->Nil();
	}
}

const IrisValue& IrisClosureBlock::GetInstanceVariable(const string& strVariableName, bool& bResult) {

	//IrisValue ivResult{ IrisInterpreter::CurInstance()->Nil() };
	bResult = false;
	IrisValue* pValue = nullptr;

	if (m_mpOtherVariables.find(strVariableName) != m_mpOtherVariables.end()) {
		bResult = true;
		return m_mpOtherVariables[strVariableName].m_ivValue;
	}
	else {
		IrisContextEnvironment* pContextEnvrionment = m_pUpperContextEnvironment;
		while (pContextEnvrionment) {
			IrisObject* pObject = pContextEnvrionment->m_uType.m_pCurObject;
			if (pObject) {
				if (pObject->GetClass()->GetClassName() != "Class"
					&& pObject->GetClass()->GetClassName() != "Module") {
					pValue = (IrisValue*)(&pObject->GetInstanceValue(strVariableName, bResult));
				}
			}
			else {
				pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strVariableName, bResult);
			}
			if (bResult) {
				return *pValue;
			}
			pContextEnvrionment = pContextEnvrionment->m_pUpperContextEnvironment;
		}

		if (bResult) {
			return *pValue;
		}
		else {
			pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strVariableName, bResult);
			if (bResult) {
				return *pValue;
			}
			return IrisInterpreter::CurInstance()->Nil();
		}
	}
}

const IrisValue& IrisClosureBlock::GetClassVariable(const string& strVariableName, bool& bResult) {
	//IrisValue ivResult{ IrisInterpreter::CurInstance()->Nil() };
	bResult = false;
	IrisValue* pValue = nullptr;

	if (m_mpOtherVariables.find(strVariableName) != m_mpOtherVariables.end()) {
		bResult = true;
		return m_mpOtherVariables[strVariableName].m_ivValue;
	}
	else {
		IrisContextEnvironment* pContextEnvrionment = m_pUpperContextEnvironment;
		while (pContextEnvrionment) {
			IrisObject* pObject = pContextEnvrionment->m_uType.m_pCurObject;
			if (pObject) {
				if (pObject->GetClass()->GetClassName() == "Class") {
					pValue = (IrisValue*)&((IrisClassBaseTag*)pObject->m_pNativeObject)->GetClass()->SearchClassVariable(strVariableName, bResult);
				}
				else if (pObject->GetClass()->GetClassName() == "Module") {
					pValue = (IrisValue*)&((IrisModuleBaseTag*)pObject->m_pNativeObject)->GetModule()->SearchClassVariable(strVariableName, bResult);
				}
				else {
					pValue = (IrisValue*)&pObject->GetClass()->SearchClassVariable(strVariableName, bResult);
				}

			}
			else {
				pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strVariableName, bResult);
			}
			if (bResult) {
				return *pValue;
			}

			pContextEnvrionment = pContextEnvrionment->m_pUpperContextEnvironment;
		}

		if (bResult) {
			return *pValue;
		}
		else {
			pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strVariableName, bResult);
			if (bResult) {
				return *pValue;
			}
			return IrisInterpreter::CurInstance()->Nil();
		}
	}
}

const IrisValue& IrisClosureBlock::GetConstance(const string& strConstanceName, bool& bResult) {
	//IrisValue ivResult{ IrisInterpreter::CurInstance()->Nil() };
	IrisValue* pValue = nullptr;
	bResult = false;
	IrisContextEnvironment* pContextEnvrionment = m_pUpperContextEnvironment;
	while (pContextEnvrionment) {
		IrisObject* pObject = pContextEnvrionment->m_uType.m_pCurObject;
		if (pObject->GetClass()->GetClassName() == "Class") {
			pValue = (IrisValue*)&((IrisClassBaseTag*)pObject->m_pNativeObject)->GetClass()->SearchConstance(strConstanceName, bResult);
		}
		else if (pObject->GetClass()->GetClassName() == "Module") {
			pValue = (IrisValue*)&((IrisModuleBaseTag*)pObject->m_pNativeObject)->GetModule()->SearchConstance(strConstanceName, bResult);
		}
		else {
			pValue = (IrisValue*)&pObject->GetClass()->SearchConstance(strConstanceName, bResult);
		}
		if (bResult) {
			return *pValue;
		}
		pContextEnvrionment = pContextEnvrionment->m_pUpperContextEnvironment;
	}

	if (bResult) {
		return *pValue;
	}
	else {
		pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetConstance(strConstanceName, bResult);
		if (bResult) {
			return *pValue;
		}
		return IrisInterpreter::CurInstance()->Nil();
	}
}

void IrisClosureBlock::Mark() {
	m_pNativeObject->Mark();
	for (auto value : m_mpOtherVariables) {
		value.second.m_ivValue.GetObject()->Mark();
	}

	//IrisContextEnvironment* pContext = m_pCurContextEnvironment;
	//while (pContext) {
	//	//pContext->m_bIsReferenced = true;
	//	pContext = pContext->m_pUpperContextEnvironment;
	//}
}

void IrisClosureBlock::AddLocalVariable(const string& strVariableName, const IrisValue& ivValue) {
	m_pCurContextEnvironment->AddLoaclVariable(strVariableName, ivValue);
}

void IrisClosureBlock::AddOtherVariable(const string& strVariableName, const IrisValue& ivValue) {
	IrisVariable ivbVariable;
	ivbVariable.m_strName = strVariableName;
	ivbVariable.m_ivValue = ivValue;

	if (m_mpOtherVariables.find(strVariableName) != m_mpOtherVariables.end()) {
		m_mpOtherVariables[strVariableName] = ivbVariable;
	}
	else {
		m_mpOtherVariables.insert(_VariablePair(strVariableName, ivbVariable));
	}
}

IrisStatementResult IrisClosureBlock::Excute(IrisValues* pValues) {
	IrisStatementResult srResult;

	m_pCurContextEnvironment->m_pExcuteBlock = this;

	if (m_pParameters) {
		if (!pValues) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ParameterNotFitIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of block assigned is not fit.");
			srResult.m_ivValue = IrisInterpreter::CurInstance()->Nil();
			return srResult;
		}
		else if (m_pParameters->GetSize() != pValues->size()) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ParameterNotFitIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of block assigned is not fit.");
			srResult.m_ivValue = IrisInterpreter::CurInstance()->Nil();
			return srResult;
		}
	}
	else {
		if(pValues) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ParameterNotFitIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of block assigned is not fit.");
			srResult.m_ivValue = IrisInterpreter::CurInstance()->Nil();
			return srResult;
		}
	}

	vector<IrisValue>::iterator it = pValues->begin();
	m_pParameters->Ergodic(
		[&](IrisIdentifier* pIdentifier) {
		bool bResult = false;
		IrisValue& ivValue = (IrisValue&)m_pCurContextEnvironment->GetVariableValue(pIdentifier->m_strIdentifier, bResult);
		if (bResult) {
			ivValue.SetObject(((IrisValue&)*(it++)).GetObject());
		}
		else {
			m_pCurContextEnvironment->AddLoaclVariable(pIdentifier->m_strIdentifier, (const IrisValue)*(it++));
		}
	}
	);

	if (m_pStatements) {
		for (auto stmt : m_pStatements->m_lsList) {
			srResult =  stmt->Excute(m_pCurContextEnvironment);

			if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return
				|| srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break
				|| srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue
				|| IrisInterpreter::CurInstance()->HaveIrregular()) {
				break;
			}
		}
	}

	m_pCurContextEnvironment->m_pExcuteBlock = nullptr;

	return srResult;
}

IrisClosureBlock::~IrisClosureBlock()
{
}
