#include "dynamic_arr.h"

struct dynamic_array *create_dynamic_array(){
	// start off with one element
	struct dynamic_array *array = (struct dynamic_array*)malloc(sizeof(struct dynamic_array));
	assert(array);

	// allocate the initial array; 
	array->array = (struct data_element **)malloc(sizeof(struct data_element*));
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
	printf("ARRAY SIZE ON CALL : %d\n",array->size);
	printf("INSERTING\n");
	if(!array){
		printf("ERROR\n");
		return;
	}

	if(array->size >= array->max_size){
		// 
		printf("UPDATED ARRAY SIZE FROM %D TO",array->max_size);
		// update max size 
		array->max_size*=2;
		struct data_element **new_array = (struct data_element**)malloc(
						sizeof(struct data_element*)*array->max_size);

		// copy all elements into new array; 
		for(int i = 0 ; i < array->size ; i++){
			new_array[i] = array->array[i];
		}

		// delete old array and replace with new
		free(array->array);
		array->array = new_array;
		printf(" %D\n",array->max_size);
	}

	//insert the element at the end of the array 
	
	array->array[array->size++] = data_element;
	printf("ARRAY SIZE: %d\n",array->size);
}

int search_idx(struct dynamic_array *array, int key){
	if(!array) return NOT_FOUND;
	printf("ARRAY SIZE: %d\n",array->size);
		
	//linear search the array 
	for(int i = 0 ; i < array->size; i++){
		if(array->array[i]->key == key) return i;
	}

	return NOT_FOUND;
}

struct data_element *search(struct dynamic_array *array, int key){
	int idx = search_idx(array, key);
	printf("FOUND %d AT INDEX: %d\n",key,idx);
	return idx != NOT_FOUND ? array->array[idx] : NULL;
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
		printf("UPDATED ARRAY SIZE FROM %D TO",array->max_size);
		// make a smaller array and copy elements 
		// update max size 
		array->max_size/=2;
		struct data_element **new_array = (struct data_element**)malloc(
						sizeof(struct data_element*)*array->max_size);

		// copy all elements into new array; 
		for(int i = 0 ; i < array->size ; i++){
			new_array[i] = array->array[i];
		}

		// delete old array and replace with new
		free(array->array);
		array->array = new_array;
		printf(" %D\n",array->max_size);
	}
}

void swap(struct data_element **a, struct data_element **b){
	struct data_element **temp;
	temp = a;
	*a = *b;
	*b = *temp;
}
