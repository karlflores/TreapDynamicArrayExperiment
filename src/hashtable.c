/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

#include "hashtable.h"

/* 
 * THIS IS AN IMPLEMENTATION OF A HASH TABLE USING DOUBLE HASHING. This can be interchanged with
 * table.c, but this is more generalised as it does not assume the same assumptions. 
 * Inserted elements can have the same id and the size of the hash table is dyanmic, once we 
 * reach the load factor, the hash table resizes and rehashes all element in the table 
 *
 * This implementation of a hashtable utilises double hashing and simple prime sized arrays and
 * hash functions to find the index of a required element 
 */

// create the hash table 
struct hash_table *create_hash_table(int load_factor){
	// find the max elements based on the load factor; 
	int max_elements = (INIT_SIZE*load_factor)/100;
	struct hash_table *ht = (struct hash_table *)malloc(sizeof(struct hash_table));
	assert(ht);

	// now set the n_filled, max elements and table size 
	ht->max_elements = max_elements;
	ht->table_size = INIT_SIZE;
	ht->load_factor = load_factor;
	ht->n_filled = 0;

	// set the hash table interfact functions 		
	ht->delete = &ht_del;
	ht->set = &ht_set;
	ht->get = &ht_get;

	// allocate the table 
	ht->table = (struct cell *)malloc(sizeof(struct cell)*INIT_SIZE);
	assert(ht->table);

	// set all values in the table
	for(int i = 0 ; i < INIT_SIZE ; i++){
		ht->table[i].data = NULL;
		ht->table[i].status = EMPTY;
	}

	return ht;
}


// function to set an element in the hash table 
void ht_set(struct hash_table *ht, struct data_element *data){
	// see if we need to resize the hash table first 
	if(ht->n_filled >= (ht->table_size*ht->load_factor)/100){

		// resize needed 
		// find the next prime number to double our current table size 
		int new_size = next_prime(ht->table_size*2);
		int old_size = ht->table_size;
		ht->table_size = new_size;

		// make a new table; 
		struct cell *new_table = (struct cell *)malloc(sizeof(struct cell)*new_size);
		assert(new_table);
		
		// keep track of the old table 
		struct cell *old_table = ht->table;
		
		// set all values in the table
		for(int i = 0 ; i < new_size ; i++){
			new_table[i].data = NULL;
			new_table[i].status = EMPTY;
		}
		
		// rehash all the elements in the table 
		for(int i = 0 ; i < old_size ; i++){
			// need to insert each of these into the new table;
			if(old_table[i].status == FILLED){
				// rehash element
				int p_hash = primary_hash(ht, old_table[i].data->id);
				int s_hash = secondary_hash(old_table[i].data->id);
				int idx = p_hash%new_size;
				int j = 1;


				// utilise double hashing to find the next available free cell in the table  
				while(new_table[idx].status != EMPTY){
					idx = (p_hash + j*s_hash)%new_size;
					j++;
				}
				new_table[idx] = old_table[i];
			}
		}

		// set the new table in the struct
		free(old_table);
		ht->table = new_table;
		
	}

	// now we are free to hash the incoming data
	int p_hash = primary_hash(ht, data->id);
	int s_hash = secondary_hash(data->id);
	int idx = p_hash % ht->table_size;
	int j = 1;
	while(ht->table[idx].status == FILLED){
		//finding position
		idx = (p_hash + j*s_hash)%ht->table_size;
		j++;
	}
	ht->table[idx].data = data;
	ht->table[idx].status = FILLED;
	ht->n_filled++;
}

// function to get an element in the hash table 
// it returns the search key if successful, or -1 if the element does not exist 
int ht_get(struct hash_table *ht, int id){
	int p_hash = primary_hash(ht, id);
	int s_hash = secondary_hash(id);	
	
	// try using the first hash function to find the element 
	int idx = p_hash %ht->table_size;
	int i = 0; 

	// if not jump by the second hash function until we find it
	while(ht->table[idx].status != EMPTY){
		if(ht->table[idx].status == FILLED){
			if(ht->table[idx].data->id == id) return ht->table[idx].data->key;
		}
		idx = (p_hash + i*s_hash)%ht->table_size;		
		i++;
	}

	// return not found if unsuccessful 
	return -1;
}

// delete an element from the hash table with a specified ID 
// return true, if the element has been deleted 
// false if the element has not been deleted 
int ht_del(struct hash_table *ht, int id){
	
	// find the element in the table 
	int p_hash = primary_hash(ht, id);
	int s_hash = secondary_hash(id);	
	
	// try first hash	
	int idx = p_hash%ht->table_size;
	int i = 1; 
	int deleted = FALSE;

	// use second hash to find the element 
	while(ht->table[idx].status != EMPTY){
		if(ht->table[idx].status == FILLED){
			if(ht->table[idx].data->id == id){
				// remove this cell;
				free(ht->table[idx].data);
				ht->table[idx].data = NULL;
				ht->table[idx].status = DELETED;	
				ht->n_filled--;
				deleted = TRUE;
				break;
			}	
		}
		// recalculate the index for next interation 
		idx = (p_hash + i*s_hash)%ht->table_size;		
		i++;
	}
	// now that we have deleted the element (or not)
	// see if we need to resize the hash table 
	if(ht->n_filled <= ht->table_size/4 && ht->table_size >= INIT_SIZE * 2){

		// resize needed 
		int new_size = next_prime(ht->table_size/2);
		int old_size = ht->table_size;
		ht->table_size = new_size;

		// make a new table; 
		struct cell *new_table = (struct cell *)malloc(sizeof(struct cell)*new_size);
		assert(new_table);

		struct cell *old_table = ht->table;
		
		// set all values in the table
		for(int i = 0 ; i < new_size ; i++){
			new_table[i].data = NULL;
			new_table[i].status = EMPTY;
		}
		
		// rehash all the elements in the table 
		for(int i = 0 ; i < old_size ; i++){
			// need to insert each of these into the new table;
			if(old_table[i].status == FILLED){
				// rehash element
				int p_hash = primary_hash(ht, old_table[i].data->id);
				int s_hash = secondary_hash(old_table[i].data->id);
				int idx = p_hash%new_size;
				int j = 1;
				while(new_table[idx].status != EMPTY){
					idx = (p_hash + j*s_hash)%new_size;
					j++;
				}
				new_table[idx] = old_table[i];
			}
		}

		// set the new table in the struct
		free(old_table);
		ht->table = new_table;
		
	}
	return deleted;

}

// delete the hash table 
void delete_hash_table(struct hash_table *ht){
	// iterate through all elements in the hash table 
	for(int i = 0 ; i < ht->table_size ; i++){
		if(ht->table[i].status == FILLED) free(ht->table[i].data);
	}
	free(ht->table);
	free(ht);
}


/* HASH FUNCTIONS */

// primary hash function based on the size of the hash table 
int primary_hash(struct hash_table *ht, int id){
	// get the current table size and return the data id mod it
	return id % ht->table_size;
}
// static hash function 
int secondary_hash(int id){
	return id % SECOND_PRIME + 1;
}

/* PRIME FUNCTIONS USED TO RESIZE THE HASH TABLE */
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
