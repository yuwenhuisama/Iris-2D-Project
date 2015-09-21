#include "IrisBlock.h"
#include "IrisInterpreter.h"

IrisBlock::IrisBlock(IrisList<IrisStatement*>* pStatements) : m_pStatements(pStatements)
{
}

IrisStatementResult IrisBlock::_ExcuteRuntimeStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult;

	//if (pStatement->m_eStatementType == IrisStatement::StatementType::BreakStatement
	//	&& pContextEnvironment->m_eUpperType != IrisContextEnvironment::EnvrionmentUpperType::Loop) {
	//	IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, pStatement->m_nLineNumber, "Statement of break can only be used in a loop.");
	//	return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	//}
	//else if (pStatement->m_eStatementType == IrisStatement::StatementType::ContinueStatement
	//	&& pContextEnvironment->m_eUpperType != IrisContextEnvironment::EnvrionmentUpperType::Loop) {
	//	IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, pStatement->m_nLineNumber, "Statement of continue can only be used in a loop.");
	//	return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	//}

	srResult = pStatement->Excute(pContextEnvironment);

	return srResult;
}

// 全局中执行语句的特殊处理 比如if等
IrisStatementResult IrisBlock::_ExcuteMainRuntimeStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult;

	// **Error**

	//else if (pStatement->m_eStatementType == IrisStatement::StatementType::BreakStatement
	//	&& pContextEnvironment->m_eUpperType != IrisContextEnvironment::EnvrionmentUpperType::Loop) {
	//	IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, pStatement->m_nLineNumber, "Statement of break can only be used in a loop.");
	//	return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	//}
	//else if (pStatement->m_eStatementType == IrisStatement::StatementType::ContinueStatement
	//	&& pContextEnvironment->m_eUpperType != IrisContextEnvironment::EnvrionmentUpperType::Loop) {
	//	IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, pStatement->m_nLineNumber, "Statement of continue can only be used in a loop.");
	//	return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	//}

	srResult = pStatement->Excute(pContextEnvironment);

	return srResult;
}

IrisStatementResult IrisBlock::_ExcuteModuleStatment(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	srResult = pStatement->Excute(pContextEnvironment);
	return srResult;
}

IrisStatementResult IrisBlock::_ExcuteClassStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	srResult = pStatement->Excute(pContextEnvironment);
	return srResult;
}

IrisStatementResult IrisBlock::_ExcuteInterfaceStatment(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	srResult = pStatement->Excute(pContextEnvironment);
	return srResult;
}

IrisStatementResult IrisBlock::Execute(IrisContextEnvironment* pContextEnvrionment){
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	//IrisValue ivResult = pInterpreter->Nil();
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	if (!m_pStatements) {
		srResult.m_ivValue = pInterpreter->Nil();
		srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
		return srResult;
	}

	for (auto stmt : m_pStatements->m_lsList) {
		if (pContextEnvrionment) {
			switch (pContextEnvrionment->m_eType)
			{
			case IrisContextEnvironment::EnvironmentType::ClassDefineTime:
				srResult = _ExcuteClassStatement(stmt, pContextEnvrionment);
				break;
			case IrisContextEnvironment::EnvironmentType::InterfaceDefineTime:
				srResult = _ExcuteInterfaceStatment(stmt, pContextEnvrionment);
				break;
			case IrisContextEnvironment::EnvironmentType::ModuleDefineTime:
				srResult = _ExcuteModuleStatment(stmt, pContextEnvrionment);
				break;
			case IrisContextEnvironment::EnvironmentType::Runtime:
				srResult = _ExcuteRuntimeStatement(stmt, pContextEnvrionment);
				break;
			default:
				break;
			}
		}
		else {
			srResult = _ExcuteMainRuntimeStatement(stmt, pContextEnvrionment);
		}

		if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return
			|| srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break
			|| srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue
			|| IrisInterpreter::CurInstance()->HaveIrregular()) {
			break;
		}
	}
	return srResult;
}

IrisBlock::~IrisBlock()
{
}
