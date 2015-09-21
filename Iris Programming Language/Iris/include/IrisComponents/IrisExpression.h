#ifndef _H_IRISEXPRESSION_
#define _H_IRISEXPRESSION_

#include "IrisList.h"
#include "IrisValue.h"

class IrisFieldIdentifier;
class IrisHashPair;
class IrisObject;
class IrisIdentifier;
class IrisContextEnvironment;
class IrisClosureBlockLiteral;

class IrisExpression {
public:
	enum class ExpressionType {
		Assign = 0,
		AssignAdd,
		AssignSub,
		AssignMul,
		AssignDiv,
		AssignMod,
		AssignBitAnd,
		AssignBitOr,
		AssignBitXor,
		AssignBitShr,
		AssignBitShl,
		AssignBitSar,
		AssignBitSal,

		LogicOr,
		LogicAnd,

		LogicBitOr,
		LogicBitXor,
		LogicBitAnd,

		Equal,
		NotEqual,

		GreatThan,
		GreatThanOrEqual,
		LessThan,
		LessThanOrEqual,

		BitShr,
		BitShl,
		BitSar,
		BitSal,
		Power,

		Add,
		Sub,
		Mul,
		Div,
		Mod,

		LogicNot,
		BitNot,
		Minus,
		Plus,

		Index,
		FunctionCall,
		SelfFunctionCall,
		Member,
		SelfMember,

		FieldIdentifier,
		Identifier,
		Integer,
		Float,
		String,
		True,
		False,
		Nil,

		Array,
		Hash,
	};

	class IrisBinaryExpression;
	class IrisUnaryExpression;
	class IrisIdentifierExpression;
	class IrisNativeObjectExpression;
	class IrisFunctionCallExpression;
	class IrisSelfFunctionCallExpression;
	class IrisFieldExpression;
	class IrisMemberExpression;
	class IrisSelfMemberExpression;
	class IrisArrayExpression;
	class IrisHashExpression;
	class IrisIndexExpression;
	
private:
	ExpressionType m_eType = ExpressionType::Assign;
	
	union {
		IrisBinaryExpression* m_pBinaryExpression = nullptr;
		IrisUnaryExpression* m_pUnaryExpression;
		IrisIdentifierExpression* m_pIdentifierExpression;
		IrisNativeObjectExpression* m_pNativeObjectExpression;
		IrisFunctionCallExpression* m_pFunctionCallExpression;
		IrisSelfFunctionCallExpression* m_pSelfCallExpression;
		IrisFieldExpression* m_pFieldExpression;
		IrisMemberExpression* m_pMemberExpression;
		IrisSelfMemberExpression* m_pSelfMemberExpression;
		IrisArrayExpression* m_pArrayExpression;
		IrisHashExpression* m_pHashExpression;
		IrisIndexExpression* m_pIndexExpression;
		//IrisInstantValueExpression* m_pInstantValueExpression;
	} m_uType;

private:
	bool _FieldIsSingleWithoutField();
	const string& _FieldSingleName();

public:
	int m_nLineNumber = 0;

public:
	static IrisExpression* CreateBinaryExpression(ExpressionType eType, IrisExpression* pLeftExpression, IrisExpression* pRightExpression);
	static IrisExpression* CreateUnaryExpression(ExpressionType eType, IrisExpression* pExpression);
	static IrisExpression* CreateIndexExpression(IrisExpression* pObjectExpression, IrisExpression* pIndexExpression);
	static IrisExpression* CreateFunctionCallExpression(IrisExpression* pObject, IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock);
	static IrisExpression* CreateSelfFunctionCallExpression(IrisIdentifier* pFunctionName, IrisList<IrisExpression*>* pParameters, IrisClosureBlockLiteral* pClosureBlock);
	static IrisExpression* CreateMemberExpression(IrisExpression* pObjectExpression, IrisIdentifier* pMemberName);
	static IrisExpression* CreateSelfMemberExpression(IrisIdentifier* pMemberName);
	static IrisExpression* CreateFieldExpression(IrisList<IrisIdentifier*>* pList, IrisIdentifier* pIdentifier, bool bIsTop);
	static IrisExpression* CreateIdentifierExpression(IrisIdentifier* pIdentifier);
	static IrisExpression* CreateInstantValueExpression(ExpressionType eType);
	static IrisExpression* CreateArrayExpression(IrisList<IrisExpression*>* pElements);
	static IrisExpression* CreateHashExpression(IrisList<IrisHashPair*>* pElements);
	static IrisExpression* CreateNativeObjectExpression(ExpressionType eType, IrisObject* pObject);

public:

	IrisValue Excute(IrisContextEnvironment* pContextEnvironment);
	//const IrisValue& ExcuteAssign(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteAssign(IrisExpression* pLeft, const IrisValue& ivResult, IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteAssignOperation(ExpressionType eType, IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteOperation(ExpressionType eType, IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteIdentifier(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteFunctionCall(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteSelfFunctionCall(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteFieldIdentifier(IrisContextEnvironment* pContextEnvironment);

	IrisValue ExcuteMember(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteSelfMember(IrisContextEnvironment* pContextEnvironment);

	IrisValue ExcuteArray(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteHash(IrisContextEnvironment* pContextEnvironment);
	IrisValue ExcuteIndex(IrisContextEnvironment* pContextEnvironment);

	IrisExpression();
	~IrisExpression();

	friend class IrisStatement;
};

#endif