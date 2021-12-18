/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/alfa.y"

    #include "alfa.h"
    #include "y.tab.h"
    #include "sym_t.h"
    #include "generacion.h"

    #include <stdio.h>
    #include <stdlib.h>

    /* Imprime err_msg si no se cumple la condicion cond */
    #define CHECK_ERROR(cond, err_msg) \
        F_BLOCK( \
            if(!(cond)){ \
            fprintf(alfa_utils_T.ferr, "[%s]: linea %d[%d] ERROR: %s\n", \
                    (alfa_utils_T.fin_name), \
                    (alfa_utils_T.line), \
                    (alfa_utils_T.col), \
                    (err_msg)); \
             YYABORT; \
            } \
        )

    #define TAM_ERRMSG 200
    
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
        return 1;
    }

    /* Para declaraciones */
    static Tipo tipo_actual;
    static Categoria clase_actual;
    static int ambito_actual;

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

#line 131 "src/alfa.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SRC_ALFA_TAB_H_INCLUDED
# define YY_YY_SRC_ALFA_TAB_H_INCLUDED
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
#line 62 "src/alfa.y"

    tipo_atributos atributos;

#line 235 "src/alfa.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_ALFA_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

#define YYUNDEFTOK  2
#define YYMAXUTOK   279


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
{
       0,   126,   126,   128,   134,   139,   151,   153,   154,   156,
     158,   162,   167,   169,   170,   172,   179,   180,   182,   183,
     185,   188,   189,   191,   192,   194,   199,   201,   202,   204,
     205,   207,   208,   210,   211,   212,   213,   215,   216,   218,
     242,   263,   265,   266,   269,   271,   295,   300,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   341,   342,   343,
     344,   345,   347,   348,   350,   351,   353,   354,   355,   356,
     357,   358,   360,   366,   372,   378,   385,   392,   398
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
  "resto_parametros_funcion", "idpf", "parametro_funcion",
  "declaraciones_funcion", "sentencias", "sentencia", "sentencia_simple",
  "bloque", "asignacion", "elemento_vector", "condicional", "bucle",
  "lectura", "escritura", "retorno_funcion", "exp", "lista_expresiones",
  "resto_lista_expresiones", "comparacion", "constante",
  "constante_logica", "constante_entera", "identificador_use",
  "identificador_new", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    33,    43,    45,    42,    47,
     123,   125,    59,    91,    93,    44,    40,    41,    61,    60,
      62
};
# endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   -18,    14,   -37,   -37,    12,   -37,   -37,    16,   -37,
      12,    15,   -37,   -37,   -37,     1,    29,   -37,   -37,     8,
       4,    24,    16,   -37,    29,   -37,    15,    10,    26,   149,
     -37,   -37,   -37,   -37,    25,    28,    32,    26,   131,   131,
     -37,   149,    30,   -37,   -37,    27,   -37,   -37,   -37,   -37,
     -37,   -27,    16,   131,   131,   -37,   -37,   -37,   -37,   131,
     131,   131,   -37,    52,   -37,   -37,   -37,   -29,    52,    17,
     -37,   -37,   131,   131,   131,    26,    33,    37,    23,   100,
      -2,     3,    73,    38,   131,   131,   131,   131,   131,   131,
     131,   -37,    52,   121,    52,   -37,   -37,    53,    16,   -37,
      54,    74,   131,   131,   131,   131,   -37,   131,   131,   -37,
      -2,    -2,     3,     3,   -37,   -37,   105,    45,   -37,    12,
      37,   149,   149,    52,    52,    52,    52,    52,    52,   131,
     -37,   -37,   -37,   149,   -37,    72,    75,   105,    86,   112,
     -37,   -37,   -37,    92,   149,    93,   -37
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,    13,    14,     0,     5,
       7,     0,    10,    12,    11,     0,    19,     8,    78,     0,
      16,     0,     0,     6,    19,     9,     0,     0,     0,     0,
      18,    17,    15,    77,     0,     0,     0,     0,     0,     0,
       4,    29,     0,    32,    33,     0,    37,    38,    34,    35,
      36,     0,    22,     0,     0,    45,    76,    74,    75,     0,
       0,     0,    60,    46,    57,    72,    73,    56,    47,     0,
      30,    31,     0,     0,     0,     0,     0,    24,     0,     0,
      55,    52,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     2,    40,     0,    39,    26,    25,     0,     0,    21,
       0,     0,     0,     0,     0,     0,    58,     0,     0,    59,
      53,    54,    48,    49,    51,    50,    65,     0,    41,    28,
      24,     0,     0,    66,    67,    68,    69,    70,    71,     0,
      62,    61,    27,     0,    23,     0,     0,    65,     0,    42,
      44,    64,    20,     0,     0,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,   -37,   -37,    -8,   -37,   -37,   -37,
      11,   -37,    97,   101,   -37,   -37,    18,   -37,    41,   -37,
     -36,   -37,   -37,   -37,   -37,   -26,   -37,   -37,   -37,   -37,
     -37,   -31,   -37,    -7,   -37,   -37,   -37,   -37,   -28,   -37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    69,    16,    29,     9,    10,    11,    12,
      13,    14,    19,    23,    24,    76,    99,    95,    77,   133,
      40,    41,    42,    43,    44,    62,    46,    47,    48,    49,
      50,    63,   117,   130,    83,    64,    65,    66,    67,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      34,    51,    17,    45,    73,    70,    73,    90,    68,    55,
       1,    74,     3,    51,     4,    45,     6,     7,     8,    15,
       6,     7,    78,    79,    86,    87,    88,    89,    80,    81,
      82,    88,    89,    28,    21,    18,    22,    84,    85,    26,
      25,    92,    93,    94,    32,    27,    33,    96,    91,    86,
      87,    88,    89,   110,   111,   112,   113,   114,   115,   116,
     100,    52,    71,    75,    53,    72,    84,    85,    54,    98,
      97,   123,   124,   125,   126,   109,   127,   128,    86,    87,
      88,    89,   131,   119,   121,   135,   136,    84,    85,   102,
     103,   104,   105,    51,    51,    45,    45,   138,   137,    86,
      87,    88,    89,   139,   122,    51,   140,    45,   145,    75,
     106,   132,   107,   108,    84,    85,    51,   142,    45,    84,
      85,   143,   144,    31,   146,    30,    86,    87,    88,    89,
     141,    86,    87,    88,    89,    84,    85,   101,   134,   120,
     129,     0,     0,     0,     0,     0,     0,    86,    87,    88,
      89,    33,    56,    57,    58,   118,    59,    35,    60,    36,
      37,    38,    39,     0,     0,     0,     0,    61,     0,    33
};

static const yytype_int16 yycheck[] =
{
      28,    29,    10,    29,    33,    41,    33,    36,    39,    37,
       3,    38,    30,    41,     0,    41,     4,     5,     6,     8,
       4,     5,    53,    54,    26,    27,    28,    29,    59,    60,
      61,    28,    29,    22,    33,    20,     7,    14,    15,    35,
      32,    72,    73,    74,    34,    21,    20,    75,    31,    26,
      27,    28,    29,    84,    85,    86,    87,    88,    89,    90,
      37,    36,    32,    52,    36,    38,    14,    15,    36,    32,
      37,   102,   103,   104,   105,    37,   107,   108,    26,    27,
      28,    29,    37,    30,    30,   121,   122,    14,    15,    16,
      17,    18,    19,   121,   122,   121,   122,   133,   129,    26,
      27,    28,    29,    31,    30,   133,    31,   133,   144,    98,
      37,   119,    39,    40,    14,    15,   144,    31,   144,    14,
      15,     9,    30,    26,    31,    24,    26,    27,    28,    29,
     137,    26,    27,    28,    29,    14,    15,    37,   120,    98,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    20,    21,    22,    23,    34,    25,     8,    27,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    36,    -1,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    42,    30,     0,    43,     4,     5,     6,    47,
      48,    49,    50,    51,    52,    51,    45,    47,    20,    53,
      80,    33,     7,    54,    55,    32,    35,    21,    51,    46,
      54,    53,    34,    20,    79,     8,    10,    11,    12,    13,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    79,    36,    36,    36,    79,    21,    22,    23,    25,
      27,    36,    66,    72,    76,    77,    78,    79,    72,    44,
      61,    32,    38,    33,    38,    51,    56,    59,    72,    72,
      72,    72,    72,    75,    14,    15,    26,    27,    28,    29,
      36,    31,    72,    72,    72,    58,    79,    37,    32,    57,
      37,    37,    16,    17,    18,    19,    37,    39,    40,    37,
      72,    72,    72,    72,    72,    72,    72,    73,    34,    30,
      59,    30,    30,    72,    72,    72,    72,    72,    72,    35,
      74,    37,    47,    60,    57,    61,    61,    72,    61,    31,
      31,    74,    31,     9,    30,    61,    31
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    44,    45,    46,    47,    47,    48,
      49,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    69,    70,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77,    78,    79,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    10,     0,     0,     0,     0,     1,     2,     3,
       1,     1,     1,     1,     1,     5,     1,     3,     2,     0,
      10,     2,     0,     3,     0,     1,     2,     1,     0,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     4,     7,    11,     7,     2,     2,     2,     3,     3,
       3,     3,     2,     3,     3,     2,     1,     1,     3,     3,
       1,     4,     2,     0,     3,     0,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 126 "src/alfa.y"
                                                                                               {P_RULE(1,"<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}
#line 1519 "src/alfa.tab.c"
    break;

  case 3:
#line 128 "src/alfa.y"
           {
                sym_t_create();
                escribir_subseccion_data(alfa_utils_T.fasm);
                escribir_cabecera_bss(alfa_utils_T.fasm);
            }
#line 1529 "src/alfa.tab.c"
    break;

  case 4:
#line 134 "src/alfa.y"
           {
                sym_t_free();
                escribir_fin(alfa_utils_T.fasm);
            }
#line 1538 "src/alfa.tab.c"
    break;

  case 5:
#line 139 "src/alfa.y"
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
#line 1554 "src/alfa.tab.c"
    break;

  case 6:
#line 151 "src/alfa.y"
            {   escribir_inicio_main(alfa_utils_T.fasm);}
#line 1560 "src/alfa.tab.c"
    break;

  case 7:
#line 153 "src/alfa.y"
                            {P_RULE(2,"<declaraciones> ::= <declaracion>");}
#line 1566 "src/alfa.tab.c"
    break;

  case 8:
#line 154 "src/alfa.y"
                                            {P_RULE(3,"<declaraciones> ::= <declaracion> <declaraciones>");}
#line 1572 "src/alfa.tab.c"
    break;

  case 9:
#line 156 "src/alfa.y"
                                        {P_RULE(4,"<declaracion> ::= <clase> <identificadores> ;");}
#line 1578 "src/alfa.tab.c"
    break;

  case 10:
#line 158 "src/alfa.y"
                      {
            P_RULE(5,"<clase> ::= <clase_escalar>");
            clase_actual = ESCALAR;
        }
#line 1587 "src/alfa.tab.c"
    break;

  case 11:
#line 162 "src/alfa.y"
                     {
          P_RULE(7,"<clase> ::= <clase_vector>");
          clase_actual = VECTOR;
        }
#line 1596 "src/alfa.tab.c"
    break;

  case 12:
#line 167 "src/alfa.y"
                     {P_RULE(9,"<clase_escalar> ::= <tipo>");}
#line 1602 "src/alfa.tab.c"
    break;

  case 13:
#line 169 "src/alfa.y"
               {P_RULE(10,"<tipo> ::= int"); tipo_actual = INT;}
#line 1608 "src/alfa.tab.c"
    break;

  case 14:
#line 170 "src/alfa.y"
                   {P_RULE(11,"<tipo> ::= boolean"); tipo_actual = BOOLEAN;}
#line 1614 "src/alfa.tab.c"
    break;

  case 15:
#line 172 "src/alfa.y"
                                                           {
        P_RULE(15,"<clase_vector> ::= array <tipo> [ constante_entera ]");
        tamanio_vector_actual = (yyvsp[-1].atributos).valor_entero;
        CHECK_ERROR(tamanio_vector_actual >= 1, "Tamaño de vector invalido");
        CHECK_ERROR(tamanio_vector_actual <= MAX_LONG_VECTOR, "Tamaño de vector invalido");
    }
#line 1625 "src/alfa.tab.c"
    break;

  case 16:
#line 179 "src/alfa.y"
                                    {P_RULE(18,"<identificadores> ::= <identificador>");}
#line 1631 "src/alfa.tab.c"
    break;

  case 17:
#line 180 "src/alfa.y"
                                                        {P_RULE(19,"<identificadores> ::= <identificador> , <identificadores>");}
#line 1637 "src/alfa.tab.c"
    break;

  case 18:
#line 182 "src/alfa.y"
                              {P_RULE(20,"<funciones> ::= <funcion> <funciones>");}
#line 1643 "src/alfa.tab.c"
    break;

  case 19:
#line 183 "src/alfa.y"
                         {P_RULE(21,"<funciones> ::=");}
#line 1649 "src/alfa.tab.c"
    break;

  case 20:
#line 186 "src/alfa.y"
        {P_RULE(22,"<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }");}
#line 1655 "src/alfa.tab.c"
    break;

  case 21:
#line 188 "src/alfa.y"
                                                                {P_RULE(23,"<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1661 "src/alfa.tab.c"
    break;

  case 22:
#line 189 "src/alfa.y"
                                  {P_RULE(24,"<parametros_funcion> ::=");}
#line 1667 "src/alfa.tab.c"
    break;

  case 23:
#line 191 "src/alfa.y"
                                                                          {P_RULE(25,"<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1673 "src/alfa.tab.c"
    break;

  case 24:
#line 192 "src/alfa.y"
                                        {P_RULE(26,"<resto_parametros_funcion> ::=");}
#line 1679 "src/alfa.tab.c"
    break;

  case 25:
#line 194 "src/alfa.y"
                         {
        (yyval.atributos) = (yyvsp[0].atributos);
        clase_actual = ESCALAR;
     }
#line 1688 "src/alfa.tab.c"
    break;

  case 26:
#line 199 "src/alfa.y"
                              {P_RULE(27,"<parametro_funcion> ::= <tipo> <identificador>");}
#line 1694 "src/alfa.tab.c"
    break;

  case 27:
#line 201 "src/alfa.y"
                                      {P_RULE(28,"<declaraciones_funcion> ::= <declaraciones>");}
#line 1700 "src/alfa.tab.c"
    break;

  case 28:
#line 202 "src/alfa.y"
                                     {P_RULE(29,"<declaraciones_funcion> ::=");}
#line 1706 "src/alfa.tab.c"
    break;

  case 29:
#line 204 "src/alfa.y"
                       {P_RULE(30,"<sentencias> ::= <sentencia>");}
#line 1712 "src/alfa.tab.c"
    break;

  case 30:
#line 205 "src/alfa.y"
                                  {P_RULE(31,"<sentencias> ::= <sentencia> <sentencias>");}
#line 1718 "src/alfa.tab.c"
    break;

  case 31:
#line 207 "src/alfa.y"
                                 {P_RULE(32,"<sentencia> ::= <sentencia_simple> ;");}
#line 1724 "src/alfa.tab.c"
    break;

  case 32:
#line 208 "src/alfa.y"
                   {P_RULE(33,"<sentencia> ::= <bloque>");}
#line 1730 "src/alfa.tab.c"
    break;

  case 33:
#line 210 "src/alfa.y"
                              {P_RULE(34,"<sentencia_simple> ::= <asignacion>");}
#line 1736 "src/alfa.tab.c"
    break;

  case 34:
#line 211 "src/alfa.y"
                           {P_RULE(35,"<sentencia_simple> ::= <lectura>");}
#line 1742 "src/alfa.tab.c"
    break;

  case 35:
#line 212 "src/alfa.y"
                             {P_RULE(36,"<sentencia_simple> ::= <escritura>");}
#line 1748 "src/alfa.tab.c"
    break;

  case 36:
#line 213 "src/alfa.y"
                                   {P_RULE(38,"<sentencia_simple> ::= <retorno_funcion>");}
#line 1754 "src/alfa.tab.c"
    break;

  case 37:
#line 215 "src/alfa.y"
                     {P_RULE(40,"<bloque> ::= <condicional>");}
#line 1760 "src/alfa.tab.c"
    break;

  case 38:
#line 216 "src/alfa.y"
               {P_RULE(41,"<bloque> ::= <bucle>");}
#line 1766 "src/alfa.tab.c"
    break;

  case 39:
#line 218 "src/alfa.y"
                                        {
                char err_msg[TAM_ERRMSG] = "";
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
#line 1795 "src/alfa.tab.c"
    break;

  case 40:
#line 242 "src/alfa.y"
                                      {
                sym_info* sym = NULL;
                char err_msg[TAM_ERRMSG] = "";
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
#line 1820 "src/alfa.tab.c"
    break;

  case 41:
#line 263 "src/alfa.y"
                                                {P_RULE(48,"<elemento_vector> ::= identificador [ <exp> ]");}
#line 1826 "src/alfa.tab.c"
    break;

  case 42:
#line 265 "src/alfa.y"
                                                    {P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");}
#line 1832 "src/alfa.tab.c"
    break;

  case 43:
#line 267 "src/alfa.y"
                {P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");}
#line 1838 "src/alfa.tab.c"
    break;

  case 44:
#line 269 "src/alfa.y"
                                                 {P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");}
#line 1844 "src/alfa.tab.c"
    break;

  case 45:
#line 271 "src/alfa.y"
                                      {
            char err_msg[TAM_ERRMSG] = "";
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
#line 1872 "src/alfa.tab.c"
    break;

  case 46:
#line 295 "src/alfa.y"
                           {
                P_RULE(56,"<escritura> ::= printf <exp>");
                escribir(alfa_utils_T.fasm, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
          }
#line 1881 "src/alfa.tab.c"
    break;

  case 47:
#line 300 "src/alfa.y"
                                 {P_RULE(61,"<retorno_funcion> ::= return <exp>");}
#line 1887 "src/alfa.tab.c"
    break;

  case 48:
#line 302 "src/alfa.y"
                  {P_RULE(72,"<exp> ::= <exp> + <exp>");}
#line 1893 "src/alfa.tab.c"
    break;

  case 49:
#line 303 "src/alfa.y"
                  {P_RULE(73,"<exp> ::= <exp> - <exp>");}
#line 1899 "src/alfa.tab.c"
    break;

  case 50:
#line 304 "src/alfa.y"
                  {P_RULE(74,"<exp> ::= <exp> / <exp>");}
#line 1905 "src/alfa.tab.c"
    break;

  case 51:
#line 305 "src/alfa.y"
                  {P_RULE(75,"<exp> ::= <exp> * <exp>");}
#line 1911 "src/alfa.tab.c"
    break;

  case 52:
#line 306 "src/alfa.y"
              {P_RULE(76,"<exp> ::= - <exp>");}
#line 1917 "src/alfa.tab.c"
    break;

  case 53:
#line 307 "src/alfa.y"
                      {P_RULE(77,"<exp> ::= <exp> && <exp>");}
#line 1923 "src/alfa.tab.c"
    break;

  case 54:
#line 308 "src/alfa.y"
                     {P_RULE(78,"<exp> ::= <exp> || <exp>");}
#line 1929 "src/alfa.tab.c"
    break;

  case 55:
#line 309 "src/alfa.y"
              {P_RULE(79,"<exp> ::= ! <exp>");}
#line 1935 "src/alfa.tab.c"
    break;

  case 56:
#line 310 "src/alfa.y"
                        {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;

        P_RULE(80,"<exp> ::= identificador");

        sprintf(err_msg, "Identificador [%s] duplicado", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym_t_check((yyvsp[0].atributos).lexema) != NULL, err_msg);

        sym=sym_info_create((yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, -1, -1);
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
#line 1971 "src/alfa.tab.c"
    break;

  case 57:
#line 341 "src/alfa.y"
                {P_RULE(81,"<exp> ::= <constante>");}
#line 1977 "src/alfa.tab.c"
    break;

  case 58:
#line 342 "src/alfa.y"
                  {P_RULE(82,"<exp> ::= ( <exp> )");}
#line 1983 "src/alfa.tab.c"
    break;

  case 59:
#line 343 "src/alfa.y"
                          {P_RULE(83,"<exp> ::= ( <comparacion> )");}
#line 1989 "src/alfa.tab.c"
    break;

  case 60:
#line 344 "src/alfa.y"
                      {P_RULE(85,"<exp> ::= <elemento_vector>");}
#line 1995 "src/alfa.tab.c"
    break;

  case 61:
#line 345 "src/alfa.y"
                                                  {P_RULE(88,"<identificador> ( <lista_expresiones> )");}
#line 2001 "src/alfa.tab.c"
    break;

  case 62:
#line 347 "src/alfa.y"
                                                {P_RULE(89,"<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
#line 2007 "src/alfa.tab.c"
    break;

  case 63:
#line 348 "src/alfa.y"
                                 {P_RULE(90,"<lista_expresiones> ::=");}
#line 2013 "src/alfa.tab.c"
    break;

  case 64:
#line 350 "src/alfa.y"
                                                          {P_RULE(91,"<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>");}
#line 2019 "src/alfa.tab.c"
    break;

  case 65:
#line 351 "src/alfa.y"
                                       {P_RULE(92,"<resto_lista_expresiones> ::=");}
#line 2025 "src/alfa.tab.c"
    break;

  case 66:
#line 353 "src/alfa.y"
                                {P_RULE(93,"<comparacion> ::= <exp> == <exp>");}
#line 2031 "src/alfa.tab.c"
    break;

  case 67:
#line 354 "src/alfa.y"
                                   {P_RULE(94,"<comparacion> ::= <exp> != <exp>");}
#line 2037 "src/alfa.tab.c"
    break;

  case 68:
#line 355 "src/alfa.y"
                                     {P_RULE(95,"<comparacion> ::= <exp> <= <exp>");}
#line 2043 "src/alfa.tab.c"
    break;

  case 69:
#line 356 "src/alfa.y"
                                     {P_RULE(96,"<comparacion> ::= <exp> >= <exp>");}
#line 2049 "src/alfa.tab.c"
    break;

  case 70:
#line 357 "src/alfa.y"
                          {P_RULE(97,"<comparacion> ::= <exp> < <exp>");}
#line 2055 "src/alfa.tab.c"
    break;

  case 71:
#line 358 "src/alfa.y"
                          {P_RULE(98,"<comparacion> ::= <exp> > <exp>");}
#line 2061 "src/alfa.tab.c"
    break;

  case 72:
#line 360 "src/alfa.y"
                             {
                P_RULE(99,"<constante> ::= <constante_logica>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 2072 "src/alfa.tab.c"
    break;

  case 73:
#line 366 "src/alfa.y"
                             {
                P_RULE(100,"<comparacion> ::= <constante_entera>");
                (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
                (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
            }
#line 2082 "src/alfa.tab.c"
    break;

  case 74:
#line 372 "src/alfa.y"
                            {
                        P_RULE(102,"<constante_logica> ::= true");
                        (yyval.atributos).tipo = BOOLEAN;
                        (yyval.atributos).valor_entero = 1;
                        (yyval.atributos).es_direccion = 0;
                    }
#line 2093 "src/alfa.tab.c"
    break;

  case 75:
#line 378 "src/alfa.y"
                             {
                        P_RULE(103,"<constante_logica> ::= false");
                        (yyval.atributos).tipo = BOOLEAN;
                        (yyval.atributos).valor_entero = 0;
                        (yyval.atributos).es_direccion = 0;
                    }
#line 2104 "src/alfa.tab.c"
    break;

  case 76:
#line 385 "src/alfa.y"
                                        {
                        P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");
                        (yyval.atributos).tipo = INT;
                        (yyval.atributos).es_direccion = 0;
                        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
                    }
#line 2115 "src/alfa.tab.c"
    break;

  case 77:
#line 393 "src/alfa.y"
                {
                    P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
                    (yyval.atributos) = (yyvsp[0].atributos);
                }
#line 2124 "src/alfa.tab.c"
    break;

  case 78:
#line 398 "src/alfa.y"
                                      {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;
        P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        sprintf(err_msg, "Identificador [%s] duplicado", (yyvsp[0].atributos).lexema);
        CHECK_ERROR(sym_t_check((yyvsp[0].atributos).lexema) == NULL, err_msg);
        
        /*si llega a aqui el check error lo permite*/
        sym=sym_info_create((yyvsp[0].atributos).lexema, VARIABLE, tipo_actual, clase_actual, -1, -1);
        CHECK_ERROR(sym, "Sin memoria");
        
        sym_t_add_symb(sym); /*insertas el símbolo donde toque (global o local, de eso se encarga la tabla)*/
        declarar_variable(alfa_utils_T.fasm, sym->lexema, sym->tipo, sym->size);
        pos_variable_local_actual++;
    }
#line 2144 "src/alfa.tab.c"
    break;


#line 2148 "src/alfa.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 414 "src/alfa.y"
