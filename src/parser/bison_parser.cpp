/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HSQL_STYPE
#define YYLTYPE         HSQL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         hsql_parse
#define yylex           hsql_lex
#define yyerror         hsql_error
#define yydebug         hsql_debug
#define yynerrs         hsql_nerrs


/* Copy the first part of user declarations.  */
#line 1 "bison_parser.y" /* yacc.c:339  */

/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 * 
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "sqllib.h"
#include "bison_parser.h"
#include "flex_lexer.h"

#include <stdio.h>

using namespace hsql;

int yyerror(YYLTYPE* llocp, SQLStatementList** result, yyscan_t scanner, const char *msg) {

	SQLStatementList* list = new SQLStatementList();
	list->isValid = false;
	list->parser_msg = strdup(msg);
	list->error_line = llocp->first_line;
	list->error_col = llocp->first_column;

	*result = list;
	return 0;
}




#line 111 "bison_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison_parser.h".  */
#ifndef YY_HSQL_BISON_PARSER_H_INCLUDED
# define YY_HSQL_BISON_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HSQL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HSQL_DEBUG 1
#  else
#   define HSQL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HSQL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HSQL_DEBUG */
#if HSQL_DEBUG
extern int hsql_debug;
#endif
/* "%code requires" blocks.  */
#line 43 "bison_parser.y" /* yacc.c:355  */

// %code requires block	
#include "parser_typedef.h"

// Auto update column and line number
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
    	yylloc->total_column++; \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#line 169 "bison_parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef HSQL_TOKENTYPE
# define HSQL_TOKENTYPE
  enum hsql_tokentype
  {
    SQL_IDENTIFIER = 258,
    SQL_STRING = 259,
    SQL_FLOATVAL = 260,
    SQL_INTVAL = 261,
    SQL_NOTEQUALS = 262,
    SQL_LESSEQ = 263,
    SQL_GREATEREQ = 264,
    SQL_DEALLOCATE = 265,
    SQL_PARAMETERS = 266,
    SQL_INTERSECT = 267,
    SQL_TEMPORARY = 268,
    SQL_TIMESTAMP = 269,
    SQL_DISTINCT = 270,
    SQL_NVARCHAR = 271,
    SQL_RESTRICT = 272,
    SQL_TRUNCATE = 273,
    SQL_ANALYZE = 274,
    SQL_BETWEEN = 275,
    SQL_CASCADE = 276,
    SQL_COLUMNS = 277,
    SQL_CONTROL = 278,
    SQL_DEFAULT = 279,
    SQL_EXECUTE = 280,
    SQL_EXPLAIN = 281,
    SQL_HISTORY = 282,
    SQL_INTEGER = 283,
    SQL_NATURAL = 284,
    SQL_PREPARE = 285,
    SQL_PRIMARY = 286,
    SQL_SCHEMAS = 287,
    SQL_SPATIAL = 288,
    SQL_VIRTUAL = 289,
    SQL_BEFORE = 290,
    SQL_COLUMN = 291,
    SQL_CREATE = 292,
    SQL_DELETE = 293,
    SQL_DIRECT = 294,
    SQL_DOUBLE = 295,
    SQL_ESCAPE = 296,
    SQL_EXCEPT = 297,
    SQL_EXISTS = 298,
    SQL_GLOBAL = 299,
    SQL_HAVING = 300,
    SQL_IMPORT = 301,
    SQL_INSERT = 302,
    SQL_ISNULL = 303,
    SQL_OFFSET = 304,
    SQL_RENAME = 305,
    SQL_SCHEMA = 306,
    SQL_SELECT = 307,
    SQL_SORTED = 308,
    SQL_TABLES = 309,
    SQL_UNIQUE = 310,
    SQL_UNLOAD = 311,
    SQL_UPDATE = 312,
    SQL_VALUES = 313,
    SQL_AFTER = 314,
    SQL_ALTER = 315,
    SQL_CROSS = 316,
    SQL_DELTA = 317,
    SQL_GROUP = 318,
    SQL_INDEX = 319,
    SQL_INNER = 320,
    SQL_LIMIT = 321,
    SQL_LOCAL = 322,
    SQL_MERGE = 323,
    SQL_MINUS = 324,
    SQL_ORDER = 325,
    SQL_OUTER = 326,
    SQL_RIGHT = 327,
    SQL_TABLE = 328,
    SQL_UNION = 329,
    SQL_USING = 330,
    SQL_WHERE = 331,
    SQL_CALL = 332,
    SQL_DATE = 333,
    SQL_DESC = 334,
    SQL_DROP = 335,
    SQL_FILE = 336,
    SQL_FROM = 337,
    SQL_FULL = 338,
    SQL_HASH = 339,
    SQL_HINT = 340,
    SQL_INTO = 341,
    SQL_JOIN = 342,
    SQL_LEFT = 343,
    SQL_LIKE = 344,
    SQL_LOAD = 345,
    SQL_NULL = 346,
    SQL_PART = 347,
    SQL_PLAN = 348,
    SQL_SHOW = 349,
    SQL_TEXT = 350,
    SQL_TIME = 351,
    SQL_VIEW = 352,
    SQL_WITH = 353,
    SQL_ADD = 354,
    SQL_ALL = 355,
    SQL_AND = 356,
    SQL_ASC = 357,
    SQL_CSV = 358,
    SQL_FOR = 359,
    SQL_INT = 360,
    SQL_KEY = 361,
    SQL_NOT = 362,
    SQL_OFF = 363,
    SQL_SET = 364,
    SQL_TBL = 365,
    SQL_TOP = 366,
    SQL_AS = 367,
    SQL_BY = 368,
    SQL_IF = 369,
    SQL_IN = 370,
    SQL_IS = 371,
    SQL_OF = 372,
    SQL_ON = 373,
    SQL_OR = 374,
    SQL_TO = 375,
    SQL_DATABASE = 376,
    SQL_USE = 377,
    SQL_CHECK = 378,
    SQL_SUM = 379,
    SQL_AVG = 380,
    SQL_MIN = 381,
    SQL_MAX = 382,
    SQL_EQUALS = 383,
    SQL_LESS = 384,
    SQL_GREATER = 385,
    SQL_NOTNULL = 386,
    SQL_UMINUS = 387
  };
#endif

/* Value type.  */
#if ! defined HSQL_STYPE && ! defined HSQL_STYPE_IS_DECLARED
typedef union HSQL_STYPE HSQL_STYPE;
union HSQL_STYPE
{
#line 99 "bison_parser.y" /* yacc.c:355  */

	double fval;
	int64_t ival;
	char* sval;
	uint uval;
	bool bval;

	hsql::SQLStatement* statement;
	hsql::CreateDBStatement* createDB_stmt;
	hsql::DropDBStatement*  dropDB_stmt;
	hsql::UseDBStatement* useDB_stmt;
	hsql::ShowTableStatement* showTable_stmt;
	hsql::CreateStatement* 	create_stmt;
	hsql::DropStatement*   	drop_stmt;
	hsql::DescStatement* desc_stmt;
	hsql::InsertStatement* 	insert_stmt;
	hsql::DeleteStatement* 	delete_stmt;
	hsql::UpdateStatement* 	update_stmt;
	hsql::SelectStatement* 	select_stmt;
	hsql::CreateIndexStatement* createIndex_stmt;
	hsql::DropIndexStatement* dropIndex_stmt;

	hsql::Expr* expr;
	hsql::OrderDescription* order;
	hsql::OrderType order_type;
	hsql::ColumnDefinition* column_t;
	hsql::GroupByDescription* group_t;
	hsql::UpdateClause* update_t;
	hsql::SQLStatementList* stmt_list;

	std::vector<char*>* str_vec;
	std::vector<hsql::ColumnDefinition*>* column_vec;
	std::vector<hsql::UpdateClause*>* update_vec;
	std::vector<hsql::Expr*>* expr_vec;
	std::vector<std::vector<hsql::Expr*>*>* expr_vec_vec;

#line 351 "bison_parser.cpp" /* yacc.c:355  */
};
# define HSQL_STYPE_IS_TRIVIAL 1
# define HSQL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined HSQL_LTYPE && ! defined HSQL_LTYPE_IS_DECLARED
typedef struct HSQL_LTYPE HSQL_LTYPE;
struct HSQL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define HSQL_LTYPE_IS_DECLARED 1
# define HSQL_LTYPE_IS_TRIVIAL 1
#endif



int hsql_parse (hsql::SQLStatementList** result, yyscan_t scanner);

#endif /* !YY_HSQL_BISON_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 379 "bison_parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL \
             && defined HSQL_STYPE_IS_TRIVIAL && HSQL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   272

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  149
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  241

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   387

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   139,     2,     2,
     144,   145,   137,   135,   148,   136,   146,   138,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   147,
     130,   128,   131,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   142,     2,   143,   140,     2,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   129,   132,   133,   134,   141
};

#if HSQL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   230,   230,   237,   238,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   262,   268,
     276,   287,   298,   309,   318,   319,   320,   324,   325,   329,
     335,   336,   339,   340,   343,   344,   348,   349,   350,   351,
     360,   372,   385,   390,   399,   400,   408,   422,   431,   432,
     436,   460,   473,   474,   478,   479,   480,   484,   485,   486,
     487,   488,   492,   493,   497,   502,   506,   507,   510,   511,
     515,   516,   517,   525,   537,   548,   549,   553,   554,   558,
     559,   560,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   595,   596,   600,   601,
     602,   606,   611,   612,   616,   620,   628,   629,   638,   639,
     644,   645
};
#endif

#if HSQL_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "FLOATVAL",
  "INTVAL", "NOTEQUALS", "LESSEQ", "GREATEREQ", "DEALLOCATE", "PARAMETERS",
  "INTERSECT", "TEMPORARY", "TIMESTAMP", "DISTINCT", "NVARCHAR",
  "RESTRICT", "TRUNCATE", "ANALYZE", "BETWEEN", "CASCADE", "COLUMNS",
  "CONTROL", "DEFAULT", "EXECUTE", "EXPLAIN", "HISTORY", "INTEGER",
  "NATURAL", "PREPARE", "PRIMARY", "SCHEMAS", "SPATIAL", "VIRTUAL",
  "BEFORE", "COLUMN", "CREATE", "DELETE", "DIRECT", "DOUBLE", "ESCAPE",
  "EXCEPT", "EXISTS", "GLOBAL", "HAVING", "IMPORT", "INSERT", "ISNULL",
  "OFFSET", "RENAME", "SCHEMA", "SELECT", "SORTED", "TABLES", "UNIQUE",
  "UNLOAD", "UPDATE", "VALUES", "AFTER", "ALTER", "CROSS", "DELTA",
  "GROUP", "INDEX", "INNER", "LIMIT", "LOCAL", "MERGE", "MINUS", "ORDER",
  "OUTER", "RIGHT", "TABLE", "UNION", "USING", "WHERE", "CALL", "DATE",
  "DESC", "DROP", "FILE", "FROM", "FULL", "HASH", "HINT", "INTO", "JOIN",
  "LEFT", "LIKE", "LOAD", "NULL", "PART", "PLAN", "SHOW", "TEXT", "TIME",
  "VIEW", "WITH", "ADD", "ALL", "AND", "ASC", "CSV", "FOR", "INT", "KEY",
  "NOT", "OFF", "SET", "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF",
  "ON", "OR", "TO", "DATABASE", "USE", "CHECK", "SUM", "AVG", "MIN", "MAX",
  "'='", "EQUALS", "'<'", "'>'", "LESS", "GREATER", "NOTNULL", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'^'", "UMINUS", "'['", "']'", "'('", "')'",
  "'.'", "';'", "','", "$accept", "input", "statement_list", "statement",
  "createDB_statement", "DBname", "dropDB_statement", "useDB_statement",
  "showTable_statement", "create_statement", "opt_primary_key",
  "column_def_commalist", "column_def", "opt_size", "opt_not_null",
  "opt_check", "column_type", "drop_statement", "desc_statement",
  "insert_statement", "value_list", "delete_statement", "update_statement",
  "update_clause_commalist", "update_clause", "select_statement",
  "opt_distinct", "select_list", "select_opt", "opt_where", "opt_group",
  "opt_having", "opt_order", "opt_order_type", "createIndex_statement",
  "dropIndex_statement", "expr_list", "literal_list", "expr",
  "operator_expr", "comp_expr", "column_name", "literal", "string_literal",
  "num_literal", "int_literal", "star_expr", "table_name", "opt_semicolon",
  "ident_commalist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,    61,   383,
      60,    62,   384,   385,   386,    43,    45,    42,    47,    37,
      94,   387,    91,    93,    40,    41,    46,    59,    44
};
# endif

#define YYPACT_NINF -126

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-126)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     125,   -38,   -14,   -46,    33,    63,    63,   -34,    21,    73,
      84,   -51,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,    63,    63,    73,    63,
      63,  -126,    29,   -55,     2,  -126,    63,    63,    73,  -126,
    -126,  -126,  -126,   125,  -126,   -23,   -22,  -126,    57,   -39,
     -12,    -4,    -3,    -2,     4,  -126,   -62,  -126,  -126,  -126,
     143,   146,     6,  -126,  -126,  -126,   161,   162,    -1,  -126,
      23,   170,   171,   175,   175,   175,   175,   170,    44,  -126,
      51,   -60,  -126,   181,    40,     9,   -16,  -126,  -126,  -126,
    -126,  -126,    -1,     8,    -1,   129,   -56,    71,  -126,  -126,
    -126,  -126,    18,    42,  -126,   -95,  -126,    48,    49,    50,
      52,   -59,  -126,     8,   146,  -126,    55,  -126,  -126,  -126,
    -126,  -126,    58,    90,    25,    61,  -126,     8,    20,  -126,
      94,   -68,     8,     8,     8,     8,   118,    66,     8,     8,
       8,     8,     8,     8,     8,     8,     8,    -1,    -1,   120,
     -63,  -126,    68,   155,   211,  -126,  -126,  -126,  -126,   154,
     -66,  -126,  -126,   214,   114,    79,   121,  -126,  -126,   113,
    -126,  -126,   -66,   -66,   -66,   -66,     8,    18,   -66,   -66,
     -66,    20,    20,    86,    86,    86,  -126,  -126,   127,  -126,
    -126,    18,    18,    23,  -126,   122,   167,    93,   149,   119,
     238,    99,   -66,   -53,  -126,   -48,    42,     3,   132,  -126,
    -126,  -126,    -1,  -126,   101,   251,  -126,  -126,     3,   -35,
    -126,   129,   -56,     3,   -56,  -126,   110,   111,    94,   -68,
       3,     3,  -126,   -41,  -126,  -126,  -126,  -126,  -126,  -126,
    -126
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,   119,     3,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,     0,
       0,    52,     0,   116,     0,    41,     0,     0,     0,    22,
      19,    21,     1,   118,     2,     0,     0,    18,    63,     0,
     106,     0,     0,     0,     0,   115,     0,    54,    57,    56,
       0,     0,     0,    40,    20,     4,     0,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
       0,    63,    48,     0,     0,     0,    26,    27,   111,   112,
     114,   110,     0,     0,     0,     0,    62,    90,    91,   108,
     109,   113,     0,    42,   120,     0,   107,     0,     0,     0,
       0,    63,    55,     0,     0,    47,     0,    73,    37,    38,
      39,    36,    31,     0,     0,     0,    93,     0,    83,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,     0,     0,     0,    58,    59,    61,    60,    65,
      50,    49,    74,     0,    33,     0,     0,    28,    23,     0,
      82,    92,    96,    99,   100,   103,     0,     0,    95,    97,
      98,    85,    84,    87,    86,    88,    89,   101,   102,    94,
      44,     0,     0,     0,   121,     0,    69,     0,     0,    35,
       0,     0,   104,     0,    78,     0,    43,     0,     0,    51,
      30,    32,     0,    29,     0,     0,   105,    45,     0,    67,
      75,    80,    81,     0,    34,    25,     0,     0,     0,     0,
       0,     0,    64,    72,    24,    79,    66,    76,    71,    70,
      68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,   218,  -126,    -7,  -126,  -126,  -126,  -126,
    -126,  -126,   138,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
      70,  -126,  -126,  -126,   156,  -126,  -126,  -126,   193,   -52,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -125,   -42,   -15,
     -67,   -32,   -84,  -126,  -126,  -126,  -126,    28,  -126,   195
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    41,    14,    15,    16,    17,
     125,    86,    87,   164,   199,   213,   122,    18,    19,    20,
     103,    21,    22,    81,    82,    23,    32,    56,    57,    69,
     196,   232,   209,   240,    24,    25,   219,   150,   220,    95,
     222,   129,    98,    99,   100,   101,    59,    34,    44,   105
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    96,    50,    88,    89,    90,    50,    88,    89,    90,
     230,    50,    88,    89,    90,   123,    68,    68,   151,    70,
      77,    47,    88,    89,    90,   126,    26,   131,    85,   115,
      36,    64,    50,   147,    35,    27,    97,   118,   238,    37,
      30,   107,   108,   109,   110,   147,    58,    50,    31,   119,
     153,   148,   203,   154,    45,    46,   166,    48,    49,   159,
      97,   239,    97,   148,    62,    63,    33,   205,    29,   141,
     142,   143,   144,   145,   146,    39,    40,   171,   128,   130,
     187,   188,   190,    28,    42,   191,    78,    38,   114,   154,
      91,    60,   216,   151,    91,   191,    43,   217,   160,    91,
     191,   132,   133,   134,   120,    71,    92,   204,   151,    91,
      92,    61,   169,   231,   121,    97,    97,   172,   173,   174,
     175,    66,    67,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   124,    68,    72,    93,   132,   133,   134,    93,
      73,    74,    75,    94,    93,   224,    79,   218,    76,    80,
      83,   229,   127,    51,    52,    53,    54,   143,   144,   145,
     146,   202,     1,     2,    84,    85,    55,   102,    51,    52,
      53,    54,     3,   104,   106,    97,   227,     4,    50,   113,
      97,   233,     5,   135,   116,   117,    97,   149,   236,   237,
     152,    97,   221,   155,   156,   157,   165,   158,    97,    97,
     162,   136,   163,   228,     6,     7,   168,   176,   221,   137,
     177,   189,   192,   193,   194,   221,   221,   195,   135,     8,
     197,   198,   138,   200,   139,   140,   146,   201,   147,   141,
     142,   143,   144,   145,   146,   207,   136,   208,   210,   170,
     211,   214,   212,   215,   137,   223,   225,     9,   141,   142,
     143,   144,   145,   146,   226,   234,   235,   138,   170,   139,
     140,    65,   167,   206,   141,   142,   143,   144,   145,   146,
     161,   112,   111
};

static const yytype_uint8 yycheck[] =
{
      32,    68,     3,     4,     5,     6,     3,     4,     5,     6,
      45,     3,     4,     5,     6,    31,    76,    76,   102,    58,
      82,    28,     4,     5,     6,    92,    64,    94,     3,    81,
      64,    38,     3,   101,     6,    73,    68,    28,    79,    73,
      86,    73,    74,    75,    76,   101,    78,     3,    15,    40,
     145,   119,   177,   148,    26,    27,    31,    29,    30,   111,
      92,   102,    94,   119,    36,    37,     3,   192,    82,   135,
     136,   137,   138,   139,   140,    54,     3,   145,    93,    94,
     147,   148,   145,   121,     0,   148,   148,   121,   148,   148,
      91,   146,   145,   177,    91,   148,   147,   145,   113,    91,
     148,     7,     8,     9,    95,   144,   107,   191,   192,    91,
     107,   109,   127,   148,   105,   147,   148,   132,   133,   134,
     135,   144,   144,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   148,    76,   146,   136,     7,     8,     9,   136,
     144,   144,   144,   144,   136,   212,     3,   144,   144,     3,
     144,   218,   144,   124,   125,   126,   127,   137,   138,   139,
     140,   176,    37,    38,     3,     3,   137,   144,   124,   125,
     126,   127,    47,     3,     3,   207,   218,    52,     3,   128,
     212,   223,    57,    89,     3,   145,   218,   116,   230,   231,
     148,   223,   207,   145,   145,   145,   106,   145,   230,   231,
     145,   107,   144,   218,    79,    80,   145,    89,   223,   115,
     144,    91,   144,    58,     3,   230,   231,    63,    89,    94,
       6,   107,   128,   144,   130,   131,   140,   106,   101,   135,
     136,   137,   138,   139,   140,   113,   107,    70,   145,   145,
      91,     3,   123,   144,   115,   113,   145,   122,   135,   136,
     137,   138,   139,   140,     3,   145,   145,   128,   145,   130,
     131,    43,   124,   193,   135,   136,   137,   138,   139,   140,
     114,    78,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    47,    52,    57,    79,    80,    94,   122,
     150,   151,   152,   153,   155,   156,   157,   158,   166,   167,
     168,   170,   171,   174,   183,   184,    64,    73,   121,    82,
      86,    15,   175,     3,   196,   196,    64,    73,   121,    54,
       3,   154,     0,   147,   197,   196,   196,   154,   196,   196,
       3,   124,   125,   126,   127,   137,   176,   177,   190,   195,
     146,   109,   196,   196,   154,   152,   144,   144,    76,   178,
      58,   144,   146,   144,   144,   144,   144,    82,   148,     3,
       3,   172,   173,   144,     3,     3,   160,   161,     4,     5,
       6,    91,   107,   136,   144,   188,   189,   190,   191,   192,
     193,   194,   144,   169,     3,   198,     3,   190,   190,   190,
     190,   198,   177,   128,   148,   178,     3,   145,    28,    40,
      95,   105,   165,    31,   148,   159,   189,   144,   188,   190,
     188,   189,     7,     8,     9,    89,   107,   115,   128,   130,
     131,   135,   136,   137,   138,   139,   140,   101,   119,   116,
     186,   191,   148,   145,   148,   145,   145,   145,   145,   178,
     188,   173,   145,   144,   162,   106,    31,   161,   145,   188,
     145,   145,   188,   188,   188,   188,    89,   144,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   189,   189,    91,
     145,   148,   144,    58,     3,    63,   179,     6,   107,   163,
     144,   106,   188,   186,   191,   186,   169,   113,    70,   181,
     145,    91,   123,   164,     3,   144,   145,   145,   144,   185,
     187,   188,   189,   113,   189,   145,     3,   187,   188,   189,
      45,   148,   180,   187,   145,   145,   187,   187,    79,   102,
     182
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   149,   150,   151,   151,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   153,   154,
     155,   156,   157,   158,   159,   159,   159,   160,   160,   161,
     162,   162,   163,   163,   164,   164,   165,   165,   165,   165,
     166,   167,   168,   168,   169,   169,   170,   171,   172,   172,
     173,   174,   175,   175,   176,   176,   176,   177,   177,   177,
     177,   177,   178,   178,   179,   179,   180,   180,   181,   181,
     182,   182,   182,   183,   184,   185,   185,   186,   186,   187,
     187,   187,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   190,   190,   191,   191,
     191,   192,   193,   193,   194,   195,   196,   196,   197,   197,
     198,   198
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     2,     2,     7,     6,     5,     0,     1,     3,     5,
       3,     0,     2,     0,     2,     0,     1,     1,     1,     1,
       3,     2,     5,     8,     3,     5,     4,     5,     1,     3,
       3,     8,     1,     0,     1,     3,     1,     1,     4,     4,
       4,     4,     2,     0,     4,     0,     2,     0,     4,     0,
       1,     1,     0,     6,     6,     1,     3,     1,     3,     3,
       1,     1,     3,     2,     3,     3,     3,     3,     3,     3,
       1,     1,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if HSQL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLStatementList** result, yyscan_t scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLStatementList** result, yyscan_t scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, hsql::SQLStatementList** result, yyscan_t scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HSQL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HSQL_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, hsql::SQLStatementList** result, yyscan_t scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (hsql::SQLStatementList** result, yyscan_t scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 77 "bison_parser.y" /* yacc.c:1429  */
{
	// Initialize
	yylloc.first_column = 0;
	yylloc.last_column = 0;
	yylloc.first_line = 0;
	yylloc.last_line = 0;
	yylloc.total_column = 0;
	yylloc.placeholder_id = 0;
}

#line 1601 "bison_parser.cpp" /* yacc.c:1429  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 230 "bison_parser.y" /* yacc.c:1646  */
    {
			*result = (yyvsp[-1].stmt_list);
		}
#line 1792 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 237 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new SQLStatementList((yyvsp[0].statement)); }
#line 1798 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 238 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1804 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 242 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createDB_stmt); }
#line 1810 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 243 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropDB_stmt); }
#line 1816 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 244 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].useDB_stmt); }
#line 1822 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 245 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].showTable_stmt); }
#line 1828 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 246 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].create_stmt); }
#line 1834 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 247 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].drop_stmt); }
#line 1840 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 248 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].desc_stmt); }
#line 1846 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 249 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].insert_stmt); }
#line 1852 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 250 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1858 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 251 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].update_stmt); }
#line 1864 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 252 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].select_stmt); }
#line 1870 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 253 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createIndex_stmt); }
#line 1876 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 254 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropIndex_stmt); }
#line 1882 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 262 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createDB_stmt) = new CreateDBStatement();
			(yyval.createDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 1891 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 276 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropDB_stmt) = new DropDBStatement();
			(yyval.dropDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 1900 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 287 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.useDB_stmt) = new UseDBStatement();
			(yyval.useDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 1909 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 298 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.showTable_stmt) = new ShowTableStatement();
		}
#line 1917 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 309 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement();
			(yyval.create_stmt)->table_name = (yyvsp[-4].sval);
			(yyval.create_stmt)->columns = (yyvsp[-2].column_vec);
			(yyval.create_stmt)->primary_key = (yyvsp[-1].sval);
		}
#line 1928 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 318 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 1934 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 319 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 1940 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 320 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 1946 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 324 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 1952 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 325 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 1958 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 329 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.column_t) = new ColumnDefinition((yyvsp[-4].sval), (ColumnDefinition::DataType) (yyvsp[-3].uval), (yyvsp[-2].ival), (yyvsp[-1].bval), (yyvsp[0].expr));
		}
#line 1966 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 335 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = (yyvsp[-1].ival); }
#line 1972 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 336 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = 20;}
#line 1978 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 339 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 1984 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 340 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false;}
#line 1990 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 343 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1996 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 344 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2002 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 348 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::INT; }
#line 2008 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 349 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::INT; }
#line 2014 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 350 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DOUBLE; }
#line 2020 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 351 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::STRING; }
#line 2026 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 360 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement();
			(yyval.drop_stmt)->table_name = (yyvsp[0].sval);
		}
#line 2035 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 372 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.desc_stmt) = new DescStatement();
			(yyval.desc_stmt)->table_name = (yyvsp[0].sval);
		}
#line 2044 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 385 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement();
			(yyval.insert_stmt)->table_name = (yyvsp[-2].sval);
			(yyval.insert_stmt)->value_list = (yyvsp[0].expr_vec_vec);
		}
#line 2054 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 390 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement();
			(yyval.insert_stmt)->table_name = (yyvsp[-5].sval);
			(yyval.insert_stmt)->keys = (yyvsp[-3].str_vec);
			(yyval.insert_stmt)->value_list = (yyvsp[0].expr_vec_vec); 			
		}
#line 2065 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 399 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec_vec) = new std::vector<std::vector<hsql::Expr*>*>(); (yyval.expr_vec_vec)->push_back((yyvsp[-1].expr_vec)); }
#line 2071 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 400 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].expr_vec_vec)->push_back((yyvsp[-1].expr_vec)); (yyval.expr_vec_vec) = (yyvsp[-4].expr_vec_vec); }
#line 2077 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 408 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->table_name = (yyvsp[-1].sval);
			(yyval.delete_stmt)->expr = (yyvsp[0].expr);
		}
#line 2087 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 422 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table_name = (yyvsp[-3].sval);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->where = (yyvsp[0].expr);
	}
#line 2098 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 431 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2104 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 432 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2110 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 436 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2120 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 460 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement();
			(yyval.select_stmt)->select_distinct = (yyvsp[-6].bval);
			(yyval.select_stmt)->select_list = (yyvsp[-5].expr_vec);
			//$$->from_table = $4;
			(yyval.select_stmt)->table_list = (yyvsp[-3].str_vec);
			(yyval.select_stmt)->where_expr = (yyvsp[-2].expr);
			(yyval.select_stmt)->group_by = (yyvsp[-1].group_t);
			(yyval.select_stmt)->order = (yyvsp[0].order);
		}
#line 2135 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 473 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2141 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 474 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2147 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 478 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2153 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 479 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2159 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 480 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2165 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 484 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2171 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 485 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeCalculate((yyvsp[-1].expr), Expr::SUM); }
#line 2177 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 486 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeCalculate((yyvsp[-1].expr), Expr::AVG); }
#line 2183 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 487 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeCalculate((yyvsp[-1].expr), Expr::MAX); }
#line 2189 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 488 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeCalculate((yyvsp[-1].expr), Expr::MIN); }
#line 2195 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 492 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2201 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 493 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2207 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 497 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2217 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 502 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2223 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 506 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2229 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 507 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2235 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 510 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2241 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 511 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2247 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 515 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2253 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 516 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2259 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 517 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2265 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 525 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createIndex_stmt) = new CreateIndexStatement();
			(yyval.createIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.createIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2275 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 537 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropIndex_stmt) = new DropIndexStatement();
			(yyval.dropIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.dropIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2285 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 548 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2291 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 549 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2297 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 553 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2303 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 554 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2309 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 558 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2315 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 564 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2321 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 565 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2327 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 566 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::MINUS, (yyvsp[0].expr)); }
#line 2333 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 567 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::ADD, (yyvsp[0].expr)); }
#line 2339 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 568 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::DIVIDE, (yyvsp[0].expr)); }
#line 2345 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 569 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::MULTIPLE, (yyvsp[0].expr)); }
#line 2351 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 570 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::MOD, (yyvsp[0].expr)); }
#line 2357 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 571 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::MI, (yyvsp[0].expr)); }
#line 2363 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 578 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2369 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 579 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolUnary(Expr::NOT, (yyvsp[0].expr)); }
#line 2375 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 580 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolUnary(Expr::ISNULL, (yyvsp[-2].expr)); }
#line 2381 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 581 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::EQUAL, (yyvsp[0].expr)); }
#line 2387 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 582 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::NOT_EQUAL, (yyvsp[0].expr)); }
#line 2393 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 583 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::LESS, (yyvsp[0].expr)); }
#line 2399 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 584 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::GREATER, (yyvsp[0].expr)); }
#line 2405 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 585 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2411 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 586 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2417 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 587 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::AND, (yyvsp[0].expr)); }
#line 2423 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 588 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2429 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 589 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2435 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 590 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2441 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 591 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeBoolBinary((yyvsp[-4].expr), Expr::IN, (yyvsp[-1].expr_vec)); }
#line 2447 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 595 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2453 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 596 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2459 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 602 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral(); }
#line 2465 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 606 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2471 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 611 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2477 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 616 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2483 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 620 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2489 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 644 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2495 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 645 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2501 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2505 "bison_parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, result, scanner, YY_("syntax error"));
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
        yyerror (&yylloc, result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, result, scanner);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, result, scanner);
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
  return yyresult;
}
#line 648 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

