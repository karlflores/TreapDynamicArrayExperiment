################################################################
#                                                              #
#                  MAKEFILE FOR TREAP EXP                      #
#                                                              #
################################################################
CC = gcc
CFLAGS = -Wall -std=c99 -g

SRC1 = treap.c table.c ds_expr.c dynamic_arr.c data.c generator.c
OBJ1 = treap.o table.o ds_expr.o dynamic_arr.o data.o generator.o

SRC2 = treap.c hashtable.c ds_expr.c dynamic_arr.c data.c generator.c
OBJ2 = treap.o hashtable.o ds_expr.o dynamic_arr.o data.o generator.o

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
