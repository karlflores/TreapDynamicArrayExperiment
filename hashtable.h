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

#define INIT_SIZE 1019
#define SECOND_PRIME 29

struct cell{
	struct data_element *data;
	int status; 
};

struct hash_table{
	struct cell *table;
	int n_filled;
	int max_elements;
	int load_factor; 
	int table_size;
	
	void (*set)(struct hash_table *,struct data_element *);
	int (*get)(struct hash_table *,int);
	int (*delete)(struct hash_table *,int);
};

struct hash_table *create_hash_table(int load_capacity);
void delete_hash_table(struct hash_table *ht);
int primary_hash(struct hash_table *ht, int id);
int secondary_hash(int id); 
void ht_set(struct hash_table *ht, struct data_element *data);
int ht_del(struct hash_table *ht, int id);
int ht_get(struct hash_table *ht, int id); 
int next_prime(int n);
int is_prime(int n);

