#include "asm_gen.h"
#include "ares.h"
#include <stdarg.h>


#define PUT_ASM(...) _put_asm(fpasm, "\t", "\n", __VA_ARGS__)
#define PUT_DIRECTIVE(...) _put_asm(fpasm, "", "\n", __VA_ARGS__)
#define PUT_LABEL(...) _put_asm(fpasm, "", ":\n", __VA_ARGS__)
#define PUT_COMMENT(...) _put_asm(fpasm, ";; ", "\n", __VA_ARGS__)


static void _put_asm(FILE* fpasm, const char* prefix, const char* suffix, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    if (prefix) fputs(prefix, fpasm);
    vfprintf(fpasm, fmt, ap);
    if (suffix) fputs(suffix, fpasm);
    va_end(ap);
}


void escribir_cabecera_presentacion(FILE* fpasm, char* input_filename)
{
    PUT_COMMENT("-------------------------------");
    PUT_COMMENT(" %s\n", input_filename);
    PUT_COMMENT("   Author: Daniel Barahona");
    PUT_COMMENT("-------------------------------");
}

void escribir_cabecera_bss(FILE* fpasm)
{
    PUT_DIRECTIVE("segment .bss");
    PUT_ASM("__esp resd 1");
}

void escribir_subseccion_data(FILE* fpasm)
{
    PUT_DIRECTIVE("segment .data");
    PUT_ASM("msg_error_division db \"**** Division por 0 no permitida\", 0");
    PUT_ASM("msg_error_expte db \"**** Exponente negativo no permitido\", 0");
    PUT_ASM("msg_error_indice_vector db \"**** Indice fuera de rango\", 0");
}

void declarar_variable(FILE* fpasm, char* nombre, int tipo, int tamano)
{
    PUT_COMMENT("; declarar_variable");
    NO_USO(tipo);
    PUT_ASM("_%s resd %d", nombre, tamano);

}

void escribir_segmento_codigo(FILE* fpasm)
{
    PUT_COMMENT("escribir_segmento_codigo");

    PUT_DIRECTIVE("segment .text");
    PUT_ASM("global main");
    PUT_ASM("extern print_int, print_boolean, print_string, print_blank");
    PUT_ASM("extern print_endofline, scan_int, scan_boolean");
}

void escribir_inicio_main(FILE* fpasm)
{
    PUT_COMMENT("escribir_inicio_main");
    PUT_LABEL("main");
    PUT_ASM("mov dword [__esp], esp");
}

void escribir_fin(FILE* fpasm)
{
    PUT_COMMENT("escribir_fin");
    PUT_ASM("jmp near fin");

    PUT_LABEL("fin_error_division");
    PUT_ASM("push dword msg_error_division");
    PUT_ASM("call print_string");
    PUT_ASM("call print_endofline");
    PUT_ASM("add esp, 4");
    PUT_ASM("jmp near fin");

    PUT_LABEL("fin_error_expte");
    PUT_ASM("push dword msg_error_expte");
    PUT_ASM("call print_string");
    PUT_ASM("call print_endofline");
    PUT_ASM("add esp, 4");
    PUT_ASM("jmp near fin");

    PUT_LABEL("fin_indice_fuera_rango");
    PUT_ASM("push dword msg_error_indice_vector");
    PUT_ASM("call print_string");
    PUT_ASM("call print_endofline");
    PUT_ASM("add esp, 4");
    PUT_ASM("jmp near fin");

    PUT_LABEL("fin");
    PUT_ASM("mov dword esp, [__esp]");
    PUT_ASM("ret");
}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable)
{
    PUT_COMMENT("escribir_operando");

    if (es_variable == 0)
        PUT_ASM("mov eax, %s", nombre);
    else
        PUT_ASM("mov eax, [_%s]", nombre);
    PUT_ASM("push eax");
}

void asignar(FILE* fpasm, char* nombre, int es_variable)
{
    PUT_COMMENT("asignar");
    PUT_ASM("pop dword eax");
    if (es_variable == 0)
        PUT_ASM("mov dword [_%s], eax", nombre);
    else {
        PUT_ASM("mov dword eax, [eax]");
        PUT_ASM("mov dword [_%s], eax", nombre);
    }
}

void apilar_constante(FILE* fpasm, int valor)
{
    PUT_COMMENT("apilar_constante");
    PUT_ASM("push dword %d", valor);
}

void apilar_valor(FILE* fpasm, int es_referencia)
{
    PUT_COMMENT("apilar_valor");
    if (es_referencia) {
        PUT_ASM("pop dword ebx");
        PUT_ASM("mov ebx, [ebx]");
        PUT_ASM("push dword ebx");
    }
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("sumar");
    PUT_ASM("pop dword eax");
    if (es_variable_2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx");
    if (es_variable_1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("add ebx, eax");
    PUT_ASM("push dword ebx");
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("restar");
    PUT_ASM("pop dword eax");
    if (es_variable_2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx");
    if (es_variable_1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("sub ebx, eax");
    PUT_ASM("push dword ebx");
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("multiplicar");
    PUT_ASM("pop dword eax");
    PUT_ASM("pop dword ebx");

    if (es_variable_1 == 1)
        PUT_ASM("mov dword ebx, [ebx]");
    if (es_variable_2 == 1)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("mov dword ecx, ebx");
    PUT_ASM("imul ecx");
    // todos los valores son de 32 bits entonces lo que queda en edx es overflow)
    PUT_ASM("push dword eax");
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("dividir");
    PUT_ASM("pop dword eax");
    if (es_variable_2 == 1)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("cmp eax, 0");
    PUT_ASM("je fin_error_division");

    PUT_ASM("pop dword ebx");
    if (es_variable_1 == 1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("mov dword ecx, eax");
    PUT_ASM("mov dword eax, ebx");
    PUT_ASM("cdq");
    PUT_ASM("idiv ecx");
    PUT_ASM("push dword eax");
}

void modulo(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("modulo");
    PUT_ASM("pop dword eax");
    if (es_variable_2 == 1)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("cmp eax, 0");
    PUT_ASM("je fin_error_division");

    PUT_ASM("pop dword ebx");
    if (es_variable_1 == 1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("mov dword ecx, eax");
    PUT_ASM("mov dword eax, ebx");
    PUT_ASM("cdq");
    PUT_ASM("idiv ecx");
    PUT_ASM("push dword edx");
}

void exponente(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
    PUT_ASM("exponente");
    PUT_ASM("pop dword ebx");
    if (es_variable_2 == 1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("cmp ebx, 0");
    PUT_ASM("jl fin_error_expte");
    PUT_ASM("je cero_exponente%d", etiqueta);

    PUT_ASM("pop dword eax");
    if (es_variable_1 == 1) {
        PUT_ASM("mov dword eax, [eax]");
    }
    // Guardar base original
    PUT_ASM("mov ecx, eax");
    PUT_ASM("sub ebx, 1");

    /* Calcular exponente */
    PUT_LABEL("exponente%d", etiqueta);
    PUT_ASM("imul ecx");
    PUT_ASM("sub ebx, 1");
    PUT_ASM("cmp ebx, 0");
    PUT_ASM("jg exponente%d", etiqueta);
    PUT_ASM("jmp fin_exponente%d", etiqueta);

    /* Caso exponente 0 => Resultado = 1*/
    PUT_LABEL("cero_exponente%d", etiqueta);
    PUT_ASM("mov eax, 1");

    /* Fin exponente */
    PUT_LABEL("fin_exponente%d", etiqueta);
    PUT_ASM("push dword eax");
}

void longitud(FILE* fpasm, int tam_vector)
{
    PUT_COMMENT("longitud de vector");
    PUT_ASM("mov dword eax, %d", tam_vector);
    PUT_ASM("push dword eax");
}

void o(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("or logico");
    PUT_ASM("pop dword eax");
    if (es_variable_2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx");
    if (es_variable_1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("or ebx, eax");
    PUT_ASM("push dword ebx");
}

void y(FILE* fpasm, int es_variable_1, int es_variable_2)
{
    PUT_COMMENT("and logico");
    PUT_ASM("pop dword eax");
    if (es_variable_2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx");
    if (es_variable_1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("and ebx, eax");
    PUT_ASM("push dword ebx");
}

void cambiar_signo(FILE* fpasm, int es_variable)
{
    PUT_COMMENT("cambiar signo");
    PUT_ASM("pop dword eax");
    if (es_variable)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("neg eax");
    PUT_ASM("push dword eax");
}

void no(FILE* fpasm, int es_variable, int cuantos_no)
{
    PUT_COMMENT("no logico");
    fprintf(fpasm, "pop dword eax");
    if (es_variable)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("cmp eax, 0");
    PUT_ASM("je dejar_1_no%d", cuantos_no);
    PUT_ASM("cmp eax, 1");
    PUT_ASM("je dejar_0_no%d", cuantos_no);
    PUT_ASM("jmp fin_no%d", cuantos_no);
    PUT_ASM("dejar_1_no%d:", cuantos_no);
    PUT_ASM("mov dword eax, 1");
    PUT_ASM("push dword eax");
    PUT_ASM("jmp fin_no%d", cuantos_no);
    PUT_ASM("dejar_0_no%d:", cuantos_no);
    PUT_ASM("mov dword eax, 0");
    PUT_ASM("push dword eax");
    PUT_ASM("fin_no%d:", cuantos_no);
}

/* FUNCIONES COMPARATIVAS */
void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparación igual\n");
    //lecuta de operandos
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    //operación
    fprintf(fpasm, "cmp ebx, eax\n"); // compara operando 1 y operando 2
    fprintf(fpasm, "je igual_es_igual%d\n", etiqueta); //si se cumple la condición de igualdad salta
    fprintf(fpasm, "mov dword eax, 0\n"); // si no salta es que no se cumple la condición
    fprintf(fpasm, "push dword eax\n"); // mete un 0 en la pila para indicar que no se cumple la condicion
    fprintf(fpasm, "jmp igual_fin%d\n", etiqueta); // saltamos al final para evitar el correcto
    fprintf(fpasm, "igual_es_igual%d:\n", etiqueta); //salto de igualdad
    fprintf(fpasm, "mov dword eax, 1\n"); //mete en la pila un 1 para indicar que se cumple
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "igual_fin%d:\n", etiqueta); //fin de la comprobación de igualdad
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparar distinto\n");
    //lectura de operandos
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    //operación
    fprintf(fpasm, "cmp ebx, eax\n"); // compara operando 1 y operando 2
    fprintf(fpasm, "jne distinto_es_distinto%d\n", etiqueta); //si se cumple la condición de desigualdad salta
    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "jmp distinto_fin%d\n", etiqueta);
    fprintf(fpasm, "distinto_es_distinto%d:\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 1\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "distinto_fin%d:\n", etiqueta);
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparación menor_igual\n");
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    fprintf(fpasm, "cmp ebx, eax\n"); // Op1 <= Op2 ?
    fprintf(fpasm, "jle mni_es_mni%d\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "jmp mni_fin%d\n", etiqueta);
    fprintf(fpasm, "mni_es_mni%d:\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 1\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "mni_fin%d:\n", etiqueta);
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparación mayor_igual\n");
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    fprintf(fpasm, "cmp ebx, eax\n"); // Op1 >= Op2 ?
    fprintf(fpasm, "jge myi_es_myi%d\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "jmp myi_fin%d\n", etiqueta);
    fprintf(fpasm, "myi_es_myi%d:\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 1\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "myi_fin%d:\n", etiqueta);
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparación menor\n");
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    fprintf(fpasm, "cmp ebx, eax\n"); // Op1 < Op2 ?
    fprintf(fpasm, "jl mn_es_mn%d\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "jmp mn_fin%d\n", etiqueta);
    fprintf(fpasm, "mn_es_mn%d:\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 1\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "mn_fin%d:\n", etiqueta);
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comparación mayor\n");
    fprintf(fpasm, "pop dword eax\n"); // Op2
    if (es_variable2)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "pop dword ebx\n"); // Op1
    if (es_variable1)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    fprintf(fpasm, "cmp ebx, eax\n"); // Op1 > Op2 ?
    fprintf(fpasm, "jg my_es_my%d\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "jmp my_fin%d\n", etiqueta);
    fprintf(fpasm, "my_es_my%d:\n", etiqueta);
    fprintf(fpasm, "mov dword eax, 1\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm, "my_fin%d:\n", etiqueta);
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/* Hay que distinguir entre Global, y Parametro o Variable Local*/
void leer(FILE* fpasm, char* nombre, int tipo, int es_global)
{
    if (!fpasm || !nombre) {
        printf("Error fallo en compilador, fichero fpasm o nombre nulo");
        return;
    }
    fprintf(fpasm, "; leer (scan)\n");
    if (es_global)
        fprintf(fpasm, "push dword _%s\n", nombre);
    fprintf(fpasm, (tipo==INT) ? "call scan_int\n" : "call scan_boolean\n");
    fprintf(fpasm, "add esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; escribir (print)\n");
    if (es_variable) {
        fprintf(fpasm,
                "pop eax\n"
                "push dword [eax]\n");
    }
    if (tipo == INT) {
        fprintf(fpasm, "call print_int\n");
    }
    else
        if (tipo == BOOLEAN) {
            fprintf(fpasm, "call print_boolean\n");
        }
    fprintf(fpasm, "call print_endofline\n");
    fprintf(fpasm, "add esp, 4\n");
}

void ifthenelse_inicio(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthenelse_inicio\n");
    fprintf(fpasm, "pop eax\n");
    if (exp_es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then%d\n", etiqueta);
}

void ifthen_inicio(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthen_inicio\n");
    fprintf(fpasm, "pop eax\n");
    if (exp_es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then%d\n", etiqueta);
}

void ifthen_fin(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthen_fin\n");
    fprintf(fpasm, "fin_then%d:\n", etiqueta);
}

void ifthenelse_fin_then(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthenelse_fin_then\n");
    fprintf(fpasm, "jmp near fin_ifelse%d\n", etiqueta);
    fprintf(fpasm, "fin_then%d:\n", etiqueta);
}

void ifthenelse_fin(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthenelse_fin\n");
    fprintf(fpasm, "fin_ifelse%d:\n", etiqueta);
}

void while_inicio(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; while_inicio\n");
    fprintf(fpasm, "inicio_while%d:\n", etiqueta);
    /* Ahora vendria una condicion (mayor, menor o igual, etc.) */
}

void while_exp_pila(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; while_exp_pila\n");

    fprintf(fpasm, "pop eax\n");
    if (exp_es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm,  "cmp eax, 0\n");
    /* Si la condicion no se cumple, salir del loop */
    fprintf(fpasm, "je near fin_while%d\n", etiqueta);
    /* Aqui vendria el contenido del while */
}

void while_fin(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; while_fin\n");
    /* Saltar al comienzo del loop */
    fprintf(fpasm, "jmp near inicio_while%d\n", etiqueta);
    fprintf(fpasm, "fin_while%d:\n", etiqueta);
    /* Codigo posterior al while */
}

void do_while_inicio(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("do_while_inicio%d", etiqueta);
    PUT_LABEL("inicio_do_while%d", etiqueta);
    /* Debajo vienen las sentencias, la condicion de parada y el salto */
    /* Asi aseguramos que las sentencias se ejecutan al menos una vez */
}

void do_while_fin(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    PUT_COMMENT("do_while_fin%d", etiqueta);
    /* Sacamos resultado de expresion booleana */
    PUT_ASM("pop eax");
    if (exp_es_variable)
        PUT_ASM("mov dword eax, [eax]");

    PUT_ASM("cmp eax, 1");
    /* Si la condicion si se cumple, saltar al comienzo del dowhile */
    PUT_ASM("je near inicio_do_while%d", etiqueta);
    /* Si no se cumple, sale del bucle y sigue ejecutando el programa */
}

void loop_in_inicio(FILE* fpasm, char *nombre, int inicio_contador, int etiqueta)
{
    PUT_COMMENT("loop_in_inicio%d", etiqueta);
    PUT_ASM("push eax");
    PUT_ASM("push eax");
    PUT_ASM("mov dword [_%s], eax", nombre, inicio_contador);
    PUT_LABEL("inicio_loop_in%d", etiqueta);
}

void loop_in_fin(FILE* fpasm, char *nombre, int fin_contador, int etiqueta)
{
    PUT_COMMENT("loop_in_fin%d", etiqueta);
    
    /* Incrementamos contador */
    PUT_ASM("mov ecx, dword [_%s]", nombre);
    PUT_ASM("push dword ecx");
    PUT_ASM("inc ecx");
    PUT_ASM("mov dword [_%s], ecx", nombre);
    /* Si el contador no ha llegado al final, continuar iterando */
    PUT_ASM("cmp ecx, %d", fin_contador);
    PUT_ASM("pop dword ecx");
    PUT_ASM("jl near inicio_loop_in%d", etiqueta);
    /* Si no, sale del bucle y sigue ejecutando el programa */
}

void escribir_elemento_vector(FILE* fpasm, char* nombre_vector, int tam_max, int exp_es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; escribir_elemento_vector\n");
    NO_USO(nombre_vector);
    NO_USO(tam_max);
    // Extraemos de la pila el valor del índice a un registro
    fprintf(fpasm, "pop dword eax\n");

    // En el caso en el que sea una dirección, accedemos al valor
    if (exp_es_direccion == 1) {
        fprintf(fpasm, "mov eax, dword [eax]\n");
    }

    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void apilar_valor_elemento_vector(FILE* fpasm)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; apilar_valor_elemento_vector\n");
    fprintf(fpasm, "pop dword eax\n");
    fprintf(fpasm, "push dword [eax]\n");
}

void comprobar_indice_vector(FILE* fpasm, const char* nombre, int es_direccion, int tam)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; comprobar_indice_vector\n");
    fprintf(fpasm, "pop dword eax\n");

    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    /* Mirar que indice no sea negativo */
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "jl fin_indice_fuera_rango\n");

    /* Mirar que indice no sea mayor que tam vector */
    fprintf(fpasm, "cmp eax, %d\n", tam);
    fprintf(fpasm, "jge fin_indice_fuera_rango\n");

    fprintf(fpasm, "lea eax, [4*eax + _%s]\n", nombre); // Dirección del elemento indexado en eax
    fprintf(fpasm, "push dword eax\n");         // Almacenamos la dirección al elemento
}

void declararFuncion(FILE* fpasm, char* nombre_funcion, int num_var_loc)
{
    if (!fpasm || !nombre_funcion) {
        printf("Error fallo en compilador, fichero fpasm o nombre_funcion nulo");
        return;
    }
    fprintf(fpasm, "; declararFuncion\n");
    fprintf(fpasm, "_%s:\n", nombre_funcion);
    fprintf(fpasm, "push ebp\n");
    fprintf(fpasm, "mov dword ebp, esp\n");
    fprintf(fpasm, "sub esp, %d\n", 4 * num_var_loc);
}

void retornarFuncion(FILE* fpasm, int es_variable)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; retornarFuncion\n");
    fprintf(fpasm, "pop dword eax\n");
    if (es_variable == 1)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "mov dword esp, ebp\n");
    fprintf(fpasm, "pop dword ebp\n");
    fprintf(fpasm, "ret\n");
}

void escribirParametro(FILE* fpasm, int direccion, int pos_parametro, int num_total_parametros)
{
    int d_ebp = 4 + 4*(num_total_parametros - pos_parametro);
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; escribirParametro\n");
    if (direccion == 1) {
        fprintf(fpasm, "lea eax, [ebp + %d]\n", d_ebp);
    }
    else {
        fprintf(fpasm, "mov eax, dword [ebp + %d]\n", d_ebp);
    }
    fprintf(fpasm, "push dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int direccion, int posicion_variable_local)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; escribirVariableLocal\n");
    int d_ebp = 4 * posicion_variable_local;
    if (direccion == 1) {
        fprintf(fpasm, "lea eax, [ebp - %d]\n", d_ebp);
    }
    else {
        fprintf(fpasm, "mov eax, dword [ebp - %d]\n", d_ebp);
    }
    fprintf(fpasm, "push dword eax\n");
}

void asignarParametro(FILE* fpasm, int es_variable, int pos_param, int num_params)
{
    int d_ebp = 4 + 4*(num_params - pos_param);
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; asignarParametro\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_variable)
        fprintf(fpasm, "mov eax, dword [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", d_ebp);
    fprintf(fpasm, "mov [ebx], eax\n");
}

void asignarVariableLocal(FILE* fpasm, int es_variable, int pos_var_loc)
{
    int d_ebp = 4*pos_var_loc;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; asignarVariableLocal\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_variable)
        fprintf(fpasm, "mov eax, dword [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", d_ebp);
    fprintf(fpasm, "mov [ebx], eax\n");
}

void operandoEnPilaAArgumento(FILE* fpasm, int es_variable)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo\n");
        return;
    }
    fprintf(fpasm, "; operandoEnPilaAArgumento\n");
    if (es_variable == 1) {
        fprintf(fpasm, "pop dword eax\n"
                "mov dword eax, [eax]\n"
                "push dword eax\n");
    }
}

void llamarFuncion(FILE* fpasm, char* nombre_funcion, int num_argumentos)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; llamarFuncion\n");
    fprintf(fpasm, "call _%s\n", nombre_funcion);
    limpiarPila(fpasm, num_argumentos);
    fprintf(fpasm, "push dword eax\n");
}

void limpiarPila(FILE* fpasm, int num_argumentos)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; limpiar pila\n");

    fprintf(fpasm, "add esp, %d\n", num_argumentos * 4);
}

void init_vector(FILE* fpasm, char* nombre, int tam_inicializacion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; inicializar vector\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);
    fprintf(fpasm, "add ebx, %d\n", 4 * (tam_vector - 1));

    for (i = tam_vector; i > tam_inicializacion; i--) {
        fprintf(fpasm, "mov dword [ebx], 0\n");
        fprintf(fpasm, "sub ebx, 4\n");
    }

    for (; i > 0; i--) {
        fprintf(fpasm, "pop dword eax\n");
        fprintf(fpasm, "mov dword [ebx], eax\n");

        if (i != 1)
            fprintf(fpasm, "sub ebx, 4\n");
    }
}

void compare_with(FILE* fpasm, int es_dir_1, int es_dir2, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; compare-with %d\n", etiqueta);

    /* Extraer expresiones a evaluar, primero exp2 y luego exp1 */
    fprintf(fpasm, "pop dword ebx\n");
    if (es_dir2)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");
    fprintf(fpasm, "pop dword eax\n");
    if (es_dir_1)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    /* Compararlos */
    fprintf(fpasm, "cmp eax, ebx\n");
    fprintf(fpasm, "jl cmpw_less%d\n", etiqueta);
    fprintf(fpasm, "je cmpw_equal%d\n", etiqueta);
    fprintf(fpasm, "jg cmpw_greater%d\n", etiqueta);
}

void salto_less(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; LESS %d\n", etiqueta);
    fprintf(fpasm, "cmpw_less%d:\n", etiqueta);
}

void salto_equal(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "jmp fin_cmpw%d\n", etiqueta);
    fprintf(fpasm, "; EQUAL %d\n", etiqueta);
    fprintf(fpasm, "cmpw_equal%d:\n", etiqueta);
}

void salto_greater(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "jmp fin_cmpw%d\n", etiqueta);
    fprintf(fpasm, "; GREATER %d\n", etiqueta);
    fprintf(fpasm, "cmpw_greater%d:\n", etiqueta);
}

void fin_compare(FILE* fpasm, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; fin del compare-with %d\n", etiqueta);
    fprintf(fpasm, "fin_cmpw%d:\n", etiqueta);
}

/* Operador de incremento: ++ */
void incremento_variable_global(FILE* fpasm, char* nombre)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Inc variable global [%s]\n", nombre);

    fprintf(fpasm, "mov dword ebx, [_%s]\n", nombre);
    fprintf(fpasm, "inc ebx\n");
    fprintf(fpasm, "mov dword [_%s], ebx\n", nombre);
}

void incremento_parametro(FILE* fpasm, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Inc parametro funcion\n");

    fprintf(fpasm, "mov dword eax, 1\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void incremento_vector(FILE* fpasm, char* nombre, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Inc elementos vector [%s]\n", nombre);

    fprintf(fpasm, "mov eax, 1\n");

    fprintf(fpasm, "mov edx, eax\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov eax, edx\n");

        fprintf(fpasm, "add eax, [ebx]\n");
        fprintf(fpasm, "mov [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void incremento_variable_local(FILE* fpasm, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Inc variable local\n");

    fprintf(fpasm, "mov eax, 1\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

/* Operador de decremento: -- */
void decremento_variable_global(FILE* fpasm, char* nombre)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Dec variable global [%s]\n", nombre);

    fprintf(fpasm, "mov dword ebx, [_%s]\n", nombre);
    fprintf(fpasm, "dec ebx\n");
    fprintf(fpasm, "mov dword [_%s], ebx\n", nombre);
}

void decremento_parametro(FILE* fpasm, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Dec parametro funcion\n");

    fprintf(fpasm, "mov eax, -1\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void decremento_vector(FILE* fpasm, char* nombre, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Dec elementos vector [%s]\n", nombre);

    fprintf(fpasm, "mov eax, -1\n");
    fprintf(fpasm, "mov edx, eax\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov eax, edx\n");

        fprintf(fpasm, "add eax, [ebx]\n");
        fprintf(fpasm, "mov [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void decremento_variable_local(FILE* fpasm, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Dec variable local\n");

    fprintf(fpasm, "mov eax, -1\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

/* Operador de autosuma: += */
void autosuma_variable_global(FILE* fpasm, char* nombre, int es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autosuma variable global [%s]\n", nombre);

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "mov dword ebx, [_%s]\n", nombre);
    fprintf(fpasm, "add ebx, eax\n");
    fprintf(fpasm, "mov dword [_%s], ebx\n", nombre);
}

void autosuma_parametro(FILE* fpasm, int es_direccion, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autosuma parametro funcion\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void autosuma_vector(FILE* fpasm, char* nombre, int es_direccion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autosuma elementos vector [%s]\n", nombre);

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov edx, dword [eax]\n");
    fprintf(fpasm, "mov edx, eax\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov eax, edx\n");

        fprintf(fpasm, "add eax, [ebx]\n");
        fprintf(fpasm, "mov [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void autosuma_variable_local(FILE* fpasm, int es_direccion, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autosuma variable local\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "add eax, [ebx]\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

/* Operador de autoresta: -= */
void autoresta_variable_global(FILE* fpasm, char* nombre, int es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autoresta variable global [%s]\n", nombre);

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "mov dword ebx, [_%s]\n", nombre);
    fprintf(fpasm, "sub ebx, eax\n");
    fprintf(fpasm, "mov dword [_%s], ebx\n", nombre);
}

void autoresta_parametro(FILE* fpasm, int es_direccion, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autoresta parametro funcion\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "mov ecx, dword [ebx]\n");
    fprintf(fpasm, "sub ecx, eax\n");
    fprintf(fpasm, "mov dword [ebx], ecx\n");
}

void autoresta_vector(FILE* fpasm, char* nombre, int es_direccion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autoresta elementos vector [%s]\n", nombre);

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov edx, dword [eax]\n");
    fprintf(fpasm, "mov edx, eax\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov eax, edx\n");

        fprintf(fpasm, "sub [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void autoresta_variable_local(FILE* fpasm, int es_direccion, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autoresta variable local\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "sub [ebx], eax\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

/* Operador de automultiplicacion: *= */
void automult_variable_global(FILE* fpasm, char* nombre, int es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Automult variable global [%s]\n", nombre);

    fprintf(fpasm, "pop dword ebx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");

    fprintf(fpasm, "mov dword eax, [_%s]\n", nombre);
    fprintf(fpasm, "imul ebx\n");
    fprintf(fpasm, "mov dword [_%s], eax\n", nombre);
}

void automult_parametro(FILE* fpasm, int es_direccion, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Automult parametro funcion\n");

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ecx, [ecx]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "mov dword eax, [ebx]\n");
    fprintf(fpasm, "imul ecx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void automult_vector(FILE* fpasm, char* nombre, int es_direccion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Automult elementos vector [%s]\n", nombre);

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov edx, dword [ecx]\n");
    fprintf(fpasm, "mov edx, ecx\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov ecx, edx\n");

        fprintf(fpasm, "mov dword eax, [ebx]\n");
        fprintf(fpasm, "imul ecx\n");
        fprintf(fpasm, "mov [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void automult_variable_local(FILE* fpasm, int es_direccion, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Automult variable local\n");

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ecx, [ecx]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "mov dword eax, [ebx]\n");
    fprintf(fpasm, "imul ecx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

/* Operador de autodivision: /= */
void autodiv_variable_global(FILE* fpasm, char* nombre, int es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autodiv variable global [%s]\n", nombre);

    fprintf(fpasm, "pop dword ebx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ebx, [ebx]\n");

    fprintf(fpasm, "mov dword eax, [_%s]\n", nombre);
    fprintf(fpasm, "cdq\n");
    fprintf(fpasm, "idiv ebx\n");
    fprintf(fpasm, "mov dword [_%s], eax\n", nombre);
}

void autodiv_parametro(FILE* fpasm, int es_direccion, int pos_param, int num_params)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autodiv parametro funcion\n");

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ecx, [ecx]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", 4 + 4*(num_params - pos_param));
    fprintf(fpasm, "mov dword eax, [ebx]\n");
    fprintf(fpasm, "cdq\n");
    fprintf(fpasm, "idiv ecx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void autodiv_vector(FILE* fpasm, char* nombre, int es_direccion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autodiv elementos vector [%s]\n", nombre);

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov edx, dword [ecx]\n");
    fprintf(fpasm, "mov edx, ecx\n");

    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            fprintf(fpasm, "mov ecx, edx\n");

        fprintf(fpasm, "mov dword eax, [ebx]\n");
        fprintf(fpasm, "cdq\n");
        fprintf(fpasm, "idiv ecx\n");
        fprintf(fpasm, "mov [ebx], eax\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}

void autodiv_variable_local(FILE* fpasm, int es_direccion, int pos_var_loc)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Autodiv variable local\n");

    fprintf(fpasm, "pop dword ecx\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword ecx, [ecx]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", 4 * pos_var_loc);
    fprintf(fpasm, "mov dword eax, [ebx]\n");
    fprintf(fpasm, "cdq\n");
    fprintf(fpasm, "idiv ecx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}


void modulo_vector(FILE* fpasm, char* nombre, int es_direccion, int tam_vector)
{
    int i;
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; Modulo vectorial\n");

    /* Cargar divisor */
    fprintf(fpasm, "pop dword eax\n");
    if (es_direccion)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "mov edx, eax\n");

    /* Cargar direccion base del vector */
    fprintf(fpasm, "mov ebx, _%s\n", nombre);

    for (i=0; i < tam_vector; i++) {
        fprintf(fpasm, "push dword edx\n");
        fprintf(fpasm, "mov dword ecx, edx\n"); // ecx <- divisor
        fprintf(fpasm, "mov dword eax, [ebx]\n"); // eax <- dividendo
        fprintf(fpasm, "cdq\n"); // extiende en signo edx:eax
        fprintf(fpasm, "idiv ecx\n");
        fprintf(fpasm, "mov dword [ebx], edx\n"); // guarda modulo en elemento vector
        fprintf(fpasm, "pop dword edx\n");

        if (i != (tam_vector - 1))
            fprintf(fpasm, "add ebx, 4\n");
    }
}
