%{
    #include "ares.h"
    #include "y.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    /* Imprime token en un fichero de debug */
    #define SHIFT() fprintf(ares_utils_T.fdbg, ";D:\t%s\n", yytext)

    /* Antes de cada regla, avanzamos el contador de columna */
    #define YY_USER_ACTION { ares_utils_T.col += yyleng; }
%}

/* SECCION DE DEFINICIONES */
/* Suprimir la accion por defecto de imprimir los caracteres que no encajan */
%option nodefault
/* Como solo leemos un fichero, esto nos evita tener que definir esta funcion */
%option noyywrap
/* No genera estas funciones y evita avisos al compilar */
%option nounput noinput

DIGITO [0-9]
LETRA [a-zA-Z]  
%%
    /* SECCION DE REGLAS */
    /* Define la creacion de tokens */

("//".*)    {  }    /* Comentarios */
("@".*)    {  }    /* Comentarios */
[ ]         {  }    /* Espacio */
[\t]        {  }    /* Tabulador */
[\n]        { ares_utils_T.line++; ares_utils_T.col = 1; }    /* Saltos de linea */

    /* Palabras reservadas */ 
begin       { SHIFT(); return TOK_MAIN; }
list        { SHIFT(); return TOK_ARRAY; }
proc        { SHIFT(); return TOK_FUNCTION; }
if          { SHIFT(); return TOK_IF; }
else        { SHIFT(); return TOK_ELSE; }
while       { SHIFT(); return TOK_WHILE; }
do          { SHIFT(); return TOK_DO; }
return      { SHIFT(); return TOK_RETURN; }
init        { SHIFT(); return TOK_INIT; }
compare     { SHIFT(); return TOK_COMPARE; }
with        { SHIFT(); return TOK_WITH; }
less        { SHIFT(); return TOK_LESS; }
equal       { SHIFT(); return TOK_EQUAL; }
greater     { SHIFT(); return TOK_GREATER; }
loop        { SHIFT(); return TOK_LOOP; }
in          { SHIFT(); return TOK_IN; }
to          { SHIFT(); return TOK_TO; }
    
    /* Tipos de datos */
i32         { SHIFT(); return TOK_INT; }
bool        { SHIFT(); return TOK_BOOLEAN; }

    /* Funciones del sistema */
output      { SHIFT(); return TOK_PRINTF; }
input       { SHIFT(); return TOK_SCANF; }
"len("      { SHIFT(); return TOK_LEN; }

    /* Simbolos */ 
";"         { SHIFT(); return yytext[0]; }
","         { SHIFT(); return yytext[0]; }
"("         { SHIFT(); return yytext[0]; }
")"         { SHIFT(); return yytext[0]; }
"["         { SHIFT(); return yytext[0]; }
"]"         { SHIFT(); return yytext[0]; }
"{"         { SHIFT(); return yytext[0]; } 
"}"         { SHIFT(); return yytext[0]; }
"="         { SHIFT(); return yytext[0]; }
"+"         { SHIFT(); return yytext[0]; }
"-"         { SHIFT(); return yytext[0]; }
"/"         { SHIFT(); return yytext[0]; }
"*"         { SHIFT(); return yytext[0]; }
"^"         { SHIFT(); return yytext[0]; }
"%"         { SHIFT(); return yytext[0]; }
"and"       { SHIFT(); return TOK_AND; }
"or"        { SHIFT(); return TOK_OR; }
"!"         { SHIFT(); return yytext[0]; }
"=="        { SHIFT(); return TOK_IGUAL; }
"!="        { SHIFT(); return TOK_DISTINTO; }
"<="        { SHIFT(); return TOK_MENORIGUAL; }
">="        { SHIFT(); return TOK_MAYORIGUAL; }
".%"        { SHIFT(); return TOK_MODULO_VECTOR; }
"<"         { SHIFT(); return yytext[0]; }
">"         { SHIFT(); return yytext[0]; }
"++"        { SHIFT(); return TOK_INCREMENTO; }
"--"        { SHIFT(); return TOK_DECREMENTO; }
"+="        { SHIFT(); return TOK_AUTOSUMA; }
"-="        { SHIFT(); return TOK_AUTORESTA; }
"*="        { SHIFT(); return TOK_AUTOMULT; }
"/="        { SHIFT(); return TOK_AUTODIV; }

    /* Constantes */
true        { SHIFT(); return TOK_TRUE; }
false       { SHIFT(); return TOK_FALSE; }
{DIGITO}+   { 
                #include "ares.h"
                SHIFT(); yylval.attributes.valor_entero = atoi(yytext); 
                return TOK_CONSTANTE_ENTERA; 
            }  
             
"\""({DIGITO}|{LETRA})*"\""   { 
                                        #include "ares.h"
                                        SHIFT();

                                        /* Error de longitud (sumamos 2 por las comillas) */
                                        if (yyleng > (MAX_LONG_ID + 2)) {
                                            ares_utils_T.col -= yyleng;
                                            ares_utils_T.error = ERR_MORFOLOGICO;
                                            manage_error("cadena con longitud superior a 100", NULL);
                                            return TOK_ERROR;
                                        }
                                        strcpy(yylval.attributes.valor_string, remove_quotes(yytext));
                                        return TOK_STRING;
                                    }

    /* Identificadores */
{LETRA}({DIGITO}|{LETRA})*  {
                                SHIFT();
                                /* Error de longitud */
                                if (yyleng > MAX_LONG_ID) {
                                    ares_utils_T.col -= yyleng;
                                    ares_utils_T.error = ERR_MORFOLOGICO;
                                    manage_error("identificador con longitud superior a 100", NULL);
                                    return TOK_ERROR;
                                }
                                strcpy(yylval.attributes.lexema, yytext);
                                return TOK_IDENTIFICADOR; 
                            }

    /* Error de simbolos no permitidos */
.         { ares_utils_T.col -= 1; ares_utils_T.error = ERR_MORFOLOGICO; manage_error("simbolo no permitido", yytext); return TOK_ERROR; }

%%
