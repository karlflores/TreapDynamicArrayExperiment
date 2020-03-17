all: 
	gcc -Wall -c main.c
	gcc -Wall -c dynamic_arr.c
	gcc -Wall -c data.c
	gcc -Wall -o main dynamic_arr.o main.o data.o
clean:
	rm -rf *.o main 
