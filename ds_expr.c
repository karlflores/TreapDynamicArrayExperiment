#include "dynamic_arr.h"
#include "treap.h"
#include "generator.h"
#include <sys/time.h>

#define MAX_DRAW 1000000
#define ARR_DEFAULT 1000000
enum DS{
	DYNAMIC_ARRAY,
	TREAP	
};

struct query{
	char type;

	// if insert store pointer to the data_element;
	struct data_element data;
	// store the search key if its a del or search
	int key;
};

void experiment_1(struct query *Q, int size, struct generator *g);
void execute(void* ds, enum DS, struct query *Q, int size);
void experiment_2(struct query *Q, int size, struct generator *g, int pcent_10);
void experiment_3(struct query *Q, int size, struct generator *g, int pcent_10);
void experiment_4(struct query *Q, int size, struct generator *g);
int get_time();

int main(int argc, char **argv){
	
	// set random generator seed
	srand(time(0));
	
	// call program with ./main [size] [test_number]
	if(argc != 3){
		fprintf(stderr,"ERROR: ./ds_expr [expr_param] [test_number]");
		return -1;
	}
	int experiment = atoi(argv[2]);
	int expr_param = atoi(argv[1]);

	struct treap *treap = create_treap();
	struct dynamic_array *dyn_arr = create_dynamic_array();
	struct generator *g = create_generator();
	
	// generate the queries first to seperate the time taken to generate from the time it takes
	// to execute
	struct query *queries;
	int q_size;
	int before, after;
	switch(experiment){
		case 1:
			q_size = expr_param;
			queries = (struct query*)malloc(sizeof(struct query)*q_size);
			assert(queries);

			experiment_1(queries,expr_param,g);
			
			break;
		case 2:
			queries = (struct query*)malloc(sizeof(struct query)*ARR_DEFAULT);
			assert(queries);

			experiment_2(queries,ARR_DEFAULT,g,expr_param);
			q_size = ARR_DEFAULT;
			break;
		case 3:
			queries = (struct query*)malloc(sizeof(struct query)*ARR_DEFAULT);
			assert(queries);
			experiment_3(queries,ARR_DEFAULT,g,expr_param);
			q_size = ARR_DEFAULT;
			break;
		case 4:
			q_size = expr_param;
			queries = (struct query*)malloc(sizeof(struct query)*q_size);
			assert(queries);
			experiment_4(queries,expr_param,g);
			break;
		default:
			return -1;
	}

	// now we can perform the experiments

	struct timeval t;
	if(experiment == 1){
   		gettimeofday(&t,NULL);
		before = t.tv_usec + t.tv_sec * 1000000;
	} else before = get_time();

	execute(treap,TREAP,queries,q_size);

	if(experiment == 1){
   		gettimeofday(&t,NULL);
		after = t.tv_usec + t.tv_sec * 1000000;
	} else after = get_time();
	
	printf("%d, ",after - before);

	if(experiment == 1){
   		gettimeofday(&t,NULL);
		before = t.tv_usec + t.tv_sec * 1000000;
	} else before = get_time();

	execute(dyn_arr,DYNAMIC_ARRAY,queries,q_size);	

	if(experiment == 1){
   		gettimeofday(&t,NULL);
		after = t.tv_usec + t.tv_sec * 1000000;
	} else after = get_time();

	printf("%d",after - before);
	delete_generator(g);
	delete_treap(treap);
	delete_dynamic_array(dyn_arr);
	free(queries);
	return 0;
}

int get_time(){
	struct timeval t;
   	gettimeofday(&t,NULL);
	return t.tv_usec / 1000 + t.tv_sec * 1000;
}

void experiment_1(struct query *Q, int size, struct generator *g){
	for(int i = 0 ; i < size ; i++){
		Q[i].data = g->gen_insertion(g);
		Q[i].type = 'i';	
	}
}

void experiment_2(struct query *Q, int size, struct generator *g, int pcent_10){	
	int del_event;

	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW + 1;
		// if the event is less than the expectation 
		if(del_event < pcent_10 * MAX_DRAW / 1000){
			// delete
			Q[i].key = g->gen_deletion(g);	
			Q[i].type = 'd';
		}else{
			Q[i].data = g->gen_insertion(g);
			Q[i].type = 'i';
		}
	}
}

void experiment_3(struct query *Q, int size, struct generator *g, int pcent_10){	
	int del_event;

	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW;
		// if the event is less than the expectation 
		if(del_event < pcent_10 * MAX_DRAW / 1000){
			// delete
			Q[i].key = g->gen_search(g);	
			Q[i].type = 's';
		}else{
			Q[i].data = g->gen_insertion(g);
			Q[i].type = 'i';
		}
	}
}

void execute(void* ds, enum DS type, struct query *Q, int size){
	if(type == TREAP){
		for(int i = 0 ; i < size ; i++){
			switch(Q[i].type){
				case 'i':
					((struct treap*)ds)->insert((struct treap*)ds,&Q[i].data);
					break;
				case 'd':
					((struct treap*)ds)->delete((struct treap*)ds,Q[i].key);
					break;
				case 's':
					((struct treap*)ds)->search((struct treap*)ds,Q[i].key);
					break;
			}
		}
	}else{
		for(int i = 0 ; i < size ; i++){
			switch(Q[i].type){
				case 'i':
					((struct dynamic_array*)ds)->insert((struct dynamic_array*)ds,&Q[i].data);
					break;
				case 'd':
					((struct dynamic_array*)ds)->delete((struct dynamic_array*)ds,Q[i].key);
					break;
				case 's':
					((struct dynamic_array*)ds)->search((struct dynamic_array*)ds,Q[i].key);
					break;
			}
		}
	
	}	
}

void experiment_4(struct query *Q, int size, struct generator *g){	
	int del_event;
	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW + 1;
		// if the event is less than the expectation 
		if(del_event < 5 * MAX_DRAW / 100){
			// delete
			Q[i].key = g->gen_deletion(g);	
			Q[i].type = 'd';
		}else if(del_event < 10 * MAX_DRAW / 100){
			// search 
			Q[i].key = g->gen_search(g);	
			Q[i].type = 's';
		}else{
			Q[i].data = g->gen_insertion(g);
			Q[i].type = 'i';
		}
	}
}
