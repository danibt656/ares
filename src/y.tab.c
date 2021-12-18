/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/alfa.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include "include/alfa.h"
    #include "include/sym_t.h"
    #include "include/generacion.h"

    /* Imprime err_msg si no se cumple la condicion cond */
    #define CHECK_ERROR(cond, err_msg) \
        F_BLOCK( \
            if(!cond) \
            fprintf(alfa_utils_T.ferr, "[%s]: linea %d[%d] ERROR: %s\n", \
                    (alfa_utils_T.fin_name), \
                    (alfa_utils_T.line), \
                    (alfa_utils_T.col), \
                    (err_msg)); \
             YYABORT; \
        )
    
    /* Imprime regla gramatical en un fichero de debug */
    #define P_RULE(n, msg) \
        F_BLOCK( \
            fprintf(alfa_utils_T.fdbg, ";R%d:\t%s\n", (n), (msg)); \
        )

    int yyerror(char *s)
    {
        /* Si imprime un error morfologico, no debe imprimir uno sintactico */
        if (alfa_utils_T.error == ERR_MORFOLOGICO)
            return 0;

        alfa_utils_T.error = ERR_SINTACTICO;
        manage_error(NULL, NULL);
    }

    /* Para declaraciones */
    static Tipo tipo_actual;
    static Categoria clase_actual;

    /* Para vectores */
    static int tamanio_vector_actual = 0;

    /* Etiquetas */
    static int etiqueta = 1;

    /* Funciones */
    static int pos_parametro_actual = -1;
    static int num_parametros_actual = 0;
    static int num_variables_locales_actual = 0;
	static int pos_variable_local_actual = 1;
	static int fn_return = 0;
	static int en_explist = 0;

#line 120 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_MAIN = 258,
    TOK_INT = 259,
    TOK_BOOLEAN = 260,
    TOK_ARRAY = 261,
    TOK_FUNCTION = 262,
    TOK_IF = 263,
    TOK_ELSE = 264,
    TOK_WHILE = 265,
    TOK_SCANF = 266,
    TOK_PRINTF = 267,
    TOK_RETURN = 268,
    TOK_AND = 269,
    TOK_OR = 270,
    TOK_IGUAL = 271,
    TOK_DISTINTO = 272,
    TOK_MENORIGUAL = 273,
    TOK_MAYORIGUAL = 274,
    TOK_IDENTIFICADOR = 275,
    TOK_CONSTANTE_ENTERA = 276,
    TOK_TRUE = 277,
    TOK_FALSE = 278,
    TOK_ERROR = 279
  };
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_INT 259
#define TOK_BOOLEAN 260
#define TOK_ARRAY 261
#define TOK_FUNCTION 262
#define TOK_IF 263
#define TOK_ELSE 264
#define TOK_WHILE 265
#define TOK_SCANF 266
#define TOK_PRINTF 267
#define TOK_RETURN 268
#define TOK_AND 269
#define TOK_OR 270
#define TOK_IGUAL 271
#define TOK_DISTINTO 272
#define TOK_MENORIGUAL 273
#define TOK_MAYORIGUAL 274
#define TOK_IDENTIFICADOR 275
#define TOK_CONSTANTE_ENTERA 276
#define TOK_TRUE 277
#define TOK_FALSE 278
#define TOK_ERROR 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "src/alfa.y" /* yacc.c:355  */

    tipo_atributos_1 atributos;

#line 212 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 229 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,     2,     2,     2,
      36,    37,    28,    26,    35,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      39,    38,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   121,   127,   132,   145,   147,   148,   150,
     152,   153,   155,   157,   158,   160,   167,   168,   170,   171,
     173,   176,   177,   179,   180,   182,   184,   185,   187,   188,
     190,   191,   193,   194,   195,   196,   198,   199,   201,   225,
     246,   248,   249,   252,   254,   278,   283,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   324,   325,   326,   327,
     328,   330,   331,   333,   334,   336,   337,   338,   339,   340,
     341,   343,   349,   355,   361,   368,   375
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_AND", "TOK_OR",
  "TOK_IGUAL", "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL",
  "TOK_IDENTIFICADOR", "TOK_CONSTANTE_ENTERA", "TOK_TRUE", "TOK_FALSE",
  "TOK_ERROR", "'!'", "'+'", "'-'", "'*'", "'/'", "'{'", "'}'", "';'",
  "'['", "']'", "','", "'('", "')'", "'='", "'<'", "'>'", "$accept",
  "programa", "iniciar", "final", "dec_vars", "wrt_main", "declaraciones",
  "declaracion", "clase", "clase_escalar", "tipo", "clase_vector",
  "identificadores", "funciones", "funcion", "parametros_funcion",
  "resto_parametros_funcion", "parametro_funcion", "declaraciones_funcion",
  "sentencias", "sentencia", "sentencia_simple", "bloque", "asignacion",
  "elemento_vector", "condicional", "bucle", "lectura", "escritura",
  "retorno_funcion", "exp", "lista_expresiones", "resto_lista_expresiones",
  "comparacion", "constante", "constante_logica", "constante_entera",
  "identificador", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    33,    43,    45,    42,    47,
     123,   125,    59,    91,    93,    44,    40,    41,    61,    60,
      62
};
# endif

#define YYPACT_NINF -40

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define YYTABLE_NINF -77

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -25,    11,   -40,   -40,    28,   -40,   -40,    10,   -40,
      28,     1,   -40,   -40,   -40,   -10,    40,   -40,   -40,    16,
      26,    41,    10,   -40,    40,   -40,     1,    29,     1,   147,
     -40,   -40,   -40,    44,    47,    48,    45,   111,   111,   -30,
     -40,   147,    32,   -40,   -40,    52,   -40,   -40,   -40,   -40,
     -40,    10,   111,   111,   -40,   -23,   -40,   -40,   -40,   111,
     111,   111,   -40,   125,   -40,   -40,   -40,    49,   125,   111,
     111,    65,   -40,   -40,   111,     1,    61,    69,     2,    91,
      15,     9,    60,    70,   111,   111,   111,   111,   111,   111,
     111,    96,   125,   -40,   125,   -40,    72,    10,   -40,    78,
      82,   111,   111,   111,   111,   -40,   111,   111,   -40,    15,
      15,     9,     9,   -40,   -40,    31,    76,   -40,    28,    69,
     147,   147,   125,   125,   125,   125,   125,   125,   111,   -40,
     -40,   -40,   147,   -40,    84,    85,    31,    90,   117,   -40,
     -40,   -40,    97,   147,    98,   -40
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,    13,    14,     0,     5,
       7,     0,    10,    12,    11,     0,    19,     8,    76,     0,
      16,     0,     0,     6,    19,     9,     0,     0,     0,     0,
      18,    17,    15,     0,     0,     0,     0,     0,     0,     0,
       4,    28,     0,    31,    32,     0,    36,    37,    33,    34,
      35,    22,     0,     0,    44,    55,    75,    73,    74,     0,
       0,     0,    59,    45,    56,    71,    72,     0,    46,     0,
       0,     0,    29,    30,     0,     0,     0,    24,     0,     0,
      54,    51,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,    38,     2,    39,    25,     0,     0,    21,     0,
       0,     0,     0,     0,     0,    57,     0,     0,    58,    52,
      53,    47,    48,    50,    49,    64,     0,    40,    27,    24,
       0,     0,    65,    66,    67,    68,    69,    70,     0,    61,
      60,    26,     0,    23,     0,     0,    64,     0,    41,    43,
      63,    20,     0,     0,     0,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   -40,   -40,   -40,    -9,   -40,   -40,   -40,
      -2,   -40,   109,   113,   -40,   -40,    22,    46,   -40,   -39,
     -40,   -40,   -40,   -40,   -29,   -40,   -40,   -40,   -40,   -40,
     -34,   -40,     8,   -40,   -40,   -40,   -40,    -4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    71,    16,    29,     9,    10,    11,    12,
      13,    14,    19,    23,    24,    76,    98,    77,   132,    40,
      41,    42,    43,    44,    62,    46,    47,    48,    49,    50,
      63,   116,   129,    83,    64,    65,    66,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    17,    72,    69,    68,     3,    15,    20,    70,     1,
      69,     4,    45,   -76,     6,     7,    84,    85,    78,    79,
      28,    18,    20,    21,    33,    80,    81,    82,    86,    87,
      88,    89,     6,     7,     8,    91,    92,    88,    89,    99,
      94,    86,    87,    88,    89,    84,    85,    22,    25,    75,
     109,   110,   111,   112,   113,   114,   115,    86,    87,    88,
      89,    26,    27,    32,    73,    54,   128,   122,   123,   124,
     125,    95,   126,   127,    84,    85,   101,   102,   103,   104,
      51,   134,   135,    52,    53,    90,    86,    87,    88,    89,
      74,    45,    45,   137,   136,    75,    93,   105,    96,   106,
     107,    97,   118,    45,   144,    84,    85,   108,   120,   131,
      84,    85,   121,   130,    45,   138,   139,    86,    87,    88,
      89,   141,    86,    87,    88,    89,   142,   143,   100,   145,
     117,    55,    56,    57,    58,    31,    59,    30,    60,    84,
      85,   133,     0,   119,   140,     0,     0,    61,     0,     0,
       0,    86,    87,    88,    89,    34,     0,    35,    36,    37,
      38,     0,     0,     0,     0,     0,     0,    39
};

static const yytype_int16 yycheck[] =
{
      29,    10,    41,    33,    38,    30,     8,    11,    38,     3,
      33,     0,    41,    36,     4,     5,    14,    15,    52,    53,
      22,    20,    26,    33,    28,    59,    60,    61,    26,    27,
      28,    29,     4,     5,     6,    69,    70,    28,    29,    37,
      74,    26,    27,    28,    29,    14,    15,     7,    32,    51,
      84,    85,    86,    87,    88,    89,    90,    26,    27,    28,
      29,    35,    21,    34,    32,    20,    35,   101,   102,   103,
     104,    75,   106,   107,    14,    15,    16,    17,    18,    19,
      36,   120,   121,    36,    36,    36,    26,    27,    28,    29,
      38,   120,   121,   132,   128,    97,    31,    37,    37,    39,
      40,    32,    30,   132,   143,    14,    15,    37,    30,   118,
      14,    15,    30,    37,   143,    31,    31,    26,    27,    28,
      29,    31,    26,    27,    28,    29,     9,    30,    37,    31,
      34,    20,    21,    22,    23,    26,    25,    24,    27,    14,
      15,   119,    -1,    97,   136,    -1,    -1,    36,    -1,    -1,
      -1,    26,    27,    28,    29,     8,    -1,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    42,    30,     0,    43,     4,     5,     6,    47,
      48,    49,    50,    51,    52,    51,    45,    47,    20,    53,
      78,    33,     7,    54,    55,    32,    35,    21,    51,    46,
      54,    53,    34,    78,     8,    10,    11,    12,    13,    20,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    36,    36,    36,    20,    20,    21,    22,    23,    25,
      27,    36,    65,    71,    75,    76,    77,    78,    71,    33,
      38,    44,    60,    32,    38,    51,    56,    58,    71,    71,
      71,    71,    71,    74,    14,    15,    26,    27,    28,    29,
      36,    71,    71,    31,    71,    78,    37,    32,    57,    37,
      37,    16,    17,    18,    19,    37,    39,    40,    37,    71,
      71,    71,    71,    71,    71,    71,    72,    34,    30,    58,
      30,    30,    71,    71,    71,    71,    71,    71,    35,    73,
      37,    47,    59,    57,    60,    60,    71,    60,    31,    31,
      73,    31,     9,    30,    60,    31
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    44,    45,    46,    47,    47,    48,
      49,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    68,    69,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     0,     0,     0,     0,     1,     2,     3,
       1,     1,     1,     1,     1,     5,     1,     3,     2,     0,
      10,     2,     0,     3,     0,     2,     1,     0,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       4,     7,    11,     7,     2,     2,     2,     3,     3,     3,
       3,     2,     3,     3,     2,     1,     1,     3,     3,     1,
       4,     2,     0,     3,     0,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 119 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(1,"<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}
#line 1415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 121 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_t_create();
                escribir_subseccion_data(alfa_utils_T.fasm);
                escribir_cabecera_bss(alfa_utils_T.fasm);
            }
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 127 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_t_free();
                escribir_fin(alfa_utils_T.fasm);
            }
#line 1434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 132 "src/alfa.y" /* yacc.c:1646  */
    {
                char** simbolos = sym_t_getGlobalSymbols();
                int i = 0;
                sym_info* sym = NULL;

                for (i = 0; simbolos[i] != NULL; i++) {
                    sym = sym_t_get_symb(simbolos[i]);
                    if (sym && VARIABLE == sym->elem)
                        declarar_variable(alfa_utils_T.fasm, sym->lexema, sym->tipo, sym->size);
                }
                escribir_segmento_codigo(alfa_utils_T.fasm);
            }
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 145 "src/alfa.y" /* yacc.c:1646  */
    {   escribir_inicio_main(alfa_utils_T.fasm);}
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 147 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(2,"<declaraciones> ::= <declaracion>");}
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 148 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(3,"<declaraciones> ::= <declaracion> <declaraciones>");}
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 150 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(4,"<declaracion> ::= <clase> <identificadores> ;");}
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(5,"<clase> ::= <clase_escalar>"); clase_actual = ESCALAR;}
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(7,"<clase> ::= <clase_vector>"); clase_actual = VECTOR;}
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 155 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(9,"<clase_escalar> ::= <tipo>");}
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 157 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(10,"<tipo> ::= int"); tipo_actual = ENTERO;}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 158 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(11,"<tipo> ::= boolean"); tipo_actual = BOOLEANO;}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 160 "src/alfa.y" /* yacc.c:1646  */
    {
        P_RULE(15,"<clase_vector> ::= array <tipo> [ constante_entera ]");
        tamanio_vector_actual = (yyvsp[-1].atributos).valor_entero;
        CHECK_ERROR(tamanio_vector_actual >= 1, "Tamaño de vector invalido");
        CHECK_ERROR(tamanio_vector_actual <= MAX_LONG_VECTOR, "Tamaño de vector invalido");
    }
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(18,"<identificadores> ::= <identificador>");}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 168 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(19,"<identificadores> ::= <identificador> , <identificadores>");}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 170 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(20,"<funciones> ::= <funcion> <funciones>");}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 171 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(21,"<funciones> ::=");}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(22,"<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }");}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 176 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(23,"<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 177 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(24,"<parametros_funcion> ::=");}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 179 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(25,"<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 180 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(26,"<resto_parametros_funcion> ::=");}
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 182 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(27,"<parametro_funcion> ::= <tipo> <identificador>");}
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 184 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(28,"<declaraciones_funcion> ::= <declaraciones>");}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 185 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(29,"<declaraciones_funcion> ::=");}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 187 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(30,"<sentencias> ::= <sentencia>");}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 188 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(31,"<sentencias> ::= <sentencia> <sentencias>");}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 190 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(32,"<sentencia> ::= <sentencia_simple> ;");}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 191 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(33,"<sentencia> ::= <bloque>");}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 193 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(34,"<sentencia_simple> ::= <asignacion>");}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 194 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(35,"<sentencia_simple> ::= <lectura>");}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 195 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(36,"<sentencia_simple> ::= <escritura>");}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 196 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(38,"<sentencia_simple> ::= <retorno_funcion>");}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 198 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(40,"<bloque> ::= <condicional>");}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 199 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(41,"<bloque> ::= <bucle>");}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 201 "src/alfa.y" /* yacc.c:1646  */
    {
                char err_msg[836] = "";
                sym_info* sym = NULL;
                P_RULE(43,"<asignacion> ::= identificador = <exp>");
                /* Comprueba que exista el identificador */
                sprintf(err_msg, "Identificador [%s] inexistente", (yyvsp[-2].atributos).lexema);
                sym = sym_t_get_symb((yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym, err_msg);

                /* Comprueba que no sea ni FUNCION ni VECTOR */
                sprintf(err_msg, "Identificador [%s] no es variable", (yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym->catg != VECTOR, err_msg);
                CHECK_ERROR(sym->elem != FUNCION, err_msg);

                /* Comprueba que el tipo sea el mismo */
                sprintf(err_msg, "Asignacion entre tipos distintos");
                CHECK_ERROR((yyvsp[0].atributos).tipo == sym->tipo, err_msg);

                /* Asignar */
                if (sym->is_var_loc!=-1) /*comprueba si es variable global*/
                    asignar(alfa_utils_T.fasm, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);
                else /*en caso contrario asigna destino en pila al ser local*/
                    asignarDestinoEnPila(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion);
            }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 225 "src/alfa.y" /* yacc.c:1646  */
    {
                sym_info* sym = NULL;
                char err_msg[129] = "";
                P_RULE(44,"<parametros_funcion> ::= <elemento_vector> = <exp>");

                /* Comprueba que exista el identificador */
                if((yyvsp[-2].atributos).lexema!=NULL)
                    sprintf(err_msg, "Identificador [%s] inexistente", (yyvsp[-2].atributos).lexema);
                else{
                    sprintf(err_msg, "Identificador nulo");
                }
                sym = sym_t_get_symb((yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym, err_msg);

                /* Comprueba que no sea FUNCION */
                sprintf(err_msg, "Identificador [%s] no es variable", (yyvsp[-2].atributos).lexema);
                CHECK_ERROR(sym->elem!=FUNCION, err_msg);

                escribir_elemento_vector(alfa_utils_T.fasm, (yyvsp[0].atributos).lexema, sym->size, sym->elem);
            }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 246 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(48,"<elemento_vector> ::= identificador [ <exp> ]");}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 248 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 250 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 252 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 254 "src/alfa.y" /* yacc.c:1646  */
    {
            char err_msg[130] = "";
            sym_info* info = sym_t_check((yyvsp[0].atributos).lexema);
            P_RULE(54,"<lectura> ::= scanf identificador"); 

            /* Buscar si el identificador existe */
            sprintf(err_msg, "Identificador [%s] no existe", (yyvsp[0].atributos).lexema);
            CHECK_ERROR(info, err_msg);

            /* Si el identificador existe */
            CHECK_ERROR((info->elem != FUNCION), "scanf no admite funciones como entrada");
            CHECK_ERROR((info->catg != VECTOR), "scanf no admite vectores como entrada");

            /* NASM: Apilar direccion de identificador */
            if (info->elem == PARAMETRO) {
                escribirParametro(alfa_utils_T.fasm, pos_parametro_actual, info->num_params);
            } else if (info->elem == VARIABLE && info->is_var_loc == 1) {
                escribirVariableLocal(alfa_utils_T.fasm, pos_variable_local_actual);
            }

            /* Llamar a scanf */
            leer(alfa_utils_T.fasm, info->lexema, info->tipo);
        }
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 278 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(56,"<escritura> ::= printf <exp>");
                escribir(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
          }
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 283 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(61,"<retorno_funcion> ::= return <exp>");}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(72,"<exp> ::= <exp> + <exp>");}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 286 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(73,"<exp> ::= <exp> - <exp>");}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 287 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(74,"<exp> ::= <exp> / <exp>");}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 288 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(75,"<exp> ::= <exp> * <exp>");}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 289 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(76,"<exp> ::= - <exp>");}
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 290 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(77,"<exp> ::= <exp> && <exp>");}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 291 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(78,"<exp> ::= <exp> || <exp>");}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 292 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(79,"<exp> ::= ! <exp>");}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 293 "src/alfa.y" /* yacc.c:1646  */
    {
        char err_msg[834] = "";
        sym_info* sym = NULL;

        P_RULE(80,"<exp> ::= identificador");

        sprintf(err_msg, "Identificador [%s] duplicado", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym_t_check((yyvsp[0].atributos).lexema), err_msg);

        sym=sym_info_create((yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, -1, -1)
        CHECK_ERROR(sym, "Sin memoria");

        /* Comprueba que no sea ni FUNCION ni VECTOR */
        sprintf(err_msg, "Identificador [%s] no es variable", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym->catg != VECTOR, err_msg);
        CHECK_ERROR(sym->elem != FUNCION, err_msg);

        /* Variable global */
        if (sym->elem == VARIABLE && !sym->is_var_loc) {
            escribir_operando(alfa_utils_T.fasm, (yyvsp[0].atributos).lexema, 1);
            (yyval.atributos).tipo = sym->tipo;
        /* Variable local */
        } else if (sym->elem == VARIABLE && sym->is_var_loc) {
            escribirVariableLocal(alfa_utils_T.fasm, pos_variable_local_actual);
            (yyval.atributos).tipo = sym->tipo;
        /* Parametro */
        } else if (sym->elem == PARAMETRO) {
            escribirParametro(alfa_utils_T.fasm, pos_parametro_actual, sym->num_params);
            (yyval.atributos).tipo = sym->tipo;
        }
      }
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 324 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(81,"<exp> ::= <constante>");}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 325 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(82,"<exp> ::= ( <exp> )");}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 326 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(83,"<exp> ::= ( <comparacion> )");}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 327 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(85,"<exp> ::= <elemento_vector>");}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 328 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(88,"<identificador> ( <lista_expresiones> )");}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 330 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(89,"<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 331 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(90,"<lista_expresiones> ::=");}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 333 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(91,"<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>");}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 334 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(92,"<resto_lista_expresiones> ::=");}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 336 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(93,"<comparacion> ::= <exp> == <exp>");}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 337 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(94,"<comparacion> ::= <exp> != <exp>");}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 338 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(95,"<comparacion> ::= <exp> <= <exp>");}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 339 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(96,"<comparacion> ::= <exp> >= <exp>");}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 340 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(97,"<comparacion> ::= <exp> < <exp>");}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 341 "src/alfa.y" /* yacc.c:1646  */
    {P_RULE(98,"<comparacion> ::= <exp> > <exp>");}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 343 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(99,"<constante> ::= <constante_logica>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 349 "src/alfa.y" /* yacc.c:1646  */
    {
                P_RULE(100,"<comparacion> ::= <constante_entera>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 355 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(102,"<constante_logica> ::= true");
                        (yyval.atributos).tipo = BOOLEANO;
                        (yyval.atributos).valor_entero = 1;
                        (yyval.atributos).es_direccion = 0;
                    }
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 361 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(103,"<constante_logica> ::= false");
                        (yyval.atributos).tipo = BOOLEANO;
                        (yyval.atributos).valor_entero = 0;
                        (yyval.atributos).es_direccion = 0;
                    }
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 368 "src/alfa.y" /* yacc.c:1646  */
    {
                        P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");
                        (yyval.atributos).tipo = ENTERO;
                        (yyval.atributos).es_direccion = 0;
                        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                    }
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 375 "src/alfa.y" /* yacc.c:1646  */
    {
        char err_msg[130] = "";
        sym_info* sym = NULL;
        P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        sprintf(err_msg, "Identificador [%s] duplicado", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym_t_check((yyvsp[0].atributos).lexema), err_msg);

        /*si llega a aqui el check error lo permite*/
        sym=sym_info_create((yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, -1, -1)
        CHECK_ERROR(sym, "Sin memoria");

        sym_t_add_symb(sym); /*insertas el símbolo donde toque (global o local, de eso se encarga la tabla)*/
        pos_variable_local_actual++;
    }
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2020 "y.tab.c" /* yacc.c:1646  */
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 390 "src/alfa.y" /* yacc.c:1906  */
