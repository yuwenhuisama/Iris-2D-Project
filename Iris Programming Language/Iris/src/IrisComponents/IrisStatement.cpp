#include "IrisStatement.h"
#include "IrisParticularStatements.h"
#include "IrisInterpreter.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisStatementResult.h"
#include "IrisInteger.h"
#include "IrisClassBaseTag.h"
#include "IrisModuleBaseTag.h"
#include "IrisStringTag.h"
#include "IrisInterfaceBaseTag.h"
#include "IrisArray.h"
#include "IrisHash.h"

IrisStatement::IrisStatement()
{
}

IrisStatementResult IrisStatement::ExcuteFunctionStatement(IrisContextEnvironment* pContexEnvironment){

	// 要求参数必须为local variable
	if (m_uType.m_pFunctionStatement->m_pFunctionHeader->m_pParameters) {
		for (auto expr : m_uType.m_pFunctionStatement->m_pFunctionHeader->m_pParameters->m_lsList) {
			// **Error**
			if (expr->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
				IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of function must be local variable.");
				return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
			}
		}
	}
	if (m_uType.m_pFunctionStatement->m_pFunctionHeader->m_pVariableParameter) {
		if (m_uType.m_pFunctionStatement->m_pFunctionHeader->m_pVariableParameter->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of function must be local variable.");
			return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
		}
	}

	IrisMethod* pMethod = new IrisMethod(
		m_uType.m_pFunctionStatement->m_pFunctionHeader,
		m_uType.m_pFunctionStatement->m_pBlock,
		m_uType.m_pFunctionStatement->m_pWithBlock,
		m_uType.m_pFunctionStatement->m_pWithoutBlock
	);
	if (pContexEnvironment) {
		if (pContexEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ModuleDefineTime) {
			IrisModule* pModule = pContexEnvironment->m_uType.m_pModule;
			if (m_uType.m_pFunctionStatement->m_pFunctionHeader->m_bIsClassMethod) {
				pModule->AddClassMethod(pMethod);
			}
			else {
				pModule->AddInstanceMethod(pMethod);
			}
		}
		else if (pContexEnvironment->m_eType == IrisContextEnvironment::EnvironmentType::ClassDefineTime){
			IrisClass* pClass = pContexEnvironment->m_uType.m_pClass;
			if (m_uType.m_pFunctionStatement->m_pFunctionHeader->m_bIsClassMethod) {
				pClass->AddClassMethod(pMethod);
			}
			else {
				pClass->AddInstanceMethod(pMethod);
			}
		}
	}
	else {
		IrisInterpreter::CurInstance()->AddMainMethod(pMethod->GetMethodName(), pMethod);
	}
	return IrisStatementResult(IrisValue::WrapObjectPointerToIrisValue(pMethod->m_pMethodObject), IrisStatementResult::StatementResultType::Normal);
}

IrisStatementResult IrisStatement::ExcuteConditionIf(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult;
	bool bHaveResult = false;
	// 先检查头表达式结果是否为真
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValue ivConditionResult = m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pCondition->Excute(pContexEnvironment);
	// 如果条件为真直接执行之
	if (ivConditionResult != pInterpreter->Nil() && ivConditionResult != pInterpreter->False()) {
		srResult = m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pBlock->Execute(pContexEnvironment);
	}
	else {
		// 如果否则检查其它条件
		// 如果有elseif的话
		if (m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pIrisElseIf) {
			for (auto elseif : m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pIrisElseIf->m_lsList) {
				// 条件检查
				ivConditionResult = elseif->m_pCondition->Excute(pContexEnvironment);
				if (ivConditionResult != pInterpreter->Nil() && ivConditionResult != pInterpreter->False()){
					srResult = elseif->m_pBlock->Execute(pContexEnvironment);
					bHaveResult = true;
					break;
				}
			}
		}
		// 如果还有else
		if (!bHaveResult && m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pElseBlock) {
			srResult = m_uType.m_pIfStatement->m_uType.m_pConditionIf->m_pElseBlock->Execute(pContexEnvironment);
		}
	}
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteLoopIf(IrisContextEnvironment* pContexEnvironment) {

	if (pContexEnvironment) {
		pContexEnvironment->m_eUpperType = IrisContextEnvironment::EnvironmentUpperType::Loop;
	}
	else {
		IrisInterpreter::CurInstance()->SetUpperType(IrisInterpreter::EnvironmentUpperType::Loop);
	}

	IrisStatementResult srResult;
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

	int nLoopTime = ((IrisIntegerTag*)m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLoopTime->Excute(pContexEnvironment).GetInstanceNativePointer())->m_nInteger;

	// 要求计次变量必须为局部变量
	IrisValue ivCount;
	if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable) {
		if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Variable of counting must be local variable.");
			return IrisStatementResult(pInterpreter->Nil(), IrisStatementResult::StatementResultType::Normal);
		}
		bool bFind = false;
		if (pContexEnvironment) {
			ivCount = pContexEnvironment->GetVariableValue(m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable->m_strIdentifier, bFind);
		}
		else {
			ivCount = pInterpreter->GetOtherValue(m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable->m_strIdentifier, bFind);
		}

		// 要是不存在那么就往环境中加入这个局部变量
		if (!bFind) {
			ivCount = pInterpreter->GetIrisClass("Integer")->CreateInstanceByInstantValue(1);
			if (pContexEnvironment) {
				pContexEnvironment->AddLoaclVariable(
					m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable->m_strIdentifier,
					ivCount);
			}
			else {
				pInterpreter->AddOtherValue(
					m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable->m_strIdentifier,
					ivCount);
			}
		}
		else {
			((IrisIntegerTag*)(ivCount.GetInstanceNativePointer()))->m_nInteger = 1;
		}
	}

	// 如果循环次数小于等于0，那么就是不确定的循环
	if (nLoopTime <= 0) {
		while (true) {
			// 计算循环条件
			IrisValue ivConditionResult = m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pCondition->Excute(pContexEnvironment);
			// 不满足条件就退出
			if (ivConditionResult == pInterpreter->Nil() || ivConditionResult == pInterpreter->False()) {
				if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable) {
					--((IrisIntegerTag*)ivCount.GetInstanceNativePointer())->m_nInteger;
				}
				break;
			}

			// 执行循环体
			srResult = m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pBlock->Execute(pContexEnvironment);

			// 计次变量增加（如果存在）
			if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable) {
				++((IrisIntegerTag*)ivCount.GetInstanceNativePointer())->m_nInteger;
			}

			// 遇到return或者break就跳出，continue继续下次循环
			if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return) {
				break;
			}
			else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break) {
				srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
				break;
			}
			else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue) {
				srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
			}
			else if (pInterpreter->HaveIrregular()) {
				break;
			}
		}
	}
	// 计数循环
	else {
		int nCount = 0;
		while (true) {
			// 计算循环条件
			IrisValue ivConditionResult = m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pCondition->Excute(pContexEnvironment);
			// 不满足条件，或者次数达到要求就退出
			if (ivConditionResult == pInterpreter->Nil() || ivConditionResult == pInterpreter->False()
				|| nCount >= nLoopTime) {
				if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable) {
					--((IrisIntegerTag*)ivCount.GetInstanceNativePointer())->m_nInteger;
				}
				break;
			}
			++nCount;
			// 执行循环体
			srResult = m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pBlock->Execute(pContexEnvironment);

			// 计次变量增加（如果存在）
			if (m_uType.m_pIfStatement->m_uType.m_pLoopIf->m_pLogVariable) {
				++((IrisIntegerTag*)ivCount.GetInstanceNativePointer())->m_nInteger;
			}

			// 遇到return或者break就跳出，continue继续下次循环
			if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return) {
				break;
			}
			else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break) {
				srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
				break;
			}
			else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue) {
				srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
			}
			else if (pInterpreter->HaveIrregular()) {
				break;
			}
		}
	}

	if (pContexEnvironment) {
		pContexEnvironment->m_eUpperType = IrisContextEnvironment::EnvironmentUpperType::Normal;
	}
	else {
		IrisInterpreter::CurInstance()->SetUpperType(IrisInterpreter::EnvironmentUpperType::Normal);
	}
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteIfStatement(IrisContextEnvironment* pContexEnvironment) {
	if (m_uType.m_pIfStatement->m_eType == IrisIfStatement::IfType::ConditionIf) {
		return ExcuteConditionIf(pContexEnvironment);
	}
	else {
		return ExcuteLoopIf(pContexEnvironment);
	}
}

IrisStatementResult IrisStatement::ExcuteForStatement(IrisContextEnvironment* pContexEnvironment) {

	if (pContexEnvironment) {
		pContexEnvironment->m_eUpperType = IrisContextEnvironment::EnvironmentUpperType::Loop;
	}
	else {
		IrisInterpreter::CurInstance()->SetUpperType(IrisInterpreter::EnvironmentUpperType::Loop);
	}

	IrisStatementResult srResult;
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

	IrisIdentifier* pIter1 = m_uType.m_pForStatement->m_pIter1;
	IrisIdentifier* pIter2 = m_uType.m_pForStatement->m_pIter2;

	IrisValue ivSource = m_uType.m_pForStatement->m_pSource->Excute(pContexEnvironment);
	pInterpreter->SaveTempValue(ivSource);
	// Array For
	if (!pIter2) {
		if (ivSource.GetObject()->GetClass()->GetClassName() == "Array") {
			vector<IrisValue>& vcSource = ((IrisArrayTag*)ivSource.GetInstanceNativePointer())->m_vcValues;

			// 要求iter必须为局部变量
			if (pIter1->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
				pInterpreter->ClearTempValue(1);
				return IrisStatementResult(pInterpreter->Nil(), IrisStatementResult::StatementResultType::Normal);
			}
			bool bFind = false;
			if (pContexEnvironment) {
				pContexEnvironment->GetVariableValue(pIter1->m_strIdentifier, bFind);
			}
			else {
				pInterpreter->GetOtherValue(pIter1->m_strIdentifier, bFind);
			}
			// 要是不存在那么就往环境中加入这个局部变量
			if (!bFind) {
				if (pContexEnvironment) {
					pContexEnvironment->AddLoaclVariable(
						pIter1->m_strIdentifier,
						pInterpreter->Nil());
				}
				else {
					pInterpreter->AddOtherValue(
						pIter1->m_strIdentifier,
						pInterpreter->Nil());
				}
			}

			IrisValue& ivIter = (IrisValue&)
				(pContexEnvironment ? 
				pContexEnvironment->GetVariableValue(pIter1->m_strIdentifier, bFind)
				: pInterpreter->GetOtherValue(pIter1->m_strIdentifier, bFind));

			for (auto value : vcSource) {
				if (value.GetObject()->m_bLiteralObject) {
					value.GetObject()->m_bLiteralObjectAssigned = true;
				}
				ivIter.SetObject(value.GetObject());
				srResult = m_uType.m_pForStatement->m_pBlock->Execute(pContexEnvironment);

				// 遇到return或者break就跳出，continue继续下次循环
				if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return) {
					break;
				}
				else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break) {
					srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
					break;
				}
				else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue) {
					srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
				}
				else if (pInterpreter->HaveIrregular()) {
					break;
				}
			}
		}
		else {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SourceObjectIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "The source Object must be an Array.");
			srResult.m_ivValue = pInterpreter->Nil();
		}
	}
	// Hash For
	else {
		if (ivSource.GetObject()->GetClass()->GetClassName() == "Hash") {
			IrisHashTag::_IrisHash& vcSource = ((IrisHashTag*)ivSource.GetInstanceNativePointer())->m_mpHash;

			// 要求iter必须为局部变量
			if (pIter1->m_eType != IrisIdentifier::IdentifilerType::LocalVariable
				|| pIter2->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
				pInterpreter->ClearTempValue(1);
				return IrisStatementResult(pInterpreter->Nil(), IrisStatementResult::StatementResultType::Normal);
			}
			bool bFind = false;
			if (pContexEnvironment) {
				pContexEnvironment->GetVariableValue(pIter1->m_strIdentifier, bFind);
			}
			else {
				pInterpreter->GetOtherValue(pIter1->m_strIdentifier, bFind);
			}
			// 要是不存在那么就往环境中加入这个局部变量
			if (!bFind) {
				if (pContexEnvironment) {
					pContexEnvironment->AddLoaclVariable(
						pIter1->m_strIdentifier,
						pInterpreter->Nil());
				}
				else {
					pInterpreter->AddOtherValue(
						pIter1->m_strIdentifier,
						pInterpreter->Nil());
				}
			}

			if (pContexEnvironment) {
				pContexEnvironment->GetVariableValue(pIter2->m_strIdentifier, bFind);
			}
			else {
				pInterpreter->GetOtherValue(pIter2->m_strIdentifier, bFind);
			}
			// 要是不存在那么就往环境中加入这个局部变量
			if (!bFind) {
				if (pContexEnvironment) {
					pContexEnvironment->AddLoaclVariable(
						pIter2->m_strIdentifier,
						pInterpreter->Nil());
				}
				else {
					pInterpreter->AddOtherValue(
						pIter2->m_strIdentifier,
						pInterpreter->Nil());
				}
			}

			IrisValue& ivIter1 = (IrisValue&)
				(pContexEnvironment ?
					pContexEnvironment->GetVariableValue(pIter1->m_strIdentifier, bFind)
					: pInterpreter->GetOtherValue(pIter1->m_strIdentifier, bFind));
			IrisValue& ivIter2 = (IrisValue&)
				(pContexEnvironment ?
					pContexEnvironment->GetVariableValue(pIter2->m_strIdentifier, bFind)
					: pInterpreter->GetOtherValue(pIter2->m_strIdentifier, bFind));

			for (auto value : vcSource) {

				if (((IrisValue&) value.first).GetObject()->m_bLiteralObject) {
					((IrisValue&)value.first).GetObject()->m_bLiteralObjectAssigned = true;
				}
				if (value.second.GetObject()->m_bLiteralObject) {
					value.second.GetObject()->m_bLiteralObjectAssigned = true;
				}

				ivIter1.SetObject(((IrisValue&)value.first).GetObject());
				ivIter2.SetObject(value.second.GetObject());
				srResult = m_uType.m_pForStatement->m_pBlock->Execute(pContexEnvironment);

				// 遇到return或者break就跳出，continue继续下次循环
				if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Return) {
					break;
				}
				else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Break) {
					srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
					break;
				}
				else if (srResult.m_eReturnType == IrisStatementResult::StatementResultType::Continue) {
					srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
				}
				else if (pInterpreter->HaveIrregular()) {
					break;
				}
			}
		}
		else {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SourceObjectIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "The source object must be a Hash.");
			srResult.m_ivValue = pInterpreter->Nil();
		}

	}

	pInterpreter->ClearTempValue(1);

	if (pContexEnvironment) {
		pContexEnvironment->m_eUpperType = IrisContextEnvironment::EnvironmentUpperType::Normal;
	}
	else {
		IrisInterpreter::CurInstance()->SetUpperType(IrisInterpreter::EnvironmentUpperType::Normal);
	}

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteSwitchStatement(IrisContextEnvironment* pContexEnvironment) {
	// 先计算待评价的表达式
	IrisValue ivExpression = m_uType.m_pSwitchStatement->m_pCondition->Excute(pContexEnvironment);
	IrisInterpreter::CurInstance()->SaveTempValue(ivExpression);

	// 对每一个when进行评价
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisValues ivParam;
	ivParam.push_back(ivExpression);
	bool bHaveResult = false;
	for (auto when : m_uType.m_pSwitchStatement->m_pSwitchBlock->m_pWhenList->m_lsList) {
		for (auto expr : when->m_pExpressions->m_lsList) {
			if (expr->Excute(pContexEnvironment).GetObject()->CallInstanceFunction("==", pContexEnvironment, &ivParam) == IrisInterpreter::CurInstance()->True()) {
				srResult = when->m_pBlock->Execute(pContexEnvironment);
				bHaveResult = true;
				break;
			}
		}
		if (bHaveResult){
			break;
		}
	}

	IrisInterpreter::CurInstance()->ClearTempValue(1);

	// when评价完如果没有结果且还有else
	if (!bHaveResult && m_uType.m_pSwitchStatement->m_pSwitchBlock->m_pElseBlock) {
		srResult = m_uType.m_pSwitchStatement->m_pSwitchBlock->m_pElseBlock->Execute(pContexEnvironment);
	}
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteModuleStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisModule* pModule = nullptr;

	// 如果Module已经有那么就为其扩充
	string strTmpPath = "";
	if (pContexEnvironment) {
		IrisModule* pTmpModule = pContexEnvironment->m_uType.m_pModule;
		while (pTmpModule) {
			strTmpPath = pTmpModule->GetModuleName() + "::" + strTmpPath;
			pTmpModule = pTmpModule->m_pUpperModule;
		}
	}
	strTmpPath += m_uType.m_pModuleStatement->m_pModuleName->m_strIdentifier;

	pModule = IrisInterpreter::CurInstance()->GetIrisModule(strTmpPath);
	// 如果没有找到
	if (!pModule) {
		if (pContexEnvironment) {
			pModule = new IrisModule(
				m_uType.m_pModuleStatement->m_pModuleName->m_strIdentifier,
				pContexEnvironment->m_uType.m_pModule
				);
		}
		else {
			pModule = new IrisModule(
				m_uType.m_pModuleStatement->m_pModuleName->m_strIdentifier,
				nullptr
				);
		}
		pModule->AddModule(IrisInterpreter::CurInstance()->GetIrisModule("Kernel"));

		string strPath = pModule->GetModuleName();
		IrisModule* pCurModule = pModule->m_pUpperModule;
		while (pCurModule) {
			strPath = pCurModule->GetModuleName() + "::" + strPath;
			pCurModule = pCurModule->m_pUpperModule;
		}
		IrisInterpreter::CurInstance()->RegistModule(strPath, pModule);
	}

	pModule->ClearInvolvingModules();
	if (m_uType.m_pModuleStatement->m_pModules) {
		m_uType.m_pModuleStatement->m_pModules->Ergodic(
			[&](IrisExpression* pExpression) {
			IrisValue ivModule = pExpression->Excute(pContexEnvironment);
			pModule->AddModule(((IrisModuleBaseTag*)(ivModule.GetInstanceNativePointer()))->GetModule());
		}
		);
	}

	// Definetime Environment
	IrisContextEnvironment iceEnvironment;
	iceEnvironment.m_eType = IrisContextEnvironment::EnvironmentType::ModuleDefineTime;
	iceEnvironment.m_uType.m_pModule = pModule;

	m_uType.m_pModuleStatement->m_pBlock->Execute(&iceEnvironment);
	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pModule->m_pModuleObject);

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteClassStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisClass* pClass = nullptr;
	IrisClass* pSuperClass = nullptr;
	IrisModule* pUpperModule = nullptr;
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();

	// 获取SuperClass
	if (!m_uType.m_pClassStatement->m_pSuperClassName) {
		// 默认为Object类的子类
		pSuperClass = pInterpreter->GetIrisClass("Object");
	}
	else if (m_uType.m_pClassStatement->m_pSuperClassName->_FieldIsSingleWithoutField()) {
		if (pContexEnvironment) {
			pSuperClass = pContexEnvironment->m_uType.m_pModule->GetClass(
				m_uType.m_pClassStatement->m_pSuperClassName->_FieldSingleName());
		}
		else {
			pSuperClass = pInterpreter->GetIrisClass(m_uType.m_pClassStatement->m_pSuperClassName->_FieldSingleName());
		}
	}
	else {
		IrisValue ivSuperClass = m_uType.m_pClassStatement->m_pSuperClassName->Excute(pContexEnvironment);
		if (ivSuperClass.GetObject()->GetClass()->GetClassName() != "Class") {
			return srResult;
		}
		pSuperClass = ((IrisClassBaseTag*)ivSuperClass.GetObject()->m_pNativeObject)->GetClass();
	}

	if (!pSuperClass) {
		// **Error**
		string strFullClassName = m_uType.m_pClassStatement->m_pSuperClassName->_FieldSingleName();
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdentifierNotFoundIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Identifier of " + strFullClassName + " not found.");
		return srResult;
	}

	// 如果Class已经有那么就为其扩充
	string strTmpPath = "";
	if (pContexEnvironment) {
		IrisModule* pTmpModule = pContexEnvironment->m_uType.m_pModule;
		while (pTmpModule) {
			strTmpPath = pTmpModule->GetModuleName() + "::" + strTmpPath;
			pTmpModule = pTmpModule->m_pUpperModule;
		}
	}
	strTmpPath += m_uType.m_pClassStatement->m_pClassName->m_strIdentifier;

	pClass = IrisInterpreter::CurInstance()->GetIrisClass(strTmpPath);

	// 类还没有被定义
	if (!pClass) {
		if (pContexEnvironment) {
			// 如果没有域限定，那么就默认是这一层
			pUpperModule = pContexEnvironment->m_uType.m_pModule;
			pClass = new IrisClass(
				m_uType.m_pModuleStatement->m_pModuleName->m_strIdentifier,
				pSuperClass,
				pUpperModule);
		}
		else {
			// 在顶层定义
			// 如果没有域限定，那么就默认是这一层
			pClass = new IrisClass(
				m_uType.m_pModuleStatement->m_pModuleName->m_strIdentifier,
				pSuperClass,
				pUpperModule);
		}
		if (!pUpperModule) {
			pInterpreter->RegistClass(pClass->GetClassName(), pClass);
		}
		else {
			pUpperModule->AddClass(pClass);
			// 添加类对象常量
			IrisValue ivObj = IrisValue::WrapObjectPointerToIrisValue(pClass->m_pClassObject);
			pUpperModule->AddConstance(pClass->GetClassName(), ivObj);
		}
	}

	pClass->ClearInvolvingModules();
	if (m_uType.m_pClassStatement->m_pModules) {
		m_uType.m_pClassStatement->m_pModules->Ergodic(
			[&](IrisExpression* pExpression) {
			IrisValue ivModule = pExpression->Excute(pContexEnvironment);
			pClass->AddModule(((IrisModuleBaseTag*)(ivModule.GetInstanceNativePointer()))->GetModule());
		}
		);
	}

	pClass->ClearInvolvingModules();
	if (m_uType.m_pClassStatement->m_pInterfaces) {
		m_uType.m_pClassStatement->m_pInterfaces->Ergodic(
			[&](IrisExpression* pExpression) {
			IrisValue ivModule = pExpression->Excute(pContexEnvironment);
			pClass->AddInterface(((IrisInterfaceBaseTag*)(ivModule.GetInstanceNativePointer()))->GetInterface());
		}
		);
	}

	// Definetime Environment
	IrisContextEnvironment iceEnvironment;
	iceEnvironment.m_eType = IrisContextEnvironment::EnvironmentType::ClassDefineTime;
	iceEnvironment.m_uType.m_pClass = pClass;

	m_uType.m_pClassStatement->m_pBlock->Execute(&iceEnvironment);
	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pClass->m_pClassObject);

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteGetterStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisClass* pClass = pContexEnvironment->m_uType.m_pClass;

	if (m_uType.m_pGetterStatement->m_pGetteredVariable->m_eType != IrisIdentifier::IdentifilerType::InstanceVariable) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Variable of getter must be instance variable.");
		return srResult;
	}

	string strGetterName = m_uType.m_pGetterStatement->m_pGetteredVariable->m_strIdentifier;
	strGetterName.assign(strGetterName.begin() + 1, strGetterName.end());
	strGetterName = "__get_" + strGetterName;
	IrisMethod* pMethod = nullptr;

	if (m_uType.m_pGetterStatement->m_pBlock) {	
		IrisIdentifier* pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
														(char*)strGetterName.c_str());
		IrisFunctionHeader* pFunctionHeader = new IrisFunctionHeader(pIdentifier, nullptr, nullptr, false);
		pMethod = new IrisMethod(pFunctionHeader,
											m_uType.m_pGetterStatement->m_pBlock,
											nullptr,
											nullptr,
											IrisMethod::MethodAuthority::Everyone);
		pClass->AddInstanceMethod(pMethod);
	}
	else {
		IrisIdentifier* pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
			(char*)strGetterName.c_str());
		IrisFunctionHeader* pFunctionHeader = new IrisFunctionHeader(pIdentifier, nullptr, nullptr, false);
		pMethod = new IrisMethod(pFunctionHeader,
								IrisMethod::MethodType::GetterMethod,
								IrisMethod::MethodAuthority::Everyone);
		pClass->AddInstanceMethod(pMethod);
	}
	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pMethod->m_pMethodObject);
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteSetterStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisClass* pClass = pContexEnvironment->m_uType.m_pClass;

	if (m_uType.m_pSetterStatement->m_pSetteredVariable->m_eType != IrisIdentifier::IdentifilerType::InstanceVariable) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Variable of setter must be instance variable.");
		return srResult;
	}

	string strSetterName = m_uType.m_pSetterStatement->m_pSetteredVariable->m_strIdentifier;
	strSetterName.assign(strSetterName.begin() + 1, strSetterName.end());
	strSetterName = "__set_" + strSetterName;
	IrisMethod* pMethod = nullptr;
	if (m_uType.m_pSetterStatement->m_pBlock) {
		IrisIdentifier* pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
			(char*)strSetterName.c_str());
		IrisList<IrisIdentifier*>* pList = new IrisList<IrisIdentifier*>();
		pList->Add(new IrisIdentifier(
			IrisIdentifier::IdentifilerType::LocalVariable,
			(char*)m_uType.m_pSetterStatement->m_pParamName->m_strIdentifier.c_str()
		));
		IrisFunctionHeader* pFunctionHeader = new IrisFunctionHeader(pIdentifier, pList, nullptr, false);
		pMethod = new IrisMethod(pFunctionHeader,
			m_uType.m_pSetterStatement->m_pBlock,
			nullptr,
			nullptr,
			IrisMethod::MethodAuthority::Everyone);
		pClass->AddInstanceMethod(pMethod);
	}
	else {
		IrisIdentifier* pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
			(char*)strSetterName.c_str());
		IrisList<IrisIdentifier*>* pList = new IrisList<IrisIdentifier*>();
		pList->Add(new IrisIdentifier(
			IrisIdentifier::IdentifilerType::LocalVariable,
			//"value"
			(char*)m_uType.m_pSetterStatement->m_pParamName->m_strIdentifier.c_str()
			));
		IrisFunctionHeader* pFunctionHeader = new IrisFunctionHeader(pIdentifier, pList, nullptr, false);
		pMethod = new IrisMethod(pFunctionHeader,
			IrisMethod::MethodType::SetterMethod,
			IrisMethod::MethodAuthority::Everyone);
		pClass->AddInstanceMethod(pMethod);
	}

	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pMethod->m_pMethodObject);
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteGSetterStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	if (m_uType.m_pGSetterStatement->m_pGSetteredVariable->m_eType != IrisIdentifier::IdentifilerType::InstanceVariable) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Variable of gsetter must be instance variable.");
		return srResult;
	}

	IrisClass* pClass = pContexEnvironment->m_uType.m_pClass;

	// Getter
	string strGetterName = m_uType.m_pGSetterStatement->m_pGSetteredVariable->m_strIdentifier;
	strGetterName.assign(strGetterName.begin() + 1, strGetterName.end());
	strGetterName = "__get_" + strGetterName;

	// Setter
	string strSetterName = m_uType.m_pGSetterStatement->m_pGSetteredVariable->m_strIdentifier;
	strSetterName.assign(strSetterName.begin() + 1, strSetterName.end());
	strSetterName = "__set_" + strSetterName;

	IrisMethod* pMethod = nullptr;

	// Getter
	IrisIdentifier* pGetterIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
		(char*)strGetterName.c_str());
	IrisFunctionHeader* pGetterFunctionHeader = new IrisFunctionHeader(pGetterIdentifier, nullptr, nullptr, false);
	pMethod = new IrisMethod(pGetterFunctionHeader,
		IrisMethod::MethodType::GetterMethod,
		IrisMethod::MethodAuthority::Everyone);
	pClass->AddInstanceMethod(pMethod);

	// Setter
	IrisIdentifier* pSetterIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable,
		(char*)strSetterName.c_str());
	IrisList<IrisIdentifier*>* pList = new IrisList<IrisIdentifier*>();
	pList->Add(new IrisIdentifier(
		IrisIdentifier::IdentifilerType::LocalVariable,
		//"value"
		(char*)m_uType.m_pGSetterStatement->m_pGSetteredVariable->m_strIdentifier.c_str()
		));
	IrisFunctionHeader* pSetterFunctionHeader = new IrisFunctionHeader(pSetterIdentifier, pList, nullptr, false);
	pMethod = new IrisMethod(pSetterFunctionHeader,
		IrisMethod::MethodType::SetterMethod,
		IrisMethod::MethodAuthority::Everyone);
	pClass->AddInstanceMethod(pMethod);

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteAuthorityStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	string strMethodName = m_uType.m_pAuthorityStatement->m_pMethodName->m_strIdentifier;
	IrisAuthorityStatement::AuthorityEnvironment eEnvironment = m_uType.m_pAuthorityStatement->m_eEnvironment;
	IrisAuthorityStatement::AuthorityTarget eTarget = m_uType.m_pAuthorityStatement->m_eTarget;
	IrisAuthorityStatement::AuthorityType eType = m_uType.m_pAuthorityStatement->m_eType;

	if (m_uType.m_pAuthorityStatement->m_pMethodName->m_eType != IrisIdentifier::IdentifilerType::LocalVariable) {
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Only method can be given authirity.");
		return srResult;
	}

	if (eEnvironment == IrisAuthorityStatement::AuthorityEnvironment::Class) {
		IrisClass* pClass = pContexEnvironment->m_uType.m_pClass;
		IrisMethod* pMethod = nullptr;
		if (eTarget == IrisAuthorityStatement::AuthorityTarget::ClassMethod) {
			pMethod = pClass->GetCurrentClassMethod(IrisClass::SearchMethodType::ClassMethod, strMethodName);
		}
		else {
			pMethod = pClass->GetCurrentClassMethod(IrisClass::SearchMethodType::InstanceMethod, strMethodName);
		}
		if (!pMethod) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName +" not found.");
			return srResult;
		}
		switch (eType)
		{
		case IrisAuthorityStatement::AuthorityType::EveryOne:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Everyone);
			break;
		case IrisAuthorityStatement::AuthorityType::Relative:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Relative);
			break;
		case IrisAuthorityStatement::AuthorityType::Personal:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Personal);
			break;
		}
	}
	else {
		IrisModule* pModule = pContexEnvironment->m_uType.m_pModule;
		IrisMethod* pMethod = nullptr;
		if (eTarget == IrisAuthorityStatement::AuthorityTarget::ClassMethod) {
			pMethod = pModule->GetCurrentModuleMethod(IrisModule::SearchMethodType::ClassMethod, strMethodName);
		}
		else {
			pMethod = pModule->GetCurrentModuleMethod(IrisModule::SearchMethodType::InstanceMethod, strMethodName);
		}
		if (!pMethod) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " not found.");
			return srResult;
		}
		switch (eType)
		{
		case IrisAuthorityStatement::AuthorityType::EveryOne:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Everyone);
			break;
		case IrisAuthorityStatement::AuthorityType::Relative:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Relative);
			break;
		case IrisAuthorityStatement::AuthorityType::Personal:
			pMethod->SetMethodAuthority(IrisMethod::MethodAuthority::Personal);
			break;
		}
	}

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteInterfaceStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	string& strInterfaceName = m_uType.m_pInterfaceStatement->m_pInterfaceName->m_strIdentifier;
	IrisModule* pUpperModule = nullptr;
	IrisInterface* pInterface = nullptr;

	string strPath = "";
	if (pContexEnvironment) {
		IrisModule* pTmpModule = pContexEnvironment->m_uType.m_pModule;
		while (pTmpModule) {
			strPath = pTmpModule->GetModuleName() + "::" + strPath;
			pTmpModule = pTmpModule->m_pUpperModule;
		}
	}
	strPath += strInterfaceName;

	pInterface = IrisInterpreter::CurInstance()->GetIrisInterface(strPath);

	// 不存在则注册，否则扩充
	if (!pInterface) {
		if (pContexEnvironment) {
			// 如果没有域限定，那么就默认是这一层
			pUpperModule = pContexEnvironment->m_uType.m_pModule;
			pInterface = new IrisInterface(strInterfaceName, pUpperModule);
		}
		else {
			// 在顶层定义
			// 如果没有域限定，那么就默认是这一层
			pInterface = new IrisInterface(strInterfaceName, pUpperModule);
		}
		if (!pUpperModule) {
			IrisInterpreter::CurInstance()->RegistInterface(pInterface->GetInterfaceName(), pInterface);
		}
		else {
			pUpperModule->AddInvolvedInterface(pInterface);
			// 添加类对象常量
			IrisValue ivObj = IrisValue::WrapObjectPointerToIrisValue(pInterface->m_pInterfaceObject);
			pUpperModule->AddConstance(pInterface->GetInterfaceName(), ivObj);
		}
	}

	pInterface->ClearJointingInterfaces();
	if (m_uType.m_pInterfaceStatement->m_pInterfaces) {
		m_uType.m_pInterfaceStatement->m_pInterfaces->Ergodic(
			[&](IrisExpression* pExpression) {
			IrisValue ivInterface = pExpression->Excute(pContexEnvironment);
			pInterface->AddInterface(((IrisInterfaceBaseTag*)(ivInterface.GetInstanceNativePointer()))->GetInterface());
		}
		);
	}

	IrisInterpreter::CurInstance()->RegistInterface(strPath, pInterface);

	// Definetime Environment
	IrisContextEnvironment iceEnvironment;
	iceEnvironment.m_eType = IrisContextEnvironment::EnvironmentType::InterfaceDefineTime;
	iceEnvironment.m_uType.m_pInterface = pInterface;

	m_uType.m_pInterfaceStatement->m_pBlock->Execute(&iceEnvironment);
	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pInterface->m_pInterfaceObject);

	return srResult;
}

IrisStatementResult IrisStatement::ExcuteInterfaceFunctionStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	IrisInterface* pInterface = pContexEnvironment->m_uType.m_pInterface;

	string& strMethodName = m_uType.m_pInterfaceFunctionStatement->m_pFunctionName->m_strIdentifier;
	int nParamSize = !m_uType.m_pInterfaceFunctionStatement->m_pParameters ? 0 : m_uType.m_pInterfaceFunctionStatement->m_pParameters->GetSize();
	bool bHaveVariableParams = m_uType.m_pInterfaceFunctionStatement->m_pVariableParameter ? true : false;

	pInterface->AddInterfaceFunctionDeclare(strMethodName, nParamSize, bHaveVariableParams);

	srResult.m_ivValue = IrisValue::WrapObjectPointerToIrisValue(pInterface->m_pInterfaceObject);
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteOrderStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	// Order
	srResult = m_uType.m_pOrderStatement->m_pOrderBlock->Execute(pContexEnvironment);

	// Serve
	if (IrisInterpreter::CurInstance()->HaveIrregular()) {
		if (pContexEnvironment) {
			pContexEnvironment->AddLoaclVariable(m_uType.m_pOrderStatement->m_pIrregularObject->m_strIdentifier, IrisInterpreter::CurInstance()->GetIrregularObejet());
		}
		else {
			IrisInterpreter::CurInstance()->AddOtherValue(m_uType.m_pOrderStatement->m_pIrregularObject->m_strIdentifier, IrisInterpreter::CurInstance()->GetIrregularObejet());
		}
		IrisInterpreter::CurInstance()->UnregistIrregularObject();
		IrisInterpreter::CurInstance()->SetIrregularFlag(false);
		m_uType.m_pOrderStatement->m_pServeBlock->Execute(pContexEnvironment);
		IrisInterpreter::CurInstance()->SetIrregularFlag(true);
	}

	// Ignore
	if (m_uType.m_pOrderStatement->m_pIgnoreBlock) {
		srResult = m_uType.m_pOrderStatement->m_pIgnoreBlock->Execute(pContexEnvironment);
	}
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteGroanStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisValue ivErrorObject =  m_uType.m_pGroanStatement->m_pGroanExpression->Excute(pContexEnvironment);
	IrisInterpreter::CurInstance()->RegistIrregularObject(ivErrorObject);
	return 	IrisStatementResult (ivErrorObject, IrisStatementResult::StatementResultType::Normal);;
}

IrisStatementResult IrisStatement::ExcuteCastStatement(IrisContextEnvironment* pContexEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);

	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisValues ivsParams;
	IrisValue ivTmp;
	int nCount = 0;

	for (auto expr : m_uType.m_pCastStatement->m_pParameters->m_lsList) {
		ivTmp = expr->Excute(pContexEnvironment);
		pInterpreter->SaveTempValue(ivTmp);
		++nCount;
		ivsParams.push_back(ivTmp);
	}

	//m_uType.m_pCastStatement->m_pParameters->Ergodic(
	//	[&](IrisExpression* pExpression) {
	//		ivTmp = pExpression->Excute(pContexEnvironment);
	//		pInterpreter->SaveTempValue(ivTmp);
	//		++nCount;
	//		ivsParams.push_back(ivTmp);
	//	}
	//);
	srResult = pContexEnvironment->m_pClosureBlock->Excute(&ivsParams);

	pInterpreter->ClearTempValue(nCount);
	return srResult;
}

IrisStatementResult IrisStatement::ExcuteSuperStatement(IrisContextEnvironment* pContextEnvironment) {
	IrisStatementResult srResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	
	//查找父类的同名方法
	const string& strMethodName = pContextEnvironment->m_pCurMethod->GetMethodName();
	IrisObject* pObj = pContextEnvironment->m_uType.m_pCurObject;

	if (!pObj) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodCanSuperIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Super can only used in a instance method whose super class has the one with the same name.");
		return srResult;
	}
	if (pObj->GetClass()->GetClassName() == "Class" || pObj->GetClass()->GetClassName() == "Module") {
		//** Error **
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodCanSuperIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Super can only used in a instance method whose super class has the one with the same name.");
		return srResult;
	}

	IrisValues ivValues;
	int nCount = 0;
	if (m_uType.m_pSuperStatement->m_pParameters) {
		m_uType.m_pSuperStatement->m_pParameters->Ergodic(
			[&](IrisExpression* pExpression) {
			IrisValue ivParam = pExpression->Excute(pContextEnvironment);
			pInterpreter->SaveTempValue(ivParam);
			++nCount;
			ivValues.push_back(ivParam);
		}
		);
	}

	IrisClass* pSuperClass = pObj->m_pClass->m_pSuperClass;

	if (!pSuperClass) {
		// ** Error **
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodCanSuperIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Super can only used in a instance method whose super class has the one with the same name.");
		return srResult;
	}

	IrisMethod* pMethod = nullptr;
	bool bResult = false;
	pMethod = pSuperClass->GetMethod(IrisClass::SearchMethodType::InstanceMethod, strMethodName, bResult);

	if (pMethod) {
		IrisValue ivObj;
		ivObj.SetObject(pObj);
		if (m_uType.m_pSuperStatement->m_pParameters) {
			srResult.m_ivValue = pMethod->Call(ivObj, pContextEnvironment, &ivValues);
		}
		else {
			srResult.m_ivValue = pMethod->Call(ivObj, pContextEnvironment, nullptr);
		}
	}
	else {
		// ** Error **
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::NoMethodCanSuperIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Super can only used in a instance method whose super class has the one with the same name.");
		return srResult;
	}

	pInterpreter->ClearTempValue(nCount);
	return srResult;
}

IrisStatementResult IrisStatement::Excute(IrisContextEnvironment* pContexEnvironment) {

	IrisInterpreter::CurInstance()->SetExcutedLineNumber(m_nLineNumber);

	IrisValue ivValue;
	IrisStatementResult srResult;
	switch (m_eStatementType)
	{
	case IrisStatement::StatementType::NormalStatement:
		ivValue = m_uType.m_pNormalStatement->m_pExpression->Excute(pContexEnvironment);
		srResult.m_eReturnType = IrisStatementResult::StatementResultType::Normal;
		srResult.m_ivValue = ivValue;
		break;
	case IrisStatement::StatementType::ClassStatement:
		srResult = ExcuteClassStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::ModuleStatement:
		srResult = ExcuteModuleStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::InterfaceStatement:
		srResult = ExcuteInterfaceStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::FunctionStatement:
		srResult = ExcuteFunctionStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::IfStatement:
		srResult = ExcuteIfStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::SwitchStatement:
		srResult = ExcuteSwitchStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::ForStatement:
		srResult = ExcuteForStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::OrderStatement:
		srResult = ExcuteOrderStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::ReturnStatement:
		if (!pContexEnvironment) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of return can only be used in function.");
			return IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Normal);
		}
		if (m_uType.m_pReturnStatement->m_pReturnExpression) {
			ivValue = m_uType.m_pReturnStatement->m_pReturnExpression->Excute(pContexEnvironment);
			srResult.m_eReturnType = IrisStatementResult::StatementResultType::Return;
			srResult.m_ivValue = ivValue;
		}
		else {
			srResult = IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Return);
		}
		break;
	case IrisStatement::StatementType::BreakStatement:
		if ((!pContexEnvironment && IrisInterpreter::CurInstance()->GetUpperType() != IrisInterpreter::EnvironmentUpperType::Loop)
			|| (pContexEnvironment && pContexEnvironment->m_eUpperType != IrisContextEnvironment::EnvironmentUpperType::Loop)) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of break can only be used in a loop.");
		}
		srResult = IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Break);
		break;
	case IrisStatement::StatementType::ContinueStatement:
		if ((!pContexEnvironment && IrisInterpreter::CurInstance()->GetUpperType() != IrisInterpreter::EnvironmentUpperType::Loop)
			|| (pContexEnvironment && pContexEnvironment->m_eUpperType != IrisContextEnvironment::EnvironmentUpperType::Loop)) {
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::IdenfierTypeIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Statement of continue can only be used in a loop.");
		}
		srResult = IrisStatementResult(IrisInterpreter::CurInstance()->Nil(), IrisStatementResult::StatementResultType::Continue);
		break;
	case IrisStatement::StatementType::InterfaceFunctionStatement:
		srResult = ExcuteInterfaceFunctionStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::GroanStatement:
		srResult = ExcuteGroanStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::SetterStatement:
		srResult = ExcuteSetterStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::GetterStatement:
		srResult = ExcuteGetterStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::GSetterStatement:
		srResult = ExcuteGSetterStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::Authority:
		srResult = ExcuteAuthorityStatement(pContexEnvironment);
		break;
	case IrisStatement::StatementType::BlockStatement:
		if (pContexEnvironment->m_pClosureBlock) {
			srResult = pContexEnvironment->m_pWithBlock->Execute(pContexEnvironment);
		}
		else {
			srResult = pContexEnvironment->m_pWithouBlock->Execute(pContexEnvironment);
		}
		break;
	case IrisStatement::StatementType::CastStatement:
		//srResult = pContexEnvironment->m_pClosureBlock->Excute(pContexEnvironment);
		srResult = ExcuteCastStatement(pContexEnvironment);
		break;
	case IrisStatement:: StatementType::SuperStatement:
		srResult = ExcuteSuperStatement(pContexEnvironment);
		break;
	default:
		break;
	}
	return srResult;
}

IrisStatement::~IrisStatement()
{
}