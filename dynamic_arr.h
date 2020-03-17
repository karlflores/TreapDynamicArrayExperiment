#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"

#define NOT_FOUND -1

struct dynamic_array;

struct dynamic_array{
	struct data_element **array;
	int size;
	int max_size;
};

struct dynamic_array *create_dynamic_array();
void insert(struct dynamic_array *array, struct data_element *data_element);
void push_back(struct dynamic_array *array, struct data_element *data_element);
int search_idx(struct dynamic_array *array, int key);
struct data_element *search(struct dynamic_array *array, int key);
void delete(struct dynamic_array *array, int key);
void swap(struct data_element **a, struct data_element **b);
