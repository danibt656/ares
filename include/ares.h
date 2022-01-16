#ifndef ARES_H
#define ARES_H 1

#include <stdio.h>

/* Macro para cuerpo de funciones en macros */
#define F_BLOCK(block) do { block } while (0)
#define NO_USO(arg) ((void)(arg))

#define MAX_LONG_ID 100
#define MAX_LONG_VECTOR 64

/* Extension de los ficheros en lenguaje ARES */
#define INPUT_EXTENSION ".ares"

/* Codigos de errores */
typedef enum ErrorCode {
    NO_ERR,
    ERR_MORFOLOGICO,
    ERR_SINTACTICO
} ErrorCode;

/* Tipos de variables*/
typedef enum {
    BOOLEAN,
    INT,
    STRING
} Tipo;

/* Estructura para ficheros de entrada y salida */
extern struct ARES_UTILS {
    FILE* fin;          /* Fichero de entrada */
    char* fin_name;     /* Nombre de fichero de entrada */
    FILE* fasm;         /* Fichero de compilacion */
    FILE* fdbg;         /* Fichero de debug (logs de flex/bison) */
    FILE* ferr;         /* Fichero de salida de errores */

    ErrorCode error;    /* Codigo de error */

    unsigned int line, col;/* Numeros de linea y columna */
} ares_utils_T;

typedef struct {
    char lexema[MAX_LONG_ID+1];         /* lexema de Identificador */

    int valor_entero;                   /* valor de constante entera */
    int es_direccion;                   /* Variable o Constante */

    char valor_string[MAX_LONG_ID+1];   /* valor de la constante String */

    Tipo tipo;                          /* boolean o entero */

    int etiqueta;                       /* para anidacion */

    int num_parametros_llamada_actual;  /* Para llamadas a funciones */

    int tam_inicializacion_vector;      /* Para inicializar vectores */
} attribute_type;

/* Ejecutar comandos de shell */
void exec_sh(const char* cmd);

/* Manejar errores */
void manage_error(char* msg, char* s);

/* Quita las comillas dobles de los extremos de un String */
char* remove_quotes(char* s1);

/* Muestra ayuda */
void print_help(const char* c);

/* Muestra numero de version */
int print_version();

/* Funcion Principal que llama al analizador */
int main(int argc, char* argv[]);


#endif /* ARES_H */
