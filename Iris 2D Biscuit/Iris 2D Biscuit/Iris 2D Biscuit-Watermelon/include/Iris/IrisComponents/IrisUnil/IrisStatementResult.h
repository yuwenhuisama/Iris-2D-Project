#ifndef _H_IRISSTATEMENTRESULT_
#define _H_IRISSTATEMENTRESULT_

#include "IrisValue.h"

class IrisStatementResult
{
public:
	enum class StatementResultType {
		Normal = 0,
		Break,
		Continue,
		Return,
	};

	IrisValue m_ivValue;
	StatementResultType m_eReturnType = StatementResultType::Normal;

	IrisStatementResult() = default;

	//operator IrisValue() { return m_ivValue; }

	IrisStatementResult(const IrisValue& ivValue, StatementResultType eType);
	~IrisStatementResult();
};

#endif