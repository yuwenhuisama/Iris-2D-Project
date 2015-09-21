#include "IrisStatementResult.h"


IrisStatementResult::IrisStatementResult(const IrisValue& ivValue, StatementResultType eType) : m_ivValue(ivValue), m_eReturnType(eType) {
}


IrisStatementResult::~IrisStatementResult()
{
}
