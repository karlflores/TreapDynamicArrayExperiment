//#include "dynamic_arr.h"
#include "hashtable.h"

int main(int argc, char **argv){
	/*	
	struct dynamic_array *dynamic_array = create_dynamic_array();
	printf("STARTING ARRAY SIZE: %d, MAX SIZE: %d\n",dynamic_array->size, dynamic_array->max_size);
	struct data_element *data;
	// insert 10 things into the array 
	for(int i = 0 ; i < 10 ; i++){
		// create data element
		data = create_data_element(i,10-i);
		printf("GOT HERE\n");
		insert(dynamic_array,data);
		printf("Inserted: ID - %d | KEY - %d\n",data->id,data->key);
	}
	
	// SEARCHING NOW 
	printf("\n\nSEARCHING\n");
	// search for the 10 items 
	for(int i = 0 ; i <= 10 ; i++){
		// create data element
		struct data_element *found = search(dynamic_array, i);
		
		if(found) printf("FOUND KEY - %d\n",found->key);
		else printf("NOT FOUND KEY - %d\n",i);
	}

	// delete item 
	for(int i = 0 ; i < 10 ; i++){
		// create data element
		delete(dynamic_array,i);
		printf("DELETED ITEM WITH KEY - %d\n",i);
	}
	
	*/
	int max = 2000000;
	int keys[max];
	// test the hash table 
	struct hash_table *ht = create_hash_table(75);
	for(int i = 0 ; i < max ; i++){
		int r = (int)rand() % max;
		keys[i] = r;
		set(ht,create_data_element(r,i)); 
	}
	printf("INSERTED %d ELEMENTS\n",max);
	int found = 0;
	for(int i = 0 ; i < max ; i++){
		int key = get(ht, keys[i]);
		if(key > -1) found++;
	}
	printf("FOUND %d KEYS\n",found);
	int deleted = 0;
	for(int i = 0 ; i < max ; i++){
		if(delete(ht, keys[i])) deleted++;
	}
	printf("DELETED %d KEYS\n",deleted);
	found = 0;
	for(int i = 0 ; i < max ; i++){
		int key = get(ht, keys[i]);
		if(key > -1) found++;
	}
	printf("FOUND %d KEYS\n",found);



	return 0;
}
