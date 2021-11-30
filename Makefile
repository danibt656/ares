CC = gcc
BISON = bison
FLEX = flex

BIN = alfa
CFLAGS = -Wall -std=c99 -pedantic
CYYFLAGS = -ansi -pedantic
BISONFLAGS = -dyv

DSRC = src
DINC = include
DTEST = test
DOBJ = obj


all: ${BIN}

${BIN}:%: $(DOBJ)/y.tab.o $(DOBJ)/lex.yy.o $(DOBJ)/%.o
	$(CC) -o $@ $^

$(DOBJ)/lex.yy.o: $(DSRC)/lex.yy.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

$(DOBJ)/y.tab.o: $(DSRC)/y.tab.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

# Compilacion de archivos .c
$(DOBJ)/%.o: $(DSRC)/%.c
	$(CC) ${CFLAGS} -c -o $@ $<

# Bison
$(DSRC)/y.tab.c: $(DSRC)/alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

$(IDIR)/y.tab.h: $(DSRC)/alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

# Lex
$(DSRC)/lex.yy.c: $(DSRC)/alfa.l $(DINC)/y.tab.h
	$(FLEX) alfa.l

clean:
	rm -rvf $(BIN) *.o lex.yy.c *.tab.h *.tab.c y.output *.output
