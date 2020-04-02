#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"

#define NOT_FOUND -1

struct dynamic_array{
	struct data_element **array;
	int size;
	int max_size;

	// interfaces for the dynamic array operations 
	
	// insert -- pass in the element you want to insert and the dynamic array you
	// want to insert into 
	void (*insert)(struct dynamic_array*, struct data_element*);

	// delete an element with the corresponding search key 
	void (*delete)(struct dynamic_array*, int);

	// search for an element with the corresponding search key 
	struct data_element* (*search)(struct dynamic_array*, int);

};

// constructor 
struct dynamic_array *create_dynamic_array();

// delete the dynamic array 
void delete_dynamic_array(struct dynamic_array *array);

// implementations of each of the operations on the dynamic array 
void da_insert(struct dynamic_array *array, struct data_element *data_element);
void push_back(struct dynamic_array *array, struct data_element *data_element);
int search_idx(struct dynamic_array *array, int key);
struct data_element *da_search(struct dynamic_array *array, int key);
void da_delete(struct dynamic_array *array, int key);
void swap(struct data_element **a, struct data_element **b);
