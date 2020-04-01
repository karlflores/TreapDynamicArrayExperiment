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
	
	void (*insert)(struct treap *,struct data_element*);
	void (*delete)(struct treap *,int);
	int (*search)(struct treap *,int);	

};


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

struct treap *create_treap();
void destroy_treap(struct treap *treap, int key);
// wrapper interfaces for the treap 
void treap_delete(struct treap *treap, int key);
int treap_search(struct treap *treap, int key);
void treap_insert(struct treap *treap, struct data_element *data);


void inorder(struct node *root);
void delete_treap_nodes(struct node *root);
void delete_treap(struct treap *treap);
