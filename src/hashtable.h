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
	void (*set)(struct hash_table *,struct data_element *);
	int (*get)(struct hash_table *,int);
	int (*delete)(struct hash_table *,int);
};


// create and delete a hash table 
struct hash_table *create_hash_table(int load_capacity);
void delete_hash_table(struct hash_table *ht);

// hash functions 
int primary_hash(struct hash_table *ht, int id);
int secondary_hash(int id); 

// hash function operations 
void ht_set(struct hash_table *ht, struct data_element *data);
int ht_del(struct hash_table *ht, int id);
int ht_get(struct hash_table *ht, int id); 


// util prime functions 
int next_prime(int n);
int is_prime(int n);

