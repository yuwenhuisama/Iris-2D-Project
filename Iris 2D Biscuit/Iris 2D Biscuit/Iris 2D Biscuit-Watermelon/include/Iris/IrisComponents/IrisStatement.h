#ifndef _H_IRISSTATEMENT_
#define _H_IRISSTATEMENT_

class IrisExpression;
class IrisNormalStatement;
class IrisClassStatement;
class IrisModuleStatement;
class IrisInterfaceStatement;
class IrisFunctionStatement;
class IrisIfStatement;
class IrisSwitchStatement;
class IrisForStatement;
class IrisOrderStatement;
class IrisReturnStatement;
class IrisBreakStatement;
class IrisContinueStatement;
class IrisInterfaceFunctionStatement;
class IrisGroanStatement;
class IrisContextEnvironment;
class IrisStatementResult;
class IrisGetterStatement;
class IrisSetterStatement;
class IrisGSetterStatement;
class IrisAuthorityStatement;
class IrisBlockStatement;
class IrisCastStatement;
class IrisSuperStatement;

class IrisValue;

class IrisStatement {
public:
	enum class StatementType {
		NormalStatement = 0,
		ClassStatement,
		ModuleStatement,
		InterfaceStatement,
		FunctionStatement,
		IfStatement,
		SwitchStatement,
		ForStatement,
		OrderStatement,
		ReturnStatement,
		BreakStatement,
		ContinueStatement,
		InterfaceFunctionStatement,
		GroanStatement,
		SetterStatement,
		GetterStatement,
		GSetterStatement,
		Authority,
		BlockStatement,
		CastStatement,
		SuperStatement,
	};
	StatementType m_eStatementType;
	union {
		IrisNormalStatement* m_pNormalStatement = nullptr;
		IrisClassStatement* m_pClassStatement;
		IrisModuleStatement* m_pModuleStatement;
		IrisInterfaceStatement* m_pInterfaceStatement;
		IrisFunctionStatement* m_pFunctionStatement;
		IrisIfStatement* m_pIfStatement;
		IrisSwitchStatement* m_pSwitchStatement;
		IrisForStatement* m_pForStatement;
		IrisOrderStatement* m_pOrderStatement;
		IrisReturnStatement* m_pReturnStatement;
		IrisBreakStatement* m_pBreakStatement;
		IrisContinueStatement* m_pContinueStatement;
		IrisInterfaceFunctionStatement* m_pInterfaceFunctionStatement;
		IrisGroanStatement* m_pGroanStatement;
		IrisGetterStatement* m_pGetterStatement;
		IrisSetterStatement* m_pSetterStatement;
		IrisGSetterStatement* m_pGSetterStatement;
		IrisAuthorityStatement* m_pAuthorityStatement;
		IrisBlockStatement* m_pBlockStatement;
		IrisCastStatement* m_pCastStatement;
		IrisSuperStatement* m_pSuperStatement;
	} m_uType;

	int m_nLineNumber = 0;

public:

	IrisStatementResult ExcuteFunctionStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteIfStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteConditionIf(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteLoopIf(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteForStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteSwitchStatement(IrisContextEnvironment* pContexEnvironment);
	
	IrisStatementResult ExcuteModuleStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteClassStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteGetterStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteSetterStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteGSetterStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteInterfaceStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteInterfaceFunctionStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteAuthorityStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteOrderStatement(IrisContextEnvironment* pContexEnvironment);
	IrisStatementResult ExcuteGroanStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteCastStatement(IrisContextEnvironment* pContexEnvironment);

	IrisStatementResult ExcuteSuperStatement(IrisContextEnvironment* pContextEnvironment);

	IrisStatementResult Excute(IrisContextEnvironment* pContexEnvironment);
	IrisStatement();
	~IrisStatement();
};

#endif;