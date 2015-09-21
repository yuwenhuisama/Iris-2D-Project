#ifndef _H_IRISINTERFACE_
#define _H_IRISINTERFACE_

#include <string>
#include <map>
using namespace std;

class IrisInterface;
class IrisModule;
class IrisObject;

class IrisInterface {
public:
	struct InterfaceFunctionDeclare {
		string m_strInterfaceName = "";
		int m_nParameterAmount = 0;
		bool m_bHaveVariableParameter = false;

		InterfaceFunctionDeclare(const string& strInterfaceName, int nParameterAmount, bool b_HaveVariableParameter) : m_strInterfaceName(strInterfaceName), m_nParameterAmount(nParameterAmount), m_bHaveVariableParameter(b_HaveVariableParameter){ }
		InterfaceFunctionDeclare() { }
	};

private:
	typedef map<string, InterfaceFunctionDeclare> _InterfaceFunctionDeclareMap;
	typedef pair<string, InterfaceFunctionDeclare> _InterfaceFunctionDeclarePair;
	typedef map<string, IrisInterface*> _InterfaceHash;
	typedef pair<string, IrisInterface*> _InterfacePair;

private:
	string m_strInterfaceName = "";
	IrisModule* m_pUpperModule = nullptr;
	_InterfaceFunctionDeclareMap m_mpFunctionDeclareMap;
	_InterfaceHash m_mpInterfaces;

private:
	IrisObject* m_pInterfaceObject = nullptr;

public:

	const string& GetInterfaceName() { return m_strInterfaceName; }

	IrisInterface(const string& strInterfaceName, IrisModule* pUpperModule = nullptr);
	IrisInterface::~IrisInterface();

	void ClearJointingInterfaces();

	void AddInterface(IrisInterface* pInterface);
	void AddInterfaceFunctionDeclare(const string& strFunctionName, int m_nParameterAmount, bool bHaveHaveVariableParameter = false);

	friend class IrisClass;
	friend class IrisModule;
	friend class IrisObject;
	friend class IrisInterpreter;
	friend class IrisStatement;
	friend class IrisGC;
};

#endif