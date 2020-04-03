/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "data.h"

#define EMPTY 0
#define FILLED 1
#define DELETED -1
#define TRUE 1
#define FALSE 0

#define MAX_TABLE_SIZE 2000000
#define INIT_SIZE 1019
#define SECOND_PRIME 29

// cell stores a data element, the status determines the state of that cell
// deleted, empty or filled 
struct cell{
	struct data_element *data;
	int status; 
};

// hash table struct 
struct hash_table{
	struct cell *table;
	int n_filled;
	int max_elements;
	int load_factor; 
	int table_size;

	// interface functions 	
	
	/* set function 
	 * param hash_table : hash table to insert the element into 
	 * param data_element : element to insert
	 */
	void (*set)(struct hash_table *,struct data_element *);

	/* get function 
	 * param hash_table : hash table to search 
	 * param int : id to search for 
	 * return int : -1 if not found, search_key if element with id is found 
	 */
	int (*get)(struct hash_table *,int);

	/* delete function
	 * param hash_table : hash table to search 
	 * param int : id of element to delete 
	 * return: 0 if delete is unsuccessful, 1 if delete is successful 
	 */
	int (*delete)(struct hash_table *,int);
};


// create and delete a hash table 

/* create a hash table with a given load capacity
 * param int: load capacity (%) from 0-100
 * return : pointer to the created hash table, delete_hash_table needs to be called
 * after use 
 */
struct hash_table *create_hash_table(int load_capacity);

/* delete a hash table after its use 
 * param hash_table : address of hash table to delete 
 */
void delete_hash_table(struct hash_table *ht);

