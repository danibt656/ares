%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "include/alfa.h"
    #include "include/sym_t.h"
    #include "include/generacion.h"
    #define CHECK_ERROR(cond, n, err_msg)\
        F_BLOCK( \
            if(!cond)
            fprintf(alfa_utils_T.ferr, ";R%d:\t%s\n", (n), (err_msg));
             YYABORT;
            \
        )
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
    static int clase_actual, tipo_actual;

    /* Etiquetas */
    static int etiqueta = 1;

    /* Funciones */
    static int pos_parametro_actual = -1;
    static int num_parametros_actual = 0;
    static int num_variables_locales_actual = 0;
	static int pos_variable_local_actual = 1;
	static int fn_return = 0;
	static int en_explist = 0;
    static int tamanio_vector_actual = 0;
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


/*%type <atributos> condicional
%type <atributos> comparacion
%type <atributos> elemento_vector
%type <atributos> exp
%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> identificador_nuevo identificador_uso idpf fn_name fn_declaration funcion
%type <atributos> idf_llamada_funcion
%type <atributos> lista_expresiones resto_lista_expresiones

%type <atributos> if_exp if_exp_sentencias
%type <atributos> while_exp while

%type <atributos> compare_with compare_less compare_equal compare_greater
%type <atributos> inicializacion_vector lista_inicializaciones*/


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

clase_vector : TOK_ARRAY tipo '[' constante_entera ']' {P_RULE(15,"<clase_vector> ::= array <tipo> [ <constante_entera> ]");};

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

asignacion : identificador '=' exp {P_RULE(43,"<asignacion> ::= <identificador> = <exp>");}
           | elemento_vector '=' exp {P_RULE(44,"<parametros_funcion> ::= <elemento_vector> = <exp>");};

elemento_vector : identificador '[' exp ']' {P_RULE(48,"<elemento_vector> ::= <identificador> [ <exp> ]");};

condicional : TOK_IF '(' exp ')' '{' sentencias '}' {P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");}
            | TOK_IF '(' exp ')' '{' sentencias '}' TOK_ELSE '{' sentencias '}'
                {P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");};

bucle : TOK_WHILE '(' exp ')' '{' sentencias '}' {P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");};

lectura : TOK_SCANF identificador { P_RULE(54,"<lectura> ::= scanf <identificador>"); };

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
    | identificador {P_RULE(80,"<exp> ::= <identificador>");}
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

constante : constante_logica {P_RULE(99,"<constante> ::= <constante_logica>");}
          | constante_entera {P_RULE(100,"<comparacion> ::= <constante_entera>");};

constante_logica : TOK_TRUE {P_RULE(102,"<constante_logica> ::= true");}
                 | TOK_FALSE {P_RULE(103,"<constante_logica> ::= false");};

constante_entera : TOK_CONSTANTE_ENTERA {P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");};

identificador : TOK_IDENTIFICADOR {
    P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        CHECK_ERROR(sym_t_check($1.lexema)!=NULL, 109, "No se permiten duplicados cerdo")
        //si llega a aqui el check error lo permite
        
    };

%%