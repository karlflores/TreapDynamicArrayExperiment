#include "hashtable.h"

#define LOAD_FACTOR 75
#define MAX_KEY 10000000 

struct generator{
	int id_next;	
	struct hash_table *generated;
	int *data_generated;
	struct generator* (*create)(void);
	struct data_element (*gen_insertion)(struct generator *);
	int (*gen_search)(struct generator *);
	int (*gen_deletion)(struct generator*);
};

struct generator *create_generator();
struct data_element *gen_element(struct generator *g);
int gen_deletion(struct generator *g);
struct data_element gen_insertion(struct generator *g);
int gen_search(struct generator *g);
void delete_generator(struct generator *g);
