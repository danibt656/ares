#include "asm_gen.h"
#include "ares.h"
#include <stdarg.h>


#define PUT_ASM(...) _put_asm(fpasm, "\t", "\n", __VA_ARGS__)
#define PUT_DIRECTIVE(...) _put_asm(fpasm, "", "\n", __VA_ARGS__)
#define PUT_LABEL(...) _put_asm(fpasm, "", ":eeeee\n", __VA_ARGS__)
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
    PUT_ASM("msg_error_loop_in db \"**** Limites de rango invalidos\", 0");
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

    PUT_LABEL("fin_error_loop_in");
    PUT_ASM("push dword msg_error_loop_in");
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
    PUT_COMMENT("comparación igual");
    //lecuta de operandos
    PUT_ASM("pop dword eax\n"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]\n");
    PUT_ASM("pop dword ebx\n"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]\n");
    //operación
    PUT_ASM("cmp ebx, eax\n"); // compara operando 1 y operando 2
    PUT_ASM("je igual_es_igual%d\n", etiqueta); //si se cumple la condición de igualdad salta
    PUT_ASM("mov dword eax, 0\n"); // si no salta es que no se cumple la condición
    PUT_ASM("push dword eax\n"); // mete un 0 en la pila para indicar que no se cumple la condicion
    PUT_ASM("jmp igual_fin%d\n", etiqueta); // saltamos al final para evitar el correcto
    PUT_ASM("igual_es_igual%d:\n", etiqueta); //salto de igualdad
    PUT_ASM("mov dword eax, 1\n"); //mete en la pila un 1 para indicar que se cumple
    PUT_ASM("push dword eax\n");
    PUT_ASM("igual_fin%d:\n", etiqueta); //fin de la comprobación de igualdad
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    PUT_COMMENT("comparar distinto");
    //lectura de operandos
    PUT_ASM("pop dword eax\n"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]\n");
    PUT_ASM("pop dword ebx\n"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]\n");
    //operación
    PUT_ASM("cmp ebx, eax\n"); // compara operando 1 y operando 2
    PUT_ASM("jne distinto_es_distinto%d\n", etiqueta); //si se cumple la condición de desigualdad salta
    PUT_ASM("mov dword eax, 0\n");
    PUT_ASM("push dword eax\n");
    PUT_ASM("jmp distinto_fin%d\n", etiqueta);
    PUT_ASM("distinto_es_distinto%d:\n", etiqueta);
    PUT_ASM("mov dword eax, 1\n");
    PUT_ASM("push dword eax\n");
    PUT_ASM("distinto_fin%d:\n", etiqueta);
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    PUT_COMMENT("comparación menor_igual");
    PUT_ASM("pop dword eax"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("cmp ebx, eax"); // Op1 <= Op2 ?
    PUT_ASM("jle mni_es_mni%d", etiqueta);
    PUT_ASM("mov dword eax, 0");
    PUT_ASM("push dword eax");
    PUT_ASM("jmp mni_fin%d", etiqueta);
    PUT_COMMENT("mni_es_mni%d", etiqueta);
    PUT_ASM("mov dword eax, 1");
    PUT_ASM("push dword eax");
    PUT_COMMENT("mni_fin%d", etiqueta);
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    PUT_COMMENT("comparación mayor_igual");
    PUT_ASM("pop dword eax\n"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("cmp ebx, eax"); // Op1 >= Op2 ?
    PUT_ASM("jge myi_es_myi%d", etiqueta);
    PUT_ASM("mov dword eax, 0");
    PUT_ASM("push dword eax");
    PUT_ASM("jmp myi_fin%d", etiqueta);
    PUT_COMMENT("myi_es_myi%d", etiqueta);
    PUT_ASM("mov dword eax, 1");
    PUT_ASM("push dword eax");
    PUT_COMMENT("myi_fin%d", etiqueta);
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    PUT_COMMENT("comparación menor");
    PUT_ASM("pop dword eax"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("cmp ebx, eax"); // Op1 < Op2 ?
    PUT_ASM("jl mn_es_mn%d", etiqueta);
    PUT_ASM("mov dword eax, 0");
    PUT_ASM("push dword eax");
    PUT_ASM("jmp mn_fin%d", etiqueta);
    PUT_COMMENT("mn_es_mn%d", etiqueta);
    PUT_ASM("mov dword eax, 1");
    PUT_ASM("push dword eax");
    PUT_COMMENT("mn_fin%d", etiqueta);
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    PUT_COMMENT("comparación mayor");
    PUT_ASM("pop dword eax"); // Op2
    if (es_variable2)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("pop dword ebx"); // Op1
    if (es_variable1)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("cmp ebx, eax"); // Op1 > Op2 ?
    PUT_ASM("jg my_es_my%d", etiqueta);
    PUT_ASM("mov dword eax, 0");
    PUT_ASM("push dword eax");
    PUT_ASM("jmp my_fin%d", etiqueta);
    PUT_LABEL("my_es_my%d", etiqueta);
    PUT_ASM("mov dword eax, 1");
    PUT_ASM("push dword eax");
    PUT_LABEL("my_fin%d", etiqueta);
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/* Hay que distinguir entre Global, y Parametro o Variable Local*/
void leer(FILE* fpasm, char* nombre, int tipo, int es_global)
{

    PUT_COMMENT("leer (input)");
    if (es_global)
        PUT_ASM("push dword _%s", nombre);
    PUT_ASM((tipo==INT) ? "call scan_int" : "call scan_boolean");
    PUT_ASM("add esp, 4");
}

void escribir(FILE* fpasm, int es_variable, int tipo)
{
    PUT_COMMENT("escribir (output)");
    if (es_variable) {
        PUT_ASM("pop eax");
        PUT_ASM("push dword [eax]");
    }
    if (tipo == INT)
        PUT_ASM("call print_int");
    else if (tipo == BOOLEAN)
        PUT_ASM("call print_boolean");
    PUT_ASM("call print_endofline");
    PUT_ASM("add esp, 4");
}

void ifthenelse_inicio(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    PUT_COMMENT("ifthenelse_inicio");
    PUT_ASM("pop eax");
    if (exp_es_variable)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("cmp eax, 0");
    PUT_ASM("je near fin_then%d", etiqueta);
}

void ifthen_inicio(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    PUT_COMMENT("ifthen_inicio");
    PUT_ASM("pop eax");
    if (exp_es_variable)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("cmp eax, 0");
    PUT_ASM("je near fin_then%d", etiqueta);
}

void ifthen_fin(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("ifthen_fin");
    PUT_LABEL("fin_then%d", etiqueta);
}

void ifthenelse_fin_then(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("ifthenelse_fin_then");
    PUT_ASM("jmp near fin_ifelse%d", etiqueta);
    PUT_LABEL("fin_then%d", etiqueta);
}

void ifthenelse_fin(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("ifthenelse_fin");
    PUT_LABEL("fin_ifelse%d", etiqueta);
}

void while_inicio(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("while_inicio");
    PUT_LABEL("inicio_while%d", etiqueta);
    /* Ahora vendria una condicion (mayor, menor o igual, etc.) */
}

void while_exp_pila(FILE* fpasm, int exp_es_variable, int etiqueta)
{
    PUT_COMMENT("while_exp_pila");

    PUT_ASM("pop eax");
    if (exp_es_variable)
        PUT_ASM("mov dword eax, [eax]");

    PUT_ASM("cmp eax, 0");
    /* Si la condicion no se cumple, salir del loop */
    PUT_ASM("je near fin_while%d", etiqueta);
    /* Aqui vendria el contenido del while */
}

void while_fin(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("while_fin");
    /* Saltar al comienzo del loop */
    PUT_ASM("jmp near inicio_while%d", etiqueta);
    PUT_LABEL("fin_while%d", etiqueta);
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
    /* Comprobar indice inferior */
    PUT_ASM("mov ebx, %d", inicio_contador);
    PUT_ASM("cmp ebx, 0");
    PUT_ASM("jl fin_error_loop_in");

    PUT_LABEL("inicio_loop_in%d", etiqueta);
}

void loop_in_fin(FILE* fpasm, char *nombre, int inicio_contador, int fin_contador, int etiqueta)
{
    PUT_COMMENT("loop_in_fin%d", etiqueta);
    
    /* Comprobar indice superior */
    PUT_ASM("mov ebx, %d", fin_contador);
    PUT_ASM("cmp ebx, %d", inicio_contador);
    PUT_ASM("jle fin_error_loop_in");

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
    PUT_COMMENT("escribir_elemento_vector");
    NO_USO(nombre_vector);
    NO_USO(tam_max);
    // Extraemos de la pila el valor del índice a un registro
    PUT_ASM("pop dword eax");

    // En el caso en el que sea una dirección, accedemos al valor
    if (exp_es_direccion == 1)
        PUT_ASM("mov eax, dword [eax]");

    PUT_ASM("pop dword ebx");
    PUT_ASM("mov dword [ebx], eax");
}

void apilar_valor_elemento_vector(FILE* fpasm)
{
    PUT_COMMENT("apilar_valor_elemento_vector");
    PUT_ASM("pop dword eax");
    PUT_ASM("push dword [eax]");
}

void comprobar_indice_vector(FILE* fpasm, const char* nombre, int es_direccion, int tam)
{
    PUT_COMMENT("comprobar_indice_vector");
    PUT_ASM("pop dword eax");

    if (es_direccion)
        PUT_ASM("mov dword eax, [eax]");
    /* Mirar que indice no sea negativo */
    PUT_ASM("cmp eax, 0");
    PUT_ASM("jl fin_indice_fuera_rango");

    /* Mirar que indice no sea mayor que tam vector */
    PUT_ASM("cmp eax, %d", tam);
    PUT_ASM("jge fin_indice_fuera_rango");

    PUT_ASM("lea eax, [4*eax + _%s]", nombre);  // Dirección del elemento indexado en eax
    PUT_ASM("push dword eax");                  // Almacenamos la dirección al elemento
}

void declararFuncion(FILE* fpasm, char* nombre_funcion, int num_var_loc)
{
    PUT_COMMENT("declararFuncion");
    PUT_LABEL("_%s", nombre_funcion);
    PUT_ASM("push ebp");
    PUT_ASM("mov dword ebp, esp");
    PUT_ASM("sub esp, %d", 4 * num_var_loc);
}

void retornarFuncion(FILE* fpasm, int es_variable)
{
    PUT_COMMENT("retornarFuncion");
    PUT_ASM("pop dword eax");
    if (es_variable == 1)
        PUT_ASM("mov dword eax, [eax]");
    PUT_ASM("mov dword esp, ebp");
    PUT_ASM("pop dword ebp");
    PUT_ASM("ret");
}

void escribirParametro(FILE* fpasm, int direccion, int pos_parametro, int num_total_parametros)
{
    int d_ebp = 4 + 4*(num_total_parametros - pos_parametro);

    PUT_COMMENT("; escribirParametro");
    if (direccion == 1)
        PUT_ASM("lea eax, [ebp + %d]", d_ebp);
    else
        PUT_ASM("mov eax, dword [ebp + %d]", d_ebp);
    PUT_ASM("push dword eax");
}

void escribirVariableLocal(FILE* fpasm, int direccion, int posicion_variable_local)
{
    int d_ebp = 4 * posicion_variable_local;

    PUT_COMMENT("; escribirVariableLocal");
    if (direccion == 1)
        PUT_ASM("lea eax, [ebp - %d]", d_ebp);
    else
        PUT_ASM("mov eax, dword [ebp - %d]", d_ebp);
    PUT_ASM("push dword eax");
}

void asignarParametro(FILE* fpasm, int es_variable, int pos_param, int num_params)
{
    int d_ebp = 4 + 4*(num_params - pos_param);

    PUT_COMMENT("; asignarParametro");

    PUT_ASM("pop dword eax");
    if (es_variable)
        PUT_ASM("mov eax, dword [eax]");

    PUT_ASM("lea ebx, [ebp + %d]", d_ebp);
    PUT_ASM("mov [ebx], eax");
}

void asignarVariableLocal(FILE* fpasm, int es_variable, int pos_var_loc)
{
    int d_ebp = 4*pos_var_loc;

    PUT_COMMENT("; asignarVariableLocal");

    PUT_ASM("pop dword eax");
    if (es_variable)
        PUT_ASM("mov eax, dword [eax]");

    PUT_ASM("lea ebx, [ebp - %d]", d_ebp);
    PUT_ASM("mov [ebx], eax");
}

void operandoEnPilaAArgumento(FILE* fpasm, int es_variable)
{
    PUT_COMMENT("; operandoEnPilaAArgumento");
    if (es_variable == 1) {
        PUT_ASM("pop dword eax");
        PUT_ASM("mov dword eax, [eax]");
        PUT_ASM("push dword eax");
    }
}

void llamarFuncion(FILE* fpasm, char* nombre_funcion, int num_argumentos)
{
    PUT_COMMENT("llamarFuncion");
    PUT_ASM("call _%s", nombre_funcion);
    limpiarPila(fpasm, num_argumentos);
    PUT_ASM("push dword eax");
}

void limpiarPila(FILE* fpasm, int num_argumentos)
{
    PUT_COMMENT("limpiar pila");

    PUT_ASM("add esp, %d", num_argumentos * 4);
}

void init_vector(FILE* fpasm, char* nombre, int tam_inicializacion, int tam_vector)
{
    int i;
    PUT_COMMENT("inicializar vector");

    PUT_ASM("mov ebx, _%s", nombre);
    PUT_ASM("add ebx, %d", 4 * (tam_vector - 1));

    for (i = tam_vector; i > tam_inicializacion; i--) {
        PUT_ASM("mov dword [ebx], 0");
        PUT_ASM("sub ebx, 4");
    }

    for (; i > 0; i--) {
        PUT_ASM("pop dword eax");
        PUT_ASM("mov dword [ebx], eax");

        if (i != 1)
            PUT_ASM("sub ebx, 4");
    }
}

void compare_with(FILE* fpasm, int es_dir_1, int es_dir2, int etiqueta)
{
    PUT_COMMENT("compare-with %d", etiqueta);

    /* Extraer expresiones a evaluar, primero exp2 y luego exp1 */
    PUT_ASM("pop dword ebx");
    if (es_dir2)
        PUT_ASM("mov dword ebx, [ebx]");
    PUT_ASM("pop dword eax");
    if (es_dir_1)
        PUT_ASM("mov dword eax, [eax]");

    /* Comparar */
    PUT_ASM("cmp eax, ebx");
    PUT_ASM("jl cmpw_less%d", etiqueta);
    PUT_ASM("je cmpw_equal%d", etiqueta);
    PUT_ASM("jg cmpw_greater%d", etiqueta);
}

void salto_less(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("LESS %d", etiqueta);
    PUT_LABEL("cmpw_less%d", etiqueta);
}

void salto_equal(FILE* fpasm, int etiqueta)
{
    PUT_ASM("jmp fin_cmpw%d", etiqueta);
    PUT_COMMENT("EQUAL %d", etiqueta);
    PUT_LABEL("cmpw_equal%d", etiqueta);
}

void salto_greater(FILE* fpasm, int etiqueta)
{
    PUT_ASM("jmp fin_cmpw%d", etiqueta);
    PUT_COMMENT("GREATER %d", etiqueta);
    PUT_LABEL("cmpw_greater%d", etiqueta);
}

void fin_compare(FILE* fpasm, int etiqueta)
{
    PUT_COMMENT("fin compare-with%d", etiqueta);
    PUT_LABEL("fin_cmpw%d", etiqueta);
}

/* Operador de incremento: ++ */
void incremento_variable_global(FILE* fpasm, char* nombre)
{
    PUT_COMMENT("Inc variable global [%s]", nombre);

    PUT_ASM("mov dword ebx, [_%s]", nombre);
    PUT_ASM("inc ebx");
    PUT_ASM("mov dword [_%s], ebx", nombre);
}

void incremento_parametro(FILE* fpasm, int pos_param, int num_params)
{
    PUT_COMMENT("Inc parametro funcion");

    PUT_ASM("mov dword eax, 1");

    PUT_ASM("lea ebx, [ebp + %d]", 4 + 4*(num_params - pos_param));
    PUT_ASM("add eax, [ebx]");
    PUT_ASM("mov dword [ebx], eax");
}

void incremento_vector(FILE* fpasm, char* nombre, int tam_vector)
{
    int i;
    PUT_COMMENT("Inc elementos vector [%s]", nombre);
    PUT_ASM("mov eax, 1");
    PUT_ASM("mov edx, eax");
    PUT_ASM("mov ebx, _%s", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            PUT_ASM("mov eax, edx");

        PUT_ASM("add eax, [ebx]");
        PUT_ASM("mov [ebx], eax");

        if (i != (tam_vector - 1))
            PUT_ASM("add ebx, 4");
    }
}

void incremento_variable_local(FILE* fpasm, int pos_var_loc)
{
    PUT_COMMENT("Inc variable local");

    PUT_ASM("mov eax, 1");

    PUT_ASM("lea ebx, [ebp - %d]", 4 * pos_var_loc);
    PUT_ASM("add eax, [ebx]");
    PUT_ASM("mov dword [ebx], eax");
}

/* Operador de decremento: -- */
void decremento_variable_global(FILE* fpasm, char* nombre)
{
    PUT_COMMENT("Dec variable global [%s]", nombre);

    PUT_ASM("mov dword ebx, [_%s]", nombre);
    PUT_ASM("dec ebx");
    PUT_ASM("mov dword [_%s], ebx", nombre);
}

void decremento_parametro(FILE* fpasm, int pos_param, int num_params)
{
    PUT_COMMENT("Dec parametro funcion");

    PUT_ASM("mov eax, -1");

    PUT_ASM("lea ebx, [ebp + %d]", 4 + 4*(num_params - pos_param));
    PUT_ASM("add eax, [ebx]");
    PUT_ASM("mov dword [ebx], eax");
}

void decremento_vector(FILE* fpasm, char* nombre, int tam_vector)
{
    int i;
    PUT_COMMENT("Dec elementos vector [%s]", nombre);

    PUT_ASM("mov eax, -1");
    PUT_ASM("mov edx, eax");

    PUT_ASM("mov ebx, _%s", nombre);

    for (i = 0; i < tam_vector; i++) {
        if (i != 0)
            PUT_ASM("mov eax, edx");

        PUT_ASM("add eax, [ebx]");
        PUT_ASM("mov [ebx], eax");

        if (i != (tam_vector - 1))
            PUT_ASM("add ebx, 4");
    }
}

void decremento_variable_local(FILE* fpasm, int pos_var_loc)
{
    PUT_COMMENT("Dec variable local");

    PUT_ASM("mov eax, -1");

    PUT_ASM("lea ebx, [ebp - %d]", 4 * pos_var_loc);
    PUT_ASM("add eax, [ebx]");
    PUT_ASM("mov dword [ebx], eax");
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
