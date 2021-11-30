#ifndef ALFA_H
#define ALFA_H

#define MAX_LONG_ID 100
#define MAX_LONG_VECTOR 64

/* Codigos de errores */
typedef enum ErrorCode
{
    NO_ERR,
    ERR_MORFOLOGICO,
    ERR_SINTACTICO
} ErrorCode;

/* Tipos de variables*/
typedef enum
{
    BOOLEAN,
    INT
} Tipo;

/* Macro para cuerpo de funciones en macros */
#define F_BLOCK(instrucciones) do { instrucciones } while (0)

/* Estructura para ficheros de entrada y salida */
extern struct ALFA_UTILS
{
    FILE *fin;          /* Fichero de entrada */
    FILE *fasm;         /* Fichero de compilacion */
    FILE *fdbg;         /* Fichero de debug (logs de flex/bison) */
    FILE *ferr;         /* Fichero de salida de errores */

    ErrorCode error;    /* Codigo de error */

    unsigned int line, col;/* Numeros de linea y columna */
} alfa_utils_T;

typedef struct TIPO_ATRIBUTOS
{
    char *lexema[MAX_LONG_ID+1];    /* lexema de Identificador */
    int valor_entero;               /* valor de constante entera */
    
    Tipo tipo;                      /* boolean o entero */
    int es_direccion;               /* ¿es puntero? */

    int etiqueta;                   /* para generacion NASM */
} tipo_atributos;

/* Funcion para manejar errores */
void manage_error(char *msg, char *s);

/* Funcion Principal que llama al analizador */
int main(int argc, char *argv[]);

#endif