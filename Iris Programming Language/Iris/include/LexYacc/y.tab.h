/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT = 259,
     STRING = 260,
     IDENTIFIER = 261,
     FUNCTION = 262,
     CLASS = 263,
     MODULE = 264,
     INTERFACE = 265,
     EXTENDS = 266,
     INVOLVES = 267,
     JOINTS = 268,
     PERSONAL = 269,
     RELATIVE = 270,
     EVERYONE = 271,
     GET = 272,
     SET = 273,
     GSET = 274,
     IF = 275,
     ELSE = 276,
     ELSEIF = 277,
     FOR = 278,
     IN = 279,
     SWITCH = 280,
     WHEN = 281,
     CAST = 282,
     ITERATOR = 283,
     SUPER = 284,
     BREAK = 285,
     CONTINUE = 286,
     RETURN = 287,
     BLOCK = 288,
     SELF = 289,
     WITH = 290,
     WITHOUT = 291,
     ORDER = 292,
     SERVE = 293,
     IGNORE = 294,
     GROAN = 295,
     TRUE = 296,
     FALSE = 297,
     NIL = 298,
     DOT = 299,
     ALIAS = 300,
     RETRY = 301,
     REDO = 302,
     GOTO = 303,
     CONST = 304,
     GLOBAL = 305,
     STATIC = 306,
     LP = 307,
     RP = 308,
     LC = 309,
     RC = 310,
     LB = 311,
     RB = 312,
     SEMICOLON = 313,
     COMMA = 314,
     LOGICAL_AND = 315,
     LOGICAL_OR = 316,
     LOGICAL_NOT = 317,
     ASSIGN = 318,
     ADD = 319,
     SUB = 320,
     MUL = 321,
     DIV = 322,
     MOD = 323,
     POWER = 324,
     BIT_AND = 325,
     BIT_OR = 326,
     BIT_XOR = 327,
     BIT_NOT = 328,
     ASSIGN_ADD = 329,
     ASSIGN_SUB = 330,
     ASSIGN_MUL = 331,
     ASSIGN_DIV = 332,
     ASSIGN_MOD = 333,
     ASSIGN_BIT_AND = 334,
     ASSIGN_BIT_OR = 335,
     ASSIGN_BIT_XOR = 336,
     BIT_SHR = 337,
     EQ = 338,
     NE = 339,
     GT = 340,
     GE = 341,
     LT = 342,
     LE = 343,
     BIT_SHL = 344,
     BIT_SAR = 345,
     BIT_SAL = 346,
     ASSIGN_BIT_SHR = 347,
     ASSIGN_BIT_SHL = 348,
     ASSIGN_BIT_SAR = 349,
     ASSIGN_BIT_SAL = 350,
     ITER = 351,
     FILED = 352,
     SHARP = 353,
     CONLON = 354
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOAT 259
#define STRING 260
#define IDENTIFIER 261
#define FUNCTION 262
#define CLASS 263
#define MODULE 264
#define INTERFACE 265
#define EXTENDS 266
#define INVOLVES 267
#define JOINTS 268
#define PERSONAL 269
#define RELATIVE 270
#define EVERYONE 271
#define GET 272
#define SET 273
#define GSET 274
#define IF 275
#define ELSE 276
#define ELSEIF 277
#define FOR 278
#define IN 279
#define SWITCH 280
#define WHEN 281
#define CAST 282
#define ITERATOR 283
#define SUPER 284
#define BREAK 285
#define CONTINUE 286
#define RETURN 287
#define BLOCK 288
#define SELF 289
#define WITH 290
#define WITHOUT 291
#define ORDER 292
#define SERVE 293
#define IGNORE 294
#define GROAN 295
#define TRUE 296
#define FALSE 297
#define NIL 298
#define DOT 299
#define ALIAS 300
#define RETRY 301
#define REDO 302
#define GOTO 303
#define CONST 304
#define GLOBAL 305
#define STATIC 306
#define LP 307
#define RP 308
#define LC 309
#define RC 310
#define LB 311
#define RB 312
#define SEMICOLON 313
#define COMMA 314
#define LOGICAL_AND 315
#define LOGICAL_OR 316
#define LOGICAL_NOT 317
#define ASSIGN 318
#define ADD 319
#define SUB 320
#define MUL 321
#define DIV 322
#define MOD 323
#define POWER 324
#define BIT_AND 325
#define BIT_OR 326
#define BIT_XOR 327
#define BIT_NOT 328
#define ASSIGN_ADD 329
#define ASSIGN_SUB 330
#define ASSIGN_MUL 331
#define ASSIGN_DIV 332
#define ASSIGN_MOD 333
#define ASSIGN_BIT_AND 334
#define ASSIGN_BIT_OR 335
#define ASSIGN_BIT_XOR 336
#define BIT_SHR 337
#define EQ 338
#define NE 339
#define GT 340
#define GE 341
#define LT 342
#define LE 343
#define BIT_SHL 344
#define BIT_SAR 345
#define BIT_SAL 346
#define ASSIGN_BIT_SHR 347
#define ASSIGN_BIT_SHL 348
#define ASSIGN_BIT_SAR 349
#define ASSIGN_BIT_SAL 350
#define ITER 351
#define FILED 352
#define SHARP 353
#define CONLON 354



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 27 "iris.y"

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


/* Line 2058 of yacc.c  */
#line 278 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
