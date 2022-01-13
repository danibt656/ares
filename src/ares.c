#include "ares.h"
#include "y.tab.h"

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_FILE "debug"

/* Inicializar valores default */
struct ALFA_UTILS ares_utils_T = {
    .fin = NULL,
    .fin_name = NULL,
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

    if (ares_utils_T.error == ERR_MORFOLOGICO)
        tipo_error = "Error morfologico";
    else if (ares_utils_T.error == ERR_SINTACTICO) {
        tipo_error = "Error sintactico";
        ares_utils_T.col -= 1;
    }
    
    /* tipo de error y linea y columna*/
    fprintf(stderr, "***%s en [lin %d, col %d]", tipo_error, ares_utils_T.line, ares_utils_T.col);
    /* mensaje concreto de error (solo si lo hay) */
    if (msg) {
        if (s)
            fprintf(stderr, ": %s (%s)\n", msg, s);
        else
            fprintf(stderr, ": %s\n", msg);
    } else
        fprintf(stderr, "\n");
}

//void exec_sh(const char *cmd)
//{
//    char *output = (char*) calloc(1, sizeof(char));
//    output[0] = '\0';
//
//    FILE *fp;
//    char path[1035];
//
//    fp = popen(cmd, "r");
//    if (!fp) {
//        printf("[Tac]: Failed to run command `%s`\n", cmd);
//        exit(1);
//    }
//
//    while (fgets(path, sizeof(path), fp) != NULL) {
//        output = (char*)realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
//        strcat(output, path);
//    }
//
//    pclose(fp);
//    free(output);
//}

extern FILE *yyout;
extern FILE *yyin;

extern int yyparse(void);


int main(int argc, char *argv[])
{
    int ret;
    
    if (argc != 3) {
        fprintf(stderr,
        "Numero de parametros incorrectos\n\
    USO: %s <entrada_ares> <salida_asm>\n\
        + entrada_ares: Fichero con codigo fuente ALFA\n\
        + salida_asm: Nombre fichero donde se generara codigo NASM\n\
\n\nPara mas informacion, referirse al README.md\n\
-----------------------------------------------------\n",
        argv[0]);
        return EXIT_FAILURE;
    }

    /* Comprobar extension de fichero de entrada */
    const char *dot = strrchr(argv[1], '.');
    if(strcmp(dot, INPUT_EXTENSION) != 0) {
        printf("** Los ficheros de entrada deben acabar en [%s]", INPUT_EXTENSION);
        return EXIT_FAILURE;
    }

    /* Abrir fichero entrada y guardar su nombre */
    if (!(ares_utils_T.fin = fopen(argv[1], "r")))
        return EXIT_FAILURE;
    ares_utils_T.fin_name = argv[1];

    /* Abrir fichero debug */
    if (!(ares_utils_T.fdbg = fopen(DEBUG_FILE, "w"))) {
        fclose(ares_utils_T.fin);
        return EXIT_FAILURE;
    }

    /* Abrir fichero salida ASM */
    if (!(ares_utils_T.fasm = fopen(argv[2], "w"))) {
        fclose(ares_utils_T.fin);
        fclose(ares_utils_T.fdbg);
        return EXIT_FAILURE;
    }

    ares_utils_T.ferr = stderr;
    yyin = ares_utils_T.fin;
    yyout = ares_utils_T.ferr;

    ret = yyparse();

//    exec_sh("echo \"Hello world\"");

    fclose(ares_utils_T.fin);
    fclose(ares_utils_T.fdbg);
    fclose(ares_utils_T.fasm);

    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
