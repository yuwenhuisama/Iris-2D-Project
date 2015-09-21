#ifndef _H_IRISIDENTIFIER_
#define _H_IRISIDENTIFIER_
#include <string>
using namespace std;

class IrisIdentifier
{
public:
	enum class IdentifilerType {
		Constance = 0,
		LocalVariable,
		GlobalVariable,
		InstanceVariable,
		ClassVariable,
	};

private:
	string m_strIdentifier;
	IdentifilerType m_eType = IdentifilerType::Constance;

public:
	IrisIdentifier(IdentifilerType eType, char* szIdentifier);
	~IrisIdentifier();

	friend class IrisMethod;
	friend class IrisExpression;
	friend class IrisStatement;
	friend class IrisClosureBlock;
};

#endif