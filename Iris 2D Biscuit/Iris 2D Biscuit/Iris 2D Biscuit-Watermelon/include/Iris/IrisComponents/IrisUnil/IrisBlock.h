#ifndef _H_IRISBLOCK_
#define _H_IRISBLOCK_

#include "IrisStatement.h"
#include "IrisValue.h"
#include "IrisList.h"
#include "IrisStatementResult.h"

class IrisBlock
{
private:
	IrisList<IrisStatement*>* m_pStatements = nullptr;

public:
	enum class IrisBlockRunType {
		Function = 0,
		ClassDefine,
		ModuleDefine,
	};

	enum class ResultType {
		Normal = 0,
		Break,
		Return,
	};

private:
	IrisStatementResult _ExcuteRuntimeStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment);
	IrisStatementResult _ExcuteMainRuntimeStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment);

	IrisStatementResult _ExcuteModuleStatment(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment);
	IrisStatementResult _ExcuteClassStatement(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment);
	IrisStatementResult _ExcuteInterfaceStatment(IrisStatement* pStatement, IrisContextEnvironment* pContextEnvironment);

public:
	IrisBlock(IrisList<IrisStatement*>* pStatements);
	IrisStatementResult Execute(IrisContextEnvironment* pContextEnvrionment);
	~IrisBlock();
};

#endif