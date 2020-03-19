#include "generator.h"

struct generator *create_generator(void){
	struct generator *gen = (struct	generator *)malloc(sizeof(struct generator));
	assert(gen);

	// create the hashtable 
	struct hash_table *ht = create_hash_table(LOAD_FACTOR);
	assert(ht);

	gen->id_next = 1;
	gen->generated = ht;
	gen->create = &create_generator;
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

struct data_element gen_insertion(struct generator *g){
	return *gen_element(g);
}

int gen_deletion(struct generator *g){
	// if our id_next is still at 1 then we have not inserted anything , thus generate a random key 
	if(g->id_next == 1) return rand()%MAX_KEY + 1;

	// generate a random id from 1 to id next -1
	int id = rand()%(g->id_next-1) + 1;

	// test if the id has already been deleted 
	int key_found = g->generated->get(g->generated, id);
	if(key_found <= -1){
		// have already generated this, therefore delete a random key
		int key = rand()%MAX_KEY + 1;
		return key;
	}
	g->generated->delete(g->generated,id);
	return key_found;
}

int gen_search(struct generator *g){
	return rand()%MAX_KEY + 1;
}

void delete_generator(struct generator *g){
	if(!g) return;
	delete_hash_table(g->generated);
	free(g);	
}
