CC = gcc
BISON = bison
FLEX = flex

BIN = alfa
CFLAGS = -g -Wall -std=c99 -pedantic
CYYFLAGS = -ansi -pedantic
BISONFLAGS = -dyv

DSRC = src/
DINC = include/
DTEST = test/
DOBJ = obj/


all: $(BIN)

$(BIN): y.tab.o lex.yy.o alfa.o
	$(CC) -o $@ $^

lex.yy.o: lex.yy.c
	$(CC) $(CYYFLAGS) -c -o $(DOBJ)lex.yy.o $(DSRC)lex.yy.c

y.tab.o: y.tab.c
	$(CC) $(CYYFLAGS) -c -o $(DOBJ)$@ $(DSRC)$<

# Compilacion de archivos .c
# %.o: %.c $(DSRC)$(DINC)%.h
# 	$(CC) ${CFLAGS} -c -o $(DOBJ)$@ $(DSRC)$<

# Bison
y.tab.c:
	bison -dyv src/alfa.y
	mv y.tab.c src/
	mv y.tab.h src/include/y.tab.h

# Lex
lex.yy.c: $(DSRC)alfa.l $(DSRC)$(DINC)y.tab.h
	$(FLEX) $(DSRC)alfa.l
	mv lex.yy.c src/

alfa.o: alfa.c
	$(CC) $(CFLAGS) -c $(DSRC)$< -o $(DOBJ)$@

generacion.o: generacion.c
	$(CC) $(CFLAGS) -c $(DSRC)$< -o $(DOBJ)$@

hash_t.o: hash_t.c
	$(CC) $(CFLAGS) -c $(DSRC)$< -o $(DOBJ)$@

sym_info.o: sym_info.c
	$(CC) $(CFLAGS) -c $(DSRC)$< -o $(DOBJ)$@

sym_t.o: sym_t.c
	$(CC) $(CFLAGS) -c $(DSRC)$^ -o $(DOBJ)$@

clean:
	rm -rvf $(BIN) $(DOBJ)*.o $(DSRC)lex.yy.c $(DSRC)$(DINC)*.tab.h $(DSRC)*.tab.c *.output
