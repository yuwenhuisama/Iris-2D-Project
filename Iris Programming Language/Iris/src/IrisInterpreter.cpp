#include "IrisInterpreter.h"
#include "IrisInteger.h"
#include "IrisFloat.h"
#include "IrisString.h"
#include "IrisClassBase.h"
#include "IrisObjectBase.h"
#include "IrisClassBase.h"
#include "IrisModuleBase.h"
#include "IrisTrueClass.h"
#include "IrisFalseClass.h"
#include "IrisNilClass.h"
#include "IrisArray.h"
#include "IrisHash.h"
#include "IrisMethodBase.h"
#include "IrisInterfaceBase.h"
#include "IrisGCModule.h"
#include "IrisClosureBlockBase.h"
#include "IrisStatementResult.h"

#include <fstream>
using namespace std;

IrisInterpreter* IrisInterpreter::s_pCurInstance = nullptr;

int IrisInterpreter::_Split(const string& str, list<string>& ret_, string sep) {
	if (str.empty())
	{
		return 0;
	}

	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

void IrisInterpreter::SetCurInterpreter(IrisInterpreter* pInterpreter) {
	s_pCurInstance = pInterpreter;
}

IrisInterpreter* IrisInterpreter::CurInstance() {
	return s_pCurInstance;
}

IrisInterpreter::IrisInterpreter()
{
}

IrisClass* IrisInterpreter::GetIrisClass(const string& strClassFullFieldName) {
	IrisModule* pTmpModule = nullptr;
	IrisClass* pClass = nullptr;
	list<string> lsRoute;
	_Split(strClassFullFieldName, lsRoute, "::");
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);
	string strRegistName = lsRoute.back();
	lsRoute.pop_back();
	if (!lsRoute.empty()) {
		bool bResult = m_trModuleTree.GetNodeData(lsRoute, pTmpModule);
		if (!bResult) {
			// **Error**
			return nullptr;
		}
		pClass = pTmpModule->GetClass(strRegistName);
	}
	else {
		if (m_mpClassMap.find(strRegistName) != m_mpClassMap.end()) {
			pClass = m_mpClassMap[strRegistName];
		}
		else {
			pClass = nullptr;
		}
	}

	return pClass;
}

IrisInterface* IrisInterpreter::GetIrisInterface(const string& strInterfaceFullFieldName) {

	IrisModule* pTmpModule = nullptr;
	IrisInterface* pInterface = nullptr;
	list<string> lsRoute;
	_Split(strInterfaceFullFieldName, lsRoute, "::");
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);
	string strRegistName = lsRoute.back();
	lsRoute.pop_back();
	if (!lsRoute.empty()) {
		bool bResult = m_trModuleTree.GetNodeData(lsRoute, pTmpModule);
		if (!bResult) {
			// **Error**
			return nullptr;
		}
		pInterface = pTmpModule->GetInterface(strRegistName);
	}
	else {
		if (m_mpInterfaceMap.find(strRegistName) != m_mpInterfaceMap.end()) {
			pInterface = m_mpInterfaceMap[strRegistName];
		}
		else {
			pInterface = nullptr;
		}
	}

	return pInterface;
}

bool IrisInterpreter::RegistClass(const string& strClassFullFieldName, IrisClass* pClass) {

	if (GetIrisModule(strClassFullFieldName)
		|| GetIrisInterface(strClassFullFieldName)) {
		// **Error**
		return false;
	}

	IrisModule* pTmpModule = nullptr;
	list<string> lsRoute;
	_Split(strClassFullFieldName, lsRoute, "::");
	string strRegistName = lsRoute.back();
	lsRoute.pop_back();

	if (!lsRoute.empty()) {
		if (!m_trModuleTree.GetNodeData(lsRoute, pTmpModule)){
			// **Error**
			return false;
		}

		if (pTmpModule->GetClass(strRegistName)){
			// **Error**
			return false;
		}

		pTmpModule->AddClass(pClass);
		pClass->m_pUpperModule = pTmpModule;
	}
	else {
		m_mpClassMap.insert(_ClassPair(strRegistName, pClass));
	}

	pClass->NativeClassDefine();
	// 添加类对象常量
	IrisValue ivObj = IrisValue::WrapObjectPointerToIrisValue(pClass->m_pClassObject);

	if (pClass->m_pUpperModule){
		pClass->m_pUpperModule->AddConstance(strRegistName, ivObj);
	}
	else{
		AddConstance(strRegistName, ivObj);
	}

	return true;
}

bool IrisInterpreter::RegistModule(const string& strModuleFullFieldName, IrisModule* pModule) {

	if (GetIrisClass(strModuleFullFieldName)
		|| GetIrisInterface(strModuleFullFieldName)) {
		// **Error**
		return false;
	}

	IrisModule* pTmpModule = nullptr;
	list<string> lsRoute;
	_Split(strModuleFullFieldName, lsRoute, "::");
	if (m_trModuleTree.GetNodeData(lsRoute, pTmpModule)) {
		return false;
	}
	string strRegistName = lsRoute.back();
	lsRoute.pop_back();
	m_trModuleTree.AddNode(lsRoute, strRegistName, pModule);

	pModule->NativeClassDefine();
	// 添加模块对象常量
	IrisValue ivObj = IrisValue::WrapObjectPointerToIrisValue(pModule->m_pModuleObject);
	if (pModule->m_pUpperModule){
		pModule->m_pUpperModule->AddConstance(strRegistName, ivObj);
	}
	else{
		AddConstance(strRegistName, ivObj);
	}

	return true;
}

bool IrisInterpreter::RegistInterface(const string& strInterfaceFullFieldName, IrisInterface* pInterface) {

	if (GetIrisModule(strInterfaceFullFieldName)
		|| GetIrisClass(strInterfaceFullFieldName)) {
		// **Error**
		return false;
	}

	IrisModule* pTmpModule = nullptr;
	list<string> lsRoute;
	_Split(strInterfaceFullFieldName, lsRoute, "::");
	string strRegistName = lsRoute.back();
	lsRoute.pop_back();

	if (!lsRoute.empty()) {
		if (!m_trModuleTree.GetNodeData(lsRoute, pTmpModule)) {
			// **Error**
			return false;
		}

		if (pTmpModule->GetClass(strRegistName)) {
			// **Error**
			return false;
		}

		pTmpModule->AddInvolvedInterface(pInterface);
		pInterface->m_pUpperModule = pTmpModule;
	}
	else {
		m_mpInterfaceMap.insert(_InterfacePair(strRegistName, pInterface));
	}

	//pClass->NativeClassDefine();
	// 添加类对象常量
	IrisValue ivObj = IrisValue::WrapObjectPointerToIrisValue(pInterface->m_pInterfaceObject);

	if (pInterface->m_pUpperModule) {
		pInterface->m_pUpperModule->AddConstance(strRegistName, ivObj);
	}
	else {
		AddConstance(strRegistName, ivObj);
	}

	return true;
}

IrisModule* IrisInterpreter::GetIrisModule(const string& strModuleFullFieldName) {
	//if (m_mpModuleMap.find(strModuleFullFilledName) != m_mpModuleMap.end()) {
	//	return m_mpModuleMap[strModuleFullFilledName];
	//}
	//return nullptr;
	IrisModule* pModule = nullptr;
	list<string> lsRoute;
	_Split(strModuleFullFieldName, lsRoute, "::");
	bool bResult = m_trModuleTree.GetNodeData(lsRoute, pModule);
	return pModule;
}

IrisClass* IrisInterpreter::GetIrisClass(const list<string>& lsRoute) {
	//IrisClass* pClass = nullptr;
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);

	IrisModule* pTmpModule = nullptr;
	IrisClass* pClass = nullptr;
	list<string> lsTmpRoute;
	//_Split(strClassFullFieldName, lsRoute, "::");
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);
	string strRegistName = lsRoute.back();
	lsTmpRoute.assign(lsRoute.begin(), lsRoute.end());
	lsTmpRoute.pop_back();
	bool bResult = m_trModuleTree.GetNodeData(lsTmpRoute, pTmpModule);
	if (!bResult) {
		// **Error**
		return nullptr;
	}

	pClass = pTmpModule->GetClass(strRegistName);
	return pClass;
}

IrisInterface* IrisInterpreter::GetIrisInterface(const list<string>& lsRoute) {
	//IrisClass* pClass = nullptr;
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);

	IrisModule* pTmpModule = nullptr;
	IrisInterface* pInterface = nullptr;
	list<string> lsTmpRoute;
	//_Split(strClassFullFieldName, lsRoute, "::");
	//bool bResult = m_trClassTree.GetNodeData(lsRoute, pClass);
	string strRegistName = lsRoute.back();
	lsTmpRoute.assign(lsRoute.begin(), lsRoute.end());
	lsTmpRoute.pop_back();
	bool bResult = m_trModuleTree.GetNodeData(lsTmpRoute, pTmpModule);
	if (!bResult) {
		// **Error**
		return nullptr;
	}

	pInterface = pTmpModule->GetInterface(strRegistName);
	return pInterface;
}

IrisModule* IrisInterpreter::GetIrisModule(const list<string>& lsRoute) {
	IrisModule* pModule = nullptr;
	bool bResult = m_trModuleTree.GetNodeData(lsRoute, pModule);
	return pModule;
}

void IrisInterpreter::Initialize() {
	// Maybe a little mass....
	RegistClass("Class", new IrisClassBase());
	GetIrisClass("Class")->ResetNativeObject();
	bool bResult = false;
	((IrisValue&)GetConstance("Class", bResult)).SetObject(GetIrisClass("Class")->m_pClassObject);
	RegistClass("Module", new IrisModuleBase());
	RegistClass("Interface", new IrisInterfaceBase());
	RegistModule("Kernel", new IrisKernel());
	RegistClass("Object", new IrisObjectBase());

	GetIrisClass("Class")->SetSuperClass(GetIrisClass("Object"));
	GetIrisClass("Module")->SetSuperClass(GetIrisClass("Object"));
	
	RegistClass("Method", new IrisMethodBase(GetIrisClass("Object")));

	GetIrisClass("Class")->ResetAllMethodsObject();
	GetIrisClass("Object")->ResetAllMethodsObject();
	GetIrisClass("Module")->ResetAllMethodsObject();
	GetIrisClass("Interface")->ResetAllMethodsObject();
	GetIrisModule("Kernel")->ResetAllMethodsObject();

	RegistClass("String", new IrisString(GetIrisClass("Object")));
	RegistClass("Integer", new IrisInteger(GetIrisClass("Object")));
	RegistClass("Float", new IrisFloat(GetIrisClass("Object")));

	RegistClass("TrueClass", new IrisTrueClass(GetIrisClass("Object")));
	RegistClass("FalseClass", new IrisFalseClass(GetIrisClass("Object")));
	RegistClass("NilClass", new IrisNilClass(GetIrisClass("Object")));

	RegistClass("Array", new IrisArray(GetIrisClass("Object")));
	RegistClass("Hash", new IrisHash(GetIrisClass("Object")));

	RegistModule("GC", new IrisGCModule());

	RegistClass("Block", new IrisClosureBlockBase(GetIrisClass("Object")));

	// True/False/Nil
	m_ivTrue = GetIrisClass("TrueClass")->CreateInstance(nullptr, nullptr);
	m_ivFalse = GetIrisClass("FalseClass")->CreateInstance(nullptr, nullptr);
	m_ivNil = GetIrisClass("NilClass")->CreateInstance(nullptr, nullptr);
}

void IrisInterpreter::ShutDown() {

}

bool IrisInterpreter::AddNewInstanceToHeap(IrisValue& ivValue) {
	m_ihHeap.AddObject(ivValue.GetObject());
	return true;
}

bool IrisInterpreter::AddNewEnvironmentToHeap(IrisContextEnvironment* pEnvironment){
	m_evEnvironmentHeap.push_back(pEnvironment);
	return true;
}

IrisValue IrisInterpreter::ExcuteStatements(IrisContextEnvironment* pContextEnvironment) {
	IrisValue ivResult = Nil();

	if (m_bEvalFlag) {
		for (auto stmt : m_pEvalStatements) {
			if (HaveIrregular()) {
				GroanFatalIrregular(FatalIrregular::IrregularNotDealedIrregular, 0, "There still a irregular goaned but not being dealed with,");
			}
			ivResult = stmt->Excute(pContextEnvironment).m_ivValue;
		}
		m_bEvalFlag = false;
	}
	else {
		for (auto stmt : *m_pCurrentStatements) {
			if (HaveIrregular()) {
				GroanFatalIrregular(FatalIrregular::IrregularNotDealedIrregular, 0, "There still a irregular goaned but not being dealed with,");
			}
			ivResult = stmt->Excute(nullptr).m_ivValue;
		}
	}

	return ivResult;
}

void IrisInterpreter::SetCurrentFile(const string& strFile) {
	m_strCurFileName = strFile;
	if (m_mpStatements.find(strFile) == m_mpStatements.end()) {
		m_mpStatements.insert(_StatementsPair(strFile, new _StatementList()));
	}
	m_pCurrentStatements = m_mpStatements[strFile];
}

void IrisInterpreter::LoadScript(const string& strFile) {

	extern char* g_pCurrentString;
	extern int g_nCurrentStringLength;
	extern int g_nReadLength;
	extern int yyparse(void);

	CurInstance()->SetCurrentFile(strFile);

	string strLine;
	string strText;

	fstream fFile("sentence.utf8");

	//fFile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
	//std::locale::global(std::locale(""));

	fFile.open(strFile, ios::in);
	if (!fFile) {
		fprintf(stderr, "%s not found.\n", strFile.c_str());
		exit(1);
	}

	while (getline(fFile, strLine)) {
		strText += strLine + "\n";
	}

	fFile.close();

	g_pCurrentString = (char*)strText.c_str();
	g_nCurrentStringLength = strText.length();
	g_nReadLength = 0;

	if (yyparse()) {
		/* BUGBUG */
		exit(1);
	}
}

void IrisInterpreter::LoadScriptString(const string& strScript) {

	extern char* g_pCurrentString;
	extern int g_nCurrentStringLength;
	extern int g_nReadLength;
	extern int yyparse(void);

	for (auto stat : m_pEvalStatements) {
		delete stat;
	}
	m_pEvalStatements.clear();

	g_pCurrentString = (char*)strScript.c_str();
	g_nCurrentStringLength = strScript.length();
	g_nReadLength = 0;
	m_bEvalFlag = true;

	if (yyparse()) {
		/* BUGBUG */
		exit(1);
	}
}

IrisMethod* IrisInterpreter::GetMainMethod(const string& strMethodName){
	if (m_mpMainMethodMap.find(strMethodName) == m_mpMainMethodMap.end()) {
		return nullptr;
	}
	return m_mpMainMethodMap[strMethodName];
}

void IrisInterpreter::AddMainMethod(const string& strMethodName, IrisMethod* pMethod) {
	if (m_mpMainMethodMap.find(strMethodName) == m_mpMainMethodMap.end()) {
		m_mpMainMethodMap.insert(_MethodPair(strMethodName, pMethod));
	}
	else {
		delete m_mpMainMethodMap[strMethodName];
		m_mpMainMethodMap[strMethodName] = pMethod;
	}
}

void IrisInterpreter::GroanFatalIrregular(FatalIrregular eIrregularType, int nLineno, const string& strTipMessage) {

	string strIrregularTitle = "<Irregular : ";
	string strMessage = "\n  Irregular-happened Report : Oh! Master, an Irregular has happened and Iris is not clever and dosen't kown how to deal with it. Could you please cheak it yourself? \n";
	string strIrregularMessage = ">The Irregular name is ";
	stringstream ssStream;
	ssStream << nLineno;
	string strLinenoMessage = "";
	if (nLineno > 0) {
		strLinenoMessage = ">and happened at line " + ssStream.str() + ".\n";
	}

	switch (eIrregularType)
	{
	case FatalIrregular::SyntaxIrregular :
		strMessage = strIrregularTitle + "SyntaxIrregular>" + strMessage;
		strMessage += strIrregularMessage + "SyntaxIrregular," + "\n" + strLinenoMessage;
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::NoMethodIrregular :
		strMessage = strIrregularTitle + "NoMethodIrregular>" + strMessage;
		strMessage += strIrregularMessage + "NoMethodIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::IdenfierTypeIrregular:
		strMessage = strIrregularTitle + "IdenfierTypeIrregular>" + strMessage;
		strMessage += strIrregularMessage + "IdenfierTypeIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::IrregularNotDealedIrregular:
		strMessage = strIrregularTitle + "IrregularNotDealedIrregular>" + strMessage;
		strMessage += strIrregularMessage + "IrregularNotDealedIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::SourceObjectIrregular:
		strMessage = strIrregularTitle + "SourceObjectIrregular>" + strMessage;
		strMessage += strIrregularMessage + "SourceObjectIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::IdentifierNotFoundIrregular:
		strMessage = strIrregularTitle + "IdentifierNotFoundIrregular>" + strMessage;
		strMessage += strIrregularMessage + "IdentifierNotFoundIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ReturnIrregular:
		strMessage = strIrregularTitle + "ReturnIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ReturnIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::LeftValueIrregular:
		strMessage = strIrregularTitle + "LeftValueIrregular>" + strMessage;
		strMessage += strIrregularMessage + "LeftValueIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::SelfPointerIrregular:
		strMessage = strIrregularTitle + "SelfPointerIrregular>" + strMessage;
		strMessage += strIrregularMessage + "SelfPointerIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ConstanceReassignIrregular:
		strMessage = strIrregularTitle + "ConstanceReassignIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ConstanceReassignIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ConstanceDeclareIrregular:
		strMessage = strIrregularTitle + "ConstanceDeclareIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ConstanceDeclareIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ClassVariableDeclareIrregular:
		strMessage = strIrregularTitle + "ClassVariableDeclareIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ClassVariableDeclareIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::MethodAuthorityIrregular:
		strMessage = strIrregularTitle + "MethodAuthorityIrregular>" + strMessage;
		strMessage += strIrregularMessage + "MethodAuthorityIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ClassNotCompleteIrregular :
		strMessage = strIrregularTitle + "ClassNotCompleteIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ClassNotCompleteIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::ParameterNotFitIrregular:
		strMessage = strIrregularTitle + "ParameterNotFitIrregular>" + strMessage;
		strMessage += strIrregularMessage + "ParameterNotFitIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	case FatalIrregular::NoMethodCanSuperIrregular:
		strMessage = strIrregularTitle + "NoMethodCanSuperIrregular>" + strMessage;
		strMessage += strIrregularMessage + "NoMethodCanSuperIrregular," + "\n" + strLinenoMessage;
		strMessage += ">Tip : " + strTipMessage + "\n";
		fprintf(stderr, strMessage.c_str());
		exit(1);
		break;
	default:
		break;
	}
}

IrisInterpreter::~IrisInterpreter()
{
}
