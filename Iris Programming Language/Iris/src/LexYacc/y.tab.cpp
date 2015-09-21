/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "iris.y"

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

/* Line 371 of yacc.c  */
#line 94 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
/* Line 387 of yacc.c  */
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


/* Line 387 of yacc.c  */
#line 358 "y.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 386 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  317
/* YYNRULES -- Number of states.  */
#define YYNSTATES  577

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   354

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    42,    45,
      49,    51,    54,    57,    59,    61,    63,    65,    67,    69,
      71,    73,    75,    77,    79,    81,    83,    85,    86,    89,
      92,    93,    96,    97,   100,   102,   104,   108,   112,   118,
     126,   132,   141,   147,   153,   161,   167,   175,   181,   189,
     194,   197,   201,   203,   206,   209,   211,   213,   215,   217,
     219,   221,   226,   229,   233,   235,   238,   241,   243,   245,
     247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
     271,   279,   285,   293,   299,   307,   310,   317,   320,   324,
     326,   329,   332,   334,   336,   338,   340,   342,   344,   346,
     348,   350,   353,   357,   359,   362,   365,   367,   369,   371,
     373,   375,   377,   379,   381,   386,   392,   401,   408,   415,
     423,   434,   443,   446,   451,   457,   460,   464,   466,   468,
     470,   472,   474,   476,   478,   480,   482,   484,   486,   488,
     490,   492,   494,   496,   498,   500,   502,   504,   506,   508,
     510,   512,   514,   520,   528,   535,   544,   546,   549,   555,
     564,   565,   568,   574,   578,   584,   586,   589,   595,   603,
     615,   624,   627,   631,   633,   636,   639,   641,   643,   645,
     647,   649,   651,   653,   654,   659,   662,   666,   669,   672,
     678,   685,   695,   703,   709,   712,   717,   723,   728,   734,
     737,   741,   743,   746,   748,   752,   754,   756,   758,   760,
     762,   764,   766,   768,   770,   772,   774,   776,   778,   780,
     784,   786,   790,   792,   796,   798,   802,   804,   808,   810,
     814,   818,   820,   824,   828,   832,   836,   838,   842,   846,
     850,   854,   856,   860,   864,   866,   870,   874,   878,   880,
     884,   886,   889,   892,   895,   898,   900,   905,   912,   920,
     927,   935,   940,   946,   950,   954,   955,   958,   962,   972,
     974,   977,   980,   982,   984,   986,   988,   990,   992,   994,
     996,  1000,  1002,  1004,  1006,  1008,  1010,  1012,  1014,  1016,
    1018,  1021,  1025,  1028,  1031,  1035,  1040,  1043,  1047,  1049,
    1053,  1055,  1059,  1062,  1066,  1073,  1075,  1078
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     101,     0,    -1,   102,    -1,   101,   102,    -1,    58,   165,
      -1,   128,    -1,   155,    -1,   139,    -1,   156,    -1,   157,
      -1,   145,    -1,   121,    -1,   103,    -1,   117,    -1,   149,
      -1,   150,    -1,   159,    -1,     8,     6,   107,   109,   108,
     104,    -1,    54,    55,    -1,    54,   105,    55,    -1,   106,
      -1,   105,   106,    -1,    58,   165,    -1,   145,    -1,   121,
      -1,   128,    -1,   136,    -1,   139,    -1,   111,    -1,   112,
      -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,   149,
      -1,   150,    -1,   159,    -1,    -1,    11,   184,    -1,    11,
       6,    -1,    -1,    13,   110,    -1,    -1,    12,   110,    -1,
       6,    -1,   184,    -1,   110,    59,     6,    -1,   110,    59,
     184,    -1,    58,    17,    56,     6,    57,    -1,    17,    56,
       6,    57,    52,    53,   163,    -1,    58,    18,    56,     6,
      57,    -1,    18,    56,     6,    57,    52,     6,    53,   163,
      -1,    58,    19,    56,     6,    57,    -1,    58,    16,    56,
       6,    57,    -1,    58,    16,    56,    34,    44,     6,    57,
      -1,    58,    15,    56,     6,    57,    -1,    58,    15,    56,
      34,    44,     6,    57,    -1,    58,    14,    56,     6,    57,
      -1,    58,    14,    56,    34,    44,     6,    57,    -1,    10,
       6,   108,   118,    -1,    54,    55,    -1,    54,   119,    55,
      -1,   120,    -1,   119,   120,    -1,    58,   165,    -1,   145,
      -1,   139,    -1,   158,    -1,   149,    -1,   150,    -1,   159,
      -1,     9,     6,   109,   122,    -1,    54,    55,    -1,    54,
     123,    55,    -1,   124,    -1,   123,   124,    -1,    58,   165,
      -1,   145,    -1,   121,    -1,   128,    -1,   139,    -1,   103,
      -1,   125,    -1,   126,    -1,   127,    -1,   117,    -1,   149,
      -1,   150,    -1,   159,    -1,    58,    16,    56,     6,    57,
      -1,    58,    16,    56,    34,    44,     6,    57,    -1,    58,
      15,    56,     6,    57,    -1,    58,    15,    56,    34,    44,
       6,    57,    -1,    58,    14,    56,     6,    57,    -1,    58,
      14,    56,    34,    44,     6,    57,    -1,   135,   129,    -1,
     135,   129,    35,   132,    36,   132,    -1,    54,    55,    -1,
      54,   130,    55,    -1,   131,    -1,   130,   131,    -1,    58,
     165,    -1,   145,    -1,   139,    -1,   103,    -1,   149,    -1,
     150,    -1,   159,    -1,   155,    -1,   160,    -1,   162,    -1,
      54,    55,    -1,    54,   133,    55,    -1,   134,    -1,   133,
     134,    -1,    58,   165,    -1,   145,    -1,   139,    -1,   103,
      -1,   149,    -1,   150,    -1,   159,    -1,   155,    -1,   161,
      -1,     7,     6,    52,    53,    -1,     7,     6,    52,   187,
      53,    -1,     7,     6,    52,   187,    59,    66,     6,    53,
      -1,     7,     6,    52,    66,     6,    53,    -1,     7,    34,
      44,     6,    52,    53,    -1,     7,    34,    44,     6,    52,
     187,    53,    -1,     7,    34,    44,     6,    52,   187,    59,
      66,     6,    53,    -1,     7,    34,    44,     6,    52,    66,
       6,    53,    -1,   137,   129,    -1,     7,   138,    52,    53,
      -1,     7,   138,    52,   187,    53,    -1,    56,    57,    -1,
      56,    57,    63,    -1,    60,    -1,    61,    -1,    62,    -1,
      83,    -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,
      88,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,
      73,    -1,    82,    -1,    89,    -1,    90,    -1,    91,    -1,
     140,    -1,   143,    -1,    20,    52,   165,    53,   163,    -1,
      20,    52,   165,    53,   163,    21,   163,    -1,    20,    52,
     165,    53,   163,   141,    -1,    20,    52,   165,    53,   163,
     141,    21,   163,    -1,   142,    -1,   141,   142,    -1,    22,
      52,   165,    53,   163,    -1,    20,    52,   165,    59,   165,
     144,    53,   163,    -1,    -1,    59,     6,    -1,    25,    52,
     165,    53,   146,    -1,    54,   147,    55,    -1,    54,   147,
      21,   163,    55,    -1,   148,    -1,   147,   148,    -1,    26,
      52,   188,    53,   163,    -1,    23,    52,     6,    24,   165,
      53,   163,    -1,    23,    52,    52,     6,    59,     6,    53,
      24,   165,    53,   163,    -1,    37,   163,    38,    52,     6,
      53,   151,   154,    -1,    54,    55,    -1,    54,   152,    55,
      -1,   153,    -1,   152,   153,    -1,    58,   165,    -1,   145,
      -1,   121,    -1,   128,    -1,   139,    -1,   149,    -1,   150,
      -1,   159,    -1,    -1,    39,    54,   152,    55,    -1,    58,
      32,    -1,    58,    32,   165,    -1,    58,    30,    -1,    58,
      31,    -1,    58,     7,     6,    52,    53,    -1,    58,     7,
       6,    52,   187,    53,    -1,    58,     7,     6,    52,   187,
      59,    66,     6,    53,    -1,    58,     7,     6,    52,    66,
       6,    53,    -1,    58,    40,    52,   165,    53,    -1,    58,
      33,    -1,    58,    27,    52,    53,    -1,    58,    27,    52,
     188,    53,    -1,    58,    29,    52,    53,    -1,    58,    29,
      52,   188,    53,    -1,    54,    55,    -1,    54,   164,    55,
      -1,   102,    -1,   164,   102,    -1,   167,    -1,   179,   166,
     165,    -1,    63,    -1,    74,    -1,    75,    -1,    76,    -1,
      77,    -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,
      92,    -1,    93,    -1,    94,    -1,    95,    -1,   168,    -1,
     167,    61,   168,    -1,   169,    -1,   168,    60,   169,    -1,
     170,    -1,   169,    71,   170,    -1,   171,    -1,   170,    72,
     171,    -1,   172,    -1,   171,    70,   172,    -1,   173,    -1,
     172,    83,   173,    -1,   172,    84,   173,    -1,   174,    -1,
     173,    85,   174,    -1,   173,    86,   174,    -1,   173,    87,
     174,    -1,   173,    88,   174,    -1,   175,    -1,   174,    82,
     175,    -1,   174,    89,   175,    -1,   174,    90,   175,    -1,
     174,    91,   175,    -1,   176,    -1,   175,    64,   176,    -1,
     175,    65,   176,    -1,   177,    -1,   176,    66,   177,    -1,
     176,    67,   177,    -1,   176,    68,   177,    -1,   178,    -1,
     177,    69,   178,    -1,   179,    -1,    62,   178,    -1,    73,
     178,    -1,    65,   178,    -1,    64,   178,    -1,   183,    -1,
     179,    56,   165,    57,    -1,   179,    44,     6,    52,    53,
     180,    -1,   179,    44,     6,    52,   188,    53,   180,    -1,
      34,    44,     6,    52,    53,   180,    -1,    34,    44,     6,
      52,   188,    53,   180,    -1,     6,    52,    53,   180,    -1,
       6,    52,   188,    53,   180,    -1,   179,    44,     6,    -1,
      34,    44,     6,    -1,    -1,    54,    55,    -1,    54,   181,
      55,    -1,    54,    28,    96,    56,   187,    57,    99,   181,
      55,    -1,   182,    -1,   181,   182,    -1,    58,   165,    -1,
     145,    -1,   121,    -1,   128,    -1,   139,    -1,   149,    -1,
     150,    -1,   159,    -1,   184,    -1,    52,   165,    53,    -1,
       6,    -1,     3,    -1,     4,    -1,     5,    -1,    41,    -1,
      42,    -1,    43,    -1,   185,    -1,   189,    -1,   186,     6,
      -1,    97,   186,     6,    -1,    97,     6,    -1,    56,    57,
      -1,    56,   188,    57,    -1,    56,   188,    59,    57,    -1,
       6,    97,    -1,   186,     6,    97,    -1,     6,    -1,   187,
      59,     6,    -1,   165,    -1,   188,    59,   165,    -1,    54,
      55,    -1,    54,   190,    55,    -1,    54,   190,   165,    96,
     165,    55,    -1,   191,    -1,   190,   191,    -1,   165,    96,
     165,    59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   110,   116,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   139,   149,   152,
     158,   163,   170,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   193,   196,   199,
     205,   208,   214,   217,   223,   228,   233,   237,   245,   252,
     263,   270,   281,   292,   302,   315,   325,   338,   348,   361,
     371,   374,   380,   385,   392,   399,   400,   401,   402,   403,
     404,   409,   420,   423,   429,   434,   441,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   464,
     474,   487,   497,   510,   520,   533,   540,   550,   553,   559,
     564,   571,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   590,   593,   599,   604,   611,   618,   619,   620,   621,
     622,   623,   624,   625,   629,   632,   635,   638,   641,   644,
     647,   650,   656,   665,   668,   679,   682,   685,   688,   691,
     694,   697,   700,   703,   706,   709,   712,   715,   718,   721,
     724,   727,   730,   733,   736,   739,   742,   745,   748,   751,
     758,   765,   775,   779,   784,   788,   795,   800,   807,   814,
     821,   824,   831,   841,   845,   852,   857,   864,   872,   879,
     890,   900,   903,   909,   914,   921,   928,   929,   930,   931,
     932,   933,   934,   939,   942,   950,   957,   968,   978,   989,
     996,  1003,  1010,  1021,  1032,  1043,  1050,  1061,  1068,  1078,
    1082,  1088,  1093,  1101,  1102,  1109,  1112,  1115,  1118,  1121,
    1124,  1127,  1130,  1133,  1136,  1139,  1142,  1145,  1151,  1152,
    1159,  1160,  1167,  1168,  1175,  1176,  1183,  1184,  1191,  1192,
    1196,  1203,  1204,  1208,  1212,  1216,  1223,  1224,  1228,  1232,
    1236,  1243,  1244,  1248,  1255,  1256,  1260,  1264,  1271,  1272,
    1279,  1280,  1284,  1288,  1292,  1299,  1300,  1304,  1308,  1312,
    1316,  1320,  1324,  1328,  1332,  1339,  1342,  1345,  1348,  1354,
    1359,  1366,  1373,  1374,  1375,  1376,  1377,  1378,  1379,  1383,
    1384,  1387,  1391,  1394,  1397,  1400,  1404,  1408,  1412,  1413,
    1417,  1421,  1425,  1432,  1436,  1440,  1448,  1453,  1461,  1466,
    1473,  1478,  1485,  1489,  1493,  1500,  1505,  1511
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "STRING",
  "IDENTIFIER", "FUNCTION", "CLASS", "MODULE", "INTERFACE", "EXTENDS",
  "INVOLVES", "JOINTS", "PERSONAL", "RELATIVE", "EVERYONE", "GET", "SET",
  "GSET", "IF", "ELSE", "ELSEIF", "FOR", "IN", "SWITCH", "WHEN", "CAST",
  "ITERATOR", "SUPER", "BREAK", "CONTINUE", "RETURN", "BLOCK", "SELF",
  "WITH", "WITHOUT", "ORDER", "SERVE", "IGNORE", "GROAN", "TRUE", "FALSE",
  "NIL", "DOT", "ALIAS", "RETRY", "REDO", "GOTO", "CONST", "GLOBAL",
  "STATIC", "LP", "RP", "LC", "RC", "LB", "RB", "SEMICOLON", "COMMA",
  "LOGICAL_AND", "LOGICAL_OR", "LOGICAL_NOT", "ASSIGN", "ADD", "SUB",
  "MUL", "DIV", "MOD", "POWER", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT",
  "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MUL", "ASSIGN_DIV", "ASSIGN_MOD",
  "ASSIGN_BIT_AND", "ASSIGN_BIT_OR", "ASSIGN_BIT_XOR", "BIT_SHR", "EQ",
  "NE", "GT", "GE", "LT", "LE", "BIT_SHL", "BIT_SAR", "BIT_SAL",
  "ASSIGN_BIT_SHR", "ASSIGN_BIT_SHL", "ASSIGN_BIT_SAR", "ASSIGN_BIT_SAL",
  "ITER", "FILED", "SHARP", "CONLON", "$accept", "translation_unit",
  "statement", "class_statement", "class_block",
  "class_involve_statement_list", "class_involve_statement",
  "extends_field", "interface_field", "module_field",
  "field_identifier_list", "getter_statement", "setter_statement",
  "getter_setter_statement", "class_everyone_statement",
  "class_relative_statement", "class_personal_statement",
  "interface_statement", "interface_block",
  "interface_involve_statement_list", "interface_involve_statement",
  "module_statement", "module_block", "module_involve_statement_list",
  "module_involve_statement", "module_everyone_statement",
  "module_relative_statement", "module_personal_statement",
  "function_statement", "function_block",
  "function_involve_statement_list", "function_involve_statement",
  "with_without_block", "with_without_involve_statement_list",
  "with_without_involve_statement", "function_header",
  "function_operator_statement", "function_operator_header", "operator",
  "if_statement", "condition_if", "elseif_list", "elseif", "loop_if",
  "loop_time", "switch_statement", "switch_block", "when_list", "when",
  "for_statement", "order_statement", "order_block",
  "order_involve_statement_list", "order_involve_statement",
  "ignore_block", "return_statement", "break_statement",
  "continue_statement", "interface_func_statement", "groan_statement",
  "block_statement", "cast_statement", "super_statement", "block",
  "statement_list", "expression", "assign_symbol", "logic_or_expression",
  "logic_and_expression", "logic_bit_or_expression",
  "logic_bit_xor_expression", "logic_bit_and_expression",
  "logic_equal_compare_expression", "logic_not_equal_expression",
  "logic_shift_expression", "add_sub_expression", "mul_div_mod_expression",
  "power_expression", "unary_expression", "top_expression",
  "closure_block", "closure_involve_statement_list",
  "closure_involve_statement", "primary_expression",
  "identifier_with_field", "array_literal", "field_identifier",
  "identifier_list", "expression_list", "hash_literal", "hash_pair_list",
  "hash_pair", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   104,   104,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   111,   111,
     112,   112,   113,   114,   114,   115,   115,   116,   116,   117,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   121,   122,   122,   123,   123,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   132,   132,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     139,   139,   140,   140,   140,   140,   141,   141,   142,   143,
     144,   144,   145,   146,   146,   147,   147,   148,   149,   149,
     150,   151,   151,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   154,   154,   155,   155,   156,   157,   158,
     158,   158,   158,   159,   160,   161,   161,   162,   162,   163,
     163,   164,   164,   165,   165,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   172,   172,
     172,   173,   173,   173,   173,   173,   174,   174,   174,   174,
     174,   175,   175,   175,   176,   176,   176,   176,   177,   177,
     178,   178,   178,   178,   178,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   180,   180,   180,   180,   181,
     181,   182,   182,   182,   182,   182,   182,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     184,   184,   184,   185,   185,   185,   186,   186,   187,   187,
     188,   188,   189,   189,   189,   190,   190,   191
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     2,     3,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     2,
       0,     2,     0,     2,     1,     1,     3,     3,     5,     7,
       5,     8,     5,     5,     7,     5,     7,     5,     7,     4,
       2,     3,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     4,     2,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       7,     5,     7,     5,     7,     2,     6,     2,     3,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     5,     8,     6,     6,     7,
      10,     8,     2,     4,     5,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     6,     8,     1,     2,     5,     8,
       0,     2,     5,     3,     5,     1,     2,     5,     7,    11,
       8,     2,     3,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     2,     3,     2,     2,     5,
       6,     9,     7,     5,     2,     4,     5,     4,     5,     2,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     2,     2,     2,     2,     1,     4,     6,     7,     6,
       7,     4,     5,     3,     3,     0,     2,     3,     9,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     2,     2,     3,     4,     2,     3,     1,     3,
       1,     3,     2,     3,     6,     1,     2,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,    12,    13,    11,     5,     0,     7,   160,   161,
      10,    14,    15,     6,     8,     9,    16,     0,     0,    37,
      42,    40,     0,     0,     0,     0,     0,   292,   293,   294,
     291,   197,   198,   195,     0,     0,   295,   296,   297,     0,
       0,     0,     0,     0,     0,     0,     0,     4,   213,   228,
     230,   232,   234,   236,   238,   241,   246,   251,   254,   258,
     260,   265,   289,   298,     0,   299,     1,     3,     0,    95,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,   209,   211,     0,     0,     0,   306,   196,     0,
       0,     0,   312,     0,     0,   315,   303,   310,     0,   261,
     260,   264,   263,   262,   302,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,     0,   300,    97,     0,   104,     0,    99,   103,
     102,   105,   106,   108,   107,   109,   110,     0,   308,   124,
       0,     0,     0,    39,    38,    40,    44,    43,    45,     0,
      71,    41,     0,    59,     0,     0,     0,     0,     0,   210,
     212,     0,   275,     0,   274,     0,   290,     0,   313,     0,
     316,   304,     0,   301,   229,   231,   233,   235,   237,   239,
     240,   242,   243,   244,   245,   247,   248,   249,   250,   252,
     253,   255,   256,   257,   259,   273,     0,   214,   307,     0,
     204,   101,    98,   100,     0,     0,     0,   125,     0,     0,
       0,     0,    72,     0,    81,    85,    78,     0,    74,    82,
      83,    84,    79,    80,    77,    86,    87,    88,    60,     0,
       0,    62,    66,    65,    68,    69,    67,    70,   162,   170,
       0,     0,     0,   172,     0,     0,   271,   275,     0,     0,
     203,     0,     0,   305,   311,     0,   266,     0,   111,     0,
     118,     0,   113,   117,   116,   119,   120,   122,   121,   123,
       0,   127,   309,     0,   128,     0,     0,     0,    17,    46,
      47,     0,     0,     0,    76,    73,    75,     0,    64,    61,
      63,     0,     0,   164,   166,     0,     0,     0,     0,     0,
       0,   175,     0,     0,   276,     0,   283,   284,   285,   282,
     286,   287,   288,     0,   279,   272,   275,     0,   317,     0,
     275,     0,   207,     0,     0,   115,   112,   114,    96,     0,
       0,   129,     0,     0,     0,     0,    18,     0,     0,    20,
      28,    29,    30,    31,    32,    33,    24,    25,    26,     0,
      27,    23,    34,    35,    36,     0,     0,     0,     0,   163,
       0,     0,   167,   171,     0,   178,     0,     0,     0,   173,
     176,     0,   193,     0,   281,   277,   280,   269,   275,   314,
     267,   275,   208,     0,   126,   131,     0,     0,   137,   138,
     139,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   140,   141,   142,   143,   144,   145,   157,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    19,    21,   132,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   169,     0,     0,     0,   181,     0,   187,
     188,   189,   186,   190,   191,     0,   183,   192,     0,   180,
       0,   270,   268,   205,     0,     0,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,    91,     0,
      89,     0,   199,     0,     0,     0,     0,     0,   174,   185,
     182,   184,     0,     0,   206,   130,   136,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,   168,     0,   177,     0,
       0,     0,   134,     0,     0,    57,     0,    55,     0,    53,
       0,    48,    50,    52,    94,    92,    90,   202,     0,   179,
     194,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,    58,    56,    54,   201,   278,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,   308,   368,   369,    83,    87,    85,
     177,   370,   371,   372,   373,   374,   375,    13,   183,   260,
     261,    14,   180,   247,   248,   249,   250,   251,    15,    79,
     157,   158,   235,   291,   292,    16,   378,   379,   441,    17,
      18,   323,   324,    19,   326,    20,   273,   330,   331,    21,
      22,   402,   475,   476,   479,    23,    24,    25,   266,    26,
     165,   299,   166,    36,    94,   107,   152,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
     276,   343,   344,    71,    72,    73,    74,   171,   108,    75,
     104,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -465
static const yytype_int16 yypact[] =
{
     511,    20,    23,    36,    43,    11,    45,   108,   111,    90,
     278,  -465,  -465,  -465,  -465,  -465,   124,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,   129,    47,    49,
     173,   176,  1079,    13,  1079,   450,   163,  -465,  -465,  -465,
     -40,  -465,  -465,  1079,   206,   153,  -465,  -465,  -465,  1079,
     690,   756,  1079,  1079,  1079,  1079,   252,  -465,   156,   204,
     202,   197,   207,    33,   161,   152,    12,    81,   212,  -465,
     291,  -465,  -465,  -465,   268,  -465,  -465,  -465,   748,   245,
       8,   276,     1,   173,    15,   230,    15,   239,    -7,   270,
     289,   246,  -465,  -465,   693,   253,   790,  -465,  -465,   296,
    1079,   255,  -465,   210,   834,  -465,  -465,  -465,   198,  -465,
      -5,  -465,  -465,  -465,   215,   304,  1079,  1079,  1079,  1079,
    1079,  1079,  1079,  1079,  1079,  1079,  1079,  1079,  1079,  1079,
    1079,  1079,  1079,  1079,  1079,  1079,  1079,   307,  1079,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  1079,   219,  -465,   524,  -465,   749,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,   263,  -465,  -465,
     313,    -6,   274,   215,  -465,   176,   215,   261,  -465,   940,
    -465,   261,   284,  -465,   111,  1079,  1079,   269,   277,  -465,
    -465,   316,   283,    -3,   286,   298,  -465,  1079,  -465,   256,
    -465,  -465,   861,   219,   204,   202,   197,   207,    33,   161,
     161,   152,   152,   152,   152,    12,    12,    12,    12,    81,
      81,   212,   212,   212,  -465,   297,   300,  -465,  -465,   301,
    -465,  -465,  -465,  -465,  1270,   322,   306,  -465,    22,    17,
     308,    18,  -465,   588,  -465,  -465,  -465,  1016,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   685,
     394,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   205,   318,
     310,   373,   354,  -465,   334,  1251,  -465,   283,  1079,   932,
    -465,   329,  1079,  -465,  -465,   937,  -465,  1003,  -465,   614,
    -465,  1319,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
     263,  -465,  -465,   383,  -465,   395,     5,   323,  -465,   215,
    -465,   344,   349,   350,  -465,  -465,  -465,   402,  -465,  -465,
    -465,   111,   357,   211,  -465,   404,   359,   111,   362,   364,
       4,  -465,   367,   327,  -465,  1008,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  1087,  -465,  -465,   283,    75,  -465,   121,
     283,    76,  -465,    92,   372,  -465,  -465,  -465,  -465,   374,
     375,  -465,    26,  1095,   369,   370,  -465,   498,  1250,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   124,
    -465,  -465,  -465,  -465,  -465,    21,    28,    34,   377,  -465,
    1079,   111,  -465,  -465,   111,  -465,   406,  1079,   111,  -465,
    -465,  1257,   393,   382,  -465,  -465,  -465,  -465,   283,  -465,
    -465,   283,  -465,  1074,  -465,  -465,   427,   385,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,   387,   437,   439,   390,   397,   398,   400,   408,   409,
    -465,  -465,  -465,  -465,   411,   407,   412,   422,   415,   430,
      60,   423,  -465,  -465,  1079,   114,   424,  -465,  1008,  -465,
    -465,  -465,  -465,  -465,  -465,  1276,  -465,  -465,   396,  -465,
     471,  -465,  -465,  -465,   137,   425,   417,    14,   429,   431,
      37,    38,    39,   475,   476,   489,  -465,   491,  -465,   492,
    -465,   493,  -465,   500,   141,   111,   454,   111,  -465,  -465,
    -465,  -465,   116,   213,  -465,  -465,  -465,  -465,   151,   457,
     458,   465,   467,   466,   480,   468,   499,   478,   485,   487,
     488,   490,   494,   484,  -465,    42,  -465,   111,  -465,  1277,
     434,   540,  -465,   502,   553,  -465,   555,  -465,   562,  -465,
     564,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   566,  -465,
    -465,   231,   111,   520,   517,   518,   522,   528,  1313,  -465,
     111,  -465,  -465,  -465,  -465,  -465,  -465
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -465,  -465,     6,   -70,  -465,  -465,   209,  -465,   410,   501,
     496,  -465,  -465,  -465,  -465,  -465,  -465,  -161,  -465,  -465,
     330,  -157,  -465,  -465,   336,  -465,  -465,  -465,  -148,   208,
    -465,   441,   299,  -465,   305,  -465,  -465,  -465,  -465,   -78,
    -465,  -465,   282,  -465,  -465,   -77,  -465,  -465,   271,   -76,
     -72,  -465,    88,  -464,  -465,   -73,  -465,  -465,  -465,   -68,
    -465,  -465,  -465,  -115,  -465,   159,  -465,  -465,   495,   497,
     506,   507,   486,    16,   250,   266,   105,   127,   -17,  1120,
    -268,    46,  -340,  -465,   -69,  -465,   552,  -235,   -63,  -465,
    -465,   505
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     159,   160,   161,   406,   306,   163,   162,   173,   156,   345,
     164,   511,    96,   174,   168,   178,    77,   178,   245,    89,
     168,   176,   246,   168,   309,   398,    27,   454,   302,    29,
     329,   252,   302,   193,   456,   109,   111,   112,   113,   137,
     458,    93,    30,   521,   523,   525,   184,   237,   302,    31,
     277,   138,   185,   238,    28,   455,   278,    97,   361,   399,
      82,   169,   457,    32,   362,    90,   168,   517,   459,   268,
     304,   522,   524,   526,   170,   511,   131,   132,   407,   159,
     160,   161,   410,   305,   163,   162,   245,   156,   303,   164,
     246,    81,   416,    37,    38,    39,    40,    33,    56,   252,
     190,   253,   254,   255,   262,   263,   264,   256,   558,   244,
     265,   257,    56,   502,   267,    56,   121,   122,   336,   224,
      41,    42,    43,     1,    44,     3,   503,   337,   408,   411,
      45,    46,    47,    48,   278,   278,     5,   209,   210,     6,
     481,     7,    49,   482,    50,   412,    51,   133,   134,   135,
     376,   278,    52,     8,    53,    54,   293,   294,   295,   377,
      34,   297,   296,    55,   290,    35,   298,   507,    57,   253,
     254,   255,   310,   278,   468,   256,   409,   244,    78,   257,
     348,    80,   262,   263,   264,    84,   336,    56,   265,    86,
     514,    88,   267,    91,   534,   337,   278,   338,   339,   340,
     535,    95,    98,   341,   542,   100,   389,   342,   101,   103,
     541,   376,   395,   293,   294,   295,   347,   116,   297,   296,
     377,   290,   351,   298,   353,   504,   321,   322,   406,   380,
     381,   382,   391,   322,   127,   383,   219,   220,     1,   384,
       3,   128,   129,   130,   469,   513,   123,   124,   125,   126,
      99,     5,   518,   470,     6,   201,     7,   202,   114,   195,
     221,   222,   223,   199,   117,   338,   339,   340,     8,   119,
     540,   341,   541,   118,   153,   342,   462,   120,    76,   463,
     167,   136,   172,   466,   179,     1,     2,     3,     4,   335,
     380,   381,   382,   182,   186,   187,   383,   226,     5,   188,
     384,     6,   194,     7,     5,   191,   197,     6,   196,     7,
     203,   227,    97,   225,   231,     8,   228,   234,   469,   236,
     241,     8,   274,   471,   472,   473,   239,   470,   271,   474,
     363,   272,     3,   477,   465,   137,     9,   275,   279,   258,
     364,   365,   259,     5,   269,   270,     6,   138,     7,   285,
     484,   280,   282,   287,   139,   469,   281,   286,   300,   301,
       8,   284,   307,   327,   470,   140,   141,   142,   143,   144,
     145,   146,   147,   211,   212,   213,   214,   325,   366,   328,
     329,   367,   469,   148,   149,   150,   151,   332,   348,   359,
     536,   470,   538,   215,   216,   217,   218,   471,   472,   473,
     385,   360,   314,   474,   336,   386,   387,   477,   388,   390,
     393,   336,   394,   337,     5,   396,   397,     6,   318,     7,
     337,   401,   559,   403,   413,   442,   443,   414,   415,   460,
     464,     8,   478,   485,   471,   472,   473,   284,   480,   487,
     474,   349,   486,   488,   477,   489,   490,   569,   355,   319,
     512,   497,   259,   491,   492,   576,   493,     1,     2,     3,
       4,   471,   472,   473,   494,   495,   499,   474,   496,   498,
       5,   477,   500,     6,   501,     7,   505,   168,   515,   508,
     516,   527,   528,   338,   339,   340,   519,     8,   520,   341,
     338,   339,   340,   342,   404,   529,   341,   530,   531,   532,
     342,    37,    38,    39,    40,    92,   533,   537,     9,   543,
     544,   546,   444,   445,   446,   447,   448,   449,     1,     2,
       3,     4,   545,   547,   548,   549,   450,    37,    38,    39,
      40,     5,    44,   561,     6,   551,     7,   557,    45,    46,
      47,    48,   552,   550,   553,   554,   302,   555,     8,   461,
      49,   556,    50,   229,    51,   562,    43,   230,    44,   563,
      52,   564,    53,    54,    45,    46,    47,    48,   565,     9,
     566,    55,   567,   570,   571,   572,    49,   452,    50,   573,
      51,   574,   181,   316,   175,   240,    52,   453,    53,    54,
     320,    37,    38,    39,    40,    56,   357,    55,   233,   358,
     539,   400,   311,   312,   313,   392,   208,   568,   115,   200,
       0,   204,     0,     0,   205,     0,     0,    37,    38,    39,
      40,    56,    44,   506,   206,     0,   207,   509,    45,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
      49,   354,    50,     0,    51,     0,    43,     0,    44,     0,
      52,     0,    53,    54,    45,    46,    47,    48,     0,     0,
       0,    55,     0,     0,     0,     0,    49,     0,    50,     0,
      51,     0,     0,     0,     0,     0,    52,     0,    53,    54,
       0,     0,     0,     0,     0,    56,     0,    55,    37,    38,
      39,    40,   317,    37,    38,    39,    40,     0,     0,     0,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     5,     0,     0,     6,     0,     7,    44,
       0,     0,     0,     0,    44,    45,    46,    47,    48,     0,
       8,    46,    47,    48,     0,     0,     0,    49,     0,    50,
       0,    51,    49,     0,    50,   102,    51,    52,   189,    53,
      54,     9,    52,     0,    53,    54,     2,     2,    55,    37,
      38,    39,    40,    55,     0,     0,     0,     0,     5,     5,
       0,     6,     6,     7,     7,     0,     0,     0,     0,     0,
       0,     0,    56,     0,     0,     8,     8,    56,     0,     0,
      44,     0,     0,    37,    38,    39,    40,    46,    47,    48,
       0,     0,     0,   154,   232,     0,   155,   155,    49,     0,
      50,     0,    51,   106,     0,     0,     0,     0,    52,     0,
      53,    54,     0,     0,    44,     0,     0,     0,     0,    55,
       0,    46,    47,    48,     0,     0,     0,    37,    38,    39,
      40,     0,    49,   192,    50,     0,    51,     0,     0,     0,
       0,     0,    52,    56,    53,    54,     0,     0,     0,     0,
       0,     0,     0,    55,    37,    38,    39,    40,    44,     0,
       0,     0,     0,     0,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    56,    50,   198,
      51,     0,     0,     0,     0,    44,    52,     0,    53,    54,
       0,     0,    46,    47,    48,     0,     0,    55,     0,     0,
       0,     0,     0,    49,     0,    50,     0,    51,   283,     0,
       0,     0,     0,    52,     0,    53,    54,     0,     0,     0,
       0,    56,     0,     0,    55,    37,    38,    39,    40,     0,
      37,    38,    39,    40,     0,     0,     0,     1,     2,     3,
       4,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       5,     0,     0,     6,     0,     7,    44,     0,     0,     0,
       0,    44,     0,    46,    47,    48,     0,     8,    46,    47,
      48,     0,     0,     0,    49,   346,    50,     0,    51,    49,
     350,    50,     0,    51,    52,   242,    53,    54,   243,    52,
       0,    53,    54,     0,     0,    55,    37,    38,    39,    40,
      55,    37,    38,    39,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     0,     0,    56,
       0,     0,     0,     0,    56,     0,     5,    44,     0,     6,
       0,     7,    44,     0,    46,    47,    48,     0,    45,    46,
      47,    48,     0,     8,     0,    49,   352,    50,     0,    51,
      49,     0,    50,     0,    51,    52,     0,    53,    54,     0,
      52,   315,    53,    54,   243,     0,    55,    37,    38,    39,
      40,    55,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     3,     0,     0,     0,
      56,    27,     0,     0,     0,    56,     0,     5,    44,     0,
       6,     0,     7,    44,     0,    46,    47,    48,     0,     0,
      46,    47,    48,     0,     8,     0,    49,   483,    50,    28,
      51,    49,     0,    50,     0,    51,    52,     0,    53,    54,
       0,    52,   405,    53,    54,   335,     0,    55,     0,     0,
       0,   417,    55,     0,     0,   418,   419,   420,     0,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,     0,
       0,    56,   110,   110,   110,   110,    56,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   363,     1,     3,
       3,     0,     0,     0,     1,     0,     3,   364,   365,     0,
       5,     5,     0,     6,     6,     7,     7,     5,     2,   333,
       6,     0,     7,     1,     1,     3,     3,     8,     8,     0,
       5,     0,     0,     6,     8,     7,     5,     5,     0,     6,
       6,     7,     7,     0,     0,   451,   334,     8,   367,   335,
       0,     0,   467,     8,     8,   468,     0,     0,     0,     0,
       1,     0,     3,     0,     0,   288,     0,     2,   289,     0,
       0,   510,   560,     5,   468,   468,     6,     0,     7,     5,
       0,     0,     6,     0,     7,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   575,     0,
       0,   335,     0,     0,   356,     0,     0,   289
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-465)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      78,    78,    78,   343,   239,    78,    78,     6,    78,   277,
      78,   475,    52,    82,     6,    84,    10,    86,   179,     6,
       6,     6,   179,     6,     6,    21,     6,     6,     6,     6,
      26,   179,     6,    96,     6,    52,    53,    54,    55,    44,
       6,    35,     6,     6,     6,     6,    53,    53,     6,     6,
      53,    56,    59,    59,    34,    34,    59,    97,    53,    55,
      11,    53,    34,    52,    59,    52,     6,    53,    34,   184,
      53,    34,    34,    34,    66,   539,    64,    65,   346,   157,
     157,   157,   350,    66,   157,   157,   247,   157,    66,   157,
     247,    44,    66,     3,     4,     5,     6,    52,    97,   247,
      94,   179,   179,   179,   182,   182,   182,   179,    66,   179,
     182,   179,    97,    53,   182,    97,    83,    84,   275,   136,
      30,    31,    32,     7,    34,     9,    66,   275,    53,    53,
      40,    41,    42,    43,    59,    59,    20,   121,   122,    23,
     408,    25,    52,   411,    54,    53,    56,    66,    67,    68,
     307,    59,    62,    37,    64,    65,   234,   234,   234,   307,
      52,   234,   234,    73,   234,    54,   234,    53,     9,   247,
     247,   247,   241,    59,    58,   247,    55,   247,    54,   247,
      59,    52,   260,   260,   260,    12,   343,    97,   260,    13,
      53,    32,   260,    34,    53,   343,    59,   275,   275,   275,
      59,    38,    43,   275,    53,    52,   321,   275,    49,    50,
      59,   368,   327,   291,   291,   291,   279,    61,   291,   291,
     368,   291,   285,   291,   287,   460,    21,    22,   568,   307,
     307,   307,    21,    22,    82,   307,   131,   132,     7,   307,
       9,    89,    90,    91,   401,   480,    85,    86,    87,    88,
      44,    20,   487,   401,    23,    57,    25,    59,     6,   100,
     133,   134,   135,   104,    60,   343,   343,   343,    37,    72,
      57,   343,    59,    71,     6,   343,   391,    70,     0,   394,
      35,    69,     6,   398,    54,     7,     8,     9,    10,    58,
     368,   368,   368,    54,    24,     6,   368,   138,    20,    53,
     368,    23,     6,    25,    20,    52,    96,    23,    53,    25,
       6,   152,    97,     6,   155,    37,    97,    54,   475,     6,
      59,    37,     6,   401,   401,   401,    52,   475,    59,   401,
       7,    54,     9,   401,   397,    44,    58,    54,    52,    55,
      17,    18,    58,    20,   185,   186,    23,    56,    25,    52,
     413,    53,    96,    52,    63,   512,   197,    57,    36,    53,
      37,   202,    54,    53,   512,    74,    75,    76,    77,    78,
      79,    80,    81,   123,   124,   125,   126,    59,    55,     6,
      26,    58,   539,    92,    93,    94,    95,    53,    59,     6,
     505,   539,   507,   127,   128,   129,   130,   475,   475,   475,
      56,     6,   243,   475,   561,    56,    56,   475,     6,    52,
       6,   568,    53,   561,    20,    53,    52,    23,   259,    25,
     568,    54,   537,    96,    52,    56,    56,    53,    53,    52,
      24,    37,    39,     6,   512,   512,   512,   278,    56,    52,
     512,   282,    57,     6,   512,     6,    56,   562,   289,    55,
      54,    44,    58,    56,    56,   570,    56,     7,     8,     9,
      10,   539,   539,   539,    56,    56,    44,   539,    57,    57,
      20,   539,    57,    23,    44,    25,    53,     6,    53,    55,
      63,     6,     6,   561,   561,   561,    57,    37,    57,   561,
     568,   568,   568,   561,   335,     6,   568,     6,     6,     6,
     568,     3,     4,     5,     6,    55,     6,    53,    58,    52,
      52,    44,    14,    15,    16,    17,    18,    19,     7,     8,
       9,    10,    57,    57,    44,    57,   367,     3,     4,     5,
       6,    20,    34,    99,    23,    57,    25,    53,    40,    41,
      42,    43,    57,    44,    57,    57,     6,    57,    37,   390,
      52,    57,    54,    29,    56,    53,    32,    33,    34,     6,
      62,     6,    64,    65,    40,    41,    42,    43,     6,    58,
       6,    73,     6,    53,    57,    57,    52,   368,    54,    57,
      56,    53,    86,   247,    83,   175,    62,   379,    64,    65,
     260,     3,     4,     5,     6,    97,   291,    73,   157,   300,
     512,   330,    14,    15,    16,   323,   120,   561,    56,   104,
      -1,   116,    -1,    -1,   117,    -1,    -1,     3,     4,     5,
       6,    97,    34,   464,   118,    -1,   119,   468,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    27,    54,    -1,    56,    -1,    32,    -1,    34,    -1,
      62,    -1,    64,    65,    40,    41,    42,    43,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    73,     3,     4,
       5,     6,     7,     3,     4,     5,     6,    -1,    -1,    -1,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    97,    -1,    20,    -1,    -1,    23,    -1,    25,    34,
      -1,    -1,    -1,    -1,    34,    40,    41,    42,    43,    -1,
      37,    41,    42,    43,    -1,    -1,    -1,    52,    -1,    54,
      -1,    56,    52,    -1,    54,    55,    56,    62,    55,    64,
      65,    58,    62,    -1,    64,    65,     8,     8,    73,     3,
       4,     5,     6,    73,    -1,    -1,    -1,    -1,    20,    20,
      -1,    23,    23,    25,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    37,    37,    97,    -1,    -1,
      34,    -1,    -1,     3,     4,     5,     6,    41,    42,    43,
      -1,    -1,    -1,    55,    55,    -1,    58,    58,    52,    -1,
      54,    -1,    56,    57,    -1,    -1,    -1,    -1,    62,    -1,
      64,    65,    -1,    -1,    34,    -1,    -1,    -1,    -1,    73,
      -1,    41,    42,    43,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    97,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,     3,     4,     5,     6,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    97,    54,    55,
      56,    -1,    -1,    -1,    -1,    34,    62,    -1,    64,    65,
      -1,    -1,    41,    42,    43,    -1,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,    -1,    56,    57,    -1,
      -1,    -1,    -1,    62,    -1,    64,    65,    -1,    -1,    -1,
      -1,    97,    -1,    -1,    73,     3,     4,     5,     6,    -1,
       3,     4,     5,     6,    -1,    -1,    -1,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      20,    -1,    -1,    23,    -1,    25,    34,    -1,    -1,    -1,
      -1,    34,    -1,    41,    42,    43,    -1,    37,    41,    42,
      43,    -1,    -1,    -1,    52,    53,    54,    -1,    56,    52,
      53,    54,    -1,    56,    62,    55,    64,    65,    58,    62,
      -1,    64,    65,    -1,    -1,    73,     3,     4,     5,     6,
      73,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     7,     8,     9,    10,    -1,    -1,    97,
      -1,    -1,    -1,    -1,    97,    -1,    20,    34,    -1,    23,
      -1,    25,    34,    -1,    41,    42,    43,    -1,    40,    41,
      42,    43,    -1,    37,    -1,    52,    53,    54,    -1,    56,
      52,    -1,    54,    -1,    56,    62,    -1,    64,    65,    -1,
      62,    55,    64,    65,    58,    -1,    73,     3,     4,     5,
       6,    73,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    -1,    -1,    -1,
      97,     6,    -1,    -1,    -1,    97,    -1,    20,    34,    -1,
      23,    -1,    25,    34,    -1,    41,    42,    43,    -1,    -1,
      41,    42,    43,    -1,    37,    -1,    52,    53,    54,    34,
      56,    52,    -1,    54,    -1,    56,    62,    -1,    64,    65,
      -1,    62,    55,    64,    65,    58,    -1,    73,    -1,    -1,
      -1,    56,    73,    -1,    -1,    60,    61,    62,    -1,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    97,    52,    53,    54,    55,    97,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     7,     7,     9,
       9,    -1,    -1,    -1,     7,    -1,     9,    17,    18,    -1,
      20,    20,    -1,    23,    23,    25,    25,    20,     8,    28,
      23,    -1,    25,     7,     7,     9,     9,    37,    37,    -1,
      20,    -1,    -1,    23,    37,    25,    20,    20,    -1,    23,
      23,    25,    25,    -1,    -1,    55,    55,    37,    58,    58,
      -1,    -1,    55,    37,    37,    58,    -1,    -1,    -1,    -1,
       7,    -1,     9,    -1,    -1,    55,    -1,     8,    58,    -1,
      -1,    55,    55,    20,    58,    58,    23,    -1,    25,    20,
      -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    58,    -1,    -1,    55,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    20,    23,    25,    37,    58,
     101,   102,   103,   117,   121,   128,   135,   139,   140,   143,
     145,   149,   150,   155,   156,   157,   159,     6,    34,     6,
       6,     6,    52,    52,    52,    54,   163,     3,     4,     5,
       6,    30,    31,    32,    34,    40,    41,    42,    43,    52,
      54,    56,    62,    64,    65,    73,    97,   165,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   183,   184,   185,   186,   189,     0,   102,    54,   129,
      52,    44,    11,   107,    12,   109,    13,   108,   165,     6,
      52,   165,    55,   102,   164,    38,    52,    97,   165,    44,
      52,   165,    55,   165,   190,   191,    57,   165,   188,   178,
     179,   178,   178,   178,     6,   186,    61,    60,    71,    72,
      70,    83,    84,    85,    86,    87,    88,    82,    89,    90,
      91,    64,    65,    66,    67,    68,    69,    44,    56,    63,
      74,    75,    76,    77,    78,    79,    80,    81,    92,    93,
      94,    95,   166,     6,    55,    58,   103,   130,   131,   139,
     145,   149,   150,   155,   159,   160,   162,    35,     6,    53,
      66,   187,     6,     6,   184,   109,     6,   110,   184,    54,
     122,   110,    54,   118,    53,    59,    24,     6,    53,    55,
     102,    52,    53,   188,     6,   165,    53,    96,    55,   165,
     191,    57,    59,     6,   168,   169,   170,   171,   172,   173,
     173,   174,   174,   174,   174,   175,   175,   175,   175,   176,
     176,   177,   177,   177,   178,     6,   165,   165,    97,    29,
      33,   165,    55,   131,    54,   132,     6,    53,    59,    52,
     108,    59,    55,    58,   103,   117,   121,   123,   124,   125,
     126,   127,   128,   139,   145,   149,   150,   159,    55,    58,
     119,   120,   139,   145,   149,   150,   158,   159,   163,   165,
     165,    59,    54,   146,     6,    54,   180,    53,    59,    52,
      53,   165,    96,    57,   165,    52,    57,    52,    55,    58,
     103,   133,   134,   139,   145,   149,   150,   155,   159,   161,
      36,    53,     6,    66,    53,    66,   187,    54,   104,     6,
     184,    14,    15,    16,   165,    55,   124,     7,   165,    55,
     120,    21,    22,   141,   142,    59,   144,    53,     6,    26,
     147,   148,    53,    28,    55,    58,   121,   128,   139,   145,
     149,   150,   159,   181,   182,   180,    53,   188,    59,   165,
      53,   188,    53,   188,    27,   165,    55,   134,   132,     6,
       6,    53,    59,     7,    17,    18,    55,    58,   105,   106,
     111,   112,   113,   114,   115,   116,   121,   128,   136,   137,
     139,   145,   149,   150,   159,    56,    56,    56,     6,   163,
      52,    21,   142,     6,    53,   163,    53,    52,    21,    55,
     148,    54,   151,    96,   165,    55,   182,   180,    53,    55,
     180,    53,    53,    52,    53,    53,    66,    56,    60,    61,
      62,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,   138,    56,    56,    14,    15,    16,    17,    18,    19,
     165,    55,   106,   129,     6,    34,     6,    34,     6,    34,
      52,   165,   163,   163,    24,   188,   163,    55,    58,   121,
     128,   139,   145,   149,   150,   152,   153,   159,    39,   154,
      56,   180,   180,    53,   188,     6,    57,    52,     6,     6,
      56,    56,    56,    56,    56,    56,    57,    44,    57,    44,
      57,    44,    53,    66,   187,    53,   165,    53,    55,   165,
      55,   153,    54,   187,    53,    53,    63,    53,   187,    57,
      57,     6,    34,     6,    34,     6,    34,     6,     6,     6,
       6,     6,     6,     6,    53,    59,   163,    53,   163,   152,
      57,    59,    53,    52,    52,    57,    44,    57,    44,    57,
      44,    57,    57,    57,    57,    57,    57,    53,    66,   163,
      55,    99,    53,     6,     6,     6,     6,     6,   181,   163,
      53,    57,    57,    57,    53,    55,   163
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 107 "iris.y"
    {
		IrisInterpreter::CurInstance()->AddStatement((yyvsp[(1) - (1)].m_pStatement));
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 110 "iris.y"
    {
		IrisInterpreter::CurInstance()->AddStatement((yyvsp[(2) - (2)].m_pStatement));
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 116 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 139 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ClassStatement;
		pStatement->m_uType.m_pClassStatement = new IrisClassStatement((yyvsp[(2) - (6)].m_pIdentifier), (yyvsp[(3) - (6)].m_pExpression), (yyvsp[(4) - (6)].m_pExpressionList), (yyvsp[(5) - (6)].m_pExpressionList), (yyvsp[(6) - (6)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 149 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 152 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 158 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 163 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 170 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 193 "iris.y"
    {
		(yyval.m_pExpression) = nullptr;
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 196 "iris.y"
    {
		(yyval.m_pExpression) = (yyvsp[(2) - (2)].m_pExpression);
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 199 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFieldExpression(nullptr, (yyvsp[(2) - (2)].m_pIdentifier), false);
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 205 "iris.y"
    {
		(yyval.m_pExpressionList) = nullptr;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 208 "iris.y"
    {
		(yyval.m_pExpressionList) = (yyvsp[(2) - (2)].m_pExpressionList);
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 214 "iris.y"
    {
		(yyval.m_pExpressionList) = nullptr;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 217 "iris.y"
    {
		(yyval.m_pExpressionList) = (yyvsp[(2) - (2)].m_pExpressionList);
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 223 "iris.y"
    {
		IrisList<IrisExpression*>* pList = new IrisList<IrisExpression*>();
		pList->Add(IrisExpression::CreateFieldExpression(nullptr, (yyvsp[(1) - (1)].m_pIdentifier), false));
		(yyval.m_pExpressionList) = pList;		
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 228 "iris.y"
    {
		IrisList<IrisExpression*>* pList = new IrisList<IrisExpression*>();
		pList->Add((yyvsp[(1) - (1)].m_pExpression));
		(yyval.m_pExpressionList) = pList;
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 233 "iris.y"
    {
		(yyvsp[(1) - (3)].m_pExpressionList)->Add(IrisExpression::CreateFieldExpression(nullptr, (yyvsp[(3) - (3)].m_pIdentifier), false));
		(yyval.m_pExpressionList) = (yyvsp[(1) - (3)].m_pExpressionList);
	}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 237 "iris.y"
    {
		(yyvsp[(1) - (3)].m_pExpressionList)->Add((yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpressionList) = (yyvsp[(1) - (3)].m_pExpressionList);		
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 245 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GetterStatement;
		pStatement->m_uType.m_pGetterStatement = new IrisGetterStatement((yyvsp[(4) - (5)].m_pIdentifier), nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 252 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GetterStatement;
		pStatement->m_uType.m_pGetterStatement = new IrisGetterStatement((yyvsp[(3) - (7)].m_pIdentifier), (yyvsp[(7) - (7)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 263 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SetterStatement;
		pStatement->m_uType.m_pSetterStatement = new IrisSetterStatement((yyvsp[(4) - (5)].m_pIdentifier), nullptr, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 270 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SetterStatement;
		pStatement->m_uType.m_pSetterStatement = new IrisSetterStatement((yyvsp[(3) - (8)].m_pIdentifier), (yyvsp[(6) - (8)].m_pIdentifier), (yyvsp[(8) - (8)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 281 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GSetterStatement;
		pStatement->m_uType.m_pGSetterStatement = new IrisGSetterStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 292 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 302 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 315 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 325 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 338 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 348 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 361 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceStatement;
		pStatement->m_uType.m_pInterfaceStatement = new IrisInterfaceStatement((yyvsp[(2) - (4)].m_pIdentifier), (yyvsp[(3) - (4)].m_pExpressionList), (yyvsp[(4) - (4)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 371 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 374 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 380 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 385 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 392 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 409 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ModuleStatement;
		pStatement->m_uType.m_pModuleStatement = new IrisModuleStatement((yyvsp[(2) - (4)].m_pIdentifier), (yyvsp[(3) - (4)].m_pExpressionList), nullptr, (yyvsp[(4) - (4)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 420 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 423 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 429 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 434 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 441 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 464 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 474 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Class;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::EveryOne;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 487 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 497 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Relative;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 510 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(4) - (5)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::InstanceMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 520 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::Authority;
		pStatement->m_uType.m_pAuthorityStatement = new IrisAuthorityStatement((yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_uType.m_pAuthorityStatement->m_eEnvironment = IrisAuthorityStatement::AuthorityEnvironment::Module;
		pStatement->m_uType.m_pAuthorityStatement->m_eTarget = IrisAuthorityStatement::AuthorityTarget::ClassMethod;
		pStatement->m_uType.m_pAuthorityStatement->m_eType = IrisAuthorityStatement::AuthorityType::Personal;
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 533 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement((yyvsp[(1) - (2)].m_pFunctionHeader), nullptr, nullptr, (yyvsp[(2) - (2)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 540 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement((yyvsp[(1) - (6)].m_pFunctionHeader), (yyvsp[(4) - (6)].m_pBlock), (yyvsp[(6) - (6)].m_pBlock), (yyvsp[(2) - (6)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 550 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 553 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 559 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 564 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 571 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 590 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 593 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 599 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 604 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 611 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 629 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (4)].m_pIdentifier), nullptr, nullptr, false);
	}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 632 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (5)].m_pIdentifier), (yyvsp[(4) - (5)].m_pIdentifierList), nullptr, false);
	}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 635 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (8)].m_pIdentifier), (yyvsp[(4) - (8)].m_pIdentifierList), (yyvsp[(7) - (8)].m_pIdentifier), false);
	}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 638 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (6)].m_pIdentifier), nullptr, (yyvsp[(5) - (6)].m_pIdentifier), false);
	}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 641 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(4) - (6)].m_pIdentifier), nullptr, nullptr, true);
	}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 644 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(4) - (7)].m_pIdentifier), (yyvsp[(6) - (7)].m_pIdentifierList), nullptr, true);
	}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 647 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(4) - (10)].m_pIdentifier), (yyvsp[(6) - (10)].m_pIdentifierList), (yyvsp[(9) - (10)].m_pIdentifier), true);
	}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 650 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(4) - (8)].m_pIdentifier), nullptr, (yyvsp[(7) - (8)].m_pIdentifier), true);
	}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 656 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::FunctionStatement;
		pStatement->m_uType.m_pFunctionStatement = new IrisFunctionStatement((yyvsp[(1) - (2)].m_pFunctionHeader), nullptr, nullptr, (yyvsp[(2) - (2)].m_pBlock));
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 665 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (4)].m_pIdentifier), nullptr, nullptr, false);
	}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 668 "iris.y"
    {
		(yyval.m_pFunctionHeader) = new IrisFunctionHeader((yyvsp[(2) - (5)].m_pIdentifier), (yyvsp[(4) - (5)].m_pIdentifierList), nullptr, false);
	}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 679 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "[]");
	}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 682 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "[]=");
	}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 685 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "+");
	}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 688 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "||");
	}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 691 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!");
	}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 694 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "==");
	}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 697 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!=");
	}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 700 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">");
	}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 703 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">=");
	}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 706 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<");
	}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 709 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<=");
	}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 712 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "+");
	}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 715 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "-");
	}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 718 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "*");
	}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 721 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "/");
	}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 724 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "%");
	}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 727 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "**");
	}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 730 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "&");
	}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 733 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "|");
	}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 736 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "^");
	}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 739 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "!");
	}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 742 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">>");
	}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 745 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<<");
	}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 748 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, ">>>");
	}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 751 "iris.y"
    {
		(yyval.m_pIdentifier) = new IrisIdentifier(IrisIdentifier::IdentifilerType::GlobalVariable, "<<<");
	}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 758 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::IfStatement;
		pStatement->m_uType.m_pIfStatement = new IrisIfStatement((yyvsp[(1) - (1)].m_pConditionIf));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 765 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::IfStatement;
		pStatement->m_uType.m_pIfStatement = new IrisIfStatement((yyvsp[(1) - (1)].m_pLoopIf));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 775 "iris.y"
    {
		IrisConditionIf* pConditionIf = new IrisConditionIf((yyvsp[(3) - (5)].m_pExpression), (yyvsp[(5) - (5)].m_pBlock), nullptr, nullptr);
		(yyval.m_pConditionIf) = pConditionIf;
	}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 779 "iris.y"
    {
		IrisConditionIf* pConditionIf = new IrisConditionIf((yyvsp[(3) - (7)].m_pExpression), (yyvsp[(5) - (7)].m_pBlock), nullptr, (yyvsp[(7) - (7)].m_pBlock));
		(yyval.m_pConditionIf) = pConditionIf;
	}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 784 "iris.y"
    {
		IrisConditionIf* pConditionIf = new IrisConditionIf((yyvsp[(3) - (6)].m_pExpression), (yyvsp[(5) - (6)].m_pBlock), (yyvsp[(6) - (6)].m_pElseIfList), nullptr);
		(yyval.m_pConditionIf) = pConditionIf;
	}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 788 "iris.y"
    {
		IrisConditionIf* pConditionIf = new IrisConditionIf((yyvsp[(3) - (8)].m_pExpression), (yyvsp[(5) - (8)].m_pBlock), (yyvsp[(6) - (8)].m_pElseIfList), (yyvsp[(8) - (8)].m_pBlock));
		(yyval.m_pConditionIf) = pConditionIf;
	}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 795 "iris.y"
    {
		IrisList<IrisElseIf*>* pElseIfList = new IrisList<IrisElseIf*>();
		pElseIfList->Add((yyvsp[(1) - (1)].m_pElseIf));
		(yyval.m_pElseIfList) = pElseIfList;
	}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 800 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pElseIfList)->Add((yyvsp[(2) - (2)].m_pElseIf));
		(yyval.m_pElseIfList) = (yyvsp[(1) - (2)].m_pElseIfList);
	}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 807 "iris.y"
    {
		IrisElseIf* pElseIf = new IrisElseIf((yyvsp[(3) - (5)].m_pExpression), (yyvsp[(5) - (5)].m_pBlock));
		(yyval.m_pElseIf) = pElseIf;
	}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 814 "iris.y"
    {
		IrisLoopIf* pLoopIf = new IrisLoopIf((yyvsp[(3) - (8)].m_pExpression), (yyvsp[(5) - (8)].m_pExpression), (yyvsp[(6) - (8)].m_pIdentifier), (yyvsp[(8) - (8)].m_pBlock));
		(yyval.m_pLoopIf) = pLoopIf;
	}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 821 "iris.y"
    {
		(yyval.m_pIdentifier) = nullptr;
	}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 824 "iris.y"
    {
		(yyval.m_pIdentifier) = (yyvsp[(2) - (2)].m_pIdentifier);
	}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 831 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SwitchStatement;
		pStatement->m_uType.m_pSwitchStatement = new IrisSwitchStatement((yyvsp[(3) - (5)].m_pExpression), (yyvsp[(5) - (5)].m_pSwitchBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 841 "iris.y"
    {
		IrisSwitchBlock* pSwitchBlock = new IrisSwitchBlock((yyvsp[(2) - (3)].m_pWhenList), nullptr);
		(yyval.m_pSwitchBlock) = pSwitchBlock;
	}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 845 "iris.y"
    {
		IrisSwitchBlock* pSwitchBlock = new IrisSwitchBlock((yyvsp[(2) - (5)].m_pWhenList), (yyvsp[(4) - (5)].m_pBlock));
		(yyval.m_pSwitchBlock) = pSwitchBlock;		
	}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 852 "iris.y"
    {
		IrisList<IrisWhen*>* pWhenList = new IrisList<IrisWhen*>();
		pWhenList->Add((yyvsp[(1) - (1)].m_pWhen));
		(yyval.m_pWhenList) = pWhenList;
	}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 857 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pWhenList)->Add((yyvsp[(2) - (2)].m_pWhen));
		(yyval.m_pWhenList) = (yyvsp[(1) - (2)].m_pWhenList);
	}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 864 "iris.y"
    {
		IrisWhen* pWhen = new IrisWhen((yyvsp[(3) - (5)].m_pExpressionList), (yyvsp[(5) - (5)].m_pBlock));
		(yyval.m_pWhen) = pWhen;
	}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 872 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ForStatement;
		pStatement->m_uType.m_pForStatement = new IrisForStatement((yyvsp[(3) - (7)].m_pIdentifier), nullptr, (yyvsp[(5) - (7)].m_pExpression), (yyvsp[(7) - (7)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 879 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ForStatement;
		pStatement->m_uType.m_pForStatement = new IrisForStatement((yyvsp[(4) - (11)].m_pIdentifier), (yyvsp[(6) - (11)].m_pIdentifier), (yyvsp[(9) - (11)].m_pExpression), (yyvsp[(11) - (11)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 890 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::OrderStatement;
		pStatement->m_uType.m_pOrderStatement = new IrisOrderStatement((yyvsp[(2) - (8)].m_pBlock), (yyvsp[(5) - (8)].m_pIdentifier), (yyvsp[(7) - (8)].m_pBlock), (yyvsp[(8) - (8)].m_pBlock));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 900 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 903 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 909 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 914 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 921 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 939 "iris.y"
    {
		(yyval.m_pBlock) = nullptr;
	}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 942 "iris.y"
    {
		(yyval.m_pBlock) = new IrisBlock((yyvsp[(3) - (4)].m_pStatementList));;
	}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 950 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ReturnStatement;
		pStatement->m_uType.m_pReturnStatement = new IrisReturnStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 957 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ReturnStatement;
		pStatement->m_uType.m_pReturnStatement = new IrisReturnStatement((yyvsp[(3) - (3)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 968 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::BreakStatement;
		pStatement->m_uType.m_pBreakStatement = new IrisBreakStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 978 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::ContinueStatement;
		pStatement->m_uType.m_pContinueStatement = new IrisContinueStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 989 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement((yyvsp[(3) - (5)].m_pIdentifier), nullptr, nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 996 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement((yyvsp[(3) - (6)].m_pIdentifier), (yyvsp[(5) - (6)].m_pIdentifierList), nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1003 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement((yyvsp[(3) - (9)].m_pIdentifier), (yyvsp[(5) - (9)].m_pIdentifierList), (yyvsp[(8) - (9)].m_pIdentifier));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1010 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::InterfaceFunctionStatement;
		pStatement->m_uType.m_pInterfaceFunctionStatement = new IrisInterfaceFunctionStatement((yyvsp[(3) - (7)].m_pIdentifier), nullptr, (yyvsp[(6) - (7)].m_pIdentifier));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1021 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::GroanStatement;
		pStatement->m_uType.m_pGroanStatement = new IrisGroanStatement((yyvsp[(4) - (5)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1032 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::BlockStatement;
		pStatement->m_uType.m_pBlockStatement = new IrisBlockStatement();
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1043 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::CastStatement;
		pStatement->m_uType.m_pCastStatement = new IrisCastStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1050 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::CastStatement;
		pStatement->m_uType.m_pCastStatement = new IrisCastStatement((yyvsp[(4) - (5)].m_pExpressionList));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1061 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SuperStatement;
		pStatement->m_uType.m_pSuperStatement = new IrisSuperStatement(nullptr);
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1068 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::SuperStatement;
		pStatement->m_uType.m_pSuperStatement = new IrisSuperStatement((yyvsp[(4) - (5)].m_pExpressionList));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;	
	}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1078 "iris.y"
    {
		IrisBlock* pBlock = new IrisBlock(nullptr);
		(yyval.m_pBlock) = pBlock;
	}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1082 "iris.y"
    {
		IrisBlock* pBlock = new IrisBlock((yyvsp[(2) - (3)].m_pStatementList));
		(yyval.m_pBlock) = pBlock;		
	}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1088 "iris.y"
    {
		IrisList<IrisStatement*>* pStatementList = new IrisList<IrisStatement*>();
		pStatementList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pStatementList;
	}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1093 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1102 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression((yyvsp[(2) - (3)].m_eExpressionType), (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1109 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::Assign;
	}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1112 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignAdd;
	}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1115 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignSub;
	}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1118 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignMul;
	}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1121 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignDiv;
	}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1124 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignMod;
	}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1127 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitAnd;
	}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1130 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitOr;
	}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1133 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitXor;
	}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1136 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitShr;
	}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1139 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitShl;
	}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1142 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitSar;
	}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1145 "iris.y"
    {
		(yyval.m_eExpressionType) = IrisExpression::ExpressionType::AssignBitSal;
	}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1152 "iris.y"
    {
		(yyval.m_pExpression) =  IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicOr, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1160 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicAnd, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1168 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitOr, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1176 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitXor, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1184 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LogicBitAnd, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1192 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Equal, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1196 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::NotEqual, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1204 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::GreatThan, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1208 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::GreatThanOrEqual, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1212 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LessThan, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1216 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::LessThanOrEqual, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1224 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitShr, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1228 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitShl, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1232 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitSar, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1236 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::BitSal, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1244 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Add, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1248 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Sub, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1256 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Mul, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1260 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Div, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 1264 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Mod, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1272 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateBinaryExpression(IrisExpression::ExpressionType::Power, (yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1280 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::LogicNot, (yyvsp[(2) - (2)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1284 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::BitNot, (yyvsp[(2) - (2)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1288 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::Minus, (yyvsp[(2) - (2)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1292 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateUnaryExpression(IrisExpression::ExpressionType::Plus, (yyvsp[(2) - (2)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1300 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateIndexExpression((yyvsp[(1) - (4)].m_pExpression), (yyvsp[(3) - (4)].m_pExpression));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1304 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFunctionCallExpression((yyvsp[(1) - (6)].m_pExpression), (yyvsp[(3) - (6)].m_pIdentifier), nullptr, (yyvsp[(6) - (6)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1308 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFunctionCallExpression((yyvsp[(1) - (7)].m_pExpression), (yyvsp[(3) - (7)].m_pIdentifier), (yyvsp[(5) - (7)].m_pExpressionList), (yyvsp[(7) - (7)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1312 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateSelfFunctionCallExpression((yyvsp[(3) - (6)].m_pIdentifier), nullptr, (yyvsp[(6) - (6)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1316 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateSelfFunctionCallExpression((yyvsp[(3) - (7)].m_pIdentifier), (yyvsp[(5) - (7)].m_pExpressionList), (yyvsp[(7) - (7)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1320 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFunctionCallExpression(nullptr, (yyvsp[(1) - (4)].m_pIdentifier), nullptr, (yyvsp[(4) - (4)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1324 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFunctionCallExpression(nullptr, (yyvsp[(1) - (5)].m_pIdentifier), (yyvsp[(3) - (5)].m_pExpressionList), (yyvsp[(5) - (5)].m_pClosureBlockLiteral));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1328 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateMemberExpression((yyvsp[(1) - (3)].m_pExpression), (yyvsp[(3) - (3)].m_pIdentifier));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1332 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateSelfMemberExpression((yyvsp[(3) - (3)].m_pIdentifier));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1339 "iris.y"
    {
		(yyval.m_pClosureBlockLiteral) = nullptr;
	}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1342 "iris.y"
    {
		(yyval.m_pClosureBlockLiteral) = nullptr;
	}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1345 "iris.y"
    {
		(yyval.m_pClosureBlockLiteral) = new IrisClosureBlockLiteral(nullptr, (yyvsp[(2) - (3)].m_pStatementList));
	}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1348 "iris.y"
    {
		(yyval.m_pClosureBlockLiteral) = new IrisClosureBlockLiteral((yyvsp[(5) - (9)].m_pIdentifierList), (yyvsp[(8) - (9)].m_pStatementList));
	}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1354 "iris.y"
    {
		IrisList<IrisStatement*>* pList = new IrisList<IrisStatement*>();
		pList->Add((yyvsp[(1) - (1)].m_pStatement));
		(yyval.m_pStatementList) = pList;
	}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1359 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pStatementList)->Add((yyvsp[(2) - (2)].m_pStatement));
		(yyval.m_pStatementList) = (yyvsp[(1) - (2)].m_pStatementList);
	}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1366 "iris.y"
    {
		IrisStatement* pStatement = new IrisStatement();
		pStatement->m_eStatementType = IrisStatement::StatementType::NormalStatement;
		pStatement->m_uType.m_pNormalStatement = new IrisNormalStatement((yyvsp[(2) - (2)].m_pExpression));
		pStatement->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
		(yyval.m_pStatement) = pStatement;
	}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1384 "iris.y"
    {
		(yyval.m_pExpression) = (yyvsp[(2) - (3)].m_pExpression);
	}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1387 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateIdentifierExpression((yyvsp[(1) - (1)].m_pIdentifier));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1391 "iris.y"
    {
		(yyval.m_pExpression) = (yyvsp[(1) - (1)].m_pExpression);
	}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1394 "iris.y"
    {
		(yyval.m_pExpression) = (yyvsp[(1) - (1)].m_pExpression);
	}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1397 "iris.y"
    {
		(yyval.m_pExpression) = (yyvsp[(1) - (1)].m_pExpression);
	}
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1400 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::True);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1404 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::False);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1408 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateInstantValueExpression(IrisExpression::ExpressionType::Nil);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1417 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFieldExpression((yyvsp[(1) - (2)].m_pIdentifierList), (yyvsp[(2) - (2)].m_pIdentifier), false);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1421 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFieldExpression((yyvsp[(2) - (3)].m_pIdentifierList), (yyvsp[(3) - (3)].m_pIdentifier), true);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1425 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateFieldExpression(nullptr, (yyvsp[(2) - (2)].m_pIdentifier), true);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1432 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateArrayExpression(nullptr);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1436 "iris.y"
    {
        (yyval.m_pExpression) = IrisExpression::CreateArrayExpression((yyvsp[(2) - (3)].m_pExpressionList));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 1440 "iris.y"
    {
        (yyval.m_pExpression) = IrisExpression::CreateArrayExpression((yyvsp[(2) - (4)].m_pExpressionList));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1448 "iris.y"
    {
		IrisList<IrisIdentifier*>* pFieldIdentifier = new IrisList<IrisIdentifier*>();
		pFieldIdentifier->Add((yyvsp[(1) - (2)].m_pIdentifier));
		(yyval.m_pIdentifierList) = pFieldIdentifier;
	}
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 1453 "iris.y"
    {
		(yyvsp[(1) - (3)].m_pIdentifierList)->Add((yyvsp[(2) - (3)].m_pIdentifier));
		(yyval.m_pIdentifierList) = (yyvsp[(1) - (3)].m_pIdentifierList);
	}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1461 "iris.y"
    {
		IrisList<IrisIdentifier*>* pList = new IrisList<IrisIdentifier*>();
		pList->Add((yyvsp[(1) - (1)].m_pIdentifier));
		(yyval.m_pIdentifierList) = pList;
	}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1466 "iris.y"
    {
		(yyvsp[(1) - (3)].m_pIdentifierList)->Add((yyvsp[(3) - (3)].m_pIdentifier));
		(yyval.m_pIdentifierList) = (yyvsp[(1) - (3)].m_pIdentifierList);
	}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1473 "iris.y"
    {
		IrisList<IrisExpression*>* pExpressionList = new IrisList<IrisExpression*>();
		pExpressionList->Add((yyvsp[(1) - (1)].m_pExpression));
		(yyval.m_pExpressionList) = pExpressionList;
	}
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 1478 "iris.y"
    {
		(yyvsp[(1) - (3)].m_pExpressionList)->Add((yyvsp[(3) - (3)].m_pExpression));
		(yyval.m_pExpressionList) = (yyvsp[(1) - (3)].m_pExpressionList);
	}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1485 "iris.y"
    {
		(yyval.m_pExpression) = IrisExpression::CreateHashExpression(nullptr);
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
	}
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1489 "iris.y"
    {
        (yyval.m_pExpression) = IrisExpression::CreateHashExpression((yyvsp[(2) - (3)].m_pHashPairList));
		(yyval.m_pExpression)->m_nLineNumber = IrisInterpreter::CurInstance()->GetCurrentLineNumber();
    }
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1493 "iris.y"
    {
		(yyvsp[(2) - (6)].m_pHashPairList)->Add(new IrisHashPair((yyvsp[(3) - (6)].m_pExpression), (yyvsp[(5) - (6)].m_pExpression)));
        (yyval.m_pExpression) = IrisExpression::CreateHashExpression((yyvsp[(2) - (6)].m_pHashPairList));
    }
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1500 "iris.y"
    {
		IrisList<IrisHashPair*>* pHashPairList = new IrisList<IrisHashPair*>();
		pHashPairList->Add((yyvsp[(1) - (1)].m_pHashPair));
		(yyval.m_pHashPairList) = pHashPairList;
	}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1505 "iris.y"
    {
		(yyvsp[(1) - (2)].m_pHashPairList)->Add((yyvsp[(2) - (2)].m_pHashPair));
		(yyval.m_pHashPairList) = (yyvsp[(1) - (2)].m_pHashPairList);
	}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1511 "iris.y"
    {
		(yyval.m_pHashPair) = new IrisHashPair((yyvsp[(1) - (4)].m_pExpression), (yyvsp[(3) - (4)].m_pExpression));
	}
    break;


/* Line 1792 of yacc.c  */
#line 4460 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1514 "iris.y"
