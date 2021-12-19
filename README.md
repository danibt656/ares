# PAUTLEN_Proyecto
## Proyecto de Autómatas y Lenguajes

*Author: Carlos Anivarro*

*Author: Daniel Barahona*

*Author: David Garitagoitia*


Se incluye un fichero Makefile con las siguientes reglas:
+ all: compila todo y genera el ejecutable `alfa`. Genera un fichero debug con las trazas de flex y bison llamado `debug`
+ clean: borra todos los ficheros generados
+ compile_file: compila un fichero de prueba en ALFA y lo ejecuta. Uso: make compile_file src=<FICHERO_ALFA>
+ valgrind: ejecuta valgrind en el compilador sobre un fichero dado
