#include <stdio.h>
#include <stdlib.h>
#include "include/y.tab.h"
#include "include/alfa.h"

#define DEBUG_FILE "debug"

/* Inicializar valores default */
struct ALFA_UTILS alfa_utils_T = {
    .fin = NULL,
    .fasm = NULL,
    .fdbg = NULL,
    .ferr = NULL,

    .error = NO_ERR,

    .line = 1,
    .col = 1,
};

void manage_error(char *msg, char *s)
{
    char *tipo_error;

    if (alfa_utils_T.error == ERR_MORFOLOGICO)
        tipo_error = "Error morfologico";
    else if (alfa_utils_T.error == ERR_SINTACTICO) {
        tipo_error = "Error sintactico";
        alfa_utils_T.col -= 1;
    }
    
    /* tipo de error y linea y columna*/
    fprintf(stderr, "***%s en [lin %d, col %d]", tipo_error, alfa_utils_T.line, alfa_utils_T.col);
    /* mensaje concreto de error (solo si lo hay) */
    if (msg) {
        if (s)
            fprintf(stderr, ": %s (%s)\n", msg, s);
        else
            fprintf(stderr, ": %s\n", msg);
    } else
        fprintf(stderr, "\n");
}

extern FILE *yyout;
extern FILE *yyin;

extern int yyparse(void);


int main(int argc, char *argv[])
{
    int ret;
    
    if (argc != 3) {
        fprintf(stderr, "USO: %s <entrada_source> <salida_asm>", argv[0]);
        return EXIT_FAILURE;
    }

    /* Abrir fichero entrada */
    if (!(alfa_utils_T.fin = fopen(argv[1], "r")))
        return EXIT_FAILURE;

    /* Abrir fichero debug */
    if (!(alfa_utils_T.fdbg = fopen(DEBUG_FILE, "w"))) {
        fclose(alfa_utils_T.fin);
        return EXIT_FAILURE;
    }

    /* Abrir fichero salida ASM */
    if (!(alfa_utils_T.fasm = fopen(argv[2], "w"))) {
        fclose(alfa_utils_T.fin);
        fclose(alfa_utils_T.fdbg);
        return EXIT_FAILURE;
    }

    alfa_utils_T.ferr = stderr;
    yyin = alfa_utils_T.fin;
    yyout = alfa_utils_T.ferr;

    ret = yyparse();

    fclose(alfa_utils_T.fin);
    fclose(alfa_utils_T.fdbg);
    fclose(alfa_utils_T.fasm);

    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}