#include "hashtable.h"

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

void ht_set(struct hash_table *ht, struct data_element *data){
	// see if we need to resize the hash table first 
	if(ht->n_filled >= (ht->table_size*ht->load_factor)/100){

		printf("RESIZING...\n");
		// resize needed 
		int new_size = next_prime(ht->table_size*2);
		int old_size = ht->table_size;
		printf("OLD SIZE : %d\n", old_size);
		printf("NEW SIZE : %d\n", new_size);
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
	// now we are free to rehash the incoming data
	int p_hash = primary_hash(ht, data->id);
	int s_hash = secondary_hash(data->id);
	int idx = p_hash % ht->table_size;
	int j = 1;
	while(ht->table[idx].status == FILLED){
		//finding position
		//printf("finding... %d\n", idx);
		idx = (p_hash + j*s_hash)%ht->table_size;
		j++;
	}
	ht->table[idx].data = data;
	ht->table[idx].status = FILLED;
	ht->n_filled++;
}

int ht_get(struct hash_table *ht, int id){
	int p_hash = primary_hash(ht, id);
	int s_hash = secondary_hash(id);	

	int idx = p_hash %ht->table_size;
	int i = 0; 
	while(ht->table[idx].status != EMPTY){
		if(ht->table[idx].status == FILLED){
			if(ht->table[idx].data->id == id) return ht->table[idx].data->key;
		}
		idx = (p_hash + i*s_hash)%ht->table_size;		
		i++;
	}
	return -1;
}

int ht_del(struct hash_table *ht, int id){
	int p_hash = primary_hash(ht, id);
	int s_hash = secondary_hash(id);	

	int idx = p_hash%ht->table_size;
	int i = 1; 
	int deleted = FALSE;
	while(ht->table[idx].status != EMPTY){
		if(ht->table[idx].status == FILLED){
			if(ht->table[idx].data->id == id){
				// remove this cell;
				free(ht->table[idx].data);
				ht->table[idx].status = DELETED;	
				ht->n_filled--;
				deleted = TRUE;
				//printf("REMOVED ELEMENT FROM HT (%d,%d)\n",ht->table[idx].data->id,
				//				ht->table[idx].data->key);
				break;
			}	
		}
		idx = (p_hash + i*s_hash)%ht->table_size;		
		i++;
	}
	// see if we need to resize the hash table first 
	if(ht->n_filled <= ht->table_size/4 && ht->table_size >= INIT_SIZE * 2){

		printf("RESIZING...\n");
		// resize needed 
		int new_size = next_prime(ht->table_size/2);
		int old_size = ht->table_size;
		printf("OLD SIZE : %d\n", old_size);
		printf("NEW SIZE : %d\n", new_size);
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
