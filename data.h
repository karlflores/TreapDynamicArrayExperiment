#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

// data element structure 
struct data_element{
	int id;
	int key;
};

struct data_element *create_data_element(int id, int key);
#endif
