/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

#include "hashtable.h"

#define LOAD_FACTOR 75
#define MAX_KEY 10000000 

enum operation_type{
	INSERT,
	DELETE,
	SEARCH
};

struct operation{
	// if the operation type is 
	// INSERT: use key 
	// DELETE: use key
	// SEARCH: use data
	enum operation_type operation;
	int key;
	struct data_element data;
};

struct generator{
	int id_next;	
	struct hash_table *generated;
	int *data_generated;

	// generator interfaces -- all return a struct containing the operaiton information 
	struct operation (*gen_insertion)(struct generator *);
	struct operation (*gen_search)(struct generator *);
	struct operation (*gen_deletion)(struct generator*);
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
struct operation  gen_deletion(struct generator *g);
struct operation gen_insertion(struct generator *g);
struct operation gen_search(struct generator *g);
