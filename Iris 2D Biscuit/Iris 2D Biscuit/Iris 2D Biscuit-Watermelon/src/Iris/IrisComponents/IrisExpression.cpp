#include "IrisExpression.h"
#include "IrisParticularStatements.h"
#include "IrisInterpreter.h"
#include "IrisObject.h"
#include "IrisIdentifier.h"
#include "IrisContextEnvironment.h"
#include "IrisClassBaseTag.h"
#include "IrisModuleBaseTag.h"
#include "IrisClosureBlockBaseTag.h"

class IrisExpression::IrisBinaryExpression {
public:
	IrisExpression* m_pLeft = nullptr;
	IrisExpression* m_pRight = nullptr;
public:
	IrisBinaryExpression(IrisExpression* pLeft, IrisExpression* pRight) : m_pLeft(pLeft), m_pRight(pRight) {}
	~IrisBinaryExpression() {
		if (m_pLeft)
			delete m_pLeft;
		if (m_pRight)
			delete m_pRight;
	}
};

class IrisExpression::IrisUnaryExpression {
public:
	IrisExpression* m_pExpression = nullptr;
public:
	IrisUnaryExpression(IrisExpression* pExpression) : m_pExpression(pExpression) {	}
	~IrisUnaryExpression() {
		if (m_pExpression)
			delete m_pExpression;
	}
};

class IrisExpression::IrisIdentifierExpression {
public:
	IrisIdentifier* m_pIdentifier = nullptr;
public:
	IrisIdentifierExpression(IrisIdentifier* pIdentifier) : m_pIdentifier(pIdentifier) {}
	~IrisIdentifierExpression() {
		if (m_pIdentifier)
			delete m_pIdentifier;
	}
};

class IrisExpression::IrisNativeObjectExpression {
public:
	IrisObject* m_pObject = nullptr;
public:
	IrisNativeObjectExpression(IrisObject* pObject) : m_pObject(pObject) {}
	~IrisNativeObjectExpression() {}
};

class IrisExpression::IrisFunctionCallExpression {
public :
	IrisExpression* m_pObject = nullptr;
	IrisIdentifier* m_pFunctionName = nullptr;
	IrisList<IrisExpression*>* m_pParameters = nullptr;
	IrisClosureBlockLiteral* m_pClosureBlock = nullptr;

public:
	IrisFunctionCallExpression(IrisExpression* pObject, IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock) : m_pObject(pObject), m_pFunctionName(pFunctionName), m_pParameters(pParameters), m_pClosureBlock(pClosureBlock) {}
	~IrisFunctionCallExpression() {
		if (m_pObject){
			delete m_pObject;
		}
		if (m_pFunctionName) {
			delete m_pFunctionName;
		}
		if (m_pParameters) {
			m_pParameters->Ergodic(
				[](IrisExpression* pExpression) {delete pExpression; pExpression = nullptr; }
			);
			delete m_pParameters;
		}
		if (m_pClosureBlock) {
			delete m_pClosureBlock;
		}
	}
};

class IrisExpression::IrisSelfFunctionCallExpression {
public:
	IrisIdentifier* m_pFunctionName = nullptr;
	IrisList<IrisExpression*>* m_pParameters = nullptr;
	IrisClosureBlockLiteral* m_pClosureBlock = nullptr;

public:
	IrisSelfFunctionCallExpression(IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock) : m_pFunctionName(pFunctionName), m_pParameters(pParameters), m_pClosureBlock(pClosureBlock) { }
	~IrisSelfFunctionCallExpression() {
		if (m_pFunctionName) {
			delete m_pFunctionName;
		}
		if (m_pParameters) {
			m_pParameters->Ergodic(
				[](IrisExpression* pExpression) {delete pExpression; pExpression = nullptr; }
			);
			delete m_pParameters;
		}
		if (m_pClosureBlock) {
			delete m_pClosureBlock;
		}
	}
};

class IrisExpression::IrisFieldExpression {
public:
	IrisFieldIdentifier* m_pFieldIdentifier = nullptr;
public:
	IrisFieldExpression(IrisFieldIdentifier* pFieldIdentifier) : m_pFieldIdentifier(pFieldIdentifier){
	}
	~IrisFieldExpression() {
		if (m_pFieldIdentifier) {
			delete m_pFieldIdentifier;
		}
	}
};

class IrisExpression::IrisMemberExpression {
public:
	IrisExpression* m_pCaller = nullptr;
	IrisIdentifier* m_pProperty = nullptr;

public:
	IrisMemberExpression(IrisExpression* pCaller, IrisIdentifier* pPropery) : m_pCaller(pCaller), m_pProperty(pPropery) {}
	~IrisMemberExpression() {
		if (m_pCaller) {
			delete m_pCaller;
		}
		if (m_pProperty) {
			delete m_pProperty;
		}
	}
};

class IrisExpression::IrisSelfMemberExpression {
public:
	IrisIdentifier* m_pProperty = nullptr;

public:
	IrisSelfMemberExpression(IrisIdentifier* pProperty) : m_pProperty(pProperty) {}
	~IrisSelfMemberExpression() {
		if (m_pProperty) {
			delete m_pProperty;
		}
	}
};

class IrisExpression::IrisArrayExpression {
public:
	IrisList<IrisExpression*>* m_pElementList;

public:
	IrisArrayExpression(IrisList<IrisExpression*>* pElementList) : m_pElementList(pElementList) {}
	~IrisArrayExpression() {
		if (m_pElementList) {
			m_pElementList->Ergodic(
				[](IrisExpression* pExpression) { delete pExpression; pExpression = nullptr; }
			);
			delete m_pElementList;
		}
	}
};

class IrisExpression::IrisHashExpression {
public:
	IrisList<IrisHashPair*>* m_pHashPairs = nullptr;

public:
	IrisHashExpression(IrisList<IrisHashPair*>* pHashPairs) : m_pHashPairs(pHashPairs) {}
	~IrisHashExpression() {
		if (m_pHashPairs) {
			m_pHashPairs->Ergodic(
				[](IrisHashPair* pPair) { delete pPair; pPair = nullptr; }
			);
		}
	}
};

class IrisExpression::IrisIndexExpression {
public:
	IrisExpression* m_pTarget = nullptr;
	IrisExpression* m_pIndexer = nullptr;

public:
	IrisIndexExpression(IrisExpression* pTarget, IrisExpression* pIndexer) : m_pTarget(pTarget), m_pIndexer(pIndexer) {}
	~IrisIndexExpression() {
		if (m_pTarget) {
			delete m_pTarget;
		}
		if (m_pIndexer) {
			delete m_pIndexer;
		}
	}
};

IrisExpression::IrisExpression()
{
}

bool IrisExpression::_FieldIsSingleWithoutField(){
	return !m_uType.m_pFieldExpression->m_pFieldIdentifier->m_bIsTopField && !m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pList;
}

const string& IrisExpression::_FieldSingleName() {
	return m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pIdentifier->m_strIdentifier;
}

IrisExpression* IrisExpression::CreateBinaryExpression(ExpressionType eType, IrisExpression* pLeftExpression, IrisExpression* pRightExpression){
	IrisExpression* pExpression = new IrisExpression;
	IrisBinaryExpression* pBinaryExpression = new IrisBinaryExpression(pLeftExpression, pRightExpression);
	pExpression->m_eType = eType;
	pExpression->m_uType.m_pBinaryExpression = pBinaryExpression;

	return pExpression;
}

IrisExpression* IrisExpression::CreateUnaryExpression(ExpressionType eType, IrisExpression* pExpression){
	IrisExpression* pOutExpression = new IrisExpression;
	IrisUnaryExpression* pUnaryExpression = new IrisUnaryExpression(pExpression);
	pOutExpression->m_eType = eType;
	pOutExpression->m_uType.m_pUnaryExpression = pUnaryExpression;
	return pOutExpression;
}

IrisExpression* IrisExpression::CreateIndexExpression(IrisExpression* pObjectExpression, IrisExpression* pIndexExpression){
	IrisExpression* pExpression = new IrisExpression;
	IrisIndexExpression* pIndex = new IrisIndexExpression(pObjectExpression, pIndexExpression);
	pExpression->m_eType = IrisExpression::ExpressionType::Index;
	pExpression->m_uType.m_pIndexExpression = pIndex;

	return pExpression;
}

IrisExpression* IrisExpression::CreateFunctionCallExpression(IrisExpression* pObject, IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock){
	IrisExpression* pExpression = new IrisExpression;
	IrisFunctionCallExpression* pFunctionCallExpression = new IrisFunctionCallExpression(pObject, pFunctionName, pParameters, pClosureBlock);
	pExpression->m_eType = IrisExpression::ExpressionType::FunctionCall;
	pExpression->m_uType.m_pFunctionCallExpression = pFunctionCallExpression;

	return pExpression;
}

IrisExpression* IrisExpression::CreateSelfFunctionCallExpression(IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock){
	IrisExpression* pExpression = new IrisExpression;
	IrisSelfFunctionCallExpression* pSelfFunctionCallExpression = new IrisSelfFunctionCallExpression(pFunctionName, pParameters, pClosureBlock);
	pExpression->m_eType = IrisExpression::ExpressionType::SelfFunctionCall;
	pExpression->m_uType.m_pSelfCallExpression = pSelfFunctionCallExpression;

	return pExpression;
}

IrisExpression* IrisExpression::CreateMemberExpression(IrisExpression* pObjectExpression, IrisIdentifier* pMmberName){
	IrisExpression* pExpression = new IrisExpression;
	IrisMemberExpression* pMemberExpression = new IrisMemberExpression(pObjectExpression, pMmberName);
	pExpression->m_eType = IrisExpression::ExpressionType::Member;
	pExpression->m_uType.m_pMemberExpression = pMemberExpression;

	return pExpression;
}

IrisExpression* IrisExpression::CreateSelfMemberExpression(IrisIdentifier* pMmberName){
	IrisExpression* pExpression = new IrisExpression;
	IrisSelfMemberExpression* pSelfMemberExpression = new IrisSelfMemberExpression(pMmberName);
	pExpression->m_eType = IrisExpression::ExpressionType::SelfMember;
	pExpression->m_uType.m_pSelfMemberExpression = pSelfMemberExpression;

	return pExpression;
}

IrisExpression* IrisExpression::CreateFieldExpression(IrisList<IrisIdentifier*>* pList, IrisIdentifier* pIdentifier, bool bIsTop){
	IrisExpression* pExpression = new IrisExpression;
	IrisFieldIdentifier* pIrisFieldIdentifier = new IrisFieldIdentifier(pList, pIdentifier, bIsTop);
	pExpression->m_eType = IrisExpression::ExpressionType::FieldIdentifier;
	pExpression->m_uType.m_pFieldExpression = new IrisFieldExpression(pIrisFieldIdentifier);

	return pExpression;
}

IrisExpression* IrisExpression::CreateIdentifierExpression(IrisIdentifier* pIdentifier){
	IrisExpression* pExpression = new IrisExpression;
	IrisIdentifierExpression* pIdentifierExpression = new IrisIdentifierExpression(pIdentifier);
	pExpression->m_eType = ExpressionType::Identifier;
	pExpression->m_uType.m_pIdentifierExpression = pIdentifierExpression;
	return pExpression;
}

IrisExpression* IrisExpression::CreateInstantValueExpression(ExpressionType eType){
	IrisExpression* pExpression = new IrisExpression;
	//IrisInstantValueExpression* pIdentifierExpression = new IrisInstantValueExpression(eType);
	pExpression->m_eType = eType;
	//pExpression->m_uType.m_pIdentifierExpression = pIdentifierExpression;
	return pExpression;
}

IrisExpression* IrisExpression::CreateArrayExpression(IrisList<IrisExpression*>* pElements){
	IrisExpression* pExpression = new IrisExpression;
	IrisArrayExpression* pArrayExpression = new IrisArrayExpression(pElements);
	pExpression->m_eType = ExpressionType::Array;
	pExpression->m_uType.m_pArrayExpression = pArrayExpression;
	return pExpression;
}

IrisExpression* IrisExpression::CreateHashExpression(IrisList<IrisHashPair*>* pElements){
	IrisExpression* pExpression = new IrisExpression;
	IrisHashExpression* pHashExpression = new IrisHashExpression(pElements);
	pExpression->m_eType = ExpressionType::Hash;
	pExpression->m_uType.m_pHashExpression = pHashExpression;
	return pExpression;
}

IrisExpression* IrisExpression::CreateNativeObjectExpression(ExpressionType eType, IrisObject* pObject){
	IrisExpression* pExpression = new IrisExpression;
	IrisNativeObjectExpression* pNativeObjectExpression = new IrisNativeObjectExpression(pObject);
	pObject->m_bLiteralObject = true;
	pObject->m_bLiteralObjectAssigned = false;
	pExpression->m_eType = eType;
	pExpression->m_uType.m_pNativeObjectExpression = pNativeObjectExpression;
	return pExpression;
}

IrisValue IrisExpression::ExcuteAssign(IrisExpression* pLeft, const IrisValue& ivResult, IrisContextEnvironment* pContextEnvironment){

	if (((IrisValue&)ivResult).GetObjectPointer()->m_bLiteralObject) {
		((IrisValue&)ivResult).GetObjectPointer()->m_bLiteralObjectAssigned = true;
	}

	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

	// 出错
	if (pLeft->m_eType != ExpressionType::Identifier
		&& pLeft->m_eType != ExpressionType::Member
		&& pLeft->m_eType != ExpressionType::SelfMember
		&& pLeft->m_eType != ExpressionType::Index){
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::LeftValueIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Left value must be identifier, object's member, self'member or array/hash's index.");
		return IrisInterpreter::CurInstance()->Nil();
	}
	else if (pLeft->m_eType == ExpressionType::Member) {
		IrisValue ivObj = pLeft->m_uType.m_pMemberExpression->m_pCaller->Excute(pContextEnvironment);
		string strProperName = "__set_" + pLeft->m_uType.m_pMemberExpression->m_pProperty->m_strIdentifier;
		IrisValues ivsParam = { ivResult };
		return ivObj.GetObjectPointer()->CallInstanceFunction(strProperName, pContextEnvironment, &ivsParam, CallerSide::Outside);
	}
	else if (pLeft->m_eType == ExpressionType::SelfMember) {
		if (!pContextEnvironment || !pContextEnvironment->m_uType.m_pCurObject) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
			// **Error**
			return IrisInterpreter::CurInstance()->Nil();
		}

		if (pContextEnvironment && pContextEnvironment->m_bIsClosure) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
			// **Error**
			return IrisInterpreter::CurInstance()->Nil();
		}

		IrisObject* pObj = pContextEnvironment->m_uType.m_pCurObject;
		string strPropertyName = "@" + pLeft->m_uType.m_pSelfMemberExpression->m_pProperty->m_strIdentifier;

		bool bResult = false;
		IrisValue& ivTmpResult = (IrisValue&)pObj->GetInstanceValue(strPropertyName, bResult);

		if (!bResult) {
			pObj->AddInstanceValue(strPropertyName, ivResult);
			return ivResult;
		}
		ivTmpResult.SetObject(((IrisValue&)ivResult).GetObjectPointer());
		return ivTmpResult;
	}
	else if (pLeft->m_eType == ExpressionType::Index) {
		IrisValue ivObj = pLeft->m_uType.m_pIndexExpression->m_pTarget->Excute(pContextEnvironment);
		IrisValue ivIndex = pLeft->m_uType.m_pIndexExpression->m_pIndexer->Excute(pContextEnvironment);

		IrisValues ivsParam = { ivIndex, ivResult };
		return ivObj.GetObjectPointer()->CallInstanceFunction("[]=", pContextEnvironment, &ivsParam, CallerSide::Outside);
	}
	else {
		//ivResult = pRight->Excute(pContextEnvironment);
		IrisIdentifier::IdentifilerType eType = pLeft->m_uType.m_pIdentifierExpression->m_pIdentifier->m_eType;
		const string& strIdentifiler = pLeft->m_uType.m_pIdentifierExpression->m_pIdentifier->m_strIdentifier;
		switch (eType)
		{
		case IrisIdentifier::IdentifilerType::Constance:
			// 只允许在定义类、常量或者全局环境下定义常量、且常量不可二次赋值
			if (!pContextEnvironment) {
				// 不存在就定义
				bool bResult = false;
				const IrisValue& ivTmp = pInterpreter->GetConstance(strIdentifiler, bResult);
				if (!bResult){
					pInterpreter->AddConstance(strIdentifiler, ivResult);
				}
				// 若存在则报错
				else {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ConstanceReassignIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Constance can not be reassigned.");
					return IrisInterpreter::CurInstance()->Nil();
				}
			}
			else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ClassDefineTime){
				IrisClass* pCurClass = pContextEnvironment->m_uType.m_pClass;
				// 不存在就定义
				bool bResult = false;
				const IrisValue& ivTmp = pCurClass->SearchConstance(strIdentifiler, bResult);
				if (!bResult){
					pCurClass->AddConstance(strIdentifiler, ivResult);
				}
				// 若存在则报错
				else {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ConstanceReassignIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Constance can not be reassigned.");
					return IrisInterpreter::CurInstance()->Nil();
				}
			}
			else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ModuleDefineTime){
				IrisModule* pCurModule = pContextEnvironment->m_uType.m_pModule;
				bool bResult = false;
				const IrisValue& ivTmp = pCurModule->SearchConstance(strIdentifiler, bResult);
				if (!bResult){
					pCurModule->AddConstance(strIdentifiler, ivResult);
				}
				// 若存在则报错
				else {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ConstanceReassignIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Constance can not be reassigned.");
					return IrisInterpreter::CurInstance()->Nil();
				}
			}
			// 其他情况下都是非法的
			else{
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ConstanceDeclareIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Constance can not be declared here.");
				return IrisInterpreter::CurInstance()->Nil();
			}
			break;
		case IrisIdentifier::IdentifilerType::LocalVariable:
			// 局部变量：在Main环境的情况下在MainEnvironmentVariables里面搜索，否则在pContextEnvironment中搜索
			// Main 的情况下
			if (!pContextEnvironment){
				// 未定义则添加
				bool bResult = false;
				const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifiler, bResult);
				if (!bResult){
					pInterpreter->AddOtherValue(strIdentifiler, ivResult);
				}
				else{
					// 修改赋值内容
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			else {
				// 未定义则添加
				bool bResult = false;
				const IrisValue& ivTmp = pContextEnvironment->m_bIsClosure
					? pContextEnvironment->m_pExcuteBlock
					->GetLocalVariable(strIdentifiler, bResult)
					: pContextEnvironment->GetVariableValue(strIdentifiler, bResult);
				if (!bResult){
					if (pContextEnvironment->m_bIsClosure) {
						(pContextEnvironment->m_pExcuteBlock
							->AddLocalVariable(strIdentifiler, ivResult));
					}
					else {
						pContextEnvironment->AddLoaclVariable(strIdentifiler, ivResult);
					}
				}
				else{
					// 修改赋值内容
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			break;
		case IrisIdentifier::IdentifilerType::GlobalVariable:
			// 没找到则添加
		{
			bool bResult = false;
			const IrisValue& ivTmp = pInterpreter->GetGlobalValue(strIdentifiler, bResult);
			if (!bResult){
				pInterpreter->AddGlobalValue(strIdentifiler, ivResult);
			}
			else{
				((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
			}
		}
			break;
		case IrisIdentifier::IdentifilerType::InstanceVariable:
			// Runtime的时候在本对象中找，否则在Global中找
			if (pContextEnvironment
				&& pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::Runtime){
				IrisObject* pObject = pContextEnvironment->m_uType.m_pCurObject;

				bool bResult = false;
				const IrisValue& ivTmp = 
					pContextEnvironment->m_bIsClosure
					? pContextEnvironment->m_pExcuteBlock
					->GetInstanceVariable(strIdentifiler, bResult)
					: pObject->GetInstanceValue(strIdentifiler, bResult);
				if (!bResult){
					if (pContextEnvironment->m_bIsClosure) {
						pContextEnvironment->m_pExcuteBlock->AddOtherVariable(strIdentifiler, ivResult);
					}
					else {
						pObject->AddInstanceValue(strIdentifiler, ivResult);
					}
				}
				else{
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			else{
				// 未定义则添加
				bool bResult = false;
				const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifiler, bResult);
				if (!bResult){
					pInterpreter->AddOtherValue(strIdentifiler, ivResult);
				}
				else{
					// 修改赋值内容
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			break;
		case IrisIdentifier::IdentifilerType::ClassVariable:
			if (pContextEnvironment
				&& pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::Runtime){
				IrisObject* pObject = pContextEnvironment->m_uType.m_pCurObject;

				bool bResult = false;
				const IrisValue& ivTmp = pContextEnvironment->m_bIsClosure
					? pContextEnvironment->m_pExcuteBlock
					->GetClassVariable(strIdentifiler, bResult)
					: pObject->GetClass()->SearchClassVariable(strIdentifiler, bResult);
				if (!bResult){
					if (pContextEnvironment->m_bIsClosure) {
						pContextEnvironment->m_pExcuteBlock->AddOtherVariable(strIdentifiler, ivResult);
					}
					else {
						pObject->GetClass()->AddClassVariable(strIdentifiler, ivResult);
					}
				}
				else{
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			else if (pContextEnvironment
				&& pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ClassDefineTime){
				IrisClass* pClass = pContextEnvironment->m_uType.m_pClass;

				bool bResult = false;
				const IrisValue& ivTmp = pClass->SearchClassVariable(strIdentifiler, bResult);
				if (!bResult){
					pClass->AddClassVariable(strIdentifiler, ivResult);
				}
				else{
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			else if (pContextEnvironment
				&& pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ModuleDefineTime){
				IrisModule* pModule = pContextEnvironment->m_uType.m_pModule;

				bool bResult = false;
				const IrisValue& ivTmp = pModule->SearchClassVariable(strIdentifiler, bResult);
				if (!bResult){
					pModule->AddClassVariable(strIdentifiler, ((IrisValue)ivResult));
				}
				else{
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			// **Error**
			else if (pContextEnvironment
				&& pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::InterfaceDefineTime){
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ClassVariableDeclareIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Class variable cannot be declared in interface.");
				return pInterpreter->Nil();
			}
			// Global
			else{
				// 未定义则添加
				bool bResult = false;
				const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifiler, bResult);
				if (!bResult){
					pInterpreter->AddOtherValue(strIdentifiler, ivResult);
				}
				else{
					// 修改赋值内容
					((IrisValue&)ivTmp).SetObject(((IrisValue&)ivResult).GetObjectPointer());
				}
			}
			break;
		default:
			break;
		}
	}
	return ivResult;
}

IrisValue IrisExpression::ExcuteAssignOperation(ExpressionType eType, IrisContextEnvironment* pContextEnvironment){
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValue ivTmpLeftValue = m_uType.m_pBinaryExpression->m_pLeft->Excute(pContextEnvironment);
	pInterpreter->SaveTempValue(ivTmpLeftValue);
	IrisValue ivTmpRightValue = m_uType.m_pBinaryExpression->m_pRight->Excute(pContextEnvironment);
	pInterpreter->SaveTempValue(ivTmpRightValue);
	IrisValues ivsParam;
	ivsParam.push_back(ivTmpRightValue);;

	switch (eType)
	{
	case IrisExpression::ExpressionType::AssignAdd:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("+", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignSub:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("-", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignMul:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("*", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignDiv:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("/", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignMod:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("%", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitAnd:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("&", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitOr:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("|", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitXor:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("^", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitShr:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">>", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitShl:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<<", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitSar:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">>>", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::AssignBitSal:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<<<", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	}

	pInterpreter->ClearTempValue(2);
	return ExcuteAssign(m_uType.m_pBinaryExpression->m_pLeft, ivTmpLeftValue, pContextEnvironment);
}

IrisValue IrisExpression::ExcuteOperation(ExpressionType eType, IrisContextEnvironment* pContextEnvironment){
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValue ivTmpLeftValue = m_uType.m_pBinaryExpression->m_pLeft->Excute(pContextEnvironment);
	pInterpreter->SaveTempValue(ivTmpLeftValue);
	IrisValue ivTmpRightValue = m_uType.m_pBinaryExpression->m_pRight->Excute(pContextEnvironment);
	pInterpreter->SaveTempValue(ivTmpRightValue);
	IrisValues ivsParam;
	ivsParam.push_back(ivTmpRightValue);	

	switch (eType)
	{
	case IrisExpression::ExpressionType::LogicOr:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("||", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LogicAnd:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("&&", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LogicBitOr:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("|", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LogicBitXor:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("^", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LogicBitAnd:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("&", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Equal:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("==", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::NotEqual:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("!=", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::GreatThan:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::GreatThanOrEqual:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">=", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LessThan:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::LessThanOrEqual:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<=", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::BitShr:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">>", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::BitShl:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<<", pContextEnvironment, &ivsParam);
		break;
	case IrisExpression::ExpressionType::BitSar:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction(">>>", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::BitSal:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("<<<", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Power:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("**", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Add:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("+", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Sub:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("-", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Mul:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("*", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Div:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("/", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Mod:
		ivTmpLeftValue = ivTmpLeftValue.GetObjectPointer()->CallInstanceFunction("%", pContextEnvironment, &ivsParam, CallerSide::Outside);
		break;
	}
	pInterpreter->ClearTempValue(2);
	return ivTmpLeftValue;
}

IrisValue IrisExpression::ExcuteIdentifier(IrisContextEnvironment* pContextEnvironment) {
	const string& strIdentifier = m_uType.m_pIdentifierExpression->m_pIdentifier->m_strIdentifier;
	IrisIdentifier::IdentifilerType eType = m_uType.m_pIdentifierExpression->m_pIdentifier->m_eType;
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

	// 全局变量统一处理
	if (eType == IrisIdentifier::IdentifilerType::GlobalVariable){
		bool bResult = false;
		const IrisValue& ivTmp = pInterpreter->GetGlobalValue(strIdentifier, bResult);
		if (!bResult){
			pInterpreter->AddGlobalValue(strIdentifier, pInterpreter->Nil());
			return pInterpreter->Nil();
		}
		return ivTmp;
	}
	// Main环境下去Interpreter里面找
	if (!pContextEnvironment){
		if (eType == IrisIdentifier::IdentifilerType::Constance){
			bool bResult = false;
			const IrisValue& ivTmp = pInterpreter->GetConstance(strIdentifier, bResult);
			if (!bResult){
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
		else{
			bool bResult = false;
			const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifier, bResult);
			if (!bResult){
				pInterpreter->AddOtherValue(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
	}
	else if(pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ClassDefineTime){
		IrisClass* pClass = pContextEnvironment->m_uType.m_pClass;
		// 定义类的时候出现未定义的实例变量或局部变量则定义到全局中
		if (eType == IrisIdentifier::IdentifilerType::InstanceVariable
			|| eType == IrisIdentifier::IdentifilerType::LocalVariable){
			bool bResult = false;
			const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifier, bResult);
			if (!bResult){
				pInterpreter->AddOtherValue(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
		// 出现类变量则定义到类中
		else if (eType == IrisIdentifier::IdentifilerType::ClassVariable) {
			bool bResult = false;
			const IrisValue& ivTmp = pClass->SearchClassVariable(strIdentifier, bResult);
			if (!bResult){
				pClass->AddClassVariable(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
		else {
			bool bResult = false;
			const IrisValue& ivTmp = pClass->SearchConstance(strIdentifier, bResult);
			if (!bResult){
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
	}
	else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ModuleDefineTime) {
		IrisModule* pModule = pContextEnvironment->m_uType.m_pModule;
		// 定义模块的时候出现未定义的实例变量或局部变量则定义到全局中
		if (eType == IrisIdentifier::IdentifilerType::InstanceVariable
			|| eType == IrisIdentifier::IdentifilerType::LocalVariable){
			bool bResult = false;
			const IrisValue& ivTmp = pInterpreter->GetOtherValue(strIdentifier, bResult);
			if (!bResult){
				pInterpreter->AddOtherValue(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
		// 出现类变量则定义到模块中
		else if (eType == IrisIdentifier::IdentifilerType::ClassVariable) {
			bool bResult = false;
			const IrisValue& ivTmp = pModule->SearchClassVariable(strIdentifier, bResult);
			if (!bResult){
				pModule->AddClassVariable(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
		else {
			bool bResult = false;
			const IrisValue& ivTmp = pModule->SearchConstance(strIdentifier, bResult);
			if (!bResult){
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
				return pInterpreter->Nil();
			}
			return ivTmp;
		}
	}
	else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::Runtime) {
		// 出现类变量定义到类中
		IrisValue ivTmp;
		IrisObject* pObject = pContextEnvironment->m_uType.m_pCurObject;
		if (eType == IrisIdentifier::IdentifilerType::ClassVariable){
			if (pObject) {
				IrisClass* pClass = pObject->GetClass();
				if (pClass->GetClassName() == "Module") {
					bool bResult = false;
					ivTmp = ((IrisModuleBaseTag*)pObject->m_pNativeObject)->GetModule()->SearchClassVariable(strIdentifier, bResult);
					if (!bResult) {
						((IrisModuleBaseTag*)pObject->m_pNativeObject)->GetModule()->AddClassVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
				else if (pClass->GetClassName() == "Class") {
					bool bResult = false;
					ivTmp = ((IrisClassBaseTag*)pObject->m_pNativeObject)->GetClass()->SearchClassVariable(strIdentifier, bResult);
					if (!bResult) {
						((IrisClassBaseTag*)pObject->m_pNativeObject)->GetClass()->AddClassVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
				else {
					bool bResult = false;
					if (pContextEnvironment->m_bIsClosure) {
						IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
						ivTmp = pClosureBlock->GetClassVariable(strIdentifier, bResult);
						if (!bResult) {
							pClosureBlock->AddOtherVariable(strIdentifier, pInterpreter->Nil());
							return pInterpreter->Nil();
						}
					}
					else {
						ivTmp = pClass->SearchClassVariable(strIdentifier, bResult);
						if (!bResult) {
							pClass->AddClassVariable(strIdentifier, pInterpreter->Nil());
							return pInterpreter->Nil();
						}
					}
				}
				return ivTmp;
			}
			// Main
			else {
				bool bResult = false;
				if (pContextEnvironment->m_bIsClosure) {
					IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
					ivTmp = pClosureBlock->GetClassVariable(strIdentifier, bResult);
					if (!bResult) {
						pClosureBlock->AddOtherVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
				else {
					ivTmp = pInterpreter->GetOtherValue(strIdentifier, bResult);
					if (!bResult) {
						pInterpreter->AddOtherValue(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
			}
			return ivTmp;
		}
		// 出现实例变量定义到对象中，但如果是调用类方法那么定义到环境中
		else if (eType == IrisIdentifier::IdentifilerType::InstanceVariable) {
			if (pObject) {
				bool bResult = false;
				if (pObject->GetClass()->GetClassName() == "Module"
					|| pObject->GetClass()->GetClassName() == "Class") {
					ivTmp = pContextEnvironment->GetVariableValue(strIdentifier, bResult);
					if (!bResult) {
						pContextEnvironment->AddLoaclVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
					return ivTmp;
				}
				else if (pContextEnvironment->m_bIsClosure) {
					IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
					ivTmp = pClosureBlock->GetInstanceVariable(strIdentifier, bResult);
					if (!bResult) {
						pClosureBlock->AddOtherVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
					return ivTmp;
				}

				ivTmp = pObject->GetInstanceValue(strIdentifier, bResult);
				if (!bResult) {
					pObject->AddInstanceValue(strIdentifier, pInterpreter->Nil());
					return pInterpreter->Nil();
				}
				return ivTmp;
			}
			// Main
			else {
				bool bResult = false;
				if (pContextEnvironment->m_bIsClosure) {
					IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
					ivTmp = pClosureBlock->GetInstanceVariable(strIdentifier, bResult);
					if (!bResult) {
						pClosureBlock->AddOtherVariable(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
				else {
					ivTmp = pInterpreter->GetOtherValue(strIdentifier, bResult);
					if (!bResult) {
						pInterpreter->AddOtherValue(strIdentifier, pInterpreter->Nil());
						return pInterpreter->Nil();
					}
				}
				return ivTmp;
			}
		}
		// 出现局部变量定义到Environment中
		else if (eType == IrisIdentifier::IdentifilerType::LocalVariable){
			bool bResult = false;

			if (pContextEnvironment->m_bIsClosure) {
				IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
				ivTmp = pClosureBlock->GetLocalVariable(strIdentifier, bResult);
				if (!bResult) {
					pClosureBlock->AddLocalVariable(strIdentifier, pInterpreter->Nil());
					return pInterpreter->Nil();
				}
				return ivTmp;
			}

			ivTmp = pContextEnvironment->GetVariableValue(strIdentifier, bResult);
			if (!bResult) {
				//pObject->AddInstanceValue(strIdentifier, pInterpreter->Nil());
				pContextEnvironment->AddLoaclVariable(strIdentifier, pInterpreter->Nil());
				return pInterpreter->Nil();
			}
		}
		// 出现常量正常处理
		else {
			bool bResult = false;

			if (pObject) {
				if (pContextEnvironment->m_bIsClosure) {
					IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
					ivTmp = pClosureBlock->GetConstance(strIdentifier, bResult);
					if (!bResult) {
						// **Error**
						IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
						return pInterpreter->Nil();
					}
					return ivTmp;
				}

				ivTmp = pObject->GetClass()->SearchConstance(strIdentifier, bResult);
				if (!bResult) {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
					return pInterpreter->Nil();
				}
			}
			// Main
			else {
				bool bResult = false;
				if (pContextEnvironment->m_bIsClosure) {
					IrisClosureBlock* pClosureBlock = pContextEnvironment->m_pExcuteBlock;
					ivTmp = pClosureBlock->GetConstance(strIdentifier, bResult);
					if (!bResult) {
						// **Error**
						IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
						return pInterpreter->Nil();
					}
				}
				else {
					ivTmp = pInterpreter->GetConstance(strIdentifier, bResult);
					if (!bResult) {
						// **Error**
						IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strIdentifier + " not found.");
						return pInterpreter->Nil();
					}
				}
			}
		}
		return ivTmp;
	}
	// **Error**
	return pInterpreter->Nil();
}

IrisValue IrisExpression::ExcuteFunctionCall(IrisContextEnvironment* pContextEnvironment) {
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValue ivResult;
	int nTimes = 0;
	IrisContextEnvironment* pCurEnvironment = nullptr;
	IrisClosureBlock* pClosureBlock = nullptr;

	if (m_uType.m_pFunctionCallExpression->m_pClosureBlock) {
		pClosureBlock = new IrisClosureBlock(pContextEnvironment, m_uType.m_pFunctionCallExpression->m_pClosureBlock->m_pParameters, m_uType.m_pFunctionCallExpression->m_pClosureBlock->m_pStatements);
		pCurEnvironment = pClosureBlock->m_pCurContextEnvironment;
		IrisContextEnvironment* pTmpEnv = pClosureBlock->m_pCurContextEnvironment;
		while (pTmpEnv) {
			++pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}
	}

	// 内部
	if (pContextEnvironment && pContextEnvironment->m_uType.m_pCurObject) {
		// 如果是在定义时调用，那么在该类/模块中寻找
		if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ModuleDefineTime) {
			IrisModule* pModule = pContextEnvironment->m_uType.m_pModule;

			const string& strMethodName = m_uType.m_pFunctionCallExpression->m_pFunctionName->m_strIdentifier;
			IrisList<IrisExpression*>* pParameters = m_uType.m_pFunctionCallExpression->m_pParameters;
			IrisExpression* pObj = m_uType.m_pFunctionCallExpression->m_pObject;

			IrisValues* pRealParameters = nullptr;
			IrisValues ivsParameters;
			if (pParameters) {
				pParameters->Ergodic(
					[&](IrisExpression* pExpression){
						IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
						++nTimes;
						pInterpreter->SaveTempValue(ivTmpValue);
						ivsParameters.push_back(ivTmpValue);
				}
				);
				pRealParameters = &ivsParameters;
			}
			//如果pObj为null则是在调用模块的ClassMethod
			if (!pObj) {
				// ClassMethod中有这个方法就调用
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				ivResult = pModule->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
			// 否则就是这个对象调用
			else {
				IrisValue ivObj = pObj->Excute(pContextEnvironment);
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				pInterpreter->SaveTempValue(ivObj);
				if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Class"){
					ivResult = ((IrisClassBaseTag*)ivObj.GetInstanceNativePointer())->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Module") {
					ivResult = ((IrisModuleBaseTag*)ivObj.GetInstanceNativePointer())->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else {
					ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				pInterpreter->ClearTempValue(1);
			}
		}
		else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ClassDefineTime) {
			IrisClass* pClass = pContextEnvironment->m_uType.m_pClass;

			const string& strMethodName = m_uType.m_pFunctionCallExpression->m_pFunctionName->m_strIdentifier;
			IrisList<IrisExpression*>* pParameters = m_uType.m_pFunctionCallExpression->m_pParameters;
			IrisExpression* pObj = m_uType.m_pFunctionCallExpression->m_pObject;

			IrisValues* pRealParameters = nullptr;
			IrisValues ivsParameters;
			if (pParameters) {
				pParameters->Ergodic(
					[&](IrisExpression* pExpression) {
						IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
						++nTimes;
						pInterpreter->SaveTempValue(ivTmpValue);
						ivsParameters.push_back(ivTmpValue);
				}
				);
				pRealParameters = &ivsParameters;
			}
			//如果pObj为null则是在调用模块的ClassMethod
			if (!pObj) {
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				// ClassMethod中有这个方法就调用
				ivResult = pClass->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
			// 否则就是这个对象调用
			else {
				IrisValue ivObj = pObj->Excute(pContextEnvironment);
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				pInterpreter->SaveTempValue(ivObj);
				if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Class") {
					ivResult = ((IrisClassBaseTag*)ivObj.GetInstanceNativePointer())->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Module") {
					ivResult = ((IrisModuleBaseTag*)ivObj.GetInstanceNativePointer())->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else {
					ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				pInterpreter->ClearTempValue(1);
			}
		}
		else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::InterfaceDefineTime) {
			const string& strMethodName = m_uType.m_pFunctionCallExpression->m_pFunctionName->m_strIdentifier;
			IrisList<IrisExpression*>* pParameters = m_uType.m_pFunctionCallExpression->m_pParameters;
			IrisExpression* pObj = m_uType.m_pFunctionCallExpression->m_pObject;

			IrisValues* pRealParameters = nullptr;
			IrisValues ivsParameters;
			if (pParameters) {
				pParameters->Ergodic(
					[&](IrisExpression* pExpression) {
					IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
					++nTimes;
					pInterpreter->SaveTempValue(ivTmpValue);
					ivsParameters.push_back(ivTmpValue);
				}
				);
				pRealParameters = &ivsParameters;
			}

			//如果pObj为null则是在调用Main Method
			if (!pObj) {
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				IrisMethod* pMethod = IrisInterpreter::CurInstance()->GetMainMethod(strMethodName);
				if (pMethod) {
					ivResult = pMethod->CallMainMethod(pRealParameters);
				} else{
					//**Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " not found.");
					ivResult = IrisInterpreter::CurInstance()->Nil();
				}
			}
			// 否则就是这个对象调用
			else {
				IrisValue ivObj = pObj->Excute(pContextEnvironment);
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				pInterpreter->SaveTempValue(ivObj);
				if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Class") {
					ivResult = ((IrisClassBaseTag*)ivObj.GetInstanceNativePointer())->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Module") {
					ivResult = ((IrisModuleBaseTag*)ivObj.GetInstanceNativePointer())->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else {
					ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				pInterpreter->ClearTempValue(1);
			}
		}
		else if (pContextEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::Runtime) {
			const string& strMethodName = m_uType.m_pFunctionCallExpression->m_pFunctionName->m_strIdentifier;
			IrisList<IrisExpression*>* pParameters = m_uType.m_pFunctionCallExpression->m_pParameters;
			IrisExpression* pObj = m_uType.m_pFunctionCallExpression->m_pObject;

			IrisValues* pRealParameters = nullptr;
			IrisValues ivsParameters;
			if (pParameters) {
				pParameters->Ergodic(
					[&](IrisExpression* pExpression){
					++nTimes;
					IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
					pInterpreter->SaveTempValue(ivTmpValue);
					ivsParameters.push_back(ivTmpValue);
				}
				);
				pRealParameters = &ivsParameters;
			}

			// 如果没有调用者，则检查当前调用的方法是类方法还是实例方法
			if (!pObj) {
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				IrisObject* pRealObj = pContextEnvironment->m_uType.m_pCurObject;
				if (pRealObj->GetClass()->GetClassName() == "Class") {
					ivResult = ((IrisClassBaseTag*)pRealObj->m_pNativeObject)->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Inside);
				}
				else if(pRealObj->GetClass()->GetClassName() == "Module") {
					ivResult = ((IrisModuleBaseTag*)pRealObj->m_pNativeObject)->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Inside);
				}
				else {
					ivResult = pRealObj->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Inside);
				}
			}
			// 有调用者则用调用者调用
			else {
				IrisValue ivObj = pObj->Excute(pContextEnvironment);
				if (pCurEnvironment) {
					if (pContextEnvironment) {
						pContextEnvironment->m_pTransferBlock = pClosureBlock;
					}
					else {
						pInterpreter->SetMainClosureBlock(pClosureBlock);
					}
				}
				//ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				pInterpreter->SaveTempValue(ivObj);
				if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Class") {
					ivResult = ((IrisClassBaseTag*)ivObj.GetInstanceNativePointer())->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Module") {
					ivResult = ((IrisModuleBaseTag*)ivObj.GetInstanceNativePointer())->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				else {
					ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
				}
				pInterpreter->ClearTempValue(1);
			}
			pInterpreter->ClearTempValue(nTimes);
		}
		else {
			// **Error**
			return IrisInterpreter::CurInstance()->Nil();
		}
	}
	// 全局
	else {
		const string& strMethodName = m_uType.m_pFunctionCallExpression->m_pFunctionName->m_strIdentifier;
		IrisList<IrisExpression*>* pParameters = m_uType.m_pFunctionCallExpression->m_pParameters;
		IrisExpression* pObj = m_uType.m_pFunctionCallExpression->m_pObject;

		IrisValues* pRealParameters = nullptr;
		IrisValues ivsParameters;
		if (pParameters) {
			pParameters->Ergodic(
				[&](IrisExpression* pExpression){
				IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
				++nTimes;
				pInterpreter->SaveTempValue(ivTmpValue);
				ivsParameters.push_back(ivTmpValue);
				//ivsParameters.push_back(pExpression->Excute(pContextEnvironment));
			}
			);
			pRealParameters = &ivsParameters;
		}

		//如果pObj为null则是在调用Main的Method，Main的Method将会先后在MainMethods和Kernel中寻找
		if (!pObj) {
			if (pCurEnvironment) {
				if (pContextEnvironment) {
					pContextEnvironment->m_pTransferBlock = pClosureBlock;
				}
				else {
					pInterpreter->SetMainClosureBlock(pClosureBlock);
				}
			}
			// Main中有这个方法就调用
			IrisMethod* pMethod = pInterpreter->GetMainMethod(strMethodName);
			if (pMethod) {
				ivResult = pMethod->CallMainMethod(pRealParameters);
			}
			else {
				ivResult = pInterpreter->GetIrisModule("Kernel")->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
		}
		// 否则就是这个对象调用
		else {
			IrisValue ivObj = pObj->Excute(pContextEnvironment);
			if (pCurEnvironment) {
				if (pContextEnvironment) {
					pContextEnvironment->m_pTransferBlock = pClosureBlock;
				}
				else {
					pInterpreter->SetMainClosureBlock(pClosureBlock);
				}
			}
			pInterpreter->SaveTempValue(ivObj);
			if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Module"){
				ivResult = ((IrisModuleBaseTag*)ivObj.GetInstanceNativePointer())->GetModule()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
			else if (ivObj.GetObjectPointer()->GetClass()->GetClassName() == "Class") {
				ivResult = ((IrisClassBaseTag*)ivObj.GetInstanceNativePointer())->GetClass()->CallClassMethod(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
			else {
				ivResult = ivObj.GetObjectPointer()->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Outside);
			}
			pInterpreter->ClearTempValue(1);
		}
		pInterpreter->ClearTempValue(nTimes);
	}

	if (pCurEnvironment) {
		IrisContextEnvironment* pTmpEnv = pCurEnvironment;
		while (pTmpEnv) {
			--pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}
	}

	return ivResult;
}

IrisValue IrisExpression::ExcuteSelfFunctionCall(IrisContextEnvironment* pContextEnvironment) {
	IrisValue ivResult;
	int nTimes = 0;

	if (pContextEnvironment && pContextEnvironment->m_bIsClosure) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
		return IrisInterpreter::CurInstance()->Nil();
	}

	if (!pContextEnvironment || !pContextEnvironment->m_uType.m_pCurObject) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
		return IrisInterpreter::CurInstance()->Nil();
	}

	// 获取调用者
	IrisObject* pCaller = pContextEnvironment->m_uType.m_pCurObject;

	// 如果是在类方法中self调用那么错误
	if (pCaller->GetClass()->GetClassName() == "Class"
		|| pCaller->GetClass()->GetClassName() == "Module") {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
		return IrisInterpreter::CurInstance()->Nil();
	}

	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisContextEnvironment* pCurEnvironment = nullptr;

	if (m_uType.m_pFunctionCallExpression->m_pClosureBlock) {
		IrisClosureBlock* pClosureBlock = new IrisClosureBlock(pContextEnvironment, m_uType.m_pFunctionCallExpression->m_pClosureBlock->m_pParameters, m_uType.m_pFunctionCallExpression->m_pClosureBlock->m_pStatements);
		if (pContextEnvironment) {
			pContextEnvironment->m_pTransferBlock = pClosureBlock;
		}
		else {
			pInterpreter->SetMainClosureBlock(pClosureBlock);
		}
		pCurEnvironment = pClosureBlock->m_pCurContextEnvironment;
		IrisContextEnvironment* pTmpEnv = pClosureBlock->m_pCurContextEnvironment;
		while (pTmpEnv) {
			++pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}
	}


	const string& strMethodName = m_uType.m_pSelfCallExpression->m_pFunctionName->m_strIdentifier;
	IrisList<IrisExpression*>* pParameters = m_uType.m_pSelfCallExpression->m_pParameters;

	IrisValues* pRealParameters = nullptr;
	IrisValues ivsParameters;
	if (pParameters) {
		pParameters->Ergodic(
			[&](IrisExpression* pExpression){
			IrisValue ivTmpValue = pExpression->Excute(pContextEnvironment);
			++nTimes;
			IrisInterpreter::CurInstance()->SaveTempValue(ivTmpValue);
			ivsParameters.push_back(ivTmpValue);
		}
		);
		pRealParameters = &ivsParameters;
	}

	ivResult = pCaller->CallInstanceFunction(strMethodName, pContextEnvironment, pRealParameters, CallerSide::Inside);
	IrisInterpreter::CurInstance()->ClearTempValue(nTimes);

	if (pCurEnvironment) {
		IrisContextEnvironment* pTmpEnv = pCurEnvironment;
		while (pTmpEnv) {
			--pTmpEnv->m_nReferenced;
			pTmpEnv = pTmpEnv->m_pUpperContextEnvironment;
		}
	}

	return ivResult;
}

IrisValue IrisExpression::ExcuteFieldIdentifier(IrisContextEnvironment* pContextEnvironment) {

	IrisValue ivResult;
	IrisList<IrisIdentifier*>* pIdentifiers = m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pList;
	//if (m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pIdentifier->m_eType != IrisIdentifier::IdentifilerType::Constance)
	list<string> lsRoute;
	if (pIdentifiers) {
		pIdentifiers->Ergodic(
			[&](IrisIdentifier* pIdentifier) { lsRoute.push_back(pIdentifier->m_strIdentifier); }
		);
		string strConstanceName = m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pIdentifier->m_strIdentifier;

		IrisModule* pModule = nullptr;
		IrisClass* pClass = nullptr;
		if (pModule = IrisInterpreter::CurInstance()->GetIrisModule(lsRoute)) {
			bool bResult = false;
			ivResult = pModule->SearchConstance(strConstanceName, bResult);
			if (!bResult) {
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strConstanceName + " not found.");
				return IrisInterpreter::CurInstance()->Nil();
			}
		}
		else if (pClass = IrisInterpreter::CurInstance()->GetIrisClass(lsRoute)) {
			bool bResult = false;
			ivResult = pClass->SearchConstance(strConstanceName, bResult);
			if (!bResult) {
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strConstanceName + " not found.");
				return IrisInterpreter::CurInstance()->Nil();
			}
		}
	}
	else {
		string strConstanceName = m_uType.m_pFieldExpression->m_pFieldIdentifier->m_pIdentifier->m_strIdentifier;

		IrisModule* pModule = nullptr;
		IrisClass* pClass = nullptr;
		if (pModule = IrisInterpreter::CurInstance()->GetIrisModule(strConstanceName)) {
			ivResult = IrisValue::WrapObjectPointerToIrisValue(pModule->m_pModuleObject);
		}
		else if (pClass = IrisInterpreter::CurInstance()->GetIrisClass(strConstanceName)) {
			ivResult = IrisValue::WrapObjectPointerToIrisValue(pClass->m_pClassObject);
		}
		else {
			bool bResult = false;
			ivResult = IrisInterpreter::CurInstance()->GetConstance(strConstanceName, bResult);
			if (!bResult) {
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifer of " + strConstanceName + " not found.");
				return ivResult;
			}
		}
	}

	return ivResult;
}

IrisValue IrisExpression::ExcuteMember(IrisContextEnvironment* pContextEnvironment) {
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValue ivCaller = m_uType.m_pMemberExpression->m_pCaller->Excute(pContextEnvironment);
	pInterpreter->SaveTempValue(ivCaller);
	string strPropertyName = 
		"__get_" + m_uType.m_pMemberExpression->m_pProperty->m_strIdentifier;

	IrisValue ivResult = ivCaller.GetObjectPointer()->CallInstanceFunction(strPropertyName, pContextEnvironment, nullptr, CallerSide::Outside);
	pInterpreter->ClearTempValue(1);

	return ivResult;
}

IrisValue IrisExpression::ExcuteSelfMember(IrisContextEnvironment* pContextEnvironment) {
	if (!pContextEnvironment || pContextEnvironment->m_uType.m_pCurObject) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SelfPointerIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of self must be used in instance method of class.");
		return IrisInterpreter::CurInstance()->Nil();
	}

	IrisObject* pObj = pContextEnvironment->m_uType.m_pCurObject;
	string strPropertyName = "@" + m_uType.m_pSelfMemberExpression->m_pProperty->m_strIdentifier;

	bool bResult = false;
	IrisValue ivResult = pObj->GetInstanceValue(strPropertyName, bResult);

	if (!bResult) {
		pObj->AddInstanceValue(strPropertyName, IrisInterpreter::CurInstance()->Nil());
		return IrisInterpreter::CurInstance()->Nil();
	}

	return ivResult;
}

IrisValue IrisExpression::ExcuteArray(IrisContextEnvironment* pContextEnvironment) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->Nil();

	if (m_uType.m_pArrayExpression->m_pElementList) {
		IrisValues ivValues;
		m_uType.m_pArrayExpression->m_pElementList->Ergodic(
			[&](IrisExpression* pExpression) {
			ivValues.push_back(pExpression->Excute(pContextEnvironment));
		}
		);
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Array")->CreateInstance(&ivValues, pContextEnvironment);
	}
	else {
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Array")->CreateInstance(nullptr, pContextEnvironment);
	}

	return ivValue;
}
IrisValue IrisExpression::ExcuteHash(IrisContextEnvironment* pContextEnvironment) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->Nil();

	if (m_uType.m_pHashExpression->m_pHashPairs) {
		IrisValues ivValues;
		m_uType.m_pHashExpression->m_pHashPairs->Ergodic(
			[&](IrisHashPair* pPair) {
			ivValues.push_back(pPair->m_pKey->Excute(pContextEnvironment));
			ivValues.push_back(pPair->m_pValue->Excute(pContextEnvironment));
		}
		);
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Hash")->CreateInstance(&ivValues, pContextEnvironment);
	}
	else {
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Hash")->CreateInstance(nullptr, pContextEnvironment);
	}

	return ivValue;
}

IrisValue IrisExpression::ExcuteIndex(IrisContextEnvironment* pContextEnvironment) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->Nil();

	IrisValue ivObj = m_uType.m_pIndexExpression->m_pTarget->Excute(pContextEnvironment);
	IrisInterpreter::CurInstance()->SaveTempValue(ivObj);
	IrisValue ivIndex = m_uType.m_pIndexExpression->m_pIndexer->Excute(pContextEnvironment);
	IrisInterpreter::CurInstance()->SaveTempValue(ivIndex);

	IrisValues ivsParam;
	ivsParam.push_back(ivIndex);
	ivValue = ivObj.GetObjectPointer()->CallInstanceFunction("[]", pContextEnvironment, &ivsParam, CallerSide::Outside);

	IrisInterpreter::CurInstance()->ClearTempValue(2);

	return ivValue;
}

IrisValue IrisExpression::Excute(IrisContextEnvironment* pContextEnvironment) {

	IrisInterpreter::CurInstance()->SetExcutedLineNumber(m_nLineNumber);

	IrisValue ivValue;
	IrisValue ivTmpValue;
	switch (m_eType)
	{
	case IrisExpression::ExpressionType::Assign:
		ivValue = ExcuteAssign(
			m_uType.m_pBinaryExpression->m_pLeft,
			m_uType.m_pBinaryExpression->m_pRight->Excute(pContextEnvironment),
			pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignAdd:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignAdd, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignSub:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignSub, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignMul:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignMul, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignDiv:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignDiv, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignMod:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignMod, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitAnd:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitAnd, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitOr:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitOr, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitXor:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitXor, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitShr:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitShr, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitShl:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitShl, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitSar:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitSar, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::AssignBitSal:
		ivValue = ExcuteAssignOperation(IrisExpression::ExpressionType::AssignBitSal, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicOr:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LogicOr, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicAnd:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LogicAnd, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicBitOr:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::AssignBitSal, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicBitXor:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LogicBitXor, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicBitAnd:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LogicBitAnd, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Equal:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Equal, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::NotEqual:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::NotEqual, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::GreatThan:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::GreatThan, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::GreatThanOrEqual:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::GreatThanOrEqual, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LessThan:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LessThan, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LessThanOrEqual:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::LessThanOrEqual, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::BitShr:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::BitShr, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::BitShl:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::BitShl, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::BitSar:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::BitSar, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::BitSal:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::BitSal, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Power:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Power, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Add:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Add, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Sub:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Sub, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Mul:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Mul, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Div:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Div, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Mod:
		ivValue = ExcuteOperation(IrisExpression::ExpressionType::Mod, pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::LogicNot:
		ivValue = m_uType.m_pUnaryExpression->m_pExpression->Excute(pContextEnvironment)
			.GetObjectPointer()->CallInstanceFunction("!", pContextEnvironment, nullptr, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::BitNot:
		ivValue = m_uType.m_pUnaryExpression->m_pExpression->Excute(pContextEnvironment)
			.GetObjectPointer()->CallInstanceFunction("~", pContextEnvironment, nullptr, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Minus:
		ivTmpValue = m_uType.m_pUnaryExpression->m_pExpression->Excute(pContextEnvironment);
		ivValue = ivTmpValue
			.GetObjectPointer()->CallInstanceFunction("__minus", pContextEnvironment, nullptr, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Plus:
		ivValue = m_uType.m_pUnaryExpression->m_pExpression->Excute(pContextEnvironment)
			.GetObjectPointer()->CallInstanceFunction("__plus", pContextEnvironment, nullptr, CallerSide::Outside);
		break;
	case IrisExpression::ExpressionType::Index:
		ivValue = ExcuteIndex(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::FunctionCall:
		ivValue = ExcuteFunctionCall(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::SelfFunctionCall:
		ivValue = ExcuteSelfFunctionCall(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Member:
		ivValue = ExcuteMember(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::SelfMember:
		ivValue = ExcuteSelfMember(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::FieldIdentifier:
		ivValue = ExcuteFieldIdentifier(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Identifier:
		ivValue = ExcuteIdentifier(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Integer:
	case IrisExpression::ExpressionType::Float:
	case IrisExpression::ExpressionType::String:
		ivValue.SetObject(m_uType.m_pNativeObjectExpression->m_pObject);
		break;
	case IrisExpression::ExpressionType::True:
		ivValue = IrisInterpreter::CurInstance()->True();
		break;
	case IrisExpression::ExpressionType::False:
		ivValue = IrisInterpreter::CurInstance()->False();
		break;
	case IrisExpression::ExpressionType::Nil:
		ivValue = IrisInterpreter::CurInstance()->Nil();
		break;
	case IrisExpression::ExpressionType::Array:
		ivValue = ExcuteArray(pContextEnvironment);
		break;
	case IrisExpression::ExpressionType::Hash:
		ivValue = ExcuteHash(pContextEnvironment);
		break;
	default:
		break;
	}
	return ivValue;
}

IrisExpression::~IrisExpression()
{
}
