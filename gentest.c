#include "generator.h"
#include <time.h>

#define MAX 100000
int main(int argc, char **argv){
	srand(time(0));
	
	int lengths[] = {100000,200000,500000,800000,1000000};

	struct generator *g = create_generator();

	for(int i = 0 ; i < MAX ; i++){
		gen_insertion(g);
		//printf("INSERT %-10d: (%10d,%10d)\n",g->id_next,d.id,d.key); 
	}

	for(int i = 0 ; i < MAX ; i++){
		gen_deletion(g);
		//printf("DELETE %-10d: %10d\n",i,d); 
	}
	return 0;
	
}
