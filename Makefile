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
	$(BISON) $(BISONFLAGS) $(DSRC)/alfa.y
	mv y.tab.c $(DSRC)/y.tab.c

$(IDIR)/y.tab.h: $(DSRC)/alfa.y
	$(BISON) $(BISONFLAGS) $(DSRC)/alfa.y
	mv y.tab.h $(IDIR)/y.tab.h

# Lex
$(DSRC)/lex.yy.c: $(DSRC)/alfa.l $(DINC)/y.tab.h
	$(FLEX) $(DSRC)/alfa.l

clean:
	rm -rvf $(BIN) $(DOBJ)/*.o lex.yy.c $(IDIR)/*.tab.h $(DSRC)/*.tab.c *.output
