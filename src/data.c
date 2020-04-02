/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */


#include "data.h"

struct data_element *create_data_element(int id, int key){
	struct data_element *data = (struct data_element*)malloc(sizeof(struct data_element));
	assert(data);
	data->id = id;
	data->key = key;
	return data;
}
