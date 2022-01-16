#include "ares.h"
#include "y.tab.h"

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define DEBUG_FILE "debug"

#define ARG_FLAGS "f:o:dhv"

/* Inicializar valores default */
struct ARES_UTILS ares_utils_T = {
    .fin = NULL,
    .fin_name = NULL,
    .fasm = NULL,
    .fdbg = NULL,
    .ferr = NULL,

    .error = NO_ERR,

    .line = 1,
    .col = 1,
};

void manage_error(char* msg, char* s)
{
    char* tipo_error;

    if (ares_utils_T.error == ERR_MORFOLOGICO)
        tipo_error = "Error morfologico";
    else
        if (ares_utils_T.error == ERR_SINTACTICO) {
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
    }
    else
        fprintf(stderr, "\n");
}

char* remove_quotes(char* s1) 
{
    size_t len = strlen(s1);
    if (s1[0] == '"' && s1[len - 1] == '"') {
        s1[len - 1] = '\0';
        memmove(s1, s1 + 1, len - 1);
    }
    return s1;
}

void exec_sh(const char* cmd)
{
    char* output = (char*) calloc(1, sizeof(char));
    output[0] = '\0';

    FILE* fp;
    char path[1035];

    fp = popen(cmd, "r");
    if (!fp) {
        printf("[Tac]: Failed to run command `%s`\n", cmd);
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        output = (char*)realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
        strcat(output, path);
    }

    pclose(fp);
    free(output);
}

void print_help(const char* c)
{
    fprintf(stderr,
            "\nUSO: %s <entrada_ares> <salida>\n\
    + entrada_ares: Fichero con codigo fuente ARES\n\
    + salida_asm: Nombre fichero ejecutable\n\
\nOpciones\n\
    -h: muestra esta ayuda\n\n\
    -f: nombre fichero de entrada con extesion `.ares`\n\n\
    -o: nombre de fichero salida (ejecutable)\n\n\
    -d: activa modo DEBUG. Se geera el ejecutable y el fichero con codigo NASM\n\n\
    -u: desinstala el compilador del Lenguaje ARES\n\n\
\nPara mas informacion, referirse al README.md\n\
-----------------------------------------------------\n",
            c);
}

int print_version()
{
    printf("Current version: ares v2.1\n");
    return EXIT_SUCCESS;
}

extern FILE* yyout;
extern FILE* yyin;

extern int yyparse(void);


int main(int argc, char* argv[])
{
    int ret = 1, opt;
    int file_in_exists=-1, file_out_exists=-1, dbg_enabled=-1;
    char cmd[128] = "", file_in[64] = "", file_out[64] = "";


    while ((opt = getopt(argc, argv, ARG_FLAGS)) != -1) {
        switch (opt) {
            case 'f':
                sprintf(file_in, "%s", optarg);
                file_in_exists = 1;
                break;
            case 'o':
                sprintf(file_out, "%s", optarg);
                file_out_exists = 1;
                break;
            case 'd':
                dbg_enabled = 1;
                break;
            case 'h':
                print_help(argv[0]);
                break;
            case 'v':
                printf("OPTIND %d", optind);
                return print_version();
            case ':':
                printf("** la opcion necesita un valor\n");
                break;
            case '?':
                printf("** opcion desconocida: %c\n", optopt);
                break;
        }
    }

    if (file_in_exists == -1) {
        printf("** Se requiere un fichero de entrada con extension .ares\n");
        return EXIT_FAILURE;
    }

    if (file_out_exists == -1) {
        printf("** Se requiere nombre de fichero ejecutable\n");
        return EXIT_FAILURE;
    }

    /* Comprobar extension de fichero de entrada */
    const char* dot = strrchr(file_in, '.');
    if (strcmp(dot, INPUT_EXTENSION) != 0) {
        printf("** Los ficheros de entrada deben acabar en [%s]\n", INPUT_EXTENSION);
        return EXIT_FAILURE;
    }

    /* Abrir fichero entrada y guardar su nombre */
    if (!(ares_utils_T.fin = fopen(file_in, "r")))
        return EXIT_FAILURE;

    /* Abrir fichero debug */
    if (!(ares_utils_T.fdbg = fopen(DEBUG_FILE, "w"))) {
        fclose(ares_utils_T.fin);
        return EXIT_FAILURE;
    }
    /* Abrir fichero salida ASM */
    if (!(ares_utils_T.fasm = fopen("exe.asm", "w"))) {
        fclose(ares_utils_T.fin);
        fclose(ares_utils_T.fdbg);
        return EXIT_FAILURE;
    }

    ares_utils_T.fin_name = file_in;
    ares_utils_T.ferr = stderr;
    yyin = ares_utils_T.fin;
    yyout = ares_utils_T.ferr;

    ret = yyparse();

    fclose(ares_utils_T.fin);
    fclose(ares_utils_T.fdbg);
    fclose(ares_utils_T.fasm);

    /* Compilar fichero NASM y borrarlo a menos que DEBUG este activado */
    exec_sh("nasm -f elf32 exe.asm");
    sprintf(cmd, "gcc -m32 -o %s exe.o obj/areslib.o", file_out);
    exec_sh(cmd);

    if (dbg_enabled == -1)
        exec_sh("rm exe.o exe.asm");

    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
