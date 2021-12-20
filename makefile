.DEFAULT_GOAL = all
.PHONY: all clean help nasm astyle
.SUFFIXES:

## Directorios
BDIR := .
SDIR := src
IDIR := include
ODIR := obj
EDIR := src
NDIR := .

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

EXES := alfa.c

EXES := $(patsubst %,$(EDIR)/%,$(EXES))
EOBJ := $(patsubst $(EDIR)/%.c,$(ODIR)/%.o,$(EXES))
EBIN := $(patsubst $(EDIR)/%.c,$(BDIR)/%,$(EXES))

DEPEND_FILES := $(wildcard $(ODIR)/*.d)

FLEX_SOURCES := $(wildcard $(SDIR)/*.l)
FLEX_GENERATED_FILES := $(FLEX_SOURCES:.l=.yy.c)
FLEX_OBJ := $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(FLEX_GENERATED_FILES))

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

$(FLEX_OBJ): CFLAGS += -Wno-sign-compare -D_XOPEN_SOURCE=700

all: CFLAGS += -g

all: $(EBIN)

nasm: $(NASM_BIN)

$(SOBJ):$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(SDIR)/%.yy.c: $(SDIR)/%.l $(BISON_GENERATED_FILES)
	$(LEX) $(LFLAGS) -o $@ $<

$(SDIR)/%.tab.c: $(SDIR)/%.y
	$(BISON) $(BFLAGS) -o $@ $<
	# mv $(BISON_HEADERS_ORIG) $(IDIR)
	# mv $(BISON_OUTPUT_ORIG) $(MDIR)
	# mv $(BISON_GRAPH_ORIG) $(MDIR)

$(EOBJ):$(ODIR)/%.o: $(EDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(EBIN):$(BDIR)/%: $(ODIR)/%.o $(SOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(NASM_OBJ):$(ODIR)/%.o: $(NDIR)/%.nasm
	$(NASM) $(NFLAGS) -o $@ $<

$(NASM_BIN): $(BDIR)/%: $(ODIR)/%.o $(ALFALIB)
	$(CC) $(CCNASMFLAGS) -o $@ $^ $(CFLAGS)

clean:
	@$(RM) alfa exe
	@$(RM) $(SOBJ) $(EOBJ) $(EBIN) $(DEPEND_FILES)
	@$(RM) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES)
	@$(RM) $(BISON_HEADERS) $(BISON_HEADERS_ORIG) $(BISON_OUTPUT) $(BISON_OUTPUT_ORIG)
	@$(RM) $(BISON_GRAPH_ORIG) $(BISON_GRAPH)
	@$(RM) $(NASM_OBJ) $(NASM_BIN) debug *.asm *.o

help:
	@echo "Flags de Makefile:"
	@echo "    all                 - compila todo y genera el ejecutable alfa"
	@echo "                             -> Genera un fichero debug con las trazas de flex y bison"
	@echo "    clean               - borra todos los ficheros generados"
	@echo "    compile_file        - compila un fichero de prueba en ALFA y lo ejecuta"
	@echo "                             -> Uso: make compile_file src=<FICHERO_ALFA>"
	@echo "    valgrind            - ejecuta valgrind en el compilador sobre un fichero dado"

compile_file:
	@echo "-------------------------------"
	./alfa $(src) exe.asm
	nasm -f elf32 exe.asm
	gcc -m32 -o exe exe.o obj/alfalib.o
	@echo "-------------------------------"
	./exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./alfa $(src) exe.asm

CFLAGS += -MMD
-include $(DEPEND_FILES)
