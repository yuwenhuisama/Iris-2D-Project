#ifndef _H_IRISMETHOD_
#define _H_IRISMETHOD_

#include "IrisObject.h"
#include "IrisValue.h"
#include "IrisBlock.h"
#include "IrisParticularStatements.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

class IrisFunctionHeader;

class IrisMethod {
public:
	enum class MethodType {
		NativeMethod = 0,
		UserMethod,
		GetterMethod,
		SetterMethod,
	};

	enum class MethodAuthority {
		Everyone = 0,
		Relative,
		Personal,
	};

public:
	typedef IrisValue(*IrisNativeFunction)(IrisValue&, IrisValues*, IrisValues*, IrisContextEnvironment*);

private:
	struct UserFunction;

private:
	string m_strMethodName = "";
	bool m_bIsWithVariableParameter = false;
	MethodType m_eMethodType = MethodType::NativeMethod;
	int m_nParameterAmount = 0;
	union {
		IrisNativeFunction m_pfNativeFunction = nullptr;
		UserFunction* m_pUserFunction;
	} m_uFunction;

	MethodAuthority m_eAuthority = MethodAuthority::Everyone;

	IrisObject* m_pMethodObject = nullptr;

	bool _ParameterCheck(IrisValues* pParameters);
	IrisContextEnvironment* _CreateContextEnvironment(IrisObject* pCaller, IrisValues* pParameters);

public:
	IrisMethod(const string& strMethodName, IrisNativeFunction pfNativeFunction, int nParameterAmount, bool bIsWithVariableParameter, MethodAuthority eAuthority = MethodAuthority::Everyone);
	IrisMethod(IrisFunctionHeader* pFunctionHeader, IrisBlock* pFunctionBlock, IrisBlock* pWithBlock = nullptr, IrisBlock* pWithoutBlock = nullptr, MethodAuthority eAuthority = MethodAuthority::Everyone);
	IrisMethod(IrisFunctionHeader* pFunctionHeader, MethodType eType, MethodAuthority eAuthority = MethodAuthority::Everyone);

	void ResetObject();

	void SetMethodAuthority(MethodAuthority eAuthority);

	/* Native Function的定义
	IrisValue FunctionName(IrisValue ivObject, IrisValue ivParam1, IrisValue ivParam2, ...);
	*/
	// 按照类型的不同分别调用不同的函数（直接调用 or 解释运行）
	IrisValue Call(IrisValue& ivObject, IrisContextEnvironment* pContexEnvironment, IrisValues* pParameters = nullptr);
	IrisValue CallMainMethod(IrisValues* pParameters = nullptr);

	const string& GetMethodName();

	~IrisMethod();

	friend class IrisClass;
	friend class IrisModule;
	friend class IrisStatement;
	friend class IrisObject;
	friend class IrisGC;
};

#endif