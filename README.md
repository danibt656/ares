# Ares
### *The* Ares *Programming Language*

***

## Makefile

Se incluye un fichero Makefile con las siguientes reglas (para verlas por terminal se puede ejecutar el comando `make help`):

+ all: compila todo y genera el ejecutable `ares`. Genera un fichero debug con las trazas de flex y bison llamado `debug`
+ clean: borra todos los ficheros generados
+ runf: compila un fichero de prueba en ARES y lo ejecuta. 
  
  Uso: `make runf src=<FICHERO_ARES>`

  El fichero ejecutable generado se llama 'exe'
+ valgrind: ejecuta valgrind en el compilador sobre un fichero dado
+ reset: versión concisa que ejecuta primero la regla `make clean` y después la regla `make all`

## Generacion del ejecutable `./ares`

Para generar el ejecutable con el compilador de ARES, basta con ejecutar la correspondiente regla del makefile (conviene asegurarse antes de que todos los ficheros objeto y ejecutables antiguos estén eliminados con `make clean`):

```
make clean; make all
```

## Compilación de programas ARES

> **Es ***muy*** importante que los programas de entrada acaben con la extensión `.ares`**

Si se prefiere dar un nombre propio al ejecutable y no usar la regla `make runf` (ver más abajo, *"Ejecución de tests"*), se puede hacer uso del ejecutable `ares`:

```
./ares <entrada_source> <salida>
```

Los argumentos de este programa son los siguientes:

+ **entrada_source**: Fichero fuente escrito en lenguaje ARES
+ **salida**: fichero donde se genera el ejecutable. Para ejecutarlo, utilizar `./<salida>`

## Ejecucion de tests

En el directorio tests/ hay varios programas ARES que se pueden compilar con el ejecutable generado. Para compilar un programa ARES y ejecutarlo, se puede usar la regla del makefile para ello:

```
make runf src=<SOURCECODE_ARES>
```

Por ejemplo, para ejecutar el test **fibonacci.ares** contenido en la carpeta tests/:

```
make runf src=tests/fibonacci.ares
```

Esto generará un archivoejecutable llamado 'exe' y lo ejecutará automáticamente.