/*
 * AUTHORSHIP
 * AUTHOR: KARL FLORES 
 * COMP90077 Assignment 1 
 *
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#include "data.h"

#define LEFT 1
#define RIGHT 0
#define TRUE 1 
#define FALSE 0
#define MAX_PRIORITY 100000000

struct treap{
	// the root of the tree
	struct node *root;
	
	// treap interface functions  	

	/* insert function 
	 * param treap: address of treap to insert into 
	 * param data_element: address of data element to insert into the treap
	 */
	void (*insert)(struct treap *,struct data_element*);

	/* delete function 
	 * param treap: address of treap to delete from  
	 * param int: search key of element to delete 
	 */
	void (*delete)(struct treap *,int);

	/* search function 
	 * param treap: address of treap to search 
	 * param int: search key of element to search 
	 */
	int (*search)(struct treap *,int);	

};


// a node structure -- the tree itself
struct node {
	struct node *left;
	struct node *right;
	struct data_element *data;	
	int priority;

};

// functions to create and delete a treap from memory 

/*Create a treap 
 * return : pointer to a treap -- needs to be deleted after use 
 */

struct treap *create_treap();

/* Delete a treap that has been allocated 
 * param treap : address of treap to delete
 */
void delete_treap(struct treap *treap);
