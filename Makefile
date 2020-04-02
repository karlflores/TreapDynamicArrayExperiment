################################################################
#                                                              #
#                  MAKEFILE FOR TREAP EXP                      #
#                                                              #
################################################################
CC = gcc
CFLAGS = -Wall -std=c99 -g

SRC1 = src/treap.c src/table.c src/ds_expr.c src/dynamic_arr.c src/data.c src/generator.c
OBJ1 = src/treap.o src/table.o src/ds_expr.o src/dynamic_arr.o src/data.o src/generator.o

SRC2 = src/treap.c src/hashtable.c src/ds_expr.c src/dynamic_arr.c src/data.c src/generator.c
OBJ2 = src/treap.o src/hashtable.o src/ds_expr.o src/dynamic_arr.o src/data.o src/generator.o

EXE1 = ds_expr
EXE2 = ds_expr_ht

all: $(EXE1)
ht: $(EXE2)

$(EXE1): $(OBJ1) Makefile
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ1) -g 

$(EXE2): $(OBJ2) Makefile
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2) -g 

clean:
	rm -f $(OBJ1) $(EXE1) $(OBJ2) $(EXE2)
