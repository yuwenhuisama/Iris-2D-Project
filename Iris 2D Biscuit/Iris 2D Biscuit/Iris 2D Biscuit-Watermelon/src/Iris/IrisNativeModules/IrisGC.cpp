#include "IrisGC.h"
#include "IrisInterpreter.h"
#include "IrisMethodBase.h"

void IrisGC::_ErgodicTreeAndMark(IrisTree<IrisModule*>::Node<IrisModule*>* pCurNode) {
	pCurNode->m_tData->m_pModuleObject->Mark();
	for (auto value : pCurNode->m_tData->m_hsClassMethods) {
		value.second->m_pMethodObject->Mark();
	}
	for (auto value : pCurNode->m_tData->m_hsClassVariables) {
		value.second.m_ivValue.GetObjectPointer()->Mark();
	}
	for (auto value : pCurNode->m_tData->m_hsConstances) {
		value.second.m_ivValue.GetObjectPointer()->Mark();
	}
	for (auto value : pCurNode->m_tData->m_hsInstanceMethods) {
		value.second->m_pMethodObject->Mark();
	}
	for (auto value : pCurNode->m_tData->m_hsClasses) {

		value.second->m_pClassObject->Mark();
		for (auto value2 : value.second->m_hsClassMethods) {
			value2.second->m_pMethodObject->Mark();
		}
		for (auto value2 : value.second->m_hsClassVariables) {
			value2.second.m_ivValue.GetObjectPointer()->Mark();
		}
		for (auto value2 : value.second->m_hsConstances) {
			value2.second.m_ivValue.GetObjectPointer()->Mark();
		}
		for (auto value2 : value.second->m_hsInstanceMethods) {
			value2.second->m_pMethodObject->Mark();
		}
	}
	for (auto value : pCurNode->m_tData->m_hsInvolvedInterfaces) {
		value.second->m_pInterfaceObject->Mark();
	}
	for (auto value : pCurNode->m_mpChildNodes) {
		_ErgodicTreeAndMark(value.second);
	}
}

void IrisGC::_ClearMark() {
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisHeap& ihHeap = pInterpreter->m_ihHeap;
	list<IrisObject*>& lsObjects = ihHeap.GetHeapList();
	for (list<IrisObject*>::iterator iter = lsObjects.begin(); iter != lsObjects.end(); ) {
		(*iter)->ClearMark();
		++iter;
	}
}

void IrisGC::_Mark() {
	// 需要Mark的对象：临时栈、全局变量、Main环境下的变量/常量、所有类/模块的类变量/常量、所有可引用到的对象的实例变量、以及所有可以引用到的Method对象。
	((IrisValue&)IrisInterpreter::CurInstance()->Nil()).GetObjectPointer()->Mark();
	((IrisValue&)IrisInterpreter::CurInstance()->True()).GetObjectPointer()->Mark();
	((IrisValue&)IrisInterpreter::CurInstance()->False()).GetObjectPointer()->Mark();
	if (IrisInterpreter::CurInstance()->HaveIrregular()) {
		((IrisValue&)IrisInterpreter::CurInstance()->GetIrregularObejet()).GetObjectPointer()->Mark();
	}
	IrisInterpreter* pInter = IrisInterpreter::CurInstance();
	// 临时栈
	for (auto value : IrisInterpreter::CurInstance()->m_isStack.m_lsStack) {
		value.GetObjectPointer()->Mark();
	}
	// 全局变量
	for (auto value : IrisInterpreter::CurInstance()->m_mpGlobalVariables) {
		value.second.m_ivValue.GetObjectPointer()->Mark();
	}
	// Main环境变量
	for (auto value : IrisInterpreter::CurInstance()->m_mpMainEnvironmentVariables) {
		value.second.m_ivValue.GetObjectPointer()->Mark();
	}
	// Main环境常量
	for (auto value : IrisInterpreter::CurInstance()->m_mpConstances) {
		value.second.m_ivValue.GetObjectPointer()->Mark();
	}
	// Main环境类
	for (auto value : IrisInterpreter::CurInstance()->m_mpClassMap) {
		value.second->m_pClassObject->Mark();
		for (auto value2 : value.second->m_hsClassMethods) {
			value2.second->m_pMethodObject->Mark();
		}
		for (auto value2 : value.second->m_hsClassVariables) {
			value2.second.m_ivValue.GetObjectPointer()->Mark();
		}
		for (auto value2 : value.second->m_hsConstances) {
			value2.second.m_ivValue.GetObjectPointer()->Mark();
		}
		for (auto value2 : value.second->m_hsInstanceMethods) {
			value2.second->m_pMethodObject->Mark();
		}
	}
	// Main环境接口
	for (auto value : IrisInterpreter::CurInstance()->m_mpInterfaceMap) {
		value.second->m_pInterfaceObject->Mark();
	}
	// Main环境方法
	for (auto value : IrisInterpreter::CurInstance()->m_mpMainMethodMap) {
		value.second->m_pMethodObject->Mark();
	}
	// 开始遍历所有模块/类
	IrisTree<IrisModule*>& trModuleTree = IrisInterpreter::CurInstance()->m_trModuleTree;
	for (auto module : trModuleTree.m_pRoot->m_mpChildNodes) {
		_ErgodicTreeAndMark(module.second);
	}

	// Environment
	list<IrisContextEnvironment*>& lsEnvironments = IrisInterpreter::CurInstance()->m_evEnvironmentHeap;
	for (list<IrisContextEnvironment*>::iterator iter = lsEnvironments.begin(); iter != lsEnvironments.end(); )
	{
		if ((*iter)->m_nReferenced == 0) {
			sm_nCurrentContextEnvrionmentHeapSize -= sizeof(IrisContextEnvironment);
			delete (*iter);
			lsEnvironments.erase(iter++);
		}
		else {
			++iter;
		}
	}

	// 环境
	for (auto env : IrisInterpreter::CurInstance()->m_evEnvironmentHeap) {
		for (auto value : env->m_mpVariables) {
			value.second.m_ivValue.GetObjectPointer()->Mark();
		}
	}
}

void IrisGC::_Sweep() {
	// 清扫
	IrisInterpreter* pInterpreter = IrisInterpreter::CurInstance();
	IrisHeap& ihHeap = pInterpreter->m_ihHeap;
	list<IrisObject*>& lsObjects = ihHeap.GetHeapList();
	for (list<IrisObject*>::iterator iter = lsObjects.begin(); iter != lsObjects.end(); )
	{
		if (!(*iter)->m_bIsMaked) {
			if ((*iter)->m_bLiteralObject && !(*iter)->m_bLiteralObjectAssigned) {
				++iter;
			}
			else {
				if ((*iter)->GetClass()->GetClassName() != "Object") {
					sm_nCurrentHeapSize -= (*iter)->GetClass()->GetTrustteeSize() + sizeof(IrisObject);
				}
				else {
					sm_nCurrentHeapSize -= sizeof(IrisObject);
				}
				delete (*iter);
				lsObjects.erase(iter++);
			}
		}
		else {
			++iter;
		}
	}
}

int IrisGC::sm_nCurrentHeapSize = 0;
int IrisGC::sm_nNextThresholdSize = IrisGC::c_nThreshold;
int IrisGC::sm_nCurrentContextEnvrionmentHeapSize = 0;
int IrisGC::sm_nNextContextEnvrionmentThresholdSize = IrisGC::c_nThreshold;

bool IrisGC::sm_bFlag = true;

void IrisGC::ResetNextThreshold() {
	sm_nNextThresholdSize = sm_nCurrentHeapSize + c_nThreshold;
}

void IrisGC::AddSize(int nSize) {
	sm_nCurrentHeapSize += nSize;
}

void IrisGC::SetGCFlag(bool bFlag) {
	sm_bFlag = bFlag;
}

void IrisGC::Start() {
	if(sm_bFlag) {
		if(sm_nCurrentHeapSize > sm_nNextThresholdSize) {
			_ClearMark();
			_Mark();
			_Sweep();
			if (sm_nCurrentHeapSize > sm_nNextThresholdSize) {
				sm_nNextThresholdSize = sm_nCurrentHeapSize + c_nThreshold;
			}
		}
	}
}

void IrisGC::ForceStart() {
	if (sm_bFlag) {
		_ClearMark();
		_Mark();
		_Sweep();
		if (sm_nCurrentHeapSize > sm_nNextThresholdSize) {
			sm_nNextThresholdSize = sm_nCurrentHeapSize + c_nThreshold;
		}
	}
}

void IrisGC::AddContextEnvironmentSize() {
	sm_nCurrentContextEnvrionmentHeapSize += sizeof(IrisContextEnvironment);
}

void IrisGC::ContextEnvironmentGC() {
	if (sm_bFlag) {
		if (sm_nCurrentContextEnvrionmentHeapSize > sm_nNextContextEnvrionmentThresholdSize) {
			// Environment
			list<IrisContextEnvironment*>& lsEnvironments = IrisInterpreter::CurInstance()->m_evEnvironmentHeap;
			for (list<IrisContextEnvironment*>::iterator iter = lsEnvironments.begin(); iter != lsEnvironments.end(); )
			{
				if ((*iter)->m_nReferenced == 0) {
					sm_nCurrentContextEnvrionmentHeapSize -= sizeof(IrisContextEnvironment);
					delete (*iter);
					lsEnvironments.erase(iter++);
				}
				else {
					++iter;
				}
			}

			if (sm_nCurrentContextEnvrionmentHeapSize > sm_nNextContextEnvrionmentThresholdSize) {
				sm_nNextContextEnvrionmentThresholdSize = sm_nCurrentContextEnvrionmentHeapSize + c_nThreshold;
			}
		}
	}
}

IrisGC::IrisGC()
{
}


IrisGC::~IrisGC()
{
}
