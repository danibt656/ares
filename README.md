# PAUTLEN_Proyecto
### Proyecto de Autómatas y Lenguajes

*Author: Carlos Anivarro*

*Author: Daniel Barahona*

*Author: David Garitagoitia*
***
## Makefile

Se incluye un fichero Makefile con las siguientes reglas:
+ all: compila todo y genera el ejecutable `alfa`. Genera un fichero debug con las trazas de flex y bison llamado `debug`
+ clean: borra todos los ficheros generados
+ compile_file: compila un fichero de prueba en ALFA y lo ejecuta. Uso: make compile_file src=<FICHERO_ALFA>
+ valgrind: ejecuta valgrind en el compilador sobre un fichero dado

## Generacion del ejecutable

Para generar el ejecutable con el compilador de ALFA, basta con ejecutar la correspondiente regla del makefile (conviene asegurarse antes de que todos los ficheros objeto y ejecutables antiguos estén eliminados con `make clean`):

```
make clean; make all
```

## Ejecucion de pruebas

En el directorio tests hay varios programas ALFA que se pueden compilar con el ejecutable generado. Para compilar un programa ALFA a NASM, generar el ejecutable con gcc y ejecutarlo, se puede usar la regla del makefile para ello:

```
make compile_file src=<SOURCECODE_ALFA>
```

Por ejemplo, para ejecutar el test **fibonacci.alfa**:

```
make compile_file src=tests/fibonacci.alfa
```
