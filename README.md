# ARES

***

## Makefile

Se incluye un fichero Makefile con las siguientes reglas (para verlas por terminal se puede ejecutar el comando `make help`):

+ all: compila todo y genera el ejecutable `ares`. Genera un fichero debug con las trazas de flex y bison llamado `debug`
+ clean: borra todos los ficheros generados
+ compile_file: compila un fichero de prueba en ALFA y lo ejecuta. Uso: make compile_file src=<FICHERO_ALFA>
+ valgrind: ejecuta valgrind en el compilador sobre un fichero dado

## Generacion del ejecutable `./ares`

Para generar el ejecutable con el compilador de ALFA, basta con ejecutar la correspondiente regla del makefile (conviene asegurarse antes de que todos los ficheros objeto y ejecutables antiguos estén eliminados con `make clean`):

```
make clean; make all
```

## Generacion de codigo ensamblador

> **Es ***muy*** importante que los programas de entrada acaben con la extensión `.ares`**

Si solo se quiere obtener el fichero con el código NASM (y luego linkar éste a mano), se puede hacer uso del ejecutable `ares`:

```
./ares <entrada_source> <salida_asm>
```

Los argumentos de este programa son los siguientes:

+ <entrada_source>: Fichero fuente escrito en lenguaje ALFA
+ <salida_asm> fichero donde se genera el codigo ensamblador en NASM que funcionalmente es equivalente al programa contenido en el fichero de entrada ALFA.

## Ejecucion de pruebas

En el directorio tests/ hay varios programas ALFA que se pueden compilar con el ejecutable generado. Para compilar un programa ALFA a NASM, generar el ejecutable con gcc y ejecutarlo, se puede usar la regla del makefile para ello:

```
make compile_file src=<SOURCECODE_ALFA>
```

Por ejemplo, para ejecutar el test **fibonacci.ares** contenido en la carpeta tests/:

```
make compile_file src=tests/fibonacci.ares
```