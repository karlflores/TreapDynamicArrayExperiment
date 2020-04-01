#include "hashtable.h"

struct hash_table *create_hash_table(int load_factor){
	// find the max elements based on the load factor; 
	struct hash_table *ht = (struct hash_table *)malloc(sizeof(struct hash_table));
	assert(ht);

	// now set the n_filled, max elements and table size 
	ht->max_elements = MAX_TABLE_SIZE;
	ht->table_size = MAX_TABLE_SIZE;
	ht->load_factor = load_factor;
	ht->n_filled = 0;
	ht->delete = &ht_del;
	ht->set = &ht_set;
	ht->get = &ht_get;

	// allocate the table 
	ht->table = (struct cell *)malloc(sizeof(struct cell)*MAX_TABLE_SIZE);
	assert(ht->table);

	// set all values in the table
	for(int i = 0 ; i < MAX_TABLE_SIZE ; i++){
		ht->table[i].data = NULL;
		ht->table[i].status = EMPTY;
	}

	return ht;
}

void ht_set(struct hash_table *ht, struct data_element *data){
	if(ht->n_filled > MAX_TABLE_SIZE-1) return;
	//printf("HT SIZE: %d\n",ht->n_filled);
	ht->table[data->id].data = data;
	ht->table[data->id].status = FILLED;
	ht->n_filled++;
}

int ht_get(struct hash_table *ht, int id){
	if(ht->table[id].status == EMPTY || ht->table[id].status == DELETED) return -1;
	return ht->table[id].data->key;
}

int ht_del(struct hash_table *ht, int id){
	if(ht->table[id].status == FILLED){
		// remove this cell;
		free(ht->table[id].data);
		ht->table[id].data = NULL;
		ht->table[id].status = DELETED;	
		ht->n_filled--;
		return TRUE;
	}	
	return FALSE;

}

void delete_hash_table(struct hash_table *ht){
	// iterate through all elements in the hash table 
	for(int i = 0 ; i < ht->table_size ; i++){
		if(ht->table[i].status == FILLED) free(ht->table[i].data);
	}
	free(ht->table);
	free(ht);
}

int primary_hash(struct hash_table *ht, int id){
	// get the current table size and return the data id mod it
	return id % ht->table_size;
}

int secondary_hash(int id){
	return id % SECOND_PRIME + 1;
}

int is_prime(int n){
	for(int i = 2 ; i <= sqrt(n) ; i++){
		if(n % i == 0) return FALSE;
	}
	return TRUE;
}

int next_prime(int n){
	while(!is_prime(n++));
	return n-1;
}
