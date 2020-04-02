/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

#include "hashtable.h"

#define LOAD_FACTOR 75
#define MAX_KEY 10000000 

struct generator{
	int id_next;	
	struct hash_table *generated;
	int *data_generated;

	// generator interfaces 
	struct data_element (*gen_insertion)(struct generator *);
	int (*gen_search)(struct generator *);
	int (*gen_deletion)(struct generator*);
};

// create the generator to use 
// return: pointer to the created generator, need to free after use 
struct generator *create_generator();

// delete the generator after use
// param: g - pointer to the generator you want to delete 
void delete_generator(struct generator *g);

// implementations of each operation, need to pass in the generator you want to use 
// into each of these functions 
struct data_element *gen_element(struct generator *g);
int gen_deletion(struct generator *g);
struct data_element gen_insertion(struct generator *g);
int gen_search(struct generator *g);
