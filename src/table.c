/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES
 * COMP90077 Assignment 1
 *
 */

#include "hashtable.h"
// hash functions 
int primary_hash(struct hash_table *ht, int id);
int secondary_hash(int id); 

// hash function operations 
void ht_set(struct hash_table *ht, struct data_element *data);
int ht_del(struct hash_table *ht, int id);
int ht_get(struct hash_table *ht, int id); 

/*
 * Implementation of a hash table based on the functions definitions in hashtable.h
 * this assumes that the items that we are inserting in to the hash table are in
 * the range [0,MAX_TABLE_SIZE], and all ids are unique.  
 *  
 */


// Constructor
// param: load_factor (0,100) - how full the table should be 
// before we try to resize 
struct hash_table *create_hash_table(int load_factor){
	// find the max elements based on the load factor; 
	struct hash_table *ht = (struct hash_table *)malloc(sizeof(struct hash_table));
	assert(ht);

	// now set the n_filled, max elements and table size 
	ht->max_elements = MAX_TABLE_SIZE;
	ht->table_size = MAX_TABLE_SIZE;
	ht->load_factor = load_factor;
	ht->n_filled = 0;

	// hash table interfaces 
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

// insert an element -- just use the id as an index into the table 
void ht_set(struct hash_table *ht, struct data_element *data){
	if(ht->n_filled > MAX_TABLE_SIZE-1) return;
	ht->table[data->id].data = data;
	ht->table[data->id].status = FILLED;
	ht->n_filled++;
}

// retrieve an element based on the index 
int ht_get(struct hash_table *ht, int id){
	if(ht->table[id].status == EMPTY || ht->table[id].status == DELETED) return -1;
	return ht->table[id].data->key;
}

// delete an element based on the index 
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

// delete the entire hash table 
void delete_hash_table(struct hash_table *ht){
	// iterate through all elements in the hash table 
	for(int i = 0 ; i < ht->table_size ; i++){
		if(ht->table[i].status == FILLED) free(ht->table[i].data);
	}
	free(ht->table);
	free(ht);
}
