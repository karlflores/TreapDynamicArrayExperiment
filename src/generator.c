/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES
 * COMP90077 Assignment 1
 *
 */

#include "generator.h"

struct generator *create_generator(void){
	struct generator *gen = (struct	generator *)malloc(sizeof(struct generator));
	assert(gen);

	// create the hashtable 
	struct hash_table *ht = create_hash_table(LOAD_FACTOR);
	assert(ht);
	gen->id_next = 1;
	gen->generated = ht;
	
	// assign the functions pointers 
	gen->gen_deletion = &gen_deletion;
	gen->gen_insertion = &gen_insertion;
	gen->gen_search = &gen_search;
	return gen;
}

struct data_element *gen_element(struct generator *g){
	int id = g->id_next++;
	//generate the random key 
	int key = rand()%MAX_KEY + 1;

	// add this to the generated list 
	struct data_element *data = create_data_element(id,key);
	g->generated->set(g->generated, data);
	return data;
}

/*
 * OPERATION FUNCTION IMPLEMENTATIONS 
 */
struct operation gen_insertion(struct generator *g){
	struct operation op;
	op.data = *gen_element(g);
	op.operation = INSERT;
	return op;
}

struct operation gen_deletion(struct generator *g){
	struct operation op; 
	op.operation = DELETE;
	// if our id_next is still at 1 then we have not inserted anything , thus generate a random key 
	if(g->id_next == 1){
		op.key = rand()%MAX_KEY + 1;
		return op;
	}

	// generate a random id from 1 to id next -1
	int id = rand()%(g->id_next-1) + 1;

	// test if the id has already been deleted 
	int key_found = g->generated->get(g->generated, id);
	if(key_found <= -1){
		// have already generated this, therefore delete a random key
		op.key = rand()%MAX_KEY + 1;
		return op;
	}
	g->generated->delete(g->generated,id);
	
	// construct the operation 
	op.key = key_found;
	return op;
}

struct operation gen_search(struct generator *g){
	struct operation op;
	op.operation = SEARCH;
	op.key = rand()%MAX_KEY + 1;
	return op;
}

void delete_generator(struct generator *g){
	if(!g) return;
	delete_hash_table(g->generated);
	free(g);	
}
