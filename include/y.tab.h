/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
enum yytokentype {
    TOK_MAIN = 258,
    TOK_ARRAY = 259,
    TOK_FUNCTION = 260,
    TOK_IF = 261,
    TOK_ELSE = 262,
    TOK_WHILE = 263,
    TOK_RETURN = 264,
    TOK_INIT = 265,
    TOK_COMPARE = 266,
    TOK_WITH = 267,
    TOK_LESS = 268,
    TOK_EQUAL = 269,
    TOK_GREATER = 270,
    TOK_DO = 271,
    TOK_LOOP = 272,
    TOK_IN = 273,
    TOK_TO = 274,
    TOK_INT = 275,
    TOK_BOOLEAN = 276,
    TOK_SCANF = 277,
    TOK_PRINTF = 278,
    TOK_LEN = 279,
    TOK_AND = 280,
    TOK_OR = 281,
    TOK_IGUAL = 282,
    TOK_DISTINTO = 283,
    TOK_MENORIGUAL = 284,
    TOK_MAYORIGUAL = 285,
    TOK_MODULO_VECTOR = 286,
    TOK_INCREMENTO = 287,
    TOK_DECREMENTO = 288,
    TOK_AUTOSUMA = 289,
    TOK_AUTORESTA = 290,
    TOK_AUTOMULT = 291,
    TOK_AUTODIV = 292,
    TOK_IDENTIFICADOR = 293,
    TOK_CONSTANTE_ENTERA = 294,
    TOK_TRUE = 295,
    TOK_FALSE = 296,
    TOK_STRING = 297,
    TOK_ERROR = 298
};
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_ARRAY 259
#define TOK_FUNCTION 260
#define TOK_IF 261
#define TOK_ELSE 262
#define TOK_WHILE 263
#define TOK_RETURN 264
#define TOK_INIT 265
#define TOK_COMPARE 266
#define TOK_WITH 267
#define TOK_LESS 268
#define TOK_EQUAL 269
#define TOK_GREATER 270
#define TOK_DO 271
#define TOK_LOOP 272
#define TOK_IN 273
#define TOK_TO 274
#define TOK_INT 275
#define TOK_BOOLEAN 276
#define TOK_SCANF 277
#define TOK_PRINTF 278
#define TOK_LEN 279
#define TOK_AND 280
#define TOK_OR 281
#define TOK_IGUAL 282
#define TOK_DISTINTO 283
#define TOK_MENORIGUAL 284
#define TOK_MAYORIGUAL 285
#define TOK_MODULO_VECTOR 286
#define TOK_INCREMENTO 287
#define TOK_DECREMENTO 288
#define TOK_AUTOSUMA 289
#define TOK_AUTORESTA 290
#define TOK_AUTOMULT 291
#define TOK_AUTODIV 292
#define TOK_IDENTIFICADOR 293
#define TOK_CONSTANTE_ENTERA 294
#define TOK_TRUE 295
#define TOK_FALSE 296
#define TOK_STRING 297
#define TOK_ERROR 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 57 "ares.y"

    attribute_type attributes;

#line 109 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
