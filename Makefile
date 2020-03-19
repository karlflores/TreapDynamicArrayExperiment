all: 
	gcc -Wall -c ds_expr.c
	gcc -Wall -c dynamic_arr.c
	gcc -Wall -c hashtable.c
	gcc -Wall -c treap.c
	gcc -Wall -c generator.c
	gcc -Wall -c data.c
	gcc -Wall -o ds_expr dynamic_arr.o ds_expr.o data.o treap.o generator.o hashtable.o

da: 
	gcc -Wall -c main.c
	gcc -Wall -c dynamic_arr.c
	gcc -Wall -c data.c
	gcc -Wall -o main dynamic_arr.o main.o data.o
ht: 
	gcc -Wall -c main.c
	gcc -Wall -c dynamic_arr.c
	gcc -Wall -c data.c
	gcc -Wall -c hashtable.c
	gcc -Wall -o main hashtable.o main.o data.o
gen: 
	gcc -Wall -c gentest.c
	gcc -Wall -c generator.c
	gcc -Wall -c data.c
	gcc -Wall -c hashtable.c
	gcc -Wall -o gentest hashtable.o generator.o gentest.o data.o
treap:
	gcc -Wall -c treap_test.c
	gcc -Wall -c treap.c
	gcc -Wall -c data.c
	gcc -Wall -o main treap.o treap_test.o data.o

clean:
	rm -rf *.o main 
