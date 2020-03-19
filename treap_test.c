#include "treap.h"
#include <time.h>

int main(int argc, char **argv){
	srand(time(0));
	
	struct treap *treap = create_treap();	
	// keys to insert 
	int max = 1000000;
	int keys[max];
	
	for(int i = 0 ; i < max ; i++){
		printf(">>> INSERTED... %d\r",i);
		// create data 
		struct data_element *data = create_data_element(i,rand()%max+1); 
		keys[i] = data->key;
		treap->insert(treap, data);
		if(!treap) printf("ERROR\n");

	}

	int found = 0;
	for(int i = 0 ; i < max ; i++){
		if(treap->search(treap, keys[i])) found++;
		if(treap->search(treap, -1)) printf(">> ERROR: found a deleted key\n");

	}
	printf("FOUND %d ELEMENTS | NUM INSERTED = %d\n", found, max);

	int del = 0;
	for(int i = 0 ; i < max ; i++){
		treap->delete(treap, keys[i]);
	   	if(treap) del++;
	}
	printf("DELETED %d ELEMENTS | NUM INSERTED = %d\n", found, max);
	inorder(treap->root);

	return 0;
}
