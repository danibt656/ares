#ifndef _TOKENS_H
#define _TOKENS_H 1


/* Palabras reservadas */
#define TOK_MAIN                100
#define TOK_INT                 101
#define TOK_BOOLEAN             102
#define TOK_ARRAY               103
#define TOK_FUNCTION            104
#define TOK_IF                  105
#define TOK_ELSE                106
#define TOK_WHILE               107
#define TOK_SCANF               108
#define TOK_PRINTF              109
#define TOK_RETURN              110
#define TOK_INIT                111
#define TOK_COMPARE             112
#define TOK_WITH                113
#define TOK_LESS                114
#define TOK_EQUAL               115
#define TOK_GREATER             116
#define TOK_DO                  117
#define TOK_LEN                 118
#define TOK_LOOP                119
#define TOK_IN                  120
#define TOK_TO                  121

/* Simbolos */
#define TOK_PUNTOYCOMA          200
#define TOK_COMA                201
#define TOK_PARENTESISIZQUIERDO 202
#define TOK_PARENTESISDERECHO   203
#define TOK_CORCHETEIZQUIERDO   204
#define TOK_CORCHETEDERECHO     205
#define TOK_LLAVEIZQUIERDA      206
#define TOK_LLAVEDERECHA        207
#define TOK_ASIGNACION          208
#define TOK_MAS                 209
#define TOK_MENOS               210
#define TOK_DIVISION            211
#define TOK_ASTERISCO           212
#define TOK_AND                 213
#define TOK_OR                  214
#define TOK_NOT                 215
#define TOK_IGUAL               216
#define TOK_DISTINTO            217
#define TOK_MENORIGUAL          218
#define TOK_MAYORIGUAL          219
#define TOK_MENOR               220
#define TOK_MAYOR               221
#define TOK_INCREMENTO          222
#define TOK_DECREMENTO          223
#define TOK_MODULO_VECTOR       224
#define TOK_AUTOSUMA            225
#define TOK_AUTORESTA           226
#define TOK_AUTOMULT            227
#define TOK_AUTODIV             228


/* Identificadores  */
#define TOK_IDENTIFICADOR       300

/* Constantes */

#define TOK_CONSTANTE_ENTERA    400
#define TOK_TRUE                401
#define TOK_FALSE               402
#define TOK_STRING              403

/* Errores */
#define TOK_ERROR                -1

#endif