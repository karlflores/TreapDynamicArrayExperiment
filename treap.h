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
	struct node *root;
	
	// treap interface functions  	
	void (*insert)(struct treap *,struct data_element*);
	void (*delete)(struct treap *,int);
	int (*search)(struct treap *,int);	

};


// a node structure -- the tree itself
struct node {
	struct node *left;
	struct node *right;
	struct data_element *data;	
	int priority;

};

struct node *rotate_left(struct node *root);
struct node *rotate_right(struct node *root);

// node functions
struct node *insert_node(struct node *root, struct data_element *data);
struct node *delete_node(struct node *root, int key);
struct node *create_node(struct data_element *data);
int search_node(struct node *root, int key);
void delete_treap_nodes(struct node *root);

// functions to create and delete a treap from memory 
struct treap *create_treap();
void delete_treap(struct treap *treap);

// wrapper interfaces for the treap 
void treap_delete(struct treap *treap, int key);
int treap_search(struct treap *treap, int key);
void treap_insert(struct treap *treap, struct data_element *data);

/* UTILS */
void inorder(struct node *root);
