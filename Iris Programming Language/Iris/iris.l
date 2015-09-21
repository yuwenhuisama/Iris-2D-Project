%{
#include "Iris.h"
#include "y.tab.h"

extern char* g_pCurrentString;
extern int g_nCurrentStringLength;
extern int g_nReadLength;

extern "C" int yywrap(void) {
    return 1;
}

extern "C" int StringRead(char* pBuffer, int nMaxToRead) {
	int nLengthToRead = g_nCurrentStringLength - g_nReadLength > nMaxToRead ? nMaxToRead : g_nCurrentStringLength - g_nReadLength;
	
	for(int i = 0; i < nLengthToRead; ++i) {
		pBuffer[i] = g_pCurrentString[g_nReadLength + i];
	}
	
	g_nReadLength += nLengthToRead;
	return nLengthToRead;
}

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) result = StringRead(buf, max_size);

%}
%start MULTIPLE_LINE_COMMENT_STATE SINGLE_LINE_COMMENT_STATE STRING_LITERAL_STATE
%%
<INITIAL>"fun"		return FUNCTION;
<INITIAL>"class"	return CLASS;
<INITIAL>"module"	return MODULE;
<INITIAL>"interface"	return INTERFACE;
<INITIAL>"extends"	return EXTENDS;
<INITIAL>"involves" return INVOLVES;
<INITIAL>"joints"	return JOINTS;
<INITIAL>"personal"	return PERSONAL;
<INITIAL>"relative"	return RELATIVE;
<INITIAL>"everyone"	return EVERYONE;
<INITIAL>"get"		return GET;
<INITIAL>"set"		return SET;
<INITIAL>"gset"		return GSET;
<INITIAL>"if"		return IF;
<INITIAL>"else"		return ELSE;
<INITIAL>"elseif"	return ELSEIF;
<INITIAL>"for"		return FOR;
<INITIAL>"in"		return IN;
<INITIAL>"switch"	return SWITCH;
<INITIAL>"when"		return WHEN;
<INITIAL>"cast"		return CAST;
<INITIAL>"iterator"	return ITERATOR;
<INITIAL>"super"	return SUPER;
<INITIAL>"break"	return BREAK;
<INITIAL>"continue"	return CONTINUE;
<INITIAL>"return"	return RETURN;
<INITIAL>"block"	return BLOCK;
<INITIAL>"self"		return SELF;
<INITIAL>"with"		return WITH;
<INITIAL>"without"	return WITHOUT;
<INITIAL>"order"	return ORDER;
<INITIAL>"serve"	return SERVE;
<INITIAL>"ignore"	return IGNORE;
<INITIAL>"groan"	return GROAN;
<INITIAL>"true"		return TRUE;
<INITIAL>"false"	return FALSE;
<INITIAL>"nil"		return NIL;

<INITIAL>"alias"	return ALIAS;
<INITIAL>"retry"	return RETRY;
<INITIAL>"redo"		return REDO;
<INITIAL>"goto"		return GOTO;
<INITIAL>"const"	return CONST;
<INITIAL>"global"	return GLOBAL;
<INITIAL>"static"	return STATIC;

<INITIAL>"."		return DOT;
<INITIAL>"("        return LP;
<INITIAL>")"        return RP;
<INITIAL>"{"        return LC;
<INITIAL>"}"        return RC;
<INITIAL>"["        return LB;
<INITIAL>"]"        return RB;
<INITIAL>";"        return SEMICOLON;
<INITIAL>","        return COMMA;
<INITIAL>"&&"       return LOGICAL_AND;
<INITIAL>"||"       return LOGICAL_OR;
<INITIAL>"!"		return LOGICAL_NOT;
<INITIAL>"="        return ASSIGN;
<INITIAL>"=="       return EQ;
<INITIAL>"!="       return NE;
<INITIAL>">"        return GT;
<INITIAL>">="       return GE;
<INITIAL>"<"        return LT;
<INITIAL>"<="       return LE;
<INITIAL>"+"        return ADD;
<INITIAL>"-"        return SUB;
<INITIAL>"*"        return MUL;
<INITIAL>"/"        return DIV;
<INITIAL>"%"        return MOD;
<INITIAL>"**"		return POWER;
<INITIAL>"&"		return BIT_AND;
<INITIAL>"|"		return BIT_OR;
<INITIAL>"^"		return BIT_XOR;
<INITIAL>"~"		return BIT_NOT;
<INITIAL>"+="		return ASSIGN_ADD;
<INITIAL>"-="		return ASSIGN_SUB;
<INITIAL>"*="		return ASSIGN_MUL;
<INITIAL>"/="		return ASSIGN_DIV;
<INITIAL>"%="		return ASSIGN_MOD;
<INITIAL>"&="		return ASSIGN_BIT_AND;
<INITIAL>"|="		return ASSIGN_BIT_OR;
<INITIAL>"^="		return ASSIGN_BIT_XOR;
<INITIAL>">>"		return BIT_SHR;
<INITIAL>"<<"		return BIT_SHL;
<INITIAL>">>>"		return BIT_SAR;
<INITIAL>"<<<"		return BIT_SAL;
<INITIAL>">>="		return ASSIGN_BIT_SHR;
<INITIAL>"<<="		return ASSIGN_BIT_SHL;
<INITIAL>">>>="		return ASSIGN_BIT_SAR;
<INITIAL>"<<<="		return ASSIGN_BIT_SAL;
<INITIAL>"=>"		return ITER;
<INITIAL>"::"		return FILED;
<INITIAL>"#"		return SHARP;
<INITIAL>":"		return CONLON;

<INITIAL>[A-Z][_A-Za-z0-9]* {
	//标识符-常量
	yylval.m_pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::Constance, yytext);
	return IDENTIFIER;	
}
<INITIAL>[_a-z][_a-zA-Z0-9]* {
	// 标识符-局部变量
	yylval.m_pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::LocalVariable, yytext);
	return IDENTIFIER;
}
<INITIAL>\$[_a-zA-Z][_a-zA-Z0-9]* {
	// 标识符-全局变量
	yylval.m_pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, yytext);
	return IDENTIFIER;
}
<INITIAL>@[_a-zA-Z][_a-zA-Z0-9]* {
	// 标识符-实例变量
	yylval.m_pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::InstanceVariable, yytext);
	return IDENTIFIER;
}
<INITIAL>@@[_a-zA-Z][_a-zA-Z0-9]* {
	// 标识符-类变量
	yylval.m_pIdentifier = new IrisIdentifier(IrisIdentifier::IdentifilerType::ClassVariable, yytext);
	return IDENTIFIER;
}

<INITIAL>((\+|-)?[1-9][0-9]*)|"0"|"+0"|"-0" {
	//整数
	IrisExpression* pExpression = IrisExpression::CreateNativeObjectExpression(IrisExpression::ExpressionType::Integer,
			IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstanceFromLiteral(yytext).GetObject());
	yylval.m_pExpression = pExpression;
	return INTEGER;
}

<INITIAL>((\+|-)?[0-9]+\.[0-9]*) {
	//浮点数
	IrisExpression* pExpression = IrisExpression::CreateNativeObjectExpression(IrisExpression::ExpressionType::Float,
			IrisInterpreter::CurInstance()->GetIrisClass("Float")->CreateInstanceFromLiteral(yytext).GetObject());
	yylval.m_pExpression = pExpression;
	return FLOAT;
}

<INITIAL>\" {
	//开始字符串
	IrisInterpreter::CurInstance()->StartStringProcess();
	BEGIN STRING_LITERAL_STATE;
}

<INITIAL>[ \t] {;}
<INITIAL>\n {
	IrisInterpreter::CurInstance()->IncreamLineNumber();
}
<INITIAL>"//" {
	// 开始单行注释
	BEGIN SINGLE_LINE_COMMENT_STATE;
}
<INITIAL>"/*" {
	// 开始多行注释
	BEGIN MULTIPLE_LINE_COMMENT_STATE;
}

<INITIAL>. {
	// 错误处理
	//IrisInterpreter::CurInstance()->GroanIrregular(IrisInterpreter::CurInstance()->GetCurrentLineNumber(), new IrisSyntaxIrregular());
	//fprintf(stderr, "Grammar Error !\n");
	//exit(0);
	IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::SyntaxIrregular, IrisInterpreter::CurInstance()->GetCurrentLineNumber(), "");
}

<INITIAL><<EOF>> {
	return EOF;
}

<SINGLE_LINE_COMMENT_STATE>\n {
	// 结束单行注释
	IrisInterpreter::CurInstance()->IncreamLineNumber();
	BEGIN INITIAL;
}
<SINGLE_LINE_COMMENT_STATE>. ;

<SINGLE_LINE_COMMENT_STATE><<EOF>> {
	return EOF;
}

<MULTIPLE_LINE_COMMENT_STATE>"*/" {
	// 结束多行注释
	BEGIN INITIAL;
}
<MULTIPLE_LINE_COMMENT_STATE>\n {
	IrisInterpreter::CurInstance()->IncreamLineNumber();
}
<MULTIPLE_LINE_COMMENT_STATE>.	;

<MULTIPLE_LINE_COMMENT_STATE><<EOF>> {
	return EOF;
}

<STRING_LITERAL_STATE>\" {
	// 终止字符串
	IrisExpression* pExpression = IrisExpression::CreateNativeObjectExpression(IrisExpression::ExpressionType::String,
		IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(IrisInterpreter::CurInstance()->EndStringProcess()).GetObject());
	yylval.m_pExpression = pExpression;
	BEGIN INITIAL;
	return STRING;
}
<STRING_LITERAL_STATE>\n {
	IrisInterpreter::CurInstance()->AddStringChar('\n');
	IrisInterpreter::CurInstance()->IncreamLineNumber();
}
<STRING_LITERAL_STATE>\\\" {
	IrisInterpreter::CurInstance()->AddStringChar('"');
}
<STRING_LITERAL_STATE>\\t {
	IrisInterpreter::CurInstance()->AddStringChar('\t');
}
<STRING_LITERAL_STATE>\\n {
	IrisInterpreter::CurInstance()->AddStringChar('\n');
}
<STRING_LITERAL_STATE>\\ {
	IrisInterpreter::CurInstance()->AddStringChar('\\');
}
<STRING_LITERAL_STATE>. {
	IrisInterpreter::CurInstance()->AddStringChar(yytext[0]);
}
%%