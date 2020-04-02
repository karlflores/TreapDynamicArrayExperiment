/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

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

void experiment_1(struct operation *Q, int size, struct generator *g);
void execute(void* ds, enum DS, struct operation *Q, int size);
void experiment_2(struct operation *Q, int size, struct generator *g, int pcent_10);
void experiment_3(struct operation *Q, int size, struct generator *g, int pcent_10);
void experiment_4(struct operation *Q, int size, struct generator *g);
int get_time();


/* MAIN PROGRAM 
 *
 * run the program as follows 
 * ./ds_expr [expr_param] [experiment number]
 *
 * output: runtime_treap, runtime_dynamic_arr (both in ms)
 * */
int main(int argc, char **argv){
	
	// set random generator seed
	srand(time(0));
	
	// call program with ./main [size] [expr_number]
	if(argc != 3){
		fprintf(stderr,"ERROR: ./ds_expr [expr_param] [expr_number]");
		return -1;
	}

	// IO
	int experiment = atoi(argv[2]);
	int expr_param = atoi(argv[1]);

	// error checking 
	if(experiment > 4){
		fprintf(stderr,"ERROR: experiment number needs to be 1,2,3 or 4\n");	
		return -1;

	}else if(experiment == 2 || experiment == 3){
		if(expr_param > 100 || expr_param < 1){
			fprintf(stderr,"ERROR: expr param needs to be in the range 1-100 (where expr_param = perecetage*10 i.e. 100 = 10%%\n");	
			return -1;
		}
	}else{
		if(expr_param > 1000000 || expr_param < 1){
			fprintf(stderr,"ERROR: expr param needs to be in the range 1-1000000\n");	
			return -1;
		}
	}
	
	// create the data structures and generators
	struct treap *treap = create_treap();
	struct dynamic_array *dyn_arr = create_dynamic_array();
	struct generator *g = create_generator();
	
	// generate the queries first to seperate the time taken to generate from the time it takes
	// to execute
	struct operation *queries;
	int q_size;
	int before, after;
	switch(experiment){
		case 1:
			q_size = expr_param;
			queries = (struct operation*)malloc(sizeof(struct operation)*q_size);
			assert(queries);

			experiment_1(queries,expr_param,g);
			
			break;
		case 2:
			queries = (struct operation*)malloc(sizeof(struct operation)*ARR_DEFAULT);
			assert(queries);
			experiment_2(queries,ARR_DEFAULT,g,expr_param);
			q_size = ARR_DEFAULT;
			break;
		case 3:
			queries = (struct operation*)malloc(sizeof(struct operation)*ARR_DEFAULT);
			assert(queries);
			experiment_3(queries,ARR_DEFAULT,g,expr_param);
			q_size = ARR_DEFAULT;
			break;
		case 4:
			q_size = expr_param;
			queries = (struct operation*)malloc(sizeof(struct operation)*q_size);
			assert(queries);
			experiment_4(queries,expr_param,g);
			break;
		default:
			return -1;
	}

	// now we can perform the experiments
	before = get_time();
	execute(treap,TREAP,queries,q_size);
	after = get_time();
	
	printf("%d, ",after - before);

	before = get_time();
	execute(dyn_arr,DYNAMIC_ARRAY,queries,q_size);	
	after = get_time();

	printf("%d",after - before);

	// delete all tings 
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


/*EXPERIMENT FUNCTION IMPLEMENTED AS PER IMPLEMENTATION SPEC */
/* All experiments are called with the sequenceo of operations Q,
 * the size of the sequence s and the generator used to generate the 
 * elements g
 */
void experiment_1(struct operation *Q, int size, struct generator *g){	
	for(int i = 0 ; i < size ; i++){
		Q[i] = g->gen_insertion(g);
	}
}

void experiment_2(struct operation *Q, int size, struct generator *g, int pcent_10){	
	int del_event;
	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW + 1;
		// if the event is less than the expectation 
		if(del_event < pcent_10 * MAX_DRAW / 1000){
			// delete
			Q[i] = g->gen_deletion(g);	
		}else{
			Q[i] = g->gen_insertion(g);
		}
	}
}

void experiment_3(struct operation *Q, int size, struct generator *g, int pcent_10){	
	int del_event;

	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW;
		// if the event is less than the expectation 
		if(del_event < pcent_10 * MAX_DRAW / 1000){
			// delete
			Q[i] = g->gen_search(g);	
		}else{
			Q[i] = g->gen_insertion(g);
		}
	}
}

void experiment_4(struct operation *Q, int size, struct generator *g){	
	int del_event;
	for(int i = 0 ; i < size ; i++){
		del_event = rand()%MAX_DRAW + 1;
		// if the event is less than the expectation 
		if(del_event < 5 * MAX_DRAW / 100){
			// delete
			Q[i] = g->gen_deletion(g);	
		}else if(del_event < 10 * MAX_DRAW / 100){
			// search 
			Q[i] = g->gen_search(g);	
		}else{
			Q[i] = g->gen_insertion(g);
		}
	}
}

// Execute the sequence of operations on the supplied data structure
// pass in a pointer to the ds as well as an enum value represening the type of 
// DS you are passing in 
// pass in the sequence of operations as well as the input size 
void execute(void* ds, enum DS type, struct operation *Q, int size){
	if(type == TREAP){
		for(int i = 0 ; i < size ; i++){
			switch(Q[i].operation){
				case INSERT:
					((struct treap*)ds)->insert((struct treap*)ds,&Q[i].data);
					break;
				case DELETE:
					((struct treap*)ds)->delete((struct treap*)ds,Q[i].key);
					break;
				case SEARCH:
					((struct treap*)ds)->search((struct treap*)ds,Q[i].key);
					break;
			}
		}
	}else{
		for(int i = 0 ; i < size ; i++){
			switch(Q[i].operation){
				case INSERT:
					((struct dynamic_array*)ds)->insert((struct dynamic_array*)ds,&Q[i].data);
					break;
				case DELETE:
					((struct dynamic_array*)ds)->delete((struct dynamic_array*)ds,Q[i].key);
					break;
				case SEARCH:
					((struct dynamic_array*)ds)->search((struct dynamic_array*)ds,Q[i].key);
					break;
			}
		}
	
	}	
}
