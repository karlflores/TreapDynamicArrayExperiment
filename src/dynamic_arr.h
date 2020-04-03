/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES
 * COMP90077 Assignment 1
 *
 */

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
	/*  insert function 
	 *  param dyanmic_array: dynamic array to insert into
	 *  param data_element : element to insert
	 */
	void (*insert)(struct dynamic_array*, struct data_element*);

	/* delete an element with the corresponding search key 
	 * param dynamic_array : array to delete element from
	 * param int : search key of the element to delete
	 */
	void (*delete)(struct dynamic_array*, int);

	/* search for an element with the corresponding search key 
	 * param dynamic array : array to search from 
	 * param int : search key to search for 
	 */
	struct data_element* (*search)(struct dynamic_array*, int);

};

// constructor 
/* Create a dynamic array 
 * return: pointer to an empty dynamic array 
 * needs to be freed after use 
 */
struct dynamic_array *create_dynamic_array();

// delete the dynamic array 
/* Delete a dynamic array 
 * param array: pointer to a dynamic array 
 */
void delete_dynamic_array(struct dynamic_array *array);
