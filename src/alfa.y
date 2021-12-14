%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "include/alfa.h"
    #include "include/sym_t.h"
    #include "include/generacion.h"

    /* Imprime err_msg si no se cumple la condicion cond */
    #define CHECK_ERROR(cond, err_msg)\
        F_BLOCK( \
            if(!cond)
            fprintf(alfa_utils_T.ferr, "[%s]: linea %d[%d] ERROR: %s\n", 
                    (alfa_utils_T.fin_name),
                    (alfa_utils_T.line),
                    (alfa_utils_T.col),
                    (err_msg));
             YYABORT;
            \
        )
    
    /* Imprime regla gramatical en un fichero de debug */
    #define P_RULE(n, msg) \
        F_BLOCK( \
            fprintf(alfa_utils_T.fdbg, ";R%d:\t%s\n", (n), (msg)); \
        )

    int yyerror(char *s)
    {
        /* Si imprime un error morfologico, no debe imprimir uno sintactico */
        if (alfa_utils_T.error == ERR_MORFOLOGICO)
            return 0;

        alfa_utils_T.error = ERR_SINTACTICO;
        manage_error(NULL, NULL);
    }

    /* Para declaraciones */
    static TIPO tipo_actual;
    static CATEGORIA clase_actual:

    /* Para vectores */
    static int tamanio_vector_actual = 0;

    /* Etiquetas */
    static int etiqueta = 1;

    /* Funciones */
    static int pos_parametro_actual = -1;
    static int num_parametros_actual = 0;
    static int num_variables_locales_actual = 0;
	static int pos_variable_local_actual = 1;
	static int fn_return = 0;
	static int en_explist = 0;
%}

%union{
    tipo_atributos atributos;
}

/* Palabras reservadas */ 
%token TOK_MAIN               
%token TOK_INT                
%token TOK_BOOLEAN            
%token TOK_ARRAY              
%token TOK_FUNCTION           
%token TOK_IF                 
%token TOK_ELSE               
%token TOK_WHILE              
%token TOK_SCANF              
%token TOK_PRINTF             
%token TOK_RETURN             

          
%token TOK_AND                
%token TOK_OR               
%token TOK_IGUAL              
%token TOK_DISTINTO           
%token TOK_MENORIGUAL         
%token TOK_MAYORIGUAL            

%token <atributos> TOK_IDENTIFICADOR      

%token <atributos> TOK_CONSTANTE_ENTERA   
%token TOK_TRUE               
%token TOK_FALSE             

%token TOK_ERROR


%type <atributos> condicional
%type <atributos> comparacion
%type <atributos> elemento_vector
%type <atributos> exp
%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> identificador funcion
/* %type <atributos> idpf fn_name fn_declaration */
/* %type <atributos> idf_llamada_funcion */
%type <atributos> lista_expresiones resto_lista_expresiones

/* %type <atributos> if_exp if_exp_sentencias */
%type <atributos> while
/* %type <atributos> while_exp */

/* %type <atributos> compare_with compare_less compare_equal compare_greater */
/* %type <atributos> inicializacion_vector lista_inicializaciones */


%left TOK_AND TOK_OR
%left '!'
%left '+' '-'
%left '*' '/'

%start programa

%%

/* Seccion de reglas */

programa : TOK_MAIN '{' iniciar declaraciones dec_vars funciones wrt_main sentencias final '}' {P_RULE(1,"<programa> ::= main { <declaraciones> <funciones> <sentencias> }");};

iniciar :  {
                sym_t_create();
                escribir_subseccion_data(alfa_utils_T.fasm);
                escribir_cabecera_bss(alfa_utils_T.fasm);
            }

final :    {
                sym_t_free();
                escribir_fin(alfa_utils_T.fasm);
            }

dec_vars:   {
                char** simbolos = sym_t_getGlobalSymbols();
                int i = 0;
                sym_info* sym = NULL;

                for (i = 0; simbolos[i] != NULL; i++) {
                    sym = sym_t_get_symb(simbolos[i]);
                    if (sym && VARIABLE == sym->elem)
                        declarar_variable(alfa_utils_T.fasm, sym->lexema, sym->tipo, sym->size);
                }
                escribir_segmento_codigo(alfa_utils_T.fasm);
            }

wrt_main:   {   escribir_inicio_main(alfa_utils_T.fasm);}

declaraciones : declaracion {P_RULE(2,"<declaraciones> ::= <declaracion>");}
              |   declaracion declaraciones {P_RULE(3,"<declaraciones> ::= <declaracion> <declaraciones>");};

declaracion : clase identificadores ';' {P_RULE(4,"<declaracion> ::= <clase> <identificadores> ;");};

clase : clase_escalar {P_RULE(5,"<clase> ::= <clase_escalar>"); clase_actual = ESCALAR;}
      | clase_vector {P_RULE(7,"<clase> ::= <clase_vector>"); clase_actual = VECTOR;};

clase_escalar : tipo {P_RULE(9,"<clase_escalar> ::= <tipo>");};

tipo : TOK_INT {P_RULE(10,"<tipo> ::= int"); tipo_actual = ENTERO;}
     | TOK_BOOLEAN {P_RULE(11,"<tipo> ::= boolean"); tipo_actual = BOOLEANO;};

clase_vector : TOK_ARRAY tipo '[' TOK_CONSTANTE_ENTERA ']' {
        P_RULE(15,"<clase_vector> ::= array <tipo> [ constante_entera ]");
        tamanio_vector_actual = $4.valor_entero;
        CHECK_ERROR(tamanio_vector_actual >= 1, "Tamaño de vector invalido");
        CHECK_ERROR(tamanio_vector_actual <= MAX_LONG_VECTOR, "Tamaño de vector invalido");
    };

identificadores : identificador {P_RULE(18,"<identificadores> ::= <identificador>");}
                | identificador ',' identificadores {P_RULE(19,"<identificadores> ::= <identificador> , <identificadores>");};

funciones : funcion funciones {P_RULE(20,"<funciones> ::= <funcion> <funciones>");}
          | /* lambda */ {P_RULE(21,"<funciones> ::=");};

funcion : TOK_FUNCTION tipo identificador '(' parametros_funcion ')' '{' declaraciones_funcion sentencias '}'
        {P_RULE(22,"<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }");};

parametros_funcion : parametro_funcion resto_parametros_funcion {P_RULE(23,"<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                   | /* lambda */ {P_RULE(24,"<parametros_funcion> ::=");};

resto_parametros_funcion : ';' parametro_funcion resto_parametros_funcion {P_RULE(25,"<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                         | /* lambda */ {P_RULE(26,"<resto_parametros_funcion> ::=");};

parametro_funcion : tipo identificador {P_RULE(27,"<parametro_funcion> ::= <tipo> <identificador>");};

declaraciones_funcion : declaraciones {P_RULE(28,"<declaraciones_funcion> ::= <declaraciones>");}
                      | /* lambda */ {P_RULE(29,"<declaraciones_funcion> ::=");};

sentencias : sentencia {P_RULE(30,"<sentencias> ::= <sentencia>");}
           | sentencia sentencias {P_RULE(31,"<sentencias> ::= <sentencia> <sentencias>");};

sentencia : sentencia_simple ';' {P_RULE(32,"<sentencia> ::= <sentencia_simple> ;");}
          | bloque {P_RULE(33,"<sentencia> ::= <bloque>");};

sentencia_simple : asignacion {P_RULE(34,"<sentencia_simple> ::= <asignacion>");}
                 | lectura {P_RULE(35,"<sentencia_simple> ::= <lectura>");}
                 | escritura {P_RULE(36,"<sentencia_simple> ::= <escritura>");}
                 | retorno_funcion {P_RULE(38,"<sentencia_simple> ::= <retorno_funcion>");};

bloque : condicional {P_RULE(40,"<bloque> ::= <condicional>");}
       | bucle {P_RULE(41,"<bloque> ::= <bucle>");};

asignacion : TOK_IDENTIFICADOR '=' exp {
                P_RULE(43,"<asignacion> ::= identificador = <exp>");
                char err_msg[128] = "";

                /* Comprueba que exista el identificador */
                sprintf(err_msg, "Identificador [%d] inexistente", $1.lexema);
                sym = sym_t_get_symb($1.lexema);
                CHECK_ERROR(sym==NULL, err_msg);

                /* Comprueba que no sea ni FUNCION ni VECTOR */
                sprintf(err_msg, "Identificador [%d] no es variable", $1.lexema);
                CHECK_ERROR(sym.CATEGORIA==VECTOR, err_msg);
                CHECK_ERROR(sym.ELEMENTO==FUNCION, err_msg);

                /* Asignar */
                if (sym.is_var_loc!=-1) //comprueba si es variable global
                    asignar(alfa_utils_T.fasm, $1.lexema, $3.es_direccion)
                else //en caso contrario asigna destino en pila al ser local
                    asignarDestinoEnPila(alfa_utils_T.fasm, $3.es_direccion)
            }
           | elemento_vector '=' exp {
                P_RULE(44,"<parametros_funcion> ::= <elemento_vector> = <exp>");
                char err_msg[128] = "";

                /* Comprueba que exista el identificador */
                sprintf(err_msg, "Identificador [%d] inexistente", $1.lexema);
                sym = sym_t_get_symb($1.lexema);
                CHECK_ERROR(sym==NULL, err_msg);

                /* Comprueba que no sea FUNCION */
                sprintf(err_msg, "Identificador [%d] no es variable", $1.lexema);
                CHECK_ERROR(sym.ELEMENTO==FUNCION, err_msg);

                escribir_elemento_vector(alfa_utils_T.fasm, $3.lexema, sym.size, $3.es_direccion)
            };

elemento_vector : TOK_IDENTIFICADOR '[' exp ']' {P_RULE(48,"<elemento_vector> ::= identificador [ <exp> ]");};

condicional : TOK_IF '(' exp ')' '{' sentencias '}' {P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");}
            | TOK_IF '(' exp ')' '{' sentencias '}' TOK_ELSE '{' sentencias '}'
                {P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");};

bucle : TOK_WHILE '(' exp ')' '{' sentencias '}' {P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");};

lectura : TOK_SCANF TOK_IDENTIFICADOR {
            P_RULE(54,"<lectura> ::= scanf identificador"); 

            /* Buscar si el identificador existe */
            char err_msg[125] = "";
            sprintf(err_msg, "Identificador [%d] no existe", $1.lexema);
            sym_info* info = sym_t_check($2.lexema);
            CHECK_ERROR(info ==NULL, err_msg);

            /* Si el identificador existe */
            CHECK_ERROR((info->elem != FUNCION), "scanf no admite funciones como entrada");
            CHECK_ERROR((info->catg != VECTOR), "scanf no admite vectores como entrada");

            /* NASM: Apilar direccion de identificador */
            if (info->elem == PARAMETRO) {
                escribirParametro(alfa_utils_T.fasm, pos_parametro_actual, info->num_params);
            } else if (info->elem == VARIABLE) {
                /* Si es variable global, su direccion es su lexema */
                if (info->is_var_loc == -1)
                    
                else
                    escribirVariableLocal(alfa_utils_T.fasm, pos_variable_local_actual);
            }

            /* NASM: llamar a funcion scanf de alfalib.o */
            if (info->tipo == INT) {
                /* Llamar a scan_int */

            } else if (info->tipo == BOOLEAN) {
                /* Llamar a scan_bool */

            }
            /* NASM: Restaurar la pila */
        };

escritura : TOK_PRINTF exp {P_RULE(56,"<escritura> ::= printf <exp>");};

retorno_funcion : TOK_RETURN exp {P_RULE(61,"<retorno_funcion> ::= return <exp>");};

exp : exp '+' exp {P_RULE(72,"<exp> ::= <exp> + <exp>");}
    | exp '-' exp {P_RULE(73,"<exp> ::= <exp> - <exp>");}
    | exp '/' exp {P_RULE(74,"<exp> ::= <exp> / <exp>");}
    | exp '*' exp {P_RULE(75,"<exp> ::= <exp> * <exp>");}
    | '-' exp {P_RULE(76,"<exp> ::= - <exp>");}
    | exp TOK_AND exp {P_RULE(77,"<exp> ::= <exp> && <exp>");}
    | exp TOK_OR exp {P_RULE(78,"<exp> ::= <exp> || <exp>");}
    | '!' exp {P_RULE(79,"<exp> ::= ! <exp>");}
    | TOK_IDENTIFICADOR {P_RULE(80,"<exp> ::= identificador");}
    | constante {P_RULE(81,"<exp> ::= <constante>");}
    | '(' exp ')' {P_RULE(82,"<exp> ::= ( <exp> )");}
    | '(' comparacion ')' {P_RULE(83,"<exp> ::= ( <comparacion> )");}
    | elemento_vector {P_RULE(85,"<exp> ::= <elemento_vector>");}
    | identificador '(' lista_expresiones ')' {P_RULE(88,"<identificador> ( <lista_expresiones> )");};

lista_expresiones : exp resto_lista_expresiones {P_RULE(89,"<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
                  | /* lambda */ {P_RULE(90,"<lista_expresiones> ::=");};

resto_lista_expresiones : ',' exp resto_lista_expresiones {P_RULE(91,"<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>");}
                        | /* lambda */ {P_RULE(92,"<resto_lista_expresiones> ::=");};

comparacion : exp TOK_IGUAL exp {P_RULE(93,"<comparacion> ::= <exp> == <exp>");}
            | exp TOK_DISTINTO exp {P_RULE(94,"<comparacion> ::= <exp> != <exp>");}
            | exp TOK_MENORIGUAL exp {P_RULE(95,"<comparacion> ::= <exp> <= <exp>");}
            | exp TOK_MAYORIGUAL exp {P_RULE(96,"<comparacion> ::= <exp> >= <exp>");}
            | exp '<' exp {P_RULE(97,"<comparacion> ::= <exp> < <exp>");}
            | exp '>' exp {P_RULE(98,"<comparacion> ::= <exp> > <exp>");};

constante : constante_logica {
                P_RULE(99,"<constante> ::= <constante_logica>");
                $$.tipo = $1.tipo;
                $$.es_direccion = $1.es_direccion;
                $$.valor_entero = $1.valor_entero;
            }
          | constante_entera {
                P_RULE(100,"<comparacion> ::= <constante_entera>");
                $$.tipo = $1.tipo;
                $$.es_direccion = $1.es_direccion;
            };

constante_logica : TOK_TRUE {
                        P_RULE(102,"<constante_logica> ::= true");
                        $$.tipo = BOOLEANO;
                        $$.es_direccion = 0;
                        $$.valor_entero = 1;
                    }
                 | TOK_FALSE {
                        P_RULE(103,"<constante_logica> ::= false");
                        $$.tipo = BOOLEANO;
                        $$.es_direccion = 0;
                        $$.valor_entero = 0;
                    };

constante_entera : TOK_CONSTANTE_ENTERA {
                        P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");
                        $$.tipo = ENTERO;
                        $$.es_direccion = 0;
                        $$.valor_entero = $1.valor_entero
                    };

identificador : TOK_IDENTIFICADOR {
    P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        char err_msg[125] = "";
        sprintf(err_msg, "Identificador [%d] duplicado", $1.lexema);
        CHECK_ERROR(sym_t_check($1.lexema)!=NULL, err_msg);

        //si llega a aqui el check error lo permite
        sym_info* sym = NULL;
        //DUDA
        sym=sym_info_create($1.lexema, VARIABLE, tipo_actual, clase_actual, -1, -1, -1)
        CHECK_ERROR(sym==NULL, "Sin memoria");

        sym_t_add_symb(sym) //insertas el símbolo donde toque (global o local, de eso se encarga la tabla)
        pos_variable_local_actual++;
    };

%%