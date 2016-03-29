#ifndef _H_IIRISCONTEXTENVIRONMENT_
#define _H_IIRISCONTEXTENVIRONMENT_

class IIrisClosureBlock;

class IIrisContextEnvironment
{
public:

	IIrisContextEnvironment() {}

	//virtual IIrisClosureBlock* GetClosureBlock() = 0;
	//virtual void SetClosureBlock(IIrisClosureBlock* pBlock) = 0;
	//virtual IIrisContextEnvironment* GetUpperContextEnvrioment() = 0;

	//virtual const IrisValue& GetVariableValue(const string& strVariableName, bool& bResult) = 0;
	//virtual void AddLocalVariable(const string& strVariableName, const IrisValue& ivValue) = 0;

	virtual ~IIrisContextEnvironment() = 0 {};
};

#endif