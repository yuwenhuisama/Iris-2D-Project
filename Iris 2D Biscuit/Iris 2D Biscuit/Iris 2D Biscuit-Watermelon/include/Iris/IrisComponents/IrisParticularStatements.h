#ifndef _H_IRISUNILCONPONENT_
#define _H_IRISUNILCONPONENT_

#include "IrisExpression.h"
#include "IrisBlock.h"
#include "IrisIdentifier.h"

class IrisHashPair {
public:
	IrisExpression* m_pKey = nullptr;
	IrisExpression* m_pValue = nullptr;

public:
	IrisHashPair(IrisExpression* pKey, IrisExpression* pValue) : m_pKey(pKey), m_pValue(pValue) {}
	~IrisHashPair() { 
		if(m_pKey)
			delete m_pKey;
		if (m_pValue)
			delete m_pValue; }
};

class IrisFieldIdentifier {
public:
	IrisList<IrisIdentifier*>* m_pList = nullptr;
	IrisIdentifier* m_pIdentifier = nullptr;
	bool m_bIsTopField = false;

public:
	IrisFieldIdentifier(IrisList<IrisIdentifier*>* pList, IrisIdentifier* pIdentifier, bool bIsTopField) : m_pList(pList), m_pIdentifier(pIdentifier), m_bIsTopField(bIsTopField) {}
	~IrisFieldIdentifier() {
		if (m_pList) {
			m_pList->Ergodic([](IrisIdentifier* x) { delete x; x = nullptr; });
			m_pList->Clear();
			delete m_pList;
		}
		if (m_pIdentifier)
			delete m_pIdentifier;
	}
};

class IrisNormalStatement {
public:
	IrisExpression* m_pExpression = nullptr;

public:
	IrisNormalStatement(IrisExpression* pExpression) : m_pExpression(pExpression) {}
	~IrisNormalStatement() {
		if (m_pExpression)
			delete m_pExpression; 
	}
};

class IrisClassStatement {
public:

	IrisIdentifier* m_pClassName = nullptr;
	IrisExpression* m_pSuperClassName = nullptr;
	IrisList<IrisExpression*>* m_pModules = nullptr;
	IrisList<IrisExpression*>* m_pInterfaces = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisClassStatement(IrisIdentifier* pClasssName, IrisExpression* pSuperClassName, IrisList<IrisExpression*>* pModules, IrisList<IrisExpression*>* pInterfaces, IrisBlock* pBlock) : m_pClassName(pClasssName), m_pSuperClassName(pSuperClassName), m_pModules(pModules), m_pInterfaces(pInterfaces), m_pBlock(pBlock) {}
	~IrisClassStatement() {
		if (m_pClassName)
			delete m_pClassName;
		if (m_pSuperClassName)
			delete m_pSuperClassName;
		if (m_pModules) {
			m_pModules->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pModules->Clear();
		}
		if (m_pInterfaces) {
			m_pInterfaces->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pInterfaces->Clear();
			delete m_pInterfaces;
		}
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisModuleStatement {
public:
	IrisIdentifier* m_pModuleName = nullptr;
	IrisList<IrisExpression*>* m_pModules = nullptr;
	IrisList<IrisExpression*>* m_pInterfaces = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisModuleStatement(IrisIdentifier* pModuleName, IrisList<IrisExpression*>* pModules, IrisList<IrisExpression*>* pInterfaces, IrisBlock* pBlock) : m_pModuleName(pModuleName), m_pModules(pModules), m_pInterfaces(pInterfaces), m_pBlock(pBlock) {}
	~IrisModuleStatement() {
		if (m_pModuleName)
			delete m_pModuleName;
		if (m_pModules) {
			m_pModules->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pModules->Clear();
			delete m_pModules;
		}
		if (m_pInterfaces) {
			m_pInterfaces->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pInterfaces->Clear();
			delete m_pInterfaces;
		}
		if (m_pBlock) {
			delete m_pBlock;
		}
	}
};

class IrisInterfaceStatement {
public:
	IrisIdentifier* m_pInterfaceName = nullptr;
	IrisList<IrisExpression*>* m_pInterfaces = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisInterfaceStatement(IrisIdentifier* pInterfaceName, IrisList<IrisExpression*>* pInterfaces, IrisBlock* pBlock) : m_pInterfaceName(pInterfaceName), m_pInterfaces(pInterfaces), m_pBlock(pBlock) {}
	~IrisInterfaceStatement() {
		if (m_pInterfaceName)
			delete m_pInterfaceName;
		if (m_pInterfaces) {
			m_pInterfaces->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pInterfaces->Clear();
			delete m_pInterfaces;
		}
		if (m_pBlock) {
			delete m_pBlock;
		}
	}
};

class IrisFunctionHeader {
public:
	IrisIdentifier* m_pFunctionName = nullptr;
	IrisList<IrisIdentifier*>* m_pParameters = nullptr;
	IrisIdentifier* m_pVariableParameter = nullptr;
	bool m_bIsClassMethod = false;

public:
	IrisFunctionHeader(IrisIdentifier* pFunctionName, IrisList<IrisIdentifier*>* pParameters, IrisIdentifier* pVariableParameter, bool bIsClassMethod) : m_pFunctionName(pFunctionName), m_pParameters(pParameters), m_pVariableParameter(pVariableParameter), m_bIsClassMethod(bIsClassMethod) {}
	~IrisFunctionHeader() {
		if (m_pFunctionName)
			delete m_pFunctionName;
		if (m_pParameters) {
			m_pParameters->Ergodic([](IrisIdentifier* x) { delete x; x = nullptr; });
			m_pParameters->Clear();
			delete m_pParameters;
		}
		if (m_pVariableParameter)
			delete m_pVariableParameter;
	}

	friend class IrisFunctionStatement;
	friend class IrisMethod;
};

class IrisFunctionStatement {
public:
	IrisFunctionHeader* m_pFunctionHeader = nullptr;
	IrisBlock* m_pWithBlock = nullptr;
	IrisBlock* m_pWithoutBlock = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisFunctionStatement(IrisFunctionHeader* pFunctionHeader, IrisBlock* pWithBlock, IrisBlock* pWithoutBlock, IrisBlock* pBlock) : m_pFunctionHeader(pFunctionHeader), m_pWithBlock(pWithBlock), m_pWithoutBlock(pWithoutBlock), m_pBlock(pBlock) {}
	~IrisFunctionStatement() {
		if (m_pFunctionHeader)
			delete m_pFunctionHeader;
		if (m_pWithBlock)
			delete m_pWithBlock;
		if (m_pWithoutBlock)
			delete m_pWithoutBlock;
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisElseIf {
public:
	IrisExpression* m_pCondition = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisElseIf(IrisExpression* pCondition, IrisBlock* pBlock) : m_pCondition(pCondition), m_pBlock(pBlock) {}
	~IrisElseIf() {
		if (m_pCondition)
			delete m_pCondition;
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisConditionIf {
public:
	IrisExpression* m_pCondition = nullptr;
	IrisBlock* m_pBlock = nullptr;
	IrisList<IrisElseIf*>* m_pIrisElseIf = nullptr;
	IrisBlock* m_pElseBlock = nullptr;

public:
	IrisConditionIf(IrisExpression* pCondition, IrisBlock* pBlock, IrisList<IrisElseIf*>* pIrisElseIf, IrisBlock* pElseBlock) : m_pCondition(pCondition), m_pBlock(pBlock), m_pIrisElseIf(pIrisElseIf), m_pElseBlock(pElseBlock) {}
	~IrisConditionIf() {
		if (m_pCondition)
			delete m_pCondition;
		if (m_pBlock)
			delete m_pBlock;
		if (m_pIrisElseIf) {
			m_pIrisElseIf->Ergodic([](IrisElseIf* x) { delete x; x = nullptr; });
			m_pIrisElseIf->Clear();
			delete m_pIrisElseIf;
		}
		if (m_pElseBlock)
			delete m_pElseBlock;
	}
};

class IrisLoopIf {
public:
	IrisExpression* m_pCondition = nullptr;
	IrisExpression* m_pLoopTime = nullptr;
	IrisIdentifier* m_pLogVariable = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisLoopIf(IrisExpression* pCondition, IrisExpression* pLoopTime, IrisIdentifier* pLogVariable, IrisBlock* pBlock) : m_pCondition(pCondition), m_pLoopTime(pLoopTime), m_pLogVariable(pLogVariable), m_pBlock(pBlock) {}
	~IrisLoopIf() {
		if (m_pCondition)
			delete m_pCondition;
		if (m_pLoopTime)
			delete m_pLoopTime;
		if (m_pLogVariable)
			delete m_pLogVariable;
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisIfStatement{
public:
	enum class IfType {
		ConditionIf = 0,
		LoopIf,
	} m_eType = IfType::ConditionIf;

	union {
		IrisConditionIf* m_pConditionIf = nullptr;
		IrisLoopIf* m_pLoopIf;
	} m_uType;

public:
	IrisIfStatement(IrisConditionIf* pConditionIf) { m_eType = IfType::ConditionIf; m_uType.m_pConditionIf = pConditionIf; }
	IrisIfStatement(IrisLoopIf* pLoopIf) { m_eType = IfType::LoopIf; m_uType.m_pLoopIf = pLoopIf; }
	~IrisIfStatement() {
		switch (m_eType)
		{
		case IrisIfStatement::IfType::ConditionIf:
			delete m_uType.m_pConditionIf;
			break;
		case IrisIfStatement::IfType::LoopIf:
			delete m_uType.m_pLoopIf;
			break;
		}
	}
};

class IrisWhen {
public:
	IrisList<IrisExpression*>* m_pExpressions = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisWhen(IrisList<IrisExpression*>* pExpressions, IrisBlock* pBlock) : m_pExpressions(pExpressions), m_pBlock(pBlock) {}
	~IrisWhen() {
		if (m_pExpressions) {
			m_pExpressions->Ergodic([](IrisExpression* x) { delete x; x = nullptr; });
			m_pExpressions->Clear();
			delete m_pExpressions;
		}
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisSwitchBlock {
public:
	IrisList<IrisWhen*>* m_pWhenList = nullptr;
	IrisBlock* m_pElseBlock = nullptr;

public:
	IrisSwitchBlock(IrisList<IrisWhen*>* pWhenList, IrisBlock* pElseBlock) : m_pWhenList(pWhenList), m_pElseBlock(pElseBlock) {}
	~IrisSwitchBlock() {
		if (m_pWhenList) {
			m_pWhenList->Ergodic([](IrisWhen* x) { delete x; x = nullptr; });
			m_pWhenList->Clear();
			delete m_pWhenList;
		}
		if (m_pElseBlock)
			delete m_pElseBlock;
	}
};

class IrisSwitchStatement{
public:
	IrisExpression* m_pCondition = nullptr;
	IrisSwitchBlock* m_pSwitchBlock = nullptr;

public:
	IrisSwitchStatement(IrisExpression* pCondition, IrisSwitchBlock* pSwitchBlock) : m_pCondition(pCondition), m_pSwitchBlock(pSwitchBlock) {}
	~IrisSwitchStatement() {
		if (m_pCondition)
			delete m_pCondition;
		if (m_pSwitchBlock)
			delete m_pSwitchBlock;
	}
};

class IrisForStatement {
public:
	IrisIdentifier* m_pIter1 = nullptr;
	IrisIdentifier* m_pIter2 = nullptr;
	IrisExpression* m_pSource = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisForStatement(IrisIdentifier* pIter1, IrisIdentifier* pIter2, IrisExpression* pSource, IrisBlock* pBlock) : m_pIter1(pIter1), m_pIter2(pIter2), m_pSource(pSource), m_pBlock(pBlock) {}
	~IrisForStatement() {
		if (m_pIter1)
			delete m_pIter1;
		if (m_pIter2)
			delete m_pIter2;
		if (m_pSource)
			delete m_pSource;
		if (m_pBlock)
			delete m_pBlock;
	}
};

class IrisOrderStatement {
public:
	IrisBlock* m_pOrderBlock = nullptr;
	IrisIdentifier* m_pIrregularObject = nullptr;
	IrisBlock* m_pServeBlock = nullptr;
	IrisBlock* m_pIgnoreBlock = nullptr;

public:
	IrisOrderStatement(IrisBlock* pOrderBlock, IrisIdentifier* pIrregularObject, IrisBlock* pServeBlock, IrisBlock* pIgnoreBlock) : m_pOrderBlock(pOrderBlock), m_pIrregularObject(pIrregularObject), m_pServeBlock(pServeBlock), m_pIgnoreBlock(pIgnoreBlock) {}
	~IrisOrderStatement() {
		if (m_pOrderBlock)
			delete m_pOrderBlock;
		if (m_pIrregularObject)
			delete m_pIrregularObject;
		if (m_pServeBlock)
			delete m_pServeBlock;
		if (m_pIgnoreBlock)
			delete m_pIgnoreBlock;
	}
};

class IrisReturnStatement {
public:
	IrisExpression* m_pReturnExpression = nullptr;

public:
	IrisReturnStatement(IrisExpression* pReturnExpression) : m_pReturnExpression(pReturnExpression) {}
	~IrisReturnStatement() {
		if (m_pReturnExpression)
			delete m_pReturnExpression;
	}
};

class IrisBreakStatement {
public:
	IrisIdentifier* m_pLabel = nullptr;

public:
	IrisBreakStatement(IrisIdentifier* pLabel) : m_pLabel(pLabel) {}
	~IrisBreakStatement() {
		if (m_pLabel)
			delete m_pLabel;
	}
};

class IrisContinueStatement {
public:
	IrisIdentifier* m_pLabel = nullptr;

public:
	IrisContinueStatement(IrisIdentifier* pLabel) : m_pLabel(pLabel) {}
	~IrisContinueStatement() {
		if (m_pLabel)
			delete m_pLabel;
	}
};

class IrisInterfaceFunctionStatement {
public:
	IrisIdentifier* m_pFunctionName = nullptr;
	IrisList<IrisIdentifier*>* m_pParameters = nullptr;
	IrisIdentifier* m_pVariableParameter = nullptr;

public:
	IrisInterfaceFunctionStatement(IrisIdentifier* pFunctionName, IrisList<IrisIdentifier*>* pParameters, IrisIdentifier* pVariableParameters) : m_pFunctionName(pFunctionName), m_pParameters(pParameters), m_pVariableParameter(pVariableParameters) {}
	~IrisInterfaceFunctionStatement() {
		if (m_pFunctionName)
			delete m_pFunctionName;
		if (m_pParameters) {
			m_pParameters->Ergodic([](IrisIdentifier* x) { delete x; x = nullptr; });
			m_pParameters->Clear();
			delete m_pParameters;
		}
		if (m_pVariableParameter)
			delete m_pVariableParameter;
	}
};

class IrisGroanStatement {
public:
	IrisExpression* m_pGroanExpression = nullptr;

public:
	IrisGroanStatement(IrisExpression* pGroanExpression) : m_pGroanExpression(pGroanExpression) {}
	~IrisGroanStatement() {
		if (m_pGroanExpression)
			delete m_pGroanExpression;
	}

};

class IrisSetterStatement {
public:
	IrisIdentifier* m_pSetteredVariable = nullptr;
	IrisIdentifier* m_pParamName = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisSetterStatement(IrisIdentifier* pSetteredVariable, IrisIdentifier* pParamName, IrisBlock* pBlock) : m_pSetteredVariable(pSetteredVariable), m_pParamName(pParamName), m_pBlock(pBlock) {}
	~IrisSetterStatement() {
		if (m_pSetteredVariable) {
			delete m_pSetteredVariable;
		}
		if (m_pParamName) {
			delete m_pParamName;
		}
		//if (m_pBlock) {
		//	delete m_pBlock;
		//}
	}
};

class IrisGetterStatement {
public:
	IrisIdentifier* m_pGetteredVariable = nullptr;
	IrisBlock* m_pBlock = nullptr;

public:
	IrisGetterStatement(IrisIdentifier* pGetteredVariable, IrisBlock* pBlock) : m_pGetteredVariable(pGetteredVariable), m_pBlock(pBlock) {}
	~IrisGetterStatement() {
		if (m_pGetteredVariable) {
			delete m_pGetteredVariable;
		}
		//if (m_pBlock) {
		//	delete m_pBlock;
		//}
	}
};

class IrisGSetterStatement {
public:
	IrisIdentifier* m_pGSetteredVariable = nullptr;

public:
	IrisGSetterStatement(IrisIdentifier* pGSetteredVariable) : m_pGSetteredVariable(pGSetteredVariable) {}
	~IrisGSetterStatement() {
		if (m_pGSetteredVariable) {
			delete m_pGSetteredVariable;
		}
	}

};

class IrisAuthorityStatement {
public:
	enum class AuthorityEnvironment {
		Class = 0,
		Module,
	};

	enum class AuthorityTarget {
		InstanceMethod = 0,
		ClassMethod,
	};

	enum class AuthorityType {
		EveryOne = 0,
		Relative,
		Personal,
	};

public:
	IrisIdentifier* m_pMethodName = nullptr;
	AuthorityEnvironment m_eEnvironment = AuthorityEnvironment::Class;
	AuthorityTarget m_eTarget = AuthorityTarget::InstanceMethod;
	AuthorityType m_eType = AuthorityType::EveryOne;

public:
	IrisAuthorityStatement(IrisIdentifier* pMethodName) : m_pMethodName(pMethodName) {}
	~IrisAuthorityStatement() {
		if (m_pMethodName) {
			delete m_pMethodName;
		}
	}
};

class IrisClosureBlockLiteral {
public:
	IrisList<IrisIdentifier*>* m_pParameters = nullptr;
	IrisList<IrisStatement*>* m_pStatements = nullptr;

public:
	IrisClosureBlockLiteral(IrisList<IrisIdentifier*>* pParameters, IrisList<IrisStatement*>* pStatements) : m_pParameters(pParameters), m_pStatements(pStatements) {}
	~IrisClosureBlockLiteral() {
		if (m_pParameters) {
			m_pParameters->Ergodic(
				[](IrisIdentifier* pIdentifier) { delete pIdentifier; pIdentifier = nullptr; }
			);
		}
		if (m_pStatements) {
			m_pStatements->Ergodic(
				[](IrisStatement* pStatement) { delete pStatement; pStatement = nullptr; }
			);
		}
	}
};

class IrisBlockStatement {
public:
	IrisBlockStatement() {}
	~IrisBlockStatement() {}
};

class IrisCastStatement {
public:
	IrisList<IrisExpression*>* m_pParameters = nullptr;
	
public:
	IrisCastStatement(IrisList<IrisExpression*>* pParameters) : m_pParameters(pParameters) {}
	~IrisCastStatement() {
		if (m_pParameters) {
			m_pParameters->Ergodic(
				[](IrisExpression* pExpression) { delete pExpression; pExpression = nullptr; }
			);
		}
	}
};

class IrisSuperStatement {
public:
	IrisList<IrisExpression*>* m_pParameters = nullptr;

public:
	IrisSuperStatement(IrisList<IrisExpression*>* pParameters) : m_pParameters(pParameters) {}
	~IrisSuperStatement() {
		if (m_pParameters) {
			m_pParameters->Ergodic(
				[](IrisExpression* pExpression) { delete pExpression; pExpression = nullptr; }
			);
		}
	}
};

#endif