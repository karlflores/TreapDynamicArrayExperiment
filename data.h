#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

struct data_element;

struct data_element{
	int id;
	int key;
};

struct data_element *create_data_element(int id, int key);
