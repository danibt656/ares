.DEFAULT_GOAL = all
.PHONY: all clean help nasm astyle
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

ARTISTIC_STYLE_OPTIONS ?= .astylerc

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

all: CFLAGS += -g

all: $(EBIN)

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

# Borrar ficheros generados con make all
clean:
	@$(RM) ares exe
	@$(RM) $(SOBJ) $(EOBJ) $(EBIN) $(DEPENDENCIAS)
	@$(RM) $(FLEX_GENERATED_FILES) $(BISON_GENERATED_FILES)
	@$(RM) $(BISON_HEADERS) $(BISON_HEADERS_ORIG) $(BISON_OUTPUT) $(BISON_OUTPUT_ORIG)
	@$(RM) $(NASM_OBJ) $(NASM_BIN) debug *.asm *.o

# Borrar ficheros generados y volver a compilar
reset:
	make clean
	make all

# Ayuda
help:
	@echo "Makefile Options:"
	@echo "    all              - compiles everything & generates the ares executable"
	@echo "    clean               - deletes all files generated during compiling"
	@echo "    runf                - compiles an ARES file and executes it"
	@echo "                             -> Usage: make runf src=<SOURCECODE_ARES>"
	@echo "                             -> Generates an executable file called 'exe'"
	@echo "    valgrind            - runs valgrind over the compiler through a source file"
	@echo "                             -> Usage: make valgrind src=<SOURCECODE_ARES>"
	@echo "    astyle              - styles code according to $(ARTISTIC_STYLE_OPTIONS) file"
	@echo "    reset               - runs the rule 'make clean' first, and then 'make all'"

runf:
	@echo "-------------------------------"
	./ares -f $(src) -o exe -d
	@echo "-------------------------------"
	./exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./ares $(src) exe.asm

style:
	astyle --options=$(ARTISTIC_STYLE_OPTIONS) $(DINC)/*.h $(DSRC)/*.c

CFLAGS += -MMD
-include $(DEPENDENCIAS)
