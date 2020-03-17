#include "dynamic_arr.h"

int main(int argc, char **argv){
	
	struct dynamic_array *dynamic_array = create_dynamic_array();
	// insert 10 things into the array 
	for(int i = 0 ; i < 10 ; i++){
		// create data element
		struct data_element *data = create_data_element(i,10-i);
		printf("GOT HERE\n");
		insert(dynamic_array,data);
		printf("Inserted: ID - %d | KEY - %d\n",data->id,data->key);
	}

	// search for the 10 items 
	for(int i = 0 ; i < 10 ; i++){
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
	
	return 0;
}
