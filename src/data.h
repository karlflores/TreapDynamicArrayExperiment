/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

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

/*
 * Create a data element, needs to be freed after use 
 * param id: id of the element 
 * param key: key of the element
 * return: pointer to the element (id,key)
 */
struct data_element *create_data_element(int id, int key);
#endif
