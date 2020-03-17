#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <data.h> 

#define NOT_FOUND -1

struct dynamic_array{
	struct data_element *array;
	int size;
	int max_size;
};

struct dynamic_array *create_dynamic_array();

struct dynamic_array *create_dynamic_array(){
	// start off with one element
	struct dynamic_array *array = (struct dynamic_array*)malloc(sizeof(struct dynamic_array));
	assert(dynamic_array);

	// allocate the initial array; 
	array->array = (int *)malloc(sizeof(int));
	assert(array->array);

	// set the size and max_size;
	array->size = 0;
	array->max_size = 1;
	return array;
}

// insert an element into the dynamic array;
void insert(struct dynamic_array *array, struct data_element *data_element){
	push_back(array, data_element);
}

// push back operation 
void push_back(struct dynamic_array *array, struct data_element *data_element){

	if(array->size == array->max_size){
		// update max size 
		array->max_size*=2;
		struct data_element *new_array = (struct data_element*)malloc(
						sizeof(data_element)*array->max_size);

		// copy all elements into new array; 
		for(int i = 0 ; i < array->size ; i++){
			new_array[i] = array->array[i];
		}

		// delete old array and replace with new
		free(array->array);
		array->array = new_array;
	}

	//insert the element at the end of the array 
	array->array[size-1] = data_element;
	array->size++;
}

int search_idx(struct dynamic_array *array, int key){
	if(!array) return NOT_FOUND;
	
	//linear search the array 
	for(int i = 0 ; i < array->size ; i++)
		if(array->array[i]->key == key) return i;

	return NOT_FOUND;
}

int search(struct dynamic_array *array, int key){
	int idx = search_idx(array, key);
	return search_idx != NOT_FOUND ? array->array[idx] : NULL;
}

void delete(struct dynamic_array *array, int key){
	// search for the poistion 
	int idx = search_idx(array, key);
	if(idx == NOT_FOUND) return;
	
	// swap the element with the back element;
	swap(&array->array[idx], &array->array[array->size-1]);

	// free the element 
	free(array->array[array->size-1]);

	// update params
	array->size--;

	// test if we need to resize array 
	if(array->size < array->max_size / 4){
		// make a smaller array and copy elements 
		// update max size 
		array->max_size/=2;
		struct data_element *new_array = (struct data_element*)malloc(
						sizeof(data_element)*array->max_size);

		// copy all elements into new array; 
		for(int i = 0 ; i < array->size ; i++){
			new_array[i] = array->array[i];
		}

		// delete old array and replace with new
		free(array->array);
		array->array = new_array;
	}
}

void swap(struct data_element **a, struct data_element **b){
	struct data_element **temp;
	temp = a;
	*a = *b;
	*b = *temp;
}
