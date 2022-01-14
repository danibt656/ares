.DEFAULT_GOAL = install
.PHONY: install clean help nasm astyle
.SUFFIXES:

## Directorios
DBIN := .
DNASM := .
DSRC := src
DINC := include
DOBJ := obj
DEXE := src

# Flags
CC       ?= gcc
LEX      ?= flex
BISON    ?= bison
CFLAGS   := -std=gnu99 -Iinclude -pedantic -Wall -Wextra
LDFLAGS  :=
LFLAGS   :=
BFLAGS   := -dyv
RM       := rm -fv
NASM     := nasm
NFLAGS   := -f elf32
CCNASMFLAGS := -m32

ARESLIB     := $(DOBJ)/areslib.o

EXES := ares.c
EXES := $(patsubst %,$(DEXE)/%,$(EXES))
EOBJ := $(patsubst $(DEXE)/%.c,$(DOBJ)/%.o,$(EXES))
EBIN := $(patsubst $(DEXE)/%.c,$(DBIN)/%,$(EXES))

DEPENDENCIAS := $(wildcard $(DOBJ)/*.d)

FLEX_SOURCES := $(wildcard $(DSRC)/*.l)
FLEX_GENERATED_FILES := $(FLEX_SOURCES:.l=.yy.c)
FLEX_OBJ := $(patsubst $(DSRC)/%.c, $(DOBJ)/%.o, $(FLEX_GENERATED_FILES))

BISON_SOURCES := $(wildcard $(DSRC)/*.y)
BISON_GENERATED_FILES := $(BISON_SOURCES:.y=.tab.c)
BISON_OBJ := $(patsubst $(DSRC)/%.c, $(DOBJ)/%.o, $(BISON_GENERATED_FILES))
BISON_HEADERS_ORIG := $(patsubst %.c,%.h, $(BISON_GENERATED_FILES))
BISON_HEADERS := $(patsubst $(DSRC)/%,$(DINC)/%, $(BISON_HEADERS_ORIG))
BISON_OUTPUT_ORIG := $(patsubst %.tab.c,%.output, $(BISON_GENERATED_FILES))
BISON_OUTPUT := $(patsubst $(DSRC)/%,$(MDIR)/%, $(BISON_OUTPUT_ORIG))

SRCS := $(filter-out $(EXES) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES), $(wildcard $(DSRC)/*.c))
SOBJ := $(patsubst $(DSRC)/%.c,$(DOBJ)/%.o,$(SRCS) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES))

NASM_SOURCES := $(wildcard $(DNASM)/*.nasm)
NASM_OBJ := $(patsubst $(DNASM)/%.nasm, $(DOBJ)/%.o, $(NASM_SOURCES))
NASM_BIN := $(patsubst %.nasm, %, $(NASM_SOURCES))

$(FLEX_OBJ): CFLAGS += -Wno-sign-compare -D_XOPEN_SOURCE=700

install: CFLAGS += -g

install: $(EBIN)

nasm: $(NASM_BIN)

$(SOBJ):$(DOBJ)/%.o: $(DSRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DSRC)/%.yy.c: $(DSRC)/%.l $(BISON_GENERATED_FILES)
	$(LEX) $(LFLAGS) -o $@ $<

$(DSRC)/%.tab.c: $(DSRC)/%.y
	$(BISON) $(BFLAGS) -o $@ $<

$(EOBJ):$(DOBJ)/%.o: $(DEXE)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(EBIN):$(DBIN)/%: $(DOBJ)/%.o $(SOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(NASM_OBJ):$(DOBJ)/%.o: $(DNASM)/%.nasm
	$(NASM) $(NFLAGS) -o $@ $<

$(NASM_BIN): $(DBIN)/%: $(DOBJ)/%.o $(ARESLIB)
	$(CC) $(CCNASMFLAGS) -o $@ $^ $(CFLAGS)

# Borrar ficheros generados con make install
clean:
	@$(RM) ares exe
	@$(RM) $(SOBJ) $(EOBJ) $(EBIN) $(DEPENDENCIAS)
	@$(RM) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES)
	@$(RM) $(BISON_HEADERS) $(BISON_HEADERS_ORIG) $(BISON_OUTPUT) $(BISON_OUTPUT_ORIG)
	@$(RM) $(NASM_OBJ) $(NASM_BIN) debug *.asm *.o

# Borrar ficheros generados y volver a compilar
reset:
	make clean
	make install

# Ayuda
help:
	@echo "Flags de Makefile:"
	@echo "    install              - compila todo y genera el ejecutable ares"
	@echo "                             -> Genera un fichero debug con las trazas de flex y bison"
	@echo "    clean               - borra todos los ficheros generados"
	@echo "    runf                - compila un fichero de prueba en ARES y lo ejecuta"
	@echo "                             -> Uso: make runf src=<FICHERO_ARES>"
	@echo "                             -> El fichero ejecutable se llama 'exe' y se encuentra en el directorio /ares/build"
	@echo "    valgrind            - ejecuta valgrind en el compilador sobre un fichero dado"
	@echo "    reset               - ejecuta primero la regla 'make clean' y luego 'make install'"

runf:
	@echo "-------------------------------"
	./ares -f $(src) -o exe
	@echo "-------------------------------"
	./exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./ares $(src) exe.asm

CFLAGS += -MMD
-include $(DEPENDENCIAS)
