%{
#include "Iris.h"
#include <sstream>
using namespace std;
//#define YYDEBUG 1

extern int yylex();

int yyerror(char const *str)
{
	extern char *yytext;

	string strMessage = "<Irregular : SyntaxIrregular>\n  Irregular-happened Report : Oh! Master, an Irregular has happened and Iris is not clever and dosen't kown how to deal with it. Can you please cheak it yourself? \n";
	string strIrregularMessage = ">The Irregular name is ";
	stringstream ssStream;
	ssStream << IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	string strLinenoMessage = ">and happened at line " + ssStream.str() + " where token is " + string(yytext) + ".";

	strMessage += strIrregularMessage + "SyntaxIrregular," + "\n" + strLinenoMessage + "\n";

	//fprintf(stderr, "parser error near %s\n", yytext);
	fprintf(stderr, strMessage.c_str());
	return 0;
}
%}

%union {
	IrisIdentifier* m_pIdentifier = nullptr;
	IrisList<IrisIdentifier*>* m_pIdentifierList;
	IrisExpression* m_pExpression; 
	IrisList<IrisExpression*>* m_pExpressionList;
	IrisStatement* m_pStatement;
	IrisList<IrisStatement*>* m_pStatementList;
	IrisExpression::ExpressionType m_eExpressionType;
	IrisBlock* m_pBlock;
	IrisFunctionHeader* m_pFunctionHeader;
	IrisConditionIf* m_pConditionIf;
	IrisLoopIf* m_pLoopIf;
	IrisElseIf* m_pElseIf;
	IrisList<IrisElseIf*>* m_pElseIfList;
	IrisWhen* m_pWhen;
	IrisList<IrisWhen*>* m_pWhenList;
	IrisSwitchBlock* m_pSwitchBlock;
	IrisHashPair* m_pHashPair;
	IrisList<IrisHashPair*>* m_pHashPairList;
	IrisClosureBlockLiteral* m_pClosureBlockLiteral;
}

%token <m_pExpression>     INTEGER
%token <m_pExpression>     FLOAT
%token <m_pExpression>     STRING
%token <m_pIdentifier>     IDENTIFIER
%token FUNCTION CLASS MODULE INTERFACE EXTENDS INVOLVES JOINTS PERSONAL RELATIVE
	   EVERYONE GET SET GSET IF ELSE ELSEIF FOR IN SWITCH WHEN CAST ITERATOR
	   SUPER BREAK CONTINUE RETURN BLOCK SELF WITH WITHOUT ORDER SERVE
	   IGNORE GROAN TRUE FALSE NIL DOT
	   ALIAS RETRY REDO GOTO CONST GLOBAL STATIC LP RP LC RC LB RB 
	   SEMICOLON COMMA LOGICAL_AND LOGICAL_OR LOGICAL_NOT ASSIGN 
	   ADD SUB MUL DIV MOD POWER BIT_AND BIT_OR BIT_XOR BIT_NOT
	   ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV 
	   ASSIGN_MOD ASSIGN_BIT_AND ASSIGN_BIT_OR ASSIGN_BIT_XOR BIT_SHR 
	   EQ NE GT GE LT LE
	   BIT_SHL BIT_SAR BIT_SAL ASSIGN_BIT_SHR ASSIGN_BIT_SHL ASSIGN_BIT_SAR
	   ASSIGN_BIT_SAL ITER FILED SHARP CONLON
%type<m_pStatement>  statement module_involve_statement function_statement function_operator_statement
					 return_statement if_statement break_statement continue_statement switch_statement
					 module_statement class_statement class_involve_statement
					 setter_statement getter_statement getter_setter_statement
					 class_everyone_statement class_relative_statement class_personal_statement
					 module_everyone_statement module_relative_statement module_personal_statement
					 interface_statement interface_involve_statement interface_func_statement
					 for_statement order_statement groan_statement order_involve_statement
					 function_involve_statement closure_involve_statement with_without_involve_statement
					 block_statement cast_statement super_statement
%type<m_pExpression> expression logic_or_expression logic_and_expression logic_bit_or_expression
					 logic_bit_xor_expression logic_bit_and_expression logic_equal_compare_expression
					 logic_not_equal_expression logic_shift_expression add_sub_expression
					 mul_div_mod_expression unary_expression top_expression primary_expression
					 extends_field identifier_with_field array_literal hash_literal power_expression
%type<m_pIdentifier> loop_time operator
%type<m_pIdentifierList> identifier_list field_identifier

%type<m_pBlock> block module_block class_block interface_block ignore_block order_block function_block with_without_block
%type<m_pClosureBlockLiteral> closure_block
%type<m_pExpressionList> expression_list field_identifier_list module_field interface_field
%type<m_pStatementList> statement_list module_involve_statement_list class_involve_statement_list
						interface_involve_statement_list order_involve_statement_list function_involve_statement_list
						closure_involve_statement_list with_without_involve_statement_list

%type<m_pConditionIf> condition_if
%type<m_pLoopIf> loop_if
%type<m_pElseIfList> elseif_list
%type<m_pElseIf> elseif

%type<m_pWhenList> when_list
%type<m_pWhen> when
%type<m_pSwitchBlock> switch_block

%type<m_eExpressionType> assign_symbol
%type<m_pFunctionHeader> function_header function_operator_header

%type<m_pHashPair> hash_pair
%type<m_pHashPairList> hash_pair_list

%%
translation_unit
	: statement {
		IrisInterpreter::CurInstance()->AddStatement($1);
	}
	| translation_unit statement {
		IrisInterpreter::CurInstance()->AddStatement($2);
	}
	;

statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| function_statement
	| return_statement
	| if_statement
	| break_statement
	| continue_statement
	| switch_statement
	| module_statement
	| class_statement
	| interface_statement
	| for_statement
	| order_statement
	| groan_statement
	;
/*class_statement*/

class_statement
	: CLASS IDENTIFIER extends_field module_field interface_field class_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ClassStatement;
		pStatement->m_uType.m_pClassStatement = new IrisClassStatement($2, $3, $4, $5, $6);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
class_block
	: LC RC {
		$$ = nullptr;
	}
	| LC class_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
class_involve_statement_list
	: class_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| class_involve_statement_list class_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
class_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		$$ = pStatement;
	}
	| switch_statement
	| module_statement
	| function_statement
	| function_operator_statement
	| if_statement
	| getter_statement
	| setter_statement
	| getter_setter_statement
	| class_everyone_statement
	| class_relative_statement
	| class_personal_statement
	| for_statement
	| order_statement
	| groan_statement
	;
	
extends_field
	: {
		$$ = nullptr;
	}
	| EXTENDS identifier_with_field {
		$$ = $2;
	} 
	| EXTENDS IDENTIFIER {
		$$ = IrisExpression::CreateFieldExpression(nullptr, $2, false);
	}
	;

interface_field
	: {
		$$ = nullptr;
	}
	| JOINTS field_identifier_list {
		$$ = $2;
	}
	;
	
module_field
	: {
		$$ = nullptr;
	}
	| INVOLVES field_identifier_list {
		$$ = $2;
	}
	;

field_identifier_list
	: IDENTIFIER {
		IrisList<IrisExpression*>* pList = new IrisList<IrisExpression*>();
		pList->Add(IrisExpression::CreateFieldExpression(nullptr, $1, false));
		$$ = pList;		
	}
	| identifier_with_field {
		IrisList<IrisExpression*>* pList = new IrisList<IrisExpression*>();
		pList->Add($1);
		$$ = pList;
	}
	| field_identifier_list COMMA IDENTIFIER {
		$1->Add(IrisExpression::CreateFieldExpression(nullptr, $3, false));
		$$ = $1;
	}
	| field_identifier_list COMMA identifier_with_field {
		$1->Add($3);
		$$ = $1;		
	}
	;
	
/*getter_statement*/
getter_statement
	: SEMICOLON GET LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GetterStatement;
		pStatement->m_uType.m_pGetterStatement = new IrisGetterStatement($4, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| GET LB IDENTIFIER RB LP RP block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GetterStatement;
		pStatement->m_uType.m_pGetterStatement = new IrisGetterStatement($3, $7);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

/*setter_statement*/
setter_statement
	: SEMICOLON SET LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SetterStatement;
		pStatement->m_uType.m_pSetterStatement = new IrisSetterStatement($4, nullptr, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SET LB IDENTIFIER RB LP IDENTIFIER RP block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SetterStatement;
		pStatement->m_uType.m_pSetterStatement = new IrisSetterStatement($3, $6, $8);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

/*getter_setter_statement*/
getter_setter_statement
	: SEMICOLON GSET LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GSetterStatement;
		pStatement->m_uType.m_pGSetterStatement = new IrisGSetterStatement($4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*everyone_statement*/
class_everyone_statement
	: SEMICOLON EVERYONE LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON EVERYONE LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}

/*relative_statement*/
class_relative_statement
	: SEMICOLON RELATIVE LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON RELATIVE LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}

/*personal_statement*/
class_personal_statement
	: SEMICOLON PERSONAL LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON PERSONAL LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	
/*interface_statement*/
interface_statement
	: INTERFACE IDENTIFIER interface_field interface_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceStatement;
		pStatement->m_uType.m_pInterfaceStatement = new IrisInterfaceStatement($2, $3, $4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
		
interface_block
	: LC RC {
		$$ = nullptr;
	}
	| LC interface_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
interface_involve_statement_list
	: interface_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| interface_involve_statement_list interface_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
interface_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| if_statement
	| interface_func_statement
	| for_statement
	| order_statement
	| groan_statement
	;
	
/*module_statement*/
module_statement
	: MODULE IDENTIFIER module_field module_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ModuleStatement;
		pStatement->m_uType.m_pModuleStatement = new IrisModuleStatement($2, $3, nullptr, $4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
module_block
	: LC RC {
		$$ = nullptr;
	}
	| LC module_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
module_involve_statement_list
	: module_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| module_involve_statement_list module_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
module_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| module_statement
	| function_statement
	| if_statement
	| class_statement
	| module_everyone_statement
	| module_relative_statement
	| module_personal_statement
	| interface_statement
	| for_statement
	| order_statement
	| groan_statement
	;
	
/*everyone_statement*/
module_everyone_statement
	: SEMICOLON EVERYONE LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON EVERYONE LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}

/*relative_statement*/
module_relative_statement
	: SEMICOLON RELATIVE LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON RELATIVE LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}

/*personal_statement*/
module_personal_statement
	: SEMICOLON PERSONAL LB IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($4);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON PERSONAL LB SELF DOT IDENTIFIER RB {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement($6);
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	
/*function_statement*/
function_statement
	: function_header function_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement($1, nullptr, nullptr, $2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| function_header function_block WITH with_without_block WITHOUT with_without_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement($1, $4, $6, $2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

function_block
	: LC RC {
		$$ = nullptr;
	}
	| LC function_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
function_involve_statement_list
	: function_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| function_involve_statement_list function_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
function_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| if_statement
	| class_statement
	| for_statement
	| order_statement
	| groan_statement
	| return_statement
	| block_statement
	| super_statement
	;
	
with_without_block
	: LC RC {
		$$ = nullptr;
	}
	| LC with_without_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
with_without_involve_statement_list
	: with_without_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| with_without_involve_statement_list with_without_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
with_without_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| if_statement
	| class_statement
	| for_statement
	| order_statement
	| groan_statement
	| return_statement
	| cast_statement
	;

function_header
	: FUNCTION IDENTIFIER LP RP {
		$$ = new IrisFunctionHeader($2, nullptr, nullptr, false);
	}
	| FUNCTION IDENTIFIER LP identifier_list RP {
		$$ = new IrisFunctionHeader($2, $4, nullptr, false);
	}
	| FUNCTION IDENTIFIER LP identifier_list COMMA MUL IDENTIFIER RP {
		$$ = new IrisFunctionHeader($2, $4, $7, false);
	}
	| FUNCTION IDENTIFIER LP MUL IDENTIFIER RP {
		$$ = new IrisFunctionHeader($2, nullptr, $5, false);
	}
	| FUNCTION SELF DOT IDENTIFIER LP RP {
		$$ = new IrisFunctionHeader($4, nullptr, nullptr, true);
	}
	| FUNCTION SELF DOT IDENTIFIER LP identifier_list RP {
		$$ = new IrisFunctionHeader($4, $6, nullptr, true);
	}
	| FUNCTION SELF DOT IDENTIFIER LP identifier_list COMMA MUL IDENTIFIER RP {
		$$ = new IrisFunctionHeader($4, $6, $9, true);
	}
	| FUNCTION SELF DOT IDENTIFIER LP MUL IDENTIFIER RP {
		$$ = new IrisFunctionHeader($4, nullptr, $7, true);
	}
	;
	
function_operator_statement
	: function_operator_header function_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement($1, nullptr, nullptr, $2);
		$$ = pStatement;
	}
	;
	
function_operator_header
	: FUNCTION operator LP RP {
		$$ = new IrisFunctionHeader($2, nullptr, nullptr, false);
	}
	| FUNCTION operator LP identifier_list RP {
		$$ = new IrisFunctionHeader($2, $4, nullptr, false);
	}
	;
/*
	| FUNCTION operator LP identifier_list COMMA MUL IDENTIFIER RP {
		$$ = new IrisFunctionHeader($2, $4, $7, false);
	}
*/
	
operator
	: LB RB {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "[]");
	}
	| LB RB ASSIGN {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "[]=");
	}
	| LOGICAL_AND {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "+");
	}
	| LOGICAL_OR {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "||");
	}
	| LOGICAL_NOT {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!");
	}
	| EQ {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "==");
	}
	| NE {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!=");
	}
	| GT {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">");
	}
	| GE {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">=");
	}
	| LT {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<");
	}
	| LE {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<=");
	}
	| ADD {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "+");
	}
	| SUB {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "-");
	}
	| MUL {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "*");
	}
	| DIV {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "/");
	}
	| MOD {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "%");
	}
	| POWER {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "**");
	}
	| BIT_AND {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "&");
	}
	| BIT_OR {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "|");
	}
	| BIT_XOR {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "^");
	}
	| BIT_NOT {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!");
	}
	| BIT_SHR {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">>");
	}
	| BIT_SHL {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<<");
	}
	| BIT_SAR {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">>>");
	}
	| BIT_SAL {
		$$ = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<<<");
	}
	;
	
/*if_statement*/
if_statement
	: condition_if {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::IfStatement;
		pStatement->m_uType.m_pIfStatement = new IrisIfStatement($1);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| loop_if {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::IfStatement;
		pStatement->m_uType.m_pIfStatement = new IrisIfStatement($1);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

condition_if
	: IF LP expression RP block {
		IrisConditionIf* pConditionIf = new IrisConditionIf($3, $5, nullptr, nullptr);
		$$ = pConditionIf;
	}
	| IF LP expression RP block ELSE block {
		IrisConditionIf* pConditionIf = new IrisConditionIf($3, $5, nullptr, $7);
		$$ = pConditionIf;
	}
	
	| IF LP expression RP block elseif_list {
		IrisConditionIf* pConditionIf = new IrisConditionIf($3, $5, $6, nullptr);
		$$ = pConditionIf;
	}
	| IF LP expression RP block elseif_list ELSE block {
		IrisConditionIf* pConditionIf = new IrisConditionIf($3, $5, $6, $8);
		$$ = pConditionIf;
	}
	;

elseif_list
	: elseif {
		IrisList<IrisElseIf*>* pElseIfList = new IrisList<IrisElseIf*>();
		pElseIfList->Add($1);
		$$ = pElseIfList;
	}
	| elseif_list elseif {
		$1->Add($2);
		$$ = $1;
	}
	;

elseif
	: ELSEIF LP expression RP block {
		IrisElseIf* pElseIf = new IrisElseIf($3, $5);
		$$ = pElseIf;
	}
	;
	
loop_if
	: IF LP expression COMMA expression loop_time RP block {
		IrisLoopIf* pLoopIf = new IrisLoopIf($3, $5, $6, $8);
		$$ = pLoopIf;
	}
	;
	
loop_time
	: {
		$$ = nullptr;
	}
	| COMMA IDENTIFIER {
		$$ = $2;
	}
	;
	
/*switch_statement*/
switch_statement
	: SWITCH LP expression RP switch_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SwitchStatement;
		pStatement->m_uType.m_pSwitchStatement = new IrisSwitchStatement($3, $5);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
switch_block
	: LC when_list RC {
		IrisSwitchBlock* pSwitchBlock = new IrisSwitchBlock($2, nullptr);
		$$ = pSwitchBlock;
	}
	| LC when_list ELSE block RC {
		IrisSwitchBlock* pSwitchBlock = new IrisSwitchBlock($2, $4);
		$$ = pSwitchBlock;		
	}
	;
	
when_list
	: when {
		IrisList<IrisWhen*>* pWhenList = new IrisList<IrisWhen*>();
		pWhenList->Add($1);
		$$ = pWhenList;
	}
	| when_list when {
		$1->Add($2);
		$$ = $1;
	}
	;
	
when
	: WHEN LP expression_list RP block {
		IrisWhen* pWhen = new IrisWhen($3, $5);
		$$ = pWhen;
	}
	;

/*for_statement*/
for_statement
	: FOR LP IDENTIFIER IN expression RP block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ForStatement;
		pStatement->m_uType.m_pForStatement = new IrisForStatement($3, nullptr, $5, $7);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| FOR LP LP IDENTIFIER COMMA IDENTIFIER RP IN expression RP block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ForStatement;
		pStatement->m_uType.m_pForStatement = new IrisForStatement($4, $6, $9, $11);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*order_statement*/
order_statement
	: ORDER block SERVE LP IDENTIFIER RP order_block ignore_block {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::OrderStatement;
		pStatement->m_uType.m_pOrderStatement = new IrisOrderStatement($2, $5, $7, $8);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

order_block
	: LC RC {
		$$ = nullptr;
	}
	| LC order_involve_statement_list RC {
		$$ = new IrisBlock($2);
	}
	;
	
order_involve_statement_list
	: order_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| order_involve_statement_list order_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
order_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| module_statement
	| function_statement
	| if_statement
	| for_statement
	| order_statement
	| groan_statement
	;

	
ignore_block
	: {
		$$ = nullptr;
	}
	| IGNORE LC order_involve_statement_list RC {
		$$ = new IrisBlock($3);;
	}
	;

	
/*return_statement*/
return_statement
	: SEMICOLON RETURN {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ReturnStatement;
		pStatement->m_uType.m_pReturnStatement = new IrisReturnStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON RETURN expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ReturnStatement;
		pStatement->m_uType.m_pReturnStatement = new IrisReturnStatement($3);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*break_statement*/
break_statement
	: SEMICOLON BREAK  {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::BreakStatement;
		pStatement->m_uType.m_pBreakStatement = new IrisBreakStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}

/*continue_statement*/
continue_statement
	: SEMICOLON CONTINUE {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ContinueStatement;
		pStatement->m_uType.m_pContinueStatement = new IrisContinueStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

/*interface_func_statement*/
interface_func_statement
	: SEMICOLON FUNCTION IDENTIFIER LP RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement($3, nullptr, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON FUNCTION IDENTIFIER LP identifier_list RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement($3, $5, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON FUNCTION IDENTIFIER LP identifier_list COMMA MUL IDENTIFIER RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement($3, $5, $8);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON FUNCTION IDENTIFIER LP MUL IDENTIFIER RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement($3, nullptr, $6);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;

/*groan_statement*/
groan_statement
	: SEMICOLON GROAN LP expression RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GroanStatement;
		pStatement->m_uType.m_pGroanStatement = new IrisGroanStatement($4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*block_statement*/
block_statement
	: SEMICOLON BLOCK {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::BlockStatement;
		pStatement->m_uType.m_pBlockStatement = new IrisBlockStatement();
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*cast_statement*/
cast_statement
	: SEMICOLON CAST LP RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::CastStatement;
		pStatement->m_uType.m_pCastStatement = new IrisCastStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON CAST LP expression_list RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::CastStatement;
		pStatement->m_uType.m_pCastStatement = new IrisCastStatement($4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	;
	
/*super_statement*/
super_statement
	: SEMICOLON SUPER LP RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SuperStatement;
		pStatement->m_uType.m_pSuperStatement = new IrisSuperStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| SEMICOLON SUPER LP expression_list RP {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SuperStatement;
		pStatement->m_uType.m_pSuperStatement = new IrisSuperStatement($4);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;	
	}
	
/*block*/
block
	: LC RC {
		IrisBlock* pBlock = new IrisBlock(nullptr);
		$$ = pBlock;
	}
	| LC statement_list RC {
		IrisBlock* pBlock = new IrisBlock($2);
		$$ = pBlock;		
	}
	
statement_list
	: statement {
		IrisList<IrisStatement*>* pStatementList = new IrisList<IrisStatement*>();
		pStatementList->Add($1);
		$$ = pStatementList;
	}
	| statement_list statement {
		$1->Add($2);
		$$ = $1;
	}
	;

/*expression*/	
expression
	: logic_or_expression
	| top_expression assign_symbol expression {
		$$ = IrisExpression::CreateBinaryExpression($2, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

assign_symbol
	: ASSIGN {
		$$ = IrisExpression::ExpressionType::Assign;
	}
	| ASSIGN_ADD {
		$$ = IrisExpression::ExpressionType::AssignAdd;
	}
	| ASSIGN_SUB {
		$$ = IrisExpression::ExpressionType::AssignSub;
	}
	| ASSIGN_MUL {
		$$ = IrisExpression::ExpressionType::AssignMul;
	}
	| ASSIGN_DIV {
		$$ = IrisExpression::ExpressionType::AssignDiv;
	}
	| ASSIGN_MOD {
		$$ = IrisExpression::ExpressionType::AssignMod;
	}
	| ASSIGN_BIT_AND {
		$$ = IrisExpression::ExpressionType::AssignBitAnd;
	}
	| ASSIGN_BIT_OR {
		$$ = IrisExpression::ExpressionType::AssignBitOr;
	}
	| ASSIGN_BIT_XOR {
		$$ = IrisExpression::ExpressionType::AssignBitXor;
	}
	| ASSIGN_BIT_SHR {
		$$ = IrisExpression::ExpressionType::AssignBitShr;
	}
	| ASSIGN_BIT_SHL {
		$$ = IrisExpression::ExpressionType::AssignBitShl;
	}
	| ASSIGN_BIT_SAR {
		$$ = IrisExpression::ExpressionType::AssignBitSar;
	}
	| ASSIGN_BIT_SAL {
		$$ = IrisExpression::ExpressionType::AssignBitSal;
	}
	;

logic_or_expression
	: logic_and_expression
	| logic_or_expression LOGICAL_OR logic_and_expression {
		$$ =  IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicOr, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
logic_and_expression
	: logic_bit_or_expression
	| logic_and_expression LOGICAL_AND logic_bit_or_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicAnd, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

logic_bit_or_expression
	: logic_bit_xor_expression
	| logic_bit_or_expression BIT_OR logic_bit_xor_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitOr, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

logic_bit_xor_expression
	: logic_bit_and_expression
	| logic_bit_xor_expression BIT_XOR logic_bit_and_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitXor, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
logic_bit_and_expression
	: logic_equal_compare_expression
	| logic_bit_and_expression BIT_AND logic_equal_compare_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitAnd, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

logic_equal_compare_expression
	: logic_not_equal_expression
	| logic_equal_compare_expression EQ logic_not_equal_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Equal, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_equal_compare_expression NE logic_not_equal_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::NotEqual, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

logic_not_equal_expression
	: logic_shift_expression
	| logic_not_equal_expression GT logic_shift_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::GreatThan, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_not_equal_expression GE logic_shift_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::GreatThanOrEqual, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_not_equal_expression LT logic_shift_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LessThan, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_not_equal_expression LE logic_shift_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LessThanOrEqual, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
logic_shift_expression
	: add_sub_expression
	| logic_shift_expression BIT_SHR add_sub_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitShr, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_shift_expression BIT_SHL add_sub_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitShl, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_shift_expression BIT_SAR add_sub_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitSar, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| logic_shift_expression BIT_SAL add_sub_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitSal, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	} 
	;
	
add_sub_expression
	: mul_div_mod_expression
	| add_sub_expression ADD mul_div_mod_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Add, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| add_sub_expression SUB mul_div_mod_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Sub, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
mul_div_mod_expression
	: power_expression
	| mul_div_mod_expression MUL power_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Mul, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| mul_div_mod_expression DIV power_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Div, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| mul_div_mod_expression MOD power_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Mod, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;

power_expression
	: unary_expression
	| power_expression POWER unary_expression {
		$$ = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Power, $1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	} 
	;

unary_expression
	: top_expression
	| LOGICAL_NOT unary_expression {
		$$ = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::LogicNot, $2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| BIT_NOT unary_expression {
		$$ = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::BitNot, $2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| SUB unary_expression {
		$$ = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::Minus, $2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| ADD unary_expression {
		$$ = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::Plus, $2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
top_expression
	: primary_expression
	| top_expression LB expression RB {
		$$ = IrisExpression::CreateIndexExpression($1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| top_expression DOT IDENTIFIER LP RP closure_block {
		$$ = IrisExpression::CreateFunctionCallExpression($1, $3, nullptr, $6);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| top_expression DOT IDENTIFIER LP expression_list RP closure_block {
		$$ = IrisExpression::CreateFunctionCallExpression($1, $3, $5, $7);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| SELF DOT IDENTIFIER LP RP closure_block {
		$$ = IrisExpression::CreateSelfFunctionCallExpression($3, nullptr, $6);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| SELF DOT IDENTIFIER LP expression_list RP closure_block {
		$$ = IrisExpression::CreateSelfFunctionCallExpression($3, $5, $7);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| IDENTIFIER LP RP closure_block {
		$$ = IrisExpression::CreateFunctionCallExpression(nullptr, $1, nullptr, $4);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| IDENTIFIER LP expression_list RP closure_block {
		$$ = IrisExpression::CreateFunctionCallExpression(nullptr, $1, $3, $5);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| top_expression DOT IDENTIFIER {
		$$ = IrisExpression::CreateMemberExpression($1, $3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| SELF DOT IDENTIFIER {
		$$ = IrisExpression::CreateSelfMemberExpression($3);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
closure_block
	: {
		$$ = nullptr;
	}
	| LC RC {
		$$ = nullptr;
	}
	| LC closure_involve_statement_list RC {
		$$ = new IrisClosureBlockLiteral(nullptr, $2);
	}
	| LC ITERATOR ITER LB identifier_list RB CONLON closure_involve_statement_list RC {
		$$ = new IrisClosureBlockLiteral($5, $8);
	}
	;
	
closure_involve_statement_list
	: closure_involve_statement {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add($1);
		$$ = pList;
	}
	| closure_involve_statement_list closure_involve_statement {
		$1->Add($2);
		$$ = $1;
	}
	;
	
closure_involve_statement
	: SEMICOLON expression {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement($2);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		$$ = pStatement;
	}
	| switch_statement
	| module_statement
	| function_statement
	| if_statement
	| for_statement
	| order_statement
	| groan_statement
	;
	
primary_expression
	: identifier_with_field
	| LP expression RP {
		$$ = $2;
	}
	| IDENTIFIER {
		$$ = IrisExpression::CreateIdentifierExpression($1);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| INTEGER {
		$$ = $1;
	}
	| FLOAT {
		$$ = $1;
	}
	| STRING {
		$$ = $1;
	}
	| TRUE {
		$$ = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::True);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| FALSE {
		$$ = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::False);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| NIL {
		$$ = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::Nil);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| array_literal
	| hash_literal
	;

identifier_with_field
	: field_identifier IDENTIFIER {
		$$ = IrisExpression::CreateFieldExpression($1, $2, false);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| FILED field_identifier IDENTIFIER {
		$$ = IrisExpression::CreateFieldExpression($2, $3, true);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	| FILED IDENTIFIER {
		$$ = IrisExpression::CreateFieldExpression(nullptr, $2, true);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
	;
	
array_literal
	: LB RB {
		$$ = IrisExpression::CreateArrayExpression(nullptr);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    | LB expression_list RB {
        $$ = IrisExpression::CreateArrayExpression($2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    | LB expression_list COMMA RB {
        $$ = IrisExpression::CreateArrayExpression($2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    ;
	
	
field_identifier
	: IDENTIFIER FILED {
		IrisList<IrisIdentifier*>* pFieldIdentifier = new IrisList<IrisIdentifier*>();
		pFieldIdentifier->Add($1);
		$$ = pFieldIdentifier;
	}
	| field_identifier IDENTIFIER FILED {
		$1->Add($2);
		$$ = $1;
	}
	;

	
identifier_list
	: IDENTIFIER {
		IrisList<IrisIdentifier*>* pList = new IrisList<IrisIdentifier*>();
		pList->Add($1);
		$$ = pList;
	}
	| identifier_list COMMA IDENTIFIER {
		$1->Add($3);
		$$ = $1;
	}
	;

expression_list
	: expression {
		IrisList<IrisExpression*>* pExpressionList = new IrisList<IrisExpression*>();
		pExpressionList->Add($1);
		$$ = pExpressionList;
	}
	| expression_list COMMA expression {
		$1->Add($3);
		$$ = $1;
	}
	;

hash_literal
	: LC RC {
		$$ = IrisExpression::CreateHashExpression(nullptr);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    | LC hash_pair_list RC {
        $$ = IrisExpression::CreateHashExpression($2);
		$$->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    | LC hash_pair_list expression ITER expression RC {
		$2->Add(new IrisHashPair($3, $5));
        $$ = IrisExpression::CreateHashExpression($2);
    }
    ;
	
hash_pair_list
	: hash_pair {
		IrisList<IrisHashPair*>* pHashPairList = new IrisList<IrisHashPair*>();
		pHashPairList->Add($1);
		$$ = pHashPairList;
	}
	| hash_pair_list hash_pair {
		$1->Add($2);
		$$ = $1;
	}
	
hash_pair
	: expression ITER expression COMMA {
		$$ = new IrisHashPair($1, $3);
	}
%%