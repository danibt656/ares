.DEFAULT_GOAL = all
.PHONY: all test debug clean zip help graph nasm astyle
.SUFFIXES:

## Definiciones de carpetas
BDIR := .
SDIR := src
IDIR := include
ODIR := obj
EDIR := src
NDIR := .

# Fichero con configuracion de astyle
# Respeta la variable de entorno en caso de estar definida
ARTISTIC_STYLE_OPTIONS ?= .astylerc


## Nombre fichero compresion
ZIP := ../G8_CARLOS_ANIVARRO_DANIEL_BARAHONA_DAVID_GARITAGOITIA.zip

## Configuracion de las herramientas
CC       ?= gcc
LEX      ?= flex
BISON    ?= bison
CFLAGS   := -std=c99 -Iinclude -pedantic -Wall -Wextra
LDFLAGS  :=
LFLAGS   :=
BFLAGS   := -d -y -v -g
RM       := rm -fv
NASM     := nasm
NFLAGS   := -f elf32
CCNASMFLAGS := -m32

ALFALIB     := $(ODIR)/alfalib.o

## Mains objetivos de make all
EXES := alfa.c

EXES := $(patsubst %,$(EDIR)/%,$(EXES))
EOBJ := $(patsubst $(EDIR)/%.c,$(ODIR)/%.o,$(EXES))
EBIN := $(patsubst $(EDIR)/%.c,$(BDIR)/%,$(EXES))

DEPEND_FILES := $(wildcard $(ODIR)/*.d)

## Definiciones de objetivos
FLEX_SOURCES := $(wildcard $(SDIR)/*.l)
FLEX_GENERATED_FILES := $(FLEX_SOURCES:.l=.yy.c)
FLEX_OBJ := $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(FLEX_GENERATED_FILES))

## Definiciones de objetivos
BISON_SOURCES := $(wildcard $(SDIR)/*.y)
BISON_GENERATED_FILES := $(BISON_SOURCES:.y=.tab.c)
BISON_OBJ := $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(BISON_GENERATED_FILES))
BISON_HEADERS_ORIG := $(patsubst %.c,%.h, $(BISON_GENERATED_FILES))
BISON_HEADERS := $(patsubst $(SDIR)/%,$(IDIR)/%, $(BISON_HEADERS_ORIG))
BISON_OUTPUT_ORIG := $(patsubst %.tab.c,%.output, $(BISON_GENERATED_FILES))
BISON_OUTPUT := $(patsubst $(SDIR)/%,$(MDIR)/%, $(BISON_OUTPUT_ORIG))

BISON_GRAPH_ORIG := $(patsubst %.tab.c,%.dot, $(BISON_GENERATED_FILES))
BISON_GRAPH := $(patsubst $(SDIR)/%,$(MDIR)/%, $(BISON_GRAPH_ORIG))
DOT := dot
DOTFLAGS := -O -Tpdf

SRCS := $(filter-out $(EXES) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES), $(wildcard $(SDIR)/*.c))
SOBJ := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRCS) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES))


NASM_SOURCES := $(wildcard $(NDIR)/*.nasm)
NASM_OBJ := $(patsubst $(NDIR)/%.nasm, $(ODIR)/%.o, $(NASM_SOURCES))
NASM_BIN := $(patsubst %.nasm, %, $(NASM_SOURCES))


# Flags de compilacion extras para ficheros generados por flex
$(FLEX_OBJ): CFLAGS += -Wno-sign-compare -D_XOPEN_SOURCE=700

## Flags adicionales
all: CFLAGS += -O3 -DNDEBUG
test: CFLAGS += -g
debug: CFLAGS += -g

## Objetivos
all: $(EBIN)

nasm: $(NASM_BIN)

debug: $(EBIN)

## Deteccion automatica de dependencias (_solo_ entre ficheros .c y .h)
# La siguiente regla le dice a make como generar el fichero .depend
# Solo ejecuta el cpp sobre los fuentes, y acumula las dependencias
# (flag -MM) en un formato que puede procesar make
#CFLAGS += -MMD
# Lo incluimos en este make solo si no estamos haciendo un clean
# (para no crearlo y destruirlo inmediatamente)
# y lo prefijamos con un - para que no falle aunque no se pueda incluir
# (como la primera vez que se ejecuta este makefile)
#ifneq ($(MAKECMDGOALS),clean)
#-include $(patsubst $(wildcard $(SDIR)/*.c,$(ODIR)/%.o),:.c=.d)
#endif

## Reglas de compilacion

## Compilacion de .c de src
$(SOBJ):$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

## Generacion de .yy.c a partir de .l
## Debe estar generada la cabecera de bison
$(SDIR)/%.yy.c: $(SDIR)/%.l $(BISON_GENERATED_FILES)
	$(LEX) $(LFLAGS) -o $@ $<

## Generacion de .tab.c a partir de .y
$(SDIR)/%.tab.c: $(SDIR)/%.y
	$(BISON) $(BFLAGS) -o $@ $<
	# mv $(BISON_HEADERS_ORIG) $(IDIR)
	# mv $(BISON_OUTPUT_ORIG) $(MDIR)
	# mv $(BISON_GRAPH_ORIG) $(MDIR)

## Compilacion de .c de exes
$(EOBJ):$(ODIR)/%.o: $(EDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

## Linkado de exes
$(EBIN):$(BDIR)/%: $(ODIR)/%.o $(SOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


## Compilacion de .nasm
$(NASM_OBJ):$(ODIR)/%.o: $(NDIR)/%.nasm
	$(NASM) $(NFLAGS) -o $@ $<

## Linkado de los nasm junto con alfalib
$(NASM_BIN): $(BDIR)/%: $(ODIR)/%.o $(ALFALIB)
	$(CC) $(CCNASMFLAGS) -o $@ $^ $(CFLAGS)

clean:
	@$(RM) alfa exe
	@$(RM) $(SOBJ) $(EOBJ) $(EBIN) $(DEPEND_FILES)
	@$(RM) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES)
	@$(RM) $(BISON_HEADERS) $(BISON_HEADERS_ORIG) $(BISON_OUTPUT) $(BISON_OUTPUT_ORIG)
	@$(RM) $(BISON_GRAPH_ORIG) $(BISON_GRAPH)
	@$(RM) $(NASM_OBJ) $(NASM_BIN) debug *.asm

help:
	@echo "Posibles comandos:"
	@echo "    	all      			- construye el/los ejecutable $(EBIN)"
	@echo "    	debug    			- compila todo usando con simbolos de depuracion"
	@echo "    	clean    			- borra todos los ficheros generados"
	@echo "    	compile_file		- compila un fichero de prueba en ALFA y lo ejecuta"
	@echo "		valdrind			- ejecuta valgrind en el compilador sobre un fichero dado"
	@echo "	   							- USO: make compile_file src=<FICHERO_ALFA>"

compile_file:
	./alfa $(src) exe.asm
	nasm -f elf32 exe.asm
	gcc -m32 -o exe exe.o obj/alfalib.o 
	./exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./alfa $(src) exe.asm

## Deteccion de dependencias automatica, v2
CFLAGS += -MMD
-include $(DEPEND_FILES)
